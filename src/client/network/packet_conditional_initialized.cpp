#include "packet_conditional_initialized.h"

namespace {
uint32_t word(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
uint32_t byte(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movzbl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
void zero_word(void* pointer) {
    __asm__ volatile("movl $0,(%0)" ::"r"(pointer) : "memory");
}
void zero_byte(void* pointer) {
    __asm__ volatile("movb $0,(%0)" ::"r"(pointer) : "memory");
}
void put(void* pointer, uint32_t value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(pointer), "r"(value) : "memory");
}
} // namespace

extern "C" __attribute__((noinline)) void initialize_prefix_005915f0(uint8_t* frame) {
    // Original5915f5/5915f9 precede its actual reader-argument load.
    zero_word(frame + 12);
    zero_word(frame + 16);
}
extern "C" __attribute__((noinline)) void
prepare_initialized_005915f0(PacketReader* reader, uint8_t* frame, uint32_t* state) {
    zero_word(frame + 20);
    zero_word(frame + 24);
    zero_word(frame + 28);
    zero_byte(frame + 4);
    zero_byte(frame);
    zero_byte(frame + 32);
    read_packet_bytes_with_diagnostic(reader, frame + 8, 1);
    if (byte(frame + 8) == 0) {
        read_packet_bytes_with_diagnostic(reader, frame + 4, 1);
        read_packet_bytes_with_diagnostic(reader, frame, 1);
        read_available_packet_bytes(reader, frame + 12, 21);
    }
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    put(state, reinterpret_cast<uint32_t>(receiver));
    put(state + 1, table);
}

// Complete5915f0..591683. The two scalar defaults clear BYTEs only, retaining
// the upper24 bits later passed as full DWORDs. Text clears cover exactly21B.
extern "C" __attribute__((naked)) void fun_005915f0(PacketReader*) {
    __asm__ volatile("subl $36,%esp\n\tmovl %esp,%eax\n\tpushl %eax\n\t"
                     "call _initialize_prefix_005915f0\n\taddl $4,%esp\n\t"
                     "pushl %esi\n\tmovl 44(%esp),%esi\n\tsubl $8,%esp\n\t"
                     "movl %esp,%eax\n\tleal 12(%esp),%edx\n\t"
                     "pushl %eax\n\tpushl %edx\n\tpushl %esi\n\t"
                     "call _prepare_initialized_005915f0\n\taddl $12,%esp\n\t"
                     "movl (%esp),%ecx\n\tmovl 4(%esp),%edx\n\taddl $8,%esp\n\t"
                     "leal 16(%esp),%eax\n\tpushl %eax\n\tmovl 8(%esp),%eax\n\t"
                     "pushl %eax\n\tmovl 16(%esp),%eax\n\tpushl %eax\n\t"
                     "movl 24(%esp),%eax\n\tpushl %eax\n\tcall *0x1dc(%edx)\n\t"
                     "popl %esi\n\taddl $36,%esp\n\tret");
}
