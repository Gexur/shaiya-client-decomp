#include "packet_byvalue.h"

namespace {
uint32_t word(const void* p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
} // namespace

// Original 0x00594c60..0x00594c9a; all28 by-value bytes are written.
extern "C" __attribute__((noinline)) uint32_t byvalue_00594c60(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 28);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t call_words[7] = {word(scratch + 0),  word(scratch + 4),  word(scratch + 8),
                                    word(scratch + 12), word(scratch + 16), word(scratch + 20),
                                    word(scratch + 24)};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl 24(%%eax)\n\tpushl 20(%%eax)\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl %%ecx,%%eax\n\tcall *0x40c(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00594c60(PacketReader*) {
    __asm__ volatile(
        "subl $28,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 40(%esp),%eax\n\tleal 8(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _byvalue_00594c60\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\taddl $28,%esp\n\tret");
}

// Original 0x00597830..0x0059786d; all120 by-value bytes are written.
extern "C" __attribute__((noinline)) uint32_t byvalue_00597830(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 120);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t call_words[30] = {
        word(scratch + 0),   word(scratch + 4),   word(scratch + 8),   word(scratch + 12),
        word(scratch + 16),  word(scratch + 20),  word(scratch + 24),  word(scratch + 28),
        word(scratch + 32),  word(scratch + 36),  word(scratch + 40),  word(scratch + 44),
        word(scratch + 48),  word(scratch + 52),  word(scratch + 56),  word(scratch + 60),
        word(scratch + 64),  word(scratch + 68),  word(scratch + 72),  word(scratch + 76),
        word(scratch + 80),  word(scratch + 84),  word(scratch + 88),  word(scratch + 92),
        word(scratch + 96),  word(scratch + 100), word(scratch + 104), word(scratch + 108),
        word(scratch + 112), word(scratch + 116)};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl 116(%%eax)\n\tpushl 112(%%eax)\n\tpushl 108(%%eax)\n\tpushl 104(%%eax)\n\tpushl 100(%%eax)\n\tpushl 96(%%eax)\n\tpushl 92(%%eax)\n\tpushl 88(%%eax)\n\tpushl 84(%%eax)\n\tpushl 80(%%eax)\n\tpushl 76(%%eax)\n\tpushl 72(%%eax)\n\tpushl 68(%%eax)\n\tpushl 64(%%eax)\n\tpushl 60(%%eax)\n\tpushl 56(%%eax)\n\tpushl 52(%%eax)\n\tpushl 48(%%eax)\n\tpushl 44(%%eax)\n\tpushl 40(%%eax)\n\tpushl 36(%%eax)\n\tpushl 32(%%eax)\n\tpushl 28(%%eax)\n\tpushl 24(%%eax)\n\tpushl 20(%%eax)\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl %%ecx,%%eax\n\tcall *0x5e0(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00597830(PacketReader*) {
    __asm__ volatile(
        "subl $120,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 132(%esp),%eax\n\tleal 8(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _byvalue_00597830\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\taddl $120,%esp\n\tret");
}
