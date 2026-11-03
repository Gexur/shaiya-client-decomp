#include "string_errors.h"

namespace {
// Normalized source lifetime guards for the two original unwind-map actions;
// these are compiler integration records, not additional original procedures.
struct BaseUnwind {
    OriginalExceptionBase* base;
    bool active = true;
    ~BaseUnwind() {
        if (active)
            fun_005cdd7f(base);
    }
};
struct TemporaryString {
    shaiya::startup::String_00405710 value;
    explicit TemporaryString(const char* text) {
        FUN_00405800(&value, text);
    }
    ~TemporaryString() {
        FUN_00529db0(&value);
    }
};
} // namespace
extern "C" OriginalLogicError* __attribute__((thiscall))
FUN_0040ad80(OriginalLogicError* self, const shaiya::startup::String_00405710* message) {
    fun_005cdd1c(&self->base);
    BaseUnwind unwind{&self->base};
    self->base.vtable = &dat_006dbc74;
    self->text.size_014 = 0;
    self->text.capacity_018 = 15;
    self->text.storage_004[0] = 0;
    FUN_00405620(&self->text, message, 0, 0xffffffffu);
    unwind.active = false;
    return self;
}
extern "C" OriginalLogicError* __attribute__((thiscall))
FUN_0040b040(OriginalLogicError* self, const OriginalLogicError* source) {
    fun_005cdd2d(&self->base, &source->base);
    BaseUnwind unwind{&self->base};
    self->base.vtable = &dat_006dbc74;
    self->text.capacity_018 = 15;
    self->text.size_014 = 0;
    self->text.storage_004[0] = 0;
    FUN_00405620(&self->text, &source->text, 0, 0xffffffffu);
    unwind.active = false;
    return self;
}
extern "C" [[noreturn]] void FUN_005e1911() {
    TemporaryString message("invalid string position"); // original006DBC94
    OriginalLogicError exception;
    FUN_0040ad80(&exception, &message.value);
    exception.base.vtable = &dat_006dbc8c;
    fun_005cce46(&exception, const_cast<CxxThrowInfo*>(&dat_006fa6dc));
    __builtin_unreachable();
}
extern "C" [[noreturn]] void __attribute__((thiscall))
FUN_005e1951(shaiya::startup::String_00405710*) {
    TemporaryString message("string too long"); // original006DBCAC
    OriginalLogicError exception;
    FUN_0040ad80(&exception, &message.value);
    exception.base.vtable = &dat_006dbc80;
    fun_005cce46(&exception, const_cast<CxxThrowInfo*>(&dat_006fa52c));
    __builtin_unreachable();
}
