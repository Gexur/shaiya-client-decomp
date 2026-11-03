#include "com_array_owner.h"
#include "com_payload520.h"
#include "../startup/global_ownership.h"
#include "../runtime/allocations.h"
#include "../runtime/array_lifetime.h"
#include "graphics/native_resources.h"
namespace {
using Word = uint32_t __attribute__((may_alias));
Word& word(void* self, uint32_t offset) {
    return *reinterpret_cast<Word*>(static_cast<uint8_t*>(self) + offset);
}
void* pointer(void* self, uint32_t offset) {
    return reinterpret_cast<void*>(word(self, offset));
}
void release(void* object) {
    shaiya::graphics::native::release_asset_resource(object);
}
void raw_array(void* self, uint32_t offset) {
    void* current = pointer(self, offset);
    if (current != nullptr) {
        fun_005cdc59(current);
        word(self, offset) = 0;
    }
}
void release_buffer_field(void* self, uint32_t offset) {
    void* current = pointer(self, offset);
    if (current != nullptr) {
        release(current);
        word(self, offset) = 0;
    }
}
} // namespace
extern "C" void* __attribute__((thiscall)) FUN_005b0c30(void* self) {
    // Original store order is retained explicitly, including untouched holes.
    const uint8_t offsets[] = {0,   4,   8,   12,  16,  20,  24,  36,  44,  40,  48,
                               52,  64,  72,  68,  76,  80,  92,  100, 96,  140, 144,
                               156, 160, 164, 104, 108, 112, 116, 120, 124, 128, 132};
    for (uint8_t offset : offsets)
        *reinterpret_cast<volatile Word*>(static_cast<uint8_t*>(self) + offset) = 0;
    *reinterpret_cast<volatile uint8_t*>(static_cast<uint8_t*>(self) + 0xa8) = 0;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_005b00e0(void* self) {
    void* current = pointer(self, 0);
    if (current != nullptr)
        release(current);
    current = pointer(self, 4);
    if (current != nullptr)
        release(current);
}
extern "C" void __attribute__((thiscall)) FUN_005b0d10(void* self) {
    raw_array(self, 0x31c);
    raw_array(self, 0x320);
    raw_array(self, 0x308);
    raw_array(self, 0x30c);
    FUN_005afc70(static_cast<uint8_t*>(self) + 0x100);
}
extern "C" void __attribute__((thiscall)) FUN_005b15a0(void* self) {
    void* elements = pointer(self, 0x68);
    if (elements != nullptr) {
        void* cookie = reinterpret_cast<void*>(reinterpret_cast<uint32_t>(elements) - 4u);
        uint32_t count;
        __asm__ volatile("movl (%1),%0" : "=r"(count) : "r"(cookie) : "memory");
        fun_005cdcbc(elements, 0x438, static_cast<int32_t>(count), FUN_005b0d10);
        fun_005cdc59(cookie);
        word(self, 0x68) = 0;
    }
    raw_array(self, 0);
    raw_array(self, 4);
    release_buffer_field(self, 0x14);
    release_buffer_field(self, 0x18);
    word(self, 0x24) = 0;
    word(self, 0x2c) = 0;
    word(self, 0x28) = 0;
    release_buffer_field(self, 0x8c);
    release_buffer_field(self, 0x90);
    word(self, 0x9c) = 0;
    word(self, 0xa0) = 0;
    word(self, 0xa4) = 0;
    word(self, 0x6c) = 0;
    word(self, 0x70) = 0;
    word(self, 0x74) = 0;
    word(self, 0x78) = 0;
    word(self, 0x7c) = 0;
}
