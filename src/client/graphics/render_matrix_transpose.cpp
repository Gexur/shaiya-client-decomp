#include "graphics/render_matrix_transpose.h"
#include <stdint.h>
namespace {
struct WordBytes {
    unsigned char bytes[4];
};
inline const WordBytes& source_word(const unsigned char* input, unsigned field) {
    return *reinterpret_cast<const WordBytes*>(input + 4 * field);
}
inline WordBytes& output_word(unsigned char* output, unsigned field) {
    return *reinterpret_cast<WordBytes*>(output + 4 * field);
}
inline void push(const unsigned char* input, unsigned field) {
    __asm__ volatile("flds %0" ::"m"(source_word(input, field)) : "st", "memory");
}
inline void pop(unsigned char* output, unsigned field) {
    __asm__ volatile("fstps %0" : "=m"(output_word(output, field))::"st", "memory");
}
inline uint32_t load(const unsigned char* input, unsigned field) {
    uint32_t value;
    __asm__ volatile("movl %1,%0" : "=r"(value) : "m"(source_word(input, field)) : "memory");
    return value;
}
inline void store(unsigned char* output, unsigned field, uint32_t value) {
    __asm__ volatile("movl %1,%0" : "=m"(output_word(output, field)) : "r"(value) : "memory");
}
inline void mixed_pair(unsigned char* output, const unsigned char* input, unsigned low,
                       unsigned high) {
    const uint32_t raw = load(input, high);
    push(input, low);
    store(output, low, raw);
    pop(output, high);
}
} // namespace
extern "C" void* __attribute__((stdcall)) FUN_005e500f(void* destination, const void* source) {
    auto* output = static_cast<unsigned char*>(destination);
    auto* input = static_cast<const unsigned char*>(source);
    // Original first pair converts both floats. The other five pairs copy the
    // upper field as raw bits and convert the lower field through x87. This
    // asymmetry matters for NaN payloads, aliases and partial write faults.
    push(input, 1);
    push(input, 4);
    pop(output, 1);
    pop(output, 4);
    mixed_pair(output, input, 2, 8);
    mixed_pair(output, input, 3, 12);
    mixed_pair(output, input, 6, 9);
    mixed_pair(output, input, 7, 13);
    mixed_pair(output, input, 11, 14);
    if (destination != source) {
        store(output, 0, load(input, 0));
        store(output, 5, load(input, 5));
        store(output, 10, load(input, 10));
        store(output, 15, load(input, 15));
    }
    return destination;
}
