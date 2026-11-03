#include "packet_text.h"
namespace {
uint32_t word(const void* p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
uint32_t count_byte(const void* p) {
    uint32_t v;
    __asm__ volatile("movzbl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
uint32_t count_word(const void* p) {
    uint32_t v;
    __asm__ volatile("movzwl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void clear(void* p, uint32_t count) {
    uint32_t value = 0;
    __asm__ volatile("rep stosl" : "+D"(p), "+c"(count) : "a"(value) : "memory");
}
} // namespace

// Complete original 0x00593a50..0x00593aac.
extern "C" __attribute__((noinline)) uint32_t text_00593a50(const void* actual_arguments,
                                                            uint8_t* frame) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    clear(frame + 8, 500);
    read_packet_bytes_with_diagnostic(reader, frame + 4, 2);
    const uint32_t length = count_word(frame + 4);
    read_available_packet_bytes(reader, frame + 8, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value0 = reinterpret_cast<uint32_t>(frame + 8);
    const uint32_t value1 = word(frame + 4);
    const uint32_t call_words[3] = {value1, value0, value1};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 4(%%edx)\n\tpushl 0(%%edx)\n\tmovl 8(%%edx),%%edx\n\tcall *0x2f4(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593a50(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $2008,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _text_00593a50\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x00593be0..0x00593c37.
extern "C" __attribute__((noinline)) uint32_t text_00593be0(const void* actual_arguments,
                                                            uint8_t* frame) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    clear(frame + 8, 256);
    read_packet_bytes_with_diagnostic(reader, frame + 7, 1);
    const uint32_t length = count_byte(frame + 7);
    read_available_packet_bytes(reader, frame + 8, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value0 = reinterpret_cast<uint32_t>(frame + 8);
    const uint32_t call_words[2] = {value0, value0};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 0(%%edx)\n\tmovl 4(%%edx),%%edx\n\tcall *0x320(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00593be0(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $1032,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _text_00593be0\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x00594150..0x005941a7.
extern "C" __attribute__((noinline)) uint32_t text_00594150(const void* actual_arguments,
                                                            uint8_t* frame) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    clear(frame + 8, 256);
    read_packet_bytes_with_diagnostic(reader, frame + 7, 1);
    const uint32_t length = count_byte(frame + 7);
    read_available_packet_bytes(reader, frame + 8, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value0 = reinterpret_cast<uint32_t>(frame + 8);
    const uint32_t call_words[2] = {value0, value0};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 0(%%edx)\n\tmovl 4(%%edx),%%edx\n\tcall *0x35c(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00594150(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $1032,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _text_00594150\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x005941b0..0x00594207.
extern "C" __attribute__((noinline)) uint32_t text_005941b0(const void* actual_arguments,
                                                            uint8_t* frame) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    clear(frame + 8, 256);
    read_packet_bytes_with_diagnostic(reader, frame + 7, 1);
    const uint32_t length = count_byte(frame + 7);
    read_available_packet_bytes(reader, frame + 8, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value0 = reinterpret_cast<uint32_t>(frame + 8);
    const uint32_t call_words[2] = {value0, value0};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 0(%%edx)\n\tmovl 4(%%edx),%%edx\n\tcall *0x360(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005941b0(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $1032,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _text_005941b0\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x00594210..0x00594267.
extern "C" __attribute__((noinline)) uint32_t text_00594210(const void* actual_arguments,
                                                            uint8_t* frame) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    clear(frame + 8, 256);
    read_packet_bytes_with_diagnostic(reader, frame + 7, 1);
    const uint32_t length = count_byte(frame + 7);
    read_available_packet_bytes(reader, frame + 8, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value0 = reinterpret_cast<uint32_t>(frame + 8);
    const uint32_t call_words[2] = {value0, value0};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 0(%%edx)\n\tmovl 4(%%edx),%%edx\n\tcall *0x364(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00594210(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $1032,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _text_00594210\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x00594270..0x005942c7.
extern "C" __attribute__((noinline)) uint32_t text_00594270(const void* actual_arguments,
                                                            uint8_t* frame) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    clear(frame + 8, 256);
    read_packet_bytes_with_diagnostic(reader, frame + 7, 1);
    const uint32_t length = count_byte(frame + 7);
    read_available_packet_bytes(reader, frame + 8, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value0 = reinterpret_cast<uint32_t>(frame + 8);
    const uint32_t call_words[2] = {value0, value0};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 0(%%edx)\n\tmovl 4(%%edx),%%edx\n\tcall *0x368(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00594270(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $1032,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _text_00594270\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x005942d0..0x00594327.
extern "C" __attribute__((noinline)) uint32_t text_005942d0(const void* actual_arguments,
                                                            uint8_t* frame) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    clear(frame + 8, 256);
    read_packet_bytes_with_diagnostic(reader, frame + 7, 1);
    const uint32_t length = count_byte(frame + 7);
    read_available_packet_bytes(reader, frame + 8, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value0 = reinterpret_cast<uint32_t>(frame + 8);
    const uint32_t call_words[2] = {value0, value0};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 0(%%edx)\n\tmovl 4(%%edx),%%edx\n\tcall *0x36c(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005942d0(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $1032,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _text_005942d0\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x00594330..0x00594387.
extern "C" __attribute__((noinline)) uint32_t text_00594330(const void* actual_arguments,
                                                            uint8_t* frame) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    clear(frame + 8, 256);
    read_packet_bytes_with_diagnostic(reader, frame + 7, 1);
    const uint32_t length = count_byte(frame + 7);
    read_available_packet_bytes(reader, frame + 8, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value0 = reinterpret_cast<uint32_t>(frame + 8);
    const uint32_t call_words[2] = {value0, value0};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 0(%%edx)\n\tmovl 4(%%edx),%%edx\n\tcall *0x370(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00594330(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $1032,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _text_00594330\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}

// Complete original 0x00594560..0x005945b7.
extern "C" __attribute__((noinline)) uint32_t text_00594560(const void* actual_arguments,
                                                            uint8_t* frame) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    clear(frame + 8, 64);
    read_packet_bytes_with_diagnostic(reader, frame + 7, 1);
    const uint32_t length = count_byte(frame + 7);
    read_available_packet_bytes(reader, frame + 8, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t value0 = reinterpret_cast<uint32_t>(frame + 8);
    const uint32_t call_words[2] = {value0, value0};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %3,%%edx\n\tmovl %2,%%eax\n\tpushl 0(%%edx)\n\tmovl 4(%%edx),%%edx\n\tcall *0x3a8(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "r"(call_words)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00594560(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $264,%esp\n\tpushl %esi\n\tpushl %edi\n\tleal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcall _text_00594560\n\taddl $8,%esp\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret");
}
