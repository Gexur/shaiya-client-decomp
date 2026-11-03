#include "packet_scalar_loop.h"
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
} // namespace
// Original596d10..596d62. The original eight bytes at entryESP-8 retain
// inherited gaps and the upper24 bits of the one-byte element read.
extern "C" __attribute__((noinline)) uint32_t scalar_loop_00596d10(const void* arguments,
                                                                   uint8_t* frame) {
    auto* reader = reinterpret_cast<PacketReader*>(word(arguments));
    uint32_t result = read_packet_bytes_with_diagnostic(reader, frame + 3, 1);
    const uint32_t initial_count = byte(frame + 3);
    result = (result & 0xffffff00u) | initial_count; // actual MOV AL preserves EAX upper24
    if (initial_count != 0) {
        int32_t index = 0;
        do {
            read_packet_bytes_with_diagnostic(reader, frame + 4, 1);
            auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
            const uint32_t scalar = word(frame + 4);
            const uint32_t table = word(receiver);
            __asm__ volatile(
                "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl %%eax\n\tcall *0x5a0(%%edx)"
                : "=a"(result)
                : "m"(receiver), "m"(scalar), "m"(table)
                : "ecx", "edx", "memory", "cc");
            const int32_t count = static_cast<int32_t>(byte(frame + 3));
            ++index;
            if (index >= count)
                break;
        } while (true);
    }
    return result;
}
extern "C" __attribute__((naked)) void fun_00596d10(PacketReader*) {
    __asm__ volatile(
        "subl $8,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 20(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _scalar_loop_00596d10\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}
