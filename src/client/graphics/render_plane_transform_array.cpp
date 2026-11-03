#include "graphics/render_plane_transform_array.h"
#include "startup/math_dispatch_state.h"
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
} // namespace
extern "C" __attribute__((noinline)) u32 __cdecl recovered_005e72e5(u32 slots, u32 frame) {
    u32 bx, cx, dx, di, si;
    u32 count = word(slots + 20);
    bx = word(slots + 0u); // original005e72f3
    put(slots, bx);
    if (count) {
        dx = word(slots + 16u); // original005e72ff
        cx = word(slots + 8u);  // original005e7302
        do {
            const volatile long double fp_value0 =
                static_cast<long double>(f32(cx + 4u)); // original005e7307
            di = bx;                                    // original005e730a
            const volatile long double fp_value1 =
                static_cast<long double>(f32(dx + 16u));                  // original005e730c
            const volatile long double fp_value2 = fp_value0 * fp_value1; // original005e730c
            bx += word(slots + 4u);                                       // original005e730f
            const volatile long double fp_value3 =
                static_cast<long double>(f32(dx + 48u)); // original005e7312
            si = frame - 16;
            const volatile long double fp_value4 =
                static_cast<long double>(f32(cx + 12u));                  // original005e7318
            const volatile long double fp_value5 = fp_value3 * fp_value4; // original005e7318
            const volatile long double fp_value6 = fp_value2 + fp_value5; // original005e731b
            const volatile long double fp_value7 =
                static_cast<long double>(f32(cx + 8u)); // original005e731d
            const volatile long double fp_value8 =
                static_cast<long double>(f32(dx + 32u));                   // original005e7320
            const volatile long double fp_value9 = fp_value7 * fp_value8;  // original005e7320
            const volatile long double fp_value10 = fp_value6 + fp_value9; // original005e7323
            const volatile long double fp_value11 =
                static_cast<long double>(f32(cx)); // original005e7325
            const volatile long double fp_value12 =
                static_cast<long double>(f32(dx));                           // original005e7327
            const volatile long double fp_value13 = fp_value11 * fp_value12; // original005e7327
            const volatile long double fp_value14 = fp_value10 + fp_value13; // original005e7329
            f32(frame - 16u) = static_cast<float>(fp_value14);               // original005e732b
            const volatile long double fp_value15 =
                static_cast<long double>(f32(cx + 8u)); // original005e732e
            const volatile long double fp_value16 =
                static_cast<long double>(f32(dx + 36u));                     // original005e7331
            const volatile long double fp_value17 = fp_value15 * fp_value16; // original005e7331
            const volatile long double fp_value18 =
                static_cast<long double>(f32(cx)); // original005e7334
            const volatile long double fp_value19 =
                static_cast<long double>(f32(dx + 4u));                      // original005e7336
            const volatile long double fp_value20 = fp_value18 * fp_value19; // original005e7336
            const volatile long double fp_value21 = fp_value17 + fp_value20; // original005e7339
            const volatile long double fp_value22 =
                static_cast<long double>(f32(cx + 4u)); // original005e733b
            const volatile long double fp_value23 =
                static_cast<long double>(f32(dx + 20u));                     // original005e733e
            const volatile long double fp_value24 = fp_value22 * fp_value23; // original005e733e
            const volatile long double fp_value25 = fp_value21 + fp_value24; // original005e7341
            const volatile long double fp_value26 =
                static_cast<long double>(f32(dx + 52u)); // original005e7343
            const volatile long double fp_value27 =
                static_cast<long double>(f32(cx + 12u));                     // original005e7346
            const volatile long double fp_value28 = fp_value26 * fp_value27; // original005e7346
            const volatile long double fp_value29 = fp_value25 + fp_value28; // original005e7349
            f32(frame - 12u) = static_cast<float>(fp_value29);               // original005e734b
            const volatile long double fp_value30 =
                static_cast<long double>(f32(cx + 12u)); // original005e734e
            const volatile long double fp_value31 =
                static_cast<long double>(f32(dx + 56u));                     // original005e7351
            const volatile long double fp_value32 = fp_value30 * fp_value31; // original005e7351
            const volatile long double fp_value33 =
                static_cast<long double>(f32(cx + 4u)); // original005e7354
            const volatile long double fp_value34 =
                static_cast<long double>(f32(dx + 24u));                     // original005e7357
            const volatile long double fp_value35 = fp_value33 * fp_value34; // original005e7357
            const volatile long double fp_value36 = fp_value32 + fp_value35; // original005e735a
            const volatile long double fp_value37 =
                static_cast<long double>(f32(dx + 8u)); // original005e735c
            const volatile long double fp_value38 =
                static_cast<long double>(f32(cx));                           // original005e735f
            const volatile long double fp_value39 = fp_value37 * fp_value38; // original005e735f
            const volatile long double fp_value40 = fp_value36 + fp_value39; // original005e7361
            const volatile long double fp_value41 =
                static_cast<long double>(f32(cx + 8u)); // original005e7363
            const volatile long double fp_value42 =
                static_cast<long double>(f32(dx + 40u));                     // original005e7366
            const volatile long double fp_value43 = fp_value41 * fp_value42; // original005e7366
            const volatile long double fp_value44 = fp_value40 + fp_value43; // original005e7369
            f32(frame - 8u) = static_cast<float>(fp_value44);                // original005e736b
            const volatile long double fp_value45 =
                static_cast<long double>(f32(cx + 8u)); // original005e736e
            const volatile long double fp_value46 =
                static_cast<long double>(f32(dx + 44u));                     // original005e7371
            const volatile long double fp_value47 = fp_value45 * fp_value46; // original005e7371
            const volatile long double fp_value48 =
                static_cast<long double>(f32(dx + 12u)); // original005e7374
            const volatile long double fp_value49 =
                static_cast<long double>(f32(cx));                           // original005e7377
            const volatile long double fp_value50 = fp_value48 * fp_value49; // original005e7377
            const volatile long double fp_value51 = fp_value47 + fp_value50; // original005e7379
            const volatile long double fp_value52 =
                static_cast<long double>(f32(cx + 4u)); // original005e737b
            const volatile long double fp_value53 =
                static_cast<long double>(f32(dx + 28u));                     // original005e737e
            const volatile long double fp_value54 = fp_value52 * fp_value53; // original005e737e
            const volatile long double fp_value55 = fp_value51 + fp_value54; // original005e7381
            const volatile long double fp_value56 =
                static_cast<long double>(f32(cx + 12u)); // original005e7383
            cx += word(slots + 12u);                     // original005e7386
            --count;
            const volatile long double fp_value57 =
                static_cast<long double>(f32(dx + 60u));                     // original005e738a
            const volatile long double fp_value58 = fp_value56 * fp_value57; // original005e738a
            const volatile long double fp_value59 = fp_value55 + fp_value58; // original005e738d
            f32(frame - 4u) = static_cast<float>(fp_value59);                // original005e738f
            put(di, word(si));
            di += 4;
            si += 4; // original005e7392
            put(di, word(si));
            di += 4;
            si += 4; // original005e7393
            put(di, word(si));
            di += 4;
            si += 4; // original005e7394
            put(di, word(si));
            di += 4;
            si += 4; // original005e7395
        } while (count);
    }
    return word(slots);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e72e5(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $16,%esp\n\tpushl %ebp\n\tleal 8(%ebp),%eax\n\tpushl %eax\n\tcalll _recovered_005e72e5\n\taddl $8,%esp\n\tleave\n\tretl $24");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e72d2(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+276");
}
