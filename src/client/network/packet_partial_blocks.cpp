#include "packet_partial_blocks.h"

namespace {
uint32_t word(const void* p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
} // namespace

// Original 0x00594cd0..0x00594d11; exactfb80/fc10 output spans.
extern "C" __attribute__((noinline)) uint32_t partial_00594cd0(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    read_available_packet_bytes(reader, scratch + 4, 21);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t scalar = word(scratch);
    uint8_t* data = scratch + 4;
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl %4\n\tpushl %%eax\n\tcall *0x414(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(scalar), "m"(data)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00594cd0(PacketReader*) {
    __asm__ volatile(
        "subl $28,%esp\n\tpushl %esi\n\tleal 36(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _partial_00594cd0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $28,%esp\n\tret");
}

// Original 0x00595440..0x00595481; exactfb80/fc10 output spans.
extern "C" __attribute__((noinline)) uint32_t partial_00595440(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    read_available_packet_bytes(reader, scratch + 4, 21);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t scalar = word(scratch);
    uint8_t* data = scratch + 4;
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl %4\n\tpushl %%eax\n\tcall *0x478(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(scalar), "m"(data)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00595440(PacketReader*) {
    __asm__ volatile(
        "subl $28,%esp\n\tpushl %esi\n\tleal 36(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _partial_00595440\n\taddl $8,%esp\n\tpopl %esi\n\taddl $28,%esp\n\tret");
}

// Original 0x00597870..0x005978b1; exactfb80/fc10 output spans.
extern "C" __attribute__((noinline)) uint32_t partial_00597870(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    read_available_packet_bytes(reader, scratch + 4, 65);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t scalar = word(scratch);
    uint8_t* data = scratch + 4;
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl %4\n\tpushl %%eax\n\tcall *0x5e4(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(scalar), "m"(data)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00597870(PacketReader*) {
    __asm__ volatile(
        "subl $72,%esp\n\tpushl %esi\n\tleal 80(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _partial_00597870\n\taddl $8,%esp\n\tpopl %esi\n\taddl $72,%esp\n\tret");
}
