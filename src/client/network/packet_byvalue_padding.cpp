#include "packet_byvalue_padding.h"
namespace {
uint32_t word(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
uint16_t half(const void* pointer) {
    uint16_t value;
    __asm__ volatile("movw (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
void put(void* pointer, uint32_t value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(pointer), "r"(value) : "memory");
}
void put_half(void* pointer, uint16_t value) {
    __asm__ volatile("movw %1,(%0)" ::"r"(pointer), "r"(value) : "memory");
}
} // namespace
// The third adapter argument occupies the original PUSH0x32 stack slot at
// entryESP-64. Its last two bytes later become the uncopied argument padding.
// It is not a recovered game parameter or an extra payload field.
extern "C" __attribute__((noinline)) void read_byvalue_005949f0(PacketReader* reader,
                                                                uint8_t* frame, uint32_t) {
    read_packet_bytes_with_diagnostic(reader, frame, 50);
}
// Complete original5949f0..594a2c algorithm. Copy only48+2 bytes into the
// actual52-byte outgoing argument area. Never clear or copy either tail.
extern "C" __attribute__((noinline)) void copy_byvalue_005949f0(uint8_t* frame, uint8_t* outgoing,
                                                                uint32_t* callback_state) {
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    for (uint32_t index = 0; index != 12; ++index)
        put(outgoing + index * 4, word(frame + index * 4));
    put_half(outgoing + 48, half(frame + 48));
    put(callback_state, reinterpret_cast<uint32_t>(receiver));
    put(callback_state + 1, table);
    put(callback_state + 2, reinterpret_cast<uint32_t>(frame + 50));
    put(callback_state + 3, reinterpret_cast<uint32_t>(outgoing + 50));
}
extern "C" __attribute__((naked)) void fun_005949f0(PacketReader*) {
    // Both C++ preparation calls have returned before the virtual method is
    // entered. It may freely use its stack below the original outgoing area.
    __asm__ volatile(
        "movl 4(%esp),%ecx\n\tsubl $52,%esp\n\tpushl %esi\n\tpushl %edi\n\tpushl $50\n\tleal 12(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcall _read_byvalue_005949f0\n\taddl $12,%esp\n\tsubl $52,%esp\n\tsubl $16,%esp\n\tmovl %esp,%eax\n\tleal 16(%esp),%edx\n\tleal 76(%esp),%ecx\n\tpushl %eax\n\tpushl %edx\n\tpushl %ecx\n\tcall _copy_byvalue_005949f0\n\taddl $12,%esp\n\tmovl (%esp),%ecx\n\tmovl 4(%esp),%edx\n\tmovl 8(%esp),%esi\n\tmovl 12(%esp),%edi\n\tmovl %ecx,%eax\n\taddl $16,%esp\n\tcall *0x3ec(%edx)\n\tpopl %edi\n\tpopl %esi\n\taddl $52,%esp\n\tret");
}
