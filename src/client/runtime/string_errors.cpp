#include "string_errors.h"
#include "allocations.h"
#include "strings.h"
#include "../core/string_internal.h"

extern "C" const char dat_006d5f00[18] = "Unknown exception";

extern "C" OriginalExceptionBase* __attribute__((thiscall))
fun_005cdd1c(OriginalExceptionBase* self) {
    self->message = nullptr;
    self->owns_message = 0;
    self->vtable = &dat_006d5ef8;
    return self;
}
extern "C" OriginalExceptionBase* __attribute__((thiscall))
fun_005cdd2d(OriginalExceptionBase* self, const OriginalExceptionBase* source) {
    self->vtable = &dat_006d5ef8;
    self->owns_message = source->owns_message;
    if (self->owns_message != 0) {
        if (source->message != nullptr) {
            self->message = static_cast<char*>(fun_005cfade(fun_005d4cf0(source->message) + 1));
            if (self->message != nullptr)
                fun_005d6350(self->message, source->message);
        } else
            self->message = nullptr;
    } else
        self->message = source->message;
    return self;
}
extern "C" void __attribute__((thiscall)) fun_005cdd7f(void* object) {
    auto* self = static_cast<OriginalExceptionBase*>(object);
    self->vtable = &dat_006d5ef8;
    if (self->owns_message != 0)
        fun_005cfaf0(self->message);
}
extern "C" const char* __attribute__((thiscall)) fun_005cdd95(const void* object) {
    auto* self = static_cast<const OriginalExceptionBase*>(object);
    return self->message != nullptr ? self->message : dat_006d5f00;
}
extern "C" void* __attribute__((thiscall)) fun_005cdda2(void* self, uint32_t flags) {
    fun_005cdd7f(self);
    if ((flags & 1) != 0)
        fun_005cc620(self);
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_0040ab70(void* object) {
    auto* self = static_cast<OriginalLogicError*>(object);
    self->base.vtable = &dat_006dbc74;
    if (self->text.capacity_018 >= 16)
        fun_005cc620(shaiya::recovered_string::data(&self->text));
    self->text.capacity_018 = 15;
    self->text.size_014 = 0;
    self->text.storage_004[0] = 0;
    fun_005cdd7f(&self->base);
}
extern "C" const char* __attribute__((thiscall)) FUN_0040abb0(const void* object) {
    return reinterpret_cast<const char*>(
        shaiya::recovered_string::data(&static_cast<const OriginalLogicError*>(object)->text));
}
extern "C" void* __attribute__((thiscall)) FUN_0040d230(void* self, uint32_t flags) {
    FUN_0040ab70(self);
    if ((flags & 1) != 0)
        fun_005cc620(self);
    return self;
}
extern "C" OriginalLogicError* __attribute__((thiscall))
FUN_0040b0b0(OriginalLogicError* self, const OriginalLogicError* source) {
    FUN_0040b040(self, source);
    self->base.vtable = &dat_006dbc80;
    return self;
}
extern "C" OriginalLogicError* __attribute__((thiscall))
FUN_0040d830(OriginalLogicError* self, const OriginalLogicError* source) {
    FUN_0040b040(self, source);
    self->base.vtable = &dat_006dbc8c;
    return self;
}
