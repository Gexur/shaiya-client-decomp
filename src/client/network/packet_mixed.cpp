#include "packet_mixed.h"

namespace {
uint32_t word(const void* p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
} // namespace

// Original 0x0058dbd0..0x0058dd2f; checked full mixed consumer body.
extern "C" __attribute__((noinline)) uint32_t mixed_0058dbd0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 48, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 44, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 40, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 36, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 32, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 52, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 56, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 60, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 64, 4);
    read_available_packet_bytes(reader, scratch + 68, 25);
    const uint32_t value_0 = reinterpret_cast<uint32_t>(scratch + 68);
    const uint32_t value_1 = reinterpret_cast<uint32_t>(scratch + 52);
    const uint32_t value_2 = word(scratch + 0);
    const uint32_t value_3 = word(scratch + 4);
    const uint32_t value_4 = word(scratch + 8);
    const uint32_t value_5 = word(scratch + 12);
    const uint32_t value_6 = word(scratch + 16);
    const uint32_t value_7 = word(scratch + 20);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t value_9 = word(scratch + 24);
    const uint32_t table = word(receiver);
    const uint32_t value_11 = word(scratch + 28);
    const uint32_t value_12 = word(scratch + 32);
    const uint32_t value_13 = word(scratch + 36);
    const uint32_t value_14 = word(scratch + 40);
    const uint32_t value_15 = word(scratch + 44);
    const uint32_t value_16 = word(scratch + 48);
    const uint32_t call_words[16] = {value_16, value_15, value_14, value_13, value_12, value_11,
                                     value_9,  value_7,  value_6,  value_5,  value_4,  value_3,
                                     value_2,  value_1,  value_0,  value_16};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 56(%%edx)\n\tpushl 52(%%edx)\n\tpushl 48(%%edx)\n\tpushl 44(%%edx)\n\tpushl 40(%%edx)\n\tpushl 36(%%edx)\n\tpushl 32(%%edx)\n\tpushl 28(%%edx)\n\tpushl 24(%%edx)\n\tpushl 20(%%edx)\n\tpushl 16(%%edx)\n\tpushl 12(%%edx)\n\tpushl 8(%%edx)\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 60(%%edx),%%edx\n\tcall *0x28(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058dbd0(PacketReader*) {
    __asm__ volatile(
        "subl $96,%esp\n\tpushl %esi\n\tleal 104(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _mixed_0058dbd0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $96,%esp\n\tret");
}

// Original 0x0058fa30..0x0058fabf; checked full mixed consumer body.
extern "C" __attribute__((noinline)) uint32_t mixed_0058fa30(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_3 = word(scratch + 4);
    const uint32_t value_4 = word(scratch + 8);
    const uint32_t value_5 = word(scratch + 12);
    const uint32_t value_6 = word(scratch + 16);
    const uint32_t value_7 = word(scratch + 20);
    const uint32_t call_words[8] = {0x00000000u, value_7, value_6, value_5,
                                    value_4,     value_3, value_0, value_7};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 24(%%edx)\n\tpushl 20(%%edx)\n\tpushl 16(%%edx)\n\tpushl 12(%%edx)\n\tpushl 8(%%edx)\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 28(%%edx),%%edx\n\tcall *0x104(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058fa30(PacketReader*) {
    __asm__ volatile(
        "subl $24,%esp\n\tpushl %esi\n\tleal 32(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _mixed_0058fa30\n\taddl $8,%esp\n\tpopl %esi\n\taddl $24,%esp\n\tret");
}

// Original 0x0058fac0..0x0058fb4f; checked full mixed consumer body.
extern "C" __attribute__((noinline)) uint32_t mixed_0058fac0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_3 = word(scratch + 4);
    const uint32_t value_4 = word(scratch + 8);
    const uint32_t value_5 = word(scratch + 12);
    const uint32_t value_6 = word(scratch + 16);
    const uint32_t value_7 = word(scratch + 20);
    const uint32_t call_words[8] = {0x00000001u, value_7, value_6, value_5,
                                    value_4,     value_3, value_0, value_7};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 24(%%edx)\n\tpushl 20(%%edx)\n\tpushl 16(%%edx)\n\tpushl 12(%%edx)\n\tpushl 8(%%edx)\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 28(%%edx),%%edx\n\tcall *0x104(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058fac0(PacketReader*) {
    __asm__ volatile(
        "subl $24,%esp\n\tpushl %esi\n\tleal 32(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _mixed_0058fac0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $24,%esp\n\tret");
}

// Original 0x00591170..0x005911d7; checked full mixed consumer body.
extern "C" __attribute__((noinline)) uint32_t mixed_00591170(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    read_available_packet_bytes(reader, scratch + 12, 21);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_2 = reinterpret_cast<uint32_t>(scratch + 12);
    const uint32_t value_3 = word(scratch + 0);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t value_5 = word(scratch + 8);
    const uint32_t call_words[5] = {value_5, value_4, value_3, value_2, value_5};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 16(%%eax),%%eax\n\tcall *0x1d4(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00591170(PacketReader*) {
    __asm__ volatile(
        "subl $36,%esp\n\tpushl %esi\n\tleal 44(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _mixed_00591170\n\taddl $8,%esp\n\tpopl %esi\n\taddl $36,%esp\n\tret");
}

// Original 0x005917b0..0x0059189c; checked full mixed consumer body.
extern "C" __attribute__((noinline)) uint32_t mixed_005917b0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 36, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 32, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    read_available_packet_bytes(reader, scratch + 40, 21);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_2 = reinterpret_cast<uint32_t>(scratch + 40);
    const uint32_t value_3 = word(scratch + 0);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t value_5 = word(scratch + 8);
    const uint32_t value_6 = word(scratch + 12);
    const uint32_t value_7 = word(scratch + 16);
    const uint32_t value_8 = word(scratch + 20);
    const uint32_t value_9 = word(scratch + 24);
    const uint32_t value_10 = word(scratch + 28);
    const uint32_t value_11 = word(scratch + 32);
    const uint32_t value_12 = word(scratch + 36);
    const uint32_t call_words[12] = {value_12, value_11, value_10, value_9, value_8, value_7,
                                     value_6,  value_5,  value_4,  value_3, value_2, value_12};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 40(%%eax)\n\tpushl 36(%%eax)\n\tpushl 32(%%eax)\n\tpushl 28(%%eax)\n\tpushl 24(%%eax)\n\tpushl 20(%%eax)\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 44(%%eax),%%eax\n\tcall *0x1e8(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005917b0(PacketReader*) {
    __asm__ volatile(
        "subl $64,%esp\n\tpushl %esi\n\tleal 72(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _mixed_005917b0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $64,%esp\n\tret");
}

// Original 0x00591e70..0x00591fa8; checked full mixed consumer body.
extern "C" __attribute__((noinline)) uint32_t mixed_00591e70(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 44, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 40, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 36, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 32, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 56, 8);
    read_packet_bytes_with_diagnostic(reader, scratch + 48, 8);
    read_available_packet_bytes(reader, scratch + 64, 21);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_2 = reinterpret_cast<uint32_t>(scratch + 64);
    const uint32_t value_3 = reinterpret_cast<uint32_t>(scratch + 48);
    const uint32_t value_4 = reinterpret_cast<uint32_t>(scratch + 56);
    const uint32_t value_5 = word(scratch + 0);
    const uint32_t value_6 = word(scratch + 4);
    const uint32_t value_7 = word(scratch + 8);
    const uint32_t value_8 = word(scratch + 12);
    const uint32_t value_9 = word(scratch + 16);
    const uint32_t value_10 = word(scratch + 20);
    const uint32_t value_11 = word(scratch + 24);
    const uint32_t value_12 = word(scratch + 28);
    const uint32_t value_13 = word(scratch + 32);
    const uint32_t value_14 = word(scratch + 36);
    const uint32_t value_15 = word(scratch + 40);
    const uint32_t value_16 = word(scratch + 44);
    const uint32_t call_words[16] = {value_16, value_15, value_14, value_13, value_12, value_11,
                                     value_10, value_9,  value_8,  value_7,  value_6,  value_5,
                                     value_4,  value_3,  value_2,  value_16};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 56(%%edx)\n\tpushl 52(%%edx)\n\tpushl 48(%%edx)\n\tpushl 44(%%edx)\n\tpushl 40(%%edx)\n\tpushl 36(%%edx)\n\tpushl 32(%%edx)\n\tpushl 28(%%edx)\n\tpushl 24(%%edx)\n\tpushl 20(%%edx)\n\tpushl 16(%%edx)\n\tpushl 12(%%edx)\n\tpushl 8(%%edx)\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 60(%%edx),%%edx\n\tcall *0x214(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00591e70(PacketReader*) {
    __asm__ volatile(
        "subl $88,%esp\n\tpushl %esi\n\tleal 96(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _mixed_00591e70\n\taddl $8,%esp\n\tpopl %esi\n\taddl $88,%esp\n\tret");
}

// Original 0x005947c0..0x00594827; checked full mixed consumer body.
extern "C" __attribute__((noinline)) uint32_t mixed_005947c0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    read_available_packet_bytes(reader, scratch + 12, 25);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_2 = reinterpret_cast<uint32_t>(scratch + 12);
    const uint32_t value_3 = word(scratch + 0);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t value_5 = word(scratch + 8);
    const uint32_t call_words[5] = {value_5, value_4, value_3, value_2, value_5};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 16(%%eax),%%eax\n\tcall *0x3cc(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005947c0(PacketReader*) {
    __asm__ volatile(
        "subl $40,%esp\n\tpushl %esi\n\tleal 48(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _mixed_005947c0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $40,%esp\n\tret");
}

// Original 0x00594f20..0x00594f9a; checked full mixed consumer body.
extern "C" __attribute__((noinline)) uint32_t mixed_00594f20(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 9);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    const uint32_t value_0 = word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_3 = word(scratch + 4);
    const uint32_t value_4 = word(scratch + 8);
    const uint32_t value_5 = reinterpret_cast<uint32_t>(scratch + 16);
    const uint32_t value_6 = word(scratch + 12);
    const uint32_t call_words[6] = {value_6, value_5, value_4, value_3, value_0, value_6};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 20(%%eax),%%eax\n\tcall *0x430(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00594f20(PacketReader*) {
    __asm__ volatile(
        "subl $28,%esp\n\tpushl %esi\n\tleal 36(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _mixed_00594f20\n\taddl $8,%esp\n\tpopl %esi\n\taddl $28,%esp\n\tret");
}

// Original 0x00595250..0x005952a4; checked full mixed consumer body.
extern "C" __attribute__((noinline)) uint32_t mixed_00595250(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    read_available_packet_bytes(reader, scratch + 8, 21);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_2 = reinterpret_cast<uint32_t>(scratch + 8);
    const uint32_t value_3 = word(scratch + 0);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t call_words[4] = {value_4, value_3, value_2, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 8(%%edx)\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 12(%%edx),%%edx\n\tcall *0x464(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00595250(PacketReader*) {
    __asm__ volatile(
        "subl $32,%esp\n\tpushl %esi\n\tleal 40(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _mixed_00595250\n\taddl $8,%esp\n\tpopl %esi\n\taddl $32,%esp\n\tret");
}

// Original 0x00596e80..0x00596efa; checked full mixed consumer body.
extern "C" __attribute__((noinline)) uint32_t mixed_00596e80(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 6);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_3 = reinterpret_cast<uint32_t>(scratch + 16);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t value_5 = word(scratch + 8);
    const uint32_t value_6 = word(scratch + 12);
    const uint32_t call_words[6] = {value_6, value_5, value_4, value_3, value_0, value_6};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 20(%%eax),%%eax\n\tcall *0x5a4(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00596e80(PacketReader*) {
    __asm__ volatile(
        "subl $24,%esp\n\tpushl %esi\n\tleal 32(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _mixed_00596e80\n\taddl $8,%esp\n\tpopl %esi\n\taddl $24,%esp\n\tret");
}

// Original 0x00597040..0x005970e0; checked full mixed consumer body.
extern "C" __attribute__((noinline)) uint32_t mixed_00597040(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 6);
    read_available_packet_bytes(reader, scratch + 28, 21);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_2 = reinterpret_cast<uint32_t>(scratch + 28);
    const uint32_t value_3 = reinterpret_cast<uint32_t>(scratch + 20);
    const uint32_t value_4 = word(scratch + 0);
    const uint32_t value_5 = word(scratch + 4);
    const uint32_t value_6 = word(scratch + 8);
    const uint32_t value_7 = word(scratch + 12);
    const uint32_t value_8 = word(scratch + 16);
    const uint32_t call_words[8] = {value_8, value_7, value_6, value_5,
                                    value_4, value_3, value_2, value_8};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 24(%%eax)\n\tpushl 20(%%eax)\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 28(%%eax),%%eax\n\tcall *0x2b4(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00597040(PacketReader*) {
    __asm__ volatile(
        "subl $52,%esp\n\tpushl %esi\n\tleal 60(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _mixed_00597040\n\taddl $8,%esp\n\tpopl %esi\n\taddl $52,%esp\n\tret");
}

// Original 0x00597380..0x00597492; checked full mixed consumer body.
extern "C" __attribute__((noinline)) uint32_t mixed_00597380(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 44, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 40, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 36, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 32, 1);
    read_available_packet_bytes(reader, scratch + 48, 21);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_3 = reinterpret_cast<uint32_t>(scratch + 48);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t value_5 = word(scratch + 8);
    const uint32_t value_6 = word(scratch + 12);
    const uint32_t value_7 = word(scratch + 16);
    const uint32_t value_8 = word(scratch + 20);
    const uint32_t value_9 = word(scratch + 24);
    const uint32_t value_10 = word(scratch + 28);
    const uint32_t value_11 = word(scratch + 32);
    const uint32_t value_12 = word(scratch + 36);
    const uint32_t value_13 = word(scratch + 40);
    const uint32_t value_14 = word(scratch + 44);
    const uint32_t call_words[14] = {value_14, value_13, value_12, value_11, value_10,
                                     value_9,  value_8,  value_7,  value_6,  value_5,
                                     value_4,  value_3,  value_0,  value_14};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 48(%%eax)\n\tpushl 44(%%eax)\n\tpushl 40(%%eax)\n\tpushl 36(%%eax)\n\tpushl 32(%%eax)\n\tpushl 28(%%eax)\n\tpushl 24(%%eax)\n\tpushl 20(%%eax)\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 52(%%eax),%%eax\n\tcall *0x5c0(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00597380(PacketReader*) {
    __asm__ volatile(
        "subl $72,%esp\n\tpushl %esi\n\tleal 80(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _mixed_00597380\n\taddl $8,%esp\n\tpopl %esi\n\taddl $72,%esp\n\tret");
}

// Original 0x005974a0..0x005975b2; checked full mixed consumer body.
extern "C" __attribute__((noinline)) uint32_t mixed_005974a0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 44, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 40, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 36, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 32, 1);
    read_available_packet_bytes(reader, scratch + 48, 21);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_3 = reinterpret_cast<uint32_t>(scratch + 48);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t value_5 = word(scratch + 8);
    const uint32_t value_6 = word(scratch + 12);
    const uint32_t value_7 = word(scratch + 16);
    const uint32_t value_8 = word(scratch + 20);
    const uint32_t value_9 = word(scratch + 24);
    const uint32_t value_10 = word(scratch + 28);
    const uint32_t value_11 = word(scratch + 32);
    const uint32_t value_12 = word(scratch + 36);
    const uint32_t value_13 = word(scratch + 40);
    const uint32_t value_14 = word(scratch + 44);
    const uint32_t call_words[14] = {value_14, value_13, value_12, value_11, value_10,
                                     value_9,  value_8,  value_7,  value_6,  value_5,
                                     value_4,  value_3,  value_0,  value_14};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 48(%%eax)\n\tpushl 44(%%eax)\n\tpushl 40(%%eax)\n\tpushl 36(%%eax)\n\tpushl 32(%%eax)\n\tpushl 28(%%eax)\n\tpushl 24(%%eax)\n\tpushl 20(%%eax)\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 52(%%eax),%%eax\n\tcall *0x5c4(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005974a0(PacketReader*) {
    __asm__ volatile(
        "subl $72,%esp\n\tpushl %esi\n\tleal 80(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _mixed_005974a0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $72,%esp\n\tret");
}

// Original 0x005975c0..0x00597635; checked full mixed consumer body.
extern "C" __attribute__((noinline)) uint32_t mixed_005975c0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    read_available_packet_bytes(reader, scratch + 12, 25);
    read_available_packet_bytes(reader, scratch + 40, 65);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_2 = reinterpret_cast<uint32_t>(scratch + 12);
    const uint32_t value_3 = word(scratch + 0);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t value_5 = word(scratch + 8);
    const uint32_t call_words[5] = {value_5, value_4, value_3, value_2, value_5};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 16(%%eax),%%eax\n\tcall *0x5d0(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005975c0(PacketReader*) {
    __asm__ volatile(
        "subl $108,%esp\n\tpushl %esi\n\tleal 116(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _mixed_005975c0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $108,%esp\n\tret");
}

// Original 0x00597c40..0x00597d3f; checked full mixed consumer body.
extern "C" __attribute__((noinline)) uint32_t mixed_00597c40(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 40, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 36, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 32, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 1);
    read_available_packet_bytes(reader, scratch + 44, 21);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value_2 = reinterpret_cast<uint32_t>(scratch + 44);
    const uint32_t value_3 = word(scratch + 0);
    const uint32_t value_4 = word(scratch + 4);
    const uint32_t value_5 = word(scratch + 8);
    const uint32_t value_6 = word(scratch + 12);
    const uint32_t value_7 = word(scratch + 16);
    const uint32_t value_8 = word(scratch + 20);
    const uint32_t value_9 = word(scratch + 24);
    const uint32_t value_10 = word(scratch + 28);
    const uint32_t value_11 = word(scratch + 32);
    const uint32_t value_12 = word(scratch + 36);
    const uint32_t value_13 = word(scratch + 40);
    const uint32_t call_words[13] = {value_13, value_12, value_11, value_10, value_9,
                                     value_8,  value_7,  value_6,  value_5,  value_4,
                                     value_3,  value_2,  value_13};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 44(%%edx)\n\tpushl 40(%%edx)\n\tpushl 36(%%edx)\n\tpushl 32(%%edx)\n\tpushl 28(%%edx)\n\tpushl 24(%%edx)\n\tpushl 20(%%edx)\n\tpushl 16(%%edx)\n\tpushl 12(%%edx)\n\tpushl 8(%%edx)\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 48(%%edx),%%edx\n\tcall *0x614(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00597c40(PacketReader*) {
    __asm__ volatile(
        "subl $68,%esp\n\tpushl %esi\n\tleal 76(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _mixed_00597c40\n\taddl $8,%esp\n\tpopl %esi\n\taddl $68,%esp\n\tret");
}
