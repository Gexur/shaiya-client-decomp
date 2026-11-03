#include "string.h"
#include "string_internal.h"
#include "../runtime/allocations.h"

using shaiya::startup::String_00405710;

// Existing recovered bodies moved out of the graphics translation unit. The
// delete spelling below names the canonical recovered005CC620 implementation.
extern "C" String_00405710* __attribute__((thiscall)) FUN_00405800(String_00405710* self,
                                                                   const char* text) {
    self->capacity_018 = 15;
    self->size_014 = 0;
    self->storage_004[0] = 0;
    uint32_t length = 0;
    while (text[length] != 0)
        ++length;
    FUN_00405710(self, text, length);
    return self;
}
extern "C" uint32_t __attribute__((thiscall)) FUN_00529db0(String_00405710* self) {
    if (self->capacity_018 >= 16)
        fun_005cc620(shaiya::recovered_string::data(self));
    self->capacity_018 = 15;
    self->size_014 = 0;
    self->storage_004[0] = 0;
    return 0;
}
