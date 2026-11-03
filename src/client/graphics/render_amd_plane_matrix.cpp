#include "graphics/render_amd_plane_matrix.h"
#include "graphics/render_normalize_amd.h"
#include "graphics/render_scale_amd.h"
#include "graphics/render_amd_trig_rotation.h"
namespace {
using u32 = uint32_t;
using Packed = long long __attribute__((vector_size(8)));
struct B8 {
    unsigned char bytes[8];
};
#define AMD __attribute__((target("mmx"), always_inline)) inline
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
AMD Packed pair(u32 p) {
    Packed v;
    __asm__ volatile("movq %1,%0" : "=y"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return v;
}
AMD void store(u32 p, Packed v) {
    __asm__ volatile("movq %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "y"(v) : "memory");
}
AMD Packed shift32(Packed p) {
    __asm__ volatile("psrlq $32,%0" : "+y"(p));
    return p;
}
AMD Packed pfmul(Packed a, Packed b) {
    __asm__ volatile("pfmul %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfadd(Packed a, Packed b) {
    __asm__ volatile("pfadd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed unpack_low(Packed a, Packed b) {
    __asm__ volatile("punpckldq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed unpack_high(Packed a, Packed b) {
    __asm__ volatile("punpckhdq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD void empty() {
    __asm__ volatile("femms" ::
                         : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "st", "st(1)",
                           "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory");
}
} // namespace
extern "C" alignas(8) const uint32_t dat_006f0238[2] = {0xc0000000u, 0xc0000000u};
extern "C" alignas(8) const uint32_t dat_006f0240[2] = {0xc0000000u, 0x3f800000u};
// Complete actual686855..686931. The genuine plane provider writes all16B.
extern "C" __attribute__((target("mmx"))) u32 recovered_00686855(u32 arguments) {
    empty();
    alignas(8) uint32_t normalized[4];
    const u32 temporary = reinterpret_cast<u32>(normalized);
    const u32 input = word(arguments + 4);
    FUN_0068b915(reinterpret_cast<void*>(temporary), reinterpret_cast<const void*>(input));
    const u32 output = word(arguments);
    Packed mm0 = pair(temporary), mm1 = pair(temporary + 8), mm2 = mm0, mm3 = mm1;
    mm0 = pfmul(mm0, pair(reinterpret_cast<u32>(dat_006f0238)));
    mm1 = pfmul(mm1, pair(reinterpret_cast<u32>(dat_006f0240)));
    Packed mm4 = mm2, mm6 = mm2;
    mm4 = unpack_low(mm4, mm4);
    mm6 = unpack_high(mm6, mm6);
    Packed mm5 = mm4, mm7 = mm6;
    mm5 = shift32(mm5);
    mm7 = shift32(mm7);
    mm4 = pfmul(mm4, mm0);
    mm5 = pfmul(mm5, mm1);
    mm6 = pfmul(mm6, mm0);
    mm7 = pfmul(mm7, mm1);
    mm4 = pfadd(mm4, pair(reinterpret_cast<u32>(dat_006f0228)));
    mm6 = pfadd(mm6, pair(reinterpret_cast<u32>(dat_006f0220)));
    store(output, mm4);
    store(output + 8, mm5);
    store(output + 16, mm6);
    store(output + 24, mm7);
    mm4 = mm3;
    mm6 = mm3;
    mm4 = unpack_low(mm4, mm4);
    mm6 = unpack_high(mm6, mm6);
    mm5 = mm4;
    mm7 = mm6;
    mm5 = shift32(mm5);
    mm7 = shift32(mm7);
    mm4 = pfmul(mm4, mm0);
    mm5 = pfmul(mm5, mm1);
    mm6 = pfmul(mm6, mm0);
    mm7 = pfmul(mm7, mm1);
    mm5 = pfadd(mm5, pair(reinterpret_cast<u32>(dat_006f0228)));
    mm7 = pfadd(mm7, pair(reinterpret_cast<u32>(dat_006f0220)));
    store(output + 32, mm4);
    store(output + 40, mm5);
    store(output + 48, mm6);
    store(output + 56, mm7);
    empty();
    return output;
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00686855(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00686855\n\taddl $4,%esp\n\tretl $8");
}
