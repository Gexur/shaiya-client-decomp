#include "graphics/surface/surface_transfer_context.h"
extern "C" void __attribute__((stdcall)) FUN_005e9b1d(uint32_t);
namespace {
using u32 = uint32_t;
using i32 = int32_t;
void* ptr(u32 p) {
    return reinterpret_cast<void*>(p);
}
void* at(void* p, u32 o) {
    return ptr(reinterpret_cast<uintptr_t>(p) + o);
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
template <class Target> Target method(u32 table, u32 offset) {
    return reinterpret_cast<Target>(word(ptr(table + offset)));
}
u32 call1(u32 object, u32 slot) {
    using Method = u32(__attribute__((stdcall))*)(void*);
    const u32 table = word(ptr(object));
    return method<Method>(table, slot)(ptr(object));
}
void release(void* self, u32 offset) {
    const u32 p = word(at(self, offset));
    if (p) {
        call1(p, 8);
        put(at(self, offset), 0);
    }
}
void copy_row(u32 destination, u32 source, u32 bytes) {
    // Original ordered REP MOVSD followed by REP MOVSB, preserving forward
    // overlap and actual DWORD versus BYTE access widths. This is no memcpy.
    u32 count = bytes >> 2;
    __asm__ volatile("rep movsl" : "+D"(destination), "+S"(source), "+c"(count)::"memory");
    count = bytes & 3;
    __asm__ volatile("rep movsb" : "+D"(destination), "+S"(source), "+c"(count)::"memory");
}
} // namespace
// Only the observed first20bytes are initialized, not an invented whole class.
extern "C" __attribute__((noinline, thiscall)) void* FUN_005f033c(void* self) {
    put(self, 0);
    put(at(self, 4), 0);
    put(at(self, 8), 0);
    put(at(self, 12), 0);
    put(at(self, 16), 0);
    return self;
}

// Complete5f034f..5f042e; original56privatebytes atentryESP-60 remain real
// backing, including ignored/partial GetDesc and successful-lock outputs.
extern "C" int32_t recovered_005f034f(u32* args, unsigned char* frame) {
    u32 source = word(args), table = word(ptr(source));
    using Output = i32(__attribute__((stdcall))*)(void*, void*);
    method<Output>(table, 0x30)(ptr(source), frame);
    table = word(ptr(source));
    using Lock = i32(__attribute__((stdcall))*)(void*, void*, void*, u32);
    const i32 first = method<Lock>(table, 0x34)(ptr(source), frame + 0x28, nullptr, 0);
    if (first < 0)
        return first;
    u32 destination = word(args + 1);
    table = word(ptr(destination));
    const i32 second = method<Lock>(table, 0x34)(ptr(destination), frame + 0x20, nullptr, 0);
    i32 result = 0;
    if (second < 0)
        result = second;
    else {
        const u32 format = word(frame);
        u32 height;
        if (format == 0x31545844 || format == 0x32545844 || format == 0x33545844 ||
            format == 0x34545844 || format == 0x35545844) {
            height = (word(frame + 0x1c) + 3) >> 2;
            put(frame + 0x1c, height);
        } else
            height = word(frame + 0x1c);
        const u32 destination_pitch = word(frame + 0x20), source_pitch = word(frame + 0x28);
        put(frame + 0x30, destination_pitch);
        if (static_cast<i32>(destination_pitch) >= static_cast<i32>(source_pitch))
            put(frame + 0x30, source_pitch);
        u32 from = word(frame + 0x2c), to = word(frame + 0x24);
        put(frame + 0x34, 0);
        if (height) {
            do {
                const u32 count = word(frame + 0x30);
                copy_row(to, from, count);
                from += word(frame + 0x28);
                to += word(frame + 0x20);
                const u32 next = word(frame + 0x34) + 1;
                put(frame + 0x34, next);
            } while (word(frame + 0x34) < word(frame + 0x1c));
            // Original reload occurs only after a nonempty copy loop; zero-height
            // and destination-lock failure paths keep their original cached objects.
            destination = word(args + 1);
            source = word(args);
        }
        call1(destination, 0x38);
    }
    call1(source, 0x38);
    return result;
}
extern "C" __attribute__((naked, stdcall)) int32_t FUN_005f034f(void*, void*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $56,%esp\n\tleal -56(%ebp),%ecx\n\tleal 8(%ebp),%eax\n\tpushl %ecx\n\tpushl %eax\n\tcalll _recovered_005f034f\n\taddl $8,%esp\n\tleave\n\tretl $8");
}
extern "C" __attribute__((noinline, thiscall)) int32_t FUN_005f042e(void* self) {
    u32 unlocked = word(at(self, 8));
    if (!unlocked)
        unlocked = word(at(self, 4));
    if (unlocked)
        call1(unlocked, 0x38);
    if (word(at(self, 4)) && word(at(self, 8)) && word(at(self, 0x10)) && !(byte(self) & 1)) {
        FUN_005e9b1d(1);
        const u32 device = word(at(self, 0x10)), table = word(ptr(device)),
                  destination = word(at(self, 4)), source = word(at(self, 8));
        using Update = i32(__attribute__((stdcall))*)(void*, void*, void*, void*, void*);
        const i32 result = method<Update>(table, 0x78)(ptr(device), ptr(source), nullptr,
                                                       ptr(destination), nullptr);
        FUN_005e9b1d(0);
        if (result < 0) {
            FUN_005e9b1d(1);
            const u32 to = word(at(self, 4)), from = word(at(self, 8));
            FUN_005f034f(ptr(from), ptr(to));
            FUN_005e9b1d(0);
        }
    }
    release(self, 8);
    release(self, 12);
    release(self, 16);
    release(self, 4);
    return 0;
}
extern "C" __attribute__((naked, thiscall)) int32_t FUN_005f050b(void*) {
    __asm__ volatile("jmp _FUN_005f042e");
}
