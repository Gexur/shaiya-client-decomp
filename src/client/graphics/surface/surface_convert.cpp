#include "graphics/surface/surface_convert.h"
#include "graphics/surface/surface_prepare.h"
#include "graphics/surface/surface_transfer_context.h"
extern "C" uint32_t __attribute__((stdcall)) FUN_005fb453(void*);
extern "C" int32_t __attribute__((thiscall)) FUN_005f2032(void*, void*);
#define FILTER(address) extern "C" int32_t __attribute__((thiscall)) FUN_##address(void*)
FILTER(005edcc4);
FILTER(005eddce);
FILTER(005edea1);
FILTER(005ee074);
FILTER(005ee24a);
FILTER(005ee612);
FILTER(005eeb06);
FILTER(005eeea8);
FILTER(005efc3f);
FILTER(005ef5b9);
#undef FILTER
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
void put(void* p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void clear(void* p) {
    __asm__ volatile("andl $0,(%0)" ::"r"(p) : "memory", "cc");
}
u32 deleting(u32 object) {
    const u32 table = word(ptr(object)), entry = word(ptr(table));
    using Method = u32(__attribute__((thiscall))*)(void*, u32);
    return reinterpret_cast<Method>(entry)(ptr(object), 1);
}
void release(void* slot) {
    const u32 value = word(slot);
    if (value) {
        deleting(value);
        clear(slot);
    }
}
void copy_words(void* to, u32 from, u32 count) {
    for (u32 i = 0; i < count; ++i)
        put(at(to, 4 * i), word(ptr(from + 4 * i)));
}
} // namespace
// Complete original8-byte observed constructor prefix, reverse slot order.
extern "C" __attribute__((noinline, thiscall)) void* FUN_005ec9be(void* self) {
    clear(at(self, 4));
    clear(self);
    return self;
}
// Empty original destruction preserves incoming EAX. The tiny entry bridge
// retains that real register input while all work remains ordinary C++.
extern "C" uint32_t recovered_005ec9c8(u32 self, u32 incoming) {
    u32 result = incoming;
    const u32 second = word(ptr(self + 4));
    if (second)
        result = deleting(second);
    const u32 first = word(ptr(self));
    if (first)
        result = deleting(first);
    return result;
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005ec9c8(void*) {
    __asm__ volatile(
        "pushl %eax\n\tpushl %ecx\n\tcalll _recovered_005ec9c8\n\taddl $8,%esp\n\tretl");
}
// Complete5f01ff..5f033c: real fallback order and exact factory/configure
// boundaries. The twelve pixel factory/backend routines remain declarations.
extern "C" int32_t recovered_005f01ff(u32* args, u32 self) {
    const u32 flags = word(args + 2);
    clear(ptr(self + 4));
    clear(ptr(self));
    put(ptr(self + 8), flags);
    const u32 kind = flags & 0xffff;
    if (!kind || kind > 5 || (flags & 0xff800000))
        return static_cast<i32>(0x8876086c);
    const u32 destination = word(args + 1);
    put(ptr(destination + 0x48), flags & 0x200000);
    const u32 source = word(args);
    put(ptr(source + 0x48), flags & 0x400000);
    put(ptr(source + 0x40), flags & 0x80000);
    put(ptr(source + 0x44), flags & 0x100000);
    u32 converted = FUN_005fb453(ptr(source));
    put(ptr(self + 4), converted);
    i32 result = static_cast<i32>(0x80004005);
    if (converted) {
        converted = FUN_005fb453(ptr(destination));
        put(ptr(self), converted);
        if (converted) {
            const u32 input = word(ptr(self + 4));
            result = FUN_005f2032(ptr(input), ptr(converted));
            if (result >= 0) {
                if (FUN_005edcc4(ptr(self)) >= 0 || FUN_005eddce(ptr(self)) >= 0 ||
                    FUN_005edea1(ptr(self)) >= 0 || FUN_005ee074(ptr(self)) >= 0 ||
                    FUN_005ee24a(ptr(self)) >= 0 || FUN_005ee612(ptr(self)) >= 0 ||
                    FUN_005eeb06(ptr(self)) >= 0 || FUN_005eeea8(ptr(self)) >= 0 ||
                    FUN_005efc3f(ptr(self)) >= 0 || FUN_005ef5b9(ptr(self)) >= 0)
                    result = 0;
                else
                    result = static_cast<i32>(0x80004005);
            }
        }
    }
    release(ptr(self + 4));
    release(ptr(self));
    return result;
}
extern "C" __attribute__((naked, thiscall)) int32_t FUN_005f01ff(void*, void*, void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %ecx\n\tpushl %eax\n\tcalll _recovered_005f01ff\n\taddl $8,%esp\n\tretl $12");
}
// Complete5e1d1f..5e1e07,200privatebytes atentryESP-204. Source/destination
// descriptors are84bytes each; owner-pair+bc is separate from context+54.
extern "C" int32_t recovered_005e1d1f(u32* args, unsigned char* frame) {
    void* owner = frame + 0xbc;
    FUN_005ec9be(owner);
    void* context = frame + 0x54;
    FUN_005f033c(context);
    i32 result = 0;
    if (!word(args))
        result = static_cast<i32>(0x8876086c);
    else {
        const u32 cached_destination = word(args + 3);
        if (!cached_destination || !word(args + 7))
            result = static_cast<i32>(0x8876086c);
        else {
            if (word(args + 8) == 0xffffffff)
                put(args + 8, 0x80004);
            const u32 rectangle = word(args + 2), palette = word(args + 1), surface = word(args);
            result = FUN_005f0510(context, frame, ptr(surface), ptr(palette), ptr(rectangle), 0, 0);
            if (result >= 0) {
                put(frame + 0x6c, word(args + 4));
                put(frame + 0x70, word(args + 5));
                const u32 prepared_field = word(frame + 0x48);
                put(frame + 0x68, cached_destination);
                const u32 destination_rectangle = word(args + 7);
                put(frame + 0x74, 0);
                copy_words(frame + 0x78, destination_rectangle, 4);
                const u32 filter = word(args + 8);
                put(frame + 0x88, 0);
                put(frame + 0x8c, 1);
                copy_words(frame + 0x90, reinterpret_cast<u32>(frame + 0x78), 6);
                put(frame + 0xb0, prepared_field);
                put(frame + 0xb4, word(args + 9));
                put(frame + 0xb8, word(args + 6));
                result = FUN_005f01ff(owner, frame, frame + 0x68, filter);
                if (result >= 0)
                    result = 0;
            }
        }
    }
    FUN_005f050b(context);
    FUN_005ec9c8(owner);
    return result;
}
extern "C" __attribute__((naked, stdcall)) int32_t FUN_005e1d1f(uint32_t, uint32_t, uint32_t,
                                                                uint32_t, uint32_t, uint32_t,
                                                                uint32_t, void*, uint32_t,
                                                                uint32_t) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $200,%esp\n\tleal -200(%ebp),%ecx\n\tleal 8(%ebp),%eax\n\tpushl %ecx\n\tpushl %eax\n\tcalll _recovered_005e1d1f\n\taddl $8,%esp\n\tleave\n\tretl $40");
}
