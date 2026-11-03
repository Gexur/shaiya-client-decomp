#include "graphics/native_postfx_ports.h"
#include "graphics/native_resources.h"
#include "graphics/native_render_passes.h"
#include <new>
namespace {
using namespace shaiya::graphics::native;
struct PostFx {
    Texture2D *capture = nullptr, *image = nullptr, *scratch = nullptr;
    UINT width = 0, height = 0;
};
UINT& word(void* owner, UINT offset) {
    return *reinterpret_cast<UINT*>(static_cast<unsigned char*>(owner) + offset);
}
unsigned char& flag(void* owner, UINT offset) {
    return *(static_cast<unsigned char*>(owner) + offset);
}
float scalar(void* owner, UINT offset) {
    return *reinterpret_cast<float*>(static_cast<unsigned char*>(owner) + offset);
}
PostFx* state(void* owner) {
    return reinterpret_cast<PostFx*>(word(owner, 0x88));
}
HRESULT ensure(void* owner) {
    auto* current = renderer();
    if (!current->device || !current->backbuffer)
        return E_UNEXPECTED;
    if (state(owner) && state(owner)->width == current->width &&
        state(owner)->height == current->height)
        return S_OK;
    native_postfx_release(owner);
    void* memory = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(PostFx));
    if (!memory)
        return E_OUTOFMEMORY;
    auto* value = new (memory) PostFx{};
    word(owner, 0x88) = UINT(value);
    value->width = current->width;
    value->height = current->height;
    D3D11_TEXTURE2D_DESC source = {};
    current->backbuffer->GetDesc(&source);
    if (source.SampleDesc.Count != 1) {
        native_postfx_release(owner);
        return E_INVALIDARG;
    }
    HRESULT result =
        create_texture(*current, value->width, value->height, source.Format, nullptr, 1,
                       D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET, &value->capture);
    UINT width = value->width / 2, height = value->height / 2;
    if (!width)
        width = 1;
    if (!height)
        height = 1;
    if (SUCCEEDED(result))
        result = create_render_texture(*current, width, height, &value->image);
    if (SUCCEEDED(result))
        result = create_render_texture(*current, width, height, &value->scratch);
    if (FAILED(result)) {
        native_postfx_release(owner);
        return result;
    }
    word(owner, 0x14) = UINT(value->image);
    word(owner, 0x18) = UINT(value->scratch);
    word(owner, 0x1c) = UINT(value->capture);
    word(owner, 0x20) = UINT(value->image->target);
    word(owner, 0x24) = UINT(value->scratch->target);
    word(owner, 0x28) = UINT(value->capture->target);
    return S_OK;
}
HRESULT filter(Texture2D& source, ID3D11RenderTargetView* target, UINT width, UINT height,
               GlowFilter kind, float alpha = 1, Blend blend = Blend::opaque) {
    GlowDraw draw;
    draw.source = source.view;
    draw.target = target;
    draw.width = width;
    draw.height = height;
    draw.source_texel_size[0] = 1.0f / float(source.width);
    draw.source_texel_size[1] = 1.0f / float(source.height);
    draw.filter = kind;
    draw.alpha = alpha;
    draw.blend = blend;
    return draw_glow(*renderer(), draw);
}
HRESULT capture(void* owner) {
    HRESULT result = ensure(owner);
    if (FAILED(result))
        return result;
    auto* current = renderer();
    auto* value = state(owner);
    ID3D11RenderTargetView* target = nullptr;
    ID3D11DepthStencilView* depth = nullptr;
    current->context->OMGetRenderTargets(1, &target, &depth);
    current->context->OMSetRenderTargets(0, nullptr, nullptr);
    current->context->CopyResource(value->capture->gpu, current->backbuffer);
    current->context->OMSetRenderTargets(1, &target, depth);
    if (target)
        target->Release();
    if (depth)
        depth->Release();
    return S_OK;
}
float strength(void* owner) {
    const float authored = scalar(owner, 0x8c);
    if (authored > 0 && authored <= 1)
        return authored;
    const UINT quality = word(owner, 0x90);
    return quality == 0 ? 0 : quality == 1 ? 25.0f / 255.0f : 50.0f / 255.0f;
}
} // namespace
extern "C" void native_postfx_release(void* owner) {
    if (!owner)
        return;
    auto* value = state(owner);
    if (value) {
        if (value->capture)
            value->capture->release();
        if (value->image)
            value->image->release();
        if (value->scratch)
            value->scratch->release();
        value->~PostFx();
        HeapFree(GetProcessHeap(), 0, value);
    }
    for (UINT offset = 0x14; offset <= 0x80; offset += 4)
        word(owner, offset) = 0;
    word(owner, 0x88) = 0;
}
extern "C" bool __attribute__((thiscall)) FUN_0054e670(void* owner) {
    return SUCCEEDED(ensure(owner));
}
extern "C" bool __attribute__((thiscall)) FUN_0054e7c0(void* owner) {
    HRESULT result = ensure(owner);
    word(owner, 4) = SUCCEEDED(result) ? 1 : 0;
    flag(owner, 8) = flag(owner, 9) = SUCCEEDED(result) ? 1 : 0;
    flag(owner, 0x84) = SUCCEEDED(result) ? 1 : 0;
    flag(owner, 0x86) = word(owner, 0x90) ? 1 : 0;
    return SUCCEEDED(result);
}
extern "C" HRESULT __attribute__((thiscall)) FUN_0054f020(void* owner) {
    HRESULT result = ensure(owner);
    if (FAILED(result))
        return result;
    auto* value = state(owner);
    return filter(*value->capture, value->image->target, value->image->width, value->image->height,
                  GlowFilter::eight_tap);
}
extern "C" HRESULT __attribute__((thiscall)) FUN_0054f540(void* owner) {
    HRESULT result = ensure(owner);
    if (FAILED(result))
        return result;
    auto* value = state(owner);
    result = filter(*value->image, value->scratch->target, value->scratch->width,
                    value->scratch->height, GlowFilter::gaussian_x);
    if (SUCCEEDED(result))
        result = filter(*value->scratch, value->image->target, value->image->width,
                        value->image->height, GlowFilter::gaussian_y);
    return result;
}
extern "C" HRESULT __attribute__((thiscall)) FUN_0054f250(void* owner) {
    return FUN_0054f540(owner);
}
extern "C" HRESULT __attribute__((thiscall)) FUN_0054f860(void* owner) {
    if (!flag(owner, 8) || !flag(owner, 9))
        return S_FALSE;
    HRESULT result = capture(owner);
    if (SUCCEEDED(result))
        result = FUN_0054f020(owner);
    UINT iterations = word(owner, 0xc);
    if (iterations > 16)
        iterations = 16;
    for (UINT i = 0; i < iterations && SUCCEEDED(result); ++i)
        result = FUN_0054f540(owner);
    if (FAILED(result))
        flag(owner, 8) = 0;
    return result;
}
extern "C" HRESULT __attribute__((thiscall)) FUN_0054ea70(void* owner) {
    if (!flag(owner, 0x86))
        return S_FALSE;
    HRESULT result = ensure(owner);
    if (FAILED(result))
        return result;
    auto* current = renderer();
    auto* value = state(owner);
    return filter(*value->image, current->color_target, current->width, current->height,
                  GlowFilter::copy, strength(owner), Blend::additive);
}
extern "C" HRESULT __attribute__((thiscall)) FUN_0054ee80(void* owner) {
    if (!flag(owner, 8) || !flag(owner, 9))
        return S_FALSE;
    return FUN_0054ea70(owner);
}
extern "C" HRESULT __attribute__((thiscall)) FUN_0054f980(void* owner) {
    HRESULT result = FUN_0054f860(owner);
    return FAILED(result) ? result : FUN_0054ea70(owner);
}
extern "C" HRESULT __attribute__((thiscall)) FUN_0054f170(void*, Buffer* buffer, INT width,
                                                          INT height, const float* offset) {
    if (!buffer || !offset || !buffer->asset_bytes || buffer->size < sizeof(UiVertex) * 4)
        return E_INVALIDARG;
    UiVertex vertices[4];
    for (UINT i = 0; i < 4; ++i)
        vertices[i] = reinterpret_cast<UiVertex*>(buffer->asset_bytes)[i];
    const float left = offset[0] - .5f, top = offset[1] - .5f;
    vertices[0].x = vertices[1].x = left;
    vertices[2].x = vertices[3].x = left + float(width);
    vertices[1].y = vertices[3].y = top;
    vertices[0].y = vertices[2].y = top + float(height);
    return update_buffer(*renderer(), *buffer, 0, vertices, sizeof(vertices));
}
