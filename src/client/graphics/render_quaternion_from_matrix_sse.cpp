#include "graphics/render_quaternion_from_matrix_sse.h"
// Exact12-byte readonly index vector; next pool word at6f391c is unowned here.
extern "C" const uint32_t dat_006f3910[3] = {1, 2, 0};
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
const float zero = 0.0f;
u32 compare(const volatile long double& left, const volatile float& right) {
    uint16_t status;
    __asm__ volatile("fldt %1\n\tfcomps %2\n\tfnstsw %0"
                     : "=a"(status)
                     : "m"(left), "m"(right)
                     : "st", "memory");
    return status;
}
long double root(const volatile long double& value) {
    long double result;
    __asm__ volatile("fldt %1\n\tfsqrt\n\tfstpt %0" : "=m"(result) : "m"(value) : "st", "memory");
    return result;
}
} // namespace
// Backend selected by the original SSE patcher, but this300-byte body uses
// x87 arithmetic. In particular its negative-trace choice uses raw diagonal
// entries, unlike original6789's rounded derived minors. No body is aliased.
extern "C" void* recovered_006802a2(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments), matrix = word(slots + 4);       //02aa
    const volatile long double yy = static_cast<long double>(f32(matrix + 20));         //02ad
    const volatile long double yx = yy + static_cast<long double>(f32(matrix));         //02b0
    const volatile long double trace = yx + static_cast<long double>(f32(matrix + 40)); //02b2
    if (!(compare(trace, zero) & 0x4100u)) {
        const volatile long double sum = trace + 1.0L;                                   //02c2
        const u32 output = word(slots);                                                  //02c8
        const volatile long double squared_root = root(sum);                             //02cb
        const volatile long double scale = squared_root * 0.5L;                          //02cd
        f32(output + 12) = static_cast<float>(scale);                                    //02d5
        const volatile long double factor = 0.25L / scale;                               //02d8
        const volatile long double x0 = static_cast<long double>(f32(matrix + 24));      //02de
        const volatile long double x1 = x0 - static_cast<long double>(f32(matrix + 36)); //02e1
        const volatile long double x2 = x1 * factor;
        f32(output) = static_cast<float>(x2);                                           //02e4..e6
        const volatile long double y0 = static_cast<long double>(f32(matrix + 32));     //02e8
        const volatile long double y1 = y0 - static_cast<long double>(f32(matrix + 8)); //02eb
        const volatile long double y2 = y1 * factor;
        f32(output + 4) = static_cast<float>(y2);                                        //02ee..f0
        const volatile long double z0 = static_cast<long double>(f32(matrix + 4));       //02f3
        const volatile long double z1 = z0 - static_cast<long double>(f32(matrix + 16)); //02f6
        const volatile long double z2 = z1 * factor;
        f32(output + 8) = static_cast<float>(z2); //02f9..fb
        return reinterpret_cast<void*>(output);
    }
    volatile float diagonal[3];
    const u32 raw_y = word(matrix + 20);                                   //0303
    const volatile long double xx = static_cast<long double>(f32(matrix)); //0308
    put(reinterpret_cast<u32>(&diagonal[1]), raw_y);                       //030a
    const u32 raw_z = word(matrix + 40);                                   //030d
    diagonal[0] = static_cast<float>(xx);            //0310 FST retains extended x
    const u32 status_xy = compare(xx, diagonal[1]);  //0313
    put(reinterpret_cast<u32>(&diagonal[2]), raw_z); //0317
    u32 index = (status_xy & 0x100u) ? 1u : 0u;      //031b..0325
    const volatile long double selected = static_cast<long double>(diagonal[index]); //0326
    put(slots + 4, index);                                                           //032a
    if (compare(selected, diagonal[2]) & 0x100u) {
        index = 2;
        put(slots + 4, index);
    } //032d..033a
    u32 offset = index << 2;                                                 //033d..033f
    const u32 adjacent = word(reinterpret_cast<u32>(dat_006f3910) + offset); //0342
    const volatile long double selected_again = static_cast<long double>(diagonal[index]); //0348
    u32 adjacent_offset = adjacent << 2; //034c..034e
    const volatile long double subtract_adjacent =
        selected_again - static_cast<long double>(diagonal[adjacent]);            //0351
    const u32 last = word(reinterpret_cast<u32>(dat_006f3910) + adjacent_offset); //0355
    const volatile long double subtract_last =
        subtract_adjacent - static_cast<long double>(diagonal[last]);                        //0361
    const u32 output = word(slots);                                                          //0365
    u32 first_index = index + adjacent_offset;                                               //0368
    const volatile long double sum = subtract_last + 1.0L;                                   //036d
    u32 second_index = adjacent + offset;                                                    //0373
    const volatile long double squared_root = root(sum);                                     //0375
    const volatile long double scale = squared_root * 0.5L;                                  //0377
    f32(output + offset) = static_cast<float>(scale);                                        //037f
    const volatile long double factor = 0.25L / scale;                                       //0382
    const volatile long double a0 = static_cast<long double>(f32(matrix + first_index * 4)); //0388
    const volatile long double a1 =
        a0 + static_cast<long double>(f32(matrix + second_index * 4)); //038b
    first_index = word(slots + 4);                                     //038e fresh actual index
    const u32 last_offset = last << 2;                                 //0391..0394
    first_index += last_offset;                                        //0397
    const volatile long double a2 = a1 * factor;                       //039c
    offset += last;                                                    //039e
    f32(output + adjacent_offset) = static_cast<float>(a2);            //03a0
    adjacent_offset += last;                                           //03a3
    const volatile long double b0 = static_cast<long double>(f32(matrix + first_index * 4)); //03a5
    const volatile long double b1 = b0 + static_cast<long double>(f32(matrix + offset * 4)); //03a8
    const volatile long double b2 = b1 * factor;                                             //03b3
    f32(output + last_offset) = static_cast<float>(b2);                                      //03b5
    const volatile long double w0 =
        static_cast<long double>(f32(matrix + adjacent_offset * 4)); //03ba
    const volatile long double w1 =
        w0 - static_cast<long double>(f32(matrix + (last_offset + adjacent) * 4)); //03be
    const volatile long double w2 = w1 * factor;                                   //03c3
    f32(output + 12) = static_cast<float>(w2);                                     //03c5
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_006802a2(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_006802a2\n\taddl $4,%esp\n\tretl $8");
}
