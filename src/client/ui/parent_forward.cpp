#include "parent_forward.h"
namespace shaiya::ui {
namespace {
u32 word(const void* base, u32 offset) {
    u32 value;
    auto* at = static_cast<const u8*>(base) + offset;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
u32 byte(const void* base, u32 offset) {
    u32 value;
    auto* at = static_cast<const u8*>(base) + offset;
    __asm__ volatile("movzbl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
void put_byte(void* base, u32 offset, u8 value) {
    auto* at = static_cast<u8*>(base) + offset;
    __asm__ volatile("movb %1,(%0)" ::"r"(at), "q"(value) : "memory");
}
} // namespace

// Original004a75f0..004a7674. Its false initial gate leaves incomingEAX
// untouched. Only the low byte of4c8fb0 controls the next branch/index.
extern "C" u32 recovered_004a75f0(Object_004230b0* self, u32 argument, u32 incoming) {
    if (word(self, 0) == 0)
        return incoming;
    u32 mapped = byte(self, 4);
    void* context = &dat_008655e8;
    // Original also supplies the zero-extended byte in EAX to this custom
    // caller contract. Capture full residualEAX when its low byte is14.
    __asm__ volatile("pushl %%eax\n\tcalll _FUN_004c8fb0"
                     : "+a"(mapped), "+c"(context)::"edx", "memory", "cc");
    if (static_cast<u8>(mapped) == 14)
        return mapped;
    const u32 code = static_cast<u8>(mapped);
    const u32 offset = code * 40;
    // Actual PUSH ECX reserves this private DWORD with the receiver bits.
    // MOV BYTE[ESP+4],AL replaces only its low byte; the later DWORD load
    // passes the untouched receiver upper24bits as part of operand4.
    const u32 stored_mapping = (reinterpret_cast<u32>(self) & 0xffffff00u) | code;
    const u32 second = byte(dat_008666dd, offset + 1);
    const u32 first = byte(dat_008666dd, offset);
    const u32 found = find_item_record(dat_0086de50, first, second);
    if (found == 0)
        return found;
    const u8 current_first = static_cast<u8>(byte(dat_008666dd, offset));
    put_byte(self, 4, current_first);
    const u8 current_second = static_cast<u8>(byte(dat_008666dd, offset + 1));
    put_byte(self, 5, current_second);
    return FUN_004a3950(self, argument, 0, 0, stored_mapping, 0xffffffffu, 0, 0, 0, 0, 1);
}

// Textual register/stack adapter only: originalECX=self, stack+4=word,
// EAX=observable incoming scratch, RET4. The algorithm above is all C++.
extern "C" u32 __attribute__((naked, thiscall)) FUN_004a75f0(Object_004230b0*, u32) {
    __asm__ volatile(
        "pushl %eax\n\tpushl 8(%esp)\n\tpushl %ecx\n\tcalll _recovered_004a75f0\n\taddl $12,%esp\n\tretl $4");
}

// Original004a7680..004a76eb. A single zeroed localDWORD's address is a
// raw operand of both calls; no output/record meaning is inferred for it.
extern "C" u32 __attribute__((thiscall)) FUN_004a7680(Object_004230b0* self, u32 a1, u32 a2, u32 a3,
                                                      u32 a4, u32 a5, u32 a6, u32 a7, u32 a8) {
    u32 local = 0;
    const u32 cached_fifth = a5;
    (void)FUN_004a3950(self, reinterpret_cast<u32>(&local), a1, a2, a3, a4, a5, a6, a7, a8, 0);
    auto* callback =
        reinterpret_cast<shaiya::startup::CallbackObject_00405cc0*>(word(&dat_007191d4, 0));
    const u32 enabled = callback->callbacks->callback_004(callback, 0x27);
    if (static_cast<u8>(enabled) == 0 || cached_fifth == 100)
        return enabled;
    u32 result = reinterpret_cast<u32>(&local);
    void* receiver = self;
    // Actual4a76d9 also enters75f0 with EAX equal to the argument address.
    __asm__ volatile("pushl %%eax\n\tcalll _FUN_004a75f0"
                     : "+a"(result), "+c"(receiver)::"edx", "memory", "cc");
    return result;
}
} // namespace shaiya::ui
