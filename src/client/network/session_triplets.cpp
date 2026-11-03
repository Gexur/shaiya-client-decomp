#include "network/session_triplets.h"
extern "C" {
// These ranges lie beyond .data's file-backed bytes, in loader-zeroed memory.
}
namespace {
uint32_t byte(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movzbl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
void put_byte(void* pointer, uint32_t value) {
    __asm__ volatile("movb %b1,(%0)" ::"r"(pointer), "q"(value) : "memory");
}
uint32_t compared_flags(uint32_t index) {
    uint32_t flags;
    __asm__ volatile("cmpb $0xf0,%b1\n\tpushfl\n\tpopl %0"
                     : "=r"(flags)
                     : "q"(index)
                     : "memory", "cc");
    return flags;
}
void store_triplet(const uint32_t* arguments, uint32_t* state, const uint32_t* incoming,
                   OriginalSessionTriplet* table) {
    const uint32_t index = byte(arguments);
    uint32_t eax = (incoming[0] & 0xffffff00u) | index, ecx = incoming[1], edx = incoming[2];
    const uint32_t flags = compared_flags(index);
    if (index < 240) {
        const uint32_t first = byte(arguments + 1), second = byte(arguments + 2);
        eax = index;
        put_byte(&table[index].first, first);
        const uint32_t third = byte(arguments + 3);
        put_byte(&table[index].second, second);
        put_byte(&table[index].third, third);
        ecx = (ecx & 0xffffff00u) | third;
        edx = (edx & 0xffffff00u) | second;
    }
    state[0] = eax;
    state[1] = ecx;
    state[2] = edx;
    state[3] = flags;
}
} // namespace
extern "C" __attribute__((noinline)) void prepare_triplet_0056d4c0(const uint32_t* a, uint32_t* s,
                                                                   const uint32_t* i) {
    store_triplet(a, s, i, dat_021fe736);
}
extern "C" __attribute__((noinline)) void prepare_triplet_0056d5b0(const uint32_t* a, uint32_t* s,
                                                                   const uint32_t* i) {
    store_triplet(a, s, i, dat_021fea06);
}
// The original receives four stack DWORDs and ignores receiverECX for writes.
// Its physical result is index(EAX) on the accepted branch, merged incoming
// EAX/AL on the rejected branch; ECX/EDX retain their upper24 bits. The tiny
// adapters retain these contracts, CMP-defined status bits and RET16.
#define TRIPLET_ENTRY(name, helper)                                                                                                                                                             \
    extern "C" __attribute__((naked, thiscall)) uint32_t name(void*, uint32_t, uint32_t, uint32_t,                                                                                              \
                                                              uint32_t) {                                                                                                                       \
        __asm__ volatile(                                                                                                                                                                       \
            "pushl %edx\n\tpushl %ecx\n\tpushl %eax\n\tsubl $16,%esp\n\tmovl %esp,%eax\n\tleal 16(%esp),%ecx\n\tleal 32(%esp),%edx\n\tpushl %ecx\n\tpushl %eax\n\tpushl %edx\n\tcall _" #helper \
            "\n\taddl $12,%esp\n\tmovl (%esp),%eax\n\tmovl 4(%esp),%ecx\n\tmovl 8(%esp),%edx\n\tpushl 12(%esp)\n\tpopfl\n\tleal 28(%esp),%esp\n\tretl $16");                                    \
    }
TRIPLET_ENTRY(fun_0056d4c0, prepare_triplet_0056d4c0)
TRIPLET_ENTRY(fun_0056d5b0, prepare_triplet_0056d5b0)
#undef TRIPLET_ENTRY
