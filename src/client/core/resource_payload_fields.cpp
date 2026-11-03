#include "triple_list32.h"
#include "../runtime/allocations.h"
#include "graphics/native_resources.h"

namespace {
// Alias-qualified representation operations retain the original DWORD/WORD
// field widths without claiming an otherwise unobserved complete class.
using Word32 = uint32_t __attribute__((may_alias));
using Word16 = uint16_t __attribute__((may_alias));
inline uint32_t load32(const void* object, uint32_t offset) {
    return *reinterpret_cast<const Word32*>(static_cast<const uint8_t*>(object) + offset);
}
inline void store32(void* object, uint32_t offset, uint32_t value) {
    *reinterpret_cast<Word32*>(static_cast<uint8_t*>(object) + offset) = value;
}
inline uint16_t load16(const void* object, uint32_t offset) {
    return *reinterpret_cast<const Word16*>(static_cast<const uint8_t*>(object) + offset);
}
inline void store16(void* object, uint32_t offset, uint16_t value) {
    *reinterpret_cast<Word16*>(static_cast<uint8_t*>(object) + offset) = value;
}
inline void delete_array_field(void* object, uint32_t offset) {
    uint32_t current = load32(object, offset);
    if (current != 0) {
        fun_005cdc59(reinterpret_cast<void*>(current));
        store32(object, offset, 0);
    }
}
inline void release_interface_field(void* object, uint32_t offset) {
    const uint32_t current = load32(object, offset);
    if (current != 0) {
        shaiya::graphics::native::release_asset_resource(reinterpret_cast<void*>(current));
        store32(object, offset, 0);
    }
}
} // namespace
extern "C" void __attribute__((thiscall)) FUN_00550710(void* object) {
    delete_array_field(object, 0x34);
    delete_array_field(object, 0x2c);
    delete_array_field(object, 0x08);
    release_interface_field(object, 0x00);
    release_interface_field(object, 0x04);
    release_interface_field(object, 0x0c);
    release_interface_field(object, 0x14);
}
extern "C" void __attribute__((thiscall)) FUN_005507c0(void* object) {
    const uint16_t count = load16(object, 0x13c);
    if (count != 0) {
        if (count == 1) {
            FUN_00550710(object);
            store16(object, 0x13c, 0);
        } else
            store16(object, 0x13c, static_cast<uint16_t>(count - 1u));
    }
}
extern "C" void __attribute__((thiscall)) FUN_0053dd40(void* object) {
    const uint16_t count = load16(object, 0x10c);
    if (count != 0) {
        if (count == 1) {
            release_interface_field(object, 4);
            store16(object, 0x10c, 0);
        } else
            store16(object, 0x10c, static_cast<uint16_t>(count - 1u));
    }
}
