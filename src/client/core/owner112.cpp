#include "core/owner112.h"
#include "runtime/allocations.h"
namespace {
inline void* pointer(const void* object, uint32_t offset = 0) {
    void* result;
    const auto* at = static_cast<const unsigned char*>(object) + offset;
    __asm__ __volatile__("movl (%1),%0" : "=r"(result) : "r"(at) : "memory");
    return result;
}
inline void store_pointer(void* object, uint32_t offset, void* value) {
    auto* at = static_cast<unsigned char*>(object) + offset;
    __asm__ __volatile__("movl %1,(%0)" ::"r"(at), "r"(value) : "memory");
}
inline uint32_t word(const void* object, uint32_t offset) {
    uint32_t result;
    const auto* at = static_cast<const unsigned char*>(object) + offset;
    __asm__ __volatile__("movl (%1),%0" : "=r"(result) : "r"(at) : "memory");
    return result;
}
inline void store_word(void* object, uint32_t offset, uint32_t value) {
    auto* at = static_cast<unsigned char*>(object) + offset;
    __asm__ __volatile__("movl %1,(%0)" ::"r"(at), "r"(value) : "memory");
}
} // namespace
namespace shaiya::ui {
extern "C" const Deleting_0052d550 PTR_FUN_006c5850[1] = {FUN_0052d550};
// These two original allocation helpers are factored from the earlier UI
// unit. Explicit hardware writes also retain the original null+4 fault;
// no guessed allocation-failure repair or C++ invalid-dereference UB is used.
extern "C" __attribute__((noinline)) void* FUN_0052cf70() {
    void* node = FUN_005cc96d(0x18);
    if (node != nullptr)
        store_pointer(node, 0, node);
    u32 next_address = reinterpret_cast<u32>(node) + 4;
    if (next_address != 0)
        store_pointer(reinterpret_cast<void*>(next_address), 0, node);
    return node;
}
extern "C" __attribute__((noinline)) void* FUN_0052cf90() {
    void* node = FUN_005cc96d(0x14);
    if (node != nullptr)
        store_pointer(node, 0, node);
    u32 next_address = reinterpret_cast<u32>(node) + 4;
    if (next_address != 0)
        store_pointer(reinterpret_cast<void*>(next_address), 0, node);
    return node;
}
// Original004ce800..004ce837: detach the chain before releasing any node.
// Header/member reloads and the next-pointer read before free stay explicit.
extern "C" void __attribute__((thiscall)) FUN_004ce800(OriginalOwner112Fields* self) {
    void* header = pointer(self, 4);
    void* current = pointer(header);
    store_pointer(header, 0, header);
    header = pointer(self, 4);
    store_pointer(header, 4, header);
    void* end = pointer(self, 4);
    store_word(self, 8, 0);
    if (current != end) {
        do {
            void* next = pointer(current);
            fun_005cc620(current);
            header = pointer(self, 4);
            current = next;
        } while (current != header);
    }
}
// Original00447020..0044703d, also the constructor's sole FuncInfo action.
extern "C" void __attribute__((thiscall)) FUN_00447020(OriginalOwner112Fields* self) {
    FUN_004ce800(self);
    fun_005cc620(pointer(self, 4));
    store_pointer(self, 4, nullptr);
}
// Original0052d2f0..0052d387. All four payload reads (and the repeated reads
// on nonnull payload) occur in the original, even though three values are
// copied only to private scratch. Hardware reads retain their fault order.
extern "C" void __attribute__((thiscall)) FUN_0052d2f0(OriginalOwner112* self) {
    void* header = pointer(self, 0x50);
    void* current = pointer(header);
    while (current != header) {
        (void)word(current, 8);
        (void)word(current, 12);
        (void)word(current, 16);
        void* payload = pointer(current, 20);
        if (payload != nullptr) {
            (void)word(current, 8);
            (void)word(current, 12);
            (void)word(current, 16);
            payload = pointer(current, 20);
            fun_005cc620(payload);
        }
        header = pointer(self, 0x50);
        current = pointer(header);
        if (current != header) {
            void* previous = pointer(current, 4);
            void* next = pointer(current);
            store_pointer(previous, 0, next);
            next = pointer(current);
            previous = pointer(current, 4);
            store_pointer(next, 4, previous);
            fun_005cc620(current);
            store_word(self, 0x54, word(self, 0x54) - 1u);
        }
        header = pointer(self, 0x50);
        current = pointer(header);
    }
    FUN_004ce800(&self->fields_058);
    store_word(self, 0x64, 0);
}
// Original0052d500 has no exception registration. Its exact repeated clear
// calls and post-free pointer clears are kept, including failures in free.
extern "C" void __attribute__((thiscall)) FUN_0052d500(OriginalOwner112* self) {
    self->vtable_000 = PTR_FUN_006c5850;
    FUN_0052d2f0(self);
    FUN_004ce800(&self->fields_058);
    fun_005cc620(pointer(self, 0x5c));
    store_pointer(self, 0x5c, nullptr);
    FUN_004ce800(&self->fields_04c);
    fun_005cc620(pointer(self, 0x50));
    store_pointer(self, 0x50, nullptr);
}
extern "C" OriginalOwner112* __attribute__((thiscall)) FUN_0052d550(OriginalOwner112* self,
                                                                    u32 flags) {
    FUN_0052d500(self);
    if (flags & 1)
        fun_005cc620(self);
    return self;
}
} // namespace shaiya::ui
