#include "graphics/render_transform_amd.h"
namespace {
using Packed = long long __attribute__((vector_size(8)));
struct PairBytes {
    unsigned char bytes[8];
};
#define MMX_INLINE __attribute__((target("mmx,3dnow"), always_inline)) inline
MMX_INLINE Packed load_pair(const float* source) {
    Packed value;
    __asm__ __volatile__("movq %1,%0"
                         : "=y"(value)
                         : "m"(*reinterpret_cast<const PairBytes*>(source)));
    return value;
}
MMX_INLINE Packed load_scalar(const float* source) {
    Packed value;
    __asm__ __volatile__("movd %1,%0" : "=y"(value) : "m"(*source));
    return value;
}
MMX_INLINE void store_pair(float* target, Packed value) {
    __asm__ __volatile__("movq %1,%0" : "=m"(*reinterpret_cast<PairBytes*>(target)) : "y"(value));
}
MMX_INLINE void store_scalar(float* target, Packed value) {
    __asm__ __volatile__("movd %1,%0" : "=m"(*target) : "y"(value));
}
MMX_INLINE void media_empty() {
    __asm__ __volatile__("femms" ::
                             : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "st",
                               "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
                               "memory");
}
MMX_INLINE Packed punpckldq(Packed a, Packed b) {
    __asm__ __volatile__("punpckldq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed punpckhdq(Packed a, Packed b) {
    __asm__ __volatile__("punpckhdq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed pfmul(Packed a, Packed b) {
    __asm__ __volatile__("pfmul %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed pfadd(Packed a, Packed b) {
    __asm__ __volatile__("pfadd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
} // namespace
extern "C" __attribute__((target("mmx,3dnow"))) float* __attribute__((stdcall))
FUN_0068b03b(float* output, const float* vector, const float* matrix) {
    media_empty();                                                       // original0068b040
    const Packed packed_000 = load_pair(vector + 0);                     // original0068b04b
    const Packed packed_001 = punpckldq(packed_000, packed_000);         // original0068b051
    const Packed packed_002 = punpckhdq(packed_000, packed_000);         // original0068b054
    const Packed packed_003 = pfmul(packed_001, load_pair(matrix + 0));  // original0068b05a
    const Packed packed_004 = pfmul(packed_002, load_pair(matrix + 4));  // original0068b061
    const Packed packed_005 = pfadd(packed_003, load_pair(matrix + 12)); // original0068b066
    const Packed packed_006 = pfmul(packed_001, load_pair(matrix + 2));  // original0068b06b
    const Packed packed_007 = pfmul(packed_002, load_pair(matrix + 6));  // original0068b070
    const Packed packed_008 = pfadd(packed_005, packed_004);             // original0068b075
    const Packed packed_009 = pfadd(packed_006, load_pair(matrix + 14)); // original0068b079
    const Packed packed_010 = pfadd(packed_009, packed_007);             // original0068b07e
    store_pair(output + 0, packed_008);                                  // original0068b082
    store_pair(output + 2, packed_010);                                  // original0068b085
    media_empty();                                                       // original0068b089
    return output;
}

extern "C" __attribute__((target("mmx,3dnow"))) float* __attribute__((stdcall))
FUN_0068a264(float* output, const float* vector, const float* matrix) {
    media_empty();                                                       // original0068a269
    const Packed packed_000 = load_pair(vector + 0);                     // original0068a274
    const Packed packed_001 = punpckldq(packed_000, packed_000);         // original0068a27a
    const Packed packed_002 = punpckhdq(packed_000, packed_000);         // original0068a27d
    const Packed packed_003 = load_scalar(vector + 2);                   // original0068a280
    const Packed packed_004 = punpckldq(packed_003, packed_003);         // original0068a284
    const Packed packed_005 = pfmul(packed_001, load_pair(matrix + 0));  // original0068a28a
    const Packed packed_006 = pfmul(packed_002, load_pair(matrix + 4));  // original0068a291
    const Packed packed_007 = pfmul(packed_004, load_pair(matrix + 8));  // original0068a299
    const Packed packed_008 = pfadd(packed_005, load_pair(matrix + 12)); // original0068a29e
    const Packed packed_009 = pfmul(packed_001, load_pair(matrix + 2));  // original0068a2a3
    const Packed packed_010 = pfadd(packed_006, packed_007);             // original0068a2a8
    const Packed packed_011 = pfmul(packed_002, load_pair(matrix + 6));  // original0068a2ac
    const Packed packed_012 = pfmul(packed_004, load_pair(matrix + 10)); // original0068a2b1
    const Packed packed_013 = pfadd(packed_009, load_pair(matrix + 14)); // original0068a2b6
    const Packed packed_014 = pfadd(packed_008, packed_010);             // original0068a2bb
    const Packed packed_015 = pfadd(packed_011, packed_012);             // original0068a2bf
    const Packed packed_016 = pfadd(packed_013, packed_015);             // original0068a2c3
    store_pair(output + 0, packed_014);                                  // original0068a2c7
    store_pair(output + 2, packed_016);                                  // original0068a2ca
    media_empty();                                                       // original0068a2ce
    return output;
}

extern "C" __attribute__((target("mmx,3dnow"))) float* __attribute__((stdcall))
FUN_0068b302(float* output, const float* vector, const float* matrix) {
    media_empty();                                                       // original0068b307
    const Packed packed_000 = load_pair(vector + 0);                     // original0068b312
    const Packed packed_001 = punpckldq(packed_000, packed_000);         // original0068b318
    const Packed packed_002 = punpckhdq(packed_000, packed_000);         // original0068b31b
    const Packed packed_003 = load_pair(vector + 2);                     // original0068b31e
    const Packed packed_004 = punpckldq(packed_003, packed_003);         // original0068b325
    const Packed packed_005 = punpckhdq(packed_003, packed_003);         // original0068b328
    const Packed packed_006 = pfmul(packed_001, load_pair(matrix + 0));  // original0068b32e
    const Packed packed_007 = pfmul(packed_002, load_pair(matrix + 4));  // original0068b335
    const Packed packed_008 = pfmul(packed_004, load_pair(matrix + 8));  // original0068b33d
    const Packed packed_009 = pfmul(packed_005, load_pair(matrix + 12)); // original0068b345
    const Packed packed_010 = pfadd(packed_006, packed_007);             // original0068b34a
    const Packed packed_011 = pfmul(packed_001, load_pair(matrix + 2));  // original0068b34e
    const Packed packed_012 = pfadd(packed_008, packed_009);             // original0068b353
    const Packed packed_013 = pfmul(packed_002, load_pair(matrix + 6));  // original0068b357
    const Packed packed_014 = pfmul(packed_004, load_pair(matrix + 10)); // original0068b35c
    const Packed packed_015 = pfmul(packed_005, load_pair(matrix + 14)); // original0068b361
    const Packed packed_016 = pfadd(packed_010, packed_012);             // original0068b366
    const Packed packed_017 = pfadd(packed_011, packed_013);             // original0068b36a
    const Packed packed_018 = pfadd(packed_014, packed_015);             // original0068b36e
    const Packed packed_019 = pfadd(packed_017, packed_018);             // original0068b372
    store_pair(output + 0, packed_016);                                  // original0068b376
    store_pair(output + 2, packed_019);                                  // original0068b379
    media_empty();                                                       // original0068b37d
    return output;
}

extern "C" __attribute__((target("mmx,3dnow"))) float* __attribute__((stdcall))
FUN_0068b092(float* output, const float* vector, const float* matrix) {
    media_empty();                                                      // original0068b097
    const Packed packed_000 = load_pair(vector + 0);                    // original0068b0a2
    const Packed packed_001 = punpckldq(packed_000, packed_000);        // original0068b0a8
    const Packed packed_002 = punpckhdq(packed_000, packed_000);        // original0068b0ab
    const Packed packed_003 = pfmul(packed_001, load_pair(matrix + 0)); // original0068b0b1
    const Packed packed_004 = pfmul(packed_002, load_pair(matrix + 4)); // original0068b0b8
    const Packed packed_005 = pfadd(packed_003, packed_004);            // original0068b0bd
    store_pair(output + 0, packed_005);                                 // original0068b0c1
    media_empty();                                                      // original0068b0c4
    return output;
}

extern "C" __attribute__((target("mmx,3dnow"))) float* __attribute__((stdcall))
FUN_0068a2d7(float* output, const float* vector, const float* matrix) {
    media_empty();                                                       // original0068a2dc
    const Packed packed_000 = load_pair(vector + 0);                     // original0068a2e7
    const Packed packed_001 = punpckldq(packed_000, packed_000);         // original0068a2ed
    const Packed packed_002 = punpckhdq(packed_000, packed_000);         // original0068a2f0
    const Packed packed_003 = load_scalar(vector + 2);                   // original0068a2f3
    const Packed packed_004 = punpckldq(packed_003, packed_003);         // original0068a2f7
    const Packed packed_005 = pfmul(packed_001, load_pair(matrix + 0));  // original0068a2fd
    const Packed packed_006 = pfmul(packed_002, load_pair(matrix + 4));  // original0068a304
    const Packed packed_007 = pfmul(packed_004, load_pair(matrix + 8));  // original0068a30c
    const Packed packed_008 = pfmul(packed_001, load_pair(matrix + 2));  // original0068a311
    const Packed packed_009 = pfadd(packed_006, packed_007);             // original0068a316
    const Packed packed_010 = pfmul(packed_002, load_pair(matrix + 6));  // original0068a31a
    const Packed packed_011 = pfmul(packed_004, load_pair(matrix + 10)); // original0068a31f
    const Packed packed_012 = pfadd(packed_005, packed_009);             // original0068a324
    const Packed packed_013 = pfadd(packed_010, packed_011);             // original0068a328
    const Packed packed_014 = pfadd(packed_008, packed_013);             // original0068a32c
    store_pair(output + 0, packed_012);                                  // original0068a330
    store_scalar(output + 2, packed_014);                                // original0068a333
    media_empty();                                                       // original0068a337
    return output;
}

extern "C" __attribute__((target("mmx,3dnow"))) float* __attribute__((stdcall))
FUN_0068b979(float* output, const float* vector, const float* matrix) {
    media_empty();                                                       // original0068b979
    const Packed packed_000 = load_pair(vector + 0);                     // original0068b983
    const Packed packed_001 = punpckldq(packed_000, packed_000);         // original0068b989
    const Packed packed_002 = punpckhdq(packed_000, packed_000);         // original0068b98c
    const Packed packed_003 = load_pair(vector + 2);                     // original0068b98f
    const Packed packed_004 = punpckldq(packed_003, packed_003);         // original0068b996
    const Packed packed_005 = punpckhdq(packed_003, packed_003);         // original0068b999
    const Packed packed_006 = pfmul(packed_001, load_pair(matrix + 0));  // original0068b99f
    const Packed packed_007 = pfmul(packed_002, load_pair(matrix + 4));  // original0068b9a6
    const Packed packed_008 = pfmul(packed_004, load_pair(matrix + 8));  // original0068b9ae
    const Packed packed_009 = pfmul(packed_005, load_pair(matrix + 12)); // original0068b9b6
    const Packed packed_010 = pfadd(packed_006, packed_007);             // original0068b9bb
    const Packed packed_011 = pfmul(packed_001, load_pair(matrix + 2));  // original0068b9bf
    const Packed packed_012 = pfadd(packed_008, packed_009);             // original0068b9c4
    const Packed packed_013 = pfmul(packed_002, load_pair(matrix + 6));  // original0068b9c8
    const Packed packed_014 = pfmul(packed_004, load_pair(matrix + 10)); // original0068b9d1
    const Packed packed_015 = pfmul(packed_005, load_pair(matrix + 14)); // original0068b9d6
    const Packed packed_016 = pfadd(packed_010, packed_012);             // original0068b9db
    const Packed packed_017 = pfadd(packed_011, packed_013);             // original0068b9df
    const Packed packed_018 = pfadd(packed_014, packed_015);             // original0068b9e3
    const Packed packed_019 = pfadd(packed_017, packed_018);             // original0068b9e7
    store_pair(output + 0, packed_016);                                  // original0068b9eb
    store_pair(output + 2, packed_019);                                  // original0068b9ee
    media_empty();                                                       // original0068b9f2
    return output;
}
