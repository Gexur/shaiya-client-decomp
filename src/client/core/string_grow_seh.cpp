#include "string_internal.h"
#include "../runtime/allocations.h"

using shaiya::recovered_string::data;
using shaiya::startup::String_00405710;

extern "C" unsigned char* __attribute__((thiscall))
FUN_004054e0(String_00405710* self, uint32_t requested, uint32_t old_size) {
    uint32_t capacity = requested | 15u;
    if (capacity == 0xffffffffu)
        capacity = requested;
    else {
        const uint32_t previous = self->capacity_018;
        const uint32_t half = previous >> 1;
        if (capacity / 3 < half && previous <= 0xfffffffeu - half)
            capacity = previous + half;
    }
    unsigned char* allocated;
    try {
        allocated = static_cast<unsigned char*>(fun_005cc96d(capacity + 1));
    } catch (...) {
        capacity = requested;
        try {
            allocated = static_cast<unsigned char*>(fun_005cc96d(requested + 1));
        } catch (...) {
            if (self->capacity_018 >= 16)
                fun_005cc620(data(self));
            self->capacity_018 = 15;
            self->size_014 = 0;
            self->storage_004[0] = 0;
            throw;
        }
    }
    return FUN_0040557c(self, allocated, capacity, old_size);
}
