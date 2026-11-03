#include "graphics/render_matrix_transformations.h"
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
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void zero(u32 p) {
    __asm__ volatile("fldz\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
void one(u32 p) {
    __asm__ volatile("fld1\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
void negative(u32 output, u32 input) {
    __asm__ volatile("flds (%1)\n\tfchs\n\tfstps (%0)" ::"r"(output), "r"(input) : "st", "memory");
}
void add(u32 output, u32 left, u32 right) {
    __asm__ volatile("flds (%1)\n\tfadds (%2)\n\tfstps (%0)" ::"r"(output), "r"(left), "r"(right)
                     : "st", "memory");
}
void sub(u32 output, u32 left, u32 right) {
    __asm__ volatile("flds (%1)\n\tfsubs (%2)\n\tfstps (%0)" ::"r"(output), "r"(left), "r"(right)
                     : "st", "memory");
}
void one_minus_times(u32 output, u32 scale, u32 center) {
    __asm__ volatile("fld1\n\tfsubs (%1)\n\tfmuls (%2)\n\tfstps (%0)" ::"r"(output), "r"(scale),
                     "r"(center)
                     : "st", "memory");
}
u32 rounded(u32 input) {
    u32 v;
    __asm__ volatile("flds (%1)\n\tfstps %0" : "=m"(v) : "r"(input) : "st", "memory");
    return v;
}
bool unequal_angle(u32 input) {
    uint16_t sw;
    __asm__ volatile("flds (%1)\n\tflds %2\n\tfucompp\n\tfnstsw %%ax"
                     : "=a"(sw)
                     : "r"(input), "m"(dat_006bb5fc)
                     : "st", "st(1)", "memory");
    const u32 tested = sw & 0x4400u;
    return tested == 0 || tested == 0x4400u;
}
void multiply(u32 output, u32 matrix) {
    FUN_005e4db8(reinterpret_cast<D3DMATRIX*>(output), reinterpret_cast<const D3DMATRIX*>(output),
                 reinterpret_cast<const D3DMATRIX*>(matrix));
}
void transpose(u32 output, u32 matrix) {
    FUN_005e5009(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(matrix));
}
void zeros12(u32 p) {
    zero(p + 56);
    zero(p + 52);
    zero(p + 48);
    zero(p + 44);
    zero(p + 36);
    zero(p + 32);
    zero(p + 28);
    zero(p + 24);
    zero(p + 16);
    zero(p + 12);
    zero(p + 8);
    zero(p + 4);
}
void zeros9(u32 p) {
    zero(p + 44);
    zero(p + 36);
    zero(p + 32);
    zero(p + 28);
    zero(p + 24);
    zero(p + 16);
    zero(p + 12);
    zero(p + 8);
    zero(p + 4);
}
void identity(u32 p) {
    zeros12(p);
    one(p + 60);
    one(p + 40);
    one(p + 20);
    one(p);
}
} // namespace

// Complete005e5c06..005e5f12. Actual original three independent64B matrix
// spans are retained; no additional original frame bytes are initialized.
extern "C" u32 recovered_transform_005e5c06(u32 slots) {
    alignas(16) u32 private_matrices[48];
    const u32 frame = reinterpret_cast<u32>(private_matrices) + 192;
    const u32 scale_matrix = frame - 64, rotation = frame - 128, transposed = frame - 192;
    const u32 scale = word(slots + 12);
    u32 output;
    if (scale) {
        if (word(slots + 8)) {
            zero(frame - 8);
            const u32 sx = word(scale);
            const u32 scale_orientation = word(slots + 8);
            zero(frame - 12);
            put(frame - 64, sx);
            zero(frame - 16);
            const u32 sy = word(scale + 4);
            zero(frame - 20);
            const u32 sz = word(scale + 8);
            put(frame - 24, sz);
            zero(frame - 28);
            put(frame - 44, sy);
            zero(frame - 32);
            zero(frame - 36);
            zero(frame - 40);
            zero(frame - 48);
            zero(frame - 52);
            zero(frame - 56);
            zero(frame - 60);
            one(frame - 4);
            FUN_005e5ad9(reinterpret_cast<void*>(rotation),
                         reinterpret_cast<const void*>(scale_orientation));
            const u32 center = word(slots + 4);
            if (center) {
                transpose(transposed, rotation);
                output = word(slots);
                identity(output);
                negative(output + 48, center);
                negative(output + 52, center + 4);
                negative(output + 56, center + 8);
                multiply(output, transposed);
                multiply(output, scale_matrix);
                multiply(output, rotation);
                add(output + 48, output + 48, center);
                add(output + 52, center + 4, output + 52);
                add(output + 56, output + 56, center + 8);
            } else {
                output = word(slots);
                transpose(output, rotation);
                multiply(output, scale_matrix);
                multiply(output, rotation);
            }
        } else {
            const u32 center = word(slots + 4);
            output = word(slots);
            if (center) {
                zeros9(output);
                put(output, word(scale));
                put(output + 20, word(scale + 4));
                put(output + 40, word(scale + 8));
                one_minus_times(output + 48, scale, center);
                one_minus_times(output + 52, scale + 4, center + 4);
                one_minus_times(output + 56, scale + 8, center + 8);
                one(output + 60);
            } else {
                zeros12(output);
                put(output, word(scale));
                put(output + 20, word(scale + 4));
                put(output + 40, word(scale + 8));
                one(output + 60);
            }
        }
    } else {
        output = word(slots);
        identity(output);
    }
    if (word(slots + 20)) {
        const u32 quaternion = word(slots + 20);
        FUN_005e5ad9(reinterpret_cast<void*>(rotation), reinterpret_cast<const void*>(quaternion));
        const u32 center = word(slots + 16);
        if (center) {
            sub(output + 48, output + 48, center);
            sub(output + 52, output + 52, center + 4);
            sub(output + 56, output + 56, center + 8);
            multiply(output, rotation);
            add(output + 48, output + 48, center);
            add(output + 52, output + 52, center + 4);
            add(output + 56, output + 56, center + 8);
        } else
            multiply(output, rotation);
    }
    const u32 translation = word(slots + 24);
    if (translation) {
        add(output + 48, output + 48, translation);
        add(output + 52, translation + 4, output + 52);
        add(output + 56, translation + 8, output + 56);
    }
    return output;
}

// Complete005e5f45..005e623e. Both original angle tests retain FUCOMPP/TEST
// parity (including NaNs), followed by separately reloaded rounded arguments.
extern "C" u32 recovered_transform_005e5f45(u32 slots) {
    alignas(16) u32 private_matrices[48];
    const u32 frame = reinterpret_cast<u32>(private_matrices) + 192;
    const u32 scale_matrix = frame - 64, rotation = frame - 128, transposed = frame - 192;
    const u32 scale = word(slots + 12);
    u32 output;
    if (scale) {
        if (unequal_angle(slots + 8)) {
            zero(frame - 8);
            const u32 sx = word(scale);
            put(frame - 64, sx);
            zero(frame - 12);
            const u32 sy = word(scale + 4);
            zero(frame - 16);
            put(frame - 44, sy);
            zero(frame - 20);
            zero(frame - 28);
            zero(frame - 32);
            zero(frame - 36);
            zero(frame - 40);
            zero(frame - 48);
            zero(frame - 52);
            zero(frame - 56);
            zero(frame - 60);
            one(frame - 24);
            one(frame - 4);
            const u32 angle = rounded(slots + 8);
            FUN_005e5918(reinterpret_cast<void*>(rotation), angle);
            const u32 center = word(slots + 4);
            if (center) {
                transpose(transposed, rotation);
                output = word(slots);
                identity(output);
                negative(output + 48, center);
                negative(output + 52, center + 4);
                multiply(output, transposed);
                multiply(output, scale_matrix);
                multiply(output, rotation);
                add(output + 48, center, output + 48);
                add(output + 52, center + 4, output + 52);
            } else {
                output = word(slots);
                transpose(output, rotation);
                multiply(output, scale_matrix);
                multiply(output, rotation);
            }
        } else {
            const u32 center = word(slots + 4);
            output = word(slots);
            if (center) {
                zeros9(output);
                put(output, word(scale));
                const u32 sy = word(scale + 4);
                one(output + 40);
                put(output + 20, sy);
                one_minus_times(output + 48, scale, center);
                one_minus_times(output + 52, scale + 4, center + 4);
                zero(output + 56);
                one(output + 60);
            } else {
                zeros12(output);
                put(output, word(scale));
                const u32 sy = word(scale + 4);
                one(output + 40);
                put(output + 20, sy);
                one(output + 60);
            }
        }
    } else {
        output = word(slots);
        identity(output);
    }
    if (unequal_angle(slots + 20)) {
        const u32 angle = rounded(slots + 20);
        FUN_005e5918(reinterpret_cast<void*>(rotation), angle);
        const u32 center = word(slots + 16);
        if (center) {
            sub(output + 48, output + 48, center);
            sub(output + 52, output + 52, center + 4);
            multiply(output, rotation);
            add(output + 48, center, output + 48);
            add(output + 52, center + 4, output + 52);
        } else
            multiply(output, rotation);
    }
    const u32 translation = word(slots + 24);
    if (translation) {
        add(output + 48, translation, output + 48);
        add(output + 52, translation + 4, output + 52);
    }
    return output;
}
extern "C" __attribute__((naked, stdcall)) void*
FUN_005e5c06(void*, const void*, const void*, const void*, const void*, const void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_transform_005e5c06\n\taddl $4,%esp\n\tretl $28");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e5f45(void*, const void*, u32, const void*,
                                                              const void*, u32, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_transform_005e5f45\n\taddl $4,%esp\n\tretl $28");
}
extern "C" __attribute__((naked, stdcall)) void*
FUN_005e5bf3(void*, const void*, const void*, const void*, const void*, const void*, const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+160");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e5f12(void*, const void*, u32, const void*,
                                                              const void*, u32, const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tflds 28(%ebp)\n\tpushl 32(%ebp)\n\tpushl %ecx\n\tfstps (%esp)\n\tpushl 24(%ebp)\n\tflds 16(%ebp)\n\tpushl 20(%ebp)\n\tpushl %ecx\n\tfstps (%esp)\n\tpushl 12(%ebp)\n\tpushl 8(%ebp)\n\tcalll *_dat_0070f370+288\n\tpopl %ebp\n\tretl $28");
}
// Distinct actual six-byte fast transpose entry, not its lazy initializer.
extern "C" __attribute__((naked, stdcall)) void* FUN_005e5009(void*, const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+152");
}
