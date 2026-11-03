#include "packet_reply_echo.h"
#include "network/outbound.h"
namespace {
uint32_t word(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
uint8_t read_byte(const void* pointer) {
    uint8_t value;
    __asm__ volatile("movb (%1),%0" : "=q"(value) : "r"(pointer) : "memory");
    return value;
}
void put_word(void* pointer, uint16_t value) {
    __asm__ volatile("movw %1,(%0)" ::"r"(pointer), "r"(value) : "memory");
}
void put(void* pointer, uint32_t value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(pointer), "r"(value) : "memory");
}
void put_byte(void* pointer, uint8_t value) {
    __asm__ volatile("movb %1,(%0)" ::"r"(pointer), "q"(value) : "memory");
}
} // namespace
// These adapters retain the original two length argument slots while the
// actual reader implementations execute. The third parameters are not fields.
extern "C" __attribute__((noinline)) void read_first_0059cf10(PacketReader* reader, uint8_t* output,
                                                              uint32_t) {
    read_packet_bytes_with_diagnostic(reader, output, 4);
}
extern "C" __attribute__((noinline)) void read_second_0059cf10(PacketReader* reader,
                                                               uint8_t* output, uint32_t) {
    read_packet_bytes_with_diagnostic(reader, output, 1);
}
// Exact original DWORD-then-BYTE reads followed by WORD/DWORD/BYTE writes.
// Only the seven-byte reply at original frame+8 is constructed; the remaining
// stack allocation is neither initialized nor forwarded to the sender.
extern "C" __attribute__((noinline)) void build_reply_0059cf10(uint8_t* frame) {
    const uint32_t value = word(frame + 4);
    const uint8_t field = read_byte(frame + 3);
    put_word(frame + 8, 0x0b1b);
    put(frame + 10, value);
    put_byte(frame + 14, field);
}
extern "C" __attribute__((naked)) void fun_0059cf10(PacketReader*) {
    // Genuine8200-byte stack probe, exact reader outputs and real597f60 call
    // with its original packet address and two outgoing argument positions.
    // No helper remains suspended when the real sender starts executing.
    __asm__ volatile(
        "movl $8200,%eax\n\tcall _fun_005cd2a0\n\tpushl %esi\n\tmovl 8208(%esp),%esi\n\tpushl $4\n\tleal 12(%esp),%eax\n\tpushl %eax\n\tpushl %esi\n\tcall _read_first_0059cf10\n\taddl $12,%esp\n\tpushl $1\n\tleal 11(%esp),%eax\n\tpushl %eax\n\tpushl %esi\n\tcall _read_second_0059cf10\n\taddl $12,%esp\n\tleal 4(%esp),%eax\n\tpushl %eax\n\tcall _build_reply_0059cf10\n\taddl $4,%esp\n\tleal 12(%esp),%ecx\n\tpushl $7\n\tpushl %ecx\n\tcall _fun_00597f60\n\taddl $8,%esp\n\tpopl %esi\n\taddl $8200,%esp\n\tret");
}
