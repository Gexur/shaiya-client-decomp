#include "graphics/surface/surface_filter_storage.h"
#include "runtime/allocations.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
unsigned char byte(u32 p) {
    unsigned char v;
    __asm__ volatile("movb (%1),%0" : "=q"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void release(u32 pointer) {
    fun_005cc620(reinterpret_cast<void*>(pointer));
}
u32 invoke(u32 target, u32 object, u32 eax) {
    __asm__ volatile("calll *%2" : "+a"(eax), "+c"(object) : "r"(target) : "edx", "memory", "cc");
    return eax;
}
} // namespace
// Original5e232f..5e235b. Raw slots preserve the per-iteration size/callback
// reloads, unlike an assumed fixed typed destructor-loop interface.
extern "C" uint32_t recovered_005e232f(const uint32_t* arguments) {
    const u32 slots = reinterpret_cast<uintptr_t>(arguments), count = word(slots + 8),
              size = word(slots + 4), first = word(slots);
    u32 cursor = first + count * size, result = count - 1;
    if (!(result & 0x80000000u)) {
        u32 remaining = result + 1;
        do {
            cursor -= word(slots + 4);
            const u32 target = word(slots + 12);
            result = invoke(target, cursor, result);
        } while (--remaining);
    }
    return result;
}
extern "C" __attribute__((naked, stdcall)) uint32_t FUN_005e232f(void*, uint32_t, uint32_t,
                                                                 uintptr_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e232f\n\taddl $4,%esp\n\tretl $16");
}
// Original5eca00..5eca09. The destructor's volatile EAX after the real void
// free boundary is explicitly outside this source's established contract.
extern "C" void __attribute__((thiscall)) FUN_005eca00(void* object) {
    release(word(reinterpret_cast<uintptr_t>(object)));
}
// Original5ef56a..5ef5b9. The second BYTE flag test is deliberately deferred
// until after the destructor iterator or pointed-to-buffer release returns.
extern "C" void* recovered_005ef56a(void* object, const uint32_t* arguments) {
    const u32 self = reinterpret_cast<uintptr_t>(object),
              slots = reinterpret_cast<uintptr_t>(arguments);
    if (byte(slots) & 2) {
        const u32 header = self - 4, count = word(header);
        FUN_005e232f(object, 12, count, reinterpret_cast<uintptr_t>(&FUN_005eca00));
        if (byte(slots) & 1)
            release(header);
        return reinterpret_cast<void*>(header);
    }
    release(word(self));
    if (byte(slots) & 1)
        release(self);
    return object;
}
extern "C" __attribute__((naked, thiscall)) void* FUN_005ef56a(void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005ef56a\n\taddl $8,%esp\n\tretl $4");
}
// Original5fc891..5fc89e: three ordered zero DWORD stores and EAX=this.
extern "C" void* __attribute__((thiscall)) FUN_005fc891(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object);
    put(self, 0);
    put(self + 4, 0);
    put(self + 8, 0);
    return object;
}
