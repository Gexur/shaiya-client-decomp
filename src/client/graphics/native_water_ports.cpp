#include "graphics/native_water_ports.h"
#include "graphics/native_scene_ports.h"
#include <stdint.h>
using namespace shaiya::graphics::native;
extern "C" {
extern float dat_00719a54, dat_02207ffc;
extern const float dat_006bede8, dat_006bc860, dat_006bb62c, dat_006bca08, dat_006c127c,
    dat_006c6564, dat_006c1bc0;
extern const char dat_006c6580[], dat_006c6568[];
HRESULT __cdecl FUN_0040d480(NativeRenderer*, const char*, Texture2D**);
void __attribute__((stdcall)) native_scene_clip_plane(const float*);
}
namespace {
using Word = uint32_t __attribute__((may_alias));
Word& word(void* object, UINT offset) {
    return *reinterpret_cast<Word*>(static_cast<unsigned char*>(object) + offset);
}
template <class T> T* at(void* object, UINT offset) {
    return reinterpret_cast<T*>(static_cast<unsigned char*>(object) + offset);
}
template <class T> T*& slot(void* object, UINT offset) {
    return *at<T*>(object, offset);
}
template <class T> void release_slot(void* object, UINT offset) {
    T*& value = slot<T>(object, offset);
    if (value)
        value->release();
    value = nullptr;
}
float root(float value) {
    float result;
    __asm__ volatile("flds %1\n\tfsqrt\n\tfstps %0" : "=m"(result) : "m"(value) : "st");
    return result;
}
void trig(float value, float& cosine, float& sine) {
    __asm__ volatile("flds %2\n\tfsincos\n\tfstps %0\n\tfstps %1"
                     : "=m"(cosine), "=m"(sine)
                     : "m"(value)
                     : "st");
}
struct Water32 {
    float xyz[3];
    UINT color;
    float uv[2], reflection[2];
};
struct Water56 {
    float xyz[3], normal[3], uv[2], uv1[2], uv2[2], uv3[2];
};
struct Screen20 {
    float x, y, z, rhw;
    UINT color;
};
static_assert(sizeof(Water32) == 32 && sizeof(Water56) == 56 && sizeof(Screen20) == 20);
void clip_plane(void* owner, UINT offset) {
    native_scene_clip_plane(at<float>(owner, offset));
}
} // namespace
namespace shaiya::graphics::native {
void water_release(void* owner) {
    auto*& scope = slot<TargetScope>(owner, 0x10);
    if (scope)
        release_target_scope(scope);
    scope = nullptr;
    const UINT textures[] = {0xf0, 0xf4, 0xf8, 0x2dc, 0x2f0, 0x2f4, 0x2e8, 0x2ec};
    for (UINT offset : textures)
        release_slot<Texture2D>(owner, offset);
    release_slot<Buffer>(owner, 0x2e0);
    release_slot<Buffer>(owner, 0x2e4);
    const UINT unused[] = {0x14, 0x2d8, 0x2f8, 0x2fc};
    for (UINT offset : unused)
        word(owner, offset) = 0;
}
} // namespace shaiya::graphics::native
extern "C" void __attribute__((thiscall)) FUN_0053ded0(void* owner) {
    if (word(owner, 0) == 0) {
        dat_02207ffc += dat_00719a54 * dat_006bede8;
        auto* buffer = slot<Buffer>(owner, 0x2e0);
        if (!buffer || buffer->size < sizeof(Water32) * 4)
            return;
        auto* vertices = reinterpret_cast<Water32*>(buffer->asset_bytes);
        const float phase = dat_02207ffc * dat_006bc860;
        vertices[0].uv[0] = vertices[1].uv[0] = .5f;
        vertices[2].uv[0] = vertices[3].uv[0] = 400.5f;
        vertices[0].uv[1] = vertices[3].uv[1] = phase + dat_006bb62c;
        vertices[1].uv[1] = vertices[2].uv[1] = phase;
        update_buffer(*renderer(), *buffer, 0, buffer->asset_bytes, buffer->size);
    } else if (word(owner, 0) == 1)
        *at<float>(owner, 0x300) += dat_00719a54 * dat_006bca08;
}
namespace {
// Wrapped central differences preserve the authored height-map normal operation.
HRESULT height_normals(Texture2D& source, Texture2D** output) {
    auto& r = *renderer();
    const bool rgba = source.format == DXGI_FORMAT_R8G8B8A8_UNORM ||
                      source.format == DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    const bool bgra =
        source.format == DXGI_FORMAT_B8G8R8A8_UNORM || source.format == DXGI_FORMAT_B8G8R8X8_UNORM;
    if (!rgba && !bgra)
        return E_NOTIMPL;
    D3D11_TEXTURE2D_DESC description = {};
    source.gpu->GetDesc(&description);
    description.Usage = D3D11_USAGE_STAGING;
    description.BindFlags = 0;
    description.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    description.MiscFlags = 0;
    ID3D11Texture2D* staging = nullptr;
    HRESULT result = r.device->CreateTexture2D(&description, nullptr, &staging);
    if (FAILED(result))
        return result;
    r.context->CopyResource(staging, source.gpu);
    TextureMip mips[15] = {};
    for (UINT level = 0; level < source.levels; ++level) {
        UINT width = source.width >> level, height = source.height >> level;
        if (!width)
            width = 1;
        if (!height)
            height = 1;
        auto* pixels =
            static_cast<unsigned char*>(HeapAlloc(GetProcessHeap(), 0, size_t(width) * height * 4));
        if (!pixels) {
            result = E_OUTOFMEMORY;
            break;
        }
        mips[level] = {pixels, width * 4, width * height * 4};
        D3D11_MAPPED_SUBRESOURCE mapped = {};
        result = r.context->Map(staging, level, D3D11_MAP_READ, 0, &mapped);
        if (FAILED(result))
            break;
        const auto* bytes = static_cast<const unsigned char*>(mapped.pData);
        const UINT red = bgra ? 2 : 0;
        for (UINT y = 0; y < height; ++y)
            for (UINT x = 0; x < width; ++x) {
                UINT left = x ? x - 1 : width - 1, right = x + 1 == width ? 0 : x + 1,
                     above = y ? y - 1 : height - 1, below = y + 1 == height ? 0 : y + 1;
                float nx = (float(bytes[size_t(y) * mapped.RowPitch + left * 4 + red]) -
                            float(bytes[size_t(y) * mapped.RowPitch + right * 4 + red])) *
                           (10.0f / 255);
                float ny = (float(bytes[size_t(above) * mapped.RowPitch + x * 4 + red]) -
                            float(bytes[size_t(below) * mapped.RowPitch + x * 4 + red])) *
                           (10.0f / 255);
                const float inverse = 1 / root(nx * nx + ny * ny + 1);
                unsigned char* pixel = pixels + (size_t(y) * width + x) * 4;
                pixel[0] = static_cast<unsigned char>((nx * inverse * .5f + .5f) * 255 + .5f);
                pixel[1] = static_cast<unsigned char>((ny * inverse * .5f + .5f) * 255 + .5f);
                pixel[2] = static_cast<unsigned char>((inverse * .5f + .5f) * 255 + .5f);
                pixel[3] = 255;
            }
        r.context->Unmap(staging, level);
    }
    if (SUCCEEDED(result))
        result = create_texture(r, source.width, source.height, DXGI_FORMAT_R8G8B8A8_UNORM, mips,
                                source.levels, D3D11_BIND_SHADER_RESOURCE, output);
    for (auto& mip : mips)
        if (mip.bytes)
            HeapFree(GetProcessHeap(), 0, const_cast<void*>(mip.bytes));
    staging->Release();
    return result;
}
} // namespace
extern "C" HRESULT __attribute__((thiscall)) FUN_0053e020(void* owner) {
    auto* bytes = static_cast<unsigned char*>(HeapAlloc(GetProcessHeap(), 0, 256 * 256 * 2));
    if (!bytes)
        return E_OUTOFMEMORY;
    for (UINT y = 0; y < 256; ++y)
        for (UINT x = 0; x < 256; ++x) {
            float cosine, sine;
            trig((float(y) * dat_006c127c - dat_006bc860 + float(x) * dat_006c127c - dat_006bc860) *
                     dat_006c6564,
                 cosine, sine);
            bytes[(y * 256 + x) * 2] = static_cast<unsigned char>(int(cosine * dat_006c1bc0));
            bytes[(y * 256 + x) * 2 + 1] = static_cast<unsigned char>(int(sine * dat_006c1bc0));
        }
    TextureMip mip = {bytes, 512, 256 * 512};
    Texture2D* texture = nullptr;
    HRESULT result = create_texture(*renderer(), 256, 256, DXGI_FORMAT_R8G8_SNORM, &mip, 1,
                                    D3D11_BIND_SHADER_RESOURCE, &texture);
    HeapFree(GetProcessHeap(), 0, bytes);
    if (SUCCEEDED(result)) {
        release_slot<Texture2D>(owner, 0x2dc);
        slot<Texture2D>(owner, 0x2dc) = texture;
    }
    return result;
}
extern "C" UINT __attribute__((thiscall)) FUN_0053e150(void* owner) {
    const char* names[] = {dat_006c6580, dat_006c6568};
    const UINT offsets[] = {0x2f0, 0x2f4};
    for (UINT i = 0; i < 2; ++i) {
        Texture2D* height = nullptr;
        HRESULT result = FUN_0040d480(renderer(), names[i], &height);
        if (FAILED(result))
            return 0;
        Texture2D* normal = nullptr;
        result = height_normals(*height, &normal);
        height->release();
        if (FAILED(result))
            return 0;
        release_slot<Texture2D>(owner, offsets[i]);
        slot<Texture2D>(owner, offsets[i]) = normal;
    }
    return 1;
}
extern "C" HRESULT __attribute__((thiscall)) FUN_0053e2d0(void* owner) {
    const float width = float(word(owner, 8)) - .5f, height = float(word(owner, 12)) - .5f;
    const Screen20 vertices[] = {{-.5f, height, 0, 1, 0xff000000},
                                 {-.5f, -.5f, 0, 1, 0xff000000},
                                 {width, height, 0, 1, 0xff000000},
                                 {width, -.5f, 0, 1, 0xff000000}};
    Buffer* buffer = nullptr;
    HRESULT result = create_buffer(*renderer(), BufferKind::vertices, vertices, sizeof(vertices),
                                   sizeof(Screen20), DXGI_FORMAT_UNKNOWN, &buffer);
    if (SUCCEEDED(result)) {
        release_slot<Buffer>(owner, 0x2e4);
        slot<Buffer>(owner, 0x2e4) = buffer;
    }
    return result;
}
extern "C" UINT __attribute__((thiscall)) FUN_0053e3e0(void* owner, Texture2D* destination) {
    TargetScope* scope = slot<TargetScope>(owner, 0x10);
    if (!scope || !destination)
        return 0;
    const float white[] = {1, 1, 1, 1};
    return SUCCEEDED(begin_target(*scope, *destination, nullptr, white));
}
extern "C" UINT __attribute__((thiscall)) FUN_0053e4a0(void* owner) {
    TargetScope* scope = slot<TargetScope>(owner, 0x10);
    return scope && SUCCEEDED(end_target(*scope));
}
extern "C" void __attribute__((thiscall)) FUN_0053e660(void* owner) {
    if (!*at<unsigned char>(owner, 4) || !*at<unsigned char>(owner, 0x1d0))
        return;
    clip_plane(owner, word(owner, 0) == 0                ? 0x160
                      : *at<unsigned char>(owner, 0x304) ? 0x180
                                                         : 0x1b0);
}
extern "C" void __attribute__((thiscall)) FUN_0053e6d0(void* owner) {
    if (!*at<unsigned char>(owner, 4) || !*at<unsigned char>(owner, 0x1d0))
        return;
    clip_plane(owner, word(owner, 0) == 0                ? 0x160
                      : *at<unsigned char>(owner, 0x304) ? 0x1a0
                                                         : 0x1b0);
}
extern "C" void __attribute__((thiscall)) FUN_0053e740(void* owner) {
    if (!*at<unsigned char>(owner, 4) || !*at<unsigned char>(owner, 0x1d0))
        return;
    clip_plane(owner, word(owner, 0) == 0                ? 0x170
                      : *at<unsigned char>(owner, 0x304) ? 0x190
                                                         : 0x1c0);
}
extern "C" HRESULT __attribute__((thiscall)) FUN_0053e7b0(void* owner) {
    Buffer* buffer = nullptr;
    HRESULT result;
    if (word(owner, 0) == 0) {
        const Water32 vertices[] = {{{-2048, 0, -2048}, 0x723f9e66, {0, 0}, {0, 0}},
                                    {{-2048, 0, 2048}, 0x723f9e66, {0, 0}, {0, 0}},
                                    {{2048, 0, -2048}, 0x723f9e66, {0, 0}, {0, 0}},
                                    {{2048, 0, 2048}, 0x723f9e66, {0, 0}, {0, 0}}};
        result = create_buffer(*renderer(), BufferKind::vertices, vertices, sizeof(vertices),
                               sizeof(Water32), DXGI_FORMAT_UNKNOWN, &buffer);
    } else if (word(owner, 0) == 1) {
        const Water56 vertices[] = {
            {{-2048, 0, -2048}, {0, 1, 0}, {0, 2000}, {0, 2000}, {0, 2000}, {0, 2000}},
            {{-2048, 0, 2048}, {0, 1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
            {{2048, 0, -2048}, {0, 1, 0}, {2000, 2000}, {2000, 2000}, {2000, 2000}, {2000, 2000}},
            {{2048, 0, 2048}, {0, 1, 0}, {2000, 0}, {2000, 0}, {2000, 0}, {2000, 0}}};
        result = create_buffer(*renderer(), BufferKind::vertices, vertices, sizeof(vertices),
                               sizeof(Water56), DXGI_FORMAT_UNKNOWN, &buffer);
    } else
        return E_NOTIMPL;
    if (SUCCEEDED(result)) {
        release_slot<Buffer>(owner, 0x2e0);
        slot<Buffer>(owner, 0x2e0) = buffer;
    }
    return result;
}
extern "C" UINT __attribute__((thiscall)) FUN_0053ec60(void* owner) {
    water_release(owner);
    const UINT mode = word(owner, 0), width = word(owner, 8), height = word(owner, 12);
    if (mode > 1 || !width || !height)
        return 0;
    auto& r = *renderer();
    HRESULT result = create_target_scope(r, width, height, true, &slot<TargetScope>(owner, 0x10));
    if (SUCCEEDED(result)) {
        slot<Texture2D>(owner, 0xf0) = slot<TargetScope>(owner, 0x10)->depth;
        slot<Texture2D>(owner, 0xf0)->retain();
        result = create_render_texture(r, width, height, &slot<Texture2D>(owner, 0xf4));
    }
    if (SUCCEEDED(result) && mode == 1)
        result = create_render_texture(r, width, height, &slot<Texture2D>(owner, 0xf8));
    if (SUCCEEDED(result)) {
        if (mode == 0)
            result = FUN_0053e020(owner);
        else if (!FUN_0053e150(owner))
            result = E_FAIL;
    }
    if (SUCCEEDED(result))
        result = FUN_0053e7b0(owner);
    if (SUCCEEDED(result))
        result = FUN_0053e2d0(owner);
    if (FAILED(result)) {
        water_release(owner);
        return 0;
    }
    return 1;
}
extern "C" void __cdecl native_water_release(void* owner) {
    shaiya::graphics::native::water_release(owner);
}
