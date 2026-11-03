#include "graphics/surface/surface_block_premultiplied.h"
#include "graphics/surface/surface_block_decode.h"
#include "graphics/surface/surface_block_codec_helpers.h"
namespace {
uint32_t word(uint32_t pointer) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
void registers(uint32_t* state, uint32_t ecx, uint32_t edx) {
    state[0] = ecx;
    state[1] = edx;
}
uint32_t finish(uint32_t arguments, uint32_t* state) {
    uint32_t receiver = word(arguments), result, edx;
    __asm__ volatile("calll _FUN_0064f6c2"
                     : "=a"(result), "+c"(receiver), "=d"(edx)
                     :
                     : "memory", "cc", "st", "st(1)");
    registers(state, receiver, edx);
    return static_cast<int32_t>(result) < 0 ? result : 0;
}
} // namespace
// Complete original0065149f..006514c5. Both initial arguments are freshly
// pushed, second before first. The receiver is loaded again after decoding.
extern "C" uint32_t recovered_0065149f(uint32_t arguments, uint32_t* state) {
    const uint32_t input = word(arguments + 4);
    const uint32_t output = word(arguments);
    uint32_t result, ecx, edx;
    __asm__ volatile("pushl %4\n\tpushl %3\n\tcalll _FUN_00650bb5@8"
                     : "=a"(result), "=c"(ecx), "=d"(edx)
                     : "r"(output), "r"(input)
                     : "memory", "cc", "st", "st(1)", "st(2)");
    registers(state, ecx, edx);
    if (static_cast<int32_t>(result) < 0)
        return result;
    return finish(arguments, state);
}
// Complete original006514c5..006514eb. The distinct compressed alpha decoder
// precedes the same genuine sixteen-record unpremultiplication body.
extern "C" uint32_t recovered_006514c5(uint32_t arguments, uint32_t* state) {
    const uint32_t input = word(arguments + 4);
    const uint32_t output = word(arguments);
    uint32_t result, ecx, edx;
    __asm__ volatile("pushl %4\n\tpushl %3\n\tcalll _FUN_00650c3a@8"
                     : "=a"(result), "=c"(ecx), "=d"(edx)
                     : "r"(output), "r"(input)
                     : "memory", "cc", "st", "st(1)", "st(2)");
    registers(state, ecx, edx);
    if (static_cast<int32_t>(result) < 0)
        return result;
    return finish(arguments, state);
}
// Explicit argument-address bridges retain the original caller storage and
// RET8; they do not give decoder children aliases to the parent's two words.
extern "C" __attribute__((naked)) uint32_t FUN_0065149f() {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $8,%esp\n\tleal -8(%ebp),%edx\n\tpushl %edx\n\tleal 8(%ebp),%eax\n\tpushl %eax\n\tcalll _recovered_0065149f\n\taddl $8,%esp\n\tmovl -8(%ebp),%ecx\n\tmovl -4(%ebp),%edx\n\tleave\n\tretl $8");
}
extern "C" __attribute__((naked)) uint32_t FUN_006514c5() {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $8,%esp\n\tleal -8(%ebp),%edx\n\tpushl %edx\n\tleal 8(%ebp),%eax\n\tpushl %eax\n\tcalll _recovered_006514c5\n\taddl $8,%esp\n\tmovl -8(%ebp),%ecx\n\tmovl -4(%ebp),%edx\n\tleave\n\tretl $8");
}
