#include "graphics/render_matrix_constants.h"
namespace {
struct WordBytes {
    unsigned char bytes[4];
};
inline WordBytes& word(unsigned char* output, uint32_t offset) {
    return *reinterpret_cast<WordBytes*>(output + offset);
}
inline void zero(unsigned char* output, uint32_t offset) {
    // Keep the original x87 push/store-pop, including its state on a fault.
    __asm__ volatile("fldz\n\tfstps %0" : "=m"(word(output, offset))::"st", "memory");
}
inline void push_zero() {
    __asm__ volatile("fldz" ::: "st", "memory");
}
inline void pop(unsigned char* output, uint32_t offset) {
    __asm__ volatile("fstps %0" : "=m"(word(output, offset))::"st", "memory");
}
inline void one(unsigned char* output, uint32_t offset) {
    __asm__ volatile("fld1\n\tfstps %0" : "=m"(word(output, offset))::"st", "memory");
}
inline void copy(unsigned char* output, uint32_t offset, uint32_t bits) {
    __asm__ volatile("movl %1,%0" : "=m"(word(output, offset)) : "r"(bits) : "memory");
}
} // namespace
extern "C" void* __attribute__((stdcall)) FUN_005e56c1(void* pointer, uint32_t x, uint32_t y,
                                                       uint32_t z) {
    auto* out = static_cast<unsigned char*>(pointer);
    zero(out, 0x38);
    // Original carries a pushed zero across each of these integer stores.
    // A fault in the copy must leave that zero on the hardware x87 stack.
    push_zero();
    copy(out, 0, x);
    pop(out, 0x34);
    push_zero();
    copy(out, 0x14, y);
    pop(out, 0x30);
    copy(out, 0x28, z);
    zero(out, 0x2c);
    zero(out, 0x24);
    zero(out, 0x20);
    zero(out, 0x1c);
    zero(out, 0x18);
    zero(out, 0x10);
    zero(out, 0x0c);
    zero(out, 8);
    zero(out, 4);
    one(out, 0x3c);
    return pointer;
}
extern "C" void* __attribute__((stdcall)) FUN_005e5755(void* pointer, uint32_t x, uint32_t y,
                                                       uint32_t z) {
    auto* out = static_cast<unsigned char*>(pointer);
    zero(out, 0x2c);
    push_zero();
    copy(out, 0x30, x);
    pop(out, 0x24);
    push_zero();
    copy(out, 0x34, y);
    pop(out, 0x20);
    copy(out, 0x38, z);
    zero(out, 0x1c);
    zero(out, 0x18);
    zero(out, 0x10);
    zero(out, 0x0c);
    zero(out, 8);
    zero(out, 4);
    one(out, 0x3c);
    one(out, 0x28);
    one(out, 0x14);
    one(out, 0);
    return pointer;
}
