#include "probe_callback.h"
namespace {
uint32_t half(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movzwl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
uint32_t word(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
} // namespace
// Complete original55f7f0..55f806. ECX receiver is ignored; only the low
// WORD of the first argument and the pointer DWORD are read. The real443cd0
// receives both outgoing words but its original body reads neither of them.
extern "C" __attribute__((noinline)) uint32_t probe_callback_0055f7f0(const uint8_t* arguments) {
    const uint32_t count = half(arguments);
    const uint32_t data = word(arguments + 4);
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%eax\n\tmovl %2,%%ecx\n\tpushl %%eax\n\tpushl %%ecx\n\tcall _fun_00443cd0\n\taddl $8,%%esp"
        : "=a"(result)
        : "m"(count), "m"(data)
        : "ecx", "memory", "cc");
    return result;
}
extern "C" __attribute__((naked)) uint32_t PACKET_THISCALL fun_0055f7f0(SessionPrefix*, uint32_t,
                                                                        const void*) {
    __asm__ volatile(
        "pushl %edx\n\tleal 8(%esp),%eax\n\tpushl %eax\n\tcall _probe_callback_0055f7f0\n\taddl $4,%esp\n\tpopl %edx\n\tretl $8");
}
