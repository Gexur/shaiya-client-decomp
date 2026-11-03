#include "graphics/render_device.h"
#include "startup/logger_format.h"
#include "core/string.h"
#include "network/packets.h"
#include "config/initialization.hpp"
#include "ui/constructors.hpp"
#include "graphics/native_renderer.h"
#include "graphics/native_resources.h"
#include "graphics/native_font.h"

using shaiya::config::DAT_0070859c;
using shaiya::config::DAT_007085a0;
using shaiya::config::DAT_0071987c;
using shaiya::config::DAT_00719a44;
using shaiya::startup::String_00405710;
using shaiya::ui::FUN_005cc96d;
extern "C" {
extern unsigned char dat_0224ead0[];
extern const uintptr_t dat_006c8398[];
void __cdecl FUN_005cc620(void*);
String_00405710* __attribute__((thiscall))
get_config_string_or_insert_default(void*, String_00405710*, const String_00405710*,
                                    const String_00405710*, const String_00405710*);
char* __cdecl FUN_005cd0f0(char*, const char*, uint32_t);
void __attribute__((thiscall)) FUN_00541bf0(void*);
void __attribute__((thiscall)) FUN_00541c40(void*);
void __attribute__((thiscall)) FUN_00541fe0(void*);
void* __cdecl FUN_005ad720();
uint32_t __attribute__((thiscall)) FUN_005ad770(void*, void*);
int32_t __attribute__((thiscall)) FUN_0054a4e0(void*);
void __attribute__((thiscall)) FUN_00542400(void*);
void __attribute__((thiscall)) FUN_005424d0(void*);
void __attribute__((thiscall)) FUN_005425f0(void*);
int32_t __attribute__((thiscall)) FUN_00547cd0(void*);
}

namespace {
void* at(void* self, uintptr_t offset) {
    return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(self) + offset);
}
uint32_t word_at(void* self, uintptr_t offset) {
    const auto* p = static_cast<const unsigned char*>(at(self, offset));
    return uint32_t(p[0]) | uint32_t(p[1]) << 8 | uint32_t(p[2]) << 16 | uint32_t(p[3]) << 24;
}
void put_word(void* self, uintptr_t offset, uint32_t value) {
    auto* p = static_cast<unsigned char*>(at(self, offset));
    p[0] = uint8_t(value);
    p[1] = uint8_t(value >> 8);
    p[2] = uint8_t(value >> 16);
    p[3] = uint8_t(value >> 24);
}
void put_pointer(void* self, uintptr_t offset, void* pointer) {
    put_word(self, offset, uint32_t(reinterpret_cast<uintptr_t>(pointer)));
}
shaiya::graphics::native::NativeRenderer* device(void* self) {
    return reinterpret_cast<shaiya::graphics::native::NativeRenderer*>(word_at(self, 0x408));
}
void clear_bytes(void* pointer, uint32_t count) {
    auto* p = static_cast<unsigned char*>(pointer);
    while (count-- != 0)
        *p++ = 0;
}
char* string_data(String_00405710& value) {
    return value.capacity_018 >= 16 ? reinterpret_cast<char*>(word_at(&value, 4))
                                    : reinterpret_cast<char*>(value.storage_004);
}
void gdi_font(void* self, int32_t height, uint32_t charset, const char* face) {
    HFONT font = CreateFontA(height, 0, 0, 0, 400, 0, 0, 0, charset, 0, 0, 0, 0, face);
    put_pointer(self, 0x3ac, font);
}
bool strict_font(void* self, uintptr_t offset, int32_t height, uint32_t weight, uint32_t charset,
                 const char* face) {
    return FUN_005e8da9(device(self), height, 0, weight, 1, 0, charset, 0, 0, 0, face,
                        reinterpret_cast<void**>(at(self, offset))) >= 0;
}
void helper_font(void* self, uintptr_t offset, int32_t height, uint32_t weight, const char* face) {
    (void)FUN_0054bdf0(reinterpret_cast<void**>(at(self, 0x408)),
                       reinterpret_cast<void**>(at(self, offset)), height, weight, face);
}
bool strict_fonts(void* self, uint32_t charset, const char* face, int32_t h1, int32_t h2,
                  int32_t h3) {
    return strict_font(self, 0x3a8, h1, 400, charset, face) &&
           strict_font(self, 0x39c, h2, 400, charset, face) &&
           strict_font(self, 0x3a0, h3, 700, charset, face);
}
bool configured_fonts(void* self, const char* fallback, uint32_t charset) {
    String_00405710 default_name, key, section, result;
    FUN_00405800(&default_name, fallback);
    FUN_00405800(&key, "FontName");
    FUN_00405800(&section, "Config");
    get_config_string_or_insert_default(dat_0224ead0, &result, &section, &key, &default_name);
    FUN_00529db0(&section);
    FUN_00529db0(&key);
    FUN_00529db0(&default_name);
    gdi_font(self, 12, charset, string_data(result));
    const bool okay = strict_font(self, 0x3a8, 12, 400, charset, string_data(result)) &&
                      strict_font(self, 0x39c, 11, 400, charset, string_data(result)) &&
                      strict_font(self, 0x3a0, 12, 700, charset, string_data(result));
    FUN_00529db0(&result);
    return okay;
}
bool initialize_fonts(void* self, int32_t locale) {
    static const char face_006c85e0[] = "\xb1\xbc\xb8\xb2\xc3\xbc";
    static const char face_006c85d8[] = "\xb1\xbc\xb8\xb2";
    switch (locale) {
    case 2:
        gdi_font(self, 12, 0x86, "simsun");
        return strict_fonts(self, 0x86, "simsun", 12, 11, 12);
    case 5:
    case 9:
        gdi_font(self, 12, 0x88, "simsun");
        return strict_fonts(self, 0x88, "simsun", 12, 11, 12);
    case 4:
        gdi_font(self, 15, 0x80, "courier");
        return strict_fonts(self, 0x80, "courier", 12, 12, 13);
    case 8:
        return configured_fonts(self, "simsun", 0x88);
    case 12:
        return configured_fonts(self, "arial", 0xa2);
    case 11:
        gdi_font(self, 12, 0xcc, "Verdana");
        return strict_fonts(self, 0xcc, "Verdana", 12, 12, 12);
    case 3:
        gdi_font(self, 12, 1, "Arial");
        helper_font(self, 0x3a8, 15, 400, "Arial");
        helper_font(self, 0x39c, 12, 400, "Arial");
        helper_font(self, 0x3a0, 15, 700, "Arial");
        break;
    case 6:
    case 10:
        gdi_font(self, 15, 1, "arial");
        helper_font(self, 0x3a8, 13, 400, "arial");
        helper_font(self, 0x39c, 12, 400, "arial");
        helper_font(self, 0x3a0, 12, 700, "arial");
        break;
    case 7:
    case 13:
    case 14:
    case 16:
        gdi_font(self, 15, 1, "arial");
        helper_font(self, 0x3a8, 13, 400, "arial");
        helper_font(self, 0x39c, 12, 400, "arial");
        helper_font(self, 0x3a0, 17, 400, "arial");
        helper_font(self, 0x3a4, 17, 400, "arial");
        break;
    case 15:
        gdi_font(self, 15, 0xee, "arial");
        helper_font(self, 0x3a8, 13, 400, "arial");
        helper_font(self, 0x39c, 12, 400, "arial");
        helper_font(self, 0x3a0, 14, 400, "arial");
        break;
    case 17:
        gdi_font(self, 15, 1, "arial");
        helper_font(self, 0x3a8, 14, 400, "arial");
        helper_font(self, 0x39c, 13, 400, "arial");
        helper_font(self, 0x3a0, 13, 700, "arial");
        break;
    default:
        gdi_font(self, 12, 1, face_006c85e0);
        helper_font(self, 0x3a8, 12, 400, face_006c85e0);
        helper_font(self, 0x39c, 11, 400, face_006c85d8);
        helper_font(self, 0x3a0, 12, 700, face_006c85d8);
        break;
    }
    return true;
}
} // namespace

extern "C" HRESULT __attribute__((stdcall))
FUN_005e8da9(void* device_pointer, int32_t height, uint32_t width, uint32_t weight, uint32_t levels,
             uint32_t italic, uint32_t charset, uint32_t output, uint32_t quality, uint32_t pitch,
             const char* face, void** font) {
    FontDescription_005e8da9 description;
    clear_bytes(&description, 0x38);
    description.height = height;
    description.width = width;
    description.weight = weight;
    description.mip_levels = levels;
    description.italic = italic;
    description.charset = uint8_t(charset);
    description.output_precision = uint8_t(output);
    description.quality = uint8_t(quality);
    description.pitch_family = uint8_t(pitch);
    if (face != nullptr) {
        FUN_005cd0f0(description.face, face, 32);
        description.face[31] = 0;
    }
    (void)device_pointer;
    shaiya::graphics::native::FontOptions options;
    options.height = description.height;
    options.width = description.width;
    options.weight = description.weight;
    options.italic = description.italic != 0;
    options.charset = description.charset;
    options.output_precision = description.output_precision;
    options.quality = description.quality;
    options.pitch_family = description.pitch_family;
    options.face = description.face;
    return shaiya::graphics::native::create_font(
        options, reinterpret_cast<shaiya::graphics::native::NativeFont**>(font));
}
extern "C" int32_t __cdecl FUN_0054bdf0(void** device_pointer, void** font, int32_t height,
                                        uint32_t weight, const char* face) {
    return FUN_005e8da9(*device_pointer, height, 0, weight, 1, 0, 1, 0, 0, 0, face, font) >= 0;
}
extern "C" int32_t __attribute__((thiscall)) FUN_005416b0(void* self) {
    auto* current = device(self);
    UINT support = 0;
    if (current == nullptr || current->device == nullptr ||
        FAILED(current->device->CheckFormatSupport(DXGI_FORMAT_B8G8R8A8_UNORM, &support)))
        return 0;
    return (support & D3D11_FORMAT_SUPPORT_RENDER_TARGET) != 0 ? DXGI_FORMAT_B8G8R8A8_UNORM : 0;
}
extern "C" int32_t __attribute__((thiscall)) FUN_00541490(void* self) {
    using namespace shaiya::graphics::native;
    auto* current = device(self);
    if (current == nullptr)
        return 0;
    if (FAILED(create_buffer(*current, BufferKind::vertices, nullptr, 320000, 32,
                             DXGI_FORMAT_UNKNOWN, reinterpret_cast<Buffer**>(at(self, 0x358)))))
        return 0;
    return SUCCEEDED(create_buffer(*current, BufferKind::vertices, nullptr, 240000, 24,
                                   DXGI_FORMAT_UNKNOWN,
                                   reinterpret_cast<Buffer**>(at(self, 0x35c))));
}
extern "C" void* __attribute__((thiscall)) FUN_00541f30(void* self) {
    put_pointer(self, 0, const_cast<uintptr_t*>(dat_006c8398));
    put_word(self, 0x0c, 0);
    put_word(self, 0x10, 0);
    put_word(self, 0x14, 0);
    put_word(self, 0x18, 0);
    put_word(self, 4, 0);
    put_word(self, 0x1c, 0);
    put_word(self, 0x20, 0);
    put_word(self, 8, 0);
    return self;
}

// Preserve the game owner and font configuration at this whole-operation entry.
// GPU ownership and rendering passes are native D3D11 objects.
extern "C" int32_t __attribute__((thiscall)) FUN_00544620(void* self) {
    using namespace shaiya::graphics::native;
    auto* current = renderer();
    const bool exclusive = DAT_00719a44 != 0 && dat_00708598 == 1;
    const UINT width = exclusive ? static_cast<UINT>(DAT_0070859c) : 0;
    const UINT height = exclusive ? static_cast<UINT>(DAT_007085a0) : 0;
    if (FAILED(current->initialize(dat_00719a3c, width, height, exclusive)))
        return 0;
    put_pointer(self, 0x404, nullptr);
    put_pointer(self, 0x408, current);
    DAT_0070859c = static_cast<int32_t>(current->width);
    DAT_007085a0 = static_cast<int32_t>(current->height);
    if (!initialize_fonts(self, dat_00708598)) {
        current->shutdown();
        return 0;
    }
    FUN_00541bf0(self);
    if (word_at(self, 0x3a4) != 0)
        FUN_00541c40(self);
    dat_02209400 = current;
    FUN_00541fe0(self);
    FUN_005ad770(FUN_005ad720(), current);
    // Native font label generation owns its target scope locally.
    put_pointer(self, 0x414, nullptr);
    put_word(self, 0x33c, 0xff528bad);
    FUN_00542400(self);
    FUN_005424d0(self);
    FUN_005425f0(self);
    if (FUN_00541490(self) == 0)
        return 0;
    put_pointer(self, 0x360, nullptr);
    put_word(self, 0x418, 2);
    DXGI_ADAPTER_DESC description = {};
    if (current->adapter != nullptr && SUCCEEDED(current->adapter->GetDesc(&description))) {
        char adapter_name[256] = {};
        WideCharToMultiByte(CP_ACP, 0, description.Description, -1, adapter_name,
                            sizeof(adapter_name), nullptr, nullptr);
        FUN_005b9f30(&dat_0224e6c0, 8, "Graphic Adapter Description   : %s", adapter_name);
        FUN_005b9f30(&dat_0224e6c0, 8, "Graphic Adapter VendorId      : %d", description.VendorId);
        FUN_005b9f30(&dat_0224e6c0, 8, "Graphic Adapter DeviceId      : %d", description.DeviceId);
        FUN_005b9f30(&dat_0224e6c0, 8, "Graphic Adapter SubSysId      : %d", description.SubSysId);
        FUN_005b9f30(&dat_0224e6c0, 8, "Graphic Adapter Revision      : %d", description.Revision);
    }
    FUN_005b9f30(&dat_0224e6c0, 8, "Renderer                     : native Direct3D 11, feature %x",
                 static_cast<UINT>(current->feature_level));
    return 1;
}
