#include "graphics/surface/surface_filter.h"
#include "graphics/surface/surface_transfer.h"
extern "C" int32_t __attribute__((stdcall)) FUN_005e2f8c(void*, void*, void*, void*, void*, void*,
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
u32 byte(const void* p) {
    u32 v;
    __asm__ volatile("movzbl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(void* p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void put_byte(void* p, u32 v) {
    __asm__ volatile("movb %b1,(%0)" ::"r"(p), "q"(v) : "memory");
}
template <class Target> Target method(u32 table, u32 offset) {
    return reinterpret_cast<Target>(word(ptr(table + offset)));
}
u32 call1(u32 object, u32 slot) {
    const u32 table = word(ptr(object));
    using Method = u32(__attribute__((stdcall))*)(void*);
    return method<Method>(table, slot)(ptr(object));
}
void release(void* slot, bool clear = true) {
    const u32 value = word(slot);
    if (value) {
        call1(value, 8);
        if (clear)
            put(slot, 0);
    }
}
bool power_word(u32 value) {
    return !(value & (value - 1));
} // Original includes0.
} // namespace
// Complete5e3014..5e3306. Actual incoming texture word becomes the current
// surface. The96privatebytes atentryESP-100 retain ignored descriptor outputs.
extern "C" int32_t recovered_005e3014(u32* args, unsigned char* frame) {
    const u32 texture = word(args);
    if (!texture)
        return static_cast<i32>(0x8876086c);
    const u32 type = call1(texture, 0x28);
    put(frame + 0x50, type);
    if (type != 3 && type != 4 && type != 5)
        return static_cast<i32>(0x8876086c);
    const bool default_filter = word(args + 3) == 0xffffffff;
    put(frame + 0x48, texture);
    if (default_filter) {
        const u32 current_type = word(frame + 0x50);
        using Desc = i32(__attribute__((stdcall))*)(void*, u32, void*);
        if (current_type == 3) {
            const u32 object = word(frame + 0x48), table = word(ptr(object));
            method<Desc>(table, 0x44)(ptr(object), 0, frame);
            if (!power_word(word(frame + 0x18)) || !power_word(word(frame + 0x1c))) {
                put(args + 3, 0);
                if (!word(args + 3))
                    put(args + 3, 0x80004);
                else
                    put(args + 3, 5);
            } else
                put(args + 3, 5);
        } else if (current_type == 4) {
            const u32 object = word(frame + 0x48), table = word(ptr(object));
            method<Desc>(table, 0x44)(ptr(object), 0, frame + 0x20);
            if (!power_word(word(frame + 0x30)) || !power_word(word(frame + 0x34)) ||
                !power_word(word(frame + 0x38)))
                put(args + 3, 0x80004);
            else
                put(args + 3, 5);
        } else if (current_type == 5) {
            const u32 object = word(frame + 0x48), table = word(ptr(object));
            method<Desc>(table, 0x44)(ptr(object), 0, frame);
            if (!power_word(word(frame + 0x18)) || !power_word(word(frame + 0x1c)))
                put(args + 3, 0x80004);
            else
                put(args + 3, 5);
        } else {
            if (!word(args + 3))
                put(args + 3, 0x80004);
            else
                put(args + 3, 5);
        }
    }
    unsigned char* filter_high = reinterpret_cast<unsigned char*>(args + 3) + 2;
    if (word(frame + 0x50) == 5)
        put_byte(filter_high, byte(filter_high) | 7);
    if (byte(filter_high) & 0x40)
        put_byte(filter_high, byte(filter_high) | 0x60);
    else
        put_byte(filter_high, byte(filter_high) & 0x9f);
    const u32 levels = call1(texture, 0x34);
    const bool default_level = word(args + 2) == 0xffffffff;
    put(frame + 0x40, levels);
    if (default_level)
        put(args + 2, 0);
    if (word(args + 2) >= levels)
        return static_cast<i32>(0x8876086c);
    const bool cube = word(frame + 0x50) == 5;
    put(args, 0);
    put(frame + 0x58, 0);
    put(frame + 0x5c, 0);
    put(frame + 0x54, 0);
    put(frame + 0x3c, cube ? 6 : 1);
    const u32 filter_low = word(args + 3) & 0xff;
    if (filter_low == 2)
        put(frame + 0x44, 1);
    else {
        put(frame + 0x44, 0);
        if (filter_low == 5)
            put(frame + 0x44, 1);
    }
    const u32 faces = word(frame + 0x3c);
    put(frame + 0x4c, 0);
    i32 result = 0;
    if (faces) {
        result = static_cast<i32>(word(args + 3));
        do {
            const u32 current_type = word(frame + 0x50);
            if (current_type == 5) {
                const u32 object = word(frame + 0x48), table = word(ptr(object)),
                          level = word(args + 2), face = word(frame + 0x4c);
                using Get = i32(__attribute__((stdcall))*)(void*, u32, u32, void*);
                result = method<Get>(table, 0x48)(ptr(object), face, level, args);
            } else if (current_type == 3 || current_type == 4) {
                void* output = current_type == 4 ? frame + 0x58 : static_cast<void*>(args);
                const u32 object = word(frame + 0x48), table = word(ptr(object)),
                          level = word(args + 2);
                using Get = i32(__attribute__((stdcall))*)(void*, u32, void*);
                result = method<Get>(table, 0x48)(ptr(object), level, output);
            }
            if (result < 0)
                goto cleanup;
            {
                u32 level = word(args + 2);
                for (;;) {
                    ++level;
                    if (level >= word(frame + 0x40))
                        break;
                    const u32 mip_type = word(frame + 0x50);
                    if (mip_type == 5) {
                        const u32 object = word(frame + 0x48), table = word(ptr(object)),
                                  face = word(frame + 0x4c);
                        using Get = i32(__attribute__((stdcall))*)(void*, u32, u32, void*);
                        result = method<Get>(table, 0x48)(ptr(object), face, level, frame + 0x5c);
                    } else if (mip_type == 3 || mip_type == 4) {
                        void* output = mip_type == 4 ? frame + 0x54 : frame + 0x5c;
                        const u32 object = word(frame + 0x48), table = word(ptr(object));
                        using Get = i32(__attribute__((stdcall))*)(void*, u32, void*);
                        result = method<Get>(table, 0x48)(ptr(object), level, output);
                    }
                    if (result < 0)
                        goto cleanup;
                    const u32 copy_type = word(frame + 0x50);
                    if (copy_type == 3 || copy_type == 5) {
                        const u32 filter = word(args + 3), destination_palette = word(args + 1),
                                  destination = word(args), source_palette = word(args + 1),
                                  source = word(frame + 0x5c);
                        result = FUN_005e2d78(ptr(source), ptr(source_palette), nullptr,
                                              ptr(destination), ptr(destination_palette), nullptr,
                                              filter, 0);
                    } else if (copy_type == 4) {
                        const u32 filter = word(args + 3), destination_palette = word(args + 1),
                                  destination = word(frame + 0x58), source_palette = word(args + 1),
                                  source = word(frame + 0x54);
                        result = FUN_005e2f8c(ptr(source), ptr(source_palette), nullptr,
                                              ptr(destination), ptr(destination_palette), nullptr,
                                              filter, 0);
                    }
                    if (result < 0)
                        goto cleanup;
                    if (word(frame + 0x44)) {
                        release(args);
                        release(frame + 0x58, false);
                        const u32 surface = word(frame + 0x5c);
                        put(args, surface);
                        const u32 volume = word(frame + 0x54);
                        put(frame + 0x5c, 0);
                        put(frame + 0x58, volume);
                        put(frame + 0x54, 0);
                    } else {
                        release(frame + 0x5c);
                        release(frame + 0x54);
                    }
                }
            }
            release(args);
            release(frame + 0x58);
            put(frame + 0x4c, word(frame + 0x4c) + 1);
        } while (word(frame + 0x4c) < word(frame + 0x3c));
        result = 0;
    }
cleanup:
    release(args);
    release(frame + 0x58);
    release(frame + 0x5c);
    release(frame + 0x54, false);
    return result;
}
extern "C" __attribute__((naked, stdcall)) int32_t FUN_005e3014(void*, uint32_t, uint32_t,
                                                                uint32_t) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $96,%esp\n\tleal -96(%ebp),%ecx\n\tleal 8(%ebp),%eax\n\tpushl %ecx\n\tpushl %eax\n\tcalll _recovered_005e3014\n\taddl $8,%esp\n\tleave\n\tretl $16");
}
