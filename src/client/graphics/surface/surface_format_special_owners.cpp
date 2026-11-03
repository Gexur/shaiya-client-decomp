#include "graphics/surface/surface_format_special_owners.h"
#include "graphics/surface/surface_format_owner.h"
#include "graphics/surface/surface_format_tables.h"
#include "runtime/allocations.h"
#include "graphics/surface/surface_format_configure.h"
#include "core/untouched_lifetime.h"
extern "C" {
extern const unsigned char code_00650a73[] __asm__("_FUN_00650a73@8");
extern const unsigned char code_00650d78[] __asm__("_FUN_00650d78");
extern const unsigned char code_0065149f[] __asm__("_FUN_0065149f");
extern const unsigned char code_006514eb[] __asm__("_FUN_006514eb");
extern const unsigned char code_00650bb5[] __asm__("_FUN_00650bb5@8");
extern const unsigned char code_00650e9c[] __asm__("_FUN_00650e9c");
extern const unsigned char code_006514c5[] __asm__("_FUN_006514c5");
extern const unsigned char code_00651524[] __asm__("_FUN_00651524");
extern const unsigned char code_00650c3a[] __asm__("_FUN_00650c3a@8");
extern const unsigned char code_00650fcb[] __asm__("_FUN_00650fcb");
}
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
void ones(u32 p) {
    __asm__ volatile("orl $-1,(%0)" ::"r"(p) : "memory", "cc");
}
void copy6(u32 output, u32 input) {
    u32 count = 6;
    __asm__ volatile("rep movsl" : "+D"(output), "+S"(input), "+c"(count)::"memory");
}
} // namespace
// Complete5fa87f..5fa96d. Original argument1 is reloaded only after actual new.
extern "C" u32 recovered_005fa87f(u32 self, u32 arguments) {
    FUN_005f1e45(reinterpret_cast<void*>(self), reinterpret_cast<void*>(word(arguments)), 0, 1);
    const u32 left = word(self + 0x3c) & 0xfffffffeu;
    const u32 right = (word(self + 0x44) + 1) & 0xfffffffeu, count = right - left;
    put(self + 0x8c, right);
    put(self, reinterpret_cast<uintptr_t>(dat_006df6d4));
    put(self + 0x84, left);
    put(self + 0x88, 0);
    put(self + 0x94, 0);
    put(self + 0x90, 0);
    put(self + 0x98, 0);
    put(self + 0x9c, count);
    put(self + 0xa0, 0);
    put(self + 0xa4, 1);
    void* const allocation = fun_005cc96d(count << 4);
    if (allocation)
        FUN_00405c90(allocation, 16, count, reinterpret_cast<uintptr_t>(&FUN_004441b0));
    put(self + 0x80, reinterpret_cast<uintptr_t>(allocation));
    if (!allocation)
        put(self + 0xa4, 0);
    const u32 descriptor = word(arguments), format = word(descriptor + 4);
    if (format == 0x32595559u || format == 0x47424752u) {
        put(self + 0xa8, 0);
        put(self + 0xac, 8);
    } else if (format == 0x42475247u || format == 0x59565955u) {
        put(self + 0xa8, 8);
        put(self + 0xac, 0);
    }
    return self;
}
// Complete5faa99..5fac81, retaining both cached and late descriptor reads.
extern "C" u32 recovered_005faa99(u32 self, u32 arguments) {
    const u32 descriptor = word(arguments);
    FUN_005f1e45(reinterpret_cast<void*>(self), reinterpret_cast<void*>(descriptor), 0, 1);
    const u32 format = word(self + 4);
    put(self, reinterpret_cast<uintptr_t>(dat_006df3f4));
    switch (format) {
    case 0x31545844u:
        put(self + 0x88, 8);
        put(self + 0x90, reinterpret_cast<uintptr_t>(code_00650d78));
        put(self + 0x8c, reinterpret_cast<uintptr_t>(code_00650a73));
        break;
    case 0x32545844u:
        put(self + 0x88, 16);
        put(self + 0x90, reinterpret_cast<uintptr_t>(code_006514eb));
        put(self + 0x8c, reinterpret_cast<uintptr_t>(code_0065149f));
        break;
    case 0x33545844u:
        put(self + 0x88, 16);
        put(self + 0x90, reinterpret_cast<uintptr_t>(code_00650e9c));
        put(self + 0x8c, reinterpret_cast<uintptr_t>(code_00650bb5));
        break;
    case 0x34545844u:
        put(self + 0x88, 16);
        put(self + 0x90, reinterpret_cast<uintptr_t>(code_00651524));
        put(self + 0x8c, reinterpret_cast<uintptr_t>(code_006514c5));
        break;
    case 0x35545844u:
        put(self + 0x88, 16);
        put(self + 0x90, reinterpret_cast<uintptr_t>(code_00650fcb));
        put(self + 0x8c, reinterpret_cast<uintptr_t>(code_00650c3a));
        break;
    }
    copy6(self + 0x94, descriptor + 0x10);
    put(self + 0xac, word(self + 0x94) & 0xfffffffcu);
    put(self + 0xb0, word(self + 0x98) & 0xfffffffcu);
    put(self + 0xbc, word(self + 0xa4));
    const u32 record_right = (word(self + 0x9c) + 3) & 0xfffffffcu;
    u32 bottom = word(self + 0x48), left = word(self + 0x3c);
    put(self + 0xb4, record_right);
    u32 record_bottom = word(self + 0xa0);
    u32 top = word(self + 0x40);
    ones(self + 0xe8);
    ones(self + 0xec);
    record_bottom = (record_bottom + 3) & 0xfffffffcu;
    put(self + 0xb8, record_bottom);
    put(self + 0xc0, word(self + 0xa8));
    put(self + 0xd4, word(self + 0x4c));
    const u32 right = (word(self + 0x44) + 3) & 0xfffffffcu;
    left &= 0xfffffffcu;
    put(self + 0xcc, right);
    bottom = (bottom + 3) & 0xfffffffcu;
    top &= 0xfffffffcu;
    u32 back = word(self + 0x50);
    const u32 width = (right - left) >> 2;
    put(self + 0xd0, bottom);
    put(self + 0xdc, width);
    bottom -= top;
    put(self + 0xd8, back);
    back -= word(self + 0x4c);
    bottom >>= 2;
    put(self + 0xf0, 0);
    put(self + 0xf4, 0);
    put(self + 0xf8, 0);
    const u32 final_descriptor = word(arguments);
    put(self + 0xc4, left);
    put(self + 0xc8, top);
    put(self + 0xe0, bottom);
    put(self + 0xe4, back);
    put(self + 0xfc, word(final_descriptor + 0x40));
    return self;
}
#define OWNER_ENTRY(name)                                                                          \
    extern "C" __attribute__((naked, thiscall)) uint32_t FUN_##name(void*, void*) {                \
        __asm__ volatile(                                                                          \
            "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_" #name             \
            "\n\taddl $8,%esp\n\tretl $4");                                                        \
    }
OWNER_ENTRY(005fa87f)
OWNER_ENTRY(005faa99)
#undef OWNER_ENTRY
