#include "graphics/render_plane_matrices.h"
#include "graphics/render_plane_helpers_dispatch.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
struct __attribute__((packed, may_alias)) FloatWord {
    float value;
};
volatile float& f32(u32 p) {
    return reinterpret_cast<volatile FloatWord*>(p)->value;
}
void zero(u32 p) {
    __asm__ volatile("fldz\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
void one(u32 p) {
    __asm__ volatile("fld1\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
} // namespace
// Complete original5e85dd..5e86db. Normalization, exact dot-load sequence,
// F32negation spills and all16 public stores remain separate original steps.
extern "C" void* recovered_005e85dd(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments), plane = word(slots + 8); //85e7
    float p[4];
    FUN_005e6fa1(p, reinterpret_cast<const void*>(plane));                          //85ee
    const volatile long double py = static_cast<long double>(p[1]);                 //85f3
    const u32 light = word(slots + 4);                                              //85f6
    const volatile long double ly = py * static_cast<long double>(f32(light + 4));  //85f9
    const u32 output = word(slots);                                                 //85fc
    const volatile long double px = static_cast<long double>(p[0]);                 //85ff
    const volatile long double lx = px * static_cast<long double>(f32(light));      //8605
    const volatile long double yx = ly + lx;                                        //860a
    const volatile long double pw = static_cast<long double>(p[3]);                 //860c
    const volatile long double lw = pw * static_cast<long double>(f32(light + 12)); //860f
    const volatile long double yxw = yx + lw;                                       //8612
    const volatile long double pz = static_cast<long double>(p[2]);                 //8614
    const volatile long double lz = pz * static_cast<long double>(f32(light + 8));  //8617
    const volatile long double dot = yxw + lz; //861a retained extended across16stores
    volatile float n[4];
    n[0] = static_cast<float>(-static_cast<long double>(p[0])); //861c..8621
    n[1] = static_cast<float>(-static_cast<long double>(p[1])); //8624..8629
    n[2] = static_cast<float>(-static_cast<long double>(p[2])); //862c..8631
    n[3] = static_cast<float>(-static_cast<long double>(p[3])); //8634..8639
    // Original4MOVSD copy from negation scratch into normalized-plane scratch
    // has only private effects; n retains the exact copied F32values below.
    const volatile long double v00 =
        static_cast<long double>(n[0]) * static_cast<long double>(f32(light));
    const volatile long double d00 = v00 + dot;
    f32(output) = static_cast<float>(d00); //8640..8647
    const volatile long double v10 =
        static_cast<long double>(n[1]) * static_cast<long double>(f32(light));
    f32(output + 16) = static_cast<float>(v10); //8649..864e
    const volatile long double v20 =
        static_cast<long double>(n[2]) * static_cast<long double>(f32(light));
    f32(output + 32) = static_cast<float>(v20); //8651..8656
    const volatile long double v30 =
        static_cast<long double>(n[3]) * static_cast<long double>(f32(light));
    f32(output + 48) = static_cast<float>(v30); //8659..865e
    const volatile long double v01 =
        static_cast<long double>(n[0]) * static_cast<long double>(f32(light + 4));
    f32(output + 4) = static_cast<float>(v01); //8661..8667
    const volatile long double v11 =
        static_cast<long double>(n[1]) * static_cast<long double>(f32(light + 4));
    const volatile long double d11 = v11 + dot;
    f32(output + 20) = static_cast<float>(d11); //866a..8672
    const volatile long double v21 =
        static_cast<long double>(n[2]) * static_cast<long double>(f32(light + 4));
    f32(output + 36) = static_cast<float>(v21); //8675..867b
    const volatile long double v31 =
        static_cast<long double>(n[3]) * static_cast<long double>(f32(light + 4));
    f32(output + 52) = static_cast<float>(v31); //867e..8684
    const volatile long double v02 =
        static_cast<long double>(n[0]) * static_cast<long double>(f32(light + 8));
    f32(output + 8) = static_cast<float>(v02); //8687..868d
    const volatile long double v12 =
        static_cast<long double>(n[1]) * static_cast<long double>(f32(light + 8));
    f32(output + 24) = static_cast<float>(v12); //8690..8696
    const volatile long double v22 =
        static_cast<long double>(n[2]) * static_cast<long double>(f32(light + 8));
    const volatile long double d22 = v22 + dot;
    f32(output + 40) = static_cast<float>(d22); //8699..86a1
    const volatile long double v32 =
        static_cast<long double>(n[3]) * static_cast<long double>(f32(light + 8));
    f32(output + 56) = static_cast<float>(v32); //86a4..86aa
    const volatile long double v03 =
        static_cast<long double>(n[0]) * static_cast<long double>(f32(light + 12));
    f32(output + 12) = static_cast<float>(v03); //86ad..86b3
    const volatile long double v13 =
        static_cast<long double>(n[1]) * static_cast<long double>(f32(light + 12));
    f32(output + 28) = static_cast<float>(v13); //86b6..86bc
    const volatile long double v23 =
        static_cast<long double>(n[2]) * static_cast<long double>(f32(light + 12));
    f32(output + 44) = static_cast<float>(v23); //86c0..86c7
    const volatile long double v33 =
        static_cast<long double>(n[3]) * static_cast<long double>(f32(light + 12));
    const volatile long double d33 = v33 + dot;
    f32(output + 60) = static_cast<float>(d33); //86ca..86d2
    return reinterpret_cast<void*>(output);
}
// Complete original5e86db..5e879c. Early Zproduct remains extended for the
// 3x3 entries; only its later bottom-row use reloads the rounded actualarg1.
extern "C" void* recovered_005e86db(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments), plane = word(slots + 4); //86e3
    float p[4];
    FUN_005e6fa1(p, reinterpret_cast<const void*>(plane));                 //86ea
    const volatile long double a = static_cast<long double>(p[0]) * -2.0L; //86ef..86f2
    const u32 output = word(slots);                                        //86f8
    const volatile long double b = static_cast<long double>(p[1]) * -2.0L; //86fb..86fe
    const volatile long double c = static_cast<long double>(p[2]) * -2.0L; //8704..8707
    f32(slots + 4) = static_cast<float>(c);     //870d FST retains extended c
    const volatile long double identity = 1.0L; //8710
    const volatile long double v00 = static_cast<long double>(p[0]) * a;
    const volatile long double d00 = v00 + identity;
    f32(output) = static_cast<float>(d00); //8716..871d
    const volatile long double v01 = b * static_cast<long double>(p[0]);
    f32(output + 4) = static_cast<float>(v01); //871f..8724
    const volatile long double v02 = c * static_cast<long double>(p[0]);
    f32(output + 8) = static_cast<float>(v02); //8727..872c
    zero(output + 12);                         //872f..8731
    const volatile long double v10 = static_cast<long double>(p[1]) * a;
    f32(output + 16) = static_cast<float>(v10); //8734..8739
    const volatile long double v11 = static_cast<long double>(p[1]) * b;
    const volatile long double d11 = v11 + identity;
    f32(output + 20) = static_cast<float>(d11); //873c..8743
    const volatile long double v12 = c * static_cast<long double>(p[1]);
    f32(output + 24) = static_cast<float>(v12); //8746..874b
    zero(output + 28);                          //874e..8750
    const volatile long double v20 = static_cast<long double>(p[2]) * a;
    f32(output + 32) = static_cast<float>(v20); //8753..8758
    const volatile long double v21 = static_cast<long double>(p[2]) * b;
    f32(output + 36) = static_cast<float>(v21); //875b..8760
    const volatile long double v22 = static_cast<long double>(p[2]) * c;
    const volatile long double d22 = v22 + identity;
    f32(output + 40) = static_cast<float>(d22); //8763..876a
    zero(output + 44);                          //8771..8773
    const volatile long double v30 = static_cast<long double>(p[3]) * a;
    f32(output + 48) = static_cast<float>(v30); //8776..877b
    const volatile long double v31 = static_cast<long double>(p[3]) * b;
    f32(output + 52) = static_cast<float>(v31); //877e..8783
    const volatile long double v32 =
        static_cast<long double>(p[3]) * static_cast<long double>(f32(slots + 4));
    f32(output + 56) = static_cast<float>(v32); //878a..8790
    one(output + 60);                           //8793..8795
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e85dd(void*, const void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e85dd\n\taddl $4,%esp\n\tretl $12");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e86db(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e86db\n\taddl $4,%esp\n\tretl $8");
}
