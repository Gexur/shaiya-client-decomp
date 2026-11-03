#include "runtime/cxx_dispatch.h"

namespace {
// Verified x86 compiler-emitted FuncInfo3 prefix: the first28 bytes match the
// original FuncInfo layout. Only the current recovered source's emitted table
// domains are claimed; exception specifications/other modern features require
// their own compatibility evidence before adding such recovered source.
struct CompilerFuncInfo3 {
    CxxFuncInfo original_prefix;
    void* exception_specification;
    uint32_t exception_flags;
};
static_assert(sizeof(CompilerFuncInfo3) == 36);
static_assert(offsetof(CompilerFuncInfo3, exception_specification) == 28);
} // namespace

// This is a compiler-integration adapter, not an additional recovered original
// procedure. It retains all original table pointers/state counts and applies
// the demonstrated compiler22 -> original20 metadata-version translation.
extern "C" int32_t recovered_cxx_frame_handler3(OriginalExceptionRecord* exception,
                                                CxxRegistration* frame, void* context,
                                                void* dispatcher_context,
                                                CompilerFuncInfo3* compiler_information) {
    CxxFuncInfo normalized = compiler_information->original_prefix;
    if ((normalized.magic_and_flags & 0x1fffffffu) == 0x19930522u)
        normalized.magic_and_flags = (normalized.magic_and_flags & 0xe0000000u) | 0x19930520u;
    return fun_005d257e(exception, frame, context, dispatcher_context, &normalized, 0, nullptr, 0);
}

// The compiler thunk uses the same four ordinary stack arguments and EAX
// metadata register as the original005CCA04 entry.
extern "C" __attribute__((naked)) int32_t __CxxFrameHandler3(OriginalExceptionRecord*,
                                                             CxxRegistration*, void*, void*) {
    __asm__ __volatile__(
        "pushl %ebp\n\tmovl %esp, %ebp\n\tcld\n\tpushl %eax\n\t"
        "pushl 20(%ebp)\n\tpushl 16(%ebp)\n\tpushl 12(%ebp)\n\tpushl 8(%ebp)\n\t"
        "calll _recovered_cxx_frame_handler3\n\taddl $20, %esp\n\tleave\n\tretl\n\t");
}

// The original throw helper already emits the legacy exception record consumed
// by the recovered handler; no throw result or exception dispatch is fabricated.
extern "C" __attribute__((stdcall)) void _CxxThrowException(void* object,
                                                            CxxThrowInfo* information) {
    fun_005cce46(object, information);
}

// Compiler noexcept integration: MSVC __std_terminate is cdecl void(void) and
// invokes terminate(). Keep it visible for hooks introduced during LTO codegen.
extern "C" __attribute__((used)) [[noreturn]] void __cdecl __std_terminate() {
    fun_005d292f();
}
