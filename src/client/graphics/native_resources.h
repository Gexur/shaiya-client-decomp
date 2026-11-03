#pragma once

#include "graphics/native_renderer.h"
#include <stddef.h>
#include <stdint.h>

namespace shaiya::graphics::native {

struct Texture2D {
    ID3D11Texture2D* gpu = nullptr;
    ID3D11ShaderResourceView* view = nullptr;
    ID3D11RenderTargetView* target = nullptr;
    ID3D11DepthStencilView* depth = nullptr;
    UINT width = 0, height = 0, levels = 0;
    DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
    LONG references = 1;

    void retain();
    void release();
};

enum class BufferKind { vertices, indices };
struct Buffer {
    ID3D11Buffer* gpu = nullptr;
    unsigned char* asset_bytes = nullptr;
    UINT size = 0, stride = 0;
    DXGI_FORMAT index_format = DXGI_FORMAT_UNKNOWN;
    BufferKind kind = BufferKind::vertices;
    LONG references = 1;

    void retain();
    void release();
};

struct TextureMip {
    const void* bytes = nullptr;
    UINT row_pitch = 0, slice_pitch = 0;
};

struct TextureLoadOptions {
    bool generate_mips = false;
    bool interface_power_of_two = false;
    bool color_key_enabled = false;
    uint32_t color_key = 0;
    UINT requested_width = 0, requested_height = 0;
    UINT level_limit = 0;
};

HRESULT create_texture(NativeRenderer& renderer, UINT width, UINT height, DXGI_FORMAT format,
                       const TextureMip* mips, UINT levels, UINT bindings, Texture2D** texture);
HRESULT create_render_texture(NativeRenderer& renderer, UINT width, UINT height,
                              Texture2D** texture);
HRESULT create_depth_texture(NativeRenderer& renderer, UINT width, UINT height,
                             Texture2D** texture);
HRESULT load_texture(NativeRenderer& renderer, const void* encoded, size_t size,
                     const TextureLoadOptions& options, Texture2D** texture);
HRESULT create_buffer(NativeRenderer& renderer, BufferKind kind, const void* bytes, UINT size,
                      UINT stride, DXGI_FORMAT index_format, Buffer** buffer);
HRESULT update_buffer(NativeRenderer& renderer, Buffer& buffer, UINT offset, const void* bytes,
                      UINT size);
HRESULT update_texture(NativeRenderer& renderer, Texture2D& texture, UINT x, UINT y, UINT width,
                       UINT height, const void* pixels, UINT row_pitch);
// Shared lifetime operation for opaque game asset-owner records.
void release_asset_resource(void* resource);

} // namespace shaiya::graphics::native

// Stable linkage for original MSVC exception-handling owners.
extern "C" void __cdecl native_release_asset_resource(void* resource);
