#include "graphics/surface/surface_volume_linear_backend.h"
#include "graphics/surface/surface_linear_weights.h"
#include "graphics/surface/surface_format_configure.h"
#include "runtime/allocations.h"
#include "core/untouched_lifetime.h"
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
u32 weights(u32 source, u32 destination, u32 flag) {
    u32 result;
    const auto target = &FUN_005eea1a;
    __asm__ volatile("pushl %4\n\tcalll *%3"
                     : "=a"(result), "+S"(source), "+D"(destination)
                     : "r"(target), "r"(flag)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
void read_row(u32 receiver, u32 table, u32 row, u32 slice, u32 buffer, u32 z) {
    const u32 code = word(table + 4), words[3] = {row, slice, buffer};
    // Original EAX is the vtable and EDX is the current Z table record.
    __asm__ volatile("pushl 8(%4)\n\tpushl 4(%4)\n\tpushl (%4)\n\tcalll *%3"
                     : "+a"(table), "+d"(z), "+c"(receiver)
                     : "r"(code), "r"(words)
                     : "memory", "cc");
}
void write_row(u32 receiver, u32 row, u32 slice, u32 buffer) {
    u32 table = word(receiver);
    const u32 code = word(table + 8), words[3] = {row, slice, buffer};
    __asm__ volatile("pushl 8(%3)\n\tpushl 4(%3)\n\tpushl (%3)\n\tcalll *%2"
                     : "+a"(table), "+c"(receiver)
                     : "r"(code), "r"(words)
                     : "edx", "memory", "cc");
}
#include "graphics/surface/surface_volume_linear_mix.h"
constexpr int32_t failure = static_cast<int32_t>(0x80004005u),
                  out_of_memory = static_cast<int32_t>(0x8007000eu);
} // namespace
// Original5eeea8..5ef56a ends before the separate5ef56a RET4 helper.
extern "C" int32_t __attribute__((thiscall)) FUN_005eeea8(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object), flags = word(self + 8);
    if (static_cast<unsigned char>(flags) != 3)
        return failure;
    const u32 xflag = (~(flags >> 16)) & 1, yflag = (~(flags >> 17)) & 1,
              zflag = (~(flags >> 18)) & 1;
    u32 destination = word(self + 4);
    const u32 output_width = word(destination + 0x68);
    u32 source = word(self);
    const u32 input_width = word(source + 0x68);
    const u32 xtable = weights(input_width, output_width, xflag);
    source = word(self);
    const u32 input_height = word(source + 0x6c);
    destination = word(self + 4);
    const u32 output_height = word(destination + 0x6c);
    const u32 ytable = weights(input_height, output_height, yflag);
    source = word(self);
    const u32 input_depth = word(source + 0x70);
    destination = word(self + 4);
    const u32 output_depth = word(destination + 0x70);
    const u32 ztable = weights(input_depth, output_depth, zflag);
    void* output = nullptr;
    void* input = nullptr;
    int32_t result = out_of_memory;
    if (xtable && ytable && ztable) {
        destination = word(self + 4);
        const u32 count = word(destination + 0x68);
        output = fun_005cc96d(count << 4);
        if (output)
            FUN_00405c90(output, 16, count, reinterpret_cast<uintptr_t>(&FUN_004441b0));
        if (output) {
            source = word(self);
            const u32 input_count = word(source + 0x68) << 2;
            input = fun_005cc96d(input_count << 4);
            if (input)
                FUN_00405c90(input, 16, input_count, reinterpret_cast<uintptr_t>(&FUN_004441b0));
            if (input) {
                source = word(self);
                const u32 width = word(source + 0x68), base = reinterpret_cast<uintptr_t>(input);
                u32 a = base, b = base + (width << 4), c = base + (width << 5),
                    d = base + ((width + width * 2) << 4), slice = 0, z = ztable + 8;
                destination = word(self + 4);
                if (word(destination + 0x70))
                    do {
                        u32 row = 0, lower_row = 0xffffffffu, upper_row = 0xffffffffu;
                        if (word(destination + 0x6c)) {
                            u32 y = ytable + 8;
                            do {
                                const u32 first = word(y - 8);
                                if (first != lower_row) {
                                    if (first == upper_row) {
                                        const u32 olda = a, oldc = c;
                                        upper_row = 0xffffffffu;
                                        lower_row = first;
                                        a = b;
                                        b = olda;
                                        c = d;
                                        d = oldc;
                                    } else {
                                        u32 from_slice = word(z - 8);
                                        source = word(self);
                                        lower_row = first;
                                        u32 table = word(source);
                                        read_row(source, table, lower_row, from_slice, a, z);
                                        from_slice = word(z);
                                        source = word(self);
                                        table = word(source);
                                        read_row(source, table, lower_row, from_slice, c, z);
                                    }
                                }
                                const u32 second = word(y);
                                if (second != upper_row) {
                                    u32 from_slice = word(z - 8);
                                    source = word(self);
                                    upper_row = second;
                                    u32 table = word(source);
                                    read_row(source, table, upper_row, from_slice, b, z);
                                    source = word(self);
                                    table = word(source);
                                    from_slice = word(z);
                                    read_row(source, table, upper_row, from_slice, d, z);
                                }
                                destination = word(self + 4);
                                u32 x = xtable + 8, pixel = 0,
                                    to = reinterpret_cast<uintptr_t>(output);
                                if (word(destination + 0x68))
                                    do {
                                        mix_volume_linear(to, a, b, c, d, x, y, z);
                                        ++pixel;
                                        x += 16;
                                        to += 16;
                                        destination = word(self + 4);
                                    } while (pixel < word(destination + 0x68));
                                destination = word(self + 4);
                                write_row(destination, row, slice,
                                          reinterpret_cast<uintptr_t>(output));
                                destination = word(self + 4);
                                y += 16;
                                ++row;
                            } while (row < word(destination + 0x6c));
                        }
                        z += 16;
                        ++slice;
                        destination = word(self + 4);
                    } while (slice < word(destination + 0x70));
                result = 0;
            }
        }
    }
    fun_005cc620(reinterpret_cast<void*>(xtable));
    fun_005cc620(reinterpret_cast<void*>(ytable));
    fun_005cc620(reinterpret_cast<void*>(ztable));
    fun_005cc620(output);
    fun_005cc620(input);
    return result;
}
