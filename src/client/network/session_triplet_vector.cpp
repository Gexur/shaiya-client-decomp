#include "network/session_triplet_vector.h"
#include "runtime/allocations.h"
extern "C" {
// Only this observed16-byte prefix is owned. PE .data's virtual tail supplies
// these zeros; the range has no file-backed bytes and no invented constructor.
}
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
u32 byte(u32 p) {
    u32 v;
    __asm__ volatile("movzbl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
u32 half(u32 p) {
    u32 v;
    __asm__ volatile("movzwl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void put_byte(u32 p, u32 v) {
    __asm__ volatile("movb %b1,(%0)" ::"r"(p), "q"(v) : "memory");
}
void put_half(u32 p, u32 v) {
    __asm__ volatile("movw %w1,(%0)" ::"r"(p), "r"(v) : "memory");
}
u32 distance(u32 last, u32 first) {
    return static_cast<u32>(static_cast<int32_t>(last - first) >> 2);
}
} // namespace
extern "C" uint32_t recovered_00575b30(uint32_t arguments) {
    u32 count = byte(arguments);
    if (!count)
        return count;
    u32 payload = word(arguments + 4), index = 0;
    const u32 self = reinterpret_cast<uintptr_t>(&dat_021fd79c);
    do {
        const u32 allocation = reinterpret_cast<uintptr_t>(fun_005cc96d(4));
        if (!allocation)
            return 0;
        put_byte(allocation + 2, byte(payload + 2));
        put_half(allocation, half(payload));
        const u32 begin = word(self + 4), end = word(self + 8);
        put(arguments + 4, allocation);
        if (begin && distance(end, begin) < distance(word(self + 12), begin)) {
            put(end, allocation);
            put(self + 8, end + 4);
        } else {
            fun_00570310(&dat_021fd79c, end, 1, arguments + 4);
        }
        count = byte(arguments);
        ++index;
        payload += 3;
    } while (static_cast<int32_t>(index) < static_cast<int32_t>(count));
    return count;
}
extern "C" __attribute__((naked, thiscall)) uint32_t fun_00575b30(void*, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00575b30\n\taddl $4,%esp\n\tretl $8");
}
