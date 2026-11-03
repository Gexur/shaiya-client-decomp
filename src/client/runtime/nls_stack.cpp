#include "nls.h"
#include "heap.h"

struct OriginalStackMemoryInformation {
    uint32_t base, allocation_base, allocation_protection, region_size;
    uint32_t state, protection, type;
};
struct OriginalSystemInformation {
    uint32_t architecture, page_size, minimum_address, maximum_address;
    uint32_t processor_mask, processors, processor_type, allocation_granularity;
    uint16_t processor_level, processor_revision;
};
static_assert(sizeof(OriginalStackMemoryInformation) == 28);
static_assert(sizeof(OriginalSystemInformation) == 36);
extern "C" {
__declspec(dllimport) uint32_t __attribute__((stdcall))
VirtualQuery(const void*, OriginalStackMemoryInformation*, uint32_t);
__declspec(dllimport) void __attribute__((stdcall)) GetSystemInfo(OriginalSystemInformation*);
__declspec(dllimport) void* __attribute__((stdcall)) VirtualAlloc(void*, uint32_t, uint32_t,
                                                                  uint32_t);
__declspec(dllimport) int32_t __attribute__((stdcall)) VirtualProtect(void*, uint32_t, uint32_t,
                                                                      uint32_t*);
}

extern "C" int32_t fun_005cfb61() {
    OriginalStackMemoryInformation information;
    OriginalSystemInformation system;
    // Original probes four bytes from its actual stack and queries that address.
    const void* address = __builtin_alloca(4);
    if (!VirtualQuery(address, &information, 28))
        return 0;
    const uint32_t allocation_base = information.allocation_base;
    GetSystemInfo(&system);
    const uint32_t page = system.page_size;
    const uint32_t candidate = (reinterpret_cast<uint32_t>(address) & ~(page - 1u)) - page;
    const uint32_t minimum = allocation_base + (dat_0224ede8 == 1 ? 17u : 2u) * page;
    if (candidate < minimum)
        return 0;
    uint32_t target = candidate;
    if (dat_0224ede8 != 1) {
        target = allocation_base;
        do {
            if (!VirtualQuery(reinterpret_cast<void*>(target), &information, 28))
                return 0;
            target += information.region_size;
        } while (!(information.state & 0x1000u));
        target = information.base;
        if (information.protection & 0x100u)
            return 1;
        if (candidate < target)
            return 0;
        if (target < minimum)
            target = minimum;
        VirtualAlloc(reinterpret_cast<void*>(target), page, 0x1000, 4);
    }
    uint32_t old_protection;
    return VirtualProtect(reinterpret_cast<void*>(target), page, dat_0224ede8 == 1 ? 1u : 0x104u,
                          &old_protection);
}
