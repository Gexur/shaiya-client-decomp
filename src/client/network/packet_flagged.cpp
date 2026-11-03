#include "packet_flagged.h"

namespace {
uint32_t word(const void* p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
} // namespace

// Original 0x00592870..0x005928c9; checked full flagged consumer body.
extern "C" __attribute__((noinline)) uint32_t flagged_00592870(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = word(static_cast<const uint8_t*>(actual_arguments) + 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_3 = word(scratch + 0);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t value_5 = word(scratch + 8);
    const uint32_t call_words[5] = {value_5, value_4, value_3, value_0, value_5};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 12(%%edx)\n\tpushl 8(%%edx)\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 16(%%edx),%%edx\n\tcall *0x26c(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00592870(PacketReader*, uint32_t) {
    __asm__ volatile(
        "subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _flagged_00592870\n\taddl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x005928d0..0x00592929; checked full flagged consumer body.
extern "C" __attribute__((noinline)) uint32_t flagged_005928d0(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = word(static_cast<const uint8_t*>(actual_arguments) + 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_3 = word(scratch + 0);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t value_5 = word(scratch + 8);
    const uint32_t call_words[5] = {value_5, value_4, value_3, value_0, value_5};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 12(%%edx)\n\tpushl 8(%%edx)\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 16(%%edx),%%edx\n\tcall *0x270(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005928d0(PacketReader*, uint32_t) {
    __asm__ volatile(
        "subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _flagged_005928d0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00592930..0x0059299c; checked full flagged consumer body.
extern "C" __attribute__((noinline)) uint32_t flagged_00592930(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = word(static_cast<const uint8_t*>(actual_arguments) + 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_3 = word(scratch + 0);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t value_5 = word(scratch + 8);
    const uint32_t value_6 = word(scratch + 12);
    const uint32_t call_words[6] = {value_6, value_5, value_4, value_3, value_0, value_6};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 20(%%eax),%%eax\n\tcall *0x274(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00592930(PacketReader*, uint32_t) {
    __asm__ volatile(
        "subl $16,%esp\n\tpushl %esi\n\tleal 24(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _flagged_00592930\n\taddl $8,%esp\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}

// Original 0x005929a0..0x005929f9; checked full flagged consumer body.
extern "C" __attribute__((noinline)) uint32_t flagged_005929a0(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    const uint32_t value_0 = word(static_cast<const uint8_t*>(actual_arguments) + 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_3 = word(scratch + 0);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t value_5 = word(scratch + 8);
    const uint32_t call_words[5] = {value_5, value_4, value_3, value_0, value_5};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 12(%%edx)\n\tpushl 8(%%edx)\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 16(%%edx),%%edx\n\tcall *0x278(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005929a0(PacketReader*, uint32_t) {
    __asm__ volatile(
        "subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _flagged_005929a0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00592a00..0x00592a59; checked full flagged consumer body.
extern "C" __attribute__((noinline)) uint32_t flagged_00592a00(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    const uint32_t value_0 = word(static_cast<const uint8_t*>(actual_arguments) + 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_3 = word(scratch + 0);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t value_5 = word(scratch + 8);
    const uint32_t call_words[5] = {value_5, value_4, value_3, value_0, value_5};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 12(%%edx)\n\tpushl 8(%%edx)\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 16(%%edx),%%edx\n\tcall *0x27c(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00592a00(PacketReader*, uint32_t) {
    __asm__ volatile(
        "subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _flagged_00592a00\n\taddl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00592a90..0x00592b0f; checked full flagged consumer body.
extern "C" __attribute__((noinline)) uint32_t flagged_00592a90(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = word(static_cast<const uint8_t*>(actual_arguments) + 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_3 = word(scratch + 0);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t value_5 = word(scratch + 8);
    const uint32_t value_6 = word(scratch + 12);
    const uint32_t value_7 = word(scratch + 16);
    const uint32_t call_words[7] = {value_7, value_6, value_5, value_4, value_3, value_0, value_7};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 20(%%eax)\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 24(%%eax),%%eax\n\tcall *0x284(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00592a90(PacketReader*, uint32_t) {
    __asm__ volatile(
        "subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _flagged_00592a90\n\taddl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x00592b10..0x00592b7c; checked full flagged consumer body.
extern "C" __attribute__((noinline)) uint32_t flagged_00592b10(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = word(static_cast<const uint8_t*>(actual_arguments) + 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_3 = word(scratch + 0);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t value_5 = word(scratch + 8);
    const uint32_t value_6 = word(scratch + 12);
    const uint32_t call_words[6] = {value_6, value_5, value_4, value_3, value_0, value_6};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 20(%%eax),%%eax\n\tcall *0x288(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00592b10(PacketReader*, uint32_t) {
    __asm__ volatile(
        "subl $16,%esp\n\tpushl %esi\n\tleal 24(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _flagged_00592b10\n\taddl $8,%esp\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}

// Original 0x00592b80..0x00592bc6; checked full flagged consumer body.
extern "C" __attribute__((noinline)) uint32_t flagged_00592b80(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = word(static_cast<const uint8_t*>(actual_arguments) + 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_3 = word(scratch + 0);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t call_words[4] = {value_4, value_3, value_0, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 12(%%eax),%%eax\n\tcall *0x28c(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00592b80(PacketReader*, uint32_t) {
    __asm__ volatile(
        "subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _flagged_00592b80\n\taddl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00592bd0..0x00592c29; checked full flagged consumer body.
extern "C" __attribute__((noinline)) uint32_t flagged_00592bd0(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    const uint32_t value_0 = word(static_cast<const uint8_t*>(actual_arguments) + 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_3 = word(scratch + 0);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t value_5 = word(scratch + 8);
    const uint32_t call_words[5] = {value_5, value_4, value_3, value_0, value_5};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 12(%%edx)\n\tpushl 8(%%edx)\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 16(%%edx),%%edx\n\tcall *0x290(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00592bd0(PacketReader*, uint32_t) {
    __asm__ volatile(
        "subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _flagged_00592bd0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}
