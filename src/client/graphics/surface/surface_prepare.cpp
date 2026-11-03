#include "graphics/surface/surface_prepare.h"
#include "graphics/surface/surface_transfer_context.h"
#include "graphics/render_surface_frame.h"
extern "C" void __attribute__((stdcall)) FUN_005e9b1d(uint32_t);
namespace {
using u32 = uint32_t;
using i32 = int32_t;
void* ptr(u32 p) {
    return reinterpret_cast<void*>(p);
}
void* at(void* p, u32 n) {
    return ptr(reinterpret_cast<uintptr_t>(p) + n);
}
u32 word(const void* p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
u32 byte(const void* p) {
    u32 v;
    __asm__ volatile("movzbl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(void* p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void clear(void* p) {
    __asm__ volatile("andl $0,(%0)" ::"r"(p) : "memory", "cc");
}
void subtract(void* p, u32 v) {
    __asm__ volatile("subl %1,(%0)" ::"r"(p), "r"(v) : "memory", "cc");
}
template <class Target> Target method(u32 table, u32 offset) {
    return reinterpret_cast<Target>(word(ptr(table + offset)));
}
u32 call1(u32 object, u32 slot) {
    const u32 table = word(ptr(object));
    using Method = u32(__attribute__((stdcall))*)(void*);
    return method<Method>(table, slot)(ptr(object));
}
void release(void* slot) {
    const u32 p = word(slot);
    if (p) {
        call1(p, 8);
        clear(slot);
    }
}
void copy4(void* to, u32 from) {
    for (u32 i = 0; i != 4; ++i)
        put(at(to, i * 4), word(ptr(from + i * 4)));
}
bool dxt(u32 f) {
    return f == 0x31545844 || f == 0x32545844 || f == 0x33545844 || f == 0x34545844 ||
           f == 0x35545844;
}
} // namespace
// Complete1263-byte original5f0510..5f09ff. This adapter retains112 actual
// private bytes atentryESP-116; output and context remain distinct raw views.
extern "C" int32_t recovered_005f0510(u32* args, unsigned char* frame, u32 entry_self) {
    put(frame + 0x5c, entry_self);
    FUN_005f042e(ptr(entry_self));
    const u32 initial_surface = word(args + 1);
    u32 table = word(ptr(initial_surface));
    using Output = i32(__attribute__((stdcall))*)(void*, void*);
    method<Output>(table, 0x30)(ptr(initial_surface), frame);
    const u32 input_rect = word(args + 3);
    if (input_rect) {
        copy4(frame + 0x30, input_rect);
        if (static_cast<i32>(word(frame + 0x30)) < 0)
            return static_cast<i32>(0x8876086c);
        const u32 right = word(frame + 0x38);
        if (right > word(frame + 0x18) ||
            static_cast<i32>(word(frame + 0x30)) > static_cast<i32>(right))
            return static_cast<i32>(0x8876086c);
        if (static_cast<i32>(word(frame + 0x34)) < 0)
            return static_cast<i32>(0x8876086c);
        const u32 bottom = word(frame + 0x3c);
        if (bottom > word(frame + 0x1c) ||
            static_cast<i32>(word(frame + 0x34)) > static_cast<i32>(bottom))
            return static_cast<i32>(0x8876086c);
        if (word(frame + 0x30) || right != word(frame + 0x18) || word(frame + 0x34))
            put(frame + 0x6c, 1);
        else {
            const bool full = bottom == word(frame + 0x1c);
            put(frame + 0x6c, 0);
            if (!full)
                put(frame + 0x6c, 1);
        }
        if (byte(args + 5) & 1)
            put(frame + 0x58, 0);
        else if (word(frame + 0x6c))
            put(frame + 0x58, 0);
        else
            put(frame + 0x58, 1);
    } else {
        put(frame + 0x38, word(frame + 0x18));
        put(frame + 0x3c, word(frame + 0x1c));
        const u32 flags = word(args + 5);
        put(frame + 0x30, 0);
        put(frame + 0x34, 0);
        put(frame + 0x6c, 0);
        put(frame + 0x58, (~flags) & 1);
    }
    const u32 alternate = word(args + 5) & 0x10000;
    put(frame + 0x48, alternate);
    if (alternate) {
        const u32 format = word(frame), width = word(frame + 0x18), height = word(frame + 0x1c);
        put(frame + 0x4c, width);
        put(frame + 0x50, height);
        put(frame + 0x64, 0);
        if (dxt(format)) {
            const u32 combined = height | width;
            if (combined & 3) {
                do {
                    put(frame + 0x64, word(frame + 0x64) + 1);
                } while ((combined << (word(frame + 0x64) & 31)) & 3);
            }
        }
        const u32 saved_self = word(frame + 0x5c), actual_surface = word(args + 1);
        table = word(ptr(actual_surface));
        void* device_slot = ptr(saved_self + 0x10);
        method<Output>(table, 0xc)(ptr(actual_surface), device_slot);
        const u32 pool = word(frame + 0xc) == 3 ? 3 : 2, device = word(device_slot);
        table = word(ptr(device));
        void* texture_slot = ptr(saved_self + 0xc);
        const u32 actual_format = word(frame), level = word(frame + 0x64),
                  scaled_height = word(frame + 0x50) << (level & 31),
                  scaled_width = word(frame + 0x4c) << (level & 31);
        using CreateTexture =
            i32(__attribute__((stdcall))*)(void*, u32, u32, u32, u32, u32, u32, void*, u32);
        i32 result =
            method<CreateTexture>(table, 0x5c)(ptr(device), scaled_width, scaled_height, level + 1,
                                               0, actual_format, pool, texture_slot, 0);
        put(frame + 0x68, static_cast<u32>(result));
        void* surface_slot;
        if (result >= 0) {
            const u32 current_self = word(frame + 0x5c), texture = word(texture_slot);
            table = word(ptr(texture));
            surface_slot = ptr(current_self + 8);
            const u32 actual_level = word(frame + 0x64);
            using GetSurface = i32(__attribute__((stdcall))*)(void*, u32, void*);
            result = method<GetSurface>(table, 0x48)(ptr(texture), actual_level, surface_slot);
            put(frame + 0x68, static_cast<u32>(result));
            if (result >= 0) {
                if (!word(frame + 0x58)) {
                    clear(frame + 0x60);
                    FUN_005e9b1d(1);
                    const u32 to = word(surface_slot), from = word(args + 1);
                    result = FUN_005f034f(ptr(from), ptr(to));
                    put(frame + 0x68, static_cast<u32>(result));
                    FUN_005e9b1d(0);
                    if (static_cast<i32>(word(frame + 0x68)) < 0) {
                        if (!word(frame + 0x64)) {
                            u32 object = word(device_slot);
                            table = word(ptr(object));
                            const u32 fmt = word(frame), h = word(frame + 0x50),
                                      w = word(frame + 0x4c);
                            using CreateRender = i32(__attribute__((stdcall))*)(
                                void*, u32, u32, u32, u32, u32, u32, void*, u32);
                            result = method<CreateRender>(table, 0x70)(ptr(object), w, h, fmt, 0, 0,
                                                                       1, frame + 0x60, 0);
                            put(frame + 0x68, static_cast<u32>(result));
                            if (result >= 0) {
                                object = word(device_slot);
                                table = word(ptr(object));
                                const u32 temporary = word(frame + 0x60),
                                          actual_from = word(args + 1);
                                using Stretch = i32(__attribute__((stdcall))*)(void*, void*, u32,
                                                                               void*, u32, u32);
                                result = method<Stretch>(table, 0x88)(ptr(object), ptr(actual_from),
                                                                      0, ptr(temporary), 0, 0);
                                put(frame + 0x68, static_cast<u32>(result));
                                if (result >= 0) {
                                    const u32 actual_to = word(surface_slot),
                                              actual_temporary = word(frame + 0x60);
                                    result = FUN_005f034f(ptr(actual_temporary), ptr(actual_to));
                                    put(frame + 0x68, static_cast<u32>(result));
                                    call1(word(frame + 0x60), 8);
                                    if (static_cast<i32>(word(frame + 0x68)) >= 0)
                                        goto have_surface;
                                } else
                                    call1(word(frame + 0x60), 8);
                            }
                        }
                        release(surface_slot);
                        release(texture_slot);
                        release(device_slot);
                        return static_cast<i32>(word(frame + 0x68));
                    }
                }
            have_surface:
                put(frame + 0x60, word(surface_slot));
            } else {
                const u32 current_self = word(frame + 0x5c);
                release(ptr(current_self + 8));
                release(texture_slot);
                release(device_slot);
                return static_cast<i32>(word(frame + 0x68));
            }
        } else {
            const u32 current_self = word(frame + 0x5c);
            release(ptr(current_self + 8));
            release(texture_slot);
            release(device_slot);
            return static_cast<i32>(word(frame + 0x68));
        }
    } else
        put(frame + 0x60, initial_surface);
    u32 lock_flags = ((byte(args + 5) & 1) | 0x80) << 4;
    bool direct_lock = false;
    if (word(frame + 0x58) && !word(frame + 0x48) && (byte(frame + 9) & 2)) {
        if (byte(reinterpret_cast<unsigned char*>(args + 5) + 2) & 2) {
            lock_flags |= 0x2000;
            put(frame + 0x6c, 0);
            direct_lock = true;
        } else {
            FUN_005e9b1d(1);
            const u32 object = word(args + 1);
            table = word(ptr(object));
            using Query = i32(__attribute__((stdcall))*)(void*, const void*, void*);
            const i32 result = method<Query>(table, 0x2c)(ptr(object), dat_006f0024, frame + 0x54);
            if (result >= 0) {
                if (call1(word(frame + 0x54), 0x34) == 1) {
                    lock_flags |= 0x2000;
                    clear(frame + 0x6c);
                }
                release(frame + 0x54);
            }
            FUN_005e9b1d(0);
        }
    }
    if (!direct_lock) {
        if (word(frame + 0x6c)) {
            const u32 format = word(frame);
            if (dxt(format)) {
                u32 right = word(frame + 0x38), bottom = word(frame + 0x3c);
                const u32 left = word(frame + 0x30) & 0xfffffffc,
                          top = word(frame + 0x34) & 0xfffffffc;
                right = (right + 3) & 0xfffffffc;
                bottom = (bottom + 3) & 0xfffffffc;
                const bool clamp_right = right > word(frame + 0x18);
                put(frame + 0x20, left);
                put(frame + 0x28, right);
                put(frame + 0x24, top);
                put(frame + 0x2c, bottom);
                if (clamp_right) {
                    right = word(frame + 0x18);
                    put(frame + 0x28, right);
                }
                if (bottom > word(frame + 0x1c)) {
                    bottom = word(frame + 0x1c);
                    put(frame + 0x2c, bottom);
                }
                if (!left && right == word(frame + 0x18) && !top && bottom == word(frame + 0x1c))
                    clear(frame + 0x6c);
                else
                    put(frame + 0x6c, 1);
            } else if (format == 0x32595559 || format == 0x42475247 || format == 0x47424752 ||
                       format == 0x59565955) {
                const u32 left = word(frame + 0x30) & 0xfffffffe;
                u32 right = (word(frame + 0x38) + 1) & 0xfffffffe;
                const u32 top = word(frame + 0x34), bottom = word(frame + 0x3c);
                const bool clamp_right = right > word(frame + 0x18);
                put(frame + 0x20, left);
                put(frame + 0x28, right);
                put(frame + 0x24, top);
                put(frame + 0x2c, bottom);
                if (clamp_right) {
                    right = word(frame + 0x18);
                    put(frame + 0x28, right);
                }
                if (!left && right == word(frame + 0x18) && !top && bottom == word(frame + 0x1c))
                    clear(frame + 0x6c);
                else
                    put(frame + 0x6c, 1);
            } else
                copy4(frame + 0x20, reinterpret_cast<u32>(frame + 0x30));
        }
    }
    using Lock = i32(__attribute__((stdcall))*)(void*, void*, void*, u32);
    if (!direct_lock && word(frame + 0x48)) {
        const bool rectangle = word(frame + 0x6c) != 0;
        const u32 object = word(frame + 0x60);
        table = word(ptr(object));
        const i32 result = method<Lock>(table, 0x34)(
            ptr(object), frame + 0x40, rectangle ? frame + 0x20 : nullptr, lock_flags);
        if (result < 0)
            return result;
    } else {
        FUN_005e9b1d(1);
        const bool rectangle = word(frame + 0x6c) != 0;
        const u32 object = word(frame + 0x60);
        table = word(ptr(object));
        const i32 result = method<Lock>(table, 0x34)(
            ptr(object), frame + 0x40, rectangle ? frame + 0x20 : nullptr, lock_flags);
        FUN_005e9b1d(0);
        if (result < 0) {
            const u32 flags = word(args + 5) | 0x10000, self = word(frame + 0x5c),
                      extra = word(args + 4), rect = word(args + 3), palette = word(args + 2),
                      surface = word(args + 1), output = word(args);
            return FUN_005f0510(ptr(self), ptr(output), ptr(surface), ptr(palette), ptr(rect),
                                extra, flags);
        }
    }
    if (word(frame + 0x6c)) {
        const u32 left = word(frame + 0x20);
        subtract(frame + 0x30, left);
        subtract(frame + 0x38, left);
        const u32 top = word(frame + 0x24);
        subtract(frame + 0x34, top);
        subtract(frame + 0x3c, top);
    }
    const u32 output = word(args);
    put(ptr(output), word(frame + 0x44));
    put(ptr(output + 4), word(frame));
    put(ptr(output + 8), word(frame + 0x40));
    put(ptr(output + 0x18), word(frame + 0x18));
    put(ptr(output + 0x1c), word(frame + 0x1c));
    put(ptr(output + 0x28), word(frame + 0x30));
    put(ptr(output + 0x24), 1);
    put(ptr(output + 0x2c), word(frame + 0x34));
    put(ptr(output + 0x3c), 1);
    put(ptr(output + 0x40), 1);
    put(ptr(output + 0x4c), word(args + 4));
    const u32 palette = word(args + 2);
    put(ptr(output + 0x30), word(frame + 0x38));
    put(ptr(output + 0xc), 0);
    put(ptr(output + 0x10), 0);
    put(ptr(output + 0x14), 0);
    put(ptr(output + 0x20), 0);
    put(ptr(output + 0x38), 0);
    put(ptr(output + 0x44), 0);
    put(ptr(output + 0x48), 0);
    const u32 flags = word(args + 5);
    put(ptr(output + 0x50), palette);
    const u32 actual_surface = word(args + 1), self = word(frame + 0x5c);
    put(ptr(output + 0x34), word(frame + 0x3c));
    put(ptr(self + 4), actual_surface);
    put(ptr(self), flags);
    call1(actual_surface, 4);
    return 0;
}
extern "C" __attribute__((naked, thiscall)) int32_t FUN_005f0510(void*, void*, void*, void*, void*,
                                                                 uint32_t, uint32_t) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $112,%esp\n\tleal -112(%ebp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %ecx\n\tpushl %edx\n\tpushl %eax\n\tcalll _recovered_005f0510\n\taddl $12,%esp\n\tleave\n\tretl $24");
}
