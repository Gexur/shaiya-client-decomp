#include "graphics/render_matrix_decompose.h"
#include "startup/math_dispatch_state.h"
#include "graphics/render_dispatch.h"
#include "graphics/render_quaternion_from_matrix_dispatch.h"
namespace {
using u32 = uint32_t;
u32 word(u32 address) {
    u32 value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(address) : "memory");
    return value;
}
void put(u32 address, u32 value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(address), "r"(value) : "memory");
}
void clear(u32 address) {
    __asm__ volatile("andl $0,(%0)" ::"r"(address) : "memory", "cc");
}
struct __attribute__((packed, may_alias)) FloatWord {
    float value;
};
volatile float& f32(u32 address) {
    return reinterpret_cast<volatile FloatWord*>(address)->value;
}
void copy3(u32 destination, u32 source) {
    put(destination, word(source));
    put(destination + 4, word(source + 4));
    put(destination + 8, word(source + 8));
}
long double square_root(long double value) {
    long double result;
    __asm__ volatile("fldt %1;fsqrt;fstpt %0" : "=m"(result) : "m"(value) : "st");
    return result;
}
long double absolute(long double value) {
    long double result;
    __asm__ volatile("fldt %1;fabs;fstpt %0" : "=m"(result) : "m"(value) : "st");
    return result;
}
long double negate(long double value) {
    long double result;
    __asm__ volatile("fldt %1;fchs;fstpt %0" : "=m"(result) : "m"(value) : "st");
    return result;
}
bool ordered_less(long double left, long double right) {
    uint16_t status;
    __asm__ volatile("fldt %2;fldt %1;fcompp;fnstsw %%ax"
                     : "=a"(status)
                     : "m"(left), "m"(right)
                     : "st");
    // Original TEST AH,5 / JP is the complement of this ordered-less result.
    return (status & 0x0500u) == 0x0100u;
}
long double actual_determinant(u32 matrix) {
    long double result;
    __asm__ volatile("pushl %1;calll _FUN_005e4cc0@4;fstpt %0"
                     : "=m"(result)
                     : "r"(matrix)
                     : "eax", "ecx", "edx", "cc", "memory", "st");
    return result; // Preserve the actual 80-bit ST0; no float-return conversion.
}
// Exact readonly F32 operand at006c1274, bits38d1b717. This is a private
// numeric value copy, with no canonical pool-storage/adjacency ownership claim.
constexpr float epsilon = 0x1.a36e2ep-14f;
} // namespace

extern "C" __attribute__((noinline)) u32 __cdecl recovered_005e8212(u32 slots, u32 frame) {
    // Initial original private basis writes and the two initial argument reads.
    put(frame - 12, 0x3f800000u);
    put(frame - 8, 0);
    const u32 matrix = word(slots + 12);
    const u32 translation = word(slots + 8);
    put(frame - 4, 0);
    copy3(frame - 132, frame - 12);
    put(frame - 12, 0);
    put(frame - 8, 0x3f800000u);
    put(frame - 4, 0);
    copy3(frame - 120, frame - 12);
    put(frame - 12, 0);
    put(frame - 8, 0);
    put(frame - 4, 0x3f800000u);
    put(frame - 108, word(frame - 12));
    const volatile long double translation_x = f32(matrix + 48);
    f32(translation) = static_cast<float>(translation_x); //005e826e
    const u32 translation_y = word(matrix + 52);
    put(frame - 32, 0);
    put(frame - 104, word(frame - 8));
    put(frame - 36, 0);
    put(frame - 100, word(frame - 4));
    put(frame - 40, 0);
    put(translation + 4, translation_y);
    const u32 translation_z = word(matrix + 56);
    put(frame - 44, 0);
    put(translation + 8, translation_z);
    put(frame - 60, 0);
    put(frame - 12, frame - 88);
    put(frame - 76, 0);
    put(frame - 8, frame - 72);
    put(frame - 28, 0x3f800000u);
    copy3(frame - 88, matrix);
    copy3(frame - 72, matrix + 16);
    copy3(frame - 56, matrix + 32);
    // Original005e82cd..005e8325, with each operand read kept in its order.
    const volatile long double x0 = f32(frame - 80);
    const volatile long double x1 = x0 * f32(frame - 80);
    const volatile long double x2 = f32(frame - 84);
    put(frame - 4, frame - 56);
    const volatile long double x3 = x2 * f32(frame - 84);
    const u32 scale = word(slots);
    const volatile long double x4 = x1 + x3;
    const volatile long double x5 = f32(frame - 88);
    const volatile long double x6 = x5 * f32(frame - 88);
    const volatile long double x7 = x4 + x6;
    const volatile long double sx = square_root(x7);
    f32(scale) = static_cast<float>(sx);
    const volatile long double y0 = f32(frame - 64);
    const volatile long double y1 = y0 * f32(frame - 64);
    const volatile long double y2 = f32(frame - 68);
    const volatile long double y3 = y2 * f32(frame - 68);
    const volatile long double y4 = y1 + y3;
    const volatile long double y5 = f32(frame - 72);
    const volatile long double y6 = y5 * f32(frame - 72);
    const volatile long double y7 = y4 + y6;
    const volatile long double sy = square_root(y7);
    f32(slots + 8) = static_cast<float>(sy);
    f32(scale + 4) = static_cast<float>(sy);
    const volatile long double z0 = f32(frame - 48);
    const volatile long double z1 = z0 * f32(frame - 48);
    const volatile long double z2 = f32(frame - 52);
    const volatile long double z3 = z2 * f32(frame - 52);
    const volatile long double z4 = z1 + z3;
    const volatile long double z5 = f32(frame - 56);
    const volatile long double z6 = z5 * f32(frame - 56);
    const volatile long double z7 = z4 + z6;
    const volatile long double sz = square_root(z7);
    f32(slots + 12) = static_cast<float>(sz);
    const bool xy_less = ordered_less(sx, sy);
    put(scale + 8, word(slots + 12));
    u32 primary;
    if (xy_less) {
        if (ordered_less(sy, static_cast<long double>(f32(slots + 12)))) {
            clear(slots + 8);
            primary = 2;
            put(slots + 12, 1);
        } else {
            const bool xz_less = ordered_less(sx, static_cast<long double>(f32(slots + 12)));
            primary = 1;
            if (xz_less) {
                clear(slots + 8);
                put(slots + 12, 2);
            } else {
                clear(slots + 12);
                put(slots + 8, 2);
            }
        }
    } else {
        if (ordered_less(sx, static_cast<long double>(f32(slots + 12)))) {
            clear(slots + 12);
            primary = 2;
            put(slots + 8, 1);
        } else {
            const volatile long double rounded_y = f32(slots + 8);
            const volatile long double rounded_z = f32(slots + 12);
            const bool yz_less = ordered_less(rounded_y, rounded_z);
            primary = 0;
            if (yz_less) {
                put(slots + 12, 2);
                put(slots + 8, 1);
            } else {
                put(slots + 8, 2);
                put(slots + 12, 1);
            }
        }
    }
    const u32 primary_offset = primary << 2;
    const u32 primary_scale = scale + primary_offset;
    const volatile long double primary_length = f32(primary_scale);
    put(frame - 92, primary_scale);
    if (ordered_less(primary_length, static_cast<long double>(epsilon))) {
        const u32 row = word(frame + primary_offset - 12);
        copy3(row, frame + primary * 12 - 132);
    }
    u32 bx = frame + primary_offset - 12;
    u32 selected = word(bx);
    FUN_005e40eb(reinterpret_cast<float*>(selected), reinterpret_cast<const float*>(selected));
    u32 secondary_offset = word(slots + 12) << 2;
    u32 ax = word(slots);
    const volatile long double secondary_length = f32(ax + secondary_offset);
    if (ordered_less(secondary_length, static_cast<long double>(epsilon))) {
        const u32 first = word(bx);
        const volatile long double abs_x = absolute(static_cast<long double>(f32(first)));
        const volatile long double abs_y = absolute(static_cast<long double>(f32(first + 4)));
        f32(frame - 96) = static_cast<float>(abs_y);
        const volatile long double abs_z = absolute(static_cast<long double>(f32(first + 8)));
        f32(slots + 12) = static_cast<float>(abs_z);
        u32 basis;
        if (ordered_less(abs_x, abs_y)) {
            if (ordered_less(abs_y, static_cast<long double>(f32(slots + 12))))
                basis = 0;
            else if (ordered_less(abs_x, static_cast<long double>(f32(slots + 12))))
                basis = 0;
            else
                basis = 2;
        } else {
            if (ordered_less(abs_x, static_cast<long double>(f32(slots + 12))))
                basis = 1;
            else {
                const volatile long double rounded_y = f32(frame - 96);
                const volatile long double rounded_z = f32(slots + 12);
                basis = ordered_less(rounded_y, rounded_z) ? 1 : 2;
            }
        }
        const u32 unit = frame + basis * 12 - 132;
        // Original005e8475..005e84a8; row lookup lies between the first two FP reads.
        const volatile long double c0 = f32(unit + 8);
        const u32 row = word(frame + secondary_offset - 12);
        const volatile long double c1 = c0 * f32(first + 4);
        const volatile long double c2 = f32(first + 8);
        const volatile long double c3 = c2 * f32(unit + 4);
        const volatile long double c4 = c1 - c3;
        f32(frame - 24) = static_cast<float>(c4);
        const volatile long double c5 = f32(first + 8);
        const volatile long double c6 = c5 * f32(unit);
        const volatile long double c7 = f32(first);
        const volatile long double c8 = c7 * f32(unit + 8);
        const volatile long double c9 = c6 - c8;
        f32(frame - 20) = static_cast<float>(c9);
        const volatile long double c10 = f32(first);
        const volatile long double c11 = c10 * f32(unit + 4);
        const volatile long double c12 = f32(unit);
        const volatile long double c13 = c12 * f32(first + 4);
        const volatile long double c14 = c11 - c13;
        f32(frame - 16) = static_cast<float>(c14);
        copy3(row, frame - 24);
    }
    const u32 secondary_slot = frame + secondary_offset - 12;
    selected = word(secondary_slot);
    FUN_005e40eb(reinterpret_cast<float*>(selected), reinterpret_cast<const float*>(selected));
    const u32 last_offset = word(slots + 8) << 2;
    ax = word(slots);
    const volatile long double last_length = f32(ax + last_offset);
    if (ordered_less(last_length, static_cast<long double>(epsilon))) {
        const u32 second = word(secondary_slot);
        const u32 first = word(bx);
        const volatile long double c0 = f32(second + 8);
        const volatile long double c1 = c0 * f32(first + 4);
        const u32 row = word(frame + last_offset - 12);
        const volatile long double c2 = f32(first + 8);
        const volatile long double c3 = c2 * f32(second + 4);
        const volatile long double c4 = c1 - c3;
        f32(frame - 24) = static_cast<float>(c4);
        const volatile long double c5 = f32(second);
        const volatile long double c6 = c5 * f32(first + 8);
        const volatile long double c7 = f32(second + 8);
        const volatile long double c8 = c7 * f32(first);
        const volatile long double c9 = c6 - c8;
        f32(frame - 20) = static_cast<float>(c9);
        const volatile long double c10 = f32(second + 4);
        const volatile long double c11 = c10 * f32(first);
        const volatile long double c12 = f32(second);
        const volatile long double c13 = c12 * f32(first + 4);
        const volatile long double c14 = c11 - c13;
        f32(frame - 16) = static_cast<float>(c14);
        copy3(row, frame - 24);
    }
    selected = word(frame + last_offset - 12);
    FUN_005e40eb(reinterpret_cast<float*>(selected), reinterpret_cast<const float*>(selected));
    volatile long double det = actual_determinant(frame - 88);
    if (ordered_less(det, 0.0L)) {
        const u32 scale_word = word(frame - 92);
        const volatile long double scale_value = f32(scale_word);
        bx = word(bx);
        f32(scale_word) = static_cast<float>(negate(scale_value));
        const volatile long double n0 = negate(static_cast<long double>(f32(bx)));
        f32(frame - 24) = static_cast<float>(n0);
        const volatile long double n1 = negate(static_cast<long double>(f32(bx + 4)));
        f32(frame - 20) = static_cast<float>(n1);
        const volatile long double n2 = negate(static_cast<long double>(f32(bx + 8)));
        f32(frame - 16) = static_cast<float>(n2);
        put(bx, word(frame - 24));
        put(bx + 4, word(frame - 20));
        det = negate(det);
        put(bx + 8, word(frame - 16));
    }
    const volatile long double delta = det - 1.0L;
    const volatile long double squared = delta * delta;
    if (ordered_less(static_cast<long double>(epsilon), squared))
        return 0x8876086cu;
    const u32 rotation = word(slots + 4);
    FUN_005e6783(reinterpret_cast<void*>(rotation), reinterpret_cast<const void*>(frame - 88));
    const volatile long double w = f32(rotation + 12);
    f32(rotation + 12) = static_cast<float>(negate(w));
    return 0;
}

extern "C" __attribute__((naked, stdcall)) u32 FUN_005e8212(void*, void*, void*, const void*) {
    // Actual132-byte original frame exists before any helper outgoing arguments.
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $132,%esp\n\tpushl %esi\n\tpushl %edi\n\tpushl %ebp\n\tleal 8(%ebp),%eax\n\tpushl %eax\n\tcalll _recovered_005e8212\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tleave\n\tretl $16");
}
extern "C" __attribute__((naked, stdcall)) u32 FUN_005e4d92(void*, void*, void*, const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+48");
}
