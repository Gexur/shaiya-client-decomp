#include "packet_aligned.h"
namespace {
uint32_t read_4(const void* p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
uint32_t read_1(const void* p) {
    uint32_t v;
    __asm__ volatile("movzbl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
uint32_t read_2(const void* p) {
    uint32_t v;
    __asm__ volatile("movzwl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void zero_4(void* p) {
    __asm__ volatile("movl $0,(%0)" ::"r"(p) : "memory");
}
void zero_1(void* p) {
    __asm__ volatile("movb $0,(%0)" ::"r"(p) : "memory");
}
void clear(void* p, uint32_t count) {
    uint32_t value = 0;
    __asm__ volatile("rep stosl" : "+D"(p), "+c"(count) : "a"(value) : "memory");
}
} // namespace

// Complete original 0x005931b0..0x00593223; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t aligned_005931b0(const void* actual_arguments,
                                                               uint8_t* frame) {
    auto* reader_0 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    clear(frame + 8, 32);
    read_packet_bytes_with_diagnostic(reader_0, frame + 4, 0x00000004u);
    read_packet_bytes_with_diagnostic(reader_0, frame + 0, 0x00000001u);
    const uint32_t value_4 = read_1(frame + 0);
    read_available_packet_bytes(reader_0, frame + 8, value_4);
    auto* receiver_6 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_7 = read_4(receiver_6);
    const uint32_t value_8 = read_4(frame + 0);
    const uint32_t value_9 = read_4(frame + 4);
    const uint32_t call_words[6] = {
        0x00000000u, 0x00000000u, value_9, value_8, reinterpret_cast<uint32_t>(frame + 8), value_9};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 20(%%eax),%%eax\n\tcall *0x2e8(%%edx)"
        : "=a"(result)
        : "m"(receiver_6), "m"(table_7), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005931b0(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $136,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _aligned_005931b0\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x00593230..0x005932ce; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t aligned_00593230(const void* actual_arguments,
                                                               uint8_t* frame) {
    zero_4(frame + 8);
    zero_4(frame + 12);
    auto* reader_2 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    zero_4(frame + 16);
    zero_4(frame + 20);
    zero_4(frame + 24);
    clear(frame + 32, 32);
    zero_1(frame + 28);
    read_packet_bytes_with_diagnostic(reader_2, frame + 4, 0x00000001u);
    read_available_packet_bytes(reader_2, frame + 8, 0x00000015u);
    read_packet_bytes_with_diagnostic(reader_2, frame + 0, 0x00000001u);
    const uint32_t value_11 = read_1(frame + 0);
    read_available_packet_bytes(reader_2, frame + 32, value_11);
    auto* receiver_13 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_14 = read_4(receiver_13);
    const uint32_t value_15 = read_4(frame + 0);
    const uint32_t value_16 = read_4(frame + 4);
    const uint32_t call_words[7] = {value_16,    0x00000000u,
                                    0x00000000u, reinterpret_cast<uint32_t>(frame + 8),
                                    value_15,    reinterpret_cast<uint32_t>(frame + 32),
                                    value_16};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 20(%%edx)\n\tpushl 16(%%edx)\n\tpushl 12(%%edx)\n\tpushl 8(%%edx)\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 24(%%edx),%%edx\n\tcall *0x2ec(%%eax)"
        : "=a"(result)
        : "m"(receiver_13), "m"(table_14), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593230(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $160,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _aligned_00593230\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x005932d0..0x0059335d; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t aligned_005932d0(const void* actual_arguments,
                                                               uint8_t* frame) {
    zero_4(frame + 8);
    zero_4(frame + 12);
    auto* reader_2 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    zero_4(frame + 16);
    zero_4(frame + 20);
    zero_4(frame + 24);
    clear(frame + 32, 32);
    zero_1(frame + 28);
    read_available_packet_bytes(reader_2, frame + 8, 0x00000015u);
    read_packet_bytes_with_diagnostic(reader_2, frame + 4, 0x00000001u);
    const uint32_t value_10 = read_1(frame + 4);
    read_available_packet_bytes(reader_2, frame + 32, value_10);
    auto* receiver_12 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_13 = read_4(receiver_12);
    const uint32_t value_14 = read_4(frame + 4);
    const uint32_t call_words[7] = {0x00000000u,
                                    0x00000000u,
                                    0x00000001u,
                                    reinterpret_cast<uint32_t>(frame + 8),
                                    value_14,
                                    reinterpret_cast<uint32_t>(frame + 32),
                                    reinterpret_cast<uint32_t>(frame + 8)};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 20(%%eax)\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 24(%%eax),%%eax\n\tcall *0x2ec(%%edx)"
        : "=a"(result)
        : "m"(receiver_12), "m"(table_13), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005932d0(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $160,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _aligned_005932d0\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x00593360..0x005933ed; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t aligned_00593360(const void* actual_arguments,
                                                               uint8_t* frame) {
    zero_4(frame + 8);
    zero_4(frame + 12);
    auto* reader_2 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    zero_4(frame + 16);
    zero_4(frame + 20);
    zero_4(frame + 24);
    clear(frame + 32, 32);
    zero_1(frame + 28);
    read_available_packet_bytes(reader_2, frame + 8, 0x00000015u);
    read_packet_bytes_with_diagnostic(reader_2, frame + 4, 0x00000001u);
    const uint32_t value_10 = read_1(frame + 4);
    read_available_packet_bytes(reader_2, frame + 32, value_10);
    auto* receiver_12 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_13 = read_4(receiver_12);
    const uint32_t value_14 = read_4(frame + 4);
    const uint32_t call_words[7] = {0x00000000u,
                                    0x00000000u,
                                    0x00000002u,
                                    reinterpret_cast<uint32_t>(frame + 8),
                                    value_14,
                                    reinterpret_cast<uint32_t>(frame + 32),
                                    reinterpret_cast<uint32_t>(frame + 8)};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 20(%%eax)\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 24(%%eax),%%eax\n\tcall *0x2ec(%%edx)"
        : "=a"(result)
        : "m"(receiver_12), "m"(table_13), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593360(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $160,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _aligned_00593360\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x005933f0..0x00593463; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t aligned_005933f0(const void* actual_arguments,
                                                               uint8_t* frame) {
    auto* reader_0 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    clear(frame + 8, 32);
    read_packet_bytes_with_diagnostic(reader_0, frame + 4, 0x00000004u);
    read_packet_bytes_with_diagnostic(reader_0, frame + 0, 0x00000001u);
    const uint32_t value_4 = read_1(frame + 0);
    read_available_packet_bytes(reader_0, frame + 8, value_4);
    auto* receiver_6 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_7 = read_4(receiver_6);
    const uint32_t value_8 = read_4(frame + 0);
    const uint32_t value_9 = read_4(frame + 4);
    const uint32_t call_words[6] = {
        0x00000000u, 0x00000001u, value_9, value_8, reinterpret_cast<uint32_t>(frame + 8), value_9};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 20(%%eax),%%eax\n\tcall *0x2e8(%%edx)"
        : "=a"(result)
        : "m"(receiver_6), "m"(table_7), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005933f0(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $136,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _aligned_005933f0\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x005934a0..0x0059350f; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t aligned_005934a0(const void* actual_arguments,
                                                               uint8_t* frame) {
    auto* reader_0 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    clear(frame + 8, 32);
    read_packet_bytes_with_diagnostic(reader_0, frame + 4, 0x00000004u);
    read_packet_bytes_with_diagnostic(reader_0, frame + 0, 0x00000001u);
    const uint32_t value_4 = read_1(frame + 0);
    read_available_packet_bytes(reader_0, frame + 8, value_4);
    auto* receiver_6 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_7 = read_4(receiver_6);
    const uint32_t value_8 = read_4(frame + 0);
    const uint32_t value_9 = read_4(frame + 4);
    const uint32_t call_words[4] = {value_9, value_8, reinterpret_cast<uint32_t>(frame + 8),
                                    value_9};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 12(%%eax),%%eax\n\tcall *0x300(%%edx)"
        : "=a"(result)
        : "m"(receiver_6), "m"(table_7), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005934a0(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $136,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _aligned_005934a0\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x00593510..0x0059359d; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t aligned_00593510(const void* actual_arguments,
                                                               uint8_t* frame) {
    zero_4(frame + 8);
    zero_4(frame + 12);
    auto* reader_2 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    zero_4(frame + 16);
    zero_4(frame + 20);
    zero_4(frame + 24);
    clear(frame + 32, 32);
    zero_1(frame + 28);
    read_available_packet_bytes(reader_2, frame + 8, 0x00000015u);
    read_packet_bytes_with_diagnostic(reader_2, frame + 4, 0x00000001u);
    const uint32_t value_10 = read_1(frame + 4);
    read_available_packet_bytes(reader_2, frame + 32, value_10);
    auto* receiver_12 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_13 = read_4(receiver_12);
    const uint32_t value_14 = read_4(frame + 4);
    const uint32_t call_words[7] = {0x00000000u,
                                    0x00000000u,
                                    0x00000003u,
                                    reinterpret_cast<uint32_t>(frame + 8),
                                    value_14,
                                    reinterpret_cast<uint32_t>(frame + 32),
                                    reinterpret_cast<uint32_t>(frame + 8)};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 20(%%eax)\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 24(%%eax),%%eax\n\tcall *0x2ec(%%edx)"
        : "=a"(result)
        : "m"(receiver_12), "m"(table_13), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593510(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $160,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _aligned_00593510\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x00593700..0x00593787; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t aligned_00593700(const void* actual_arguments,
                                                               uint8_t* frame) {
    zero_4(frame + 8);
    zero_4(frame + 12);
    auto* reader_2 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    zero_4(frame + 16);
    zero_4(frame + 20);
    zero_4(frame + 24);
    clear(frame + 32, 32);
    zero_1(frame + 28);
    read_available_packet_bytes(reader_2, frame + 8, 0x00000015u);
    read_packet_bytes_with_diagnostic(reader_2, frame + 4, 0x00000001u);
    const uint32_t value_10 = read_1(frame + 4);
    read_available_packet_bytes(reader_2, frame + 32, value_10);
    auto* receiver_12 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_13 = read_4(receiver_12);
    const uint32_t value_14 = read_4(frame + 4);
    const uint32_t call_words[4] = {reinterpret_cast<uint32_t>(frame + 8), value_14,
                                    reinterpret_cast<uint32_t>(frame + 32),
                                    reinterpret_cast<uint32_t>(frame + 8)};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 12(%%eax),%%eax\n\tcall *0x304(%%edx)"
        : "=a"(result)
        : "m"(receiver_12), "m"(table_13), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593700(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $160,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _aligned_00593700\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x00593790..0x00593803; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t aligned_00593790(const void* actual_arguments,
                                                               uint8_t* frame) {
    auto* reader_0 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    clear(frame + 8, 32);
    read_packet_bytes_with_diagnostic(reader_0, frame + 4, 0x00000004u);
    read_packet_bytes_with_diagnostic(reader_0, frame + 0, 0x00000001u);
    const uint32_t value_4 = read_1(frame + 0);
    read_available_packet_bytes(reader_0, frame + 8, value_4);
    auto* receiver_6 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_7 = read_4(receiver_6);
    const uint32_t value_8 = read_4(frame + 0);
    const uint32_t value_9 = read_4(frame + 4);
    const uint32_t call_words[6] = {
        0x00000001u, 0x00000000u, value_9, value_8, reinterpret_cast<uint32_t>(frame + 8), value_9};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 20(%%eax),%%eax\n\tcall *0x2e8(%%edx)"
        : "=a"(result)
        : "m"(receiver_6), "m"(table_7), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593790(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $136,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _aligned_00593790\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x00593810..0x005938ae; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t aligned_00593810(const void* actual_arguments,
                                                               uint8_t* frame) {
    zero_4(frame + 8);
    zero_4(frame + 12);
    auto* reader_2 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    zero_4(frame + 16);
    zero_4(frame + 20);
    zero_4(frame + 24);
    clear(frame + 32, 32);
    zero_1(frame + 28);
    read_packet_bytes_with_diagnostic(reader_2, frame + 4, 0x00000001u);
    read_available_packet_bytes(reader_2, frame + 8, 0x00000015u);
    read_packet_bytes_with_diagnostic(reader_2, frame + 0, 0x00000001u);
    const uint32_t value_11 = read_1(frame + 0);
    read_available_packet_bytes(reader_2, frame + 32, value_11);
    auto* receiver_13 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_14 = read_4(receiver_13);
    const uint32_t value_15 = read_4(frame + 0);
    const uint32_t value_16 = read_4(frame + 4);
    const uint32_t call_words[7] = {value_16,    0x00000001u,
                                    0x00000000u, reinterpret_cast<uint32_t>(frame + 8),
                                    value_15,    reinterpret_cast<uint32_t>(frame + 32),
                                    value_16};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 20(%%edx)\n\tpushl 16(%%edx)\n\tpushl 12(%%edx)\n\tpushl 8(%%edx)\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 24(%%edx),%%edx\n\tcall *0x2ec(%%eax)"
        : "=a"(result)
        : "m"(receiver_13), "m"(table_14), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593810(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $160,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _aligned_00593810\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x005938b0..0x0059393d; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t aligned_005938b0(const void* actual_arguments,
                                                               uint8_t* frame) {
    zero_4(frame + 8);
    zero_4(frame + 12);
    auto* reader_2 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    zero_4(frame + 16);
    zero_4(frame + 20);
    zero_4(frame + 24);
    clear(frame + 32, 32);
    zero_1(frame + 28);
    read_available_packet_bytes(reader_2, frame + 8, 0x00000015u);
    read_packet_bytes_with_diagnostic(reader_2, frame + 4, 0x00000001u);
    const uint32_t value_10 = read_1(frame + 4);
    read_available_packet_bytes(reader_2, frame + 32, value_10);
    auto* receiver_12 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_13 = read_4(receiver_12);
    const uint32_t value_14 = read_4(frame + 4);
    const uint32_t call_words[7] = {0x00000000u,
                                    0x00000001u,
                                    0x00000001u,
                                    reinterpret_cast<uint32_t>(frame + 8),
                                    value_14,
                                    reinterpret_cast<uint32_t>(frame + 32),
                                    reinterpret_cast<uint32_t>(frame + 8)};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 20(%%eax)\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 24(%%eax),%%eax\n\tcall *0x2ec(%%edx)"
        : "=a"(result)
        : "m"(receiver_12), "m"(table_13), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005938b0(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $160,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _aligned_005938b0\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x00593940..0x005939cd; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t aligned_00593940(const void* actual_arguments,
                                                               uint8_t* frame) {
    zero_4(frame + 8);
    zero_4(frame + 12);
    auto* reader_2 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    zero_4(frame + 16);
    zero_4(frame + 20);
    zero_4(frame + 24);
    clear(frame + 32, 32);
    zero_1(frame + 28);
    read_available_packet_bytes(reader_2, frame + 8, 0x00000015u);
    read_packet_bytes_with_diagnostic(reader_2, frame + 4, 0x00000001u);
    const uint32_t value_10 = read_1(frame + 4);
    read_available_packet_bytes(reader_2, frame + 32, value_10);
    auto* receiver_12 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_13 = read_4(receiver_12);
    const uint32_t value_14 = read_4(frame + 4);
    const uint32_t call_words[7] = {0x00000000u,
                                    0x00000001u,
                                    0x00000002u,
                                    reinterpret_cast<uint32_t>(frame + 8),
                                    value_14,
                                    reinterpret_cast<uint32_t>(frame + 32),
                                    reinterpret_cast<uint32_t>(frame + 8)};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 20(%%eax)\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 24(%%eax),%%eax\n\tcall *0x2ec(%%edx)"
        : "=a"(result)
        : "m"(receiver_12), "m"(table_13), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593940(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $160,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _aligned_00593940\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x005939d0..0x00593a43; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t aligned_005939d0(const void* actual_arguments,
                                                               uint8_t* frame) {
    auto* reader_0 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    clear(frame + 8, 32);
    read_packet_bytes_with_diagnostic(reader_0, frame + 4, 0x00000004u);
    read_packet_bytes_with_diagnostic(reader_0, frame + 0, 0x00000001u);
    const uint32_t value_4 = read_1(frame + 0);
    read_available_packet_bytes(reader_0, frame + 8, value_4);
    auto* receiver_6 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_7 = read_4(receiver_6);
    const uint32_t value_8 = read_4(frame + 0);
    const uint32_t value_9 = read_4(frame + 4);
    const uint32_t call_words[6] = {
        0x00000001u, 0x00000001u, value_9, value_8, reinterpret_cast<uint32_t>(frame + 8), value_9};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 16(%%eax)\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 20(%%eax),%%eax\n\tcall *0x2e8(%%edx)"
        : "=a"(result)
        : "m"(receiver_6), "m"(table_7), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005939d0(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $136,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _aligned_005939d0\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x00596310..0x00596375; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t aligned_00596310(const void* actual_arguments,
                                                               uint8_t* frame) {
    auto* reader_0 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    clear(frame + 8, 256);
    read_packet_bytes_with_diagnostic(reader_0, frame + 4, 0x00000004u);
    read_packet_bytes_with_diagnostic(reader_0, frame + 3, 0x00000001u);
    const uint32_t value_4 = read_1(frame + 3);
    read_available_packet_bytes(reader_0, frame + 8, value_4);
    auto* receiver_6 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_7 = read_4(receiver_6);
    const uint32_t call_words[2] = {reinterpret_cast<uint32_t>(frame + 8),
                                    reinterpret_cast<uint32_t>(frame + 8)};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 0(%%eax)\n\tmovl 4(%%eax),%%eax\n\tcall *0x53c(%%edx)"
        : "=a"(result)
        : "m"(receiver_6), "m"(table_7), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00596310(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $1032,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _aligned_00596310\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}
