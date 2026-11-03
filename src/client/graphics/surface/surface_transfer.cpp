#include "graphics/surface/surface_transfer.h"
#include "graphics/surface/surface_transfer_context.h"
extern "C" void __attribute__((stdcall)) FUN_005e9b1d(uint32_t);
// These are genuine unresolved original dependencies, not success backends.
extern "C" int32_t __attribute__((thiscall)) FUN_005f0510(void*, void*, void*, void*, void*,
                                                          uint32_t, uint32_t);
extern "C" int32_t __attribute__((stdcall)) FUN_005e1d1f(uint32_t, uint32_t, uint32_t, uint32_t,
                                                         uint32_t, uint32_t, uint32_t, void*,
                                                         uint32_t, uint32_t);
namespace {
using u32 = uint32_t;
using i32 = int32_t;
void* ptr(u32 p) {
    return reinterpret_cast<void*>(p);
}
u32 word(const void* p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(void* p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
template <class Target> Target method(u32 table, u32 offset) {
    return reinterpret_cast<Target>(word(ptr(table + offset)));
}
u32 call1(u32 object, u32 slot) {
    const u32 table = word(ptr(object));
    using Method = u32(__attribute__((stdcall))*)(void*);
    return method<Method>(table, slot)(ptr(object));
}
void copy4(void* to, u32 from) {
    for (u32 i = 0; i != 4; ++i)
        put(static_cast<unsigned char*>(to) + i * 4, word(ptr(from + i * 4)));
}
bool equal_palette(u32 source, u32 destination) {
    u32 count = 256;
    unsigned char equal;
    __asm__ volatile("repe cmpsl\n\tsete %0"
                     : "=qm"(equal), "+S"(source), "+D"(destination), "+c"(count)::"memory", "cc");
    return equal != 0;
}
} // namespace
// Complete original5e2d78..5e2f8c. The real200-byte private area is reserved
// at entryESP-204: context+54, source/dest descriptors+68/+88, RECTs+b8/+a8.
extern "C" int32_t recovered_005e2d78(u32* args, unsigned char* frame) {
    void* context = frame + 0x54;
    FUN_005f033c(context);
    i32 result = static_cast<i32>(0x8876086c);
    const u32 source = word(args);
    if (source) {
        const u32 destination = word(args + 3);
        if (destination) {
            using Output = i32(__attribute__((stdcall))*)(void*, void*);
            u32 table = word(ptr(source));
            method<Output>(table, 0x30)(ptr(source), frame + 0x68);
            table = word(ptr(destination));
            method<Output>(table, 0x30)(ptr(destination), frame + 0x88);
            bool fallback = (word(args + 6) & 0xffff) == 5;
            if (!fallback)
                fallback = word(args + 7) != 0;
            if (!fallback) {
                const u32 palette_source = word(args + 1), palette_destination = word(args + 4);
                if (palette_source != palette_destination)
                    fallback = !palette_source || !palette_destination ||
                               !equal_palette(palette_source, palette_destination);
            }
            if (!fallback) {
                const u32 rect_source = word(args + 2);
                u32 right_source, bottom_source;
                if (rect_source) {
                    copy4(frame + 0xb8, rect_source);
                    right_source = word(frame + 0xc0);
                    bottom_source = word(frame + 0xc4);
                } else {
                    right_source = word(frame + 0x80);
                    bottom_source = word(frame + 0x84);
                    put(frame + 0xb8, 0);
                    put(frame + 0xbc, 0);
                    put(frame + 0xc0, right_source);
                    put(frame + 0xc4, bottom_source);
                }
                u32 right_destination, bottom_destination;
                if (word(args + 5)) {
                    const u32 rect_destination = word(args + 5);
                    copy4(frame + 0xa8, rect_destination);
                    bottom_destination = word(frame + 0xb4);
                    right_destination = word(frame + 0xb0);
                    bottom_source = word(frame + 0xc4);
                } else {
                    bottom_destination = word(frame + 0xa4);
                    put(frame + 0xa8, 0);
                    put(frame + 0xac, 0);
                    right_destination = word(frame + 0xa0);
                    put(frame + 0xb0, right_destination);
                    put(frame + 0xb4, bottom_destination);
                }
                right_destination -= word(frame + 0xa8);
                right_source -= word(frame + 0xb8);
                fallback = right_source != right_destination;
                if (!fallback) {
                    bottom_destination -= word(frame + 0xac);
                    bottom_source -= word(frame + 0xbc);
                    fallback = bottom_source != bottom_destination;
                }
                if (!fallback) {
                    table = word(ptr(destination));
                    method<Output>(table, 0xc)(ptr(destination), args + 3);
                    FUN_005e9b1d(1);
                    result = static_cast<i32>(0x80004005);
                    if (!word(frame + 0x74)) {
                        if (!word(frame + 0x94)) {
                            const u32 device = word(args + 3);
                            table = word(ptr(device));
                            const u32 actual_source = word(args);
                            using Copy = i32(__attribute__((stdcall))*)(void*, void*, void*, void*,
                                                                        void*, u32);
                            result = method<Copy>(table, 0x88)(ptr(device), ptr(destination),
                                                               frame + 0xa8, ptr(actual_source),
                                                               frame + 0xb8, 0);
                        } else if (word(frame + 0x94) == 2) {
                            const u32 device = word(args + 3);
                            table = word(ptr(device));
                            const u32 actual_source = word(args);
                            using Copy =
                                i32(__attribute__((stdcall))*)(void*, void*, void*, void*, void*);
                            result = method<Copy>(table, 0x78)(ptr(device), ptr(destination),
                                                               frame + 0xa8, ptr(actual_source),
                                                               frame + 0xb8);
                        }
                    }
                    FUN_005e9b1d(0);
                    const u32 device = word(args + 3);
                    call1(device, 8);
                    fallback = result < 0;
                }
            }
            if (fallback) {
                const u32 flags = word(args) == destination ? 0x10001 : 1;
                const u32 rect_destination = word(args + 5), palette_destination = word(args + 4);
                result = FUN_005f0510(context, frame, ptr(destination), ptr(palette_destination),
                                      ptr(rect_destination), 0, flags);
                if (result >= 0) {
                    const u32 color = word(args + 7), filter = word(args + 6),
                              actual_palette_destination = word(args + 4);
                    const u32 third = word(frame + 8), second = word(frame + 4),
                              first = word(frame);
                    const u32 rect_source = word(args + 2), palette_source = word(args + 1),
                              actual_source = word(args);
                    result = FUN_005e1d1f(actual_source, palette_source, rect_source, first, second,
                                          third, actual_palette_destination, frame + 0x28, filter,
                                          color);
                    if (result >= 0) {
                        if (!word(frame + 0x94) && word(frame + 0x74)) {
                            table = word(ptr(destination));
                            method<Output>(table, 0xc)(ptr(destination), args);
                            u32 device = word(args);
                            result = static_cast<i32>(call1(device, 0xc));
                            device = word(args);
                            call1(device, 8);
                            result = result ? static_cast<i32>(0x88760868) : 0;
                        } else
                            result = 0;
                    }
                }
            } else
                result = 0;
        }
    }
    FUN_005f050b(context);
    return result;
}
extern "C" __attribute__((naked, stdcall)) int32_t FUN_005e2d78(void*, void*, void*, void*, void*,
                                                                void*, uint32_t, uint32_t) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $200,%esp\n\tleal -200(%ebp),%ecx\n\tleal 8(%ebp),%eax\n\tpushl %ecx\n\tpushl %eax\n\tcalll _recovered_005e2d78\n\taddl $8,%esp\n\tleave\n\tretl $32");
}
