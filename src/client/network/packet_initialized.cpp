#include "packet_initialized.h"
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
void zero_2(void* p) {
    __asm__ volatile("movw $0,(%0)" ::"r"(p) : "memory");
}
void zero_1(void* p) {
    __asm__ volatile("movb $0,(%0)" ::"r"(p) : "memory");
}
void clear(void* p, uint32_t count) {
    uint32_t value = 0;
    __asm__ volatile("rep stosl" : "+D"(p), "+c"(count) : "a"(value) : "memory");
}
} // namespace

// Complete original 0x005911e0..0x0059132c; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t initialized_005911e0(const void* actual_arguments,
                                                                   uint8_t* frame) {
    zero_4(frame + 4);
    zero_4(frame + 8);
    zero_4(frame + 12);
    zero_4(frame + 16);
    zero_4(frame + 20);
    auto* reader_5 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    zero_4(frame + 24);
    zero_4(frame + 28);
    zero_4(frame + 32);
    zero_2(frame + 36);
    read_packet_bytes_with_diagnostic(reader_5, frame + 0, 0x00000001u);
    read_packet_bytes_with_diagnostic(reader_5, frame + 4, 0x00000001u);
    read_packet_bytes_with_diagnostic(reader_5, frame + 5, 0x00000001u);
    read_packet_bytes_with_diagnostic(reader_5, frame + 6, 0x00000001u);
    read_packet_bytes_with_diagnostic(reader_5, frame + 7, 0x00000001u);
    read_packet_bytes_with_diagnostic(reader_5, frame + 8, 0x00000002u);
    read_packet_bytes_with_diagnostic(reader_5, frame + 10, 0x00000001u);
    read_packet_bytes_with_diagnostic(reader_5, frame + 11, 0x00000001u);
    read_packet_bytes_with_diagnostic(reader_5, frame + 12, 0x00000001u);
    read_packet_bytes_with_diagnostic(reader_5, frame + 13, 0x00000001u);
    read_packet_bytes_with_diagnostic(reader_5, frame + 14, 0x00000001u);
    read_packet_bytes_with_diagnostic(reader_5, frame + 15, 0x00000001u);
    read_packet_bytes_with_diagnostic(reader_5, frame + 16, 0x00000001u);
    read_available_packet_bytes(reader_5, frame + 17, 0x00000015u);
    const uint32_t value_24 = read_4(frame + 16);
    const uint32_t value_25 = read_4(frame + 15);
    const uint32_t value_26 = read_4(frame + 14);
    const uint32_t value_27 = read_4(frame + 13);
    const uint32_t value_28 = read_4(frame + 12);
    const uint32_t value_29 = read_4(frame + 11);
    auto* receiver_30 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t value_31 = read_4(frame + 10);
    const uint32_t table_32 = read_4(receiver_30);
    const uint32_t value_33 = read_4(frame + 8);
    const uint32_t value_34 = read_4(frame + 7);
    const uint32_t value_35 = read_4(frame + 6);
    const uint32_t value_36 = read_4(frame + 5);
    const uint32_t value_37 = read_4(frame + 4);
    const uint32_t value_38 = read_4(frame + 0);
    const uint32_t call_words[15] = {value_38, value_37,
                                     value_36, value_35,
                                     value_34, value_33,
                                     value_31, value_29,
                                     value_28, value_27,
                                     value_26, value_25,
                                     value_24, reinterpret_cast<uint32_t>(frame + 17),
                                     value_38};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 52(%%edx)\n\tpushl 48(%%edx)\n\tpushl 44(%%edx)\n\tpushl 40(%%edx)\n\tpushl 36(%%edx)\n\tpushl 32(%%edx)\n\tpushl 28(%%edx)\n\tpushl 24(%%edx)\n\tpushl 20(%%edx)\n\tpushl 16(%%edx)\n\tpushl 12(%%edx)\n\tpushl 8(%%edx)\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 56(%%edx),%%edx\n\tcall *0x1d8(%%eax)"
        : "=a"(result)
        : "m"(receiver_30), "m"(table_32), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005911e0(PacketReader*) {
    __asm__ volatile(
        "subl $40,%esp\n\tpushl %esi\n\tleal 4(%esp),%edx\n\tleal 48(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _initialized_005911e0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $40,%esp\n\tret");
}

// Complete original 0x00593640..0x0059368b; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t initialized_00593640(const void* actual_arguments,
                                                                   uint8_t* frame) {
    auto* reader_0 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    zero_4(frame + 4);
    zero_4(frame + 0);
    read_packet_bytes_with_diagnostic(reader_0, frame + 4, 0x00000004u);
    read_packet_bytes_with_diagnostic(reader_0, frame + 0, 0x00000002u);
    const uint32_t value_5 = read_4(frame + 0);
    auto* receiver_6 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_7 = read_4(receiver_6);
    const uint32_t value_8 = read_4(frame + 4);
    const uint32_t call_words[3] = {value_8, value_5, value_8};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 8(%%eax),%%eax\n\tcall *0x308(%%edx)"
        : "=a"(result)
        : "m"(receiver_6), "m"(table_7), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593640(PacketReader*) {
    __asm__ volatile(
        "subl $8,%esp\n\tpushl %esi\n\tleal 4(%esp),%edx\n\tleal 16(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _initialized_00593640\n\taddl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Complete original 0x00593690..0x00593700; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t initialized_00593690(const void* actual_arguments,
                                                                   uint8_t* frame) {
    auto* reader_0 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    zero_4(frame + 0);
    read_packet_bytes_with_diagnostic(reader_0, frame + 0, 0x00000004u);
    zero_4(frame + 4);
    zero_4(frame + 8);
    zero_4(frame + 12);
    zero_4(frame + 16);
    zero_4(frame + 20);
    zero_4(frame + 24);
    zero_4(frame + 28);
    zero_4(frame + 32);
    read_available_packet_bytes(reader_0, frame + 4, 0x00000020u);
    auto* receiver_12 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t value_13 = read_4(frame + 0);
    zero_1(frame + 35);
    const uint32_t table_15 = read_4(receiver_12);
    const uint32_t call_words[3] = {value_13, reinterpret_cast<uint32_t>(frame + 4), value_13};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 8(%%edx),%%edx\n\tcall *0x30c(%%eax)"
        : "=a"(result)
        : "m"(receiver_12), "m"(table_15), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593690(PacketReader*) {
    __asm__ volatile(
        "subl $36,%esp\n\tpushl %esi\n\tleal 4(%esp),%edx\n\tleal 44(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _initialized_00593690\n\taddl $8,%esp\n\tpopl %esi\n\taddl $36,%esp\n\tret");
}

// Complete original 0x005945c0..0x0059461f; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t initialized_005945c0(const void* actual_arguments,
                                                                   uint8_t* frame) {
    zero_4(frame + 4);
    zero_4(frame + 8);
    zero_4(frame + 12);
    auto* reader_3 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    zero_4(frame + 16);
    zero_4(frame + 20);
    zero_4(frame + 24);
    zero_1(frame + 28);
    read_packet_bytes_with_diagnostic(reader_3, frame + 0, 0x00000004u);
    read_available_packet_bytes(reader_3, frame + 4, 0x00000019u);
    auto* receiver_10 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_11 = read_4(receiver_10);
    const uint32_t value_12 = read_4(frame + 0);
    const uint32_t call_words[3] = {value_12, reinterpret_cast<uint32_t>(frame + 4), value_12};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 8(%%edx),%%edx\n\tcall *0x3b0(%%eax)"
        : "=a"(result)
        : "m"(receiver_10), "m"(table_11), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005945c0(PacketReader*) {
    __asm__ volatile(
        "subl $32,%esp\n\tpushl %esi\n\tleal 4(%esp),%edx\n\tleal 40(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _initialized_005945c0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $32,%esp\n\tret");
}

// Complete original 0x00594620..0x005946a5; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t initialized_00594620(const void* actual_arguments,
                                                                   uint8_t* frame) {
    zero_4(frame + 12);
    zero_4(frame + 16);
    zero_4(frame + 20);
    auto* reader_3 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    zero_4(frame + 24);
    zero_4(frame + 28);
    zero_4(frame + 32);
    zero_1(frame + 36);
    read_packet_bytes_with_diagnostic(reader_3, frame + 8, 0x00000001u);
    read_packet_bytes_with_diagnostic(reader_3, frame + 4, 0x00000004u);
    read_packet_bytes_with_diagnostic(reader_3, frame + 0, 0x00000001u);
    read_available_packet_bytes(reader_3, frame + 12, 0x00000019u);
    auto* receiver_12 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_13 = read_4(receiver_12);
    const uint32_t value_14 = read_4(frame + 0);
    const uint32_t value_15 = read_4(frame + 4);
    const uint32_t value_16 = read_4(frame + 8);
    const uint32_t call_words[5] = {value_16, value_15, value_14,
                                    reinterpret_cast<uint32_t>(frame + 12), value_16};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 16(%%eax),%%eax\n\tcall *0x3b4(%%edx)"
        : "=a"(result)
        : "m"(receiver_12), "m"(table_13), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00594620(PacketReader*) {
    __asm__ volatile(
        "subl $40,%esp\n\tpushl %esi\n\tleal 4(%esp),%edx\n\tleal 48(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _initialized_00594620\n\taddl $8,%esp\n\tpopl %esi\n\taddl $40,%esp\n\tret");
}

// Complete original 0x005948b0..0x00594931; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t initialized_005948b0(const void* actual_arguments,
                                                                   uint8_t* frame) {
    zero_4(frame + 12);
    zero_4(frame + 16);
    auto* reader_2 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    zero_4(frame + 20);
    zero_4(frame + 24);
    zero_4(frame + 28);
    zero_1(frame + 32);
    read_packet_bytes_with_diagnostic(reader_2, frame + 8, 0x00000004u);
    read_packet_bytes_with_diagnostic(reader_2, frame + 4, 0x00000001u);
    read_packet_bytes_with_diagnostic(reader_2, frame + 0, 0x00000001u);
    read_available_packet_bytes(reader_2, frame + 12, 0x00000015u);
    auto* receiver_11 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_12 = read_4(receiver_11);
    const uint32_t value_13 = read_4(frame + 0);
    const uint32_t value_14 = read_4(frame + 4);
    const uint32_t value_15 = read_4(frame + 8);
    const uint32_t call_words[5] = {value_15, value_14, value_13,
                                    reinterpret_cast<uint32_t>(frame + 12), value_15};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 12(%%eax)\n\tpushl 8(%%eax)\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 16(%%eax),%%eax\n\tcall *0x3d8(%%edx)"
        : "=a"(result)
        : "m"(receiver_11), "m"(table_12), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005948b0(PacketReader*) {
    __asm__ volatile(
        "subl $36,%esp\n\tpushl %esi\n\tleal 4(%esp),%edx\n\tleal 44(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _initialized_005948b0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $36,%esp\n\tret");
}

// Complete original 0x00596d70..0x00596db9; literal original data flow.
extern "C" __attribute__((noinline)) uint32_t initialized_00596d70(const void* actual_arguments,
                                                                   uint8_t* frame) {
    auto* reader_0 = reinterpret_cast<PacketReader*>(read_4(actual_arguments));
    zero_4(frame + 0);
    read_packet_bytes_with_diagnostic(reader_0, frame + 4, 0x00000001u);
    read_packet_bytes_with_diagnostic(reader_0, frame + 0, 0x00000004u);
    const uint32_t value_4 = read_4(frame + 0);
    auto* receiver_5 = reinterpret_cast<SessionPrefix*>(read_4(&dat_0224a328));
    const uint32_t table_6 = read_4(receiver_5);
    const uint32_t value_7 = read_4(frame + 4);
    const uint32_t call_words[3] = {value_7, value_4, value_7};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%eax\n\tmovl %2,%%edx\n\tpushl 4(%%eax)\n\tpushl 0(%%eax)\n\tmovl 8(%%eax),%%eax\n\tcall *0x580(%%edx)"
        : "=a"(result)
        : "m"(receiver_5), "m"(table_6), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00596d70(PacketReader*) {
    __asm__ volatile(
        "subl $8,%esp\n\tpushl %esi\n\tleal 4(%esp),%edx\n\tleal 16(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _initialized_00596d70\n\taddl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}
