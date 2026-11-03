#include "packet_byvalue_mixed.h"
namespace {
uint32_t word(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
uint8_t byte(const void* pointer) {
    uint8_t value;
    __asm__ volatile("movb (%1),%0" : "=q"(value) : "r"(pointer) : "memory");
    return value;
}
void put(void* pointer, uint32_t value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(pointer), "r"(value) : "memory");
}
void put_byte(void* pointer, uint8_t value) {
    __asm__ volatile("movb %1,(%0)" ::"r"(pointer), "q"(value) : "memory");
}
} // namespace
// The third adapter argument occupies the original literal reader-length
// argument slot at entryESP-48. It is neither a game field nor an extra input.
extern "C" __attribute__((noinline)) void read_first_00594b80(PacketReader* reader, uint8_t* frame,
                                                              uint32_t) {
    read_packet_bytes_with_diagnostic(reader, frame, 1);
}
extern "C" __attribute__((noinline)) void read_second_00594b80(PacketReader* reader, uint8_t* frame,
                                                               uint32_t) {
    read_packet_bytes_with_diagnostic(reader, frame, 29);
}
// Original594b80..594bd0: seven DWORD copies, full first scalar read/push,
// then the last BYTE copy. The outgoing block's three uncopied tail bytes
// retain the upper bytes of the earlier PUSH29 word, including mutations.
extern "C" __attribute__((noinline)) void copy_byvalue_00594b80(uint8_t* frame, uint8_t* outgoing,
                                                                uint32_t* callback_state) {
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    for (uint32_t index = 0; index != 7; ++index)
        put(outgoing + index * 4, word(frame + 4 + index * 4));
    put(outgoing - 4, word(frame));
    put_byte(outgoing + 28, byte(frame + 32));
    put(callback_state, reinterpret_cast<uint32_t>(receiver));
    put(callback_state + 1, table);
    put(callback_state + 2, reinterpret_cast<uint32_t>(frame + 33));
    put(callback_state + 3, reinterpret_cast<uint32_t>(outgoing + 29));
}
extern "C" __attribute__((naked)) void fun_00594b80(PacketReader*) {
    // Every C++ preparation returns before callback entry. Its stack begins
    // at the original entryESP-84 with the real36-byte argument area above it.
    __asm__ volatile(
        "subl $36,%esp\n\tpushl %esi\n\tmovl 44(%esp),%esi\n\tpushl %edi\n\tpushl $1\n\tleal 12(%esp),%eax\n\tpushl %eax\n\tpushl %esi\n\tcall _read_first_00594b80\n\taddl $12,%esp\n\tpushl $29\n\tleal 16(%esp),%eax\n\tpushl %eax\n\tpushl %esi\n\tcall _read_second_00594b80\n\taddl $12,%esp\n\tsubl $36,%esp\n\tsubl $16,%esp\n\tmovl %esp,%eax\n\tleal 20(%esp),%edx\n\tleal 60(%esp),%ecx\n\tpushl %eax\n\tpushl %edx\n\tpushl %ecx\n\tcall _copy_byvalue_00594b80\n\taddl $12,%esp\n\tmovl (%esp),%ecx\n\tmovl 4(%esp),%edx\n\tmovl 8(%esp),%esi\n\tmovl 12(%esp),%edi\n\tmovl %ecx,%eax\n\taddl $16,%esp\n\tcall *0x400(%edx)\n\tpopl %edi\n\tpopl %esi\n\taddl $36,%esp\n\tret");
}
