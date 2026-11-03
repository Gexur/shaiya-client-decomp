#include "graphics/surface/surface_format_configure.h"
#include "core/untouched_lifetime.h"
#include "runtime/allocations.h"
namespace {
using u32 = uint32_t;
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
u32 invoke_constructor(u32 code, u32 self, u32 incoming_eax) {
    // The original helper forwards residual EAX into its opaque zero-stack-word
    // constructor call. No incompatible C++ function-pointer type is invented.
    __asm__ volatile("calll *%2"
                     : "+a"(incoming_eax), "+c"(self)
                     : "r"(code)
                     : "edx", "memory", "cc");
    return incoming_eax;
}
} // namespace
// Complete405c90..405cc0. The original DEC/sign test admits count80000000,
// while0 and80000001..ffffffff skip. No conventional signed-count rewrite.
extern "C" uint32_t recovered_00405c90(u32* args) {
    const u32 count = word(args + 2);
    u32 result = count - 1;
    if (!(result & 0x80000000)) {
        const u32 constructor = word(args + 3), stride = word(args + 1);
        u32 object = word(args), remaining = result + 1;
        do {
            result = invoke_constructor(constructor, object, result);
            object += stride;
            --remaining;
        } while (remaining);
    }
    return result;
}
extern "C" __attribute__((naked, stdcall)) uint32_t FUN_00405c90(void*, uint32_t, uint32_t,
                                                                 uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00405c90\n\taddl $4,%esp\n\tretl $16");
}
// Complete5f2032..5f20b5. Only observed offsets are accessed, no full class
// or allocation bounds are invented. Actual CRT new and constructor execute.
extern "C" int32_t recovered_005f2032(u32* args, u32 self) {
    const u32 other = word(args), other_type = word(ptr(other + 8)), own_type = word(ptr(self + 8));
    if (own_type != other_type && own_type != 4)
        put(ptr(self + 0x54), other_type);
    if (word(ptr(self + 0x54)) || word(ptr(self + 0x10))) {
        const u32 count = word(ptr(self + 0x68));
        void* allocated = fun_005cc96d(count << 4);
        if (allocated)
            FUN_00405c90(allocated, 16, count, reinterpret_cast<uintptr_t>(&FUN_004441b0));
        put(ptr(self + 0x58), reinterpret_cast<uintptr_t>(allocated));
        if (!allocated)
            return static_cast<int32_t>(0x8007000e);
        const u32 own_flag = word(ptr(self + 0x10)), fresh_other = word(args);
        if (own_flag && word(ptr(fresh_other + 0x10))) {
            put(ptr(fresh_other + 0x14), 1);
            put(ptr(self + 0x14), 1);
        }
    }
    return 0;
}
extern "C" __attribute__((naked, thiscall)) int32_t FUN_005f2032(void*, void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %ecx\n\tpushl %eax\n\tcalll _recovered_005f2032\n\taddl $8,%esp\n\tretl $4");
}
