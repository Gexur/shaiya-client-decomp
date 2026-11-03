#include "graphics/native_resources.h"
#include <new>
#include <wincodec.h>

namespace shaiya::graphics::native {
namespace {
constexpr UINT maximum_dimension = 16384, maximum_levels = 15;
template <class T> void release_gpu(T*& object) {
    if (object) {
        object->Release();
        object = nullptr;
    }
}
void* allocate(size_t size) {
    return size && size <= 0x7fffffffu ? HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size)
                                       : nullptr;
}
void free_bytes(void* bytes) {
    if (bytes)
        HeapFree(GetProcessHeap(), 0, bytes);
}
void copy_bytes(void* destination, const void* source, size_t size) {
    auto* to = static_cast<unsigned char*>(destination);
    const auto* from = static_cast<const unsigned char*>(source);
    if (reinterpret_cast<uintptr_t>(to) > reinterpret_cast<uintptr_t>(from) &&
        reinterpret_cast<uintptr_t>(to) - reinterpret_cast<uintptr_t>(from) < size) {
        while (size) {
            --size;
            to[size] = from[size];
        }
    } else
        while (size--)
            *to++ = *from++;
}
template <class T> T* make() {
    void* memory = allocate(sizeof(T));
    return memory ? new (memory) T() : nullptr;
}
UINT smaller(UINT a, UINT b) {
    return a < b ? a : b;
}
UINT half(UINT value) {
    return value > 1 ? value / 2 : 1;
}
UINT mip_count(UINT width, UINT height) {
    UINT count = 1;
    for (UINT size = width > height ? width : height; size > 1; size /= 2)
        ++count;
    return count;
}
UINT power_of_two(UINT size) {
    UINT result = 1;
    while (result < size)
        result *= 2;
    return result;
}
bool valid_dimensions(UINT width, UINT height) {
    return width && height && width <= maximum_dimension && height <= maximum_dimension;
}
uint16_t read16(const unsigned char* bytes) {
    return uint16_t(bytes[0]) | uint16_t(bytes[1]) << 8;
}
uint32_t read32(const unsigned char* bytes) {
    return uint32_t(bytes[0]) | uint32_t(bytes[1]) << 8 | uint32_t(bytes[2]) << 16 |
           uint32_t(bytes[3]) << 24;
}
UINT divide_channel(uint64_t numerator, UINT denominator) {
    UINT quotient, remainder;
    __asm__("divl %4"
            : "=a"(quotient), "=d"(remainder)
            : "a"(UINT(numerator)), "d"(UINT(numerator >> 32)), "rm"(denominator)
            : "cc");
    return quotient;
}
UINT block_size(DXGI_FORMAT format) {
    switch (format) {
    case DXGI_FORMAT_BC1_UNORM:
    case DXGI_FORMAT_BC1_UNORM_SRGB:
    case DXGI_FORMAT_BC4_UNORM:
    case DXGI_FORMAT_BC4_SNORM:
        return 8;
    case DXGI_FORMAT_BC2_UNORM:
    case DXGI_FORMAT_BC2_UNORM_SRGB:
    case DXGI_FORMAT_BC3_UNORM:
    case DXGI_FORMAT_BC3_UNORM_SRGB:
    case DXGI_FORMAT_BC5_UNORM:
    case DXGI_FORMAT_BC5_SNORM:
    case DXGI_FORMAT_BC6H_UF16:
    case DXGI_FORMAT_BC6H_SF16:
    case DXGI_FORMAT_BC7_UNORM:
    case DXGI_FORMAT_BC7_UNORM_SRGB:
        return 16;
    default:
        return 0;
    }
}
UINT pixel_size(DXGI_FORMAT format) {
    switch (format) {
    case DXGI_FORMAT_R8_UNORM:
    case DXGI_FORMAT_A8_UNORM:
        return 1;
    case DXGI_FORMAT_R8G8_UNORM:
    case DXGI_FORMAT_R8G8_SNORM:
    case DXGI_FORMAT_R16_UNORM:
    case DXGI_FORMAT_B5G6R5_UNORM:
    case DXGI_FORMAT_B5G5R5A1_UNORM:
    case DXGI_FORMAT_B4G4R4A4_UNORM:
        return 2;
    case DXGI_FORMAT_R8G8B8A8_UNORM:
    case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
    case DXGI_FORMAT_B8G8R8A8_UNORM:
    case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
    case DXGI_FORMAT_B8G8R8X8_UNORM:
    case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
    case DXGI_FORMAT_R10G10B10A2_UNORM:
    case DXGI_FORMAT_R16G16_FLOAT:
    case DXGI_FORMAT_R32_FLOAT:
    case DXGI_FORMAT_R24G8_TYPELESS:
    case DXGI_FORMAT_D24_UNORM_S8_UINT:
        return 4;
    case DXGI_FORMAT_R16G16B16A16_FLOAT:
        return 8;
    default:
        return 0;
    }
}
struct Image {
    UINT width = 0, height = 0;
    unsigned char* pixels = nullptr;
    void clear() {
        free_bytes(pixels);
        pixels = nullptr;
    }
    HRESULT initialize(UINT w, UINT h) {
        if (!valid_dimensions(w, h))
            return E_INVALIDARG;
        width = w;
        height = h;
        pixels = static_cast<unsigned char*>(allocate(size_t(w) * h * 4));
        return pixels ? S_OK : E_OUTOFMEMORY;
    }
};
struct Cursor {
    const unsigned char* bytes;
    size_t size, offset;
    const unsigned char* take(size_t length) {
        if (offset > size || length > size - offset)
            return nullptr;
        const auto* result = bytes + offset;
        offset += length;
        return result;
    }
};
// Asset decoders and quality filters port the existing Zig native renderer.
#include "graphics/native_texture_decode.inc"
} // namespace

void Texture2D::retain() {
    InterlockedIncrement(&references);
}
void Texture2D::release() {
    if (InterlockedDecrement(&references))
        return;
    release_gpu(depth);
    release_gpu(target);
    release_gpu(view);
    release_gpu(gpu);
    this->~Texture2D();
    free_bytes(this);
}
void Buffer::retain() {
    InterlockedIncrement(&references);
}
void Buffer::release() {
    if (InterlockedDecrement(&references))
        return;
    release_gpu(gpu);
    free_bytes(asset_bytes);
    this->~Buffer();
    free_bytes(this);
}
void release_asset_resource(void* object) {
    if (!object)
        return;
    ID3D11Resource* gpu = nullptr;
    copy_bytes(&gpu, object, sizeof(gpu));
    D3D11_RESOURCE_DIMENSION dimension = D3D11_RESOURCE_DIMENSION_UNKNOWN;
    gpu->GetType(&dimension);
    if (dimension == D3D11_RESOURCE_DIMENSION_BUFFER)
        static_cast<Buffer*>(object)->release();
    else if (dimension == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
        static_cast<Texture2D*>(object)->release();
}
HRESULT create_texture(NativeRenderer& renderer, UINT width, UINT height, DXGI_FORMAT format,
                       const TextureMip* mips, UINT levels, UINT bindings, Texture2D** out) {
    if (!out)
        return E_POINTER;
    *out = nullptr;
    if (!renderer.device || !valid_dimensions(width, height) || !levels ||
        levels > mip_count(width, height) || (!block_size(format) && !pixel_size(format)) ||
        !bindings ||
        (bindings &
         ~(D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET | D3D11_BIND_DEPTH_STENCIL)))
        return E_INVALIDARG;
    D3D11_SUBRESOURCE_DATA data[maximum_levels] = {};
    if (mips) {
        UINT w = width, h = height, block = block_size(format), bytes = pixel_size(format);
        for (UINT level = 0; level < levels; ++level) {
            UINT pitch = block ? ((w + 3) / 4) * block : w * bytes, rows = block ? (h + 3) / 4 : h;
            if (!mips[level].bytes || mips[level].row_pitch < pitch ||
                mips[level].slice_pitch < size_t(mips[level].row_pitch) * rows)
                return E_INVALIDARG;
            data[level] = {mips[level].bytes, mips[level].row_pitch, mips[level].slice_pitch};
            w = half(w);
            h = half(h);
        }
    }
    auto* texture = make<Texture2D>();
    if (!texture)
        return E_OUTOFMEMORY;
    texture->width = width;
    texture->height = height;
    texture->levels = levels;
    texture->format = format;
    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = levels;
    desc.ArraySize = 1;
    desc.Format = format;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = bindings;
    HRESULT result = renderer.device->CreateTexture2D(&desc, mips ? data : nullptr, &texture->gpu);
    if (SUCCEEDED(result) && (bindings & D3D11_BIND_SHADER_RESOURCE)) {
        D3D11_SHADER_RESOURCE_VIEW_DESC view = {};
        view.Format =
            format == DXGI_FORMAT_R24G8_TYPELESS ? DXGI_FORMAT_R24_UNORM_X8_TYPELESS : format;
        view.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        view.Texture2D.MipLevels = levels;
        result = renderer.device->CreateShaderResourceView(texture->gpu, &view, &texture->view);
    }
    if (SUCCEEDED(result) && (bindings & D3D11_BIND_RENDER_TARGET))
        result = renderer.device->CreateRenderTargetView(texture->gpu, nullptr, &texture->target);
    if (SUCCEEDED(result) && (bindings & D3D11_BIND_DEPTH_STENCIL)) {
        D3D11_DEPTH_STENCIL_VIEW_DESC depth = {};
        depth.Format =
            format == DXGI_FORMAT_R24G8_TYPELESS ? DXGI_FORMAT_D24_UNORM_S8_UINT : format;
        depth.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        result = renderer.device->CreateDepthStencilView(texture->gpu, &depth, &texture->depth);
    }
    if (FAILED(result)) {
        texture->release();
        return result;
    }
    *out = texture;
    return S_OK;
}
HRESULT create_render_texture(NativeRenderer& renderer, UINT width, UINT height,
                              Texture2D** texture) {
    return create_texture(renderer, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, nullptr, 1,
                          D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE, texture);
}
HRESULT create_depth_texture(NativeRenderer& renderer, UINT width, UINT height,
                             Texture2D** texture) {
    return create_texture(renderer, width, height, DXGI_FORMAT_R24G8_TYPELESS, nullptr, 1,
                          D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE, texture);
}
HRESULT create_buffer(NativeRenderer& renderer, BufferKind kind, const void* bytes, UINT size,
                      UINT stride, DXGI_FORMAT index_format, Buffer** out) {
    if (!out)
        return E_POINTER;
    *out = nullptr;
    if (!renderer.device || !size || !stride || size % stride ||
        (kind == BufferKind::indices && ((index_format != DXGI_FORMAT_R16_UINT || stride != 2) &&
                                         (index_format != DXGI_FORMAT_R32_UINT || stride != 4))))
        return E_INVALIDARG;
    auto* buffer = make<Buffer>();
    if (!buffer)
        return E_OUTOFMEMORY;
    buffer->asset_bytes = static_cast<unsigned char*>(allocate(size));
    if (!buffer->asset_bytes) {
        buffer->release();
        return E_OUTOFMEMORY;
    }
    buffer->kind = kind;
    buffer->size = size;
    buffer->stride = stride;
    buffer->index_format = kind == BufferKind::indices ? index_format : DXGI_FORMAT_UNKNOWN;
    if (bytes)
        copy_bytes(buffer->asset_bytes, bytes, size);
    D3D11_BUFFER_DESC desc = {};
    desc.ByteWidth = size;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags =
        kind == BufferKind::vertices ? D3D11_BIND_VERTEX_BUFFER : D3D11_BIND_INDEX_BUFFER;
    D3D11_SUBRESOURCE_DATA initial = {};
    initial.pSysMem = buffer->asset_bytes;
    HRESULT result = renderer.device->CreateBuffer(&desc, &initial, &buffer->gpu);
    if (FAILED(result)) {
        buffer->release();
        return result;
    }
    *out = buffer;
    return S_OK;
}
HRESULT update_buffer(NativeRenderer& renderer, Buffer& buffer, UINT offset, const void* bytes,
                      UINT size) {
    if (!renderer.context || !renderer.device || !buffer.gpu || !bytes || offset > buffer.size ||
        size > buffer.size - offset)
        return E_INVALIDARG;
    if (!size)
        return S_OK;
    copy_bytes(buffer.asset_bytes + offset, bytes, size);
    renderer.context->UpdateSubresource(buffer.gpu, 0, nullptr, buffer.asset_bytes, 0, 0);
    return renderer.device->GetDeviceRemovedReason();
}
HRESULT update_texture(NativeRenderer& renderer, Texture2D& texture, UINT x, UINT y, UINT width,
                       UINT height, const void* pixels, UINT row_pitch) {
    UINT bytes = pixel_size(texture.format);
    if (!renderer.context || !renderer.device || !texture.gpu || !pixels ||
        block_size(texture.format) || !bytes || !width || !height || x > texture.width ||
        y > texture.height || width > texture.width - x || height > texture.height - y ||
        row_pitch < width * bytes)
        return E_INVALIDARG;
    D3D11_BOX area = {x, y, 0, x + width, y + height, 1};
    renderer.context->UpdateSubresource(texture.gpu, 0, &area, pixels, row_pitch, 0);
    return renderer.device->GetDeviceRemovedReason();
}
HRESULT load_texture(NativeRenderer& renderer, const void* encoded, size_t size,
                     const TextureLoadOptions& options, Texture2D** out) {
    if (!out)
        return E_POINTER;
    *out = nullptr;
    if (!encoded || !size || options.level_limit > maximum_levels)
        return E_INVALIDARG;
    const auto* bytes = static_cast<const unsigned char*>(encoded);
    bool is_dds = size >= 4 && read32(bytes) == 0x20534444;
    Dds dds;
    Image levels[maximum_levels];
    HRESULT result = S_OK;
    if (is_dds)
        result = parse_dds(bytes, size, dds);
    else if (size >= 2 && bytes[0] == 'B' && bytes[1] == 'M')
        result = decode_bmp(bytes, size, levels[0]);
    else if (size >= 18 && (bytes[2] == 1 || bytes[2] == 2 || bytes[2] == 3 || bytes[2] == 9 ||
                            bytes[2] == 10 || bytes[2] == 11))
        result = decode_tga(bytes, size, levels[0]);
    else
        result = decode_wic(bytes, size, levels[0]);
    if (SUCCEEDED(result)) {
        UINT source_width = is_dds ? dds.width : levels[0].width,
             source_height = is_dds ? dds.height : levels[0].height;
        UINT width = options.requested_width          ? options.requested_width
                     : options.interface_power_of_two ? power_of_two(source_width)
                                                      : source_width;
        UINT height = options.requested_height         ? options.requested_height
                      : options.interface_power_of_two ? power_of_two(source_height)
                                                       : source_height;
        UINT count = options.generate_mips ? mip_count(width, height) : is_dds ? dds.levels : 1;
        if (options.interface_power_of_two && !options.generate_mips)
            count = 1;
        if (options.level_limit)
            count = smaller(count, options.level_limit);
        if (!valid_dimensions(width, height) || count > mip_count(width, height))
            result = E_INVALIDARG;
        else if (is_dds && dds.format != DXGI_FORMAT_UNKNOWN && !dds.premultiplied &&
                 !options.color_key_enabled && width == source_width && height == source_height &&
                 count <= dds.levels)
            result = create_texture(renderer, width, height, dds.format, dds.mips, count,
                                    D3D11_BIND_SHADER_RESOURCE, out);
        else {
            UINT w = width, h = height;
            for (UINT level = 0; level < count && SUCCEEDED(result); ++level) {
                if (is_dds && level < dds.levels)
                    result = decode_dds_level(dds, level, levels[level]);
                else if (level)
                    result = box_mip(levels[level - 1], levels[level]);
                if (SUCCEEDED(result) && options.color_key_enabled)
                    apply_color_key(levels[level], options.color_key);
                if (SUCCEEDED(result) && (levels[level].width != w || levels[level].height != h)) {
                    Image resized;
                    result = resize_triangle(levels[level], w, h, resized);
                    levels[level].clear();
                    levels[level] = resized;
                }
                w = half(w);
                h = half(h);
            }
            if (SUCCEEDED(result)) {
                TextureMip mips[maximum_levels];
                for (UINT level = 0; level < count; ++level)
                    mips[level] = {levels[level].pixels, levels[level].width * 4,
                                   levels[level].width * levels[level].height * 4};
                result = create_texture(renderer, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, mips,
                                        count, D3D11_BIND_SHADER_RESOURCE, out);
            }
        }
    }
    for (auto& image : levels)
        image.clear();
    return result;
}
} // namespace shaiya::graphics::native
extern "C" void __cdecl native_release_asset_resource(void* resource) {
    shaiya::graphics::native::release_asset_resource(resource);
}
