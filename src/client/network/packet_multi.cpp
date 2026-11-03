#include "packet_multi.h"

namespace {
inline uint32_t read_word(const void* p) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(p) : "memory");
    return value;
}
} // namespace

// Original 0x0058e280..0x0058e330, 8readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058e280(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t table = read_word(receiver);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t value_7 = read_word(scratch + 28);
    const uint32_t call_words[8] = {value_0, value_1, value_2, value_3,
                                    value_4, value_5, value_6, value_7};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tpushl 24(%%eax)\n\tmovl 28(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x60(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058e280(PacketReader*) {
    __asm__ volatile("subl $32,%esp\n\tpushl %esi\n\tleal 40(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058e280\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $32,%esp\n\tret");
}

// Original 0x0058eca0..0x0058ed17, 5readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058eca0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t call_words[5] = {value_0, value_1, value_2, value_3, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tmovl 16(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x78(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058eca0(PacketReader*) {
    __asm__ volatile("subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058eca0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x0058eda0..0x0058ee2d, 6readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058eda0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t call_words[6] = {value_0, value_1, value_2, value_3, value_4, value_5};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl 0(%%edx)\n\tpushl 4(%%edx)\n\tpushl 8(%%edx)\n\tpushl 12(%%edx)\n\tpushl 16(%%edx)\n\tmovl 20(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x84(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058eda0(PacketReader*) {
    __asm__ volatile("subl $24,%esp\n\tpushl %esi\n\tleal 32(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058eda0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $24,%esp\n\tret");
}

// Original 0x0058ee30..0x0058ee97, 4readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058ee30(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t call_words[4] = {value_0, value_1, value_2, value_3};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tmovl 12(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x88(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058ee30(PacketReader*) {
    __asm__ volatile("subl $16,%esp\n\tpushl %esi\n\tleal 24(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058ee30\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}

// Original 0x0058ef60..0x0058efda, 5readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058ef60(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t call_words[5] = {value_0, value_1, value_2, value_3, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tmovl 16(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x9c(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058ef60(PacketReader*) {
    __asm__ volatile("subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058ef60\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x0058f0d0..0x0058f14a, 5readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058f0d0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t call_words[5] = {value_0, value_1, value_2, value_3, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tmovl 16(%%eax),%%eax\n\tpushl %%eax\n\tcall *0xb8(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058f0d0(PacketReader*) {
    __asm__ volatile("subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058f0d0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x0058f260..0x0058f2c7, 4readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058f260(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t call_words[4] = {value_0, value_1, value_2, value_3};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tmovl 12(%%eax),%%eax\n\tpushl %%eax\n\tcall *0xc0(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058f260(PacketReader*) {
    __asm__ volatile("subl $16,%esp\n\tpushl %esi\n\tleal 24(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058f260\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}

// Original 0x0058f320..0x0058f3d3, 8readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058f320(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t table = read_word(receiver);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t value_7 = read_word(scratch + 28);
    const uint32_t call_words[8] = {value_0, value_1, value_2, value_3,
                                    value_4, value_5, value_6, value_7};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tpushl 24(%%eax)\n\tmovl 28(%%eax),%%eax\n\tpushl %%eax\n\tcall *0xcc(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058f320(PacketReader*) {
    __asm__ volatile("subl $32,%esp\n\tpushl %esi\n\tleal 40(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058f320\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $32,%esp\n\tret");
}

// Original 0x0058f640..0x0058f6cd, 6readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058f640(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t call_words[6] = {value_0, value_1, value_2, value_3, value_4, value_5};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl 0(%%edx)\n\tpushl 4(%%edx)\n\tpushl 8(%%edx)\n\tpushl 12(%%edx)\n\tpushl 16(%%edx)\n\tmovl 20(%%edx),%%edx\n\tpushl %%edx\n\tcall *0xe4(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058f640(PacketReader*) {
    __asm__ volatile("subl $24,%esp\n\tpushl %esi\n\tleal 32(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058f640\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $24,%esp\n\tret");
}

// Original 0x0058f6d0..0x0058f75d, 6readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058f6d0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t call_words[6] = {value_0, value_1, value_2, value_3, value_4, value_5};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl 0(%%edx)\n\tpushl 4(%%edx)\n\tpushl 8(%%edx)\n\tpushl 12(%%edx)\n\tpushl 16(%%edx)\n\tmovl 20(%%edx),%%edx\n\tpushl %%edx\n\tcall *0xe8(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058f6d0(PacketReader*) {
    __asm__ volatile("subl $24,%esp\n\tpushl %esi\n\tleal 32(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058f6d0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $24,%esp\n\tret");
}

// Original 0x0058f7c0..0x0058f827, 4readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058f7c0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t call_words[4] = {value_0, value_1, value_2, value_3};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tmovl 12(%%eax),%%eax\n\tpushl %%eax\n\tcall *0xf0(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058f7c0(PacketReader*) {
    __asm__ volatile("subl $16,%esp\n\tpushl %esi\n\tleal 24(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058f7c0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}

// Original 0x0058fb50..0x0058fbb7, 4readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058fb50(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t call_words[4] = {value_0, value_1, value_2, value_3};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tmovl 12(%%eax),%%eax\n\tpushl %%eax\n\tcall *0xf4(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058fb50(PacketReader*) {
    __asm__ volatile("subl $16,%esp\n\tpushl %esi\n\tleal 24(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058fb50\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}

// Original 0x0058fbc0..0x0058fc4d, 6readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058fbc0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t call_words[6] = {value_0, value_1, value_2, value_3, value_4, value_5};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl 0(%%edx)\n\tpushl 4(%%edx)\n\tpushl 8(%%edx)\n\tpushl 12(%%edx)\n\tpushl 16(%%edx)\n\tmovl 20(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x108(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058fbc0(PacketReader*) {
    __asm__ volatile("subl $24,%esp\n\tpushl %esi\n\tleal 32(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058fbc0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $24,%esp\n\tret");
}

// Original 0x0058fc50..0x0058fcca, 5readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058fc50(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t call_words[5] = {value_0, value_1, value_2, value_3, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tmovl 16(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x110(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058fc50(PacketReader*) {
    __asm__ volatile("subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058fc50\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x0058fe10..0x0058fe9d, 6readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058fe10(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t call_words[6] = {value_0, value_1, value_2, value_3, value_4, value_5};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl 0(%%edx)\n\tpushl 4(%%edx)\n\tpushl 8(%%edx)\n\tpushl 12(%%edx)\n\tpushl 16(%%edx)\n\tmovl 20(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x140(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058fe10(PacketReader*) {
    __asm__ volatile("subl $24,%esp\n\tpushl %esi\n\tleal 32(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058fe10\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $24,%esp\n\tret");
}

// Original 0x0058fea0..0x0058ff07, 4readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058fea0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t call_words[4] = {value_0, value_1, value_2, value_3};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tmovl 12(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x144(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058fea0(PacketReader*) {
    __asm__ volatile("subl $16,%esp\n\tpushl %esi\n\tleal 24(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058fea0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}

// Original 0x0058ff10..0x0058ffc3, 8readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_0058ff10(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t table = read_word(receiver);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t value_7 = read_word(scratch + 28);
    const uint32_t call_words[8] = {value_0, value_1, value_2, value_3,
                                    value_4, value_5, value_6, value_7};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tpushl 24(%%eax)\n\tmovl 28(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x148(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_0058ff10(PacketReader*) {
    __asm__ volatile("subl $32,%esp\n\tpushl %esi\n\tleal 40(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_0058ff10\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $32,%esp\n\tret");
}

// Original 0x00590120..0x005901d3, 8readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00590120(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t table = read_word(receiver);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t value_7 = read_word(scratch + 28);
    const uint32_t call_words[8] = {value_0, value_1, value_2, value_3,
                                    value_4, value_5, value_6, value_7};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tpushl 24(%%eax)\n\tmovl 28(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x154(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00590120(PacketReader*) {
    __asm__ volatile("subl $32,%esp\n\tpushl %esi\n\tleal 40(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00590120\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $32,%esp\n\tret");
}

// Original 0x005901e0..0x00590280, 7readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_005901e0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t call_words[7] = {value_0, value_1, value_2, value_3, value_4, value_5, value_6};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tmovl 24(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x158(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005901e0(PacketReader*) {
    __asm__ volatile("subl $28,%esp\n\tpushl %esi\n\tleal 36(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_005901e0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $28,%esp\n\tret");
}

// Original 0x00590280..0x005902fa, 5readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00590280(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t call_words[5] = {value_0, value_1, value_2, value_3, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tmovl 16(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x15c(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00590280(PacketReader*) {
    __asm__ volatile("subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00590280\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x00590300..0x00590367, 4readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00590300(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t call_words[4] = {value_0, value_1, value_2, value_3};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tmovl 12(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x160(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00590300(PacketReader*) {
    __asm__ volatile("subl $16,%esp\n\tpushl %esi\n\tleal 24(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00590300\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}

// Original 0x00590370..0x00590423, 8readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00590370(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t table = read_word(receiver);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t value_7 = read_word(scratch + 28);
    const uint32_t call_words[8] = {value_0, value_1, value_2, value_3,
                                    value_4, value_5, value_6, value_7};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tpushl 24(%%eax)\n\tmovl 28(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x164(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00590370(PacketReader*) {
    __asm__ volatile("subl $32,%esp\n\tpushl %esi\n\tleal 40(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00590370\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $32,%esp\n\tret");
}

// Original 0x00590520..0x005905d3, 8readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00590520(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t table = read_word(receiver);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t value_7 = read_word(scratch + 28);
    const uint32_t call_words[8] = {value_0, value_1, value_2, value_3,
                                    value_4, value_5, value_6, value_7};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tpushl 24(%%eax)\n\tmovl 28(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x16c(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00590520(PacketReader*) {
    __asm__ volatile("subl $32,%esp\n\tpushl %esi\n\tleal 40(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00590520\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $32,%esp\n\tret");
}

// Original 0x005905e0..0x00590680, 7readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_005905e0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t call_words[7] = {value_0, value_1, value_2, value_3, value_4, value_5, value_6};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tmovl 24(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x170(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005905e0(PacketReader*) {
    __asm__ volatile("subl $28,%esp\n\tpushl %esi\n\tleal 36(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_005905e0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $28,%esp\n\tret");
}

// Original 0x00590680..0x005906fa, 5readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00590680(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t call_words[5] = {value_0, value_1, value_2, value_3, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tmovl 16(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x174(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00590680(PacketReader*) {
    __asm__ volatile("subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00590680\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x00590970..0x00590a23, 8readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00590970(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t table = read_word(receiver);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t value_7 = read_word(scratch + 28);
    const uint32_t call_words[8] = {value_0, value_1, value_2, value_3,
                                    value_4, value_5, value_6, value_7};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tpushl 24(%%eax)\n\tmovl 28(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x184(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00590970(PacketReader*) {
    __asm__ volatile("subl $32,%esp\n\tpushl %esi\n\tleal 40(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00590970\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $32,%esp\n\tret");
}

// Original 0x00590a30..0x00590ad0, 7readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00590a30(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t call_words[7] = {value_0, value_1, value_2, value_3, value_4, value_5, value_6};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tmovl 24(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x188(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00590a30(PacketReader*) {
    __asm__ volatile("subl $28,%esp\n\tpushl %esi\n\tleal 36(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00590a30\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $28,%esp\n\tret");
}

// Original 0x00590ad0..0x00590b4a, 5readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00590ad0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t call_words[5] = {value_0, value_1, value_2, value_3, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tmovl 16(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x18c(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00590ad0(PacketReader*) {
    __asm__ volatile("subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00590ad0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x00590b50..0x00590bca, 5readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00590b50(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t call_words[5] = {value_0, value_1, value_2, value_3, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tmovl 16(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x190(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00590b50(PacketReader*) {
    __asm__ volatile("subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00590b50\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x00590c00..0x00590c67, 4readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00590c00(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t call_words[4] = {value_0, value_1, value_2, value_3};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tmovl 12(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x198(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00590c00(PacketReader*) {
    __asm__ volatile("subl $16,%esp\n\tpushl %esi\n\tleal 24(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00590c00\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}

// Original 0x00590ca0..0x00590d2d, 6readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00590ca0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t call_words[6] = {value_0, value_1, value_2, value_3, value_4, value_5};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl 0(%%edx)\n\tpushl 4(%%edx)\n\tpushl 8(%%edx)\n\tpushl 12(%%edx)\n\tpushl 16(%%edx)\n\tmovl 20(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x1a0(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00590ca0(PacketReader*) {
    __asm__ volatile("subl $24,%esp\n\tpushl %esi\n\tleal 32(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00590ca0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $24,%esp\n\tret");
}

// Original 0x00590df0..0x00590e7d, 6readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00590df0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t call_words[6] = {value_0, value_1, value_2, value_3, value_4, value_5};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl 0(%%edx)\n\tpushl 4(%%edx)\n\tpushl 8(%%edx)\n\tpushl 12(%%edx)\n\tpushl 16(%%edx)\n\tmovl 20(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x1ac(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00590df0(PacketReader*) {
    __asm__ volatile("subl $24,%esp\n\tpushl %esi\n\tleal 32(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00590df0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $24,%esp\n\tret");
}

// Original 0x00590ef0..0x00590f90, 7readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00590ef0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t call_words[7] = {value_0, value_1, value_2, value_3, value_4, value_5, value_6};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tmovl 24(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x1b4(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00590ef0(PacketReader*) {
    __asm__ volatile("subl $28,%esp\n\tpushl %esi\n\tleal 36(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00590ef0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $28,%esp\n\tret");
}

// Original 0x00590f90..0x00591030, 7readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00590f90(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t call_words[7] = {value_0, value_1, value_2, value_3, value_4, value_5, value_6};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tmovl 24(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x1b8(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00590f90(PacketReader*) {
    __asm__ volatile("subl $28,%esp\n\tpushl %esi\n\tleal 36(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00590f90\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $28,%esp\n\tret");
}

// Original 0x00592f50..0x00592ff0, 7readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00592f50(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t call_words[7] = {value_0, value_1, value_2, value_3, value_4, value_5, value_6};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tmovl 24(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x2d0(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00592f50(PacketReader*) {
    __asm__ volatile("subl $28,%esp\n\tpushl %esi\n\tleal 36(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00592f50\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $28,%esp\n\tret");
}

// Original 0x00593020..0x0059309a, 5readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00593020(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t call_words[5] = {value_0, value_1, value_2, value_3, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tmovl 16(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x2d8(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593020(PacketReader*) {
    __asm__ volatile("subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00593020\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x005930d0..0x00593137, 4readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_005930d0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t call_words[4] = {value_0, value_1, value_2, value_3};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tmovl 12(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x2e0(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005930d0(PacketReader*) {
    __asm__ volatile("subl $16,%esp\n\tpushl %esi\n\tleal 24(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_005930d0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}

// Original 0x00593140..0x005931a7, 4readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00593140(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t call_words[4] = {value_0, value_1, value_2, value_3};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tmovl 12(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x2e4(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593140(PacketReader*) {
    __asm__ volatile("subl $16,%esp\n\tpushl %esi\n\tleal 24(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00593140\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}

// Original 0x00593c40..0x00593ca7, 4readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00593c40(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t call_words[4] = {value_0, value_1, value_2, value_3};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tmovl 12(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x324(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593c40(PacketReader*) {
    __asm__ volatile("subl $16,%esp\n\tpushl %esi\n\tleal 24(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00593c40\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}

// Original 0x00593cb0..0x00593d2a, 5readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00593cb0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t call_words[5] = {value_0, value_1, value_2, value_3, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tmovl 16(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x328(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593cb0(PacketReader*) {
    __asm__ volatile("subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00593cb0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x00593d30..0x00593daa, 5readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00593d30(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t call_words[5] = {value_0, value_1, value_2, value_3, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tmovl 16(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x32c(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593d30(PacketReader*) {
    __asm__ volatile("subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00593d30\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x00593db0..0x00593e2a, 5readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00593db0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t call_words[5] = {value_0, value_1, value_2, value_3, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tmovl 16(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x338(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593db0(PacketReader*) {
    __asm__ volatile("subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00593db0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x00593fd0..0x0059404a, 5readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00593fd0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t call_words[5] = {value_0, value_1, value_2, value_3, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tmovl 16(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x350(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593fd0(PacketReader*) {
    __asm__ volatile("subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00593fd0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x00594050..0x005940ca, 5readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00594050(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t call_words[5] = {value_0, value_1, value_2, value_3, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tmovl 16(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x354(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00594050(PacketReader*) {
    __asm__ volatile("subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00594050\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x005940d0..0x0059414a, 5readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_005940d0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t call_words[5] = {value_0, value_1, value_2, value_3, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tmovl 16(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x358(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005940d0(PacketReader*) {
    __asm__ volatile("subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_005940d0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x00595840..0x005958a7, 4readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00595840(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t call_words[4] = {value_0, value_1, value_2, value_3};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tmovl 12(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x4b0(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00595840(PacketReader*) {
    __asm__ volatile("subl $16,%esp\n\tpushl %esi\n\tleal 24(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00595840\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}

// Original 0x00596150..0x005961dd, 6readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00596150(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t call_words[6] = {value_0, value_1, value_2, value_3, value_4, value_5};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl 0(%%edx)\n\tpushl 4(%%edx)\n\tpushl 8(%%edx)\n\tpushl 12(%%edx)\n\tpushl 16(%%edx)\n\tmovl 20(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x520(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00596150(PacketReader*) {
    __asm__ volatile("subl $24,%esp\n\tpushl %esi\n\tleal 32(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00596150\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $24,%esp\n\tret");
}

// Original 0x00596380..0x005963fa, 5readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00596380(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t call_words[5] = {value_0, value_1, value_2, value_3, value_4};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tmovl 16(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x540(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00596380(PacketReader*) {
    __asm__ volatile("subl $20,%esp\n\tpushl %esi\n\tleal 28(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00596380\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $20,%esp\n\tret");
}

// Original 0x00596490..0x005964f7, 4readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00596490(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t call_words[4] = {value_0, value_1, value_2, value_3};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tmovl 12(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x554(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00596490(PacketReader*) {
    __asm__ volatile("subl $16,%esp\n\tpushl %esi\n\tleal 24(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00596490\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}

// Original 0x00596fd0..0x00597037, 4readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00596fd0(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t call_words[4] = {value_0, value_1, value_2, value_3};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tmovl 12(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x2b0(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00596fd0(PacketReader*) {
    __asm__ volatile("subl $16,%esp\n\tpushl %esi\n\tleal 24(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00596fd0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}

// Original 0x00597940..0x005979a7, 4readers; exact owned load order below.
extern "C" __attribute__((noinline)) uint32_t multi_00597940(const void* actual_arguments,
                                                             uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t call_words[4] = {value_0, value_1, value_2, value_3};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tmovl 12(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x5f0(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00597940(PacketReader*) {
    __asm__ volatile("subl $16,%esp\n\tpushl %esi\n\tleal 24(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _multi_00597940\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}
