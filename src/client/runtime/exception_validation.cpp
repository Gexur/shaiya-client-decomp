#include "exception_validation.h"

namespace {
struct MemoryBasicInformation32 {
    uint32_t base, allocation_base, allocation_protect, region_size;
    uint32_t state, protect, type;
};
static_assert(sizeof(MemoryBasicInformation32) == 28 && sizeof(void*) == 4);

uint32_t load32(uint32_t address) {
    const auto* p = reinterpret_cast<const uint8_t*>(address);
    return uint32_t(p[0]) | (uint32_t(p[1]) << 8) | (uint32_t(p[2]) << 16) | (uint32_t(p[3]) << 24);
}
uint16_t load16(uint32_t address) {
    const auto* p = reinterpret_cast<const uint8_t*>(address);
    return uint16_t(uint16_t(p[0]) | (uint16_t(p[1]) << 8));
}
uint32_t tib_address() {
    uint32_t tib;
    // This is the original architecture-specific NT_TIB access, not a fixture
    // or a replacement stack-boundary policy.
    __asm__ volatile("movl %%fs:0x18, %0" : "=r"(tib));
    return tib;
}
void move_to_front(uint32_t page, int32_t last) {
    for (int32_t index = 0; index <= last; ++index) {
        const uint32_t previous = dat_0224f0c8[index];
        dat_0224f0c8[index] = page;
        page = previous;
    }
}
} // namespace

extern "C" {
__declspec(dllimport) uint32_t __attribute__((stdcall))
VirtualQuery(const void*, MemoryBasicInformation32*, uint32_t);
__declspec(dllimport) int32_t __attribute__((stdcall)) InterlockedExchange(volatile int32_t*,
                                                                           int32_t);
int32_t dat_0224f0c0 = 0;
uint32_t dat_0224f0c8[16] = {};
volatile int32_t dat_0224f108 = 0;
}

// 0x005da2a6..0x005da4ce. The three-valued result, single-section PE check,
// page cache ordering and contended-exchange early returns follow the binary.
extern "C" int32_t fun_005da2a6(const void* frame) {
    const uint32_t frame_address = reinterpret_cast<uint32_t>(frame);
    const uint32_t table = load32(frame_address + 8);
    if ((table & 3) != 0)
        return 0;
    const uint32_t tib = tib_address();
    const uint32_t stack_limit = load32(tib + 8);
    if (table >= stack_limit && table < load32(tib + 4))
        return 0;
    const uint32_t level = load32(frame_address + 12);
    if (level == 0xffffffffu)
        return 1;
    uint32_t index = 0, filters = 0, entry = table;
    do {
        const uint32_t parent = load32(entry);
        if (parent != 0xffffffffu && parent >= index)
            return 0;
        if (load32(entry + 4) != 0)
            ++filters;
        ++index;
        entry += 12;
    } while (index <= level);
    if (filters != 0) {
        const uint32_t saved_stack = load32(frame_address - 8);
        if (saved_stack < stack_limit || saved_stack >= frame_address)
            return 0;
    }
    const uint32_t page = table & 0xfffff000u;
    const int32_t initial_count = dat_0224f0c0;
    for (int32_t hit = 0; hit < initial_count; ++hit) {
        if (dat_0224f0c8[hit] != page)
            continue;
        if (hit == 0)
            return 1;
        if (InterlockedExchange(&dat_0224f108, 1) != 0)
            return 1;
        if (dat_0224f0c8[hit] != page) {
            int32_t count = dat_0224f0c0;
            hit = count - 1;
            while (hit >= 0 && dat_0224f0c8[hit] != page)
                --hit;
            if (hit < 0) {
                if (count < 16)
                    dat_0224f0c0 = ++count;
                hit = count - 1;
            } else if (hit == 0) {
                InterlockedExchange(&dat_0224f108, 0);
                return 1;
            }
        }
        move_to_front(page, hit);
        InterlockedExchange(&dat_0224f108, 0);
        return 1;
    }
    MemoryBasicInformation32 memory;
    if (VirtualQuery(reinterpret_cast<const void*>(table), &memory, 28) == 0 ||
        memory.type != 0x01000000)
        return -1;
    if ((memory.protect & 0xcc) != 0) {
        const uint32_t image = memory.allocation_base;
        if (load16(image) != 0x5a4d)
            return -1;
        const uint32_t nt = image + load32(image + 0x3c);
        if (load32(nt) != 0x4550 || load16(nt + 0x18) != 0x10b || load16(nt + 6) == 0)
            return -1;
        const uint32_t section = nt + 0x18 + load16(nt + 0x14);
        const uint32_t rva = table - image;
        const uint32_t virtual_address = load32(section + 0x0c);
        if (rva >= virtual_address && rva < virtual_address + load32(section + 8) &&
            (*reinterpret_cast<const uint8_t*>(section + 0x27) & 0x80) != 0)
            return 0;
    }
    if (InterlockedExchange(&dat_0224f108, 1) != 0)
        return 1;
    const int32_t count = dat_0224f0c0;
    int32_t remaining = count;
    if (remaining > 0) {
        do {
            if (dat_0224f0c8[remaining - 1] == page)
                break;
        } while (--remaining > 0);
    }
    if (remaining == 0) {
        move_to_front(page, count < 16 ? count : 15);
        if (count < 16)
            dat_0224f0c0 = count + 1;
    }
    InterlockedExchange(&dat_0224f108, 0);
    return 1;
}
