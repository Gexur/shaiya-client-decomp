#include "packet_word_array.h"
namespace {
uint32_t word(const void* p) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(p) : "memory");
    return value;
}
} // namespace
// Complete original58e240..58e27a. Literal21 iterations, each calling the
// original two-byte reader into the next two bytes. The final two bytes of
// the original44-byte frame are untouched, not inferred array terminators.
extern "C" __attribute__((noinline)) uint32_t word_array_0058e240(const void* arguments,
                                                                  uint8_t* frame) {
    auto* reader = reinterpret_cast<PacketReader*>(word(arguments));
    for (uint32_t index = 0; index != 21; ++index)
        read_packet_bytes_with_diagnostic(reader, frame + index * 2, 2);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl %%edx\n\tcall *0x5c(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(frame)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058e240(PacketReader*) {
    __asm__ volatile(
        "subl $44,%esp\n\tpushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tleal 12(%esp),%edx\n\tleal 60(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _word_array_0058e240\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\taddl $44,%esp\n\tret");
}
