#include "graphics/render_project_unproject.h"
#include "graphics/render_matrix_pair.h"
#include "graphics/render_dispatch.h"
#include "graphics/render_transform_coord_dispatch.h"
#include "graphics/render_transform_arrays_dispatch.h"
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
long double fild(u32 p) {
    long double v;
    __asm__ volatile("fildl (%1)\n\tfstpt %0" : "=m"(v) : "r"(p) : "st", "memory");
    return v;
}
void zero(u32 p) {
    __asm__ volatile("fldz\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
void one(u32 p) {
    __asm__ volatile("fld1\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
void multiply(u32 output, u32 left, u32 right) {
    FUN_005e4db8(reinterpret_cast<D3DMATRIX*>(output), reinterpret_cast<const D3DMATRIX*>(left),
                 reinterpret_cast<const D3DMATRIX*>(right));
}
void inverse(u32 output, u32 input) {
    FUN_005e52de(reinterpret_cast<D3DMATRIX*>(output), nullptr,
                 reinterpret_cast<const D3DMATRIX*>(input));
}
} // namespace
// Complete original005e7a2b..005e7b95; following32B are an embedded branch table.
extern "C" u32 recovered_project_005e7a2b(u32 slots) {
    alignas(16) unsigned char private_storage[192];
    const u32 frame = reinterpret_cast<u32>(private_storage) + 176;
    const u32 local = frame - 0x50;
    u32 matrix = local;
    const u32 third = word(slots + 20);
    const bool second_present = word(slots + 16) != 0;
    const u32 first = word(slots + 12);
    const u32 flags = (third != 0 ? 4u : 0u) | (second_present ? 2u : 0u) | (first != 0 ? 1u : 0u);
    switch (flags) {
    case 0:
        zero(frame - 24);
        zero(frame - 28);
        zero(frame - 32);
        zero(frame - 36);
        zero(frame - 44);
        zero(frame - 48);
        zero(frame - 52);
        zero(frame - 56);
        zero(frame - 64);
        zero(frame - 68);
        zero(frame - 72);
        zero(frame - 76);
        one(frame - 20);
        one(frame - 40);
        one(frame - 60);
        one(frame - 80);
        break;
    case 1:
        matrix = first;
        break;
    case 2:
        matrix = word(slots + 16);
        break;
    case 3: {
        const u32 second = word(slots + 16);
        multiply(local, second, first);
        break;
    }
    case 4:
        matrix = third;
        break;
    case 5:
        multiply(local, third, first);
        break;
    case 6: {
        const u32 second = word(slots + 16);
        multiply(local, third, second);
        break;
    }
    case 7: {
        const u32 second = word(slots + 16);
        multiply(local, third, second);
        const u32 again = word(slots + 12);
        multiply(local, local, again);
        break;
    }
    }
    const u32 input = word(slots + 4);
    const u32 output = word(slots);
    FUN_005e44d1(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(input),
                 reinterpret_cast<const void*>(matrix));
    const u32 viewport = word(slots + 8);
    if (viewport) {
        const volatile long double extended_000 =
            static_cast<long double>(f32(output + 0)); // original005e7b15
        const u32 word_000 = word(viewport + 8);       // original005e7b17
        const volatile long double extended_001 =
            extended_000 +
            static_cast<long double>(f32(reinterpret_cast<u32>(dat_006bc4dc))); // original005e7b1c
        const volatile long double extended_002 = fild(viewport + 8);           // original005e7b22
        volatile long double extended_003 = extended_002;                       // original005e7b25
        if (static_cast<int32_t>(word_000) < 0)
            extended_003 =
                extended_002 + static_cast<long double>(
                                   f32(reinterpret_cast<u32>(dat_006bb60c)));  // original005e7b27
        const u32 word_001 = word(viewport + 0);                               // original005e7b2d
        const volatile long double extended_004 = extended_001 * extended_003; // original005e7b2f
        const volatile long double extended_005 =
            extended_004 *
            static_cast<long double>(f32(reinterpret_cast<u32>(dat_006bc860))); // original005e7b33
        const volatile long double extended_006 = fild(viewport + 0);           // original005e7b39
        volatile long double extended_007 = extended_006;                       // original005e7b3b
        if (static_cast<int32_t>(word_001) < 0)
            extended_007 =
                extended_006 + static_cast<long double>(
                                   f32(reinterpret_cast<u32>(dat_006bb60c)));  // original005e7b3d
        const volatile long double extended_008 = extended_005 + extended_007; // original005e7b43
        f32(output + 0) = static_cast<float>(extended_008);                    // original005e7b45
        const u32 word_002 = word(viewport + 12);                              // original005e7b47
        const volatile long double extended_009 = 1.0L;                        // original005e7b4c
        const volatile long double extended_010 =
            extended_009 - static_cast<long double>(f32(output + 4));  // original005e7b4e
        const volatile long double extended_011 = fild(viewport + 12); // original005e7b51
        volatile long double extended_012 = extended_011;              // original005e7b54
        if (static_cast<int32_t>(word_002) < 0)
            extended_012 =
                extended_011 + static_cast<long double>(
                                   f32(reinterpret_cast<u32>(dat_006bb60c)));  // original005e7b56
        const u32 word_003 = word(viewport + 4);                               // original005e7b5c
        const volatile long double extended_013 = extended_010 * extended_012; // original005e7b5f
        const volatile long double extended_014 =
            extended_013 *
            static_cast<long double>(f32(reinterpret_cast<u32>(dat_006bc860))); // original005e7b63
        const volatile long double extended_015 = fild(viewport + 4);           // original005e7b69
        volatile long double extended_016 = extended_015;                       // original005e7b6c
        if (static_cast<int32_t>(word_003) < 0)
            extended_016 =
                extended_015 + static_cast<long double>(
                                   f32(reinterpret_cast<u32>(dat_006bb60c)));  // original005e7b6e
        const volatile long double extended_017 = extended_014 + extended_016; // original005e7b74
        f32(output + 4) = static_cast<float>(extended_017);                    // original005e7b76
        const volatile long double extended_018 =
            static_cast<long double>(f32(viewport + 20)); // original005e7b79
        const volatile long double extended_019 =
            extended_018 - static_cast<long double>(f32(viewport + 16)); // original005e7b7c
        const volatile long double extended_020 =
            extended_019 * static_cast<long double>(f32(output + 8)); // original005e7b7f
        const volatile long double extended_021 =
            extended_020 + static_cast<long double>(f32(viewport + 16)); // original005e7b82
        f32(output + 8) = static_cast<float>(extended_021);              // original005e7b85
    }
    return output;
}
extern "C" __attribute__((naked, stdcall)) void*
FUN_005e7a2b(void*, const void*, const void*, const void*, const void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_project_005e7a2b\n\taddl $4,%esp\n\tretl $24");
}
// Complete original005e7bb5..005e7d82; following32B are an embedded branch table.
extern "C" u32 recovered_project_005e7bb5(u32 slots) {
    alignas(16) unsigned char private_storage[192];
    const u32 frame = reinterpret_cast<u32>(private_storage) + 176;
    const u32 local = frame - 0x50;
    u32 matrix = local;
    const u32 third = word(slots + 28);
    const bool second_present = word(slots + 24) != 0;
    const u32 first = word(slots + 20);
    const u32 flags = (third != 0 ? 4u : 0u) | (second_present ? 2u : 0u) | (first != 0 ? 1u : 0u);
    switch (flags) {
    case 0:
        zero(frame - 24);
        zero(frame - 28);
        zero(frame - 32);
        zero(frame - 36);
        zero(frame - 44);
        zero(frame - 48);
        zero(frame - 52);
        zero(frame - 56);
        zero(frame - 64);
        zero(frame - 68);
        zero(frame - 72);
        zero(frame - 76);
        one(frame - 20);
        one(frame - 40);
        one(frame - 60);
        one(frame - 80);
        break;
    case 1:
        matrix = first;
        break;
    case 2:
        matrix = word(slots + 24);
        break;
    case 3: {
        const u32 second = word(slots + 24);
        multiply(local, second, first);
        break;
    }
    case 4:
        matrix = third;
        break;
    case 5:
        multiply(local, third, first);
        break;
    case 6: {
        const u32 second = word(slots + 24);
        multiply(local, third, second);
        break;
    }
    case 7: {
        const u32 second = word(slots + 24);
        multiply(local, third, second);
        const u32 again = word(slots + 20);
        multiply(local, local, again);
        break;
    }
    }
    const u32 viewport = word(slots + 16);
    if (viewport) {
        const u32 word_000 = word(viewport + 8);                      // original005e7c99
        const volatile long double extended_000 = fild(viewport + 8); // original005e7c9c
        volatile long double extended_001 = extended_000;             // original005e7ca1
        if (static_cast<int32_t>(word_000) < 0)
            extended_001 =
                extended_000 + static_cast<long double>(
                                   f32(reinterpret_cast<u32>(dat_006bb60c))); // original005e7ca3
        const volatile long double extended_002 =
            extended_001 *
            static_cast<long double>(f32(reinterpret_cast<u32>(dat_006bc860))); // original005e7ca9
        const u32 word_001 = word(viewport + 12);                               // original005e7caf
        f32(frame - 144) = static_cast<float>(extended_002);                    // original005e7cb4
        const volatile long double extended_003 = 0.0L;                         // original005e7cba
        f32(frame - 140) = static_cast<float>(extended_003);                    // original005e7cbc
        const volatile long double extended_004 = 0.0L;                         // original005e7cc2
        f32(frame - 136) = static_cast<float>(extended_004);                    // original005e7cc4
        const volatile long double extended_005 = 0.0L;                         // original005e7cca
        f32(frame - 132) = static_cast<float>(extended_005);                    // original005e7ccc
        const volatile long double extended_006 = 0.0L;                         // original005e7cd2
        f32(frame - 128) = static_cast<float>(extended_006);                    // original005e7cd4
        const volatile long double extended_007 = fild(viewport + 12);          // original005e7cd7
        volatile long double extended_008 = extended_007;                       // original005e7cda
        if (static_cast<int32_t>(word_001) < 0)
            extended_008 =
                extended_007 + static_cast<long double>(
                                   f32(reinterpret_cast<u32>(dat_006bb60c))); // original005e7cdc
        const volatile long double extended_009 =
            static_cast<long double>(f32(reinterpret_cast<u32>(dat_006be7f0))); // original005e7ce2
        const u32 word_002 = word(viewport + 0);                                // original005e7ce8
        const volatile long double extended_010 = extended_009 * extended_008;  // original005e7cec
        f32(frame - 124) = static_cast<float>(extended_010);                    // original005e7cee
        const volatile long double extended_011 = 0.0L;                         // original005e7cf1
        f32(frame - 120) = static_cast<float>(extended_011);                    // original005e7cf3
        const volatile long double extended_012 = 0.0L;                         // original005e7cf6
        f32(frame - 116) = static_cast<float>(extended_012);                    // original005e7cf8
        const volatile long double extended_013 = 0.0L;                         // original005e7cfb
        f32(frame - 112) = static_cast<float>(extended_013);                    // original005e7cfd
        const volatile long double extended_014 = 0.0L;                         // original005e7d00
        f32(frame - 108) = static_cast<float>(extended_014);                    // original005e7d02
        const volatile long double extended_015 =
            static_cast<long double>(f32(viewport + 20)); // original005e7d05
        const volatile long double extended_016 =
            extended_015 - static_cast<long double>(f32(viewport + 16)); // original005e7d08
        f32(frame - 104) = static_cast<float>(extended_016);             // original005e7d0b
        const volatile long double extended_017 = 0.0L;                  // original005e7d0e
        f32(frame - 100) = static_cast<float>(extended_017);             // original005e7d10
        const volatile long double extended_018 = fild(viewport + 0);    // original005e7d13
        volatile long double extended_019 = extended_018;                // original005e7d15
        if (static_cast<int32_t>(word_002) < 0)
            extended_019 =
                extended_018 + static_cast<long double>(
                                   f32(reinterpret_cast<u32>(dat_006bb60c)));  // original005e7d17
        const u32 word_003 = word(viewport + 4);                               // original005e7d1d
        const volatile long double extended_020 = extended_019 + extended_002; // original005e7d20
        f32(frame - 96) = static_cast<float>(extended_020);                    // original005e7d24
        const volatile long double extended_021 = fild(viewport + 4);          // original005e7d27
        volatile long double extended_022 = extended_021;                      // original005e7d2a
        if (static_cast<int32_t>(word_003) < 0)
            extended_022 =
                extended_021 + static_cast<long double>(
                                   f32(reinterpret_cast<u32>(dat_006bb60c))); // original005e7d2c
        const u32 word_004 = word(viewport + 16);                             // original005e7d32
        const volatile long double extended_023 = extended_008;               // original005e7d35
        const volatile long double extended_024 =
            extended_023 *
            static_cast<long double>(f32(reinterpret_cast<u32>(dat_006bc860))); // original005e7d37
        put(frame - 88, word_004);                                              // original005e7d3d
        const volatile long double extended_025 = extended_022 + extended_024;  // original005e7d47
        f32(frame - 92) = static_cast<float>(extended_025);                     // original005e7d4e
        const volatile long double extended_026 = 1.0L;                         // original005e7d55
        f32(frame - 84) = static_cast<float>(extended_026);                     // original005e7d57
        multiply(local, matrix, frame - 0x90);
        matrix = local;
    }
    const u32 count = word(slots + 32), input_stride = word(slots + 12), input = word(slots + 8),
              output_stride = word(slots + 4), output = word(slots);
    return reinterpret_cast<u32>(FUN_005e44ea(reinterpret_cast<void*>(output), output_stride,
                                              reinterpret_cast<const void*>(input), input_stride,
                                              reinterpret_cast<const void*>(matrix), count));
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e7bb5(void*, u32, const void*, u32,
                                                              const void*, const void*, const void*,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_project_005e7bb5\n\taddl $4,%esp\n\tretl $36");
}
// Complete original005e7da2..005e7f21; following32B are an embedded branch table.
extern "C" u32 recovered_project_005e7da2(u32 slots) {
    alignas(16) unsigned char private_storage[192];
    const u32 frame = reinterpret_cast<u32>(private_storage) + 176;
    const u32 local = frame - 0x50;
    u32 matrix = local;
    const u32 second = word(slots + 16);
    const u32 third = word(slots + 20);
    const bool first_present = word(slots + 12) != 0;
    const u32 flags = (third != 0 ? 4u : 0u) | (second != 0 ? 2u : 0u) | (first_present ? 1u : 0u);
    switch (flags) {
    case 0:
        zero(frame - 24);
        zero(frame - 28);
        zero(frame - 32);
        zero(frame - 36);
        zero(frame - 44);
        zero(frame - 48);
        zero(frame - 52);
        zero(frame - 56);
        zero(frame - 64);
        zero(frame - 68);
        zero(frame - 72);
        zero(frame - 76);
        one(frame - 20);
        one(frame - 40);
        one(frame - 60);
        one(frame - 80);
        break;
    case 1:
        inverse(local, word(slots + 12));
        break;
    case 2:
        inverse(local, second);
        break;
    case 3: {
        const u32 first = word(slots + 12);
        multiply(local, second, first);
        inverse(local, local);
        break;
    }
    case 4:
        inverse(local, third);
        break;
    case 5: {
        const u32 first = word(slots + 12);
        multiply(local, third, first);
        inverse(local, local);
        break;
    }
    case 6:
        multiply(local, third, second);
        inverse(local, local);
        break;
    case 7: {
        multiply(local, third, second);
        const u32 again = word(slots + 12);
        multiply(local, local, again);
        inverse(local, local);
        break;
    }
    }
    const u32 viewport = word(slots + 8);
    u32 output, input;
    if (viewport) {
        const u32 word_000 = word(viewport + 0);                      // original005e7e88
        const volatile long double extended_000 = fild(viewport + 0); // original005e7e8a
        volatile long double extended_001 = extended_000;             // original005e7e8e
        if (static_cast<int32_t>(word_000) < 0)
            extended_001 =
                extended_000 + static_cast<long double>(
                                   f32(reinterpret_cast<u32>(dat_006bb60c))); // original005e7e90
        const u32 word_001 = word(slots + 4);                                 // original005e7e96
        input = word_001;
        const volatile long double extended_002 =
            static_cast<long double>(f32(word_001 + 0)) - extended_001; // original005e7e99
        const u32 word_002 = word(viewport + 8);                        // original005e7e9b
        const volatile long double extended_003 = fild(viewport + 8);   // original005e7ea0
        volatile long double extended_004 = extended_003;               // original005e7ea3
        if (static_cast<int32_t>(word_002) < 0)
            extended_004 =
                extended_003 + static_cast<long double>(
                                   f32(reinterpret_cast<u32>(dat_006bb60c)));  // original005e7ea5
        const volatile long double extended_005 = extended_002 / extended_004; // original005e7eab
        const u32 word_003 = word(slots + 0);                                  // original005e7ead
        output = word_003;
        const volatile long double extended_006 = extended_005 + extended_005; // original005e7eb0
        const volatile long double extended_007 =
            extended_006 -
            static_cast<long double>(f32(reinterpret_cast<u32>(dat_006bc4dc))); // original005e7eb2
        f32(word_003 + 0) = static_cast<float>(extended_007);                   // original005e7eb8
        const u32 word_004 = word(viewport + 4);                                // original005e7eba
        const volatile long double extended_008 = fild(viewport + 4);           // original005e7ebf
        volatile long double extended_009 = extended_008;                       // original005e7ec2
        if (static_cast<int32_t>(word_004) < 0)
            extended_009 =
                extended_008 + static_cast<long double>(
                                   f32(reinterpret_cast<u32>(dat_006bb60c))); // original005e7ec4
        const volatile long double extended_010 =
            static_cast<long double>(f32(word_001 + 4)) - extended_009; // original005e7eca
        const u32 word_005 = word(viewport + 12);                       // original005e7ecd
        const volatile long double extended_011 = fild(viewport + 12);  // original005e7ed2
        volatile long double extended_012 = extended_011;               // original005e7ed5
        if (static_cast<int32_t>(word_005) < 0)
            extended_012 =
                extended_011 + static_cast<long double>(
                                   f32(reinterpret_cast<u32>(dat_006bb60c)));  // original005e7ed7
        const volatile long double extended_013 = extended_010 / extended_012; // original005e7edd
        const volatile long double extended_014 = extended_013 + extended_013; // original005e7edf
        const volatile long double extended_015 =
            extended_014 -
            static_cast<long double>(f32(reinterpret_cast<u32>(dat_006bc4dc))); // original005e7ee1
        const volatile long double extended_016 = -extended_015;                // original005e7ee7
        f32(word_003 + 4) = static_cast<float>(extended_016);                   // original005e7ee9
        const volatile long double extended_017 =
            static_cast<long double>(f32(word_001 + 8)); // original005e7eec
        const volatile long double extended_018 =
            extended_017 - static_cast<long double>(f32(viewport + 16)); // original005e7eef
        const volatile long double extended_019 =
            static_cast<long double>(f32(viewport + 20)); // original005e7ef2
        const volatile long double extended_020 =
            extended_019 - static_cast<long double>(f32(viewport + 16));       // original005e7ef5
        const volatile long double extended_021 = extended_018 / extended_020; // original005e7efc
        f32(word_003 + 8) = static_cast<float>(extended_021);                  // original005e7eff
    } else {
        output = word(slots);
        input = word(slots + 4);
    }
    FUN_005e44d1(reinterpret_cast<void*>(output),
                 reinterpret_cast<const void*>(viewport ? output : input),
                 reinterpret_cast<const void*>(local));
    return output;
}
extern "C" __attribute__((naked, stdcall)) void*
FUN_005e7da2(void*, const void*, const void*, const void*, const void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_project_005e7da2\n\taddl $4,%esp\n\tretl $24");
}
// Complete original005e7f41..005e813a; following32B are an embedded branch table.
extern "C" u32 recovered_project_005e7f41(u32 slots) {
    alignas(16) unsigned char private_storage[192];
    const u32 frame = reinterpret_cast<u32>(private_storage) + 176;
    const u32 local = frame - 0x50;
    u32 matrix = local;
    const u32 second = word(slots + 24);
    const u32 third = word(slots + 28);
    const bool first_present = word(slots + 20) != 0;
    const u32 flags = (third != 0 ? 4u : 0u) | (second != 0 ? 2u : 0u) | (first_present ? 1u : 0u);
    switch (flags) {
    case 0:
        zero(frame - 24);
        zero(frame - 28);
        zero(frame - 32);
        zero(frame - 36);
        zero(frame - 44);
        zero(frame - 48);
        zero(frame - 52);
        zero(frame - 56);
        zero(frame - 64);
        zero(frame - 68);
        zero(frame - 72);
        zero(frame - 76);
        one(frame - 20);
        one(frame - 40);
        one(frame - 60);
        one(frame - 80);
        break;
    case 1:
        inverse(local, word(slots + 20));
        break;
    case 2:
        inverse(local, second);
        break;
    case 3: {
        const u32 first = word(slots + 20);
        multiply(local, second, first);
        inverse(local, local);
        break;
    }
    case 4:
        inverse(local, third);
        break;
    case 5: {
        const u32 first = word(slots + 20);
        multiply(local, third, first);
        inverse(local, local);
        break;
    }
    case 6:
        multiply(local, third, second);
        inverse(local, local);
        break;
    case 7: {
        multiply(local, third, second);
        const u32 again = word(slots + 20);
        multiply(local, local, again);
        inverse(local, local);
        break;
    }
    }
    const u32 viewport = word(slots + 16);
    if (viewport) {
        const u32 word_000 = word(viewport + 8);                      // original005e802e
        const volatile long double extended_000 = fild(viewport + 8); // original005e8031
        volatile long double extended_001 = extended_000;             // original005e8036
        if (static_cast<int32_t>(word_000) < 0)
            extended_001 =
                extended_000 + static_cast<long double>(
                                   f32(reinterpret_cast<u32>(dat_006bb60c))); // original005e8038
        const u32 word_001 = word(viewport + 12);                             // original005e803e
        const volatile long double extended_002 =
            static_cast<long double>(f32(reinterpret_cast<u32>(dat_006bc9d4))) /
            extended_001;                                              // original005e8043
        const volatile long double extended_003 = fild(viewport + 12); // original005e8049
        volatile long double extended_004 = extended_003;              // original005e804c
        if (static_cast<int32_t>(word_001) < 0)
            extended_004 =
                extended_003 + static_cast<long double>(
                                   f32(reinterpret_cast<u32>(dat_006bb60c))); // original005e804e
        const volatile long double extended_005 =
            static_cast<long double>(f32(reinterpret_cast<u32>(dat_006bc9d4))) /
            extended_004;                        // original005e8054
        const u32 word_002 = word(viewport + 0); // original005e805a
        const volatile long double extended_006 =
            static_cast<long double>(f32(reinterpret_cast<u32>(dat_006bc4dc))); // original005e805e
        const volatile long double extended_007 =
            static_cast<long double>(f32(viewport + 20)); // original005e8064
        const volatile long double extended_008 =
            extended_007 - static_cast<long double>(f32(viewport + 16));       // original005e8067
        const volatile long double extended_009 = extended_006 / extended_008; // original005e806a
        f32(frame - 4) = static_cast<float>(extended_009);                     // original005e806c
        const volatile long double extended_010 = extended_002;                // original005e806f
        f32(frame - 160) = static_cast<float>(extended_010);                   // original005e8071
        const volatile long double extended_011 = 0.0L;                        // original005e8077
        f32(frame - 156) = static_cast<float>(extended_011);                   // original005e8079
        const volatile long double extended_012 = 0.0L;                        // original005e807f
        f32(frame - 152) = static_cast<float>(extended_012);                   // original005e8081
        const volatile long double extended_013 = 0.0L;                        // original005e8087
        f32(frame - 148) = static_cast<float>(extended_013);                   // original005e8089
        const volatile long double extended_014 = 0.0L;                        // original005e808f
        f32(frame - 144) = static_cast<float>(extended_014);                   // original005e8091
        const volatile long double extended_015 = extended_005;                // original005e8097
        const volatile long double extended_016 = -extended_015;               // original005e8099
        f32(frame - 140) = static_cast<float>(extended_016);                   // original005e809b
        const volatile long double extended_017 = 0.0L;                        // original005e80a1
        f32(frame - 136) = static_cast<float>(extended_017);                   // original005e80a3
        const volatile long double extended_018 = 0.0L;                        // original005e80a9
        f32(frame - 132) = static_cast<float>(extended_018);                   // original005e80ab
        const volatile long double extended_019 = 0.0L;                        // original005e80b1
        f32(frame - 128) = static_cast<float>(extended_019);                   // original005e80b3
        const volatile long double extended_020 = 0.0L;                        // original005e80b6
        f32(frame - 124) = static_cast<float>(extended_020);                   // original005e80b8
        f32(frame - 120) = static_cast<float>(extended_009);                   // original005e80bb
        const volatile long double extended_021 = 0.0L;                        // original005e80be
        f32(frame - 116) = static_cast<float>(extended_021);                   // original005e80c0
        const volatile long double extended_022 = fild(viewport + 0);          // original005e80c3
        volatile long double extended_023 = extended_022;                      // original005e80c5
        if (static_cast<int32_t>(word_002) < 0)
            extended_023 =
                extended_022 + static_cast<long double>(
                                   f32(reinterpret_cast<u32>(dat_006bb60c)));  // original005e80c7
        const u32 word_003 = word(viewport + 4);                               // original005e80cd
        const volatile long double extended_024 = extended_023 * extended_002; // original005e80d2
        const volatile long double extended_025 = -extended_024;               // original005e80d4
        const volatile long double extended_026 = extended_025 - extended_006; // original005e80d6
        f32(frame - 112) = static_cast<float>(extended_026);                   // original005e80d8
        const volatile long double extended_027 = fild(viewport + 4);          // original005e80db
        volatile long double extended_028 = extended_027;                      // original005e80de
        if (static_cast<int32_t>(word_003) < 0)
            extended_028 =
                extended_027 + static_cast<long double>(
                                   f32(reinterpret_cast<u32>(dat_006bb60c)));  // original005e80e0
        const volatile long double extended_029 = extended_028 * extended_005; // original005e80e6
        const volatile long double extended_030 = extended_029 + extended_006; // original005e80e8
        f32(frame - 108) = static_cast<float>(extended_030);                   // original005e80ea
        const volatile long double extended_031 =
            static_cast<long double>(f32(frame - 4)); // original005e80f3
        const volatile long double extended_032 =
            extended_031 * static_cast<long double>(f32(viewport + 16)); // original005e80f6
        const volatile long double extended_033 = -extended_032;         // original005e8103
        f32(frame - 104) = static_cast<float>(extended_033);             // original005e8106
        const volatile long double extended_034 = 1.0L;                  // original005e810c
        f32(frame - 100) = static_cast<float>(extended_034);             // original005e810f
        multiply(local, frame - 0xa0, local);
    }
    const u32 count = word(slots + 32), input_stride = word(slots + 12), input = word(slots + 8),
              output_stride = word(slots + 4), output = word(slots);
    return reinterpret_cast<u32>(FUN_005e44ea(reinterpret_cast<void*>(output), output_stride,
                                              reinterpret_cast<const void*>(input), input_stride,
                                              reinterpret_cast<const void*>(matrix), count));
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e7f41(void*, u32, const void*, u32,
                                                              const void*, const void*, const void*,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_project_005e7f41\n\taddl $4,%esp\n\tretl $36");
}
extern "C" {
alignas(4) extern const uint32_t dat_006bc4dc[1] = {0x3f800000u};
alignas(4) extern const uint32_t dat_006bc860[1] = {0x3f000000u};
alignas(4) extern const uint32_t dat_006bc9d4[1] = {0x40000000u};
alignas(4) extern const uint32_t dat_006be7f0[1] = {0xbf000000u};
}
extern "C" __attribute__((naked, stdcall)) void*
FUN_005e46e5(void*, const void*, const void*, const void*, const void*, const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+60");
}
extern "C" __attribute__((naked, stdcall)) void*
FUN_005e46f8(void*, const void*, const void*, const void*, const void*, const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+60");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e46fe(void*, uint32_t, const void*,
                                                              uint32_t, const void*, const void*,
                                                              const void*, const void*, uint32_t) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+268");
}
extern "C" __attribute__((naked, stdcall)) void*
FUN_005e4711(void*, const void*, const void*, const void*, const void*, const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+64");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e4724(void*, uint32_t, const void*,
                                                              uint32_t, const void*, const void*,
                                                              const void*, const void*, uint32_t) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+272");
}
