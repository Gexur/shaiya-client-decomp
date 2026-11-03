#include "graphics/render_affine_matrices.h"
#include "graphics/render_matrix_pair.h"
#include "graphics/render_matrix_rotations.h"
#include "graphics/render_rotation_axis_dispatch.h"
#include "graphics/render_packed_trig_quaternions.h"
#include "startup/math_dispatch_state.h"
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
void diagonal3(u32 input, u32 output) {
    __asm__ volatile("flds (%0)\n\tfsts (%1)\n\tfsts 20(%1)\n\tfstps 40(%1)" ::"r"(input),
                     "r"(output)
                     : "st", "memory");
}
void diagonal2(u32 input, u32 output) {
    __asm__ volatile("flds (%0)\n\tfsts (%1)\n\tfstps 20(%1)" ::"r"(input), "r"(output)
                     : "st", "memory");
}
uint16_t angle_status(u32 p) {
    uint16_t status;
    __asm__ volatile("flds (%1)\n\tflds %2\n\tfucompp\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "r"(p), "m"(dat_006bb5fc)
                     : "st", "st(1)", "memory");
    return status;
}
void rounded(u32 input, u32 output) {
    __asm__ volatile("flds (%0)\n\tfstps (%1)" ::"r"(input), "r"(output) : "st", "memory");
}
void add(u32 output, u32 left, u32 right) {
    const volatile long double a = f32(left);
    const volatile long double b = f32(right);
    const volatile long double result = a + b;
    f32(output) = static_cast<float>(result);
}
void sub(u32 output, u32 left, u32 right) {
    const volatile long double a = f32(left);
    const volatile long double b = f32(right);
    const volatile long double result = a - b;
    f32(output) = static_cast<float>(result);
}
void multiply(u32 output, u32 matrix) {
    FUN_005e4db8(reinterpret_cast<D3DMATRIX*>(output), reinterpret_cast<const D3DMATRIX*>(output),
                 reinterpret_cast<const D3DMATRIX*>(matrix));
}
} // namespace
// Complete original005e6267; fresh argument timing and asymmetric FP operand reads retained.
extern "C" u32 recovered_affine_005e6267(u32 slots) {
    const bool rotation_present = word(slots + 12) != 0; // original626b, before output loads/stores
    const u32 output = word(slots);
    zero(output + 56);
    zero(output + 52);
    zero(output + 48);
    zero(output + 44);
    zero(output + 36);
    zero(output + 32);
    zero(output + 28);
    zero(output + 24);
    zero(output + 16);
    zero(output + 12);
    zero(output + 8);
    zero(output + 4);
    diagonal3(slots + 4, output);
    one(output + 60);
    if (rotation_present) {
        alignas(16) u32 matrix[16];
        const u32 temporary = reinterpret_cast<u32>(matrix);
        const u32 quaternion = word(slots + 12);
        FUN_005e5ad9(matrix, reinterpret_cast<const void*>(quaternion));
        const u32 center = word(slots + 8);
        if (center) {
            sub(output + 48, output + 48, center + 0);
            sub(output + 52, output + 52, center + 4);
            sub(output + 56, output + 56, center + 8);
            multiply(output, temporary);
            add(output + 48, center + 0, output + 48);
            add(output + 52, output + 52, center + 4);
            add(output + 56, center + 8, output + 56);
        } else
            multiply(output, temporary);
    }
    const u32 translation = word(slots + 16);
    if (translation) {
        add(output + 48, translation + 0, output + 48);
        add(output + 52, translation + 4, output + 52);
        add(output + 56, translation + 8, output + 56);
    }
    return output;
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6267(void*, u32, const void*, const void*,
                                                              const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_affine_005e6267\n\taddl $4,%esp\n\tretl $20");
}
// Complete original005e6384; fresh argument timing and asymmetric FP operand reads retained.
extern "C" u32 recovered_affine_005e6384(u32 slots) {
    const u32 output = word(slots);
    zero(output + 56);
    zero(output + 52);
    zero(output + 48);
    zero(output + 44);
    zero(output + 36);
    zero(output + 32);
    zero(output + 28);
    zero(output + 24);
    zero(output + 16);
    zero(output + 12);
    zero(output + 8);
    zero(output + 4);
    diagonal2(slots + 4, output);
    one(output + 40);
    one(output + 60);
    const uint16_t status = angle_status(slots + 12);
    const u32 tested = status & 0x4400u;
    if (tested == 0 || tested == 0x4400u) { // actual TEST AH44/JNP: unequal or unordered
        alignas(16) u32 matrix[16];
        const u32 temporary = reinterpret_cast<u32>(matrix);
        u32 angle;
        rounded(slots + 12, reinterpret_cast<u32>(&angle));
        FUN_005e5918(matrix, angle);
        const u32 center = word(slots + 8);
        if (center) {
            sub(output + 48, output + 48, center + 0);
            sub(output + 52, output + 52, center + 4);
            multiply(output, temporary);
            add(output + 48, center + 0, output + 48);
            add(output + 52, output + 52, center + 4);
        } else
            multiply(output, temporary);
    }
    const u32 translation = word(slots + 16);
    if (translation) {
        add(output + 48, translation + 0, output + 48);
        add(output + 52, translation + 4, output + 52);
    }
    return output;
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6384(void*, u32, const void*, u32,
                                                              const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_affine_005e6384\n\taddl $4,%esp\n\tretl $20");
}
// Complete original623e/6357 ABI wrappers: real F32 outgoing conversions,
// argument-copy order and indirect CALL are retained, including incoming aliases.
extern "C" __attribute__((naked, stdcall)) void* FUN_005e623e(void*, u32, const void*, const void*,
                                                              const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tflds 12(%ebp)\n\tpushl 24(%ebp)\n\tpushl 20(%ebp)\n\tpushl 16(%ebp)\n\tpushl %ecx\n\tfstps (%esp)\n\tpushl 8(%ebp)\n\tcalll *_dat_0070f370+168\n\tpopl %ebp\n\tretl $20");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6357(void*, u32, const void*, u32,
                                                              const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tflds 20(%ebp)\n\tpushl 24(%ebp)\n\tpushl %ecx\n\tfstps (%esp)\n\tpushl 16(%ebp)\n\tflds 12(%ebp)\n\tpushl %ecx\n\tfstps (%esp)\n\tpushl 8(%ebp)\n\tcalll *_dat_0070f370+292\n\tpopl %ebp\n\tretl $20");
}
