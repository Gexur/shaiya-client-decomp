#include "exit_registry.h"
#include "heap.h"

extern "C" __declspec(dllimport) uint32_t __attribute__((stdcall)) HeapSize(void*, uint32_t,
                                                                            const void*);

namespace {
// Keep the exact SBH lookup/header load inside an actual protected call. This
// preserves hardware-fault finally behavior with the current x86 SEH compiler.
__declspec(noinline) void small_block_size(void* pointer, SmallBlockRegion** region,
                                           uint32_t* size) {
    *region = fun_005d97b0(pointer);
    if (*region != nullptr)
        *size = static_cast<uint32_t*>(pointer)[-1] - 9;
}
} // namespace

extern "C" uint32_t fun_005d2a5a(void* pointer) {
    if (dat_022532c8 == 3) {
        fun_005d659b(4);
        SmallBlockRegion* region;
        uint32_t result;
        __try {
            small_block_size(pointer, &region, &result);
        } __finally {
            fun_005d2ac7();
        }
        if (region != nullptr)
            return result;
    }
    return HeapSize(dat_022532c4, 0, pointer);
}
