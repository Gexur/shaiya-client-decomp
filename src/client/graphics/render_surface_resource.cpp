#include "graphics/render_surface_resource.h"
#include "runtime/allocations.h"
namespace {
using u32 = uint32_t;
u32 word(const void* p) {
    u32 result;
    __asm__ volatile("movl (%1),%0" : "=r"(result) : "r"(p) : "memory");
    return result;
}
void put(void* p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
u32 byte(const void* p) {
    u32 result;
    __asm__ volatile("movzbl (%1),%0" : "=r"(result) : "r"(p) : "memory");
    return result;
}
void and_zero(void* p) {
    __asm__ volatile("andl $0,(%0)" ::"r"(p) : "cc", "memory");
}
void* at(void* p, u32 offset) {
    return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(p) + offset);
}
const void* at(const void* p, u32 offset) {
    return reinterpret_cast<const void*>(reinterpret_cast<uintptr_t>(p) + offset);
}
u32 release(void* p) {
    const u32 table = word(p);
    using Method = u32(__attribute__((stdcall))*)(void*);
    const auto call = reinterpret_cast<Method>(word(reinterpret_cast<const void*>(table + 8)));
    return call(p);
}
u32 addref(void* p) {
    const u32 table = word(p);
    using Method = u32(__attribute__((stdcall))*)(void*);
    const auto call = reinterpret_cast<Method>(word(reinterpret_cast<const void*>(table + 4)));
    return call(p);
}
bool equal_guid(const void* p, const u32* expected) {
    for (u32 i = 0; i < 4; ++i) {
        const u32 right = word(expected + i), actual = word(at(p, 4 * i));
        if (actual != right)
            return false;
    }
    return true;
}
} // namespace
// Original readonly words. These names identify exact byte spans, not guessed
// interface identities. The nine table entries are all original relocations.
extern "C" const uint32_t dat_006f73f8[4] = {0x00000000, 0x00000000, 0x000000c0, 0x46000000};
extern "C" const uint32_t dat_006effd4[4] = {0x6985f346, 0x43b32c3d, 0xaeda8bbe, 0x94d8038a};
extern "C" const OriginalCodeAddress_006df9f4 dat_006df9f4[9] = {
    reinterpret_cast<OriginalCodeAddress_006df9f4>(FUN_00602c08),
    reinterpret_cast<OriginalCodeAddress_006df9f4>(FUN_00620553),
    reinterpret_cast<OriginalCodeAddress_006df9f4>(FUN_00602c78),
    reinterpret_cast<OriginalCodeAddress_006df9f4>(FUN_006026eb),
    reinterpret_cast<OriginalCodeAddress_006df9f4>(FUN_00602715),
    reinterpret_cast<OriginalCodeAddress_006df9f4>(FUN_0060273d),
    reinterpret_cast<OriginalCodeAddress_006df9f4>(FUN_006029f3),
    reinterpret_cast<OriginalCodeAddress_006df9f4>(FUN_00602b70),
    reinterpret_cast<OriginalCodeAddress_006df9f4>(FUN_0063830d)};

extern "C" void* __attribute__((noinline, thiscall)) FUN_00602c51(void* self) {
    put(self, reinterpret_cast<uintptr_t>(dat_006df9f4));
    put(at(self, 4), 1);
    put(at(self, 8), 0);
    put(at(self, 0x20), 0);
    put(at(self, 0x24), 0);
    put(at(self, 0x28), 0);
    put(at(self, 0x2c), 0);
    put(at(self, 0x30), 0);
    put(at(self, 0x38), 0);
    return self;
}
extern "C" int32_t recovered_0060269a(void* self, u32* args) {
    const u32 device = word(args);
    if (!device)
        return static_cast<int32_t>(0x8876086c);
    if (word(at(self, 8)))
        return static_cast<int32_t>(0x80004005);
    put(at(self, 8), device);
    addref(reinterpret_cast<void*>(device));
    put(at(self, 0xc), word(args + 1));
    put(at(self, 0x10), word(args + 2));
    put(at(self, 0x14), word(args + 3));
    put(at(self, 0x18), word(args + 4));
    put(at(self, 0x1c), word(args + 5));
    return 0;
}
extern "C" __attribute__((naked, thiscall)) int32_t FUN_0060269a(void*, void*, u32, u32, u32, u32,
                                                                 u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_0060269a\n\taddl $8,%esp\n\tretl $24");
}
extern "C" uint32_t __attribute__((noinline, stdcall)) FUN_00602b70(void* self) {
    for (u32 offset = 0x20; offset <= 0x38; offset += 4) {
        if (offset == 0x34)
            continue;
        const u32 p = word(at(self, offset));
        if (p) {
            release(reinterpret_cast<void*>(p));
            put(at(self, offset), 0);
        }
    }
    return 0;
}
extern "C" uint32_t __attribute__((noinline, thiscall)) FUN_00602be4(void* self) {
    put(self, reinterpret_cast<uintptr_t>(dat_006df9f4));
    FUN_00602b70(self);
    const u32 p = word(at(self, 8));
    if (p) {
        const u32 result = release(reinterpret_cast<void*>(p));
        and_zero(at(self, 8));
        return result;
    }
    return 0;
}
extern "C" void* recovered_005e8bdf(void* self, const u32* args) {
    FUN_00602be4(self);
    if (byte(args) & 1)
        fun_005cc620(self);
    return self;
}
extern "C" __attribute__((naked, thiscall)) void* FUN_005e8bdf(void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005e8bdf\n\taddl $8,%esp\n\tretl $4");
}

extern "C" int32_t recovered_005e8d2b(u32* args) {
    if (!word(args))
        return static_cast<int32_t>(0x8876086c);
    const u32 output = word(args + 6);
    if (!output)
        return static_cast<int32_t>(0x8876086c);
    void* allocated = fun_005cc96d(0x54);
    void* self = allocated ? FUN_00602c51(allocated) : nullptr;
    if (!self)
        return static_cast<int32_t>(0x8007000e);
    const u32 b = word(args + 5), a = word(args + 4), format = word(args + 3),
              height = word(args + 2), width = word(args + 1), device = word(args);
    const int32_t result =
        FUN_0060269a(self, reinterpret_cast<void*>(device), width, height, format, a, b);
    if (result < 0) {
        FUN_005e8bdf(self, 1);
        return result;
    }
    put(reinterpret_cast<void*>(output), reinterpret_cast<uintptr_t>(self));
    return 0;
}
extern "C" __attribute__((naked, stdcall)) int32_t FUN_005e8d2b(void*, u32, u32, u32, u32, u32,
                                                                void**) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e8d2b\n\taddl $4,%esp\n\tretl $28");
}

extern "C" uint32_t __attribute__((noinline, stdcall)) FUN_00620553(void* self) {
    put(at(self, 4), word(at(self, 4)) + 1);
    return word(at(self, 4));
}
extern "C" uint32_t __attribute__((noinline, stdcall)) FUN_00602c78(void* self) {
    const u32 before = word(at(self, 4)), after = before - 1;
    put(at(self, 4), after);
    if (before == 1)
        FUN_005e8bdf(self, 1);
    return after;
}
extern "C" uint32_t __attribute__((noinline, stdcall)) FUN_0063830d(void*) {
    return 0;
}
extern "C" int32_t recovered_00602c08(u32* args) {
    void* output = reinterpret_cast<void*>(word(args + 2));
    and_zero(output);
    const void* first = reinterpret_cast<const void*>(word(args + 1));
    if (!equal_guid(first, dat_006f73f8)) {
        const void* second = reinterpret_cast<const void*>(word(args + 1));
        if (!equal_guid(second, dat_006effd4))
            return static_cast<int32_t>(0x80004002);
    }
    void* self = reinterpret_cast<void*>(word(args));
    put(output, reinterpret_cast<uintptr_t>(self));
    addref(self);
    return 0;
}
extern "C" __attribute__((naked, stdcall)) int32_t FUN_00602c08(void*, const void*, void**) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00602c08\n\taddl $4,%esp\n\tretl $12");
}
extern "C" int32_t recovered_006026eb(u32* args) {
    void* output = reinterpret_cast<void*>(word(args + 1));
    if (!output)
        return static_cast<int32_t>(0x8876086c);
    void* self = reinterpret_cast<void*>(word(args));
    put(output, word(at(self, 8)));
    const u32 device = word(at(self, 8));
    addref(reinterpret_cast<void*>(device));
    return 0;
}
extern "C" __attribute__((naked, stdcall)) int32_t FUN_006026eb(void*, void**) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_006026eb\n\taddl $4,%esp\n\tretl $8");
}
extern "C" int32_t recovered_00602715(u32* args) {
    void* output = reinterpret_cast<void*>(word(args + 1));
    if (!output)
        return static_cast<int32_t>(0x8876086c);
    const void* self = reinterpret_cast<void*>(word(args));
    for (u32 i = 0; i < 5; ++i)
        put(at(output, 4 * i), word(at(self, 0xc + 4 * i)));
    return 0;
}
extern "C" __attribute__((naked, stdcall)) int32_t FUN_00602715(void*, void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00602715\n\taddl $4,%esp\n\tretl $8");
}
