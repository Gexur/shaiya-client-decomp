#include "packet_counted.h"

namespace {
uint32_t word(const void* p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
uint32_t byte(const void* p) {
    uint32_t v;
    __asm__ volatile("movzbl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
} // namespace

// Original 0x00591b50..0x00591ba1; count BYTE times7, original private1796 bytes.
extern "C" __attribute__((noinline)) uint32_t counted_00591b50(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t length = byte(scratch) * 7u;
    read_packet_bytes_with_diagnostic(reader, scratch + 4, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t count = word(scratch);
    uint8_t* data = scratch + 4;
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl %4\n\tpushl %%edx\n\tcall *0x1f4(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(count), "m"(data)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00591b50(PacketReader*) {
    __asm__ volatile(
        "subl $1796,%esp\n\tpushl %esi\n\tleal 1804(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _counted_00591b50\n\taddl $8,%esp\n\tpopl %esi\n\taddl $1796,%esp\n\tret");
}

// Original 0x00591d70..0x00591dc1; count BYTE times11, original private2820 bytes.
extern "C" __attribute__((noinline)) uint32_t counted_00591d70(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t length = byte(scratch) * 11u;
    read_packet_bytes_with_diagnostic(reader, scratch + 4, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t count = word(scratch);
    uint8_t* data = scratch + 4;
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl %4\n\tpushl %%edx\n\tcall *0x20c(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(count), "m"(data)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00591d70(PacketReader*) {
    __asm__ volatile(
        "subl $2820,%esp\n\tpushl %esi\n\tleal 2828(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _counted_00591d70\n\taddl $8,%esp\n\tpopl %esi\n\taddl $2820,%esp\n\tret");
}

// Original 0x00594990..0x005949e1; count BYTE times50, original private2004 bytes.
extern "C" __attribute__((noinline)) uint32_t counted_00594990(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t length = byte(scratch) * 50u;
    read_packet_bytes_with_diagnostic(reader, scratch + 4, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t count = word(scratch);
    uint8_t* data = scratch + 4;
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl %4\n\tpushl %%edx\n\tcall *0x3e8(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(count), "m"(data)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00594990(PacketReader*) {
    __asm__ volatile(
        "subl $2004,%esp\n\tpushl %esi\n\tleal 2012(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _counted_00594990\n\taddl $8,%esp\n\tpopl %esi\n\taddl $2004,%esp\n\tret");
}

// Original 0x00594a60..0x00594ab1; count BYTE times29, original private2324 bytes.
extern "C" __attribute__((noinline)) uint32_t counted_00594a60(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t length = byte(scratch) * 29u;
    read_packet_bytes_with_diagnostic(reader, scratch + 4, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t count = word(scratch);
    uint8_t* data = scratch + 4;
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl %4\n\tpushl %%edx\n\tcall *0x3f8(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(count), "m"(data)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00594a60(PacketReader*) {
    __asm__ volatile(
        "subl $2324,%esp\n\tpushl %esi\n\tleal 2332(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _counted_00594a60\n\taddl $8,%esp\n\tpopl %esi\n\taddl $2324,%esp\n\tret");
}

// Original 0x00594ac0..0x00594b11; count BYTE times29, original private2324 bytes.
extern "C" __attribute__((noinline)) uint32_t counted_00594ac0(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t length = byte(scratch) * 29u;
    read_packet_bytes_with_diagnostic(reader, scratch + 4, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t count = word(scratch);
    uint8_t* data = scratch + 4;
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl %4\n\tpushl %%edx\n\tcall *0x3f4(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(count), "m"(data)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00594ac0(PacketReader*) {
    __asm__ volatile(
        "subl $2324,%esp\n\tpushl %esi\n\tleal 2332(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _counted_00594ac0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $2324,%esp\n\tret");
}

// Original 0x00594b20..0x00594b71; count BYTE times29, original private2324 bytes.
extern "C" __attribute__((noinline)) uint32_t counted_00594b20(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t length = byte(scratch) * 29u;
    read_packet_bytes_with_diagnostic(reader, scratch + 4, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t count = word(scratch);
    uint8_t* data = scratch + 4;
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl %4\n\tpushl %%edx\n\tcall *0x3fc(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(count), "m"(data)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00594b20(PacketReader*) {
    __asm__ volatile(
        "subl $2324,%esp\n\tpushl %esi\n\tleal 2332(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _counted_00594b20\n\taddl $8,%esp\n\tpopl %esi\n\taddl $2324,%esp\n\tret");
}

// Original 0x00594c00..0x00594c51; count BYTE times28, original private2244 bytes.
extern "C" __attribute__((noinline)) uint32_t counted_00594c00(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t length = byte(scratch) * 28u;
    read_packet_bytes_with_diagnostic(reader, scratch + 4, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t count = word(scratch);
    uint8_t* data = scratch + 4;
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl %4\n\tpushl %%edx\n\tcall *0x408(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(count), "m"(data)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00594c00(PacketReader*) {
    __asm__ volatile(
        "subl $2244,%esp\n\tpushl %esi\n\tleal 2252(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _counted_00594c00\n\taddl $8,%esp\n\tpopl %esi\n\taddl $2244,%esp\n\tret");
}

// Original 0x00594d20..0x00594d71; count BYTE times13, original private1304 bytes.
extern "C" __attribute__((noinline)) uint32_t counted_00594d20(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t length = byte(scratch) * 13u;
    read_packet_bytes_with_diagnostic(reader, scratch + 4, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t count = word(scratch);
    uint8_t* data = scratch + 4;
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl %4\n\tpushl %%edx\n\tcall *0x418(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(count), "m"(data)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00594d20(PacketReader*) {
    __asm__ volatile(
        "subl $1304,%esp\n\tpushl %esi\n\tleal 1312(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _counted_00594d20\n\taddl $8,%esp\n\tpopl %esi\n\taddl $1304,%esp\n\tret");
}

// Original 0x005959e0..0x00595a31; count BYTE times37, original private744 bytes.
extern "C" __attribute__((noinline)) uint32_t counted_005959e0(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t length = byte(scratch) * 37u;
    read_packet_bytes_with_diagnostic(reader, scratch + 4, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t count = word(scratch);
    uint8_t* data = scratch + 4;
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl %4\n\tpushl %%edx\n\tcall *0x4c8(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(count), "m"(data)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005959e0(PacketReader*) {
    __asm__ volatile(
        "subl $744,%esp\n\tpushl %esi\n\tleal 752(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _counted_005959e0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $744,%esp\n\tret");
}

// Original 0x00597780..0x005977d0; count BYTE times2, original private484 bytes.
extern "C" __attribute__((noinline)) uint32_t counted_00597780(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t length = byte(scratch) * 2u;
    read_packet_bytes_with_diagnostic(reader, scratch + 4, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t count = word(scratch);
    uint8_t* data = scratch + 4;
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl %4\n\tpushl %%edx\n\tcall *0x5dc(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(count), "m"(data)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00597780(PacketReader*) {
    __asm__ volatile(
        "subl $484,%esp\n\tpushl %esi\n\tleal 492(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _counted_00597780\n\taddl $8,%esp\n\tpopl %esi\n\taddl $484,%esp\n\tret");
}

// Original 0x005977d0..0x00597821; count BYTE times4, original private132 bytes.
extern "C" __attribute__((noinline)) uint32_t counted_005977d0(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t length = byte(scratch) * 4u;
    read_packet_bytes_with_diagnostic(reader, scratch + 4, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t count = word(scratch);
    uint8_t* data = scratch + 4;
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl %4\n\tpushl %%edx\n\tcall *0x5d8(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(count), "m"(data)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_005977d0(PacketReader*) {
    __asm__ volatile(
        "subl $132,%esp\n\tpushl %esi\n\tleal 140(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _counted_005977d0\n\taddl $8,%esp\n\tpopl %esi\n\taddl $132,%esp\n\tret");
}

// Original 0x00597a80..0x00597ad1; count BYTE times9, original private364 bytes.
extern "C" __attribute__((noinline)) uint32_t counted_00597a80(const void* actual_arguments,
                                                               uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t length = byte(scratch) * 9u;
    read_packet_bytes_with_diagnostic(reader, scratch + 4, length);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t count = word(scratch);
    uint8_t* data = scratch + 4;
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl %4\n\tpushl %%edx\n\tcall *0x608(%%eax)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(count), "m"(data)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00597a80(PacketReader*) {
    __asm__ volatile(
        "subl $364,%esp\n\tpushl %esi\n\tleal 372(%esp),%eax\n\tleal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _counted_00597a80\n\taddl $8,%esp\n\tpopl %esi\n\taddl $364,%esp\n\tret");
}
