#include "graphics/render_matrix_broadcast_sse.h"
namespace {
using V = float __attribute__((vector_size(16)));
struct B16 {
    unsigned char bytes[16];
};
uint32_t word(const uint32_t* p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
__attribute__((target("sse"), always_inline)) inline void replicate(uint32_t output,
                                                                    uint32_t value) {
    V v;
    __asm__ volatile("movss %1,%0\n\tshufps $0,%0,%0" : "=x"(v) : "m"(value) : "memory");
    __asm__ volatile("movaps %1,%0" : "=m"(*reinterpret_cast<B16*>(output)) : "x"(v) : "memory");
}
} // namespace
extern "C" __attribute__((target("sse"))) uint64_t
recovered_sse_matrix_broadcast(uint32_t output, const uint32_t* arguments, uint32_t* last) {
    const uint32_t input = word(arguments);
    const uint32_t item_00 = word(reinterpret_cast<const uint32_t*>(input + 0));
    replicate(output + 0, item_00); // original00681a80..00681a8e
    const uint32_t item_01 = word(reinterpret_cast<const uint32_t*>(input + 16));
    replicate(output + 64, item_01); // original00681a91..00681aa0
    const uint32_t item_02 = word(reinterpret_cast<const uint32_t*>(input + 32));
    replicate(output + 128, item_02); // original00681aa4..00681ab3
    const uint32_t item_03 = word(reinterpret_cast<const uint32_t*>(input + 48));
    replicate(output + 192, item_03); // original00681aba..00681ac9
    const uint32_t item_04 = word(reinterpret_cast<const uint32_t*>(input + 4));
    replicate(output + 16, item_04); // original00681ad0..00681adf
    const uint32_t item_05 = word(reinterpret_cast<const uint32_t*>(input + 20));
    replicate(output + 80, item_05); // original00681ae3..00681af2
    const uint32_t item_06 = word(reinterpret_cast<const uint32_t*>(input + 36));
    replicate(output + 144, item_06); // original00681af6..00681b05
    const uint32_t item_07 = word(reinterpret_cast<const uint32_t*>(input + 52));
    replicate(output + 208, item_07); // original00681b0c..00681b1b
    const uint32_t item_08 = word(reinterpret_cast<const uint32_t*>(input + 8));
    replicate(output + 32, item_08); // original00681b22..00681b31
    const uint32_t item_09 = word(reinterpret_cast<const uint32_t*>(input + 24));
    replicate(output + 96, item_09); // original00681b35..00681b44
    const uint32_t item_10 = word(reinterpret_cast<const uint32_t*>(input + 40));
    replicate(output + 160, item_10); // original00681b48..00681b57
    const uint32_t item_11 = word(reinterpret_cast<const uint32_t*>(input + 56));
    replicate(output + 224, item_11); // original00681b5e..00681b6d
    const uint32_t item_12 = word(reinterpret_cast<const uint32_t*>(input + 12));
    replicate(output + 48, item_12); // original00681b74..00681b83
    const uint32_t item_13 = word(reinterpret_cast<const uint32_t*>(input + 28));
    replicate(output + 112, item_13); // original00681b87..00681b96
    const uint32_t item_14 = word(reinterpret_cast<const uint32_t*>(input + 44));
    replicate(output + 176, item_14); // original00681b9a..00681ba9
    const uint32_t item_15 = word(reinterpret_cast<const uint32_t*>(input + 60));
    replicate(output + 240, item_15); // original00681bb0..00681bbf
    *last = item_15;
    return uint64_t(output) | (uint64_t(item_14) << 32);
}
extern "C" __attribute__((naked, thiscall)) void* FUN_00681a69(void*, const void*) {
    __asm__ volatile(
        "subl $4,%esp\n\tmovl %esp,%eax\n\tleal 8(%esp),%edx\n\tpushl %eax\n\tpushl %edx\n\tpushl %ecx\n\tcalll _recovered_sse_matrix_broadcast\n\taddl $12,%esp\n\tmovl (%esp),%ecx\n\taddl $4,%esp\n\tretl $4");
}
