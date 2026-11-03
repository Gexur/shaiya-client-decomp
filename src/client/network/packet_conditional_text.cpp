#include "packet_conditional_text.h"
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
} // namespace
extern "C" __attribute__((noinline)) void read_status_00596b90(PacketReader* reader, uint8_t* frame,
                                                               uint32_t) {
    read_packet_bytes_with_diagnostic(reader, frame, 1);
}
// Complete original596b90..596c25. Nonzero status skips all five following
// reads; callback arguments still include the inherited DWORDs/text storage.
// The original has no caller text clear or terminator insertion.
extern "C" __attribute__((noinline)) void prepare_conditional_00596b90(PacketReader* reader,
                                                                       uint8_t* frame,
                                                                       uint32_t* outgoing,
                                                                       uint32_t* state) {
    if (byte(frame) == 0) {
        read_available_packet_bytes(reader, frame + 40, 21);
        read_packet_bytes_with_diagnostic(reader, frame + 12, 4);
        read_available_packet_bytes(reader, frame + 16, 21);
        read_packet_bytes_with_diagnostic(reader, frame + 8, 4);
        read_packet_bytes_with_diagnostic(reader, frame + 4, 4);
    }
    const uint32_t last = word(frame + 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    put(outgoing + 5, last);
    put(outgoing + 4, word(frame + 8));
    put(outgoing + 3, reinterpret_cast<uint32_t>(frame + 16));
    put(outgoing + 2, word(frame + 12));
    put(outgoing + 1, reinterpret_cast<uint32_t>(frame + 40));
    put(outgoing, word(frame));
    put(state, reinterpret_cast<uint32_t>(receiver));
    put(state + 1, table);
}
extern "C" __attribute__((naked)) void fun_00596b90(PacketReader*) {
    // Original64B frame, ESI cached reader, actual six-word callbackSP E-96.
    // All C++ preparation returns before the callback and its own stack use.
    __asm__ volatile(
        "subl $64,%esp\n\tpushl %esi\n\tmovl 72(%esp),%esi\n\tpushl $1\n\tleal 8(%esp),%eax\n\tpushl %eax\n\tpushl %esi\n\tcall _read_status_00596b90\n\taddl $12,%esp\n\tsubl $32,%esp\n\tmovl %esp,%eax\n\tleal 8(%esp),%edx\n\tleal 36(%esp),%ecx\n\tpushl %eax\n\tpushl %edx\n\tpushl %ecx\n\tpushl %esi\n\tcall _prepare_conditional_00596b90\n\taddl $16,%esp\n\tmovl (%esp),%ecx\n\tmovl 4(%esp),%eax\n\taddl $8,%esp\n\tmovl (%esp),%edx\n\tcall *0x598(%eax)\n\tpopl %esi\n\taddl $64,%esp\n\tret");
}
