#include "packet_pairs.h"

namespace {
inline uint32_t read_word(const void* p) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(p) : "memory");
    return value;
}
} // namespace

// Original 0x0058e0e0..0x0058e11e; reads 1,1; virtualslot 0x34.
extern "C" __attribute__((noinline)) uint32_t pair_0058e0e0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x34(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_0058e0e0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_0058e0e0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x0058e120..0x0058e15e; reads 4,2; virtualslot 0x48.
extern "C" __attribute__((noinline)) uint32_t pair_0058e120(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 2);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x48(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_0058e120(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_0058e120\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x0058efe0..0x0058f021; reads 1,4; virtualslot 0xa0.
extern "C" __attribute__((noinline)) uint32_t pair_0058efe0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0xa0(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_0058efe0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_0058efe0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x0058f030..0x0058f071; reads 1,4; virtualslot 0xa4.
extern "C" __attribute__((noinline)) uint32_t pair_0058f030(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0xa4(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_0058f030(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_0058f030\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x0058f080..0x0058f0c1; reads 1,4; virtualslot 0xa8.
extern "C" __attribute__((noinline)) uint32_t pair_0058f080(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0xa8(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_0058f080(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_0058f080\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x0058f2d0..0x0058f311; reads 4,4; virtualslot 0xc4.
extern "C" __attribute__((noinline)) uint32_t pair_0058f2d0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0xc4(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_0058f2d0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_0058f2d0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x0058f410..0x0058f451; reads 1,1; virtualslot 0xd4.
extern "C" __attribute__((noinline)) uint32_t pair_0058f410(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0xd4(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_0058f410(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_0058f410\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x0058f830..0x0058f871; reads 4,1; virtualslot 0xf8.
extern "C" __attribute__((noinline)) uint32_t pair_0058f830(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0xf8(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_0058f830(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_0058f830\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x0058fd30..0x0058fd71; reads 4,4; virtualslot 0x130.
extern "C" __attribute__((noinline)) uint32_t pair_0058fd30(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x130(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_0058fd30(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_0058fd30\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00590700..0x00590741; reads 4,1; virtualslot 0x134.
extern "C" __attribute__((noinline)) uint32_t pair_00590700(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x134(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00590700(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00590700\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00590750..0x00590791; reads 4,4; virtualslot 0x178.
extern "C" __attribute__((noinline)) uint32_t pair_00590750(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x178(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00590750(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00590750\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00591bb0..0x00591bf1; reads 4,2; virtualslot 0x1fc.
extern "C" __attribute__((noinline)) uint32_t pair_00591bb0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 2);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x1fc(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00591bb0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00591bb0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00591e30..0x00591e6e; reads 1,4; virtualslot 0x54.
extern "C" __attribute__((noinline)) uint32_t pair_00591e30(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x54(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00591e30(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00591e30\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00591fe0..0x00592021; reads 4,1; virtualslot 0x21c.
extern "C" __attribute__((noinline)) uint32_t pair_00591fe0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x21c(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00591fe0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00591fe0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00592cc0..0x00592d01; reads 4,1; virtualslot 0x2a0.
extern "C" __attribute__((noinline)) uint32_t pair_00592cc0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x2a0(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00592cc0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00592cc0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00592d40..0x00592d81; reads 1,1; virtualslot 0x2a8.
extern "C" __attribute__((noinline)) uint32_t pair_00592d40(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x2a8(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00592d40(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00592d40\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00592d90..0x00592dd1; reads 1,1; virtualslot 0x2ac.
extern "C" __attribute__((noinline)) uint32_t pair_00592d90(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x2ac(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00592d90(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00592d90\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00592de0..0x00592e21; reads 1,1; virtualslot 0x2b8.
extern "C" __attribute__((noinline)) uint32_t pair_00592de0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x2b8(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00592de0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00592de0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00592e30..0x00592e71; reads 1,4; virtualslot 0x2bc.
extern "C" __attribute__((noinline)) uint32_t pair_00592e30(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x2bc(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00592e30(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00592e30\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00594480..0x005944c1; reads 1,4; virtualslot 0x394.
extern "C" __attribute__((noinline)) uint32_t pair_00594480(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x394(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00594480(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00594480\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00594740..0x00594781; reads 1,4; virtualslot 0x3c4.
extern "C" __attribute__((noinline)) uint32_t pair_00594740(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x3c4(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00594740(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00594740\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00594860..0x005948a1; reads 1,4; virtualslot 0x3d4.
extern "C" __attribute__((noinline)) uint32_t pair_00594860(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x3d4(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00594860(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00594860\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00594940..0x00594981; reads 1,4; virtualslot 0x3dc.
extern "C" __attribute__((noinline)) uint32_t pair_00594940(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x3dc(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00594940(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00594940\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00594d80..0x00594dc1; reads 4,1; virtualslot 0x41c.
extern "C" __attribute__((noinline)) uint32_t pair_00594d80(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x41c(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00594d80(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00594d80\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x005950f0..0x00595131; reads 4,4; virtualslot 0x454.
extern "C" __attribute__((noinline)) uint32_t pair_005950f0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x454(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_005950f0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_005950f0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00595350..0x00595391; reads 4,1; virtualslot 0x470.
extern "C" __attribute__((noinline)) uint32_t pair_00595350(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x470(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00595350(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00595350\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00595630..0x00595671; reads 1,4; virtualslot 0x490.
extern "C" __attribute__((noinline)) uint32_t pair_00595630(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x490(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00595630(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00595630\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x005958e0..0x00595921; reads 1,4; virtualslot 0x4b8.
extern "C" __attribute__((noinline)) uint32_t pair_005958e0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x4b8(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_005958e0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_005958e0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00595990..0x005959d1; reads 1,4; virtualslot 0x4c0.
extern "C" __attribute__((noinline)) uint32_t pair_00595990(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x4c0(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00595990(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00595990\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00595ba0..0x00595be1; reads 1,1; virtualslot 0x4d4.
extern "C" __attribute__((noinline)) uint32_t pair_00595ba0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x4d4(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00595ba0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00595ba0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00595bf0..0x00595c31; reads 1,1; virtualslot 0x4d8.
extern "C" __attribute__((noinline)) uint32_t pair_00595bf0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x4d8(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00595bf0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00595bf0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00595c70..0x00595cb1; reads 4,4; virtualslot 0x4e0.
extern "C" __attribute__((noinline)) uint32_t pair_00595c70(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x4e0(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00595c70(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00595c70\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00595d20..0x00595d61; reads 1,1; virtualslot 0xac.
extern "C" __attribute__((noinline)) uint32_t pair_00595d20(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0xac(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00595d20(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00595d20\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00595d70..0x00595db1; reads 1,1; virtualslot 0xb0.
extern "C" __attribute__((noinline)) uint32_t pair_00595d70(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0xb0(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00595d70(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00595d70\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00595dc0..0x00595e01; reads 1,4; virtualslot 0xb4.
extern "C" __attribute__((noinline)) uint32_t pair_00595dc0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0xb4(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00595dc0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00595dc0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00595e10..0x00595e51; reads 4,4; virtualslot 0x4ec.
extern "C" __attribute__((noinline)) uint32_t pair_00595e10(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x4ec(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00595e10(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00595e10\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00595e60..0x00595ea1; reads 1,4; virtualslot 0x4f0.
extern "C" __attribute__((noinline)) uint32_t pair_00595e60(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x4f0(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00595e60(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00595e60\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00595eb0..0x00595ef1; reads 4,4; virtualslot 0x4f4.
extern "C" __attribute__((noinline)) uint32_t pair_00595eb0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x4f4(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00595eb0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00595eb0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00595f30..0x00595f71; reads 1,4; virtualslot 0x500.
extern "C" __attribute__((noinline)) uint32_t pair_00595f30(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x500(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00595f30(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00595f30\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00595f80..0x00595fc1; reads 4,4; virtualslot 0x504.
extern "C" __attribute__((noinline)) uint32_t pair_00595f80(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x504(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00595f80(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00595f80\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00595fd0..0x00596011; reads 1,4; virtualslot 0x508.
extern "C" __attribute__((noinline)) uint32_t pair_00595fd0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x508(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00595fd0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00595fd0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x005960b0..0x005960f1; reads 1,4; virtualslot 0x518.
extern "C" __attribute__((noinline)) uint32_t pair_005960b0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x518(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_005960b0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_005960b0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00596100..0x00596141; reads 1,1; virtualslot 0x51c.
extern "C" __attribute__((noinline)) uint32_t pair_00596100(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x51c(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00596100(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00596100\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00596210..0x00596251; reads 4,1; virtualslot 0x528.
extern "C" __attribute__((noinline)) uint32_t pair_00596210(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x528(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00596210(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00596210\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00596290..0x005962d1; reads 4,1; virtualslot 0x534.
extern "C" __attribute__((noinline)) uint32_t pair_00596290(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x534(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00596290(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00596290\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00596f00..0x00596f41; reads 1,1; virtualslot 0x5a8.
extern "C" __attribute__((noinline)) uint32_t pair_00596f00(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x5a8(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00596f00(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00596f00\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00596f50..0x00596f91; reads 4,1; virtualslot 0x2c0.
extern "C" __attribute__((noinline)) uint32_t pair_00596f50(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x2c0(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00596f50(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00596f50\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x005976d0..0x00597711; reads 2,1; virtualslot 0x600.
extern "C" __attribute__((noinline)) uint32_t pair_005976d0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x600(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_005976d0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_005976d0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x005978f0..0x00597931; reads 1,4; virtualslot 0x5e8.
extern "C" __attribute__((noinline)) uint32_t pair_005978f0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x5e8(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_005978f0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_005978f0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x005979b0..0x005979f1; reads 1,1; virtualslot 0x5f4.
extern "C" __attribute__((noinline)) uint32_t pair_005979b0(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x5f4(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_005979b0(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_005979b0\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}

// Original 0x00597a30..0x00597a71; reads 1,1; virtualslot 0x5f8.
extern "C" __attribute__((noinline)) uint32_t pair_00597a30(const void* actual_arguments,
                                                            uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t second = read_word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t first = read_word(scratch + 4);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *0x5f8(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve original two payloadDWORDs at entryESP-8/-4; ESI save is below.
extern "C" __attribute__((naked)) void fun_00597a30(PacketReader*) {
    __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"
                     "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _pair_00597a30\n\t"
                     "addl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");
}
