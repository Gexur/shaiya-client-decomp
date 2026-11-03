#include "graphics/render_quaternion_from_matrix_alternate.h"
// Exact12-byte original readonly index vector; no following pool bytes are owned.
extern "C" const uint32_t dat_006f39a0[3] = {1, 2, 0};
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
// Complete original683f9f..6840cb. Full107-instruction comparison proves the
// same x87 control/data flow as6802a2, with only its two index-data operands
// relocated to original6f39a0. No original body is aliased at runtime.
extern "C" void* recovered_00683f9f(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments), matrix = word(slots + 4);
    const volatile long double yy = static_cast<long double>(f32(matrix + 20));
    const volatile long double yx = yy + static_cast<long double>(f32(matrix));
    const volatile long double trace = yx + static_cast<long double>(f32(matrix + 40));
    if (!(compare(trace, zero) & 0x4100u)) {
        const volatile long double sum = trace + 1.0L;
        const u32 output = word(slots);
        const volatile long double squared_root = root(sum);
        const volatile long double scale = squared_root * 0.5L;
        f32(output + 12) = static_cast<float>(scale);
        const volatile long double factor = 0.25L / scale;
        const volatile long double x0 = static_cast<long double>(f32(matrix + 24));
        const volatile long double x1 = x0 - static_cast<long double>(f32(matrix + 36));
        const volatile long double x2 = x1 * factor;
        f32(output) = static_cast<float>(x2);
        const volatile long double y0 = static_cast<long double>(f32(matrix + 32));
        const volatile long double y1 = y0 - static_cast<long double>(f32(matrix + 8));
        const volatile long double y2 = y1 * factor;
        f32(output + 4) = static_cast<float>(y2);
        const volatile long double z0 = static_cast<long double>(f32(matrix + 4));
        const volatile long double z1 = z0 - static_cast<long double>(f32(matrix + 16));
        const volatile long double z2 = z1 * factor;
        f32(output + 8) = static_cast<float>(z2);
        return reinterpret_cast<void*>(output);
    }
    volatile float diagonal[3];
    const u32 raw_y = word(matrix + 20);
    const volatile long double xx = static_cast<long double>(f32(matrix));
    put(reinterpret_cast<u32>(&diagonal[1]), raw_y);
    const u32 raw_z = word(matrix + 40);
    diagonal[0] = static_cast<float>(xx);
    const u32 status_xy = compare(xx, diagonal[1]);
    put(reinterpret_cast<u32>(&diagonal[2]), raw_z);
    u32 index = (status_xy & 0x100u) ? 1u : 0u;
    const volatile long double selected = static_cast<long double>(diagonal[index]);
    put(slots + 4, index);
    if (compare(selected, diagonal[2]) & 0x100u) {
        index = 2;
        put(slots + 4, index);
    }
    u32 offset = index << 2;
    const u32 adjacent = word(reinterpret_cast<u32>(dat_006f39a0) + offset);
    const volatile long double selected_again = static_cast<long double>(diagonal[index]);
    u32 adjacent_offset = adjacent << 2;
    const volatile long double subtract_adjacent =
        selected_again - static_cast<long double>(diagonal[adjacent]);
    const u32 last = word(reinterpret_cast<u32>(dat_006f39a0) + adjacent_offset);
    const volatile long double subtract_last =
        subtract_adjacent - static_cast<long double>(diagonal[last]);
    const u32 output = word(slots);
    u32 first_index = index + adjacent_offset;
    const volatile long double sum = subtract_last + 1.0L;
    u32 second_index = adjacent + offset;
    const volatile long double squared_root = root(sum);
    const volatile long double scale = squared_root * 0.5L;
    f32(output + offset) = static_cast<float>(scale);
    const volatile long double factor = 0.25L / scale;
    const volatile long double a0 = static_cast<long double>(f32(matrix + first_index * 4));
    const volatile long double a1 = a0 + static_cast<long double>(f32(matrix + second_index * 4));
    first_index = word(slots + 4);
    const u32 last_offset = last << 2;
    first_index += last_offset;
    const volatile long double a2 = a1 * factor;
    offset += last;
    f32(output + adjacent_offset) = static_cast<float>(a2);
    adjacent_offset += last;
    const volatile long double b0 = static_cast<long double>(f32(matrix + first_index * 4));
    const volatile long double b1 = b0 + static_cast<long double>(f32(matrix + offset * 4));
    const volatile long double b2 = b1 * factor;
    f32(output + last_offset) = static_cast<float>(b2);
    const volatile long double w0 = static_cast<long double>(f32(matrix + adjacent_offset * 4));
    const volatile long double w1 =
        w0 - static_cast<long double>(f32(matrix + (last_offset + adjacent) * 4));
    const volatile long double w2 = w1 * factor;
    f32(output + 12) = static_cast<float>(w2);
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00683f9f(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00683f9f\n\taddl $4,%esp\n\tretl $8");
}
