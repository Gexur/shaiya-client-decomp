#include "graphics/render_backend_681331_sse.h"
namespace {
using u32 = uint32_t;
using V = float __attribute__((vector_size(16)));
struct B4 {
    unsigned char bytes[4];
};
struct B8 {
    unsigned char bytes[8];
};
struct B16 {
    unsigned char bytes[16];
};
#define SIMD __attribute__((target("sse"), always_inline)) inline
u32 word(const u32* p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
SIMD V scalar(u32 p) {
    V v;
    __asm__ volatile("movss %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B4*>(p)) : "memory");
    return v;
}
SIMD V scalar_word(u32 v) {
    V result;
    __asm__ volatile("movss %1,%0" : "=x"(result) : "m"(v));
    return result;
}
SIMD V high(V v, u32 p) {
    __asm__ volatile("movhps %1,%0" : "+x"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return v;
}
SIMD V aligned(const u32* p) {
    V v;
    __asm__ volatile("movaps %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B16*>(p)) : "memory");
    return v;
}
SIMD V add(V a, V b) {
    __asm__ volatile("addps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V sub(V a, V b) {
    __asm__ volatile("subps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V mul(V a, V b) {
    __asm__ volatile("mulps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V adds(V a, V b) {
    __asm__ volatile("addss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V subs(V a, V b) {
    __asm__ volatile("subss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V muls(V a, V b) {
    __asm__ volatile("mulss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V high_to_low(V a, V b) {
    __asm__ volatile("movhlps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V low_to_high(V a, V b) {
    __asm__ volatile("movlhps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V unpack_low(V a, V b) {
    __asm__ volatile("unpcklps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
template <int mask> SIMD V shuffle(V a, V b) {
    __asm__ volatile("shufps %2,%1,%0" : "+x"(a) : "x"(b), "i"(mask));
    return a;
}
SIMD void vector_store(void* p, V v) {
    __asm__ volatile("movups %1,%0" : "=m"(*reinterpret_cast<B16*>(p)) : "x"(v) : "memory");
}
SIMD void scalar_store(u32* p, V v) {
    __asm__ volatile("movss %1,%0" : "=m"(*reinterpret_cast<B4*>(p)) : "x"(v) : "memory");
}
void copy_words(u32 output, const u32* input, u32 bytes) {
    u32 count = bytes >> 2;
    __asm__ volatile("rep movsl" : "+D"(output), "+S"(input), "+c"(count)::"memory");
    count = bytes & 3;
    __asm__ volatile("rep movsb" : "+D"(output), "+S"(input), "+c"(count)::"memory");
}
} // namespace
extern "C" __attribute__((target("sse"), force_align_arg_pointer)) u32
recovered_sse_backend_681331(const u32* arguments) {
    alignas(16) unsigned char frame_storage[0x2d0];
    const u32 frame = reinterpret_cast<u32>(frame_storage) + 0x2d0;
    const u32 arg_4 = word(arguments + 4); // original00681358
    const u32 arg_5 = word(arguments + 5); // original0068135b
    const V v000 = scalar(arg_4 + 8);      // original0068135e movss xmm0, dword ptr [eax + 8]
    put(frame - 164, arg_4);               // original00681363
    const u32 arg_6 = word(arguments + 6); // original00681369
    vector_store(reinterpret_cast<void*>(frame - 704), v000); // original0068136c
    const V v001 = high(v000, arg_4);       // original00681373 movhps xmm0, qword ptr [eax]
    const u32 arg_0 = word(arguments + 0);  // original00681376
    const u32 arg_7 = word(arguments + 7);  // original00681379
    const V v002 = v001;                    // original0068137c movaps xmm1, xmm0
    put(frame - 168, arg_7);                // original0068137f
    const u32 arg_3 = word(arguments + 3);  // original00681385
    const V v003 = shuffle<78>(v002, v001); // original00681388 shufps xmm1, xmm0, 0x4e
    put(frame - 144, arg_3);                // original0068138c
    const u32 arg_1 = word(arguments + 1);  // original00681392
    vector_store(reinterpret_cast<void*>(frame - 704), v003); // original00681395
    put(frame - 140, arg_1);                                  // original0068139c
    const u32 arg_2 = word(arguments + 2);                    // original006813a2
    const V v004 = scalar(arg_5 + 8); // original006813a5 movss xmm0, dword ptr [edi + 8]
    vector_store(reinterpret_cast<void*>(frame - 608), v004); // original006813aa
    const V v005 = high(v004, arg_5);       // original006813b1 movhps xmm0, qword ptr [edi]
    const V v006 = shuffle<78>(v005, v005); // original006813b4 shufps xmm0, xmm0, 0x4e
    vector_store(reinterpret_cast<void*>(frame - 608), v006); // original006813b8
    const V v007 = scalar(arg_6 + 8); // original006813bf movss xmm0, dword ptr [esi + 8]
    vector_store(reinterpret_cast<void*>(frame - 560), v007); // original006813c4
    const V v008 = high(v007, arg_6);       // original006813cb movhps xmm0, qword ptr [esi]
    const V v009 = shuffle<78>(v008, v008); // original006813ce shufps xmm0, xmm0, 0x4e
    vector_store(reinterpret_cast<void*>(frame - 560), v009); // original006813d2
    const V v010 = scalar(arg_0 + 8); // original006813d9 movss xmm0, dword ptr [eax + 8]
    vector_store(reinterpret_cast<void*>(frame - 544), v010); // original006813de
    const V v011 = high(v010, arg_0);       // original006813e5 movhps xmm0, qword ptr [eax]
    const V v012 = v011;                    // original006813e8 movaps xmm1, xmm0
    const V v013 = shuffle<78>(v012, v011); // original006813eb shufps xmm1, xmm0, 0x4e
    vector_store(reinterpret_cast<void*>(frame - 544), v013); // original006813ef
    const V v014 = scalar(arg_0 + 20); // original006813f6 movss xmm0, dword ptr [eax + 0x14]
    const V v015 = aligned(reinterpret_cast<const u32*>(
        frame - 608)); // original006813fb movaps xmm4, xmmword ptr [ebp - 0x260]
    vector_store(reinterpret_cast<void*>(frame - 528), v014); // original00681402
    const V v016 = high(v014, arg_0 + 12);  // original00681409 movhps xmm0, qword ptr [eax + 0xc]
    const V v017 = shuffle<78>(v016, v016); // original0068140d shufps xmm0, xmm0, 0x4e
    vector_store(reinterpret_cast<void*>(frame - 528), v017); // original00681411
    const V v018 = scalar(arg_0 + 32); // original00681418 movss xmm1, dword ptr [eax + 0x20]
    const V v019 = v017;               // original0068141d movaps xmm5, xmm0
    vector_store(reinterpret_cast<void*>(frame - 512), v018); // original00681420
    const V v020 = high(v018, arg_0 + 24);  // original00681427 movhps xmm1, qword ptr [eax + 0x18]
    const V v021 = v017;                    // original0068142b movaps xmm6, xmm0
    const V v022 = shuffle<78>(v020, v020); // original0068142e shufps xmm1, xmm1, 0x4e
    const V v023 = v017;                    // original00681432 movaps xmm7, xmm0
    vector_store(reinterpret_cast<void*>(frame - 512), v022); // original00681435
    const V v024 = aligned(reinterpret_cast<const u32*>(
        frame - 704)); // original0068143c movaps xmm3, xmmword ptr [ebp - 0x2c0]
    const V v025 =
        sub(v024, aligned(reinterpret_cast<const u32*>(
                      frame - 608))); // original00681443 subps xmm3, xmmword ptr [ebp - 0x260]
    const V v026 = aligned(reinterpret_cast<const u32*>(
        frame - 544)); // original0068144a movaps xmm2, xmmword ptr [ebp - 0x220]
    const V v027 =
        mul(v025, aligned(dat_00717650)); // original00681451 mulps xmm3, xmmword ptr [0x717650]
    const V v028 = mul(v026, v027);       // original00681458 mulps xmm2, xmm3
    vector_store(reinterpret_cast<void*>(frame - 64), v023); // original0068145b
    const V v029 = aligned(reinterpret_cast<const u32*>(
        frame - 704)); // original0068145f movaps xmm7, xmmword ptr [ebp - 0x2c0]
    const V v030 =
        sub(v029, aligned(reinterpret_cast<const u32*>(
                      frame - 560))); // original00681466 subps xmm7, xmmword ptr [ebp - 0x230]
    const V v031 =
        mul(v030, aligned(dat_00717650)); // original0068146d mulps xmm7, xmmword ptr [0x717650]
    vector_store(reinterpret_cast<void*>(frame - 688), v028); // original00681474
    vector_store(reinterpret_cast<void*>(frame - 48), v021);  // original0068147b
    const V v032 = aligned(reinterpret_cast<const u32*>(
        frame - 544));              // original0068147f movaps xmm6, xmmword ptr [ebp - 0x220]
    const V v033 = mul(v032, v031); // original00681486 mulps xmm6, xmm7
    vector_store(reinterpret_cast<void*>(frame - 672), v033); // original00681489
    vector_store(reinterpret_cast<void*>(frame - 32), v019);  // original00681490
    const V v034 = v028;                                      // original00681494 movaps xmm5, xmm2
    const V v035 = high_to_low(v034, v033);                   // original00681497 movhlps xmm5, xmm6
    const V v036 = low_to_high(v033, v028);                   // original0068149a movlhps xmm6, xmm2
    const V v037 = add(v035, v036);                           // original0068149d addps xmm5, xmm6
    const V v038 = shuffle<245>(v036, v036); // original006814a0 shufps xmm6, xmm6, 0xf5
    const V v039 = add(v037, v038);          // original006814a4 addps xmm5, xmm6
    const V v040 = aligned(reinterpret_cast<const u32*>(
        frame - 704));              // original006814a7 movaps xmm2, xmmword ptr [ebp - 0x2c0]
    const V v041 = sub(v040, v027); // original006814ae subps xmm2, xmm3
    const V v042 = v039;            // original006814b1 movaps xmm3, xmm5
    const V v043 = shuffle<170>(v042, v042); // original006814b4 shufps xmm3, xmm3, 0xaa
    const V v044 = shuffle<0>(v039, v039);   // original006814b8 shufps xmm5, xmm5, 0
    const V v045 =
        mul(v043, aligned(reinterpret_cast<const u32*>(
                      frame - 544))); // original006814bc mulps xmm3, xmmword ptr [ebp - 0x220]
    const V v046 = add(v041, v045);   // original006814c3 addps xmm2, xmm3
    const V v047 = v022;              // original006814c6 movaps xmm3, xmm1
    vector_store(reinterpret_cast<void*>(frame - 688), v046); // original006814c9
    const V v048 =
        mul(v044, aligned(reinterpret_cast<const u32*>(
                      frame - 544))); // original006814d0 mulps xmm5, xmmword ptr [ebp - 0x220]
    vector_store(reinterpret_cast<void*>(frame - 80), v047); // original006814d7
    const V v049 = aligned(reinterpret_cast<const u32*>(
        frame - 704));              // original006814db movaps xmm3, xmmword ptr [ebp - 0x2c0]
    const V v050 = sub(v049, v031); // original006814e2 subps xmm3, xmm7
    const V v051 = v022;            // original006814e5 movaps xmm6, xmm1
    const V v052 = add(v050, v048); // original006814e8 addps xmm3, xmm5
    vector_store(reinterpret_cast<void*>(frame - 96), v051);  // original006814eb
    vector_store(reinterpret_cast<void*>(frame - 672), v052); // original006814ef
    const V v053 = aligned(reinterpret_cast<const u32*>(
        frame - 704));   // original006814f6 movaps xmm5, xmmword ptr [ebp - 0x2c0]
    const V v054 = v022; // original006814fd movaps xmm6, xmm1
    vector_store(reinterpret_cast<void*>(frame - 112), v054); // original00681500
    const V v055 = v015;                                      // original00681504 movaps xmm6, xmm4
    const V v056 = sub(v055, v053);                           // original00681507 subps xmm6, xmm5
    vector_store(reinterpret_cast<void*>(frame - 128), v056); // original0068150a
    const V v057 = aligned(reinterpret_cast<const u32*>(
        frame - 32)); // original0068150e movaps xmm5, xmmword ptr [ebp - 0x20]
    const V v058 = aligned(reinterpret_cast<const u32*>(
        frame - 48)); // original00681512 movaps xmm6, xmmword ptr [ebp - 0x30]
    const V v059 = aligned(reinterpret_cast<const u32*>(
        frame - 64));               // original00681516 movaps xmm7, xmmword ptr [ebp - 0x40]
    const V v060 = add(v046, v052); // original0068151a addps xmm2, xmm3
    const V v061 = aligned(reinterpret_cast<const u32*>(
        frame - 128)); // original0068151d movaps xmm3, xmmword ptr [ebp - 0x80]
    const V v062 =
        sub(v015, aligned(reinterpret_cast<const u32*>(
                      frame - 560))); // original00681521 subps xmm4, xmmword ptr [ebp - 0x230]
    const V v063 =
        mul(v061, aligned(dat_00717650)); // original00681528 mulps xmm3, xmmword ptr [0x717650]
    const V v064 =
        mul(v062, aligned(dat_00717650)); // original0068152f mulps xmm4, xmmword ptr [0x717650]
    const V v065 = mul(v059, v063);       // original00681536 mulps xmm7, xmm3
    const V v066 = mul(v058, v064);       // original00681539 mulps xmm6, xmm4
    vector_store(reinterpret_cast<void*>(frame - 64), v022); // original0068153c
    const V v067 = v065;                                     // original00681540 movaps xmm1, xmm7
    const V v068 = high_to_low(v065, v066);                  // original00681543 movhlps xmm7, xmm6
    const V v069 = low_to_high(v066, v067);                  // original00681546 movlhps xmm6, xmm1
    const V v070 = add(v068, v069);                          // original00681549 addps xmm7, xmm6
    const V v071 = shuffle<245>(v069, v069); // original0068154c shufps xmm6, xmm6, 0xf5
    const V v072 = add(v070, v071);          // original00681550 addps xmm7, xmm6
    const V v073 = aligned(reinterpret_cast<const u32*>(
        frame - 608));              // original00681553 movaps xmm1, xmmword ptr [ebp - 0x260]
    const V v074 = sub(v073, v064); // original0068155a subps xmm1, xmm4
    const V v075 = aligned(reinterpret_cast<const u32*>(
        frame - 608));              // original0068155d movaps xmm4, xmmword ptr [ebp - 0x260]
    const V v076 = sub(v075, v063); // original00681564 subps xmm4, xmm3
    const V v077 = v072;            // original00681567 movaps xmm3, xmm7
    const V v078 = shuffle<0>(v072, v072);   // original0068156a shufps xmm7, xmm7, 0
    const V v079 = shuffle<170>(v077, v077); // original0068156e shufps xmm3, xmm3, 0xaa
    const V v080 = mul(v078, v017);          // original00681572 mulps xmm7, xmm0
    const V v081 = mul(v079, v057);          // original00681575 mulps xmm3, xmm5
    const V v082 = add(v074, v080);          // original00681578 addps xmm1, xmm7
    const V v083 = add(v076, v081);          // original0068157b addps xmm4, xmm3
    vector_store(reinterpret_cast<void*>(frame - 592), v082); // original0068157e
    vector_store(reinterpret_cast<void*>(frame - 656), v083); // original00681585
    const V v084 = aligned(reinterpret_cast<const u32*>(
        frame - 704)); // original0068158c movaps xmm0, xmmword ptr [ebp - 0x2c0]
    const V v085 = aligned(reinterpret_cast<const u32*>(
        frame - 560));                    // original00681593 movaps xmm3, xmmword ptr [ebp - 0x230]
    const V v086 = aligned(dat_00717650); // original0068159a movaps xmm5, xmmword ptr [0x717650]
    const V v087 = aligned(reinterpret_cast<const u32*>(
        frame - 112));              // original006815a1 movaps xmm6, xmmword ptr [ebp - 0x70]
    const V v088 = v085;            // original006815a5 movaps xmm7, xmm3
    const V v089 = sub(v085, v084); // original006815a8 subps xmm3, xmm0
    const V v090 = add(v060, v083); // original006815ab addps xmm2, xmm4
    const V v091 = mul(v089, v086); // original006815ae mulps xmm3, xmm5
    const V v092 = aligned(reinterpret_cast<const u32*>(
        frame - 96));               // original006815b1 movaps xmm0, xmmword ptr [ebp - 0x60]
    const V v093 = mul(v087, v091); // original006815b5 mulps xmm6, xmm3
    const V v094 =
        sub(v088, aligned(reinterpret_cast<const u32*>(
                      frame - 608))); // original006815b8 subps xmm7, xmmword ptr [ebp - 0x260]
    const V v095 = mul(v094, v086);   // original006815bf mulps xmm7, xmm5
    const V v096 = aligned(reinterpret_cast<const u32*>(
        frame - 560));              // original006815c2 movaps xmm4, xmmword ptr [ebp - 0x230]
    const V v097 = mul(v092, v095); // original006815c9 mulps xmm0, xmm7
    const V v098 = sub(v096, v091); // original006815cc subps xmm4, xmm3
    const V v099 = v093;            // original006815cf movaps xmm3, xmm6
    const V v100 = high_to_low(v093, v097); // original006815d2 movhlps xmm6, xmm0
    const V v101 = low_to_high(v097, v099); // original006815d5 movlhps xmm0, xmm3
    const V v102 = aligned(reinterpret_cast<const u32*>(
        frame - 560));              // original006815d8 movaps xmm3, xmmword ptr [ebp - 0x230]
    const V v103 = add(v100, v101); // original006815df addps xmm6, xmm0
    const V v104 = shuffle<245>(v101, v101); // original006815e2 shufps xmm0, xmm0, 0xf5
    const V v105 = sub(v102, v095);          // original006815e6 subps xmm3, xmm7
    const V v106 = add(v103, v104);          // original006815e9 addps xmm6, xmm0
    const V v107 = v106;                     // original006815ec movaps xmm5, xmm6
    const V v108 = shuffle<170>(v106, v106); // original006815ef shufps xmm6, xmm6, 0xaa
    const V v109 = shuffle<0>(v107, v107);   // original006815f3 shufps xmm5, xmm5, 0
    const V v110 =
        mul(v108, aligned(reinterpret_cast<const u32*>(
                      frame - 80)));      // original006815f7 mulps xmm6, xmmword ptr [ebp - 0x50]
    const V v111 = aligned(dat_00717690); // original006815fb movaps xmm0, xmmword ptr [0x717690]
    const V v112 = add(v098, v110);       // original00681602 addps xmm4, xmm6
    const V v113 = add(v090, v112);       // original00681605 addps xmm2, xmm4
    vector_store(reinterpret_cast<void*>(frame - 624), v112); // original00681608
    const V v114 = add(v113, v082);                           // original0068160f addps xmm2, xmm1
    const V v115 = aligned(reinterpret_cast<const u32*>(
        frame - 64));               // original00681612 movaps xmm1, xmmword ptr [ebp - 0x40]
    const V v116 = mul(v109, v115); // original00681616 mulps xmm5, xmm1
    const V v117 = add(v105, v116); // original00681619 addps xmm3, xmm5
    const V v118 = add(v114, v117); // original0068161c addps xmm2, xmm3
    vector_store(reinterpret_cast<void*>(frame - 576), v117); // original0068161f
    vector_store(reinterpret_cast<void*>(frame - 640), v118); // original00681626
    const V v119 =
        mul(v118, aligned(dat_00717680)); // original0068162d mulps xmm2, xmmword ptr [0x717680]
    vector_store(reinterpret_cast<void*>(frame - 640), v119); // original00681634
    const V v120 = aligned(reinterpret_cast<const u32*>(
        frame - 704)); // original0068163b movaps xmm1, xmmword ptr [ebp - 0x2c0]
    const V v121 =
        add(v120, aligned(reinterpret_cast<const u32*>(
                      frame - 608))); // original00681642 addps xmm1, xmmword ptr [ebp - 0x260]
    const V v122 =
        add(v121, aligned(reinterpret_cast<const u32*>(
                      frame - 560))); // original00681649 addps xmm1, xmmword ptr [ebp - 0x230]
    const V v123 = mul(v122, v111);   // original00681650 mulps xmm1, xmm0
    const V v124 = sub(v119, v123);   // original00681653 subps xmm2, xmm1
    vector_store(reinterpret_cast<void*>(frame - 640), v124); // original00681656
    if (arg_2 == 0)
        return arg_0;
    put(frame - 0x94, arg_6);
    put(frame - 0x98, arg_5);
    put(frame - 0x9c, word(reinterpret_cast<const u32*>(frame - 0xa8)) * 4);
    put(frame - 0xa0, arg_1 + arg_2 * 8);
    u32 parameters_end;
    do {
        const u32 parameters = word(reinterpret_cast<const u32*>(frame - 0x8c));
        const u32 parameter_0 = word(reinterpret_cast<const u32*>(parameters));
        put(frame - 0xb0, parameter_0);
        const u32 parameter_1 = word(reinterpret_cast<const u32*>(parameters + 4));
        put(frame - 0xac, parameter_1);
        const V v125 = scalar(reinterpret_cast<u32>(
            dat_00717660));                 // original006816a1 movss xmm2, dword ptr [0x717660]
        const V v126 = scalar(frame - 176); // original006816a9 movss xmm0, dword ptr [ebp - 0xb0]
        scalar_store(reinterpret_cast<u32*>(frame - 496), v126); // original006816b1
        const V v127 = scalar(frame - 172); // original006816b9 movss xmm1, dword ptr [ebp - 0xac]
        scalar_store(reinterpret_cast<u32*>(frame - 480), v127); // original006816c1
        const V v128 = scalar(reinterpret_cast<u32>(
            dat_00717670));                    // original006816c9 movss xmm3, dword ptr [0x717670]
        const V v129 = subs(v125, v126);       // original006816d1 subss xmm2, xmm0
        const V v130 = unpack_low(v127, v126); // original006816d5 unpcklps xmm1, xmm0
        const V v131 = muls(v126, v130);       // original006816d8 mulss xmm0, xmm1
        const V v132 = subs(v129, v130);       // original006816dc subss xmm2, xmm1
        scalar_store(reinterpret_cast<u32*>(frame - 464), v132); // original006816e0
        const V v133 = muls(v128, v132);        // original006816e8 mulss xmm3, xmm2
        const V v134 = low_to_high(v130, v132); // original006816ec movlhps xmm1, xmm2
        const V v135 = muls(v131, v133);        // original006816ef mulss xmm0, xmm3
        const V v136 = shuffle<0>(v135, v135);  // original006816f3 shufps xmm0, xmm0, 0
        const V v137 = aligned(reinterpret_cast<const u32*>(
            frame - 640));              // original006816f7 movaps xmm7, xmmword ptr [ebp - 0x280]
        const V v138 = mul(v137, v136); // original006816fe mulps xmm7, xmm0
        const V v139 = v134;            // original00681701 movaps xmm2, xmm1
        const V v140 = shuffle<201>(v139, v134); // original00681704 shufps xmm2, xmm1, 0xc9
        const V v141 = v134;                     // original00681708 movaps xmm3, xmm1
        const V v142 = shuffle<210>(v141, v134); // original0068170b shufps xmm3, xmm1, 0xd2
        const V v143 = v134;                     // original0068170f movaps xmm5, xmm1
        const V v144 = mul(v143, v134);          // original00681712 mulps xmm5, xmm1
        const V v145 = mul(v134, v144);          // original00681715 mulps xmm1, xmm5
        const V v146 = v145;                     // original00681718 movaps xmm4, xmm1
        const V v147 = shuffle<0>(v146, v145);   // original0068171b shufps xmm4, xmm1, 0
        const V v148 =
            mul(v147, aligned(reinterpret_cast<const u32*>(
                          frame - 704))); // original0068171f mulps xmm4, xmmword ptr [ebp - 0x2c0]
        const V v149 = add(v138, v148);   // original00681726 addps xmm7, xmm4
        const V v150 = v145;              // original00681729 movaps xmm4, xmm1
        const V v151 = shuffle<85>(v150, v145); // original0068172c shufps xmm4, xmm1, 0x55
        const V v152 =
            mul(v151, aligned(reinterpret_cast<const u32*>(
                          frame - 560))); // original00681730 mulps xmm4, xmmword ptr [ebp - 0x230]
        const V v153 = add(v149, v152);   // original00681737 addps xmm7, xmm4
        const V v154 = v145;              // original0068173a movaps xmm4, xmm1
        const V v155 = shuffle<170>(v154, v145); // original0068173d shufps xmm4, xmm1, 0xaa
        const V v156 =
            mul(v155, aligned(reinterpret_cast<const u32*>(
                          frame - 608))); // original00681741 mulps xmm4, xmmword ptr [ebp - 0x260]
        const V v157 = add(v153, v156);   // original00681748 addps xmm7, xmm4
        const V v158 =
            mul(v144, aligned(dat_00717640)); // original0068174b mulps xmm5, xmmword ptr [0x717640]
        const V v159 = v158;                  // original00681752 movaps xmm1, xmm5
        const V v160 = mul(v159, v140);       // original00681755 mulps xmm1, xmm2
        const V v161 = v160;                  // original00681758 movaps xmm4, xmm1
        const V v162 = shuffle<0>(v161, v160); // original0068175b shufps xmm4, xmm1, 0
        const V v163 =
            mul(v162, aligned(reinterpret_cast<const u32*>(
                          frame - 672))); // original0068175f mulps xmm4, xmmword ptr [ebp - 0x2a0]
        const V v164 = add(v157, v163);   // original00681766 addps xmm7, xmm4
        const V v165 = v160;              // original00681769 movaps xmm4, xmm1
        const V v166 = shuffle<85>(v165, v160); // original0068176c shufps xmm4, xmm1, 0x55
        const V v167 =
            mul(v166, aligned(reinterpret_cast<const u32*>(
                          frame - 576))); // original00681770 mulps xmm4, xmmword ptr [ebp - 0x240]
        const V v168 = add(v164, v167);   // original00681777 addps xmm7, xmm4
        const V v169 = v160;              // original0068177a movaps xmm4, xmm1
        const V v170 = shuffle<170>(v169, v160); // original0068177d shufps xmm4, xmm1, 0xaa
        const V v171 =
            mul(v170, aligned(reinterpret_cast<const u32*>(
                          frame - 656))); // original00681781 mulps xmm4, xmmword ptr [ebp - 0x290]
        const V v172 = add(v168, v171);   // original00681788 addps xmm7, xmm4
        const V v173 = v158;              // original0068178b movaps xmm1, xmm5
        const V v174 = mul(v173, v142);   // original0068178e mulps xmm1, xmm3
        const V v175 = v174;              // original00681791 movaps xmm4, xmm1
        const V v176 = shuffle<0>(v175, v174); // original00681794 shufps xmm4, xmm1, 0
        const V v177 =
            mul(v176, aligned(reinterpret_cast<const u32*>(
                          frame - 688))); // original00681798 mulps xmm4, xmmword ptr [ebp - 0x2b0]
        const V v178 = add(v172, v177);   // original0068179f addps xmm7, xmm4
        const V v179 = v174;              // original006817a2 movaps xmm4, xmm1
        const V v180 = shuffle<85>(v179, v174); // original006817a5 shufps xmm4, xmm1, 0x55
        const V v181 =
            mul(v180, aligned(reinterpret_cast<const u32*>(
                          frame - 624))); // original006817a9 mulps xmm4, xmmword ptr [ebp - 0x270]
        const V v182 = add(v178, v181);   // original006817b0 addps xmm7, xmm4
        const V v183 = v174;              // original006817b3 movaps xmm4, xmm1
        const V v184 = shuffle<170>(v183, v174); // original006817b6 shufps xmm4, xmm1, 0xaa
        const V v185 =
            mul(v184, aligned(reinterpret_cast<const u32*>(
                          frame - 592))); // original006817ba mulps xmm4, xmmword ptr [ebp - 0x250]
        const V v186 = add(v182, v185);   // original006817c1 addps xmm7, xmm4
        vector_store(reinterpret_cast<void*>(frame - 448), v186); // original006817c4
        u32 dimensions = word(reinterpret_cast<const u32*>(frame - 0xa8)), component = 3;
        if (dimensions > 3) {
            const u32 input_c = word(reinterpret_cast<const u32*>(frame - 0x94)),
                      input_b = word(reinterpret_cast<const u32*>(frame - 0x98));
            do {
                const u32 input_a = word(reinterpret_cast<const u32*>(frame - 0xa4));
                const V weight_b = aligned(reinterpret_cast<const u32*>(frame - 0x1e0)),
                        first = scalar(input_a + component * 4),
                        weight_c = aligned(reinterpret_cast<const u32*>(frame - 0x1d0)),
                        first_product = muls(first, weight_b);
                const V second = scalar(input_b + component * 4),
                        weight_a = aligned(reinterpret_cast<const u32*>(frame - 0x1f0)),
                        second_product = muls(second, weight_c);
                const V third = scalar(input_c + component * 4),
                        sum = adds(first_product, second_product),
                        third_product = muls(third, weight_a), result = adds(sum, third_product);
                scalar_store(reinterpret_cast<u32*>(frame - 0x1c0 + component * 4), result);
                ++component;
                dimensions = word(reinterpret_cast<const u32*>(frame - 0xa8));
            } while (component < dimensions);
            put(frame - 0x98, input_b);
            put(frame - 0x94, input_c);
        }
        const u32 output = word(reinterpret_cast<const u32*>(frame - 0x90)),
                  bytes = word(reinterpret_cast<const u32*>(frame - 0x9c));
        copy_words(output, reinterpret_cast<const u32*>(frame - 0x1c0), bytes);
        const u32 previous_output = word(reinterpret_cast<const u32*>(frame - 0x90)),
                  dimension = word(reinterpret_cast<const u32*>(frame - 0xa8)),
                  previous_parameters = word(reinterpret_cast<const u32*>(frame - 0x8c));
        put(frame - 0x90, previous_output + dimension * 4);
        parameters_end = word(reinterpret_cast<const u32*>(frame - 0xa0));
        put(frame - 0x8c, previous_parameters + 8);
        if (previous_parameters + 8 >= parameters_end)
            break;
    } while (true);
    return parameters_end;
}
extern "C" __attribute__((naked, stdcall)) uint32_t FUN_00681331(uint32_t, uint32_t, uint32_t,
                                                                 uint32_t, uint32_t, uint32_t,
                                                                 uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse_backend_681331\n\taddl $4,%esp\n\tretl $32");
}
extern "C" {
alignas(16) uint32_t dat_00717640[4] = {0x40400000u, 0x40400000u, 0x40400000u, 0x40400000u};
alignas(16) uint32_t dat_00717650[4] = {0x3eaaaaabu, 0x3eaaaaabu, 0x3eaaaaabu, 0x3eaaaaabu};
alignas(4) uint32_t dat_00717660[1] = {0x3f800000u};
alignas(4) uint32_t dat_00717670[1] = {0x40c00000u};
alignas(16) uint32_t dat_00717680[4] = {0x3e800000u, 0x3e800000u, 0x3e800000u, 0x3e800000u};
alignas(16) uint32_t dat_00717690[4] = {0x3e2aaa7eu, 0x3e2aaa7eu, 0x3e2aaa7eu, 0x3e2aaa7eu};
}
