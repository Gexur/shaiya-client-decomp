#include "packet_scalar_extra.h"
namespace {
uint32_t word(const void* p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
} // namespace

// Complete original592a60..592a8b. PUSH ECX supplies the actual four-byte
// private backing; read4 overwrites it. The mode word is loaded after read4,
// before the current session/table, and the scalar DWORD is loaded afterward.
extern "C" __attribute__((noinline)) uint32_t scalar_extra_00592a60(const void* arguments,
                                                                    void* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t mode = word(static_cast<const uint8_t*>(arguments) + 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    const uint32_t scalar = word(scratch);
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl %4\n\tpushl %%eax\n\tcall *0x280(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(scalar), "m"(mode)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00592a60(PacketReader*, uint32_t) {
    __asm__ volatile(
        "pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _scalar_extra_00592a60\n\taddl $8,%esp\n\tpopl %ecx\n\tret");
}

// Complete original597ae0..597b07. Only one byte is read into PUSH ECX's
// original DWORD; its upper24 bits remain exactly the inherited ECX bits.
// The full scalar DWORD is captured before the current session/table load.
extern "C" __attribute__((noinline)) uint32_t scalar_extra_00597ae0(const void* arguments,
                                                                    void* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    const uint32_t scalar = word(scratch);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl %%eax\n\tpushl $0\n\tcall *0x624(%%edx)"
        : "=a"(result)
        : "m"(receiver), "m"(table), "m"(scalar)
        : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) void fun_00597ae0(PacketReader*) {
    __asm__ volatile(
        "pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _scalar_extra_00597ae0\n\taddl $8,%esp\n\tpopl %ecx\n\tret");
}
