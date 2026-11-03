#include "graphics/render_scale_amd.h"
extern "C" alignas(8) const uint32_t dat_006f0220[2] = {0, 0x3f800000};
namespace {
struct Slot {
    unsigned char bytes[4];
};
struct Pair {
    unsigned char bytes[8];
};
#define MEDIA_INLINE __attribute__((target("mmx"), always_inline)) inline
MEDIA_INLINE void empty() {
    __asm__ volatile("femms" ::
                         : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "st", "st(1)",
                           "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory");
}
} // namespace
// Original686a51..686a98, including original MMX identities and eight-byte
// store order. All three incoming slots remain raw float bits, not conversions.
extern "C" __attribute__((target("mmx"))) void* recovered_00686a51(const unsigned char* words) {
    empty();
    uint32_t address;
    __asm__ volatile("movl (%1),%0" : "=r"(address) : "r"(words) : "memory");
    __asm__ volatile("movd %0,%%mm3" ::"m"(*reinterpret_cast<const Slot*>(words + 8))
                     : "mm3", "memory");
    __asm__ volatile("movq %0,%%mm1" ::"m"(dat_006f0220) : "mm1", "memory");
    __asm__ volatile("movd %0,%%mm2" ::"m"(*reinterpret_cast<const Slot*>(words + 4))
                     : "mm2", "memory");
    __asm__ volatile("pxor %%mm0,%%mm0" ::: "mm0", "memory");
    __asm__ volatile("psllq $32,%%mm3" ::: "mm3", "memory");
    __asm__ volatile("movd %0,%%mm4" ::"m"(*reinterpret_cast<const Slot*>(words + 12))
                     : "mm4", "memory");
    auto* output = reinterpret_cast<unsigned char*>(address);
    __asm__ volatile("movq %%mm2,%0" : "=m"(*reinterpret_cast<Pair*>(output)) : : "memory");
    __asm__ volatile("movq %%mm0,%0" : "=m"(*reinterpret_cast<Pair*>(output + 8)) : : "memory");
    __asm__ volatile("movq %%mm0,%0" : "=m"(*reinterpret_cast<Pair*>(output + 0x18)) : : "memory");
    __asm__ volatile("movq %%mm0,%0" : "=m"(*reinterpret_cast<Pair*>(output + 0x20)) : : "memory");
    __asm__ volatile("movq %%mm0,%0" : "=m"(*reinterpret_cast<Pair*>(output + 0x30)) : : "memory");
    __asm__ volatile("movq %%mm3,%0" : "=m"(*reinterpret_cast<Pair*>(output + 0x10)) : : "memory");
    __asm__ volatile("movq %%mm4,%0" : "=m"(*reinterpret_cast<Pair*>(output + 0x28)) : : "memory");
    __asm__ volatile("movq %%mm1,%0" : "=m"(*reinterpret_cast<Pair*>(output + 0x38)) : : "memory");
    empty();
    return output;
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00686a51(void*, uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00686a51\n\taddl $4,%esp\n\tretl $16");
}
