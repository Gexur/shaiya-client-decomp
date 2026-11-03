#include "packet_conditional_bulk.h"

namespace {
uint32_t byte(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movzbl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
uint32_t word(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
void put(void* pointer, uint32_t value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(pointer), "r"(value) : "memory");
}
} // namespace

// Complete original591af0..591b47. No payload bytes are initialized by the
// consumer. Zero count skips both the bulk read and virtual call. Its MOV AL
// preserves the upper24 bits of the first reader's physical EAX result.
extern "C" __attribute__((noinline)) void
prepare_conditional_00591af0(PacketReader* reader, uint8_t* frame, uint32_t* state) {
    const uint32_t first_result = read_packet_bytes_with_diagnostic(reader, frame, 1);
    const uint32_t count = byte(frame);
    if (count == 0) {
        put(state + 2, first_result & 0xffffff00u);
        put(state + 3, 0);
        return;
    }
    read_packet_bytes_with_diagnostic(reader, frame + 4, count * 3);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    put(state, reinterpret_cast<uint32_t>(receiver));
    put(state + 1, table);
    put(state + 3, 1);
}

extern "C" __attribute__((naked)) void fun_00591af0(PacketReader*) {
    // Frame E-772 and original callbackSP E-788. All preparation completes
    // before a virtual callback can use the temporary helper stack.
    __asm__ volatile("subl $772,%esp\n\tpushl %esi\n\tmovl 780(%esp),%esi\n\t"
                     "subl $16,%esp\n\tmovl %esp,%eax\n\tleal 20(%esp),%edx\n\t"
                     "pushl %eax\n\tpushl %edx\n\tpushl %esi\n\t"
                     "call _prepare_conditional_00591af0\n\taddl $12,%esp\n\t"
                     "cmpl $0,12(%esp)\n\tje 1f\n\t"
                     "movl (%esp),%ecx\n\tmovl 4(%esp),%eax\n\taddl $16,%esp\n\t"
                     "leal 8(%esp),%edx\n\tpushl %edx\n\tmovl 8(%esp),%edx\n\t"
                     "pushl %edx\n\tcall *0x1f8(%eax)\n\tjmp 2f\n\t"
                     "1: movl 8(%esp),%eax\n\taddl $16,%esp\n\t"
                     "2: popl %esi\n\taddl $772,%esp\n\tret");
}
