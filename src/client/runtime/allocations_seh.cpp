// The original calloc body has a real lock4 finally region. The central
// MSVC-target SEH build emits its relocated scope table and handler boundary.
#include "allocations.h"
#include "../core/memory.h"

extern "C" __declspec(dllimport) void* __attribute__((stdcall)) HeapAlloc(void*, uint32_t,
                                                                          uint32_t);

extern "C" void* fun_005d8c58(uint32_t count, uint32_t element_bytes) {
    if (count != 0 && element_bytes > 0xffffffe0u / count)
        return nullptr;
    const uint32_t product_bytes = count * element_bytes;
    uint32_t requested_bytes = product_bytes;
    if (requested_bytes == 0)
        requested_bytes = 1;
    for (;;) {
        void* result = nullptr;
        if (requested_bytes <= 0xffffffe0u) {
            if (dat_022532c8 == 3) {
                requested_bytes = (requested_bytes + 15) & 0xfffffff0u;
                if (product_bytes <= dat_022532b4) {
                    fun_005d659b(4);
                    __try {
                        result = fun_005d9f8f(product_bytes);
                    } __finally {
                        fun_005d8d1e();
                    }
                    if (result != nullptr) {
                        fun_005dceb0(result, 0, product_bytes);
                        return result;
                    }
                }
            }
            result = HeapAlloc(dat_022532c4, 8, requested_bytes);
        }
        if (result != nullptr || dat_0224f0b8 == 0)
            return result;
        if (fun_005da28b(requested_bytes) == 0)
            return nullptr;
    }
}
