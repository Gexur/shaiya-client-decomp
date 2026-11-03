#include "graphics/surface/surface_error_row.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void add(u32 source, u32 pixel) {
    __asm__ volatile("flds (%0)\n\tfadds (%1)\n\tfstps (%1)" ::"r"(source), "r"(pixel)
                     : "st", "memory");
}
void clear(u32 destination, u32 bytes) {
    u32 dwords = bytes >> 2;
    __asm__ volatile("rep stosl" : "+D"(destination), "+c"(dwords) : "a"(0) : "memory");
    u32 tail = bytes & 3u;
    __asm__ volatile("rep stosb" : "+D"(destination), "+c"(tail) : "a"(0) : "memory");
}
} // namespace
// Complete original005f25f2..005f2664. The secondary physical EDX result
// is the actual wrapped clear-byte count, while logical/physical EAX is zero.
extern "C" uint64_t recovered_005f25f2(uint32_t self, uint32_t argument) {
    u32 count = 0;
    if (word(self + 0x68) != 0) {
        const u32 base = word(argument);
        u32 pixel = base + 8;
        const u32 relative = 0xfffffff8u - base;
        do {
            const u32 errors = word(self + 0x5c) + relative + pixel + 16u;
            ++count;
            add(errors, pixel - 8);
            add(errors + 4, pixel - 4);
            add(errors + 8, pixel);
            pixel += 16;
            add(errors + 12, pixel - 12);
        } while (count < word(self + 0x68));
    }
    const u32 width = word(self + 0x68), destination = word(self + 0x5c);
    const u32 bytes = (width + 2u) << 4;
    clear(destination, bytes);
    return static_cast<uint64_t>(bytes) << 32;
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f25f2(void*, void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f25f2\n\taddl $8,%esp\n\txorl %ecx,%ecx\n\tretl $4");
}
