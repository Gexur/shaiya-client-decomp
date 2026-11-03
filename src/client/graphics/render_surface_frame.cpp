#include "graphics/render_surface_frame.h"
extern "C" void __attribute__((stdcall)) FUN_005e9b1d(uint32_t);
extern "C" int32_t __attribute__((stdcall)) FUN_005e2d78(void*, void*, void*, void*, void*, void*,
                                                         uint32_t, uint32_t);
extern "C" int32_t __attribute__((stdcall)) FUN_005e3014(void*, uint32_t, uint32_t, uint32_t);
namespace {
using u32 = uint32_t;
using i32 = int32_t;
u32 word(const void* p) {
    u32 result;
    __asm__ volatile("movl (%1),%0" : "=r"(result) : "r"(p) : "memory");
    return result;
}
void put(void* p, u32 value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(value) : "memory");
}
void* ptr(u32 v) {
    return reinterpret_cast<void*>(v);
}
void* at(void* p, u32 offset) {
    return ptr(reinterpret_cast<uintptr_t>(p) + offset);
}
u32 field(void* p, u32 offset) {
    return word(at(p, offset));
}
template <class Target> Target target(u32 table, u32 offset) {
    return reinterpret_cast<Target>(word(ptr(table + offset)));
}
u32 call1(u32 object, u32 slot) {
    const u32 table = word(ptr(object));
    using Method = u32(__attribute__((stdcall))*)(void*);
    return target<Method>(table, slot)(ptr(object));
}
void release_slot(void* slot) {
    const u32 p = word(slot);
    if (p) {
        call1(p, 8);
        put(slot, 0);
    }
}
i32 set_render(u32 device, u32 table, u32 surface) {
    using Method = i32(__attribute__((stdcall))*)(void*, u32, void*);
    return target<Method>(table, 0x94)(ptr(device), 0, ptr(surface));
}
i32 set_depth(u32 device, u32 table, u32 surface) {
    using Method = i32(__attribute__((stdcall))*)(void*, void*);
    return target<Method>(table, 0x9c)(ptr(device), ptr(surface));
}
void fldz() {
    __asm__ volatile("fldz" ::: "st");
}
void fld1() {
    __asm__ volatile("fld1" ::: "st");
}
void fstp(void* p) {
    __asm__ volatile("fstps (%0)" ::"r"(p) : "st", "memory");
}
} // namespace
extern "C" const uint32_t dat_006f0024[4] = {0x85c31227, 0x4f003de5, 0x1af13a9b, 0xb5188cc3};

// Complete original60273d..6029f3; actual36-byte descriptor/private area and
// all three actual incoming argument words remain addressable. In particular
// arg0 changes from self to flag/HRESULT, and arg2 becomes &self[2c].
extern "C" int32_t recovered_0060273d(u32* args, unsigned char* frame) {
    const u32 input = word(args + 1);
    if (!input)
        return static_cast<i32>(0x8876086c);
    void* self = ptr(word(args));
    if (field(self, 0x30))
        return static_cast<i32>(0x8876086c);
    const u32 input_table = word(ptr(input));
    using Output = i32(__attribute__((stdcall))*)(void*, void*);
    target<Output>(input_table, 0x30)(ptr(input), frame);
    const u32 format = field(self, 0x14);
    if (word(frame) != format)
        return static_cast<i32>(0x8876086c);
    const u32 width = field(self, 0xc);
    if (word(frame + 0x18) != width)
        return static_cast<i32>(0x8876086c);
    const u32 height = field(self, 0x10);
    if (word(frame + 0x1c) != height)
        return static_cast<i32>(0x8876086c);
    const u32 usage = word(frame + 8) & 1;
    const u32 viewport = word(args + 2);
    put(args, usage);
    put(at(self, 0x34), usage);
    u32 flag = usage;
    if (viewport) {
        for (u32 i = 0; i < 6; ++i)
            put(at(self, 0x3c + 4 * i), word(ptr(viewport + 4 * i)));
        const u32 viewport_width = field(self, 0x44), viewport_x = field(self, 0x3c);
        if (viewport_x + viewport_width > width)
            return static_cast<i32>(0x8876086c);
        const u32 viewport_height = field(self, 0x48), viewport_y = field(self, 0x40),
                  current_height = field(self, 0x10);
        if (viewport_y + viewport_height > current_height)
            return static_cast<i32>(0x8876086c);
        flag = word(args);
        if (!flag && !word(frame + 0xc) &&
            (viewport_width != width || viewport_height != current_height))
            return static_cast<i32>(0x8876086c);
        flag = word(args); // Original6027f1 reloads the overwritten actual self word.
    } else {
        fldz();
        put(at(self, 0x3c), 0);
        fstp(at(self, 0x4c));
        put(at(self, 0x40), 0);
        fld1();
        put(at(self, 0x44), width);
        fstp(at(self, 0x50));
        put(at(self, 0x48), height);
    }
    void* color = at(self, 0x20);
    if (!word(color) && !flag) {
        const u32 device = field(self, 8), table = word(ptr(device)),
                  current_format = field(self, 0x14), current_height = field(self, 0x10);
        using Create =
            i32(__attribute__((stdcall))*)(void*, u32, u32, u32, u32, u32, u32, void*, void*);
        const i32 result = target<Create>(table, 0x70)(ptr(device), width, current_height,
                                                       current_format, 0, 0, 1, color, nullptr);
        if (result < 0)
            return result;
    }
    void* depth = at(self, 0x28);
    if (!word(depth) && field(self, 0x18)) {
        const u32 depth_format = field(self, 0x1c);
        if (depth_format == 70)
            put(args, 0);
        else {
            put(args, 1);
            if (depth_format == 82)
                put(args, 0);
        }
        const u32 device = field(self, 8), table = word(ptr(device)), discard = word(args),
                  current_height = field(self, 0x10), current_width = field(self, 0xc);
        using Create =
            i32(__attribute__((stdcall))*)(void*, u32, u32, u32, u32, u32, u32, void*, void*);
        const i32 result = target<Create>(table, 0x74)(ptr(device), current_width, current_height,
                                                       depth_format, 0, 0, discard, depth, nullptr);
        if (result < 0)
            return result;
    }
    void* state_slot = at(self, 0x38);
    const u32 state = word(state_slot);
    put(frame + 0x20, reinterpret_cast<uintptr_t>(state_slot));
    if (!state) {
        call1(field(self, 8), 0xf0);
        u32 device = field(self, 8), table = word(ptr(device));
        target<Output>(table, 0xbc)(ptr(device), at(self, 0x3c));
        device = field(self, 8);
        table = word(ptr(device));
        target<Output>(table, 0xf4)(ptr(device), state_slot);
    }
    void* old_color = at(self, 0x24);
    release_slot(old_color);
    put(args + 2, reinterpret_cast<uintptr_t>(at(self, 0x2c)));
    u32 old = field(self, 0x2c);
    if (old) {
        call1(old, 8);
        put(ptr(word(args + 2)), 0);
    }
    call1(word(ptr(word(frame + 0x20))), 0x10);
    u32 device = field(self, 8), table = word(ptr(device));
    using GetRender = i32(__attribute__((stdcall))*)(void*, u32, void*);
    target<GetRender>(table, 0x98)(ptr(device), 0, old_color);
    device = field(self, 8);
    const u32 old_depth = word(args + 2);
    table = word(ptr(device));
    target<Output>(table, 0xa0)(ptr(device), ptr(old_depth));
    const u32 render_flag = field(self, 0x34);
    u32 selected = word(args + 1);
    if (!render_flag)
        selected = field(self, 0x20);
    device = field(self, 8);
    table = word(ptr(device));
    i32 result = set_render(device, table, selected);
    if (result < 0)
        return result;
    device = field(self, 8);
    const u32 depth_surface = field(self, 0x28);
    table = word(ptr(device));
    result = set_depth(device, table, depth_surface);
    put(args, static_cast<u32>(result));
    if (result < 0) {
        const u32 saved = word(old_color);
        device = field(self, 8);
        table = word(ptr(device));
        set_render(device, table, saved);
        release_slot(old_color);
        return static_cast<i32>(word(args));
    }
    device = field(self, 8);
    table = word(ptr(device));
    result = target<Output>(table, 0xbc)(ptr(device), at(self, 0x3c));
    put(args, static_cast<u32>(result));
    // Original reloads the next device/table before inspecting this HRESULT.
    device = field(self, 8);
    table = word(ptr(device));
    void* depth_restore_slot;
    if (result < 0) {
        set_render(device, table, word(old_color));
        device = field(self, 8);
        depth_restore_slot = ptr(word(args + 2));
        const u32 saved = word(depth_restore_slot);
        table = word(ptr(device));
        set_depth(device, table, saved);
    } else {
        using Begin = i32(__attribute__((stdcall))*)(void*);
        result = target<Begin>(table, 0xa4)(ptr(device));
        put(args, static_cast<u32>(result));
        if (result >= 0) {
            const u32 current = word(args + 1);
            put(at(self, 0x30), current);
            call1(current, 4);
            return 0;
        }
        FUN_005e9b1d(1);
        const u32 saved = word(old_color);
        device = field(self, 8);
        table = word(ptr(device));
        set_render(device, table, saved);
        device = field(self, 8);
        depth_restore_slot = ptr(word(args + 2));
        const u32 saved_depth = word(depth_restore_slot);
        table = word(ptr(device));
        set_depth(device, table, saved_depth);
        call1(word(ptr(word(frame + 0x20))), 0x14);
        FUN_005e9b1d(0);
    }
    release_slot(old_color);
    release_slot(depth_restore_slot);
    return static_cast<i32>(word(args));
}
extern "C" __attribute__((naked, stdcall)) int32_t FUN_0060273d(void*, u32, u32) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $36,%esp\n\tleal -36(%ebp),%ecx\n\tleal 8(%ebp),%eax\n\tpushl %ecx\n\tpushl %eax\n\tcalll _recovered_0060273d\n\taddl $8,%esp\n\tleave\n\tretl $12");
}

// Complete original6029f3..602b70, retaining the actual self argument word as
// the QueryInterface output, original private RECT/count/surface words, and
// all ignored HRESULTs. The two D3DX transfer bodies remain real declarations.
extern "C" int32_t recovered_006029f3(u32* args, unsigned char* frame) {
    void* self = ptr(word(args));
    if (!field(self, 0x30))
        return static_cast<i32>(0x8876086c);
    call1(field(self, 8), 0xa8);
    if (!field(self, 0x34)) {
        const u32 x = field(self, 0x3c), width = field(self, 0x44), y = field(self, 0x40);
        put(frame, x);
        const u32 height = field(self, 0x48);
        put(frame + 0xc, y + height);
        const u32 destination = field(self, 0x20);
        put(frame + 4, y);
        const u32 source = field(self, 0x30);
        put(frame + 8, width + x);
        const i32 result =
            FUN_005e2d78(ptr(source), nullptr, frame, ptr(destination), nullptr, frame, 1, 0);
        if (result < 0)
            return result;
    }
    FUN_005e9b1d(1);
    u32 surface = field(self, 0x24), device = field(self, 8), table = word(ptr(device));
    set_render(device, table, surface);
    device = field(self, 8);
    surface = field(self, 0x2c);
    table = word(ptr(device));
    set_depth(device, table, surface);
    call1(field(self, 0x38), 0x14);
    FUN_005e9b1d(0);
    release_slot(at(self, 0x24));
    release_slot(at(self, 0x2c));
    if (word(args + 1)) {
        FUN_005e9b1d(1);
        surface = field(self, 0x30);
        table = word(ptr(surface));
        using Query = i32(__attribute__((stdcall))*)(void*, const void*, void*);
        const i32 queried = target<Query>(table, 0x2c)(ptr(surface), dat_006f0024, args);
        FUN_005e9b1d(0);
        if (queried >= 0) {
            u32 texture = word(args);
            const u32 levels = call1(texture, 0x34);
            put(frame + 0x10, levels);
            u32 level = 0;
            if (levels) {
                do {
                    texture = word(args);
                    table = word(ptr(texture));
                    using Level = i32(__attribute__((stdcall))*)(void*, u32, void*);
                    target<Level>(table, 0x48)(ptr(texture), level, frame + 0x14);
                    const u32 current = word(frame + 0x14);
                    call1(current, 8);
                    const u32 original = field(self, 0x30);
                    if (original == word(frame + 0x14))
                        break;
                    ++level;
                } while (level < word(frame + 0x10));
            }
            const u32 requested = word(args + 1), current = word(args);
            const i32 result = FUN_005e3014(ptr(current), 0, level, requested);
            texture = word(args);
            if (result < 0) {
                if (texture) {
                    call1(texture, 8);
                    put(args, 0);
                }
                release_slot(at(self, 0x30));
                return result;
            }
            if (texture)
                call1(texture, 8);
        }
    }
    release_slot(at(self, 0x30));
    return 0;
}
extern "C" __attribute__((naked, stdcall)) int32_t FUN_006029f3(void*, u32) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $24,%esp\n\tleal -24(%ebp),%ecx\n\tleal 8(%ebp),%eax\n\tpushl %ecx\n\tpushl %eax\n\tcalll _recovered_006029f3\n\taddl $8,%esp\n\tleave\n\tretl $8");
}
