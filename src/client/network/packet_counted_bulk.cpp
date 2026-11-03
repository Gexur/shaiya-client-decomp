#include "packet_counted_bulk.h"

// Original EAX/ESP allocation and page-touch ABI, implemented in stack_probe.cpp.
extern "C" void fun_005cd2a0();

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
void put(void* pointer, uint32_t value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(pointer), "r"(value) : "memory");
}
template <uint32_t RecordBytes>
void prepare(PacketReader* reader, uint8_t* frame, uint32_t* state) {
    read_packet_bytes_with_diagnostic(reader, frame, 1);
    const uint32_t requested = byte(frame) * RecordBytes;
    read_packet_bytes_with_diagnostic(reader, frame + 4, requested);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    put(state, reinterpret_cast<uint32_t>(receiver));
    put(state + 1, table);
}
} // namespace

// The one-byte count read preserves its three inherited upper bytes. The
// low byte controls the bulk request; the later virtual call receives all
// four bytes. The original has no overflow check for either private payload.
extern "C" __attribute__((noinline)) void
prepare_counted_00596e20(PacketReader* reader, uint8_t* frame, uint32_t* state) {
    prepare<76>(reader, frame, state);
}
extern "C" __attribute__((noinline)) void
prepare_counted_00597720(PacketReader* reader, uint8_t* frame, uint32_t* state) {
    prepare<120>(reader, frame, state);
}

extern "C" __attribute__((naked)) void fun_00596e20(PacketReader*) {
    // Original frame E-4868, callback SP E-4884. Preparation completes
    // before the virtual call; the callback may use the dead helper stack.
    __asm__ volatile("movl $4868,%eax\n\tcall _fun_005cd2a0\n\tpushl %esi\n\t"
                     "movl 4876(%esp),%esi\n\tsubl $12,%esp\n\t"
                     "movl %esp,%eax\n\tleal 16(%esp),%edx\n\t"
                     "pushl %eax\n\tpushl %edx\n\tpushl %esi\n\t"
                     "call _prepare_counted_00596e20\n\taddl $12,%esp\n\t"
                     "movl (%esp),%ecx\n\tmovl 4(%esp),%eax\n\taddl $12,%esp\n\t"
                     "leal 8(%esp),%edx\n\tpushl %edx\n\tmovl 8(%esp),%edx\n\t"
                     "pushl %edx\n\tcall *0x58c(%eax)\n\t"
                     "popl %esi\n\taddl $4868,%esp\n\tret");
}
extern "C" __attribute__((naked)) void fun_00597720(PacketReader*) {
    // Original frame E-4804, callback SP E-4820.
    __asm__ volatile("movl $4804,%eax\n\tcall _fun_005cd2a0\n\tpushl %esi\n\t"
                     "movl 4812(%esp),%esi\n\tsubl $12,%esp\n\t"
                     "movl %esp,%eax\n\tleal 16(%esp),%edx\n\t"
                     "pushl %eax\n\tpushl %edx\n\tpushl %esi\n\t"
                     "call _prepare_counted_00597720\n\taddl $12,%esp\n\t"
                     "movl (%esp),%ecx\n\tmovl 4(%esp),%eax\n\taddl $12,%esp\n\t"
                     "leal 8(%esp),%edx\n\tpushl %edx\n\tmovl 8(%esp),%edx\n\t"
                     "pushl %edx\n\tcall *0x5d4(%eax)\n\t"
                     "popl %esi\n\taddl $4804,%esp\n\tret");
}
