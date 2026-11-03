#include "runtime/string_errors.h"

// Exact readonly original006be8ec..006be8ff, including the trailing NUL.
extern "C" const char dat_006be8ec[19] = "vector<T> too long";
namespace {
struct OriginalTemporaryMessage {
    shaiya::startup::String_00405710 text;
    OriginalTemporaryMessage() {
        text.capacity_018 = 15;
        text.size_014 = 0;
        text.storage_004[0] = 0;
        FUN_00405710(&text, dat_006be8ec, 18);
    }
    // Original unwind action006ac7a0 calls00529db0 on this temporary.
    ~OriginalTemporaryMessage() {
        FUN_00529db0(&text);
    }
};
} // namespace

// Complete004375d0..00437639. The original call005cce46 never returns.
// IncomingECX is unused. Every string/exception operation is a real callee.
extern "C" [[noreturn]] void __attribute__((thiscall)) FUN_004375d0(void*) {
    OriginalTemporaryMessage message;
    OriginalLogicError exception;
    FUN_0040ad80(&exception, &message.text);
    exception.base.vtable = &dat_006dbc80;
    fun_005cce46(&exception, const_cast<CxxThrowInfo*>(&dat_006fa52c));
    __builtin_unreachable();
}
