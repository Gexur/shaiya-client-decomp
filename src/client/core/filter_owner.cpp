#include "filter_owner.h"
#include "runtime/allocations.h"
#include "runtime/array_lifetime.h"
#include "runtime/exit_registry.h"
#include "core/memory.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void zero_byte(u32 p) {
    __asm__ volatile("movb $0,(%0)" ::"r"(p) : "memory");
}
u32 free_result(u32 p) {
    u32 result;
    __asm__ volatile("pushl %1\n\tcalll _fun_005cc620\n\taddl $4,%%esp"
                     : "=a"(result)
                     : "r"(p)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
u32 array_free_result(u32 p) {
    u32 result;
    __asm__ volatile("pushl %1\n\tcalll _fun_005cdc59\n\taddl $4,%%esp"
                     : "=a"(result)
                     : "r"(p)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
void release_text(u32 p) {
    if (word(p + 0x18) >= 0x10)
        fun_005cc620(reinterpret_cast<void*>(word(p + 4)));
    put(p + 0x18, 0x0f);
    put(p + 0x14, 0);
    zero_byte(p + 4);
    fun_005cc620(reinterpret_cast<void*>(p));
}
u32 distance(u32 last, u32 first) {
    return static_cast<u32>(static_cast<int32_t>(last - first) >> 2);
}
} // namespace
// Complete437820..4378a3. The growth value is the actual second incoming word;
// the original shrinking path still makes its actual zero-length memmove call.
extern "C" u32 recovered_filter_resize(u32 self, u32 args) {
    const u32 begin = word(self + 4);
    u32 result = begin ? distance(word(self + 8), begin) : 0;
    const u32 count = word(args);
    if (result < count) {
        result = begin ? distance(word(self + 8), begin) : 0;
        const u32 last = word(self + 8), value = args + 4;
        return FUN_00437640(reinterpret_cast<OriginalFilterPointerVector*>(self), last,
                            count - result, value);
    }
    if (begin) {
        result = word(self + 8);
        const u32 actual = distance(result, begin);
        if (count < actual) {
            const u32 target = begin + count * 4;
            if (target != result) {
                const u32 bytes = distance(result, result) * 4;
                result = reinterpret_cast<u32>(fun_005cc630(reinterpret_cast<void*>(target),
                                                            reinterpret_cast<const void*>(result),
                                                            bytes)) +
                         bytes;
                put(self + 8, result);
            }
        }
    }
    return result;
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_00437820(void*, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_filter_resize\n\taddl $8,%esp\n\tretl $8");
}
// Complete437480..4375ce. Scratch fields14/18/1c and every fresh sentinel
// reload are original public object state, not private reconstructed locals.
extern "C" uint64_t recovered_filter_record_destroy(u32 self) {
    u32 index = 0;
    if (word(self) > 0) {
        do {
            const u32 value = word(word(self + 8) + index * 4);
            put(self + 0x14, value);
            if (value) {
                u32 node = word(word(value + 4));
                const u32 fresh_owner = word(self + 0x14);
                put(self + 0x18, node);
                if (node != word(fresh_owner + 4)) {
                    do {
                        const u32 payload = word(word(self + 0x18) + 8);
                        put(self + 0x1c, payload);
                        const u32 text = word(payload + 0x20);
                        if (text)
                            release_text(text);
                        const u32 current_payload = word(self + 0x1c);
                        if (current_payload)
                            release_text(current_payload);
                        const u32 next = word(word(self + 0x18));
                        put(self + 0x18, next);
                        const u32 owner = word(self + 0x14);
                        node = next;
                        if (node == word(owner + 4))
                            break;
                    } while (true);
                }
                const u32 owner = word(self + 0x14);
                if (owner) {
                    const u32 head = word(owner + 4);
                    u32 cursor = word(head);
                    put(head, head);
                    const u32 actual_head = word(owner + 4);
                    put(actual_head + 4, actual_head);
                    const bool pending = cursor != word(owner + 4);
                    put(owner + 8, 0);
                    if (pending) {
                        do {
                            const u32 next = word(cursor);
                            fun_005cc620(reinterpret_cast<void*>(cursor));
                            const u32 sentinel = word(owner + 4);
                            cursor = next;
                            if (cursor == sentinel)
                                break;
                        } while (true);
                    }
                    fun_005cc620(reinterpret_cast<void*>(word(owner + 4)));
                    put(owner + 4, 0);
                    fun_005cc620(reinterpret_cast<void*>(owner));
                }
                put(self + 0x14, 0);
            }
            ++index;
        } while (index < word(self));
    }
    const u32 begin = word(self + 8);
    if (begin)
        fun_005cc620(reinterpret_cast<void*>(begin));
    const u32 cleared = 0;
    put(self + 8, 0);
    put(self + 0xc, 0);
    put(self + 0x10, 0);
    if (cleared)
        fun_005cc620(reinterpret_cast<void*>(cleared));
    put(self + 8, 0);
    put(self + 0xc, 0);
    put(self + 0x10, 0);
    return static_cast<uint64_t>(index) << 32;
}
extern "C" __attribute__((naked, thiscall)) void FUN_00437480(void*) {
    __asm__ volatile(
        "pushl %ecx\n\tcalll _recovered_filter_record_destroy\n\taddl $4,%esp\n\tmovl %edx,%ecx\n\tretl");
}
// Complete555f30..555f5a, original vector cleanup used by record unwind.
extern "C" uint32_t __attribute__((thiscall)) FUN_00555f30(void* object) {
    const u32 self = reinterpret_cast<u32>(object);
    u32 result = word(self + 4);
    if (result)
        result = free_result(result);
    put(self + 4, 0);
    put(self + 8, 0);
    put(self + 12, 0);
    return result;
}
extern "C" OriginalFilterOwner12 dat_0071cff0 = {0, 0, nullptr};
extern "C" u32 recovered_filter_global_initialize() {
    FUN_00437910(&dat_0071cff0);
    return static_cast<u32>(fun_005ccf60(fun_006b8210));
}
extern "C" void __attribute__((naked)) fun_006b5bc0() {
    __asm__ volatile("calll _recovered_filter_global_initialize\n\tretl");
}
extern "C" u32 recovered_filter_global_destroy() {
    const u32 array = word(reinterpret_cast<u32>(&dat_0071cff0) + 8);
    if (!array)
        return array;
    const u32 count = word(array - 4);
    fun_005cdcbc(reinterpret_cast<void*>(array), 0x20, static_cast<int32_t>(count), FUN_00437480);
    return array_free_result(array - 4);
}
extern "C" void __attribute__((naked)) fun_006b8210() {
    __asm__ volatile("calll _recovered_filter_global_destroy\n\tretl");
}
