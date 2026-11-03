#include "fixed_consumers.h"

namespace {
// Explicit MOVs also describe accesses to inherited stack bytes without C++
// indeterminate-value promotion. They retain the original access ordering.
inline uint32_t word(const void* p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
inline void clear_word(void* p) {
    __asm__ volatile("movl $0,(%0)" : : "r"(p) : "memory");
}
inline void clear_byte(void* p) {
    __asm__ volatile("movb $0,(%0)" : : "r"(p) : "memory");
}
inline SessionPrefix* session() {
    return reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
}

// These bridges retain the proved original custom volatile-register inputs at
// the virtual boundary, in addition to thiscall ECX and the stack arguments.
// No callback implementation, vtable storage, or session instance is supplied.
#define POINTER_CALLBACK(slot)                                                                     \
    uint32_t result;                                                                               \
    __asm__ volatile("movl %1,%%ecx\n\tmovl (%%ecx),%%edx\n\t"                                     \
                     "movl %2,%%eax\n\tpushl %%eax\n\tcall *" #slot "(%%edx)"                      \
                     : "=a"(result)                                                                \
                     : "m"(receiver), "m"(scratch)                                                 \
                     : "ecx", "edx", "memory", "cc");                                              \
    return result
#define SCALAR_CALLBACK(slot)                                                                      \
    uint32_t result;                                                                               \
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"                                          \
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *" #slot "(%%edx)"                 \
                     : "=a"(result)                                                                \
                     : "m"(receiver), "m"(value)                                                   \
                     : "ecx", "edx", "memory", "cc");                                              \
    return result
#define TWO_SCALAR_CALLBACK(slot)                                                                  \
    uint32_t result;                                                                               \
    __asm__ volatile("movl %1,%%ecx\n\tmovl %4,%%edx\n\t"                                          \
                     "movl %2,%%eax\n\tpushl %3\n\tpushl %%eax\n\tcall *" #slot "(%%edx)"          \
                     : "=a"(result)                                                                \
                     : "m"(receiver), "m"(first), "m"(second), "m"(table)                          \
                     : "ecx", "edx", "memory", "cc");                                              \
    return result
} // namespace

extern "C" __attribute__((noinline)) uint32_t fixed_0058d5c0(const void* args, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(args));
    read_available_packet_bytes(reader, scratch, 0x15);
    auto* receiver = session();
    POINTER_CALLBACK(0x294);
}
extern "C" __attribute__((noinline)) uint32_t fixed_0058d5f0(const void* args, uint8_t* scratch) {
    clear_word(scratch);
    clear_word(scratch + 4);
    clear_word(scratch + 8);
    clear_word(scratch + 12);
    clear_word(scratch + 16);
    auto* reader = reinterpret_cast<PacketReader*>(word(args));
    clear_byte(scratch + 20);
    read_available_packet_bytes(reader, scratch, 0x15);
    auto* receiver = session();
    POINTER_CALLBACK(0x2f8);
}
extern "C" __attribute__((noinline)) uint32_t fixed_0058d640(const void* args, uint8_t* scratch) {
    clear_word(scratch);
    clear_word(scratch + 4);
    clear_word(scratch + 8);
    clear_word(scratch + 12);
    clear_word(scratch + 16);
    auto* reader = reinterpret_cast<PacketReader*>(word(args));
    clear_byte(scratch + 20);
    read_available_packet_bytes(reader, scratch, 0x15);
    auto* receiver = session();
    POINTER_CALLBACK(0x2fc);
}
extern "C" __attribute__((noinline)) uint32_t fixed_0058d690(const void* args, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(args));
    read_packet_bytes_with_diagnostic(reader, scratch, 0x1c);
    auto* receiver = session();
    POINTER_CALLBACK(0x44c);
}
extern "C" __attribute__((noinline)) uint32_t fixed_0058d6c0(const void* args, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(args));
    read_available_packet_bytes(reader, scratch, 0x15);
    auto* receiver = session();
    POINTER_CALLBACK(0x45c);
}
extern "C" __attribute__((noinline)) uint32_t fixed_0058d6f0() {
    uint32_t result;
    __asm__ volatile("movl _dat_0224a328,%%ecx\n\tmovl (%%ecx),%%eax\n\t"
                     "pushl $1\n\tcall *0x548(%%eax)"
                     : "=a"(result)
                     :
                     : "ecx", "edx", "memory", "cc");
    return result;
}
extern "C" __attribute__((noinline)) uint32_t fixed_0058d710(const void* args, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(args));
    read_available_packet_bytes(reader, scratch, 0x15);
    auto* receiver = session();
    POINTER_CALLBACK(0x56c);
}
extern "C" __attribute__((noinline)) uint32_t fixed_0058d830(const void* args, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(args));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = session();
    const uint32_t value = word(scratch);
    SCALAR_CALLBACK(0x14);
}
extern "C" __attribute__((noinline)) uint32_t fixed_0058db20(const void* args, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(args));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = session();
    const uint32_t value = word(scratch);
    SCALAR_CALLBACK(0x1c);
}
extern "C" __attribute__((noinline)) uint32_t fixed_0058db50(const void* args, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(args));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = word(scratch);
    auto* receiver = session();
    const uint32_t table = word(receiver);
    const uint32_t first = word(scratch + 4);
    TWO_SCALAR_CALLBACK(0x20);
}
extern "C" __attribute__((noinline)) uint32_t fixed_0058db90(const void* args, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(word(args));
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    const uint32_t second = word(scratch);
    auto* receiver = session();
    const uint32_t table = word(receiver);
    const uint32_t first = word(scratch + 4);
    TWO_SCALAR_CALLBACK(0x24);
}

// Only the original private storage/entry ABI lives in these adapters. Actual
// packet reads and each consumer's behavior above are C++; no binary is mapped.
// Spell the adapters explicitly: symbol names have no inferred address scheme.
#define BLOCK_ADAPTER(name, helper, size)                                                          \
    extern "C" __attribute__((naked)) void name(PacketReader*) {                                   \
        __asm__ volatile("subl $" #size ",%esp\n\tleal " #size "+4(%esp),%eax\n\t"                 \
                         "movl %esp,%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _" #helper            \
                         "\n\taddl $8,%esp\n\taddl $" #size ",%esp\n\tret");                       \
    }
BLOCK_ADAPTER(fun_0058d5c0, fixed_0058d5c0, 24)
BLOCK_ADAPTER(fun_0058d5f0, fixed_0058d5f0, 24)
BLOCK_ADAPTER(fun_0058d640, fixed_0058d640, 24)
BLOCK_ADAPTER(fun_0058d690, fixed_0058d690, 28)
BLOCK_ADAPTER(fun_0058d6c0, fixed_0058d6c0, 24)
BLOCK_ADAPTER(fun_0058d710, fixed_0058d710, 24)
extern "C" __attribute__((naked)) void fun_0058d6f0(PacketReader*) {
    __asm__ volatile("call _fixed_0058d6f0\n\tret");
}
#define BYTE_ADAPTER(name, helper)                                                                 \
    extern "C" __attribute__((naked)) void name(PacketReader*) {                                   \
        __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"                   \
                         "pushl %edx\n\tpushl %eax\n\tcall _" #helper                              \
                         "\n\taddl $8,%esp\n\tpopl %ecx\n\tret");                                  \
    }
BYTE_ADAPTER(fun_0058d830, fixed_0058d830)
BYTE_ADAPTER(fun_0058db20, fixed_0058db20)
#define TWO_ADAPTER(name, helper)                                                                  \
    extern "C" __attribute__((naked)) void name(PacketReader*) {                                   \
        __asm__ volatile("subl $8,%esp\n\tpushl %esi\n\tleal 16(%esp),%eax\n\t"                    \
                         "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _" #helper         \
                         "\n\taddl $8,%esp\n\tpopl %esi\n\taddl $8,%esp\n\tret");                  \
    }
TWO_ADAPTER(fun_0058db50, fixed_0058db50)
TWO_ADAPTER(fun_0058db90, fixed_0058db90)
