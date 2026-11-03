#pragma once
#include <stdint.h>
struct OriginalSessionPointerVector {
    uint32_t opaque_prefix;
    uint32_t* begin;
    uint32_t* end;
    uint32_t* capacity_end;
};
static_assert(sizeof(OriginalSessionPointerVector) == 16, "observed original vector prefix");
extern "C" {
extern OriginalSessionPointerVector dat_021fd79c;
__attribute__((thiscall)) uint32_t fun_00570310(OriginalSessionPointerVector* self,
                                                uint32_t position, uint32_t count,
                                                uint32_t value_pointer);
__attribute__((thiscall)) uint32_t fun_00575b30(void* ignored_receiver, uint32_t count,
                                                uint32_t packed_triplets);
}
