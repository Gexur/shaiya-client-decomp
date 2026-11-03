#include "graphics/render_scale_dispatch.h"
#include "startup/math_dispatch_state.h"
namespace {
uint32_t round_slot(const void* input) {
    uint32_t output;
    __asm__ volatile("flds %1\n\tfstps %0"
                     : "=m"(output)
                     : "m"(*static_cast<const unsigned char (*)[4]>(input))
                     : "st", "memory");
    return output;
}
void* call_scale(void* output, uint32_t x, uint32_t y, uint32_t z) {
    uint32_t words[4] = {reinterpret_cast<uint32_t>(output), x, y, z};
    void* result;
    __asm__ volatile("pushl 12(%2)\n\tpushl 8(%2)\n\tpushl 4(%2)\n\tpushl (%2)\n\tcalll *%1"
                     : "=a"(result)
                     : "m"(dat_0070f370.entries[34]), "r"(words)
                     : "ecx", "edx", "cc", "memory");
    return result;
}
} // namespace
extern "C" void* recovered_005e568b(const uint32_t* words) {
    FUN_005fd1f8(1);
    const uint32_t z = round_slot(words + 3), y = round_slot(words + 2), x = round_slot(words + 1);
    uint32_t output;
    __asm__ volatile("movl (%1),%0" : "=r"(output) : "r"(words) : "memory");
    return call_scale(reinterpret_cast<void*>(output), x, y, z);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e568b(void*, uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e568b\n\taddl $4,%esp\n\tretl $16");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e56bb(void*, uint32_t, uint32_t, uint32_t) {
    __asm__ volatile("jmpl *_dat_0070f370+136");
}
