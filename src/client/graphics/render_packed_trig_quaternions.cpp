#include "graphics/render_packed_trig_quaternions.h"
namespace {
using u32 = uint32_t;
using u64 = uint64_t;
using V = float __attribute__((vector_size(16)));
struct B4 {
    unsigned char bytes[4];
};
struct B16 {
    unsigned char bytes[16];
};
#define SSE __attribute__((target("sse"), always_inline)) inline
#define SSE2 __attribute__((target("sse2"), always_inline)) inline
u32 word(const u32* p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
SSE V aligned(u32 p) {
    V v;
    __asm__ volatile("movaps %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B16*>(p)) : "memory");
    return v;
}
SSE V scalar(u32 p) {
    V v;
    __asm__ volatile("movss %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B4*>(p)) : "memory");
    return v;
}
SSE V add(V a, V b) {
    __asm__ volatile("addps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE V sub(V a, V b) {
    __asm__ volatile("subps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE V mul(V a, V b) {
    __asm__ volatile("mulps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE V and_bits(V a, V b) {
    __asm__ volatile("andps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE V or_bits(V a, V b) {
    __asm__ volatile("orps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE V xor_bits(V a, V b) {
    __asm__ volatile("xorps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE V and_not(V a, V b) {
    __asm__ volatile("andnps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE V not_equal(V a, V b) {
    __asm__ volatile("cmpneqps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE2 V integer_and(V a, V b) {
    __asm__ volatile("pand %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE2 V integer_xor(V a, V b) {
    __asm__ volatile("pxor %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE2 V integer_add(V a, V b) {
    __asm__ volatile("paddd %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE2 V integer_sub(V a, V b) {
    __asm__ volatile("psubd %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE2 V shift_thirty(V a) {
    __asm__ volatile("pslld $30,%0" : "+x"(a));
    return a;
}
template <int n> SSE V shuffle(V a, V b) {
    __asm__ volatile("shufps %2,%1,%0" : "+x"(a) : "x"(b), "i"(n));
    return a;
}
SSE void store(u32 p, V v) {
    __asm__ volatile("movaps %1,%0" : "=m"(*reinterpret_cast<B16*>(p)) : "x"(v) : "memory");
}
SSE void store_unaligned(u32 p, V v) {
    __asm__ volatile("movups %1,%0" : "=m"(*reinterpret_cast<B16*>(p)) : "x"(v) : "memory");
}
SSE void scalar_store(u32 p, V v) {
    __asm__ volatile("movss %1,%0" : "=m"(*reinterpret_cast<B4*>(p)) : "x"(v) : "memory");
}
} // namespace
extern "C" __attribute__((target("sse"), force_align_arg_pointer)) u64
recovered_packed_trig_006a6410(const u32* arguments) {
    alignas(16) u32 scratch[12];
    const u32 w000 = word(arguments + 0); // original006a6415
    const V v000 = aligned(w000);         // original006a6418 movaps xmm0, xmmword ptr [eax]
    const V v001 = v000;                  // original006a641c movaps xmm1, xmm0
    const V v002 = v000;                  // original006a641f movaps xmm6, xmm0
    const V v003 =
        and_bits(v000, aligned(reinterpret_cast<u32>(
                           dat_00717c20))); // original006a6422 andps xmm0, xmmword ptr [0x717c20]
    const V v004 =
        and_bits(v001, aligned(reinterpret_cast<u32>(
                           dat_00717c10))); // original006a6429 andps xmm1, xmmword ptr [0x717c10]
    const V v005 = v003;                    // original006a6430 movaps xmm2, xmm0
    const V v006 = v003;                    // original006a6433 movaps xmm7, xmm0
    const V v007 =
        mul(v003, aligned(reinterpret_cast<u32>(
                      dat_00717c00))); // original006a6436 mulps xmm0, xmmword ptr [0x717c00]
    const V v008 = aligned(reinterpret_cast<u32>(
        dat_00717bf0)); // original006a643d movaps xmm4, xmmword ptr [0x717bf0]
    const V v009 = aligned(reinterpret_cast<u32>(
        dat_00717be0)); // original006a6444 movaps xmm5, xmmword ptr [0x717be0]
    const V v010 = aligned(reinterpret_cast<u32>(
        dat_00717bd0)); // original006a6453 movaps xmm6, xmmword ptr [0x717bd0]
    const V v011 = aligned(reinterpret_cast<u32>(
        dat_00717bc0)); // original006a645a movaps xmm7, xmmword ptr [0x717bc0]
    const V v012 =
        add(v007, aligned(reinterpret_cast<u32>(
                      dat_00717bb0))); // original006a6461 addps xmm0, xmmword ptr [0x717bb0]
    const V v013 = v012;               // original006a6468 movaps xmm3, xmm0
    const V v014 =
        sub(v012, aligned(reinterpret_cast<u32>(
                      dat_00717bb0))); // original006a646b subps xmm0, xmmword ptr [0x717bb0]
    const V v015 = mul(v008, v014);    // original006a6472 mulps xmm4, xmm0
    const V v016 = mul(v009, v014);    // original006a6475 mulps xmm5, xmm0
    const V v017 = mul(v010, v014);    // original006a6478 mulps xmm6, xmm0
    const V v018 = mul(v011, v014);    // original006a647b mulps xmm7, xmm0
    const V v019 = sub(v005, v015);    // original006a647e subps xmm2, xmm4
    const V v020 = sub(v019, v016);    // original006a6481 subps xmm2, xmm5
    const V v021 = aligned(reinterpret_cast<u32>(
        dat_00717ba0));             // original006a6484 movaps xmm5, xmmword ptr [0x717ba0]
    const V v022 = sub(v020, v017); // original006a648b subps xmm2, xmm6
    const V v023 = aligned(reinterpret_cast<u32>(
        dat_00717b90));             // original006a648e movaps xmm6, xmmword ptr [0x717b90]
    const V v024 = sub(v022, v018); // original006a6495 subps xmm2, xmm7
    const V v025 = v024;            // original006a6498 movaps xmm4, xmm2
    const V v026 = mul(v025, v025); // original006a649b mulps xmm4, xmm4
    const V v027 =
        and_bits(v013, aligned(reinterpret_cast<u32>(
                           dat_00717b80))); // original006a649e andps xmm3, xmmword ptr [0x717b80]
    const V v028 = v027;                    // original006a64a5 movaps xmm0, xmm3
    const V v029 = v027;                    // original006a64a8 movaps xmm7, xmm3
    const V v030 =
        and_bits(v028, aligned(reinterpret_cast<u32>(
                           dat_00717b70))); // original006a64ab andps xmm0, xmmword ptr [0x717b70]
    store(reinterpret_cast<u32>(scratch), v030);      // original006a64b2
    store(reinterpret_cast<u32>(scratch) + 16, v027); // original006a64b5
    store(reinterpret_cast<u32>(scratch) + 32, v029); // original006a64b9
    const u32 w001 = word(reinterpret_cast<const u32*>(
        reinterpret_cast<u32>(scratch) + 16)); // original006a64bd mov eax, dword ptr [edx + 0x10]
    const u32 w002 = w001 - word(reinterpret_cast<const u32*>(reinterpret_cast<u32>(
                                scratch))); // original006a64c0 sub eax, dword ptr [edx]
    const u32 w003 = w002 & word(reinterpret_cast<const u32*>(reinterpret_cast<u32>(
                                dat_00717b60))); // original006a64c2 and eax, dword ptr [0x717b60]
    const u32 w004 = w003 << 30;                 // original006a64c8 shl eax, 0x1e
    put(reinterpret_cast<u32>(scratch) + 16, w004); // original006a64cb
    const u32 w005 = word(reinterpret_cast<const u32*>(
        reinterpret_cast<u32>(scratch) + 20)); // original006a64ce mov eax, dword ptr [edx + 0x14]
    const u32 w006 =
        w005 -
        word(reinterpret_cast<const u32*>(reinterpret_cast<u32>(scratch) +
                                          4)); // original006a64d1 sub eax, dword ptr [edx + 4]
    const u32 w007 = w006 & word(reinterpret_cast<const u32*>(reinterpret_cast<u32>(
                                dat_00717b60))); // original006a64d4 and eax, dword ptr [0x717b60]
    const u32 w008 = w007 << 30;                 // original006a64da shl eax, 0x1e
    put(reinterpret_cast<u32>(scratch) + 20, w008); // original006a64dd
    const u32 w009 = word(reinterpret_cast<const u32*>(
        reinterpret_cast<u32>(scratch) + 24)); // original006a64e0 mov eax, dword ptr [edx + 0x18]
    const u32 w010 =
        w009 -
        word(reinterpret_cast<const u32*>(reinterpret_cast<u32>(scratch) +
                                          8)); // original006a64e3 sub eax, dword ptr [edx + 8]
    const u32 w011 = w010 & word(reinterpret_cast<const u32*>(reinterpret_cast<u32>(
                                dat_00717b60))); // original006a64e6 and eax, dword ptr [0x717b60]
    const u32 w012 = w011 << 30;                 // original006a64ec shl eax, 0x1e
    put(reinterpret_cast<u32>(scratch) + 24, w012); // original006a64ef
    const u32 w013 = word(reinterpret_cast<const u32*>(
        reinterpret_cast<u32>(scratch) + 28)); // original006a64f2 mov eax, dword ptr [edx + 0x1c]
    const u32 w014 =
        w013 -
        word(reinterpret_cast<const u32*>(reinterpret_cast<u32>(scratch) +
                                          12)); // original006a64f5 sub eax, dword ptr [edx + 0xc]
    const u32 w015 = w014 & word(reinterpret_cast<const u32*>(reinterpret_cast<u32>(
                                dat_00717b60))); // original006a64f8 and eax, dword ptr [0x717b60]
    const u32 w016 = w015 << 30;                 // original006a64fe shl eax, 0x1e
    put(reinterpret_cast<u32>(scratch) + 28, w016); // original006a6501
    const u32 w017 = word(reinterpret_cast<const u32*>(
        reinterpret_cast<u32>(scratch) + 32)); // original006a6504 mov eax, dword ptr [edx + 0x20]
    const u32 w018 = w017 + word(reinterpret_cast<const u32*>(reinterpret_cast<u32>(
                                scratch))); // original006a6507 add eax, dword ptr [edx]
    const u32 w019 = w018 & word(reinterpret_cast<const u32*>(reinterpret_cast<u32>(
                                dat_00717b60))); // original006a6509 and eax, dword ptr [0x717b60]
    const u32 w020 = w019 << 30;                 // original006a650f shl eax, 0x1e
    put(reinterpret_cast<u32>(scratch) + 32, w020); // original006a6512
    const u32 w021 = word(reinterpret_cast<const u32*>(
        reinterpret_cast<u32>(scratch) + 36)); // original006a6515 mov eax, dword ptr [edx + 0x24]
    const u32 w022 =
        w021 +
        word(reinterpret_cast<const u32*>(reinterpret_cast<u32>(scratch) +
                                          4)); // original006a6518 add eax, dword ptr [edx + 4]
    const u32 w023 = w022 & word(reinterpret_cast<const u32*>(reinterpret_cast<u32>(
                                dat_00717b60))); // original006a651b and eax, dword ptr [0x717b60]
    const u32 w024 = w023 << 30;                 // original006a6521 shl eax, 0x1e
    put(reinterpret_cast<u32>(scratch) + 36, w024); // original006a6524
    const u32 w025 = word(reinterpret_cast<const u32*>(
        reinterpret_cast<u32>(scratch) + 40)); // original006a6527 mov eax, dword ptr [edx + 0x28]
    const u32 w026 =
        w025 +
        word(reinterpret_cast<const u32*>(reinterpret_cast<u32>(scratch) +
                                          8)); // original006a652a add eax, dword ptr [edx + 8]
    const u32 w027 = w026 & word(reinterpret_cast<const u32*>(reinterpret_cast<u32>(
                                dat_00717b60))); // original006a652d and eax, dword ptr [0x717b60]
    const u32 w028 = w027 << 30;                 // original006a6533 shl eax, 0x1e
    put(reinterpret_cast<u32>(scratch) + 40, w028); // original006a6536
    const u32 w029 = word(reinterpret_cast<const u32*>(
        reinterpret_cast<u32>(scratch) + 44)); // original006a6539 mov eax, dword ptr [edx + 0x2c]
    const u32 w030 =
        w029 +
        word(reinterpret_cast<const u32*>(reinterpret_cast<u32>(scratch) +
                                          12)); // original006a653c add eax, dword ptr [edx + 0xc]
    const u32 w031 = w030 & word(reinterpret_cast<const u32*>(reinterpret_cast<u32>(
                                dat_00717b60))); // original006a653f and eax, dword ptr [0x717b60]
    const u32 w032 = w031 << 30;                 // original006a6545 shl eax, 0x1e
    put(reinterpret_cast<u32>(scratch) + 44, w032); // original006a6548
    const u32 w033 = word(reinterpret_cast<const u32*>(
        reinterpret_cast<u32>(scratch)));      // original006a654b mov eax, dword ptr [edx]
    const u32 w034 = w033 << 30;               // original006a654d shl eax, 0x1e
    put(reinterpret_cast<u32>(scratch), w034); // original006a6550
    const u32 w035 = word(reinterpret_cast<const u32*>(
        reinterpret_cast<u32>(scratch) + 4));      // original006a6552 mov eax, dword ptr [edx + 4]
    const u32 w036 = w035 << 30;                   // original006a6555 shl eax, 0x1e
    put(reinterpret_cast<u32>(scratch) + 4, w036); // original006a6558
    const u32 w037 = word(reinterpret_cast<const u32*>(
        reinterpret_cast<u32>(scratch) + 8));      // original006a655b mov eax, dword ptr [edx + 8]
    const u32 w038 = w037 << 30;                   // original006a655e shl eax, 0x1e
    put(reinterpret_cast<u32>(scratch) + 8, w038); // original006a6561
    const u32 w039 = word(reinterpret_cast<const u32*>(
        reinterpret_cast<u32>(scratch) + 12)); // original006a6564 mov eax, dword ptr [edx + 0xc]
    const u32 w040 = w039 << 30;               // original006a6567 shl eax, 0x1e
    put(reinterpret_cast<u32>(scratch) + 12, w040); // original006a656a
    const V v031 = aligned(reinterpret_cast<u32>(scratch) +
                           16); // original006a656d movaps xmm3, xmmword ptr [edx + 0x10]
    const V v032 = aligned(reinterpret_cast<u32>(scratch) +
                           32); // original006a6571 movaps xmm7, xmmword ptr [edx + 0x20]
    const V v033 =
        aligned(reinterpret_cast<u32>(scratch)); // original006a6575 movaps xmm0, xmmword ptr [edx]
    const V v034 = xor_bits(v031, v004);         // original006a6578 xorps xmm3, xmm1
    const V v035 = xor_bits(v004, v004);         // original006a657b xorps xmm1, xmm1
    const V v036 = not_equal(v033, v035);        // original006a657e cmpneqps xmm0, xmm1
    const V v037 = mul(v021, v026);              // original006a6582 mulps xmm5, xmm4
    const V v038 = mul(v023, v026);              // original006a6585 mulps xmm6, xmm4
    const V v039 =
        add(v037, aligned(reinterpret_cast<u32>(
                      dat_00717b50))); // original006a6588 addps xmm5, xmmword ptr [0x717b50]
    const V v040 =
        add(v038, aligned(reinterpret_cast<u32>(
                      dat_00717b40))); // original006a658f addps xmm6, xmmword ptr [0x717b40]
    const V v041 = mul(v039, v026);    // original006a6596 mulps xmm5, xmm4
    const V v042 = mul(v040, v026);    // original006a6599 mulps xmm6, xmm4
    const V v043 =
        add(v041, aligned(reinterpret_cast<u32>(
                      dat_00717b30))); // original006a659c addps xmm5, xmmword ptr [0x717b30]
    const V v044 =
        add(v042, aligned(reinterpret_cast<u32>(
                      dat_00717b20))); // original006a65a3 addps xmm6, xmmword ptr [0x717b20]
    const V v045 = mul(v043, v026);    // original006a65aa mulps xmm5, xmm4
    const V v046 = mul(v044, v026);    // original006a65ad mulps xmm6, xmm4
    const V v047 =
        add(v045, aligned(reinterpret_cast<u32>(
                      dat_00717b10))); // original006a65b0 addps xmm5, xmmword ptr [0x717b10]
    const V v048 =
        add(v046, aligned(reinterpret_cast<u32>(
                      dat_00717b00))); // original006a65b7 addps xmm6, xmmword ptr [0x717b00]
    const V v049 = mul(v047, v024);    // original006a65be mulps xmm5, xmm2
    const V v050 = mul(v048, v026);    // original006a65c1 mulps xmm6, xmm4
    const V v051 =
        add(v050, aligned(reinterpret_cast<u32>(
                      dat_00717af0)));    // original006a65c4 addps xmm6, xmmword ptr [0x717af0]
    const V v052 = v036;                  // original006a65cb movaps xmm1, xmm0
    const V v053 = v036;                  // original006a65ce movaps xmm2, xmm0
    const V v054 = and_not(v052, v049);   // original006a65d1 andnps xmm1, xmm5
    const V v055 = and_bits(v053, v051);  // original006a65d4 andps xmm2, xmm6
    const V v056 = or_bits(v054, v055);   // original006a65d7 orps xmm1, xmm2
    const V v057 = v036;                  // original006a65da movaps xmm2, xmm0
    const V v058 = and_bits(v036, v049);  // original006a65dd andps xmm0, xmm5
    const V v059 = and_not(v057, v051);   // original006a65e0 andnps xmm2, xmm6
    const V v060 = or_bits(v058, v059);   // original006a65e3 orps xmm0, xmm2
    const V v061 = xor_bits(v060, v032);  // original006a65e6 xorps xmm0, xmm7
    const V v062 = xor_bits(v056, v034);  // original006a65e9 xorps xmm1, xmm3
    const u32 w041 = word(arguments + 1); // original006a65ec
    const u32 w042 = word(arguments + 2); // original006a65ef
    store(w041, v062);                    // original006a65f2
    store(w042, v061);                    // original006a65f5
    return u64(w041) | (u64(w042) << 32);
}
extern "C" __attribute__((naked, stdcall)) u64 FUN_006a6410(const void*, void*, void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_packed_trig_006a6410\n\taddl $4,%esp\n\tretl $12");
}
extern "C" __attribute__((target("sse2"), force_align_arg_pointer)) u64
recovered_packed_trig_006a65fc(const u32* arguments) {
    const u32 w043 = word(arguments + 0); // original006a6601
    const V v063 = aligned(w043);         // original006a6604 movaps xmm0, xmmword ptr [eax]
    const V v064 = v063;                  // original006a6608 movaps xmm1, xmm0
    const V v065 = v063;                  // original006a660b movaps xmm6, xmm0
    const V v066 =
        integer_and(v063, aligned(reinterpret_cast<u32>(
                              dat_00717d60))); // original006a660e pand xmm0, xmmword ptr [0x717d60]
    const V v067 =
        integer_and(v064, aligned(reinterpret_cast<u32>(
                              dat_00717d50))); // original006a6616 pand xmm1, xmmword ptr [0x717d50]
    const V v068 = v066;                       // original006a661e movaps xmm2, xmm0
    const V v069 = v066;                       // original006a6621 movaps xmm7, xmm0
    const V v070 =
        mul(v066, aligned(reinterpret_cast<u32>(
                      dat_00717d40))); // original006a6624 mulps xmm0, xmmword ptr [0x717d40]
    const V v071 = aligned(reinterpret_cast<u32>(
        dat_00717d30)); // original006a662b movaps xmm4, xmmword ptr [0x717d30]
    const V v072 = aligned(reinterpret_cast<u32>(
        dat_00717d20)); // original006a6632 movaps xmm5, xmmword ptr [0x717d20]
    const V v073 = aligned(reinterpret_cast<u32>(
        dat_00717d10)); // original006a6639 movaps xmm6, xmmword ptr [0x717d10]
    const V v074 = aligned(reinterpret_cast<u32>(
        dat_00717d00)); // original006a6640 movaps xmm7, xmmword ptr [0x717d00]
    const V v075 =
        add(v070, aligned(reinterpret_cast<u32>(
                      dat_00717cf0))); // original006a6647 addps xmm0, xmmword ptr [0x717cf0]
    const V v076 = v075;               // original006a664e movaps xmm3, xmm0
    const V v077 =
        sub(v075, aligned(reinterpret_cast<u32>(
                      dat_00717cf0))); // original006a6651 subps xmm0, xmmword ptr [0x717cf0]
    const V v078 = mul(v071, v077);    // original006a6658 mulps xmm4, xmm0
    const V v079 = mul(v072, v077);    // original006a665b mulps xmm5, xmm0
    const V v080 = mul(v073, v077);    // original006a665e mulps xmm6, xmm0
    const V v081 = mul(v074, v077);    // original006a6661 mulps xmm7, xmm0
    const V v082 = sub(v068, v078);    // original006a6664 subps xmm2, xmm4
    const V v083 = sub(v082, v079);    // original006a6667 subps xmm2, xmm5
    const V v084 = aligned(reinterpret_cast<u32>(
        dat_00717ce0));             // original006a666a movaps xmm5, xmmword ptr [0x717ce0]
    const V v085 = sub(v083, v080); // original006a6671 subps xmm2, xmm6
    const V v086 = aligned(reinterpret_cast<u32>(
        dat_00717cd0));             // original006a6674 movaps xmm6, xmmword ptr [0x717cd0]
    const V v087 = sub(v085, v081); // original006a667b subps xmm2, xmm7
    const V v088 = v087;            // original006a667e movaps xmm4, xmm2
    const V v089 = mul(v088, v088); // original006a6681 mulps xmm4, xmm4
    const V v090 =
        and_bits(v076, aligned(reinterpret_cast<u32>(
                           dat_00717cc0))); // original006a6684 andps xmm3, xmmword ptr [0x717cc0]
    const V v091 = v090;                    // original006a668b movaps xmm0, xmm3
    const V v092 = v090;                    // original006a668e movaps xmm7, xmm3
    const V v093 =
        and_bits(v091, aligned(reinterpret_cast<u32>(
                           dat_00717cb0))); // original006a6691 andps xmm0, xmmword ptr [0x717cb0]
    const V v094 = integer_sub(v090, v093); // original006a6698 psubd xmm3, xmm0
    const V v095 = integer_add(v092, v093); // original006a669c paddd xmm7, xmm0
    const V v096 =
        integer_and(v094, aligned(reinterpret_cast<u32>(
                              dat_00717ca0))); // original006a66a0 pand xmm3, xmmword ptr [0x717ca0]
    const V v097 =
        integer_and(v095, aligned(reinterpret_cast<u32>(
                              dat_00717ca0))); // original006a66a8 pand xmm7, xmmword ptr [0x717ca0]
    const V v098 = shift_thirty(v096);         // original006a66b0 pslld xmm3, 0x1e
    const V v099 = shift_thirty(v097);         // original006a66b5 pslld xmm7, 0x1e
    const V v100 = integer_xor(v098, v067);    // original006a66ba pxor xmm3, xmm1
    const V v101 = shift_thirty(v093);         // original006a66be pslld xmm0, 0x1e
    const V v102 = integer_xor(v067, v067);    // original006a66c3 pxor xmm1, xmm1
    const V v103 = not_equal(v101, v102);      // original006a66c7 cmpneqps xmm0, xmm1
    const V v104 = mul(v084, v089);            // original006a66cb mulps xmm5, xmm4
    const V v105 = mul(v086, v089);            // original006a66ce mulps xmm6, xmm4
    const V v106 =
        add(v104, aligned(reinterpret_cast<u32>(
                      dat_00717c90))); // original006a66d1 addps xmm5, xmmword ptr [0x717c90]
    const V v107 =
        add(v105, aligned(reinterpret_cast<u32>(
                      dat_00717c80))); // original006a66d8 addps xmm6, xmmword ptr [0x717c80]
    const V v108 = mul(v106, v089);    // original006a66df mulps xmm5, xmm4
    const V v109 = mul(v107, v089);    // original006a66e2 mulps xmm6, xmm4
    const V v110 =
        add(v108, aligned(reinterpret_cast<u32>(
                      dat_00717c70))); // original006a66e5 addps xmm5, xmmword ptr [0x717c70]
    const V v111 =
        add(v109, aligned(reinterpret_cast<u32>(
                      dat_00717c60))); // original006a66ec addps xmm6, xmmword ptr [0x717c60]
    const V v112 = mul(v110, v089);    // original006a66f3 mulps xmm5, xmm4
    const V v113 = mul(v111, v089);    // original006a66f6 mulps xmm6, xmm4
    const V v114 =
        add(v112, aligned(reinterpret_cast<u32>(
                      dat_00717c50))); // original006a66f9 addps xmm5, xmmword ptr [0x717c50]
    const V v115 =
        add(v113, aligned(reinterpret_cast<u32>(
                      dat_00717c40))); // original006a6700 addps xmm6, xmmword ptr [0x717c40]
    const V v116 = mul(v114, v087);    // original006a6707 mulps xmm5, xmm2
    const V v117 = mul(v115, v089);    // original006a670a mulps xmm6, xmm4
    const V v118 =
        add(v117, aligned(reinterpret_cast<u32>(
                      dat_00717c30)));    // original006a670d addps xmm6, xmmword ptr [0x717c30]
    const V v119 = v103;                  // original006a6714 movaps xmm1, xmm0
    const V v120 = v103;                  // original006a6717 movaps xmm2, xmm0
    const V v121 = and_not(v119, v116);   // original006a671a andnps xmm1, xmm5
    const V v122 = and_bits(v120, v118);  // original006a671d andps xmm2, xmm6
    const V v123 = or_bits(v121, v122);   // original006a6720 orps xmm1, xmm2
    const V v124 = v103;                  // original006a6723 movaps xmm2, xmm0
    const V v125 = and_bits(v103, v116);  // original006a6726 andps xmm0, xmm5
    const V v126 = and_not(v124, v118);   // original006a6729 andnps xmm2, xmm6
    const V v127 = or_bits(v125, v126);   // original006a672c orps xmm0, xmm2
    const V v128 = xor_bits(v127, v099);  // original006a672f xorps xmm0, xmm7
    const V v129 = xor_bits(v123, v100);  // original006a6732 xorps xmm1, xmm3
    const u32 w044 = word(arguments + 1); // original006a6735
    const u32 w045 = word(arguments + 2); // original006a6738
    store(w044, v129);                    // original006a673b
    store(w045, v128);                    // original006a673e
    return u64(w044) | (u64(w045) << 32);
}
extern "C" __attribute__((naked, stdcall)) u64 FUN_006a65fc(const void*, void*, void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_packed_trig_006a65fc\n\taddl $4,%esp\n\tretl $12");
}
extern "C" __attribute__((target("sse"), force_align_arg_pointer)) u32
recovered_packed_quaternion_006801e3(const u32* arguments) {
    alignas(16) u32 first[4], second[4];
    const u32 a = reinterpret_cast<u32>(first), b = reinterpret_cast<u32>(second);
    const V z = scalar(reinterpret_cast<u32>(arguments + 3));
    scalar_store(a, z);
    const V y = scalar(reinterpret_cast<u32>(arguments + 2)),
            factor = aligned(reinterpret_cast<u32>(dat_006f3900));
    scalar_store(a + 4, y);
    const V x = scalar(reinterpret_cast<u32>(arguments + 1));
    scalar_store(a + 8, x);
    const V zero = scalar(reinterpret_cast<u32>(dat_006bb5fc));
    scalar_store(a + 12, zero);
    const V scaled = mul(aligned(a), factor);
    store(a, scaled);
    FUN_006a6410(first, first, second);
    const V v0 = aligned(a), v1 = shuffle<0x99>(v0, aligned(b)), v2 = shuffle<0>(v0, aligned(b));
    const V v3 = shuffle<0xf7>(v1, v1), v4 = shuffle<0xa8>(v1, v1), v5 = shuffle<0x8a>(v2, v2),
            v6 = shuffle<0x8a>(v5, v5);
    const V v7 = mul(v5, v3), v8 = mul(v7, v4), v9 = shuffle<1>(v4, v4),
            mask = aligned(reinterpret_cast<u32>(dat_006f38f0));
    const u32 output = word(arguments);
    const V v10 = shuffle<0x51>(v3, v3), v11 = mul(v6, v10), v12 = mul(v11, v9),
            v13 = xor_bits(v12, mask), result = add(v8, v13);
    store_unaligned(output, result);
    return output;
}
extern "C" __attribute__((naked, stdcall)) void* FUN_006801e3(void*, float, float, float) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_packed_quaternion_006801e3\n\taddl $4,%esp\n\tretl $16");
}
extern "C" __attribute__((target("sse2"), force_align_arg_pointer)) u32
recovered_packed_quaternion_00683ee0(const u32* arguments) {
    alignas(16) u32 first[4], second[4];
    const u32 a = reinterpret_cast<u32>(first), b = reinterpret_cast<u32>(second);
    const V z = scalar(reinterpret_cast<u32>(arguments + 3));
    scalar_store(a, z);
    const V y = scalar(reinterpret_cast<u32>(arguments + 2)),
            factor = aligned(reinterpret_cast<u32>(dat_006f3990));
    scalar_store(a + 4, y);
    const V x = scalar(reinterpret_cast<u32>(arguments + 1));
    scalar_store(a + 8, x);
    const V zero = scalar(reinterpret_cast<u32>(dat_006bb5fc));
    scalar_store(a + 12, zero);
    const V scaled = mul(aligned(a), factor);
    store(a, scaled);
    FUN_006a65fc(first, first, second);
    const V v0 = aligned(a), v1 = shuffle<0x99>(v0, aligned(b)), v2 = shuffle<0>(v0, aligned(b));
    const V v3 = shuffle<0xf7>(v1, v1), v4 = shuffle<0xa8>(v1, v1), v5 = shuffle<0x8a>(v2, v2),
            v6 = shuffle<0x8a>(v5, v5);
    const V v7 = mul(v5, v3), v8 = mul(v7, v4), v9 = shuffle<1>(v4, v4),
            mask = aligned(reinterpret_cast<u32>(dat_006f3980));
    const u32 output = word(arguments);
    const V v10 = shuffle<0x51>(v3, v3), v11 = mul(v6, v10), v12 = mul(v11, v9),
            v13 = xor_bits(v12, mask), result = add(v8, v13);
    store_unaligned(output, result);
    return output;
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00683ee0(void*, float, float, float) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_packed_quaternion_00683ee0\n\taddl $4,%esp\n\tretl $16");
}
extern "C" {
alignas(4) extern const uint32_t dat_006bb5fc[1] = {0x00000000u};
alignas(16) extern const uint32_t dat_006f38f0[4] = {0x00000000u, 0x80000000u, 0x80000000u,
                                                     0x00000000u};
alignas(16) extern const uint32_t dat_006f3900[4] = {0x3f000000u, 0x3f000000u, 0x3f000000u,
                                                     0x3f000000u};
alignas(16) extern const uint32_t dat_006f3980[4] = {0x00000000u, 0x80000000u, 0x80000000u,
                                                     0x00000000u};
alignas(16) extern const uint32_t dat_006f3990[4] = {0x3f000000u, 0x3f000000u, 0x3f000000u,
                                                     0x3f000000u};
alignas(16) uint32_t dat_00717af0[4] = {0x3f800000u, 0x3f800000u, 0x3f800000u, 0x3f800000u};
alignas(16) uint32_t dat_00717b00[4] = {0xbf000000u, 0xbf000000u, 0xbf000000u, 0xbf000000u};
alignas(16) uint32_t dat_00717b10[4] = {0x3f800000u, 0x3f800000u, 0x3f800000u, 0x3f800000u};
alignas(16) uint32_t dat_00717b20[4] = {0x3d2aaaa5u, 0x3d2aaaa5u, 0x3d2aaaa5u, 0x3d2aaaa5u};
alignas(16) uint32_t dat_00717b30[4] = {0xbe2aaaa3u, 0xbe2aaaa3u, 0xbe2aaaa3u, 0xbe2aaaa3u};
alignas(16) uint32_t dat_00717b40[4] = {0xbab6061au, 0xbab6061au, 0xbab6061au, 0xbab6061au};
alignas(16) uint32_t dat_00717b50[4] = {0x3c08839du, 0x3c08839du, 0x3c08839du, 0x3c08839du};
alignas(4) uint32_t dat_00717b60[1] = {0x00000002u};
alignas(16) uint32_t dat_00717b70[4] = {0x00000001u, 0x00000001u, 0x00000001u, 0x00000001u};
alignas(16) uint32_t dat_00717b80[4] = {0x007fffffu, 0x007fffffu, 0x007fffffu, 0x007fffffu};
alignas(16) uint32_t dat_00717b90[4] = {0x37ccf5ceu, 0x37ccf5ceu, 0x37ccf5ceu, 0x37ccf5ceu};
alignas(16) uint32_t dat_00717ba0[4] = {0xb94ca1f0u, 0xb94ca1f0u, 0xb94ca1f0u, 0xb94ca1f0u};
alignas(16) uint32_t dat_00717bb0[4] = {0x4b000000u, 0x4b000000u, 0x4b000000u, 0x4b000000u};
alignas(16) uint32_t dat_00717bc0[4] = {0x2c34611au, 0x2c34611au, 0x2c34611au, 0x2c34611au};
alignas(16) uint32_t dat_00717bd0[4] = {0x33a22000u, 0x33a22000u, 0x33a22000u, 0x33a22000u};
alignas(16) uint32_t dat_00717be0[4] = {0x39fda000u, 0x39fda000u, 0x39fda000u, 0x39fda000u};
alignas(16) uint32_t dat_00717bf0[4] = {0x3fc90000u, 0x3fc90000u, 0x3fc90000u, 0x3fc90000u};
alignas(16) uint32_t dat_00717c00[4] = {0x3f22f983u, 0x3f22f983u, 0x3f22f983u, 0x3f22f983u};
alignas(16) uint32_t dat_00717c10[4] = {0x80000000u, 0x80000000u, 0x80000000u, 0x80000000u};
alignas(16) uint32_t dat_00717c20[4] = {0x7fffffffu, 0x7fffffffu, 0x7fffffffu, 0x7fffffffu};
alignas(16) uint32_t dat_00717c30[4] = {0x3f800000u, 0x3f800000u, 0x3f800000u, 0x3f800000u};
alignas(16) uint32_t dat_00717c40[4] = {0xbf000000u, 0xbf000000u, 0xbf000000u, 0xbf000000u};
alignas(16) uint32_t dat_00717c50[4] = {0x3f800000u, 0x3f800000u, 0x3f800000u, 0x3f800000u};
alignas(16) uint32_t dat_00717c60[4] = {0x3d2aaaa5u, 0x3d2aaaa5u, 0x3d2aaaa5u, 0x3d2aaaa5u};
alignas(16) uint32_t dat_00717c70[4] = {0xbe2aaaa3u, 0xbe2aaaa3u, 0xbe2aaaa3u, 0xbe2aaaa3u};
alignas(16) uint32_t dat_00717c80[4] = {0xbab6061au, 0xbab6061au, 0xbab6061au, 0xbab6061au};
alignas(16) uint32_t dat_00717c90[4] = {0x3c08839du, 0x3c08839du, 0x3c08839du, 0x3c08839du};
alignas(16) uint32_t dat_00717ca0[4] = {0x00000002u, 0x00000002u, 0x00000002u, 0x00000002u};
alignas(16) uint32_t dat_00717cb0[4] = {0x00000001u, 0x00000001u, 0x00000001u, 0x00000001u};
alignas(16) uint32_t dat_00717cc0[4] = {0x007fffffu, 0x007fffffu, 0x007fffffu, 0x007fffffu};
alignas(16) uint32_t dat_00717cd0[4] = {0x37ccf5ceu, 0x37ccf5ceu, 0x37ccf5ceu, 0x37ccf5ceu};
alignas(16) uint32_t dat_00717ce0[4] = {0xb94ca1f0u, 0xb94ca1f0u, 0xb94ca1f0u, 0xb94ca1f0u};
alignas(16) uint32_t dat_00717cf0[4] = {0x4b000000u, 0x4b000000u, 0x4b000000u, 0x4b000000u};
alignas(16) uint32_t dat_00717d00[4] = {0x2c34611au, 0x2c34611au, 0x2c34611au, 0x2c34611au};
alignas(16) uint32_t dat_00717d10[4] = {0x33a22000u, 0x33a22000u, 0x33a22000u, 0x33a22000u};
alignas(16) uint32_t dat_00717d20[4] = {0x39fda000u, 0x39fda000u, 0x39fda000u, 0x39fda000u};
alignas(16) uint32_t dat_00717d30[4] = {0x3fc90000u, 0x3fc90000u, 0x3fc90000u, 0x3fc90000u};
alignas(16) uint32_t dat_00717d40[4] = {0x3f22f983u, 0x3f22f983u, 0x3f22f983u, 0x3f22f983u};
alignas(16) uint32_t dat_00717d50[4] = {0x80000000u, 0x80000000u, 0x80000000u, 0x80000000u};
alignas(16) uint32_t dat_00717d60[4] = {0x7fffffffu, 0x7fffffffu, 0x7fffffffu, 0x7fffffffu};
}
