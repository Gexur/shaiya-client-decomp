#include "packet_triples.h"

namespace {
inline uint32_t read_word(const void* p) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(p) : "memory");
    return value;
}
} // namespace

// Original 0x0058eed0..0x0058ef24; reads 1,4,4; virtualslot 0x90.
extern "C" __attribute__((noinline)) uint32_t triple_0058eed0(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x90(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_0058eed0(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_0058eed0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x0058f200..0x0058f254; reads 4,4,4; virtualslot 0xbc.
extern "C" __attribute__((noinline)) uint32_t triple_0058f200(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0xbc(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_0058f200(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_0058f200\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x0058f490..0x0058f4e4; reads 1,1,1; virtualslot 0xdc.
extern "C" __attribute__((noinline)) uint32_t triple_0058f490(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0xdc(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_0058f490(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_0058f490\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x0058f5b0..0x0058f604; reads 1,1,4; virtualslot 0x124.
extern "C" __attribute__((noinline)) uint32_t triple_0058f5b0(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x124(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_0058f5b0(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_0058f5b0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x0058f760..0x0058f7b4; reads 4,1,4; virtualslot 0xec.
extern "C" __attribute__((noinline)) uint32_t triple_0058f760(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0xec(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_0058f760(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_0058f760\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x0058fcd0..0x0058fd24; reads 4,1,4; virtualslot 0x12c.
extern "C" __attribute__((noinline)) uint32_t triple_0058fcd0(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x12c(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_0058fcd0(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_0058fcd0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x0058fd80..0x0058fdd4; reads 4,2,1; virtualslot 0x138.
extern "C" __attribute__((noinline)) uint32_t triple_0058fd80(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x138(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_0058fd80(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_0058fd80\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x0058ffd0..0x00590024; reads 4,2,1; virtualslot 0x14c.
extern "C" __attribute__((noinline)) uint32_t triple_0058ffd0(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x14c(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_0058ffd0(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_0058ffd0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00590d30..0x00590d84; reads 4,1,4; virtualslot 0x1a4.
extern "C" __attribute__((noinline)) uint32_t triple_00590d30(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x1a4(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_00590d30(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_00590d30\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00590d90..0x00590de4; reads 4,4,4; virtualslot 0x1a8.
extern "C" __attribute__((noinline)) uint32_t triple_00590d90(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x1a8(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_00590d90(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_00590d90\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00591a30..0x00591a84; reads 4,1,1; virtualslot 0x1ec.
extern "C" __attribute__((noinline)) uint32_t triple_00591a30(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x1ec(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_00591a30(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_00591a30\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00591a90..0x00591ae4; reads 4,1,1; virtualslot 0x1f0.
extern "C" __attribute__((noinline)) uint32_t triple_00591a90(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x1f0(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_00591a90(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_00591a90\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00591ce0..0x00591d34; reads 2,1,1; virtualslot 0x204.
extern "C" __attribute__((noinline)) uint32_t triple_00591ce0(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x204(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_00591ce0(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_00591ce0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00592c30..0x00592c84; reads 4,4,4; virtualslot 0x298.
extern "C" __attribute__((noinline)) uint32_t triple_00592c30(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x298(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_00592c30(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_00592c30\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00594dd0..0x00594e24; reads 2,1,1; virtualslot 0x420.
extern "C" __attribute__((noinline)) uint32_t triple_00594dd0(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x420(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_00594dd0(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_00594dd0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00594e30..0x00594e84; reads 2,1,1; virtualslot 0x424.
extern "C" __attribute__((noinline)) uint32_t triple_00594e30(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x424(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_00594e30(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_00594e30\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00594ec0..0x00594f14; reads 1,4,4; virtualslot 0x42c.
extern "C" __attribute__((noinline)) uint32_t triple_00594ec0(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x42c(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_00594ec0(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_00594ec0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00595000..0x00595054; reads 1,1,4; virtualslot 0x440.
extern "C" __attribute__((noinline)) uint32_t triple_00595000(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x440(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_00595000(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_00595000\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00595090..0x005950e4; reads 4,4,4; virtualslot 0x450.
extern "C" __attribute__((noinline)) uint32_t triple_00595090(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x450(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_00595090(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_00595090\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00595930..0x00595984; reads 1,1,4; virtualslot 0x4bc.
extern "C" __attribute__((noinline)) uint32_t triple_00595930(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x4bc(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_00595930(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_00595930\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00596020..0x00596074; reads 4,4,4; virtualslot 0x50c.
extern "C" __attribute__((noinline)) uint32_t triple_00596020(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x50c(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_00596020(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_00596020\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00596a40..0x00596a94; reads 1,1,1; virtualslot 0x57c.
extern "C" __attribute__((noinline)) uint32_t triple_00596a40(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x57c(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_00596a40(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_00596a40\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00596b30..0x00596b84; reads 1,1,1; virtualslot 0x594.
extern "C" __attribute__((noinline)) uint32_t triple_00596b30(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x594(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_00596b30(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_00596b30\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}

// Original 0x00597640..0x00597694; reads 4,4,4; virtualslot 0x5fc.
extern "C" __attribute__((noinline)) uint32_t triple_00597640(const void* actual_arguments,
                                                              uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t third = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t second = read_word(scratch + 4);
    const uint32_t first = read_word(scratch + 8);
    const uint32_t call_words[3] = {third, second, first};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\t"
        "pushl (%%edx)\n\tpushl 4(%%edx)\n\tmovl 8(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x5fc(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
// Original three payloadDWORDs retain inherited bytes at entryESP-12/-8/-4.
extern "C" __attribute__((naked)) void fun_00597640(PacketReader*) {
    __asm__ volatile("subl $12,%esp\n\tpushl %esi\n\tleal 20(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _triple_00597640\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $12,%esp\n\tret");
}
