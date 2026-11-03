#pragma once
#include "cxx_exception.h"

// Explicit context for005D206A's original parent-EBP/local/register inputs.
// This is a normalization record, not an alleged original on-stack C type.
struct CxxCatchCleanup {
    CxxRegistration* frame;
    OriginalExceptionRecord* exception;
    void* saved_stack;
    CxxFrameInfo* active_frame;
    OriginalExceptionRecord* saved_exception;
    void* saved_context;
    void* result;
    uint32_t suppress_destruction;
};
struct CxxTranslatorGuard {
    void* previous;
    void* dispatcher;
    uint32_t cookie;
    CxxFuncInfo* information;
    CxxRegistration* frame;
    int32_t catch_depth;
    void* guard_frame;
    void* saved_stack;
    void* saved_frame;
    int32_t unwinding;
};
static_assert(sizeof(CxxTranslatorGuard) == 40);

extern "C" {
//005D2255: frame=ESI, handler=EBX, try_block=EDI, catchable=ECX;
// six ordinary stack arguments become the other explicit parameters below.
void fun_005d2255(OriginalExceptionRecord*, CxxRegistration*, void* context,
                  void* dispatcher_context, CxxFuncInfo*, CxxHandlerType*, CxxCatchableType*,
                  CxxTryBlock*, int32_t catch_depth, void* guard_frame);
void fun_005d22bc(OriginalExceptionRecord*, CxxRegistration*, void* context,
                  void* dispatcher_context, CxxFuncInfo*, int32_t state, int32_t catch_depth,
                  void* guard_frame);
//005D20D9 receives catchable=ECX and frame/destination=EDX plus two stack args.
void fun_005d20d9(OriginalExceptionRecord*, void* frame_or_destination, const CxxHandlerType*,
                  const CxxCatchableType*);
//005D1F15 additionally receives its catch funclet inECX.
void* fun_005d1f15(OriginalExceptionRecord*, CxxRegistration*, void* context, CxxFuncInfo*,
                   void* handler, int32_t catch_depth, uint32_t code);
void fun_005d206a(CxxCatchCleanup*);
void __attribute__((stdcall)) fun_005cc9b2(void* target_frame, OriginalExceptionRecord*);
[[noreturn]] void __attribute__((stdcall)) fun_005cc97b(void* continuation, CxxRegistration*);
void __attribute__((stdcall)) fun_005cce46(void* object, CxxThrowInfo*);

int32_t fun_005dc907(const void*, uint32_t bytes);
int32_t fun_005dc923(void*, uint32_t bytes);
int32_t fun_005dc93f(void* function);
void __attribute__((stdcall)) recovered_cxx_member1(void*, void* function, void* argument);
void __attribute__((stdcall)) recovered_cxx_member2(void*, void* function, void* first,
                                                    uint32_t second);

// Actual original SE-translator boundary, recovered in the next source family.
int32_t fun_005cca75(OriginalExceptionRecord*, CxxRegistration*, void* context,
                     void* dispatcher_context, CxxFuncInfo*, int32_t catch_depth,
                     void* guard_frame);
int32_t fun_005ccb3c(OriginalExceptionRecord*, CxxTranslatorGuard*, void* context,
                     void* dispatcher_context);
}
