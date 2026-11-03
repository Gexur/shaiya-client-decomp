#include "graphics/render_quaternion_angles.h"
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
void trig(u32 angle, u32 cosine, u32 sine) {
    __asm__ volatile("flds (%0)\n\tfsincos\n\tfstps (%1)\n\tfstps (%2)" ::"r"(angle), "r"(cosine),
                     "r"(sine)
                     : "st", "st(1)", "memory");
}
} // namespace
// Complete original6976..6a51, individually naming its actual arithmetic.
// 0.5 is an ordinary exact copy of readonly6bc860, with no pool ownership.
extern "C" void* recovered_005e6976(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments);
    const volatile long double roll = static_cast<long double>(f32(slots + 12)); //697e
    const volatile long double half_roll = roll * 0.5L;                          //6984
    volatile float roll_argument = static_cast<float>(half_roll);                //6993
    u32 cosine_roll, cosine_pitch, sine_pitch, cosine_yaw, sine_yaw;
    trig(reinterpret_cast<u32>(&roll_argument), reinterpret_cast<u32>(&cosine_roll),
         slots + 12);                                                            //699c..69a3
    const volatile long double pitch = static_cast<long double>(f32(slots + 8)); //69a5
    const volatile long double half_pitch = pitch * 0.5L;                        //69ab
    f32(slots + 8) = static_cast<float>(half_pitch); //69ba actualpitch word
    trig(slots + 8, reinterpret_cast<u32>(&cosine_pitch),
         reinterpret_cast<u32>(&sine_pitch));                                  //69c3..69ca
    const volatile long double yaw = static_cast<long double>(f32(slots + 4)); //69cc
    const volatile long double half_yaw = yaw * 0.5L;                          //69d2
    f32(slots + 8) = static_cast<float>(half_yaw); //69e1 actualpitch word reused
    trig(slots + 8, reinterpret_cast<u32>(&cosine_yaw),
         reinterpret_cast<u32>(&sine_yaw)); //69ea..69f1
    const volatile long double sy =
        static_cast<long double>(f32(reinterpret_cast<u32>(&sine_yaw))); //69f3
    const u32 output = word(slots); //69f6 caches only after all three trig calls
    const volatile long double a =
        sy * static_cast<long double>(f32(reinterpret_cast<u32>(&cosine_pitch))); //69f9
    const volatile long double cy =
        static_cast<long double>(f32(reinterpret_cast<u32>(&cosine_yaw))); //69fc
    const volatile long double b =
        cy * static_cast<long double>(f32(reinterpret_cast<u32>(&sine_pitch))); //69ff
    const volatile long double cr0 =
        static_cast<long double>(f32(reinterpret_cast<u32>(&cosine_roll))); //6a02
    const volatile long double c = cr0 * b;                                 //6a05
    const volatile long double d =
        a * static_cast<long double>(f32(slots + 12)); //6a07..6a09 actualrollsine fresh
    const volatile long double x = c + d;
    f32(output) = static_cast<float>(x); //6a0c..6a0e
    const volatile long double e =
        a * static_cast<long double>(f32(reinterpret_cast<u32>(&cosine_roll)));   //6a10..12
    const volatile long double f = b * static_cast<long double>(f32(slots + 12)); //6a15..17
    const volatile long double y = e - f;
    f32(output + 4) = static_cast<float>(y); //6a1a..1c FSUBP ST1-ST0
    const volatile long double cy1 =
        static_cast<long double>(f32(reinterpret_cast<u32>(&cosine_yaw))); //6a23
    const volatile long double g =
        cy1 * static_cast<long double>(f32(reinterpret_cast<u32>(&cosine_pitch))); //6a26
    const volatile long double sy1 =
        static_cast<long double>(f32(reinterpret_cast<u32>(&sine_yaw))); //6a29
    const volatile long double h =
        sy1 * static_cast<long double>(f32(reinterpret_cast<u32>(&sine_pitch)));  //6a2c
    const volatile long double i = g * static_cast<long double>(f32(slots + 12)); //6a2f..31
    const volatile long double j =
        h * static_cast<long double>(f32(reinterpret_cast<u32>(&cosine_roll))); //6a34..36
    const volatile long double z = i - j;
    f32(output + 8) = static_cast<float>(z);                                      //6a39..3b
    const volatile long double k = h * static_cast<long double>(f32(slots + 12)); //6a3e
    const volatile long double l =
        g * static_cast<long double>(f32(reinterpret_cast<u32>(&cosine_roll))); //6a41..43
    const volatile long double w = k + l;
    f32(output + 12) = static_cast<float>(w); //6a46..48
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6976(void*, u32, u32, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e6976\n\taddl $4,%esp\n\tretl $16");
}
