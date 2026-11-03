#include "graphics/surface/surface_area_backend.h"
#include "graphics/surface/surface_area_weights.h"
#include "graphics/surface/surface_filter_storage.h"
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
void clear_word(u32 p) {
    __asm__ volatile("andl $0,(%0)" ::"r"(p) : "memory", "cc");
}
void increment(u32 p) {
    __asm__ volatile("incl (%0)" ::"r"(p) : "memory", "cc");
}
bool decrement_is_zero(u32 p) {
    unsigned char z;
    __asm__ volatile("decl (%1)\n\tsetz %0" : "=qm"(z) : "r"(p) : "memory", "cc");
    return z != 0;
}
struct __attribute__((packed, may_alias)) FloatWord {
    float value;
};
volatile float& f32(u32 p) {
    return reinterpret_cast<volatile FloatWord*>(p)->value;
}
void zero_bytes(u32 output, u32 bytes) {
    u32 count = bytes >> 2;
    __asm__ volatile("rep stosl" : "+D"(output), "+c"(count) : "a"(0) : "memory");
    count = bytes & 3;
    __asm__ volatile("rep stosb" : "+D"(output), "+c"(count) : "a"(0) : "memory");
}
void read_row(u32 receiver, u32 row, u32 slice, u32 buffer) {
    u32 table = word(receiver);
    const u32 code = word(table + 4), words[3] = {row, slice, buffer};
    __asm__ volatile("pushl 8(%3)\n\tpushl 4(%3)\n\tpushl (%3)\n\tcalll *%2"
                     : "+a"(table), "+c"(receiver)
                     : "r"(code), "r"(words)
                     : "edx", "memory", "cc");
}
void write_row(u32 receiver, u32 table, u32 row, u32 slice, u32 buffer) {
    const u32 code = word(table + 8), words[3] = {row, slice, buffer};
    __asm__ volatile("pushl 8(%3)\n\tpushl 4(%3)\n\tpushl (%3)\n\tcalll *%2"
                     : "+a"(table), "+c"(receiver)
                     : "r"(code), "r"(words)
                     : "edx", "memory", "cc");
}
// These two hardware comparisons retain original FCOM's unordered/invalid
// behavior and single public-memory read; they are not language FP predicates.
uint16_t constant_to_value(const float& constant, u32 p) {
    uint16_t sw;
    __asm__ volatile("flds %1\n\tfcoms (%2)\n\tfnstsw %%ax\n\tfstp %%st(0)"
                     : "=a"(sw)
                     : "m"(constant), "r"(p)
                     : "st", "memory");
    return sw;
}
uint16_t value_to_one(u32 p) {
    uint16_t sw;
    static const float one = 1.0f;
    __asm__ volatile("flds (%1)\n\tfcomps %2\n\tfnstsw %%ax"
                     : "=a"(sw)
                     : "r"(p), "m"(one)
                     : "st", "memory");
    return sw;
}
void clamp_value(u32 p, bool signed_lower, bool first_mode) {
    static const float zero = 0.0f, minus_one = -1.0f, one = 1.0f;
    const float& lower = signed_lower ? minus_one : zero;
    if ((constant_to_value(lower, p) & 0x4100) == 0) {
        f32(p) = lower;
        return;
    }
    if (first_mode) {
        if ((constant_to_value(one, p) & 0x4100) == 0)
            f32(p) = f32(p);
        else
            f32(p) = one;
    } else {
        if ((value_to_one(p) & 0x0500) == 0x0100)
            f32(p) = f32(p);
        else
            f32(p) = one;
    }
}
// Original5ef873..5ef8c3. All three weights and four accumulated channels
// retain the original extended operations and each separate F32 store.
void accumulate(u32 row_base, u32 input, u32 xpair, u32 ypair, u32 zpair) {
    const volatile long double wx = static_cast<long double>(f32(xpair + 4));
    const volatile long double wxz = wx * static_cast<long double>(f32(zpair + 4));
    u32 output = row_base + (word(xpair) << 4);
    const volatile long double weight = wxz * static_cast<long double>(f32(ypair + 4));
    const volatile long double a = weight * static_cast<long double>(f32(input - 8));
    const volatile long double b = a + static_cast<long double>(f32(output));
    f32(output) = static_cast<float>(b);
    output = row_base + (word(xpair) << 4) + 4;
    const volatile long double c = weight * static_cast<long double>(f32(input - 4));
    const volatile long double d = c + static_cast<long double>(f32(output));
    f32(output) = static_cast<float>(d);
    output = row_base + (word(xpair) << 4) + 8;
    const volatile long double e = weight * static_cast<long double>(f32(input));
    const volatile long double f = e + static_cast<long double>(f32(output));
    f32(output) = static_cast<float>(f);
    output = row_base + (word(xpair) << 4) + 12;
    const volatile long double g = weight * static_cast<long double>(f32(input + 4));
    const volatile long double h = g + static_cast<long double>(f32(output));
    f32(output) = static_cast<float>(h);
}
constexpr int32_t failure = static_cast<int32_t>(0x80004005u),
                  oom = static_cast<int32_t>(0x8007000eu);
} // namespace
// Draft complete original5ef5b9..5efc3f; genuine variable-area table traversal,
// cache reuse and cleanup. Remains outside canonical source pending proof.
extern "C" int32_t __attribute__((thiscall)) FUN_005ef5b9(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object), flags = word(self + 8);
    const u32 xflag = (~(flags >> 16)) & 1, yflag = (~(flags >> 17)) & 1,
              zflag = (~(flags >> 18)) & 1;
    u32 destination = word(self + 4);
    const u32 dx = word(destination + 0x68);
    u32 source = word(self);
    const u32 sx = word(source + 0x68);
    const u32 xtable = reinterpret_cast<uintptr_t>(FUN_005eca09(sx, dx, xflag));
    u32 ytable = 0, ztable = 0, cache = 0, input = 0, free_head = 0;
    int32_t result = failure;
    if (xtable) {
        destination = word(self + 4);
        const u32 dy = word(destination + 0x6c);
        source = word(self);
        const u32 sy = word(source + 0x6c);
        ytable = reinterpret_cast<uintptr_t>(FUN_005eca09(sy, dy, yflag));
        if (ytable) {
            destination = word(self + 4);
            const u32 dz = word(destination + 0x70);
            source = word(self);
            const u32 sz = word(source + 0x70);
            ztable = reinterpret_cast<uintptr_t>(FUN_005eca09(sz, dz, zflag));
            if (ztable) {
                const u32 xend = xtable + word(xtable), yend = ytable + word(ytable),
                          zend = ztable + word(ztable);
                destination = word(self + 4);
                const u32 depth = word(destination + 0x70);
                const u32 allocation = reinterpret_cast<uintptr_t>(fun_005cc96d(depth * 12 + 4));
                if (allocation) {
                    put(allocation, depth);
                    cache = allocation + 4;
                    FUN_00405c90(reinterpret_cast<void*>(cache), 12, depth,
                                 reinterpret_cast<uintptr_t>(&FUN_005fc891));
                }
                result = oom;
                if (cache) {
                    source = word(self);
                    const u32 width = word(source + 0x68);
                    input = reinterpret_cast<uintptr_t>(fun_005cc96d(width << 4));
                    if (input)
                        FUN_00405c90(reinterpret_cast<void*>(input), 16, width,
                                     reinterpret_cast<uintptr_t>(&FUN_004441b0));
                    if (input) {
                        u32 zrecord = ztable + 4;
                        while (zrecord < zend) {
                            const u32 next = zrecord + word(zrecord);
                            for (u32 pair = zrecord + 4; pair < next; pair += 8)
                                increment(cache + word(pair) * 12 + 8);
                            zrecord = next;
                        }
                        zrecord = ztable + 4;
                        u32 source_slice = 0;
                        result = 0;
                        while (zrecord < zend) {
                            const u32 znext = zrecord + word(zrecord), zbegin = zrecord + 4;
                            for (u32 pair = zbegin; pair < znext; pair += 8) {
                                const u32 entry = cache + word(pair) * 12;
                                if (!word(entry)) {
                                    if (free_head) {
                                        put(entry, word(free_head));
                                        clear_word(free_head);
                                        free_head = word(free_head + 4);
                                    } else {
                                        destination = word(self + 4);
                                        u32 count = word(destination + 0x6c);
                                        count *= word(destination + 0x68);
                                        void* allocated = fun_005cc96d(count << 4);
                                        if (allocated)
                                            FUN_00405c90(
                                                allocated, 16, count,
                                                reinterpret_cast<uintptr_t>(&FUN_004441b0));
                                        put(entry, reinterpret_cast<uintptr_t>(allocated));
                                        if (!allocated) {
                                            result = oom;
                                            goto cleanup;
                                        }
                                    }
                                    destination = word(self + 4);
                                    u32 count = word(destination + 0x6c);
                                    count *= word(destination + 0x68);
                                    const u32 buffer = word(entry);
                                    zero_bytes(buffer, count << 4);
                                }
                            }
                            u32 yrecord = ytable + 4, source_row = 0;
                            while (yrecord < yend) {
                                const u32 ynext = yrecord + word(yrecord);
                                source = word(self);
                                read_row(source, source_row, source_slice, input);
                                u32 xrecord = xtable + 4, from = input + 8;
                                while (xrecord < xend) {
                                    const u32 xnext = xrecord + word(xrecord);
                                    for (u32 zp = zbegin; zp < znext; zp += 8) {
                                        for (u32 yp = yrecord + 4; yp < ynext; yp += 8) {
                                            const u32 index = word(zp), headers = cache;
                                            destination = word(self + 4);
                                            u32 row = word(destination + 0x68);
                                            row *= word(yp);
                                            row <<= 4;
                                            row += word(headers + index * 12);
                                            for (u32 xp = xrecord + 4; xp < xnext; xp += 8)
                                                accumulate(row, from, xp, yp, zp);
                                        }
                                    }
                                    xrecord = xnext;
                                    from += 16;
                                }
                                ++source_row;
                                yrecord = ynext;
                            }
                            for (u32 pair = zbegin; pair < znext; pair += 8) {
                                const u32 entry = cache + word(pair) * 12;
                                if (decrement_is_zero(entry + 8)) {
                                    u32 row = 0;
                                    destination = word(self + 4);
                                    if (word(destination + 0x6c))
                                        do {
                                            const u32 width = word(destination + 0x68);
                                            source = word(self);
                                            const u32 kind = word(source + 8);
                                            u32 values = (width * row << 4) + word(entry);
                                            if (kind == 1 || kind == 2 || kind == 3) {
                                                u32 pixel = 0;
                                                if (width)
                                                    do {
                                                        clamp_value(values, kind != 1, kind == 1);
                                                        clamp_value(values + 4, kind != 1,
                                                                    kind == 1);
                                                        clamp_value(values + 8, kind != 1,
                                                                    kind == 1);
                                                        clamp_value(values + 12, kind == 3,
                                                                    kind == 1);
                                                        destination = word(self + 4);
                                                        ++pixel;
                                                        values += 16;
                                                    } while (pixel < word(destination + 0x68));
                                            }
                                            destination = word(self + 4);
                                            u32 buffer = word(destination + 0x68) * row;
                                            const u32 table = word(destination);
                                            buffer <<= 4;
                                            buffer += word(entry);
                                            const u32 slice = word(pair);
                                            write_row(destination, table, row, slice, buffer);
                                            ++row;
                                            destination = word(self + 4);
                                        } while (row < word(destination + 0x6c));
                                    put(entry + 4, free_head);
                                    free_head = entry;
                                }
                            }
                            ++source_slice;
                            zrecord = znext;
                        }
                    }
                }
            }
        }
    }
cleanup:
    if (cache)
        FUN_005ef56a(reinterpret_cast<void*>(cache), 3);
    fun_005cc620(reinterpret_cast<void*>(ztable));
    fun_005cc620(reinterpret_cast<void*>(ytable));
    fun_005cc620(reinterpret_cast<void*>(xtable));
    fun_005cc620(reinterpret_cast<void*>(input));
    fun_005cc620(nullptr);
    return result;
}
