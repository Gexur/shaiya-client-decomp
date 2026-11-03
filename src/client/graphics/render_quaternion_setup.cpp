#include "graphics/render_quaternion_setup.h"
#include "startup/math_dispatch_state.h"
#include "graphics/render_normalization_dispatch.h"
#include "graphics/render_quaternion_product_dispatch.h"
#include "graphics/render_quaternion_exponential.h"
#include "graphics/render_quaternion_logarithm.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
struct __attribute__((packed, may_alias)) FloatWord {
    float value;
};
volatile float& f32(u32 p) {
    return reinterpret_cast<volatile FloatWord*>(p)->value;
}
long double negate(long double v) {
    __asm__ volatile("fchs" : "+t"(v)::"memory");
    return v;
}
uint16_t compare(long double first, long double second) {
    uint16_t status;
    __asm__ volatile("fcompp\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "t"(first), "u"(second)
                     : "st", "st(1)", "memory", "cc");
    return status;
}
} // namespace
// Original160-byte reservation belongs to the entry adapter, before any helper
// arguments. This code accesses actual original frame spans, never a guessed
// conventional quaternion-setup formula or a serialized instruction stream.
extern "C" void* recovered_005e879c(u32* arguments, u32 frame) {
    const u32 slots = reinterpret_cast<u32>(arguments);
    u32 ax, si, di;
    uint16_t comparison;
    const float quarter = -0.25f;
    si = word(slots + 12u); // 005e87a8
    di = frame - 128u;      // 005e87ac
    put(di, word(si));
    si += 4;
    di += 4; // 005e87af
    put(di, word(si));
    si += 4;
    di += 4; // 005e87b0
    put(di, word(si));
    si += 4;
    di += 4; // 005e87b1
    put(di, word(si));
    si += 4;
    di += 4;                // 005e87b2
    si = word(slots + 16u); // 005e87b3
    di = frame - 80u;       // 005e87b6
    put(di, word(si));
    si += 4;
    di += 4; // 005e87b9
    put(di, word(si));
    si += 4;
    di += 4; // 005e87ba
    put(di, word(si));
    si += 4;
    di += 4; // 005e87bb
    put(di, word(si));
    si += 4;
    di += 4;                                                                            // 005e87bc
    const volatile long double fp_value0 = static_cast<long double>(f32(frame - 80u));  // 005e87bd
    const volatile long double fp_value1 = static_cast<long double>(f32(frame - 128u)); // 005e87c0
    const volatile long double fp_value2 = fp_value0 + fp_value1;                       // 005e87c0
    const volatile long double fp_value3 = static_cast<long double>(f32(frame - 76u));  // 005e87c3
    si = word(slots + 20u);                                                             // 005e87c6
    const volatile long double fp_value4 = static_cast<long double>(f32(frame - 124u)); // 005e87c9
    const volatile long double fp_value5 = fp_value3 + fp_value4;                       // 005e87c9
    di = frame - 32u;                                                                   // 005e87cc
    const volatile long double fp_value6 = static_cast<long double>(f32(frame - 72u));  // 005e87cf
    put(di, word(si));
    si += 4;
    di += 4;                                                                             // 005e87d2
    const volatile long double fp_value7 = static_cast<long double>(f32(frame - 120u));  // 005e87d3
    const volatile long double fp_value8 = fp_value6 + fp_value7;                        // 005e87d3
    const volatile long double fp_value9 = static_cast<long double>(f32(frame - 68u));   // 005e87d6
    const volatile long double fp_value10 = static_cast<long double>(f32(frame - 116u)); // 005e87d9
    const volatile long double fp_value11 = fp_value9 + fp_value10;                      // 005e87d9
    const volatile long double fp_value12 = static_cast<long double>(f32(frame - 128u)); // 005e87dc
    put(di, word(si));
    si += 4;
    di += 4;                                                                             // 005e87df
    const volatile long double fp_value13 = static_cast<long double>(f32(frame - 80u));  // 005e87e0
    const volatile long double fp_value14 = fp_value12 - fp_value13;                     // 005e87e0
    const volatile long double fp_value15 = static_cast<long double>(f32(frame - 124u)); // 005e87e3
    const volatile long double fp_value16 = static_cast<long double>(f32(frame - 76u));  // 005e87e6
    const volatile long double fp_value17 = fp_value15 - fp_value16;                     // 005e87e6
    put(di, word(si));
    si += 4;
    di += 4;                                                                             // 005e87e9
    f32(frame - 12u) = static_cast<float>(fp_value17);                                   // 005e87ea
    const volatile long double fp_value18 = static_cast<long double>(f32(frame - 120u)); // 005e87ed
    const volatile long double fp_value19 = static_cast<long double>(f32(frame - 72u));  // 005e87f0
    const volatile long double fp_value20 = fp_value18 - fp_value19;                     // 005e87f0
    put(di, word(si));
    si += 4;
    di += 4;                                                                             // 005e87f3
    f32(frame - 8u) = static_cast<float>(fp_value20);                                    // 005e87f4
    const volatile long double fp_value21 = static_cast<long double>(f32(frame - 116u)); // 005e87f7
    si = word(slots + 24u);                                                              // 005e87fa
    const volatile long double fp_value22 = static_cast<long double>(f32(frame - 68u));  // 005e87fd
    const volatile long double fp_value23 = fp_value21 - fp_value22;                     // 005e87fd
    di = frame - 112u;                                                                   // 005e8800
    put(di, word(si));
    si += 4;
    di += 4;                                                         // 005e8803
    f32(frame - 4u) = static_cast<float>(fp_value23);                // 005e8804
    const volatile long double fp_value24 = fp_value11;              // 005e8807
    const volatile long double fp_value25 = fp_value24 * fp_value11; // 005e8809
    put(di, word(si));
    si += 4;
    di += 4;                                                        // 005e880b
    const volatile long double fp_value26 = fp_value8;              // 005e880c
    const volatile long double fp_value27 = fp_value26 * fp_value8; // 005e880e
    put(di, word(si));
    si += 4;
    di += 4;                                                         // 005e8810
    const volatile long double fp_value28 = fp_value25 + fp_value27; // 005e8811
    const volatile long double fp_value29 = fp_value5;               // 005e8813
    const volatile long double fp_value30 = fp_value29 * fp_value5;  // 005e8815
    put(di, word(si));
    si += 4;
    di += 4;                                                                            // 005e8817
    const volatile long double fp_value31 = fp_value28 + fp_value30;                    // 005e8818
    const volatile long double fp_value32 = fp_value2;                                  // 005e881a
    const volatile long double fp_value33 = fp_value32 * fp_value2;                     // 005e881c
    const volatile long double fp_value34 = fp_value31 + fp_value33;                    // 005e881e
    const volatile long double fp_value35 = static_cast<long double>(f32(frame - 4u));  // 005e8820
    const volatile long double fp_value36 = static_cast<long double>(f32(frame - 4u));  // 005e8823
    const volatile long double fp_value37 = fp_value35 * fp_value36;                    // 005e8823
    const volatile long double fp_value38 = static_cast<long double>(f32(frame - 8u));  // 005e8826
    const volatile long double fp_value39 = static_cast<long double>(f32(frame - 8u));  // 005e8829
    const volatile long double fp_value40 = fp_value38 * fp_value39;                    // 005e8829
    const volatile long double fp_value41 = fp_value37 + fp_value40;                    // 005e882c
    const volatile long double fp_value42 = static_cast<long double>(f32(frame - 12u)); // 005e882e
    const volatile long double fp_value43 = static_cast<long double>(f32(frame - 12u)); // 005e8831
    const volatile long double fp_value44 = fp_value42 * fp_value43;                    // 005e8831
    const volatile long double fp_value45 = fp_value41 + fp_value44;                    // 005e8834
    const volatile long double fp_value46 = fp_value14;                                 // 005e8836
    const volatile long double fp_value47 = fp_value46 * fp_value14;                    // 005e8838
    const volatile long double fp_value48 = fp_value45 + fp_value47;                    // 005e883a
    comparison = compare(fp_value48, fp_value34);                                       // 005e883c
    if ((comparison & 0x4100u) == 0) {
        const volatile long double fp_value49 =
            static_cast<long double>(f32(frame - 128u));            // 005e884f
        si = frame - 48u;                                           // 005e8852
        const volatile long double fp_value50 = negate(fp_value49); // 005e8855
        di = frame - 128u;                                          // 005e8857
        f32(frame - 48u) = static_cast<float>(fp_value50);          // 005e885a
        const volatile long double fp_value51 =
            static_cast<long double>(f32(frame - 124u));            // 005e885d
        const volatile long double fp_value52 = negate(fp_value51); // 005e8860
        f32(frame - 44u) = static_cast<float>(fp_value52);          // 005e8862
        const volatile long double fp_value53 =
            static_cast<long double>(f32(frame - 120u));            // 005e8865
        const volatile long double fp_value54 = negate(fp_value53); // 005e8868
        f32(frame - 40u) = static_cast<float>(fp_value54);          // 005e886a
        const volatile long double fp_value55 =
            static_cast<long double>(f32(frame - 116u));            // 005e886d
        const volatile long double fp_value56 = negate(fp_value55); // 005e8870
        f32(frame - 36u) = static_cast<float>(fp_value56);          // 005e8872
        put(di, word(si));
        si += 4;
        di += 4; // 005e8875
        put(di, word(si));
        si += 4;
        di += 4; // 005e8876
        put(di, word(si));
        si += 4;
        di += 4; // 005e8877
        put(di, word(si));
        si += 4;
        di += 4; // 005e8878
    }
    const volatile long double fp_value57 = static_cast<long double>(f32(frame - 32u));  // 005e8879
    const volatile long double fp_value58 = static_cast<long double>(f32(frame - 80u));  // 005e887c
    const volatile long double fp_value59 = fp_value57 + fp_value58;                     // 005e887c
    const volatile long double fp_value60 = static_cast<long double>(f32(frame - 28u));  // 005e887f
    const volatile long double fp_value61 = static_cast<long double>(f32(frame - 76u));  // 005e8882
    const volatile long double fp_value62 = fp_value60 + fp_value61;                     // 005e8882
    const volatile long double fp_value63 = static_cast<long double>(f32(frame - 24u));  // 005e8885
    const volatile long double fp_value64 = static_cast<long double>(f32(frame - 72u));  // 005e8888
    const volatile long double fp_value65 = fp_value63 + fp_value64;                     // 005e8888
    const volatile long double fp_value66 = static_cast<long double>(f32(frame - 20u));  // 005e888b
    const volatile long double fp_value67 = static_cast<long double>(f32(frame - 68u));  // 005e888e
    const volatile long double fp_value68 = fp_value66 + fp_value67;                     // 005e888e
    const volatile long double fp_value69 = static_cast<long double>(f32(frame - 80u));  // 005e8891
    const volatile long double fp_value70 = static_cast<long double>(f32(frame - 32u));  // 005e8894
    const volatile long double fp_value71 = fp_value69 - fp_value70;                     // 005e8894
    const volatile long double fp_value72 = static_cast<long double>(f32(frame - 76u));  // 005e8897
    const volatile long double fp_value73 = static_cast<long double>(f32(frame - 28u));  // 005e889a
    const volatile long double fp_value74 = fp_value72 - fp_value73;                     // 005e889a
    f32(frame - 12u) = static_cast<float>(fp_value74);                                   // 005e889d
    const volatile long double fp_value75 = static_cast<long double>(f32(frame - 72u));  // 005e88a0
    const volatile long double fp_value76 = static_cast<long double>(f32(frame - 24u));  // 005e88a3
    const volatile long double fp_value77 = fp_value75 - fp_value76;                     // 005e88a3
    f32(frame - 8u) = static_cast<float>(fp_value77);                                    // 005e88a6
    const volatile long double fp_value78 = static_cast<long double>(f32(frame - 68u));  // 005e88a9
    const volatile long double fp_value79 = static_cast<long double>(f32(frame - 20u));  // 005e88ac
    const volatile long double fp_value80 = fp_value78 - fp_value79;                     // 005e88ac
    f32(frame - 4u) = static_cast<float>(fp_value80);                                    // 005e88af
    const volatile long double fp_value81 = fp_value68;                                  // 005e88b2
    const volatile long double fp_value82 = fp_value81 * fp_value68;                     // 005e88b4
    const volatile long double fp_value83 = fp_value65;                                  // 005e88b6
    const volatile long double fp_value84 = fp_value83 * fp_value65;                     // 005e88b8
    const volatile long double fp_value85 = fp_value82 + fp_value84;                     // 005e88ba
    const volatile long double fp_value86 = fp_value62;                                  // 005e88bc
    const volatile long double fp_value87 = fp_value86 * fp_value62;                     // 005e88be
    const volatile long double fp_value88 = fp_value85 + fp_value87;                     // 005e88c0
    const volatile long double fp_value89 = fp_value59;                                  // 005e88c2
    const volatile long double fp_value90 = fp_value89 * fp_value59;                     // 005e88c4
    const volatile long double fp_value91 = fp_value88 + fp_value90;                     // 005e88c6
    const volatile long double fp_value92 = static_cast<long double>(f32(frame - 4u));   // 005e88c8
    const volatile long double fp_value93 = static_cast<long double>(f32(frame - 4u));   // 005e88cb
    const volatile long double fp_value94 = fp_value92 * fp_value93;                     // 005e88cb
    const volatile long double fp_value95 = static_cast<long double>(f32(frame - 8u));   // 005e88ce
    const volatile long double fp_value96 = static_cast<long double>(f32(frame - 8u));   // 005e88d1
    const volatile long double fp_value97 = fp_value95 * fp_value96;                     // 005e88d1
    const volatile long double fp_value98 = fp_value94 + fp_value97;                     // 005e88d4
    const volatile long double fp_value99 = static_cast<long double>(f32(frame - 12u));  // 005e88d6
    const volatile long double fp_value100 = static_cast<long double>(f32(frame - 12u)); // 005e88d9
    const volatile long double fp_value101 = fp_value99 * fp_value100;                   // 005e88d9
    const volatile long double fp_value102 = fp_value98 + fp_value101;                   // 005e88dc
    const volatile long double fp_value103 = fp_value71;                                 // 005e88de
    const volatile long double fp_value104 = fp_value103 * fp_value71;                   // 005e88e0
    const volatile long double fp_value105 = fp_value102 + fp_value104;                  // 005e88e2
    comparison = compare(fp_value105, fp_value91);                                       // 005e88e4
    if ((comparison & 0x4100u) == 0) {
        const volatile long double fp_value106 =
            static_cast<long double>(f32(frame - 32u));               // 005e88f7
        si = frame - 48u;                                             // 005e88fa
        const volatile long double fp_value107 = negate(fp_value106); // 005e88fd
        di = frame - 32u;                                             // 005e88ff
        f32(frame - 48u) = static_cast<float>(fp_value107);           // 005e8902
        const volatile long double fp_value108 =
            static_cast<long double>(f32(frame - 28u));               // 005e8905
        const volatile long double fp_value109 = negate(fp_value108); // 005e8908
        f32(frame - 44u) = static_cast<float>(fp_value109);           // 005e890a
        const volatile long double fp_value110 =
            static_cast<long double>(f32(frame - 24u));               // 005e890d
        const volatile long double fp_value111 = negate(fp_value110); // 005e8910
        f32(frame - 40u) = static_cast<float>(fp_value111);           // 005e8912
        const volatile long double fp_value112 =
            static_cast<long double>(f32(frame - 20u));               // 005e8915
        const volatile long double fp_value113 = negate(fp_value112); // 005e8918
        f32(frame - 36u) = static_cast<float>(fp_value113);           // 005e891a
        put(di, word(si));
        si += 4;
        di += 4; // 005e891d
        put(di, word(si));
        si += 4;
        di += 4; // 005e891e
        put(di, word(si));
        si += 4;
        di += 4; // 005e891f
        put(di, word(si));
        si += 4;
        di += 4; // 005e8920
    }
    const volatile long double fp_value114 =
        static_cast<long double>(f32(frame - 112u));                                     // 005e8921
    const volatile long double fp_value115 = static_cast<long double>(f32(frame - 32u)); // 005e8924
    const volatile long double fp_value116 = fp_value114 + fp_value115;                  // 005e8924
    const volatile long double fp_value117 =
        static_cast<long double>(f32(frame - 108u));                                     // 005e8927
    const volatile long double fp_value118 = static_cast<long double>(f32(frame - 28u)); // 005e892a
    const volatile long double fp_value119 = fp_value117 + fp_value118;                  // 005e892a
    const volatile long double fp_value120 =
        static_cast<long double>(f32(frame - 104u));                                     // 005e892d
    const volatile long double fp_value121 = static_cast<long double>(f32(frame - 24u)); // 005e8930
    const volatile long double fp_value122 = fp_value120 + fp_value121;                  // 005e8930
    const volatile long double fp_value123 =
        static_cast<long double>(f32(frame - 100u));                                     // 005e8933
    const volatile long double fp_value124 = static_cast<long double>(f32(frame - 20u)); // 005e8936
    const volatile long double fp_value125 = fp_value123 + fp_value124;                  // 005e8936
    const volatile long double fp_value126 = static_cast<long double>(f32(frame - 32u)); // 005e8939
    const volatile long double fp_value127 =
        static_cast<long double>(f32(frame - 112u));                                     // 005e893c
    const volatile long double fp_value128 = fp_value126 - fp_value127;                  // 005e893c
    const volatile long double fp_value129 = static_cast<long double>(f32(frame - 28u)); // 005e893f
    const volatile long double fp_value130 =
        static_cast<long double>(f32(frame - 108u));                                     // 005e8942
    const volatile long double fp_value131 = fp_value129 - fp_value130;                  // 005e8942
    f32(frame - 12u) = static_cast<float>(fp_value131);                                  // 005e8945
    const volatile long double fp_value132 = static_cast<long double>(f32(frame - 24u)); // 005e8948
    const volatile long double fp_value133 =
        static_cast<long double>(f32(frame - 104u));                                     // 005e894b
    const volatile long double fp_value134 = fp_value132 - fp_value133;                  // 005e894b
    f32(frame - 8u) = static_cast<float>(fp_value134);                                   // 005e894e
    const volatile long double fp_value135 = static_cast<long double>(f32(frame - 20u)); // 005e8951
    const volatile long double fp_value136 =
        static_cast<long double>(f32(frame - 100u));                                     // 005e8954
    const volatile long double fp_value137 = fp_value135 - fp_value136;                  // 005e8954
    f32(frame - 4u) = static_cast<float>(fp_value137);                                   // 005e8957
    const volatile long double fp_value138 = fp_value125;                                // 005e895a
    const volatile long double fp_value139 = fp_value138 * fp_value125;                  // 005e895c
    const volatile long double fp_value140 = fp_value122;                                // 005e895e
    const volatile long double fp_value141 = fp_value140 * fp_value122;                  // 005e8960
    const volatile long double fp_value142 = fp_value139 + fp_value141;                  // 005e8962
    const volatile long double fp_value143 = fp_value119;                                // 005e8964
    const volatile long double fp_value144 = fp_value143 * fp_value119;                  // 005e8966
    const volatile long double fp_value145 = fp_value142 + fp_value144;                  // 005e8968
    const volatile long double fp_value146 = fp_value116;                                // 005e896a
    const volatile long double fp_value147 = fp_value146 * fp_value116;                  // 005e896c
    const volatile long double fp_value148 = fp_value145 + fp_value147;                  // 005e896e
    const volatile long double fp_value149 = static_cast<long double>(f32(frame - 4u));  // 005e8970
    const volatile long double fp_value150 = static_cast<long double>(f32(frame - 4u));  // 005e8973
    const volatile long double fp_value151 = fp_value149 * fp_value150;                  // 005e8973
    const volatile long double fp_value152 = static_cast<long double>(f32(frame - 8u));  // 005e8976
    const volatile long double fp_value153 = static_cast<long double>(f32(frame - 8u));  // 005e8979
    const volatile long double fp_value154 = fp_value152 * fp_value153;                  // 005e8979
    const volatile long double fp_value155 = fp_value151 + fp_value154;                  // 005e897c
    const volatile long double fp_value156 = static_cast<long double>(f32(frame - 12u)); // 005e897e
    const volatile long double fp_value157 = static_cast<long double>(f32(frame - 12u)); // 005e8981
    const volatile long double fp_value158 = fp_value156 * fp_value157;                  // 005e8981
    const volatile long double fp_value159 = fp_value155 + fp_value158;                  // 005e8984
    const volatile long double fp_value160 = fp_value128;                                // 005e8986
    const volatile long double fp_value161 = fp_value160 * fp_value128;                  // 005e8988
    const volatile long double fp_value162 = fp_value159 + fp_value161;                  // 005e898a
    comparison = compare(fp_value162, fp_value148);                                      // 005e898c
    if ((comparison & 0x4100u) == 0) {
        const volatile long double fp_value163 =
            static_cast<long double>(f32(frame - 112u));              // 005e899f
        si = frame - 48u;                                             // 005e89a2
        const volatile long double fp_value164 = negate(fp_value163); // 005e89a5
        di = frame - 112u;                                            // 005e89a7
        f32(frame - 48u) = static_cast<float>(fp_value164);           // 005e89aa
        const volatile long double fp_value165 =
            static_cast<long double>(f32(frame - 108u));              // 005e89ad
        const volatile long double fp_value166 = negate(fp_value165); // 005e89b0
        f32(frame - 44u) = static_cast<float>(fp_value166);           // 005e89b2
        const volatile long double fp_value167 =
            static_cast<long double>(f32(frame - 104u));              // 005e89b5
        const volatile long double fp_value168 = negate(fp_value167); // 005e89b8
        f32(frame - 40u) = static_cast<float>(fp_value168);           // 005e89ba
        const volatile long double fp_value169 =
            static_cast<long double>(f32(frame - 100u));              // 005e89bd
        const volatile long double fp_value170 = negate(fp_value169); // 005e89c0
        f32(frame - 36u) = static_cast<float>(fp_value170);           // 005e89c2
        put(di, word(si));
        si += 4;
        di += 4; // 005e89c5
        put(di, word(si));
        si += 4;
        di += 4; // 005e89c6
        put(di, word(si));
        si += 4;
        di += 4; // 005e89c7
        put(di, word(si));
        si += 4;
        di += 4; // 005e89c8
    }
    ax = frame - 80u;           // 005e89c9
    const u32 argument0_0 = ax; // 005e89cc
    ax = frame - 48u;           // 005e89cd
    const u32 argument0_1 = ax; // 005e89d0
    ax =
        reinterpret_cast<u32>(FUN_005e6b28(reinterpret_cast<void*>(argument0_1),
                                           reinterpret_cast<const void*>(argument0_0))); // 005e89d1
    ax = frame - 128u;                                                                   // 005e89d6
    const u32 argument1_0 = ax;                                                          // 005e89d9
    ax = frame - 48u;                                                                    // 005e89da
    const u32 argument1_1 = ax;                                                          // 005e89dd
    ax = frame - 64u;                                                                    // 005e89de
    const u32 argument1_2 = ax;                                                          // 005e89e1
    ax = reinterpret_cast<u32>(FUN_005e6a64(
        reinterpret_cast<void*>(argument1_2), reinterpret_cast<const void*>(argument1_1),
        reinterpret_cast<const void*>(argument1_0))); // 005e89e2
    si = frame - 64u;                                 // 005e89e7
    di = frame - 96u;                                 // 005e89ea
    put(di, word(si));
    si += 4;
    di += 4; // 005e89ed
    put(di, word(si));
    si += 4;
    di += 4;          // 005e89ee
    ax = frame - 96u; // 005e89ef
    put(di, word(si));
    si += 4;
    di += 4;                    // 005e89f2
    const u32 argument2_0 = ax; // 005e89f3
    ax = frame - 144u;          // 005e89f4
    const u32 argument2_1 = ax; // 005e89fa
    put(di, word(si));
    si += 4;
    di += 4; // 005e89fb
    ax =
        reinterpret_cast<u32>(FUN_005e6bf4(reinterpret_cast<void*>(argument2_1),
                                           reinterpret_cast<const void*>(argument2_0))); // 005e89fc
    ax = frame - 32u;                                                                    // 005e8a01
    const u32 argument3_0 = ax;                                                          // 005e8a04
    ax = frame - 48u;                                                                    // 005e8a05
    const u32 argument3_1 = ax;                                                          // 005e8a08
    ax = frame - 64u;                                                                    // 005e8a09
    const u32 argument3_2 = ax;                                                          // 005e8a0c
    ax = reinterpret_cast<u32>(FUN_005e6a64(
        reinterpret_cast<void*>(argument3_2), reinterpret_cast<const void*>(argument3_1),
        reinterpret_cast<const void*>(argument3_0))); // 005e8a0d
    si = frame - 64u;                                 // 005e8a12
    di = frame - 96u;                                 // 005e8a15
    put(di, word(si));
    si += 4;
    di += 4; // 005e8a18
    put(di, word(si));
    si += 4;
    di += 4;          // 005e8a19
    ax = frame - 96u; // 005e8a1a
    put(di, word(si));
    si += 4;
    di += 4;                    // 005e8a1d
    const u32 argument4_0 = ax; // 005e8a1e
    ax = frame - 16u;           // 005e8a1f
    const u32 argument4_1 = ax; // 005e8a22
    put(di, word(si));
    si += 4;
    di += 4; // 005e8a23
    ax =
        reinterpret_cast<u32>(FUN_005e6bf4(reinterpret_cast<void*>(argument4_1),
                                           reinterpret_cast<const void*>(argument4_0))); // 005e8a24
    ax = frame - 96u;                                                                    // 005e8a29
    const volatile long double fp_value171 =
        static_cast<long double>(f32(frame - 144u));                                     // 005e8a2c
    const u32 argument5_0 = ax;                                                          // 005e8a32
    const volatile long double fp_value172 = static_cast<long double>(f32(frame - 16u)); // 005e8a33
    const volatile long double fp_value173 = fp_value171 + fp_value172;                  // 005e8a33
    ax = frame - 160u;                                                                   // 005e8a36
    const volatile long double fp_value174 =
        static_cast<long double>(f32(frame - 140u));                                     // 005e8a3c
    const u32 argument5_1 = ax;                                                          // 005e8a42
    const volatile long double fp_value175 = static_cast<long double>(f32(frame - 12u)); // 005e8a43
    const volatile long double fp_value176 = fp_value174 + fp_value175;                  // 005e8a43
    f32(frame - 60u) = static_cast<float>(fp_value176);                                  // 005e8a46
    const volatile long double fp_value177 =
        static_cast<long double>(f32(frame - 136u));                                    // 005e8a49
    const volatile long double fp_value178 = static_cast<long double>(f32(frame - 8u)); // 005e8a4f
    const volatile long double fp_value179 = fp_value177 + fp_value178;                 // 005e8a4f
    f32(frame - 56u) = static_cast<float>(fp_value179);                                 // 005e8a52
    const volatile long double fp_value180 =
        static_cast<long double>(f32(frame - 132u));                                    // 005e8a55
    const volatile long double fp_value181 = static_cast<long double>(f32(frame - 4u)); // 005e8a5b
    const volatile long double fp_value182 = fp_value180 + fp_value181;                 // 005e8a5b
    const volatile long double fp_value183 =
        static_cast<long double>(f32(reinterpret_cast<u32>(&quarter)));                  // 005e8a5e
    const volatile long double fp_value184 = fp_value173;                                // 005e8a64
    const volatile long double fp_value185 = fp_value184 * fp_value183;                  // 005e8a66
    f32(frame - 96u) = static_cast<float>(fp_value185);                                  // 005e8a68
    const volatile long double fp_value186 = static_cast<long double>(f32(frame - 60u)); // 005e8a6b
    const volatile long double fp_value187 = fp_value186 * fp_value183;                  // 005e8a6e
    f32(frame - 92u) = static_cast<float>(fp_value187);                                  // 005e8a70
    const volatile long double fp_value188 = static_cast<long double>(f32(frame - 56u)); // 005e8a73
    const volatile long double fp_value189 = fp_value188 * fp_value183;                  // 005e8a76
    f32(frame - 88u) = static_cast<float>(fp_value189);                                  // 005e8a78
    const volatile long double fp_value190 = fp_value182;                                // 005e8a7b
    const volatile long double fp_value191 = fp_value190 * fp_value183;                  // 005e8a7d
    f32(frame - 84u) = static_cast<float>(fp_value191);                                  // 005e8a7f
    ax =
        reinterpret_cast<u32>(FUN_005e6c8a(reinterpret_cast<void*>(argument5_1),
                                           reinterpret_cast<const void*>(argument5_0))); // 005e8a88
    ax = frame - 160u;                                                                   // 005e8a8d
    const u32 argument6_0 = ax;                                                          // 005e8a93
    ax = frame - 80u;                                                                    // 005e8a94
    const u32 argument6_1 = ax;                                                          // 005e8a97
    ax = frame - 64u;                                                                    // 005e8a98
    const u32 argument6_2 = ax;                                                          // 005e8a9b
    ax = reinterpret_cast<u32>(FUN_005e6a64(
        reinterpret_cast<void*>(argument6_2), reinterpret_cast<const void*>(argument6_1),
        reinterpret_cast<const void*>(argument6_0))); // 005e8a9c
    di = word(slots + 0u);                            // 005e8aa1
    si = frame - 64u;                                 // 005e8aa4
    put(di, word(si));
    si += 4;
    di += 4; // 005e8aa7
    put(di, word(si));
    si += 4;
    di += 4;          // 005e8aa8
    ax = frame - 32u; // 005e8aa9
    put(di, word(si));
    si += 4;
    di += 4;                    // 005e8aac
    const u32 argument7_0 = ax; // 005e8aad
    ax = frame - 48u;           // 005e8aae
    const u32 argument7_1 = ax; // 005e8ab1
    put(di, word(si));
    si += 4;
    di += 4; // 005e8ab2
    ax =
        reinterpret_cast<u32>(FUN_005e6b28(reinterpret_cast<void*>(argument7_1),
                                           reinterpret_cast<const void*>(argument7_0))); // 005e8ab3
    ax = frame - 80u;                                                                    // 005e8ab8
    const u32 argument8_0 = ax;                                                          // 005e8abb
    ax = frame - 48u;                                                                    // 005e8abc
    const u32 argument8_1 = ax;                                                          // 005e8abf
    ax = frame - 64u;                                                                    // 005e8ac0
    const u32 argument8_2 = ax;                                                          // 005e8ac3
    ax = reinterpret_cast<u32>(FUN_005e6a64(
        reinterpret_cast<void*>(argument8_2), reinterpret_cast<const void*>(argument8_1),
        reinterpret_cast<const void*>(argument8_0))); // 005e8ac4
    si = frame - 64u;                                 // 005e8ac9
    di = frame - 96u;                                 // 005e8acc
    put(di, word(si));
    si += 4;
    di += 4; // 005e8acf
    put(di, word(si));
    si += 4;
    di += 4;          // 005e8ad0
    ax = frame - 96u; // 005e8ad1
    put(di, word(si));
    si += 4;
    di += 4;                    // 005e8ad4
    const u32 argument9_0 = ax; // 005e8ad5
    ax = frame - 144u;          // 005e8ad6
    const u32 argument9_1 = ax; // 005e8adc
    put(di, word(si));
    si += 4;
    di += 4; // 005e8add
    ax =
        reinterpret_cast<u32>(FUN_005e6bf4(reinterpret_cast<void*>(argument9_1),
                                           reinterpret_cast<const void*>(argument9_0))); // 005e8ade
    ax = frame - 112u;                                                                   // 005e8ae3
    const u32 argument10_0 = ax;                                                         // 005e8ae6
    ax = frame - 48u;                                                                    // 005e8ae7
    const u32 argument10_1 = ax;                                                         // 005e8aea
    ax = frame - 64u;                                                                    // 005e8aeb
    const u32 argument10_2 = ax;                                                         // 005e8aee
    ax = reinterpret_cast<u32>(FUN_005e6a64(
        reinterpret_cast<void*>(argument10_2), reinterpret_cast<const void*>(argument10_1),
        reinterpret_cast<const void*>(argument10_0))); // 005e8aef
    si = frame - 64u;                                  // 005e8af4
    di = frame - 96u;                                  // 005e8af7
    put(di, word(si));
    si += 4;
    di += 4; // 005e8afa
    put(di, word(si));
    si += 4;
    di += 4;          // 005e8afb
    ax = frame - 96u; // 005e8afc
    put(di, word(si));
    si += 4;
    di += 4;                     // 005e8aff
    const u32 argument11_0 = ax; // 005e8b00
    ax = frame - 16u;            // 005e8b01
    const u32 argument11_1 = ax; // 005e8b04
    put(di, word(si));
    si += 4;
    di += 4; // 005e8b05
    ax = reinterpret_cast<u32>(
        FUN_005e6bf4(reinterpret_cast<void*>(argument11_1),
                     reinterpret_cast<const void*>(argument11_0))); // 005e8b06
    ax = frame - 96u;                                               // 005e8b0b
    const volatile long double fp_value192 =
        static_cast<long double>(f32(frame - 144u));                                     // 005e8b0e
    const u32 argument12_0 = ax;                                                         // 005e8b14
    const volatile long double fp_value193 = static_cast<long double>(f32(frame - 16u)); // 005e8b15
    const volatile long double fp_value194 = fp_value192 + fp_value193;                  // 005e8b15
    ax = frame - 160u;                                                                   // 005e8b18
    const volatile long double fp_value195 =
        static_cast<long double>(f32(frame - 140u));                                     // 005e8b1e
    const u32 argument12_1 = ax;                                                         // 005e8b24
    const volatile long double fp_value196 = static_cast<long double>(f32(frame - 12u)); // 005e8b25
    const volatile long double fp_value197 = fp_value195 + fp_value196;                  // 005e8b25
    f32(frame - 60u) = static_cast<float>(fp_value197);                                  // 005e8b28
    const volatile long double fp_value198 =
        static_cast<long double>(f32(frame - 136u));                                    // 005e8b2b
    const volatile long double fp_value199 = static_cast<long double>(f32(frame - 8u)); // 005e8b31
    const volatile long double fp_value200 = fp_value198 + fp_value199;                 // 005e8b31
    f32(frame - 56u) = static_cast<float>(fp_value200);                                 // 005e8b34
    const volatile long double fp_value201 =
        static_cast<long double>(f32(frame - 132u));                                    // 005e8b37
    const volatile long double fp_value202 = static_cast<long double>(f32(frame - 4u)); // 005e8b3d
    const volatile long double fp_value203 = fp_value201 + fp_value202;                 // 005e8b3d
    const volatile long double fp_value204 =
        static_cast<long double>(f32(reinterpret_cast<u32>(&quarter)));                  // 005e8b40
    const volatile long double fp_value205 = fp_value194;                                // 005e8b46
    const volatile long double fp_value206 = fp_value205 * fp_value204;                  // 005e8b48
    f32(frame - 96u) = static_cast<float>(fp_value206);                                  // 005e8b4a
    const volatile long double fp_value207 = static_cast<long double>(f32(frame - 60u)); // 005e8b4d
    const volatile long double fp_value208 = fp_value207 * fp_value204;                  // 005e8b50
    f32(frame - 92u) = static_cast<float>(fp_value208);                                  // 005e8b52
    const volatile long double fp_value209 = static_cast<long double>(f32(frame - 56u)); // 005e8b55
    const volatile long double fp_value210 = fp_value209 * fp_value204;                  // 005e8b58
    f32(frame - 88u) = static_cast<float>(fp_value210);                                  // 005e8b5a
    const volatile long double fp_value211 = fp_value203;                                // 005e8b5d
    const volatile long double fp_value212 = fp_value211 * fp_value204;                  // 005e8b5f
    f32(frame - 84u) = static_cast<float>(fp_value212);                                  // 005e8b61
    ax = reinterpret_cast<u32>(
        FUN_005e6c8a(reinterpret_cast<void*>(argument12_1),
                     reinterpret_cast<const void*>(argument12_0))); // 005e8b6a
    ax = frame - 160u;                                              // 005e8b6f
    const u32 argument13_0 = ax;                                    // 005e8b75
    ax = frame - 32u;                                               // 005e8b76
    const u32 argument13_1 = ax;                                    // 005e8b79
    ax = frame - 64u;                                               // 005e8b7a
    const u32 argument13_2 = ax;                                    // 005e8b7d
    ax = reinterpret_cast<u32>(FUN_005e6a64(
        reinterpret_cast<void*>(argument13_2), reinterpret_cast<const void*>(argument13_1),
        reinterpret_cast<const void*>(argument13_0))); // 005e8b7e
    di = word(slots + 4u);                             // 005e8b83
    si = frame - 64u;                                  // 005e8b86
    put(di, word(si));
    si += 4;
    di += 4; // 005e8b89
    put(di, word(si));
    si += 4;
    di += 4; // 005e8b8a
    put(di, word(si));
    si += 4;
    di += 4; // 005e8b8b
    put(di, word(si));
    si += 4;
    di += 4;               // 005e8b8c
    di = word(slots + 8u); // 005e8b8d
    si = frame - 32u;      // 005e8b90
    put(di, word(si));
    si += 4;
    di += 4; // 005e8b93
    put(di, word(si));
    si += 4;
    di += 4; // 005e8b94
    put(di, word(si));
    si += 4;
    di += 4; // 005e8b95
    put(di, word(si));
    si += 4;
    di += 4;                            // 005e8b96
    return reinterpret_cast<void*>(ax); // original final product leaves EAX=private EBP-40
}
extern "C" __attribute__((naked, stdcall)) void*
FUN_005e879c(void*, void*, void*, const void*, const void*, const void*, const void*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $160,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%ebp),%eax\n\tpushl %ebp\n\tpushl %eax\n\tcalll _recovered_005e879c\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tleave\n\tretl $28");
}
extern "C" __attribute__((naked, stdcall)) void*
FUN_005e6ec0(void*, void*, void*, const void*, const void*, const void*, const void*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+184");
}
