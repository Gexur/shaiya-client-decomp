#include "graphics/render_quaternion_from_matrix.h"
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
// Readonly source words6bb5fc=0,6bc4dc=1,6bc860=.5,6bfe14=.25.
// Ordinary value copies, with no canonical pool/storage ownership claim.
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
// Complete original5e6789..5e68bf; actual argument writes remain observable.
extern "C" void* recovered_005e6789(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments), matrix = word(slots + 4);       //6791
    const volatile long double yy = static_cast<long double>(f32(matrix + 20));         //6794
    const volatile long double xy = yy + static_cast<long double>(f32(matrix));         //6797
    const volatile long double trace = xy + static_cast<long double>(f32(matrix + 40)); //6799
    if (!(compare(trace, zero) & 0x4100u)) {                                            //679c..67a7
        const volatile long double sum = trace + 1.0L;                                  //67a9
        const u32 output = word(slots);                                                 //67af
        const volatile long double squared_root = root(sum);                            //67b2
        const volatile long double scale = squared_root * 0.5L;                         //67b4
        f32(output + 12) = static_cast<float>(scale);                                   //67bc
        const volatile long double factor = 0.25L / scale;                              //67bf
        const volatile long double x0 = static_cast<long double>(f32(matrix + 24));     //67c5
        const volatile long double x1 = x0 - static_cast<long double>(f32(matrix + 36)); //67c8
        const volatile long double x2 = x1 * factor;                                     //67cb
        f32(output) = static_cast<float>(x2);                                            //67cd
        const volatile long double y0 = static_cast<long double>(f32(matrix + 32));      //67cf
        const volatile long double y1 = y0 - static_cast<long double>(f32(matrix + 8));  //67d2
        const volatile long double y2 = y1 * factor;                                     //67d5
        f32(output + 4) = static_cast<float>(y2);                                        //67d7
        const volatile long double z0 = static_cast<long double>(f32(matrix + 4));       //67da
        const volatile long double z1 = z0 - static_cast<long double>(f32(matrix + 16)); //67dd
        const volatile long double z2 = z1 * factor;                                     //67e0
        f32(output + 8) = static_cast<float>(z2);                                        //67e2
        return reinterpret_cast<void*>(output);
    }
    const u32 next[3] = {1, 2, 0}; //original private1/2/0 DWORD permutation
    volatile float diagonal[3];
    const volatile long double xx = static_cast<long double>(f32(matrix));                 //67f0
    const volatile long double xx_y = xx - static_cast<long double>(f32(matrix + 20));     //67f3
    const volatile long double xx_y_z = xx_y - static_cast<long double>(f32(matrix + 40)); //67fa
    diagonal[0] = static_cast<float>(xx_y_z); //6801 FST; extended value survives
    const volatile long double yy0 = static_cast<long double>(f32(matrix + 20));           //6807
    const volatile long double yy_x = yy0 - static_cast<long double>(f32(matrix));         //680d
    const volatile long double yy_x_z = yy_x - static_cast<long double>(f32(matrix + 40)); //680f
    diagonal[1] = static_cast<float>(yy_x_z);                                              //6812
    const volatile long double yx0 = static_cast<long double>(f32(matrix + 20));           //6815
    const volatile long double yx1 = yx0 + static_cast<long double>(f32(matrix));          //6818
    const volatile long double zz_y_x =
        static_cast<long double>(f32(matrix + 40)) - yx1;                            //681a FSUBR
    diagonal[2] = static_cast<float>(zz_y_x);                                        //681d
    u32 index = (compare(xx_y_z, diagonal[1]) & 0x100u) ? 1u : 0u;                   //6820..6829
    const volatile long double selected = static_cast<long double>(diagonal[index]); //682b
    put(slots + 4, index);                                                           //682f
    if (compare(selected, diagonal[2]) & 0x100u) {
        index = 2;
        put(slots + 4, index);
    } //6832..683e
    u32 offset = index << 2;                                                       //6841..6843
    const volatile long double chosen = static_cast<long double>(diagonal[index]); //6846
    const u32 adjacent = next[index];                                              //684a
    const volatile long double chosen_sum = chosen + 1.0L;                         //684e
    const u32 output = word(slots);                                                //6854
    u32 adjacent_offset = adjacent << 2;                                           //6857..6859
    const volatile long double squared_root = root(chosen_sum);                    //685c
    u32 first_index = index + adjacent_offset;                                     //685e
    u32 second_index = adjacent + offset;                                          //6863
    const volatile long double scale = squared_root * 0.5L;                        //6865
    f32(output + offset) = static_cast<float>(scale);                              //686d
    const volatile long double factor = 0.25L / scale;                             //6870
    const volatile long double a0 = static_cast<long double>(f32(matrix + first_index * 4)); //6876
    const volatile long double a1 =
        a0 + static_cast<long double>(f32(matrix + second_index * 4)); //6879
    first_index = word(slots + 4);               //687c: actual selected-index word reload
    const u32 last = next[adjacent];             //687f
    u32 last_offset = last << 2;                 //6883
    first_index += last_offset;                  //6886
    const volatile long double a2 = a1 * factor; //6888
    put(slots, last_offset);                     //688a: actual output-word becomes byte offset
    f32(output + adjacent_offset) = static_cast<float>(a2);                                  //6891
    offset += last;                                                                          //6894
    const volatile long double b0 = static_cast<long double>(f32(matrix + first_index * 4)); //6896
    adjacent_offset += last;                                                                 //6899
    const volatile long double b1 = b0 + static_cast<long double>(f32(matrix + offset * 4)); //689b
    last_offset = word(slots);                          //689e: actual offset word reload
    const volatile long double b2 = b1 * factor;        //68a4
    f32(output + last_offset) = static_cast<float>(b2); //68a6
    last_offset += adjacent;                            //68a9
    const volatile long double w0 =
        static_cast<long double>(f32(matrix + adjacent_offset * 4)); //68ab
    const volatile long double w1 =
        w0 - static_cast<long double>(f32(matrix + last_offset * 4)); //68af
    const volatile long double w2 = w1 * factor;                      //68b4
    f32(output + 12) = static_cast<float>(w2);                        //68b6
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6789(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e6789\n\taddl $4,%esp\n\tretl $8");
}
