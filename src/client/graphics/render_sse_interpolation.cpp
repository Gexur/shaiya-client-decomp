#include "graphics/render_sse_interpolation.h"
namespace {
using Vector = float __attribute__((vector_size(16)));
struct Bytes4 {
    unsigned char b[4];
};
struct Bytes8 {
    unsigned char b[8];
};
struct Bytes16 {
    unsigned char b[16];
};
#define SSE_INLINE __attribute__((target("sse"), always_inline)) inline
uint32_t word(const uint32_t* p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
SSE_INLINE Vector zero() {
    Vector v;
    __asm__ volatile("xorps %0,%0" : "=x"(v));
    return v;
}
SSE_INLINE Vector scalar(const void* p) {
    Vector v;
    __asm__ volatile("movss %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const Bytes4*>(p)) : "memory");
    return v;
}
SSE_INLINE Vector block(const void* p) {
    Vector v;
    __asm__ volatile("movups %1,%0"
                     : "=x"(v)
                     : "m"(*reinterpret_cast<const Bytes16*>(p))
                     : "memory");
    return v;
}
SSE_INLINE Vector low(Vector v, const void* p) {
    __asm__ volatile("movlps %1,%0"
                     : "+x"(v)
                     : "m"(*reinterpret_cast<const Bytes8*>(p))
                     : "memory");
    return v;
}
SSE_INLINE Vector high(Vector v, const void* p) {
    __asm__ volatile("movhps %1,%0"
                     : "+x"(v)
                     : "m"(*reinterpret_cast<const Bytes8*>(p))
                     : "memory");
    return v;
}
SSE_INLINE Vector copy_low(Vector a, Vector b) {
    __asm__ volatile("movss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE_INLINE Vector high_to_low(Vector a, Vector b) {
    __asm__ volatile("movhlps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
template <unsigned k> SSE_INLINE Vector shuffle(Vector a, Vector b) {
    __asm__ volatile("shufps %2,%1,%0" : "+x"(a) : "x"(b), "i"(k));
    return a;
}
SSE_INLINE Vector addps(Vector a, Vector b) {
    __asm__ volatile("addps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE_INLINE Vector subps(Vector a, Vector b) {
    __asm__ volatile("subps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE_INLINE Vector mulps(Vector a, Vector b) {
    __asm__ volatile("mulps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE_INLINE Vector addss(Vector a, Vector b) {
    __asm__ volatile("addss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE_INLINE Vector mulss(Vector a, Vector b) {
    __asm__ volatile("mulss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE_INLINE void store_scalar(void* p, Vector v) {
    __asm__ volatile("movss %1,%0" : "=m"(*reinterpret_cast<Bytes4*>(p)) : "x"(v) : "memory");
}
SSE_INLINE void store_low(void* p, Vector v) {
    __asm__ volatile("movlps %1,%0" : "=m"(*reinterpret_cast<Bytes8*>(p)) : "x"(v) : "memory");
}
SSE_INLINE void store_high(void* p, Vector v) {
    __asm__ volatile("movhps %1,%0" : "=m"(*reinterpret_cast<Bytes8*>(p)) : "x"(v) : "memory");
}
SSE_INLINE void store_block(void* p, Vector v) {
    __asm__ volatile("movups %1,%0" : "=m"(*reinterpret_cast<Bytes16*>(p)) : "x"(v) : "memory");
}
} // namespace
extern "C" __attribute__((target("sse"))) void*
recovered_sse_00680b15(const uint32_t* arguments, const unsigned char* incoming) {
    const Vector v000 = scalar(reinterpret_cast<const void*>(
        reinterpret_cast<uintptr_t>(arguments) + 20)); // original00680b1a; defined lanesf
    const Vector v001 = block(incoming + 16);          // original00680b15; defined lanesf
    const Vector v002 = copy_low(v001, v000);          // original00680b1f; defined lanesf
    const Vector v003 = mulss(v002, v000);             // original00680b23; defined lanesf
    const Vector v004 = block(incoming + 32);          // original00680b15; defined lanesf
    const Vector v005 = copy_low(v004, v000);          // original00680b27; defined lanesf
    const Vector v006 = shuffle<0x00>(v000, v000);     // original00680b2b; defined lanesf
    const Vector v007 = mulss(v005, v003);             // original00680b2f; defined lanesf
    const Vector v008 = shuffle<0x00>(v003, v003);     // original00680b33; defined lanesf
    const Vector v009 = mulps(v006, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          96));    // original00680b37; defined lanesf
    const Vector v010 = shuffle<0x00>(v007, v007); // original00680b3e; defined lanesf
    const Vector v011 = mulps(v008, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          80)); // original00680b42; defined lanesf
    const Vector v012 = addps(v009, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          112)); // original00680b49; defined lanesf
    const Vector v013 = mulps(v010, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          64));    // original00680b50; defined lanesf
    const Vector v014 = addps(v012, v011);         // original00680b57; defined lanesf
    const Vector v015 = addps(v014, v013);         // original00680b5a; defined lanesf
    const uint32_t p000 = word(arguments + 1);     // original00680b5d
    const uint32_t p001 = word(arguments + 2);     // original00680b60
    const uint32_t p002 = word(arguments + 3);     // original00680b63
    const Vector v016 = shuffle<0x55>(v015, v015); // original00680b69; defined lanesf
    const Vector v017 = shuffle<0xaa>(v015, v015); // original00680b70; defined lanesf
    const Vector v018 = shuffle<0xff>(v015, v015); // original00680b77; defined lanesf
    const Vector v019 = shuffle<0x00>(v015, v015); // original00680b7b; defined lanesf
    const Vector v020 =
        scalar(reinterpret_cast<const void*>(p000 + 8u)); // original00680b7f; defined lanesf
    const Vector v021 =
        high(v020, reinterpret_cast<const void*>(p000 + 0u)); // original00680b84; defined lanesf
    const uint32_t p003 = word(arguments + 4);                // original00680b87
    const Vector v022 = mulps(v021, v019);                    // original00680b8a; defined lanesf
    const Vector v023 =
        scalar(reinterpret_cast<const void*>(p001 + 8u)); // original00680b8d; defined lanesf
    const Vector v024 =
        high(v023, reinterpret_cast<const void*>(p001 + 0u)); // original00680b92; defined lanesf
    const Vector v025 = mulps(v024, v016);                    // original00680b95; defined lanesf
    const Vector v026 =
        scalar(reinterpret_cast<const void*>(p002 + 8u)); // original00680b98; defined lanesf
    const Vector v027 =
        high(v026, reinterpret_cast<const void*>(p002 + 0u)); // original00680b9d; defined lanesf
    const Vector v028 = addps(v022, v025);                    // original00680ba0; defined lanesf
    const Vector v029 = mulps(v027, v017);                    // original00680ba3; defined lanesf
    const Vector v030 = addps(v028, v029);                    // original00680ba6; defined lanesf
    const Vector v031 =
        scalar(reinterpret_cast<const void*>(p003 + 8u)); // original00680ba9; defined lanesf
    const Vector v032 =
        high(v031, reinterpret_cast<const void*>(p003 + 0u)); // original00680bae; defined lanesf
    const uint32_t p004 = word(arguments + 0);                // original00680bb1
    const Vector v033 = mulps(v032, v018);                    // original00680bb4; defined lanesf
    const Vector v034 = addps(v030, v033);                    // original00680bb7; defined lanesf
    store_high(const_cast<void*>(reinterpret_cast<const void*>(p004 + 0u)),
               v034); // original00680bba
    store_scalar(const_cast<void*>(reinterpret_cast<const void*>(p004 + 8u)),
                 v034);                        // original00680bbd
    const uint32_t p005 = word(arguments + 0); // original00680bc2
    return reinterpret_cast<void*>(p005);
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_00680b15(void*, const void*, const void*, const void*, const void*, uint32_t) {
    __asm__ volatile(
        "subl $128,%esp\n\tmovups %xmm0,0(%esp)\n\tmovups %xmm1,16(%esp)\n\tmovups %xmm2,32(%esp)\n\tmovups %xmm3,48(%esp)\n\tmovups %xmm4,64(%esp)\n\tmovups %xmm5,80(%esp)\n\tmovups %xmm6,96(%esp)\n\tmovups %xmm7,112(%esp)\n\tmovl %esp,%edx\n\tleal 132(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcalll _recovered_sse_00680b15\n\taddl $136,%esp\n\tretl $24");
}

extern "C" __attribute__((target("sse"))) void*
recovered_sse_00680bc9(const uint32_t* arguments, const unsigned char* incoming) {
    const Vector v000 = scalar(reinterpret_cast<const void*>(
        reinterpret_cast<uintptr_t>(arguments) + 20)); // original00680bce; defined lanesf
    const Vector v001 = block(incoming + 16);          // original00680bc9; defined lanesf
    const Vector v002 = copy_low(v001, v000);          // original00680bd3; defined lanesf
    const Vector v003 = mulss(v002, v000);             // original00680bd7; defined lanesf
    const Vector v004 = block(incoming + 32);          // original00680bc9; defined lanesf
    const Vector v005 = copy_low(v004, v000);          // original00680bdb; defined lanesf
    const Vector v006 = shuffle<0x00>(v000, v000);     // original00680bdf; defined lanesf
    const Vector v007 = mulss(v005, v003);             // original00680be3; defined lanesf
    const Vector v008 = shuffle<0x00>(v003, v003);     // original00680be7; defined lanesf
    const Vector v009 = mulps(v006, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          96));    // original00680beb; defined lanesf
    const Vector v010 = shuffle<0x00>(v007, v007); // original00680bf2; defined lanesf
    const Vector v011 = mulps(v008, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          80)); // original00680bf6; defined lanesf
    const Vector v012 = addps(v009, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          112)); // original00680bfd; defined lanesf
    const Vector v013 = mulps(v010, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          64));    // original00680c04; defined lanesf
    const Vector v014 = addps(v012, v011);         // original00680c0b; defined lanesf
    const Vector v015 = addps(v014, v013);         // original00680c0e; defined lanesf
    const uint32_t p000 = word(arguments + 1);     // original00680c11
    const uint32_t p001 = word(arguments + 2);     // original00680c14
    const uint32_t p002 = word(arguments + 3);     // original00680c17
    const Vector v016 = shuffle<0xfa>(v015, v015); // original00680c1d; defined lanesf
    const Vector v017 = shuffle<0x50>(v015, v015); // original00680c21; defined lanesf
    const Vector v018 = block(incoming + 64);      // original00680bc9; defined lanesf
    const Vector v019 =
        low(v018, reinterpret_cast<const void*>(p000 + 0u)); // original00680c25; defined lanesf
    const Vector v020 =
        high(v019, reinterpret_cast<const void*>(p001 + 0u)); // original00680c28; defined lanesf
    const uint32_t p003 = word(arguments + 4);                // original00680c2b
    const Vector v021 = mulps(v020, v017);                    // original00680c2e; defined lanesf
    const Vector v022 = block(incoming + 96);                 // original00680bc9; defined lanesf
    const Vector v023 =
        low(v022, reinterpret_cast<const void*>(p002 + 0u)); // original00680c31; defined lanesf
    const Vector v024 =
        high(v023, reinterpret_cast<const void*>(p003 + 0u)); // original00680c34; defined lanesf
    const Vector v025 = mulps(v024, v016);                    // original00680c37; defined lanesf
    const Vector v026 = addps(v021, v025);                    // original00680c3a; defined lanesf
    const Vector v027 = high_to_low(v025, v026);              // original00680c3d; defined lanesf
    const Vector v028 = addps(v026, v027);                    // original00680c40; defined lanesf
    const uint32_t p004 = word(arguments + 0);                // original00680c43
    store_low(const_cast<void*>(reinterpret_cast<const void*>(p004 + 0u)),
              v028);                           // original00680c46
    const uint32_t p005 = word(arguments + 0); // original00680c49
    return reinterpret_cast<void*>(p005);
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_00680bc9(void*, const void*, const void*, const void*, const void*, uint32_t) {
    __asm__ volatile(
        "subl $128,%esp\n\tmovups %xmm0,0(%esp)\n\tmovups %xmm1,16(%esp)\n\tmovups %xmm2,32(%esp)\n\tmovups %xmm3,48(%esp)\n\tmovups %xmm4,64(%esp)\n\tmovups %xmm5,80(%esp)\n\tmovups %xmm6,96(%esp)\n\tmovups %xmm7,112(%esp)\n\tmovl %esp,%edx\n\tleal 132(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcalll _recovered_sse_00680bc9\n\taddl $136,%esp\n\tretl $24");
}

extern "C" __attribute__((target("sse"))) void*
recovered_sse_00680c50(const uint32_t* arguments, const unsigned char* incoming) {
    const Vector v000 = scalar(reinterpret_cast<const void*>(
        reinterpret_cast<uintptr_t>(arguments) + 20)); // original00680c55; defined lanesf
    const Vector v001 = block(incoming + 16);          // original00680c50; defined lanesf
    const Vector v002 = copy_low(v001, v000);          // original00680c5a; defined lanesf
    const Vector v003 = mulss(v002, v000);             // original00680c5e; defined lanesf
    const Vector v004 = block(incoming + 32);          // original00680c50; defined lanesf
    const Vector v005 = copy_low(v004, v000);          // original00680c62; defined lanesf
    const Vector v006 = shuffle<0x00>(v000, v000);     // original00680c66; defined lanesf
    const Vector v007 = mulss(v005, v003);             // original00680c6a; defined lanesf
    const Vector v008 = shuffle<0x00>(v003, v003);     // original00680c6e; defined lanesf
    const Vector v009 = mulps(v006, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          96));    // original00680c72; defined lanesf
    const Vector v010 = shuffle<0x00>(v007, v007); // original00680c79; defined lanesf
    const Vector v011 = mulps(v008, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          80)); // original00680c7d; defined lanesf
    const Vector v012 = addps(v009, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          112)); // original00680c84; defined lanesf
    const Vector v013 = mulps(v010, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          64));    // original00680c8b; defined lanesf
    const Vector v014 = addps(v012, v011);         // original00680c92; defined lanesf
    const Vector v015 = addps(v014, v013);         // original00680c95; defined lanesf
    const uint32_t p000 = word(arguments + 1);     // original00680c98
    const Vector v016 = zero();                    // original00680c9b; defined lanesf
    const uint32_t p001 = word(arguments + 2);     // original00680c9e
    const uint32_t p002 = word(arguments + 3);     // original00680ca1
    const Vector v017 = shuffle<0x55>(v015, v015); // original00680ca7; defined lanesf
    const Vector v018 = shuffle<0xaa>(v015, v015); // original00680cae; defined lanesf
    const Vector v019 = shuffle<0xff>(v015, v015); // original00680cb5; defined lanesf
    const Vector v020 = zero();                    // original00680cb9; defined lanesf
    const Vector v021 = shuffle<0x00>(v015, v015); // original00680cbc; defined lanesf
    const Vector v022 =
        block(reinterpret_cast<const void*>(p000 + 0u)); // original00680cc0; defined lanesf
    const uint32_t p003 = word(arguments + 4);           // original00680cc3
    const Vector v023 = mulps(v022, v021);               // original00680cc6; defined lanesf
    const Vector v024 = zero();                          // original00680cc9; defined lanesf
    const Vector v025 =
        block(reinterpret_cast<const void*>(p001 + 0u)); // original00680ccc; defined lanesf
    const Vector v026 = mulps(v025, v017);               // original00680ccf; defined lanesf
    const Vector v027 = zero();                          // original00680cd2; defined lanesf
    const Vector v028 =
        block(reinterpret_cast<const void*>(p002 + 0u)); // original00680cd5; defined lanesf
    const Vector v029 = addps(v023, v026);               // original00680cd8; defined lanesf
    const Vector v030 = mulps(v028, v018);               // original00680cdb; defined lanesf
    const Vector v031 = addps(v029, v030);               // original00680cde; defined lanesf
    const Vector v032 =
        block(reinterpret_cast<const void*>(p003 + 0u)); // original00680ce1; defined lanesf
    const uint32_t p004 = word(arguments + 0);           // original00680ce4
    const Vector v033 = mulps(v032, v019);               // original00680ce7; defined lanesf
    const Vector v034 = addps(v031, v033);               // original00680cea; defined lanesf
    store_block(const_cast<void*>(reinterpret_cast<const void*>(p004 + 0u)),
                v034);                         // original00680ced
    const uint32_t p005 = word(arguments + 0); // original00680cf0
    return reinterpret_cast<void*>(p005);
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_00680c50(void*, const void*, const void*, const void*, const void*, uint32_t) {
    __asm__ volatile(
        "subl $128,%esp\n\tmovups %xmm0,0(%esp)\n\tmovups %xmm1,16(%esp)\n\tmovups %xmm2,32(%esp)\n\tmovups %xmm3,48(%esp)\n\tmovups %xmm4,64(%esp)\n\tmovups %xmm5,80(%esp)\n\tmovups %xmm6,96(%esp)\n\tmovups %xmm7,112(%esp)\n\tmovl %esp,%edx\n\tleal 132(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcalll _recovered_sse_00680c50\n\taddl $136,%esp\n\tretl $24");
}

extern "C" __attribute__((target("sse"))) void*
recovered_sse_00680cf7(const uint32_t* arguments, const unsigned char* incoming) {
    const Vector v000 = scalar(reinterpret_cast<const void*>(
        reinterpret_cast<uintptr_t>(arguments) + 20)); // original00680cfc; defined lanesf
    const Vector v001 = block(incoming + 16);          // original00680cf7; defined lanesf
    const Vector v002 = copy_low(v001, v000);          // original00680d01; defined lanesf
    const Vector v003 = mulss(v002, v000);             // original00680d05; defined lanesf
    const Vector v004 = block(incoming + 32);          // original00680cf7; defined lanesf
    const Vector v005 = copy_low(v004, v000);          // original00680d09; defined lanesf
    const Vector v006 = shuffle<0x00>(v000, v000);     // original00680d0d; defined lanesf
    const Vector v007 = mulss(v005, v003);             // original00680d11; defined lanesf
    const Vector v008 = shuffle<0x00>(v003, v003);     // original00680d15; defined lanesf
    const Vector v009 = mulps(v006, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          32));    // original00680d19; defined lanesf
    const Vector v010 = shuffle<0x00>(v007, v007); // original00680d20; defined lanesf
    const Vector v011 = mulps(v008, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          16)); // original00680d24; defined lanesf
    const Vector v012 = addss(v009, scalar(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                           48)); // original00680d2b; defined lanesf
    const Vector v013 = mulps(v010, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          0));     // original00680d33; defined lanesf
    const Vector v014 = addps(v012, v011);         // original00680d3a; defined lanesf
    const Vector v015 = addps(v014, v013);         // original00680d3d; defined lanesf
    const uint32_t p000 = word(arguments + 1);     // original00680d40
    const uint32_t p001 = word(arguments + 2);     // original00680d43
    const uint32_t p002 = word(arguments + 3);     // original00680d46
    const Vector v016 = shuffle<0x55>(v015, v015); // original00680d4c; defined lanesf
    const Vector v017 = shuffle<0xaa>(v015, v015); // original00680d53; defined lanesf
    const Vector v018 = shuffle<0xff>(v015, v015); // original00680d5a; defined lanesf
    const Vector v019 = shuffle<0x00>(v015, v015); // original00680d5e; defined lanesf
    const Vector v020 =
        scalar(reinterpret_cast<const void*>(p000 + 8u)); // original00680d62; defined lanesf
    const Vector v021 =
        high(v020, reinterpret_cast<const void*>(p000 + 0u)); // original00680d67; defined lanesf
    const uint32_t p003 = word(arguments + 4);                // original00680d6a
    const Vector v022 = mulps(v021, v019);                    // original00680d6d; defined lanesf
    const Vector v023 =
        scalar(reinterpret_cast<const void*>(p001 + 8u)); // original00680d70; defined lanesf
    const Vector v024 =
        high(v023, reinterpret_cast<const void*>(p001 + 0u)); // original00680d75; defined lanesf
    const Vector v025 = mulps(v024, v016);                    // original00680d78; defined lanesf
    const Vector v026 =
        scalar(reinterpret_cast<const void*>(p002 + 8u)); // original00680d7b; defined lanesf
    const Vector v027 =
        high(v026, reinterpret_cast<const void*>(p002 + 0u)); // original00680d80; defined lanesf
    const Vector v028 = addps(v022, v025);                    // original00680d83; defined lanesf
    const Vector v029 = mulps(v027, v017);                    // original00680d86; defined lanesf
    const Vector v030 = addps(v028, v029);                    // original00680d89; defined lanesf
    const Vector v031 =
        scalar(reinterpret_cast<const void*>(p003 + 8u)); // original00680d8c; defined lanesf
    const Vector v032 =
        high(v031, reinterpret_cast<const void*>(p003 + 0u)); // original00680d91; defined lanesf
    const uint32_t p004 = word(arguments + 0);                // original00680d94
    const Vector v033 = mulps(v032, v018);                    // original00680d97; defined lanesf
    const Vector v034 = addps(v030, v033);                    // original00680d9a; defined lanesf
    store_high(const_cast<void*>(reinterpret_cast<const void*>(p004 + 0u)),
               v034); // original00680d9d
    store_scalar(const_cast<void*>(reinterpret_cast<const void*>(p004 + 8u)),
                 v034);                        // original00680da0
    const uint32_t p005 = word(arguments + 0); // original00680da5
    return reinterpret_cast<void*>(p005);
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_00680cf7(void*, const void*, const void*, const void*, const void*, uint32_t) {
    __asm__ volatile(
        "subl $128,%esp\n\tmovups %xmm0,0(%esp)\n\tmovups %xmm1,16(%esp)\n\tmovups %xmm2,32(%esp)\n\tmovups %xmm3,48(%esp)\n\tmovups %xmm4,64(%esp)\n\tmovups %xmm5,80(%esp)\n\tmovups %xmm6,96(%esp)\n\tmovups %xmm7,112(%esp)\n\tmovl %esp,%edx\n\tleal 132(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcalll _recovered_sse_00680cf7\n\taddl $136,%esp\n\tretl $24");
}

extern "C" __attribute__((target("sse"))) void*
recovered_sse_00680dac(const uint32_t* arguments, const unsigned char* incoming) {
    const Vector v000 = scalar(reinterpret_cast<const void*>(
        reinterpret_cast<uintptr_t>(arguments) + 20)); // original00680db1; defined lanesf
    const Vector v001 = block(incoming + 16);          // original00680dac; defined lanesf
    const Vector v002 = copy_low(v001, v000);          // original00680db6; defined lanesf
    const Vector v003 = mulss(v002, v000);             // original00680dba; defined lanesf
    const Vector v004 = block(incoming + 32);          // original00680dac; defined lanesf
    const Vector v005 = copy_low(v004, v000);          // original00680dbe; defined lanesf
    const Vector v006 = shuffle<0x00>(v000, v000);     // original00680dc2; defined lanesf
    const Vector v007 = mulss(v005, v003);             // original00680dc6; defined lanesf
    const Vector v008 = shuffle<0x00>(v003, v003);     // original00680dca; defined lanesf
    const Vector v009 = mulps(v006, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          32));    // original00680dce; defined lanesf
    const Vector v010 = shuffle<0x00>(v007, v007); // original00680dd5; defined lanesf
    const Vector v011 = mulps(v008, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          16)); // original00680dd9; defined lanesf
    const Vector v012 = addss(v009, scalar(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                           48)); // original00680de0; defined lanesf
    const Vector v013 = mulps(v010, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          0));     // original00680de8; defined lanesf
    const Vector v014 = addps(v012, v011);         // original00680def; defined lanesf
    const Vector v015 = addps(v014, v013);         // original00680df2; defined lanesf
    const uint32_t p000 = word(arguments + 1);     // original00680df5
    const Vector v016 = shuffle<0x55>(v015, v015); // original00680dfb; defined lanesf
    const uint32_t p001 = word(arguments + 2);     // original00680e02
    const Vector v017 = shuffle<0xaa>(v015, v015); // original00680e05; defined lanesf
    const Vector v018 = shuffle<0xff>(v015, v015); // original00680e0c; defined lanesf
    const uint32_t p002 = word(arguments + 3);     // original00680e10
    const Vector v019 = shuffle<0x00>(v015, v015); // original00680e13; defined lanesf
    const Vector v020 =
        block(reinterpret_cast<const void*>(p000 + 0u)); // original00680e17; defined lanesf
    const uint32_t p003 = word(arguments + 4);           // original00680e1a
    const Vector v021 = mulps(v020, v019);               // original00680e1d; defined lanesf
    const Vector v022 =
        block(reinterpret_cast<const void*>(p001 + 0u)); // original00680e20; defined lanesf
    const Vector v023 = mulps(v022, v016);               // original00680e23; defined lanesf
    const Vector v024 =
        block(reinterpret_cast<const void*>(p002 + 0u)); // original00680e26; defined lanesf
    const Vector v025 = addps(v021, v023);               // original00680e29; defined lanesf
    const Vector v026 = mulps(v024, v017);               // original00680e2c; defined lanesf
    const Vector v027 = addps(v025, v026);               // original00680e2f; defined lanesf
    const Vector v028 =
        block(reinterpret_cast<const void*>(p003 + 0u)); // original00680e32; defined lanesf
    const uint32_t p004 = word(arguments + 0);           // original00680e35
    const Vector v029 = mulps(v028, v018);               // original00680e38; defined lanesf
    const Vector v030 = addps(v027, v029);               // original00680e3b; defined lanesf
    store_block(const_cast<void*>(reinterpret_cast<const void*>(p004 + 0u)),
                v030);                         // original00680e3e
    const uint32_t p005 = word(arguments + 0); // original00680e41
    return reinterpret_cast<void*>(p005);
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_00680dac(void*, const void*, const void*, const void*, const void*, uint32_t) {
    __asm__ volatile(
        "subl $128,%esp\n\tmovups %xmm0,0(%esp)\n\tmovups %xmm1,16(%esp)\n\tmovups %xmm2,32(%esp)\n\tmovups %xmm3,48(%esp)\n\tmovups %xmm4,64(%esp)\n\tmovups %xmm5,80(%esp)\n\tmovups %xmm6,96(%esp)\n\tmovups %xmm7,112(%esp)\n\tmovl %esp,%edx\n\tleal 132(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcalll _recovered_sse_00680dac\n\taddl $136,%esp\n\tretl $24");
}

extern "C" __attribute__((target("sse"))) void*
recovered_sse_00680e48(const uint32_t* arguments, const unsigned char* incoming) {
    const Vector v000 = scalar(reinterpret_cast<const void*>(
        reinterpret_cast<uintptr_t>(arguments) + 20)); // original00680e4d; defined lanesf
    const Vector v001 = block(incoming + 16);          // original00680e48; defined lanesf
    const Vector v002 = copy_low(v001, v000);          // original00680e52; defined lanesf
    const Vector v003 = mulss(v002, v000);             // original00680e56; defined lanesf
    const Vector v004 = block(incoming + 32);          // original00680e48; defined lanesf
    const Vector v005 = copy_low(v004, v000);          // original00680e5a; defined lanesf
    const Vector v006 = shuffle<0x00>(v000, v000);     // original00680e5e; defined lanesf
    const Vector v007 = mulss(v005, v003);             // original00680e62; defined lanesf
    const Vector v008 = shuffle<0x00>(v003, v003);     // original00680e66; defined lanesf
    const Vector v009 = mulps(v006, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          32));    // original00680e6a; defined lanesf
    const Vector v010 = shuffle<0x00>(v007, v007); // original00680e71; defined lanesf
    const Vector v011 = mulps(v008, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          16)); // original00680e75; defined lanesf
    const Vector v012 = addss(v009, scalar(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                           48)); // original00680e7c; defined lanesf
    const Vector v013 = mulps(v010, block(reinterpret_cast<const unsigned char*>(dat_00717550) +
                                          0));     // original00680e84; defined lanesf
    const Vector v014 = addps(v012, v011);         // original00680e8b; defined lanesf
    const Vector v015 = addps(v014, v013);         // original00680e8e; defined lanesf
    const uint32_t p000 = word(arguments + 1);     // original00680e91
    const Vector v016 = shuffle<0xfa>(v015, v015); // original00680e97; defined lanesf
    const Vector v017 = shuffle<0x50>(v015, v015); // original00680e9b; defined lanesf
    const uint32_t p001 = word(arguments + 2);     // original00680e9f
    const uint32_t p002 = word(arguments + 3);     // original00680ea2
    const Vector v018 = block(incoming + 64);      // original00680e48; defined lanesf
    const Vector v019 =
        low(v018, reinterpret_cast<const void*>(p000 + 0u)); // original00680ea5; defined lanesf
    const Vector v020 =
        high(v019, reinterpret_cast<const void*>(p001 + 0u)); // original00680ea8; defined lanesf
    const uint32_t p003 = word(arguments + 4);                // original00680eab
    const Vector v021 = mulps(v020, v017);                    // original00680eae; defined lanesf
    const Vector v022 = block(incoming + 96);                 // original00680e48; defined lanesf
    const Vector v023 =
        low(v022, reinterpret_cast<const void*>(p002 + 0u)); // original00680eb1; defined lanesf
    const Vector v024 =
        high(v023, reinterpret_cast<const void*>(p003 + 0u)); // original00680eb4; defined lanesf
    const Vector v025 = mulps(v024, v016);                    // original00680eb7; defined lanesf
    const uint32_t p004 = word(arguments + 0);                // original00680eba
    const Vector v026 = addps(v021, v025);                    // original00680ebd; defined lanesf
    const Vector v027 = block(incoming + 48);                 // original00680e48; defined lanesf
    const Vector v028 = high_to_low(v027, v026);              // original00680ec0; defined lanesf
    const Vector v029 = addps(v026, v028);                    // original00680ec3; defined lanesf
    store_low(const_cast<void*>(reinterpret_cast<const void*>(p004 + 0u)),
              v029);                           // original00680ec6
    const uint32_t p005 = word(arguments + 0); // original00680ec9
    return reinterpret_cast<void*>(p005);
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_00680e48(void*, const void*, const void*, const void*, const void*, uint32_t) {
    __asm__ volatile(
        "subl $128,%esp\n\tmovups %xmm0,0(%esp)\n\tmovups %xmm1,16(%esp)\n\tmovups %xmm2,32(%esp)\n\tmovups %xmm3,48(%esp)\n\tmovups %xmm4,64(%esp)\n\tmovups %xmm5,80(%esp)\n\tmovups %xmm6,96(%esp)\n\tmovups %xmm7,112(%esp)\n\tmovl %esp,%edx\n\tleal 132(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcalll _recovered_sse_00680e48\n\taddl $136,%esp\n\tretl $24");
}

extern "C" __attribute__((target("sse"))) void*
recovered_sse_00680ed0(const uint32_t* arguments, const unsigned char* incoming) {
    const Vector v000 = scalar(reinterpret_cast<const void*>(
        reinterpret_cast<uintptr_t>(arguments) + 16)); // original00680ed5; defined lanesf
    const uint32_t p000 = word(arguments + 1);         // original00680eda
    const Vector v001 = shuffle<0x00>(v000, v000);     // original00680edd; defined lanesf
    const Vector v002 =
        scalar(reinterpret_cast<const void*>(p000 + 8u)); // original00680ee1; defined lanesf
    const uint32_t p001 = word(arguments + 2);            // original00680ee6
    const Vector v003 =
        high(v002, reinterpret_cast<const void*>(p000 + 0u)); // original00680ee9; defined lanesf
    const Vector v004 = scalar(reinterpret_cast<const void*>(
        reinterpret_cast<uintptr_t>(arguments) + 20)); // original00680eec; defined lanesf
    const Vector v005 =
        scalar(reinterpret_cast<const void*>(p001 + 8u)); // original00680ef1; defined lanesf
    const Vector v006 =
        high(v005, reinterpret_cast<const void*>(p001 + 0u)); // original00680ef6; defined lanesf
    const Vector v007 = shuffle<0x00>(v004, v004);            // original00680ef9; defined lanesf
    const uint32_t p002 = word(arguments + 3);                // original00680efd
    const Vector v008 = subps(v006, v003);                    // original00680f00; defined lanesf
    const Vector v009 =
        scalar(reinterpret_cast<const void*>(p002 + 8u)); // original00680f03; defined lanesf
    const Vector v010 =
        high(v009, reinterpret_cast<const void*>(p002 + 0u)); // original00680f08; defined lanesf
    const Vector v011 = mulps(v008, v001);                    // original00680f0b; defined lanesf
    const Vector v012 = subps(v010, v003);                    // original00680f0e; defined lanesf
    const uint32_t p003 = word(arguments + 0);                // original00680f11
    const Vector v013 = addps(v011, v003);                    // original00680f14; defined lanesf
    const Vector v014 = mulps(v012, v007);                    // original00680f17; defined lanesf
    const Vector v015 = addps(v013, v014);                    // original00680f1a; defined lanesf
    store_scalar(const_cast<void*>(reinterpret_cast<const void*>(p003 + 8u)),
                 v015); // original00680f1d
    store_high(const_cast<void*>(reinterpret_cast<const void*>(p003 + 0u)),
               v015);                          // original00680f22
    const uint32_t p004 = word(arguments + 0); // original00680f25
    return reinterpret_cast<void*>(p004);
}
extern "C" __attribute__((naked)) float* __attribute__((stdcall))
FUN_00680ed0(float*, const volatile float*, const volatile float*, const volatile float*, float,
             float) {
    __asm__ volatile(
        "subl $128,%esp\n\tmovups %xmm0,0(%esp)\n\tmovups %xmm1,16(%esp)\n\tmovups %xmm2,32(%esp)\n\tmovups %xmm3,48(%esp)\n\tmovups %xmm4,64(%esp)\n\tmovups %xmm5,80(%esp)\n\tmovups %xmm6,96(%esp)\n\tmovups %xmm7,112(%esp)\n\tmovl %esp,%edx\n\tleal 132(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcalll _recovered_sse_00680ed0\n\taddl $136,%esp\n\tretl $24");
}

extern "C" __attribute__((target("sse"))) void*
recovered_sse_00680f2c(const uint32_t* arguments, const unsigned char* incoming) {
    const Vector v000 = scalar(reinterpret_cast<const void*>(
        reinterpret_cast<uintptr_t>(arguments) + 16)); // original00680f31; defined lanesf
    const uint32_t p000 = word(arguments + 1);         // original00680f36
    const Vector v001 = shuffle<0x00>(v000, v000);     // original00680f39; defined lanesf
    const uint32_t p001 = word(arguments + 2);         // original00680f3d
    const Vector v002 =
        block(reinterpret_cast<const void*>(p000 + 0u)); // original00680f40; defined lanesf
    const Vector v003 = scalar(reinterpret_cast<const void*>(
        reinterpret_cast<uintptr_t>(arguments) + 20)); // original00680f43; defined lanesf
    const Vector v004 =
        block(reinterpret_cast<const void*>(p001 + 0u)); // original00680f48; defined lanesf
    const Vector v005 = shuffle<0x00>(v003, v003);       // original00680f4b; defined lanesf
    const uint32_t p002 = word(arguments + 3);           // original00680f4f
    const Vector v006 = subps(v004, v002);               // original00680f52; defined lanesf
    const Vector v007 =
        block(reinterpret_cast<const void*>(p002 + 0u)); // original00680f55; defined lanesf
    const Vector v008 = mulps(v006, v001);               // original00680f58; defined lanesf
    const Vector v009 = subps(v007, v002);               // original00680f5b; defined lanesf
    const uint32_t p003 = word(arguments + 0);           // original00680f5e
    const Vector v010 = addps(v008, v002);               // original00680f61; defined lanesf
    const Vector v011 = mulps(v009, v005);               // original00680f64; defined lanesf
    const Vector v012 = addps(v010, v011);               // original00680f67; defined lanesf
    store_block(const_cast<void*>(reinterpret_cast<const void*>(p003 + 0u)),
                v012);                         // original00680f6a
    const uint32_t p004 = word(arguments + 0); // original00680f6d
    return reinterpret_cast<void*>(p004);
}
extern "C" __attribute__((naked)) float* __attribute__((stdcall))
FUN_00680f2c(float*, const volatile float*, const volatile float*, const volatile float*, float,
             float) {
    __asm__ volatile(
        "subl $128,%esp\n\tmovups %xmm0,0(%esp)\n\tmovups %xmm1,16(%esp)\n\tmovups %xmm2,32(%esp)\n\tmovups %xmm3,48(%esp)\n\tmovups %xmm4,64(%esp)\n\tmovups %xmm5,80(%esp)\n\tmovups %xmm6,96(%esp)\n\tmovups %xmm7,112(%esp)\n\tmovl %esp,%edx\n\tleal 132(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcalll _recovered_sse_00680f2c\n\taddl $136,%esp\n\tretl $24");
}

extern "C" __attribute__((target("sse"))) void*
recovered_sse_00680f74(const uint32_t* arguments, const unsigned char* incoming) {
    const Vector v000 = zero(); // original00680f79; defined lanesf
    const Vector v001 = scalar(reinterpret_cast<const void*>(
        reinterpret_cast<uintptr_t>(arguments) + 16)); // original00680f7c; defined lanesf
    const uint32_t p000 = word(arguments + 1);         // original00680f81
    const Vector v002 = shuffle<0x00>(v001, v001);     // original00680f84; defined lanesf
    const Vector v003 = zero();                        // original00680f88; defined lanesf
    const uint32_t p001 = word(arguments + 2);         // original00680f8b
    const Vector v004 =
        high(v000, reinterpret_cast<const void*>(p000 + 0u)); // original00680f8e; defined lanesf
    const Vector v005 = scalar(reinterpret_cast<const void*>(
        reinterpret_cast<uintptr_t>(arguments) + 20)); // original00680f91; defined lanesf
    const Vector v006 =
        high(v003, reinterpret_cast<const void*>(p001 + 0u)); // original00680f96; defined lanesf
    const Vector v007 = zero();                               // original00680f99; defined lanesf
    const Vector v008 = shuffle<0x00>(v005, v005);            // original00680f9c; defined lanesf
    const uint32_t p002 = word(arguments + 3);                // original00680fa0
    const Vector v009 = subps(v006, v004);                    // original00680fa3; defined lanesf
    const Vector v010 =
        high(v007, reinterpret_cast<const void*>(p002 + 0u)); // original00680fa6; defined lanesf
    const Vector v011 = mulps(v009, v002);                    // original00680fa9; defined lanesf
    const Vector v012 = subps(v010, v004);                    // original00680fac; defined lanesf
    const uint32_t p003 = word(arguments + 0);                // original00680faf
    const Vector v013 = addps(v011, v004);                    // original00680fb2; defined lanesf
    const Vector v014 = mulps(v012, v008);                    // original00680fb5; defined lanesf
    const Vector v015 = addps(v013, v014);                    // original00680fb8; defined lanesf
    store_high(const_cast<void*>(reinterpret_cast<const void*>(p003 + 0u)),
               v015);                          // original00680fbb
    const uint32_t p004 = word(arguments + 0); // original00680fbe
    return reinterpret_cast<void*>(p004);
}
extern "C" __attribute__((naked)) float* __attribute__((stdcall))
FUN_00680f74(float*, const volatile float*, const volatile float*, const volatile float*, float,
             float) {
    __asm__ volatile(
        "subl $128,%esp\n\tmovups %xmm0,0(%esp)\n\tmovups %xmm1,16(%esp)\n\tmovups %xmm2,32(%esp)\n\tmovups %xmm3,48(%esp)\n\tmovups %xmm4,64(%esp)\n\tmovups %xmm5,80(%esp)\n\tmovups %xmm6,96(%esp)\n\tmovups %xmm7,112(%esp)\n\tmovl %esp,%edx\n\tleal 132(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcalll _recovered_sse_00680f74\n\taddl $136,%esp\n\tretl $24");
}
