#pragma once
#include "constructors.hpp"
namespace shaiya::ui::ordered_detail {
inline u32 load32(const void* base, u32 offset) {
    u32 value;
    auto* at = static_cast<const u8*>(base) + offset;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
inline void store32(void* base, u32 offset, u32 value) {
    auto* at = static_cast<u8*>(base) + offset;
    __asm__ volatile("movl %1,(%0)" ::"r"(at), "r"(value) : "memory");
}
inline void store8(void* base, u32 offset, u8 value) {
    auto* at = static_cast<u8*>(base) + offset;
    __asm__ volatile("movb %1,(%0)" ::"r"(at), "q"(value) : "memory");
}
inline void zero_words(void* base, u32 offset, u32 count) {
    auto* at = reinterpret_cast<u32*>(static_cast<u8*>(base) + offset);
    __asm__ volatile("rep stosl" : "+D"(at), "+c"(count) : "a"(0) : "memory");
}
} // namespace shaiya::ui::ordered_detail
