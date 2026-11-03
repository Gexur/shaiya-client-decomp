#include "pointer_table4004.h"
#include "../runtime/allocations.h"
extern "C" OriginalPointerTableOwner4* __attribute__((thiscall))
FUN_00520550(OriginalPointerTableOwner4* owner) {
    owner->resource = nullptr;
    return owner;
}
extern "C" void __attribute__((thiscall)) FUN_00530c10(OriginalPointerTable4004* resource) {
    for (uint32_t i = 0; i < 1000; ++i) {
        OriginalTenPointers48* block = resource->blocks04[i];
        if (block != nullptr) {
            for (uint32_t j = 0; j < 10; ++j) {
                void* pointer = block->pointers08[j];
                if (pointer != nullptr) {
                    fun_005cc620(pointer);
                    block->pointers08[j] = nullptr;
                }
            }
            fun_005cc620(block);
            resource->blocks04[i] = nullptr;
        }
    }
}
extern "C" void __attribute__((thiscall)) FUN_00531550(OriginalPointerTableOwner4* owner) {
    OriginalPointerTable4004* resource = owner->resource;
    if (resource != nullptr) {
        FUN_00530c10(resource);
        fun_005cc620(resource);
        owner->resource = nullptr;
    }
}
