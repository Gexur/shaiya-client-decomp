#pragma once
#include "core/byte_access.h"
#include <stdint.h>
extern "C" {
int32_t __attribute__((cdecl)) FUN_005471c0(const char*, uint32_t*);
int32_t __attribute__((cdecl)) FUN_00547290(uint32_t, uint32_t, uint32_t, uint32_t);
int32_t __attribute__((cdecl)) FUN_00546fb0(uint32_t*, uint32_t*, char*);
int32_t __attribute__((cdecl)) FUN_005472c0(uint32_t*, uint32_t*, char*);
}
namespace directx_version_detail {
inline uint32_t load32(const void* pointer) {
    return shaiya::byte_access::load<uint32_t>(pointer);
}
inline uint8_t load8(const void* pointer) {
    return shaiya::byte_access::load<uint8_t>(pointer);
}
inline void store32(void* pointer, uint32_t value) {
    shaiya::byte_access::store(pointer, value);
}
inline void store8(void* pointer, uint8_t value) {
    shaiya::byte_access::store(pointer, value);
}
} // namespace directx_version_detail
