#include "session_triplet_vector.h"
#include "session_pointer_ranges.h"
#include "core/memory.h"
#include "runtime/allocations.h"
// Genuine original length-error dependency, not an allocator or success model.
extern "C" __attribute__((thiscall, noreturn)) void fun_004d2aa0(void* self);
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
u32 distance(u32 last, u32 first) {
    return static_cast<u32>(static_cast<int32_t>(last - first) >> 2);
}
u32 move(u32 output, u32 input, u32 bytes) {
    return reinterpret_cast<uintptr_t>(
        fun_005cc630(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(input), bytes));
}
} // namespace
// 570310..5704f0. The actual three incoming argument slots are writable original
// state. Original pushECX is restored as ECX, except the growth path replaces
// that private slot with its new allocation. Result[1] supplies that ABI value.
extern "C" uint32_t recovered_00570310(uint32_t self, uint32_t arguments, uint32_t* result) {
    const u32 value_pointer = word(arguments + 8);
    const u32 begin = word(self + 4);
    const u32 value = word(value_pointer);
    put(arguments + 8, value);
    u32 capacity = begin ? distance(word(self + 12), begin) : 0;
    const u32 count = word(arguments + 4);
    result[0] = self;
    if (!count)
        return capacity;
    const u32 size = begin ? distance(word(self + 8), begin) : 0;
    if (0x3fffffffu - size < count)
        fun_004d2aa0(reinterpret_cast<void*>(self));
    const u32 required = (begin ? distance(word(self + 8), begin) : 0) + count;
    if (capacity < required) {
        capacity = 0x3fffffffu - (capacity >> 1) < capacity ? 0 : capacity + (capacity >> 1);
        const u32 required_again = (begin ? distance(word(self + 8), begin) : 0) + count;
        if (capacity < required_again)
            capacity = (begin ? distance(word(self + 8), begin) : 0) + count;
        const u32 bytes = capacity * 4;
        put(arguments + 4, bytes);
        const u32 allocation = reinterpret_cast<uintptr_t>(fun_005cc96d(bytes));
        const u32 input = word(self + 4), position = word(arguments);
        const u32 prefix_bytes = distance(position, input) * 4;
        u32 cursor = move(allocation, input, prefix_bytes) + prefix_bytes;
        cursor = fun_004ce990(cursor, count, arguments + 8);
        const u32 suffix_bytes = distance(word(self + 8), position) * 4;
        move(cursor, position, suffix_bytes);
        const u32 old_begin = word(self + 4);
        const u32 old_size = old_begin ? distance(word(self + 8), old_begin) : 0;
        if (old_begin)
            fun_005cc620(reinterpret_cast<void*>(old_begin));
        const u32 actual_bytes = word(arguments + 4);
        put(self + 12, allocation + actual_bytes);
        put(self + 8, allocation + (count + old_size) * 4);
        put(self + 4, allocation);
        result[0] = allocation;
        return allocation;
    }
    const u32 last = word(self + 8), position = word(arguments);
    const u32 bytes = count * 4;
    put(arguments, bytes);
    if (distance(last, position) < count) {
        fun_00585260(position, last, position + bytes);
        const u32 current_last = word(self + 8);
        fun_004ce990(current_last, count - distance(current_last, position), arguments + 8);
        const u32 current_end = word(self + 8), written_bytes = word(arguments);
        const u32 end = current_end + written_bytes;
        put(self + 8, end);
        return fun_0048cad0(position, end - written_bytes, arguments + 8);
    }
    const u32 split = last - bytes;
    const u32 end = fun_00585260(split, last, last);
    put(self + 8, end);
    fun_004ce760(position, split, last);
    return fun_0048cad0(position, position + word(arguments), arguments + 8);
}
extern "C" __attribute__((naked, thiscall)) uint32_t fun_00570310(OriginalSessionPointerVector*,
                                                                  uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "subl $4,%esp\n\tmovl %esp,%eax\n\tleal 8(%esp),%edx\n\tpushl %eax\n\tpushl %edx\n\tpushl %ecx\n\tcalll _recovered_00570310\n\taddl $12,%esp\n\tmovl (%esp),%ecx\n\taddl $4,%esp\n\tretl $12");
}
