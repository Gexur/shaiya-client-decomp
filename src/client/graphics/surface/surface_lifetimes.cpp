#include "graphics/surface/surface_lifetimes.h"
#include "runtime/allocations.h"
#include "graphics/surface/surface_format_tables.h"
#include "graphics/surface/surface_format_owner.h"
#include "graphics/surface/surface_write_transform.h"
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
void clear(u32 p) {
    __asm__ volatile("andl $0,(%0)" ::"r"(p) : "memory", "cc");
}
using PixelMethod = u32 __attribute__((thiscall)) (*)(void*, u32, u32, void*);
} // namespace
// Complete005f0d79..005f0da1. Destruction installs the base vtable before
// executing the three actual CRT frees; later pointers remain late reads.
extern "C" __attribute__((noinline)) void __attribute__((thiscall)) FUN_005f0d79(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object), first = word(self + 0x38);
    put(self, reinterpret_cast<uintptr_t>(dat_006df3b0));
    fun_005cc620(reinterpret_cast<void*>(first));
    fun_005cc620(reinterpret_cast<void*>(word(self + 0x58)));
    fun_005cc620(reinterpret_cast<void*>(word(self + 0x5c)));
}
extern "C" uint32_t __attribute__((thiscall)) FUN_005f2011(void* object, uint32_t flags) {
    FUN_005f0d79(object);
    if (flags & 1)
        fun_005cc620(object);
    return reinterpret_cast<uintptr_t>(object);
}
// Complete005f21aa..005f225c. The wrapper reserves the original36B private
// region. Both real virtual methods receive the same color and temporary
// pixel addresses as the original, including when the first changes vtable.
extern "C" u32 recovered_005f21aa(u32 self, u32 frame) {
    const u32 pixels = word(self + 0x20), bytes = word(self + 0x78), stride = word(self + 0x74);
    put(frame + 24, pixels);
    put(frame + 20, word(self + 0x34));
    const u32 color = word(self + 0x18);
    clear(self + 0x18);
    put(self + 0x74, bytes);
    put(frame + 16, color);
    put(self + 0x20, frame);
    const u32 kind = word(self + 8), width = word(self + 0x68);
    put(self + 0x68, 1);
    put(self + 0x34, reinterpret_cast<uintptr_t>(dat_0070fe00));
    if (kind != 1 && kind != 4) {
        put(frame + 32, word(self + 0x54));
        const u32 output = word(self + 0x58);
        put(self + 0x54, 1);
        put(frame + 28, output);
        put(self + 0x58, self + 0x24);
        FUN_005f0da1(reinterpret_cast<void*>(self), reinterpret_cast<void*>(self + 0x24));
        put(self + 0x54, word(frame + 32));
        put(self + 0x58, word(frame + 28));
    }
    reinterpret_cast<PixelMethod>(word(word(self) + 8))(reinterpret_cast<void*>(self), 0, 0,
                                                        reinterpret_cast<void*>(self + 0x24));
    reinterpret_cast<PixelMethod>(word(word(self) + 4))(reinterpret_cast<void*>(self), 0, 0,
                                                        reinterpret_cast<void*>(self + 0x24));
    put(self + 0x20, word(frame + 24));
    put(self + 0x34, word(frame + 20));
    const u32 restored_color = word(frame + 16);
    put(self + 0x68, width);
    put(self + 0x74, stride);
    put(self + 0x18, restored_color);
    return restored_color;
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f21aa(void*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $36,%esp\n\tleal -36(%ebp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f21aa\n\taddl $8,%esp\n\tleave\n\tretl");
}
// Original00638315..00638318 consists of RET12. Base surface vtables use
// this shared empty method; registers, flags and x87 state are untouched.
extern "C" __attribute__((naked)) void FUN_00638315() {
    __asm__ volatile("retl $12");
}
