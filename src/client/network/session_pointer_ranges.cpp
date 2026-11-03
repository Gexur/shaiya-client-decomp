#include "session_pointer_ranges.h"
#include "core/memory.h"
namespace {
using u32 = uint32_t;
u32 word(u32 address) {
    u32 result;
    __asm__ volatile("movl (%1),%0" : "=r"(result) : "r"(address) : "memory");
    return result;
}
void put(u32 address, u32 value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(address), "r"(value) : "memory");
}
u32 move(u32 output, u32 input, u32 bytes) {
    return reinterpret_cast<uintptr_t>(
        fun_005cc630(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(input), bytes));
}
} // namespace
// 4ce990..4ce9ba: count precedes output; zero count skips argument3 entirely.
extern "C" uint32_t recovered_004ce990(uint32_t arguments) {
    const u32 count = word(arguments + 4), output = word(arguments);
    if (count) {
        const u32 value = word(arguments + 8);
        u32 cursor = output, remaining = count;
        do {
            put(cursor, word(value));
            cursor += 4;
        } while (--remaining);
    }
    return output + count * 4;
}
// 48cad0..48caee reloads the pointed value before every destination write.
extern "C" uint32_t recovered_0048cad0(uint32_t arguments) {
    u32 first = word(arguments);
    const u32 last = word(arguments + 4);
    if (first != last) {
        const u32 value = word(arguments + 8);
        do {
            put(first, word(value));
            first += 4;
        } while (first != last);
    }
    return first;
}
extern "C" uint32_t recovered_00585260(uint32_t arguments) {
    const u32 first = word(arguments), last = word(arguments + 4);
    const u32 bytes = static_cast<u32>(static_cast<int32_t>(last - first) >> 2) * 4;
    const u32 output = word(arguments + 8);
    return move(output, first, bytes) + bytes;
}
extern "C" uint32_t recovered_004ce760(uint32_t arguments) {
    const u32 first = word(arguments), last = word(arguments + 4);
    const u32 bytes = static_cast<u32>(static_cast<int32_t>(last - first) >> 2) * 4;
    const u32 output_end = word(arguments + 8);
    return move(output_end - bytes, first, bytes);
}
#define RANGE_ENTRY(name, helper, pop)                                                             \
    extern "C" __attribute__((naked)) uint32_t name(uint32_t, uint32_t, uint32_t) {                \
        __asm__ volatile("leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _" #helper                      \
                         "\n\taddl $4,%esp\n\tretl " pop);                                         \
    }
// Separate declarations retain the original callee-pop ABI in COFF symbols.
extern "C" __attribute__((naked, stdcall)) uint32_t fun_004ce990(uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_004ce990\n\taddl $4,%esp\n\tretl $12");
}
RANGE_ENTRY(fun_0048cad0, recovered_0048cad0, "")
extern "C" __attribute__((naked, stdcall)) uint32_t fun_00585260(uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00585260\n\taddl $4,%esp\n\tretl $12");
}
RANGE_ENTRY(fun_004ce760, recovered_004ce760, "")
#undef RANGE_ENTRY
