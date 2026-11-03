#include "graphics/native_resources.h"
#include "graphics/native_render_target.h"
#include "archive/saf.h"
#include "archive/saf_open.h"
#include "core/com_payload520.h"
#include "runtime/allocations.h"
#include "runtime/file_ops.h"
#include "config/initialization.hpp"
#include "graphics/native_scene_ports.h"

using namespace shaiya::graphics::native;
extern "C" {
extern NativeRenderer* dat_02209400;
extern unsigned char dat_0070ca48;
extern uint32_t dat_0070ca4c;
extern OriginalSafFile* dat_0224e398;
extern unsigned char dat_0224e560[];
extern const char dat_006be1d4[];
extern const char dat_006be1dc[], dat_006bcc50[], dat_006c1214[], dat_006c97b4[];
extern Texture2D* dat_0071c568;
int32_t __cdecl FUN_005ac310(const char*);
void* __cdecl FUN_005afc20();
void* __attribute__((thiscall)) FUN_005a4a90(void*, const char*, const char*);
uint32_t __attribute__((thiscall)) FUN_005aff00(void*, const char*, const char*);
uint32_t __attribute__((thiscall)) FUN_005a3cc0(void*, uint32_t, uint32_t);
void __attribute__((thiscall)) FUN_005ad860(void*);
}
namespace {
using Word = uint32_t __attribute__((may_alias));
uint32_t& field(void* object, UINT offset) {
    return *reinterpret_cast<Word*>(static_cast<unsigned char*>(object) + offset);
}
void* pointer(void* object, UINT offset) {
    return reinterpret_cast<void*>(field(object, offset));
}
template <class T> T* resource(void* object, UINT offset) {
    return static_cast<T*>(pointer(object, offset));
}
void set_pointer(void* object, UINT offset, const void* value) {
    field(object, offset) = UINT(reinterpret_cast<uintptr_t>(value));
}
void copy(void* destination, const void* source, UINT bytes) {
    auto* to = static_cast<unsigned char*>(destination);
    const auto* from = static_cast<const unsigned char*>(source);
    while (bytes--)
        *to++ = *from++;
}
bool copy_name(char* destination, UINT capacity, const char* source) {
    if (!source || !capacity)
        return false;
    UINT i = 0;
    while (source[i] && i + 1 < capacity) {
        destination[i] = source[i];
        ++i;
    }
    destination[i] = 0;
    return !source[i];
}
bool path(char* result, UINT capacity, const char* directory, const char* name) {
    if (!directory || !name || !copy_name(result, capacity, directory))
        return false;
    UINT length = 0;
    while (result[length])
        ++length;
    if (length + 1 >= capacity)
        return false;
    result[length++] = '\\';
    return copy_name(result + length, capacity - length, name);
}
void release_texture(void* owner, UINT offset) {
    auto* image = resource<Texture2D>(owner, offset);
    if (image)
        image->release();
    field(owner, offset) = 0;
}
void release_buffer(void* owner, UINT offset) {
    auto* buffer = resource<Buffer>(owner, offset);
    if (buffer)
        buffer->release();
    field(owner, offset) = 0;
}
bool stream_read(void* stream, void* destination, UINT bytes) {
    return stream && fun_005ce53d(int32_t(field(stream, 0)), destination, bytes) == int32_t(bytes);
}
int32_t world_texture_descriptor(const char* name) {
    // The recovered world opener takes its mode in EBX and its path on stack.
    int32_t result;
    const char* mode = "rb";
    __asm__ volatile("pushl %2\n\tcall _FUN_005ac310\n\taddl $4, %%esp"
                     : "=a"(result), "+b"(mode)
                     : "r"(name)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
HRESULT archive_texture(const char* name, bool world, const TextureLoadOptions& options,
                        Texture2D** output) {
    if (!output)
        return E_POINTER;
    *output = nullptr;
    if (!dat_02209400 || !name)
        return E_INVALIDARG;
    int32_t descriptor =
        world ? world_texture_descriptor(name) : open_archive_or_loose_file(name, "rb");
    if (!descriptor)
        return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    OriginalSafFile* entry = world ? dat_0224e398 : dat_00719e80;
    UINT size = entry ? entry->byte_length : 0;
    if (!size) {
        _close(descriptor);
        return E_INVALIDARG;
    }
    void* bytes = fun_005cc96d(size);
    if (!bytes) {
        _close(descriptor);
        return E_OUTOFMEMORY;
    }
    HRESULT result = fun_005ce53d(descriptor, bytes, size) == int32_t(size)
                         ? load_texture(*dat_02209400, bytes, size, options, output)
                         : HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);
    _close(descriptor);
    fun_005cc620(bytes);
    return result;
}
TextureLoadOptions quality_options(UINT width, UINT height, UINT levels, UINT color_key) {
    TextureLoadOptions options;
    options.interface_power_of_two = true;
    options.generate_mips = levels != 1;
    if (width && width != 0xffffffffu)
        options.requested_width = width;
    if (height && height != 0xffffffffu)
        options.requested_height = height;
    if (levels && levels <= 15)
        options.level_limit = levels;
    options.color_key_enabled = color_key != 0;
    options.color_key = color_key;
    return options;
}
HRESULT archive_entry(const char* name, bool world, UINT width, UINT height, UINT levels, UINT key,
                      void* information, Texture2D** output) {
    HRESULT result =
        archive_texture(name, world, quality_options(width, height, levels, key), output);
    if (SUCCEEDED(result) && information) {
        field(information, 0) = (*output)->width;
        field(information, 4) = (*output)->height;
        field(information, 8) = 1;
        field(information, 12) = (*output)->levels;
    }
    return result;
}
bool read_gpu_buffer(void* owner, UINT offset, void* stream, UINT count, UINT stride,
                     BufferKind kind) {
    if (!dat_02209400 || !count || count > 0x7fffffffu / stride)
        return false;
    Buffer* buffer = nullptr;
    if (FAILED(create_buffer(
            *dat_02209400, kind, nullptr, count * stride, stride,
            kind == BufferKind::indices ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_UNKNOWN, &buffer)))
        return false;
    bool okay =
        stream_read(stream, buffer->asset_bytes, count * stride) &&
        SUCCEEDED(update_buffer(*dat_02209400, *buffer, 0, buffer->asset_bytes, count * stride));
    if (!okay) {
        buffer->release();
        return false;
    }
    release_buffer(owner, offset);
    set_pointer(owner, offset, buffer);
    return true;
}
bool load_mesh_texture(void* stream, const char* directory, void* owner, UINT offset) {
    UINT length = 0;
    if (!stream_read(stream, &length, 4) || length > 256)
        return false;
    char name[257] = {};
    if (length && !stream_read(stream, name, length))
        return false;
    if (!length || !name[0])
        return true;
    void* texture = nullptr;
    if (dat_0070ca48)
        texture = FUN_005a4a90(dat_0224e560, static_cast<const char*>(FUN_005afc20()), name);
    else {
        auto* material =
            static_cast<OriginalComPayload520*>(fun_005cc96d(sizeof(OriginalComPayload520)));
        if (!material)
            return false;
        material->vtable = dat_006cf410;
        material->first[0] = material->second[0] = 0;
        material->resource = nullptr;
        texture = material;
        FUN_005aff00(material, directory, name);
    }
    set_pointer(owner, offset, texture);
    return true;
}
bool append_collision(void* output, const Buffer* vertices, const Buffer* indices, UINT count,
                      UINT triangles, UINT stride, UINT& vertex_cursor, UINT& index_cursor) {
    if ((count && (!vertices || vertices->size < size_t(count) * stride)) ||
        (triangles && (!indices || indices->size < size_t(triangles) * 6)))
        return false;
    auto* positions = static_cast<unsigned char*>(pointer(output, 0));
    auto* faces = static_cast<uint16_t*>(pointer(output, 4));
    if ((count && !positions) || (triangles && !faces))
        return false;
    UINT base = vertex_cursor;
    for (UINT i = 0; i < count; ++i)
        copy(positions + size_t(vertex_cursor++) * 12, vertices->asset_bytes + size_t(i) * stride,
             12);
    const auto* source =
        indices ? reinterpret_cast<const uint16_t*>(indices->asset_bytes) : nullptr;
    for (UINT i = 0; i < triangles * 3; ++i)
        faces[index_cursor++] = static_cast<uint16_t>(source[i] + base);
    return true;
}
} // namespace

extern "C" int32_t __cdecl FUN_0040d550(NativeRenderer*, const char* name, UINT width, UINT height,
                                        UINT levels, UINT, UINT, UINT, UINT, UINT, UINT key,
                                        void* information, void*, Texture2D** output) {
    return archive_entry(name, false, width, height, levels, key, information, output);
}
extern "C" int32_t __cdecl FUN_005ac500(NativeRenderer*, const char* name, UINT width, UINT height,
                                        UINT levels, UINT, UINT, UINT, UINT, UINT, UINT key,
                                        void* information, void*, Texture2D** output) {
    return archive_entry(name, true, width, height, levels, key, information, output);
}
extern "C" UINT __attribute__((thiscall)) FUN_005497a0(void* self, const char* directory,
                                                       const char* name, int display_width,
                                                       int display_height) {
    release_texture(self, 0);
    release_texture(self, 4);
    char filename[1024];
    if (!path(filename, sizeof(filename), directory, name))
        return 0;
    Texture2D* image = nullptr;
    TextureLoadOptions options;
    options.interface_power_of_two = true;
    options.level_limit = 1;
    if (FAILED(archive_texture(filename, false, options, &image)))
        return 0;
    set_pointer(self, 0, image);
    auto* dimensions = reinterpret_cast<float*>(static_cast<unsigned char*>(self) + 8);
    dimensions[0] = !display_width && !display_height ? float(image->width) : float(display_width);
    dimensions[1] =
        !display_width && !display_height ? float(image->height) : float(display_height);
    return 1;
}
extern "C" UINT __attribute__((thiscall)) FUN_005aff00(void* self, const char* directory,
                                                       const char* name) {
    char filename[1024];
    if (!path(filename, sizeof(filename), directory, name))
        return 0;
    Texture2D* image = nullptr;
    auto options = quality_options(0xffffffffu, dat_0070ca4c, 0xffffffffu, 0);
    if (FAILED(archive_texture(filename, true, options, &image)))
        return 0;
    release_texture(self, 0x204);
    set_pointer(self, 0x204, image);
    copy_name(reinterpret_cast<char*>(self) + 4, 256, name);
    copy_name(reinterpret_cast<char*>(self) + 0x104, 256, filename);
    return 1;
}
extern "C" UINT __attribute__((thiscall)) FUN_005affe0(void* self, const char* directory,
                                                       const char* name) {
    char filename[1024];
    if (!path(filename, sizeof(filename), directory, name))
        return 0;
    UINT height = dat_0070ca4c == 128 ? 256 : dat_0070ca4c == 64 ? 128 : dat_0070ca4c;
    Texture2D* image = nullptr;
    auto options = quality_options(0xffffffffu, height, 0xffffffffu, 0);
    HRESULT result = archive_texture(filename, true, options, &image);
    release_texture(self, 0x204);
    set_pointer(self, 0x204, image);
    copy_name(reinterpret_cast<char*>(self) + 4, 256, name);
    copy_name(reinterpret_cast<char*>(self) + 0x104, 256, filename);
    return SUCCEEDED(result);
}
extern "C" UINT __attribute__((thiscall)) FUN_005a4bd0(void* self, UINT triangles) {
    if (!dat_02209400 || !triangles || triangles > 0x7fffffffu / 6)
        return 0;
    Buffer* buffer = nullptr;
    if (FAILED(create_buffer(*dat_02209400, BufferKind::indices, nullptr, triangles * 6, 2,
                             DXGI_FORMAT_R16_UINT, &buffer)))
        return 0;
    release_buffer(self, 4);
    set_pointer(self, 4, buffer);
    field(self, 0xc) = triangles * 3;
    return 1;
}
extern "C" UINT __attribute__((thiscall)) FUN_005a50b0(void* self, void* stream) {
    if (!stream_read(stream, static_cast<unsigned char*>(self) + 0x1c, 4) ||
        !stream_read(stream, static_cast<unsigned char*>(self) + 0x10, 4))
        return 0;
    UINT vertices = field(self, 0x10);
    if (!vertices)
        return 1;
    field(self, 8) = vertices;
    if (!read_gpu_buffer(self, 0, stream, vertices, 44, BufferKind::vertices) ||
        !stream_read(stream, static_cast<unsigned char*>(self) + 0x14, 4))
        return 0;
    UINT triangles = field(self, 0x14);
    if (!triangles)
        return 1;
    if (triangles > 0x7fffffffu / 6)
        return 0;
    field(self, 0xc) = triangles * 3;
    return read_gpu_buffer(self, 4, stream, triangles * 3, 2, BufferKind::indices);
}
extern "C" UINT __attribute__((thiscall)) FUN_005ae780(void* self, const char* directory,
                                                       void* stream) {
    if (!load_mesh_texture(stream, directory, self, 0x1c) ||
        !stream_read(stream, static_cast<unsigned char*>(self) + 0x10, 4))
        return 0;
    UINT vertices = field(self, 0x10);
    field(self, 8) = vertices;
    if (vertices && !read_gpu_buffer(self, 0, stream, vertices, 36, BufferKind::vertices))
        return 0;
    if (!stream_read(stream, static_cast<unsigned char*>(self) + 0x14, 4))
        return 0;
    UINT triangles = field(self, 0x14);
    if (!triangles)
        return 1;
    if (triangles > 0x7fffffffu / 6)
        return 0;
    field(self, 0xc) = triangles * 3;
    return read_gpu_buffer(self, 4, stream, triangles * 3, 2, BufferKind::indices);
}
extern "C" void __attribute__((thiscall)) FUN_005ae480(void* self) {
    auto* material = resource<OriginalComPayload520>(self, 0x1c);
    if (material && !dat_0070ca48)
        FUN_005a37f0(material, 1);
    release_buffer(self, 0);
    release_buffer(self, 4);
}
extern "C" UINT __attribute__((thiscall)) FUN_005ade20(void* self, const char* directory,
                                                       void* stream, UINT frames) {
    if (!frames || frames > 0x7fffffffu / 4 || !load_mesh_texture(stream, directory, self, 0) ||
        !stream_read(stream, static_cast<unsigned char*>(self) + 0xc, 4))
        return 0;
    UINT triangles = field(self, 0xc);
    if (!triangles || triangles > 0x7fffffffu / 6)
        return 0;
    if (!read_gpu_buffer(self, 0x10, stream, triangles * 3, 2, BufferKind::indices) ||
        !stream_read(stream, static_cast<unsigned char*>(self) + 8, 4))
        return 0;
    UINT vertices = field(self, 8);
    if (!vertices)
        return 0;
    auto* buffers = static_cast<Buffer**>(fun_005cde20(frames * sizeof(Buffer*)));
    if (!buffers)
        return 0;
    for (UINT i = 0; i < frames; ++i)
        buffers[i] = nullptr;
    for (UINT i = 0; i < frames; ++i) {
        if (!read_gpu_buffer(buffers, i * sizeof(Buffer*), stream, vertices, 36,
                             BufferKind::vertices)) {
            for (UINT j = 0; j < i; ++j)
                buffers[j]->release();
            fun_005cdc59(buffers);
            return 0;
        }
    }
    auto** previous = static_cast<Buffer**>(pointer(self, 0x14));
    if (previous) {
        for (UINT i = 0; i < field(self, 4); ++i)
            if (previous[i])
                previous[i]->release();
        fun_005cdc59(previous);
    }
    set_pointer(self, 0x14, buffers);
    field(self, 4) = frames;
    return 1;
}
extern "C" void __attribute__((thiscall)) FUN_005a3ac0(void* group, void* output) {
    auto* meshes = static_cast<unsigned char*>(pointer(group, 8));
    UINT vertex_cursor = field(output, 8), index_cursor = field(output, 16);
    for (UINT i = 0; i < field(group, 4); ++i) {
        void* mesh = meshes + i * 32;
        if (!append_collision(output, resource<Buffer>(mesh, 0), resource<Buffer>(mesh, 4),
                              field(mesh, 16), field(mesh, 20), 44, vertex_cursor, index_cursor))
            return;
    }
    field(output, 8) = vertex_cursor;
    field(output, 16) = index_cursor;
}
extern "C" UINT __attribute__((thiscall)) FUN_005ae590(void* model) {
    UINT total_vertices = field(model, 0x160), triangles = field(model, 0x15c),
         count = field(model, 0);
    if (total_vertices > 0xffff)
        return 1;
    if (!count)
        return 0;
    if (field(model, 0x150))
        return 1;
    auto* output = static_cast<unsigned char*>(model) + 0x148;
    if (!FUN_005a3cc0(output, total_vertices, triangles))
        return 0;
    field(model, 0x150) = total_vertices;
    field(model, 0x154) = triangles;
    field(model, 0x158) = triangles * 3;
    UINT vertex_cursor = 0, index_cursor = 0;
    auto* meshes = static_cast<unsigned char*>(pointer(model, 4));
    for (UINT i = 0; i < count; ++i) {
        void* mesh = meshes + i * 32;
        if (!field(mesh, 16) || !field(mesh, 20))
            continue;
        if (!append_collision(output, resource<Buffer>(mesh, 0), resource<Buffer>(mesh, 4),
                              field(mesh, 16), field(mesh, 20), 36, vertex_cursor, index_cursor))
            return 0;
    }
    FUN_005ad860(output);
    return 1;
}
extern "C" UINT __attribute__((thiscall)) FUN_005adc10(void* model) {
    UINT count = field(model, 0x140);
    if (!count)
        return 0;
    if (field(model, 0x160))
        return 1;
    UINT vertices = field(model, 0x150), triangles = field(model, 0x14c);
    auto* output = static_cast<unsigned char*>(model) + 0x158;
    if (!FUN_005a3cc0(output, vertices, triangles))
        return 0;
    field(model, 0x160) = vertices;
    field(model, 0x164) = triangles;
    field(model, 0x168) = triangles * 3;
    UINT vertex_cursor = 0, index_cursor = 0;
    auto* meshes = static_cast<unsigned char*>(pointer(model, 0x154));
    for (UINT i = 0; i < count; ++i) {
        void* mesh = meshes + i * 24;
        auto** frames = static_cast<Buffer**>(pointer(mesh, 0x14));
        if (!frames ||
            !append_collision(output, frames[0], resource<Buffer>(mesh, 0x10), field(mesh, 8),
                              field(mesh, 0xc), 36, vertex_cursor, index_cursor))
            return 0;
    }
    FUN_005ad860(output);
    return 1;
}

// Native operations used by the unchanged CPU portions of asset builders.
// Their call sites supply explicit layout sizes; no graphics format/state code
// or legacy device interface enters these operations.
extern "C" HRESULT __stdcall native_vertex_asset(Buffer** output, UINT bytes, UINT stride) {
    return dat_02209400 ? create_buffer(*dat_02209400, BufferKind::vertices, nullptr, bytes, stride,
                                        DXGI_FORMAT_UNKNOWN, output)
                        : E_UNEXPECTED;
}
extern "C" HRESULT __stdcall native_index_asset(Buffer** output, UINT bytes) {
    return dat_02209400 ? create_buffer(*dat_02209400, BufferKind::indices, nullptr, bytes, 2,
                                        DXGI_FORMAT_R16_UINT, output)
                        : E_UNEXPECTED;
}
extern "C" HRESULT __stdcall native_asset_span(Buffer* buffer, UINT offset, UINT bytes,
                                               void** output) {
    if (!buffer || !output || offset > buffer->size || bytes > buffer->size - offset)
        return E_INVALIDARG;
    *output = buffer->asset_bytes + offset;
    return S_OK;
}
extern "C" HRESULT __stdcall native_upload_asset(Buffer* buffer) {
    return dat_02209400 && buffer
               ? update_buffer(*dat_02209400, *buffer, 0, buffer->asset_bytes, buffer->size)
               : E_INVALIDARG;
}
extern "C" void __stdcall native_release_asset(Buffer* buffer) {
    if (buffer)
        buffer->release();
}
extern "C" HRESULT __cdecl FUN_0040d480(NativeRenderer*, const char* name, Texture2D** output) {
    TextureLoadOptions options;
    options.interface_power_of_two = true;
    options.generate_mips = true;
    return archive_texture(name, false, options, output);
}
extern "C" UINT __attribute__((thiscall)) FUN_0053db20(void* owner, const char* directory,
                                                       const char* name) {
    release_texture(owner, 4);
    wsprintfA(reinterpret_cast<char*>(owner) + 8, dat_006be1d4, directory, name);
    return 1;
}
extern "C" UINT __attribute__((thiscall)) FUN_0053db60(void* owner, const char* name) {
    release_texture(owner, 4);
    UINT size = shaiya::config::DAT_007198ac;
    if (size == 128)
        size = 256;
    else if (size == 64)
        size = 128;
    return SUCCEEDED(
        archive_entry(name, false, size, size, 0xffffffffu, 0, nullptr,
                      reinterpret_cast<Texture2D**>(static_cast<unsigned char*>(owner) + 4)));
}
extern "C" UINT __attribute__((thiscall)) FUN_0053dbd0(void* owner, const char* name) {
    release_texture(owner, 4);
    return SUCCEEDED(
        archive_entry(name, false, 0xffffffffu, 0xffffffffu, 0xffffffffu, 0, nullptr,
                      reinterpret_cast<Texture2D**>(static_cast<unsigned char*>(owner) + 4)));
}
extern "C" void __attribute__((thiscall)) FUN_0053dc20(void* owner) {
    set_scene_diffuse(resource<Texture2D>(owner, 4));
}
extern "C" void __attribute__((stdcall)) native_actor_environment(Texture2D* image) {
    set_scene_environment(image);
}
extern "C" void __cdecl native_release_render_scope(TargetScope* scope) {
    release_target_scope(scope);
}
extern "C" UINT __cdecl FUN_00427080() {
    if (dat_0071c568)
        dat_0071c568->release();
    dat_0071c568 = nullptr;
    char filename[260];
    wsprintfA(filename, dat_006be1d4, dat_006bcc50, dat_006be1dc);
    return SUCCEEDED(
        archive_entry(filename, false, 0xffffffff, 0xffffffff, 1, 0, nullptr, &dat_0071c568));
}
extern "C" HRESULT __attribute__((thiscall)) FUN_00486120(void* owner, UINT index,
                                                          const char* name) {
    release_texture(owner, 0x1b4 + index * 4);
    char filename[1024];
    wsprintfA(filename, dat_006c1214, name);
    return FUN_0040d480(
        renderer(), filename,
        reinterpret_cast<Texture2D**>(static_cast<unsigned char*>(owner) + 0x1b4 + index * 4));
}
extern "C" UINT __attribute__((thiscall)) FUN_0054c8a0(void* owner, const char* first,
                                                       const char* second, const char* third) {
    const char* names[] = {first, second, third};
    const UINT offsets[] = {0x10, 0x18, 0x1c};
    char filename[260];
    for (UINT i = 0; i < 3; ++i) {
        release_texture(owner, offsets[i]);
        wsprintfA(filename, dat_006be1d4, dat_006c97b4, names[i]);
        if (FAILED(FUN_0040d480(
                renderer(), filename,
                reinterpret_cast<Texture2D**>(static_cast<unsigned char*>(owner) + offsets[i]))))
            return 0;
    }
    return 1;
}
extern "C" UINT __attribute__((thiscall)) FUN_004c5830(void* owner, const char* name, UINT) {
    Texture2D* image = nullptr;
    if (FAILED(archive_entry(name, false, 0xffffffff, 0xffffffff, 1, 0, nullptr, &image)))
        return 0;
    release_texture(owner, 4);
    set_pointer(owner, 4, image);
    Buffer* buffer = nullptr;
    if (FAILED(create_buffer(*renderer(), BufferKind::vertices, nullptr, 144, 36,
                             DXGI_FORMAT_UNKNOWN, &buffer))) {
        if (pointer(owner, 8))
            release_asset_resource(pointer(owner, 8));
        field(owner, 8) = 0;
        release_texture(owner, 4);
        return 0;
    }
    release_buffer(owner, 0);
    set_pointer(owner, 0, buffer);
    return 1;
}
