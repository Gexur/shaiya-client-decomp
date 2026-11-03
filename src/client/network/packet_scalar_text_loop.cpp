#include "packet_scalar_text_loop.h"
namespace {
uint32_t word(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
void put(void* pointer, uint32_t value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(pointer), "r"(value) : "memory");
}
} // namespace
extern "C" __attribute__((noinline)) uint32_t read_count_scalar_text(PacketReader* reader,
                                                                     uint8_t* frame, uint32_t) {
    return read_packet_bytes_with_diagnostic(reader, frame + 3, 1);
}
// Complete original597250..59737b and597b10..597c3b preparation.
// Eleven numeric slots retain the unread upper16/24 bits. The string reader
// requests21 bytes and is used directly, including its distinct short-read
// behavior; neither the caller nor this source adds a terminator or clear.
extern "C" __attribute__((noinline)) void read_scalar_text(PacketReader* reader, uint8_t* frame,
                                                           uint32_t* outgoing, uint32_t* state) {
    read_packet_bytes_with_diagnostic(reader, frame + 44, 1);
    read_packet_bytes_with_diagnostic(reader, frame + 40, 1);
    read_packet_bytes_with_diagnostic(reader, frame + 36, 1);
    read_packet_bytes_with_diagnostic(reader, frame + 28, 2);
    read_packet_bytes_with_diagnostic(reader, frame + 24, 1);
    read_packet_bytes_with_diagnostic(reader, frame + 20, 1);
    read_packet_bytes_with_diagnostic(reader, frame + 16, 1);
    read_packet_bytes_with_diagnostic(reader, frame + 12, 1);
    read_packet_bytes_with_diagnostic(reader, frame + 8, 1);
    read_packet_bytes_with_diagnostic(reader, frame + 4, 1);
    read_packet_bytes_with_diagnostic(reader, frame + 32, 1);
    read_available_packet_bytes(reader, frame + 48, 21);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    put(outgoing + 11, reinterpret_cast<uint32_t>(frame + 48));
    for (uint32_t index = 0; index != 11; ++index)
        put(outgoing + 10 - index, word(frame + 4 + index * 4));
    put(state, reinterpret_cast<uint32_t>(receiver));
    put(state + 1, table);
}
// Exact72-byte frame/count location and actual E-132 callbackSP. Each C++
// preparation has returned before the twelve-word virtual call. The outer
// register adapter retains ESI reader/EDI index and count reloads without
// clobbering the physical callback-returned EAX.
#define SCALAR_TEXT_ENTRY(name, slot)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
    extern "C" __attribute__((naked)) void name(PacketReader*) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   \
        __asm__ volatile(                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          \
            "subl $72,%esp\n\tpushl %esi\n\tmovl 80(%esp),%esi\n\tpushl %edi\n\tpushl $1\n\tleal 12(%esp),%eax\n\tpushl %eax\n\tpushl %esi\n\tcall _read_count_scalar_text\n\taddl $12,%esp\n\tmovb 11(%esp),%al\n\txorl %edi,%edi\n\ttestb %al,%al\n\tjbe 2f\n\t1:\n\tsubl $56,%esp\n\tmovl %esp,%eax\n\tleal 8(%esp),%edx\n\tleal 64(%esp),%ecx\n\tpushl %eax\n\tpushl %edx\n\tpushl %ecx\n\tpushl %esi\n\tcall _read_scalar_text\n\taddl $16,%esp\n\tmovl (%esp),%ecx\n\tmovl 4(%esp),%edx\n\taddl $8,%esp\n\tmovl (%esp),%eax\n\tcall *" #slot \
            "(%edx)\n\tmovzbl 11(%esp),%ecx\n\tincl %edi\n\tcmpl %ecx,%edi\n\tjl 1b\n\t2:\n\tpopl %edi\n\tpopl %esi\n\taddl $72,%esp\n\tret");                                                                                                                                                                                                                                                                                                                                                                                                     \
    }
SCALAR_TEXT_ENTRY(fun_00597250, 0x5bc)
SCALAR_TEXT_ENTRY(fun_00597b10, 0x610)
#undef SCALAR_TEXT_ENTRY
