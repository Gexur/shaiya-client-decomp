#pragma once
#include <stdint.h>
namespace original_input {
inline uint8_t* at(void* p, uint32_t offset) {
    return static_cast<uint8_t*>(p) + offset;
}
inline uint32_t load(void* p, uint32_t offset) {
    return *reinterpret_cast<volatile uint32_t*>(at(p, offset));
}
inline void store(void* p, uint32_t offset, uint32_t value) {
    *reinterpret_cast<volatile uint32_t*>(at(p, offset)) = value;
}
inline void byte(void* p, uint32_t offset, uint8_t value) {
    *reinterpret_cast<volatile uint8_t*>(at(p, offset)) = value;
}
inline void word(void* p, uint32_t offset, uint16_t value) {
    *reinterpret_cast<volatile uint16_t*>(at(p, offset)) = value;
}
using ComCall = int32_t(__attribute__((stdcall)) *)(void*);
inline int32_t com(void* interface, uint32_t offset) {
    auto* table = reinterpret_cast<uint32_t*>(load(interface, 0));
    return reinterpret_cast<ComCall>(table[offset / 4])(interface);
}
} // namespace original_input
