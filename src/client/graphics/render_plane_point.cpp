#include "graphics/render_plane_point.h"
#include <stdint.h>
namespace {
struct WordBytes {
    unsigned char bytes[4];
};
inline uint32_t bits(const volatile float* source) {
    uint32_t value;
    __asm__ volatile("movl %1,%0"
                     : "=r"(value)
                     : "m"(*reinterpret_cast<const volatile WordBytes*>(source))
                     : "memory");
    return value;
}
inline void bits(float* output, uint32_t value) {
    __asm__ volatile("movl %1,%0"
                     : "=m"(*reinterpret_cast<WordBytes*>(output))
                     : "r"(value)
                     : "memory");
}
inline void rounded_copy(float* output, const volatile float* source) {
    // Only normal.x passes through original FLD/FSTP; y/z are raw bit copies.
    __asm__ volatile("flds %1\n\tfstps %0"
                     : "=m"(*reinterpret_cast<WordBytes*>(output))
                     : "m"(*reinterpret_cast<const volatile WordBytes*>(source))
                     : "st", "memory");
}
inline long double negative(long double value) {
    __asm__ volatile("fchs" : "+t"(value));
    return value;
}
} // namespace
extern "C" float* __attribute__((stdcall)) FUN_005e7126(float* output, const volatile float* point,
                                                        const volatile float* normal) {
    rounded_copy(output, normal);
    bits(output + 1, bits(normal + 1));
    bits(output + 2, bits(normal + 2));
    const long double y = static_cast<long double>(point[1]) * static_cast<long double>(normal[1]);
    const long double z = static_cast<long double>(point[2]) * static_cast<long double>(normal[2]);
    const long double yz = y + z;
    const long double x = static_cast<long double>(point[0]) * static_cast<long double>(normal[0]);
    static_cast<volatile float*>(output)[3] = static_cast<float>(negative(yz + x));
    return output;
}
