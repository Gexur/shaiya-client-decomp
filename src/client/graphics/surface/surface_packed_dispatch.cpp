#include "graphics/surface/surface_packed_dispatch.h"
#include "graphics/surface/surface_packed_rows.h"
#include "graphics/surface/surface_packed_mmx.h"
#include "graphics/surface/surface_mmx_eligibility.h"
extern "C" {
OriginalPackedRowKernel volatile dat_0070fdf4 = &FUN_005ed171;
OriginalPackedRowKernel volatile dat_0070fdf8 = &FUN_005ed1ab;
}
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
u32 call_row(void* object, OriginalPackedRowKernel volatile& slot) {
    const u32 self = reinterpret_cast<uintptr_t>(object);
    u32 destination = word(self + 4), source = word(self), input = word(source + 0x20);
    const u32 output_stride = word(destination + 0x60), output = word(destination + 0x20),
              input_stride = word(source + 0x60), height = word(source + 0x6c),
              width = word(source + 0x68);
    const u32 words[6] = {output, input, width, height, input_stride, output_stride};
    __asm__ volatile(
        "pushl 20(%4)\n\tpushl 16(%4)\n\tpushl 12(%4)\n\tpushl 8(%4)\n\tpushl 4(%4)\n\tpushl (%4)\n\tcalll *(%3)"
        : "+a"(source), "+c"(input), "+d"(destination)
        : "r"(&slot), "r"(words)
        : "memory", "cc");
    return source;
}
} // namespace
extern "C" __attribute__((thiscall)) uint32_t FUN_005ecf49(void* object) {
    return call_row(object, dat_0070fdf4);
}
extern "C" __attribute__((thiscall)) uint32_t FUN_005ed1dc(void* object) {
    return call_row(object, dat_0070fdf8);
}
// Literal source mnemonics preserve original six-word tail ABI and the two
// distinct binding sequences. Only the actual eligibility routine chooses;
// no assumed CPU result or disabled MMX path is supplied here.
extern "C" __attribute__((naked, stdcall)) uint32_t FUN_005ed171(uint32_t, uint32_t, uint32_t,
                                                                 uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tcalll _FUN_005fd0a5\n\ttestl %eax,%eax\n\tje 1f\n\t"
        "movl $\"_FUN_005ed057@24\",%eax\n\tmovl %eax,_dat_0070fdf4\n\tmovl %eax,_dat_0070fdf8\n\tjmp 2f\n"
        "1: movl $\"_FUN_005ece1f@24\",_dat_0070fdf4\n\tmovl $\"_FUN_005ecf6b@24\",_dat_0070fdf8\n"
        "2: popl %ebp\n\tjmpl *_dat_0070fdf4");
}
extern "C" __attribute__((naked, stdcall)) uint32_t FUN_005ed1ab(uint32_t, uint32_t, uint32_t,
                                                                 uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tcalll _FUN_005fd0a5\n\ttestl %eax,%eax\n\tje 1f\n\t"
        "movl $\"_FUN_005ed057@24\",%eax\n\tmovl %eax,_dat_0070fdf4\n\tjmp 2f\n"
        "1: movl $\"_FUN_005ece1f@24\",_dat_0070fdf4\n\tmovl $\"_FUN_005ecf6b@24\",%eax\n"
        "2: movl %eax,_dat_0070fdf8\n\tpopl %ebp\n\tjmpl *%eax");
}
