#include "packet_probe_frame.h"
// Actual recovered EAX/ESP stack-allocation/probe ABI, not a host alloca.
extern "C" void fun_005cd2a0();
namespace {
uint32_t word(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
uint32_t half(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movzwl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
} // namespace
// Original58d7e0..58d82f. Its WORD request length does not initialize the
// upper16 bits later passed as a full DWORD to the virtual method. The binary
// adds no bound check before the second fb80 call; neither does this source.
extern "C" __attribute__((noinline)) uint32_t probe_frame_0058d7e0(const void* arguments,
                                                                   uint8_t* frame) {
    auto* reader = reinterpret_cast<PacketReader*>(word(arguments));
    read_packet_bytes_with_diagnostic(reader, frame, 2);
    const uint32_t count = half(frame);
    read_packet_bytes_with_diagnostic(reader, frame + 4, count);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t scalar = word(frame);
    const uint32_t call_words[4] = {reinterpret_cast<uint32_t>(receiver), table,
                                    reinterpret_cast<uint32_t>(frame + 4), scalar};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%edx\n\tmovl (%%edx),%%ecx\n\tmovl 4(%%edx),%%eax\n\tpushl 8(%%edx)\n\tpushl 12(%%edx)\n\tmovl 12(%%edx),%%edx\n\tcall *4(%%eax)"
        : "=a"(result)
        : "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058d7e0(PacketReader*) {
    __asm__ volatile(
        "movl $4100,%eax\n\tcall _fun_005cd2a0\n\tpushl %esi\n\tleal 4(%esp),%edx\n\tleal 4108(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _probe_frame_0058d7e0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $4100,%esp\n\tret");
}
