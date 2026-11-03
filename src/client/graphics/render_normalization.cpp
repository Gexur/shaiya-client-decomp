#include "graphics/render_normalization.h"
#include "graphics/render_vector.h"
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
// Exact original readonly pool words:6de5a4=00800000,
// 6de5a8=20000000 and6bc4dc=3f800000. These are value copies,
// not an asserted ownership/extent for the original constant pool.
const float threshold_min = 0x1p-126f;
const float threshold_inverse = 0x1p-63f;
const float one = 1.0f;
uint16_t compare(float value, const float& boundary) {
    uint16_t status;
    __asm__ volatile("flds %1\n\tfcomps %2\n\tfnstsw %0"
                     : "=a"(status)
                     : "m"(value), "m"(boundary)
                     : "st", "memory");
    return status;
}
long double inverse_sqrt(float value) {
    long double result;
    __asm__ volatile("flds %1\n\tfsqrt\n\tfdivrs %2\n\tfstpt %0"
                     : "=m"(result)
                     : "m"(value), "m"(one)
                     : "st", "memory");
    return result;
}
inline void four_squares(u32 slots, long double x, long double y, long double z, long double w) {
    const volatile long double xx = x * x;
    const volatile long double yy = y * y;
    const volatile long double xy = xx + yy;
    const volatile long double zz = z * z;
    const volatile long double xyz = xy + zz;
    const volatile long double ww = w * w;
    const volatile long double xyzw = xyz + ww;
    f32(slots + 4) = static_cast<float>(xyzw);
}
void copy_words(u32 out, u32 input, u32 count) {
    for (u32 i = 0; i < count; ++i)
        put(out + i * 4, word(input + i * 4));
}
} // namespace

extern "C" void* recovered_005e7637(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments), input = word(slots + 4); //763e
    const volatile long double y = static_cast<long double>(f32(input + 4));     //7641
    const volatile long double x = static_cast<long double>(f32(input));         //7645
    const volatile long double xx = x * x;                                       //7648..764a
    const volatile long double yy = y * y;                                       //764c..764e
    const volatile long double length = xx + yy;                                 //7650
    f32(slots + 4) = static_cast<float>(length);                                 //7652
    const int32_t near_one = FUN_005e3be9(f32(slots + 4), one);                  //7659..7665
    if (near_one) {
        const u32 out = word(slots); //766e
        if (out != input)
            copy_words(out, input, 2); //7671..767c
        return reinterpret_cast<void*>(out);
    }
    const uint16_t status = compare(f32(slots + 4), threshold_min); //7681..768a
    const u32 out = word(slots);                                    //768f
    if (!(status & 0x4100)) {
        const volatile long double factor = inverse_sqrt(f32(slots + 4)); //7694..7699
        const volatile long double extended_x =
            factor * static_cast<long double>(f32(input));        //769f..76a1
        volatile float result_x = static_cast<float>(extended_x); //76a3
        const volatile long double extended_y =
            factor * static_cast<long double>(f32(input + 4));    //76a6
        put(out, word(reinterpret_cast<u32>(&result_x)));         //76a9..76ac
        volatile float result_y = static_cast<float>(extended_y); //76ae
        put(out + 4, word(reinterpret_cast<u32>(&result_y)));     //76b1..767c
    } else {
        f32(out) = 0.0f;
        f32(out + 4) = 0.0f; //76b6..76bc
    }
    return reinterpret_cast<void*>(out);
}

extern "C" void* recovered_005e815a(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments), input = word(slots + 4); //8163
    const volatile long double w = static_cast<long double>(f32(input + 12));    //8166
    const volatile long double z = static_cast<long double>(f32(input + 8));     //816a
    const volatile long double y = static_cast<long double>(f32(input + 4));     //816e
    const volatile long double x = static_cast<long double>(f32(input));         //8172
    four_squares(slots, x, y, z, w);                                             //8174..818a
    const int32_t near_one = FUN_005e3be9(f32(slots + 4), one);                  //8195..81a1
    if (near_one) {
        const u32 out = word(slots); //81aa
        if (out != input)
            copy_words(out, input, 4); //81ad..81b6
        return reinterpret_cast<void*>(out);
    }
    const uint16_t status = compare(f32(slots + 4), threshold_min); //81b9..81c2
    const u32 out = word(slots);                                    //81c7
    if (!(status & 0x4100)) {
        const volatile long double factor = inverse_sqrt(f32(slots + 4)); //81cc..81d1
        volatile float result[4];
        const volatile long double result_x = factor * static_cast<long double>(f32(input));
        result[0] = static_cast<float>(result_x); //81d7..81db
        const volatile long double result_y = factor * static_cast<long double>(f32(input + 4));
        result[1] = static_cast<float>(result_y); //81de..81e3
        const volatile long double result_z = factor * static_cast<long double>(f32(input + 8));
        result[2] = static_cast<float>(result_z); //81e6..81eb
        const volatile long double result_w = factor * static_cast<long double>(f32(input + 12));
        result[3] = static_cast<float>(result_w);          //81ee..81f4
        copy_words(out, reinterpret_cast<u32>(result), 4); //81b1..81b6
    } else {
        f32(out) = 0.0f;
        f32(out + 4) = 0.0f;
        f32(out + 8) = 0.0f;
        f32(out + 12) = 0.0f; //81f9..8209
    }
    return reinterpret_cast<void*>(out);
}

extern "C" void* recovered_005e6b2e(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments), input = word(slots + 4); //6b33
    const volatile long double w = static_cast<long double>(f32(input + 12));    //6b36
    const u32 out = word(slots); //6b39: before the remaining input loads
    const volatile long double z = static_cast<long double>(f32(input + 8)); //6b3c
    const volatile long double y = static_cast<long double>(f32(input + 4)); //6b3f
    const volatile long double x = static_cast<long double>(f32(input));     //6b42
    four_squares(slots, x, y, z, w);                                         //6b44..6b5a
    const uint16_t status = compare(f32(slots + 4), threshold_inverse);      //6b65..6b6e
    if (!(status & 0x4100)) {
        const volatile long double fresh_x = static_cast<long double>(f32(input));
        f32(out) = static_cast<float>(-fresh_x); //6b75..6b7b
        const volatile long double fresh_y = static_cast<long double>(f32(input + 4));
        f32(out + 4) = static_cast<float>(-fresh_y); //6b7d..6b82
        const volatile long double fresh_z = static_cast<long double>(f32(input + 8));
        f32(out + 8) = static_cast<float>(-fresh_z); //6b85..6b8a
        const u32 raw_w = word(input + 12);
        put(out + 12, raw_w); //6b8d..6b92: raw MOV retains payload
        const int32_t near_one = FUN_005e3be9(f32(slots + 4), one); //6b90..6b9f
        if (!near_one) {
            const volatile long double factor =
                1.0L / static_cast<long double>(f32(slots + 4)); //6ba8..6baa
            const volatile long double result_x = factor * static_cast<long double>(f32(out));
            f32(out) = static_cast<float>(result_x); //6bad..6bb1
            const volatile long double result_y = factor * static_cast<long double>(f32(out + 4));
            f32(out + 4) = static_cast<float>(result_y); //6bb3..6bb8
            const volatile long double result_z = factor * static_cast<long double>(f32(out + 8));
            f32(out + 8) = static_cast<float>(result_z); //6bbb..6bc0
            const volatile long double result_w = factor * static_cast<long double>(f32(out + 12));
            f32(out + 12) = static_cast<float>(result_w); //6bc3..6bd8
        }
    } else {
        f32(out) = 0.0f;
        f32(out + 4) = 0.0f;
        f32(out + 8) = 0.0f;
        f32(out + 12) = 0.0f; //6bc8..6bd8
    }
    return reinterpret_cast<void*>(out); //6bdb
}

#define ORIGINAL_ENTRY(address)                                                                    \
    extern "C" __attribute__((naked, stdcall)) void* FUN_##address(void*, const void*) {           \
        __asm__ volatile("leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_" #address           \
                         "\n\taddl $4,%esp\n\tretl $8");                                           \
    }
ORIGINAL_ENTRY(005e7637)
ORIGINAL_ENTRY(005e815a)
ORIGINAL_ENTRY(005e6b2e)
#undef ORIGINAL_ENTRY
