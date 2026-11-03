#include "graphics/surface/surface_float_writers.h"
#include "graphics/surface/surface_write_color.h"
#include "graphics/render_float16_dispatch.h"
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
void prepare(u32 self, u32 args) {
    if (word(self + 0x10))
        put(args + 8, FUN_005f22d6(reinterpret_cast<void*>(self),
                                   reinterpret_cast<const void*>(word(args + 8))));
}
u32 destination(u32 self, u32 args) {
    u32 p = word(self + 0x60) * word(args);
    const u32 slice = word(self + 0x64) * word(args + 4);
    p += slice;
    return p + word(self + 0x20);
}
u32 half_row(u32 self, u32 args, u32 components) {
    prepare(self, args);
    u32 output = word(self + 0x60) * word(args);
    u32 result = word(self + 0x64) * word(args + 4);
    output += result;
    output += word(self + 0x20);
    u32 index = 0;
    if (word(self + 0x68) != 0) {
        put(args + 8, word(args + 8));
        do {
            result = reinterpret_cast<u32>(
                FUN_005e3c30(reinterpret_cast<void*>(output),
                             reinterpret_cast<const void*>(word(args + 8)), components));
            put(args + 8, word(args + 8) + 16);
            output += components * 2;
            ++index;
        } while (index < word(self + 0x68));
    }
    return result;
}
} // namespace
// Complete original5f8751..5f879e: one raw float DWORD from each RGBA record.
extern "C" u32 recovered_005f8751(u32 self, u32 args) {
    prepare(self, args);
    u32 output = destination(self, args), index = 0;
    if (word(self + 0x68) != 0) {
        u32 input = word(args + 8);
        do {
            put(output, word(input));
            output += 4;
            ++index;
            input += 16;
        } while (index < word(self + 0x68));
    }
    return output;
}
// Complete original5f879e..5f87f6 and5f87f6..5f884f. The converter is the
// original already-selected fast entry, without an invented initialization.
extern "C" u32 recovered_005f879e(u32 self, u32 args) {
    return half_row(self, args, 1);
}
extern "C" u32 recovered_005f87f6(u32 self, u32 args) {
    return half_row(self, args, 2);
}
// Complete5f884f..5f8890: one converter call, including a zero-component row.
extern "C" u32 recovered_005f884f(u32 self, u32 args) {
    prepare(self, args);
    const u32 components = word(self + 0x68) << 2;
    const u32 slice = word(self + 0x64) * word(args + 4);
    u32 output = word(self + 0x60) * word(args);
    const u32 input = word(args + 8);
    output += slice;
    output += word(self + 0x20);
    return reinterpret_cast<u32>(FUN_005e3c30(reinterpret_cast<void*>(output),
                                              reinterpret_cast<const void*>(input), components));
}
// Complete5f8890..5f88e3: two ordered raw DWORD copies per RGBA record.
extern "C" u32 recovered_005f8890(u32 self, u32 args) {
    prepare(self, args);
    u32 output = destination(self, args), index = 0;
    if (word(self + 0x68) != 0) {
        u32 input = word(args + 8);
        do {
            put(output, word(input));
            put(output + 4, word(input + 4));
            output += 8;
            ++index;
            input += 16;
        } while (index < word(self + 0x68));
    }
    return output;
}
// Complete5f88e3..5f892f: actual forward REP copy and wrapped byte-count EAX.
extern "C" u32 recovered_005f88e3(u32 self, u32 args) {
    prepare(self, args);
    u32 output = word(self + 0x60) * word(args);
    const u32 slice = word(self + 0x64) * word(args + 4);
    const u32 bytes = word(self + 0x68) << 4;
    u32 input = word(args + 8);
    output += slice;
    output += word(self + 0x20);
    u32 count = bytes >> 2;
    __asm__ volatile("rep movsl" : "+S"(input), "+D"(output), "+c"(count)::"memory");
    count = bytes & 3u;
    __asm__ volatile("rep movsb" : "+S"(input), "+D"(output), "+c"(count)::"memory");
    return bytes;
}
// The actual three incoming words stay addressable; RET12 consumes them.
#define ROW(n)                                                                                     \
    extern "C" __attribute__((naked, thiscall)) u32 FUN_##n(void*, u32, u32, const void*) {        \
        __asm__ volatile("leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_" #n   \
                         "\n\taddl $8,%esp\n\tretl $12");                                          \
    }
ROW(005f8751)
ROW(005f879e)
ROW(005f87f6)
ROW(005f884f)
ROW(005f8890)
ROW(005f88e3)
#undef ROW
