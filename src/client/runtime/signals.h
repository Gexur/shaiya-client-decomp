#pragma once
#include "thread_data.h"
#include "startup_filter.h"
struct RecoveredSignalContext {
    void* exception_context;
    uint32_t floating_code;
};
extern "C" {
extern void* dat_0224f224;
extern void* dat_0224f228;
extern void* dat_0224f22c;
extern void* dat_0224f230;
// Original lookup consumes table inEDX and signal inESI; explicit cdecl source
// arguments normalize only those proven machine operands.
OriginalExceptionAction* fun_005dbe5c(OriginalExceptionAction* table, int32_t signal);
int32_t fun_005dbe8a(int32_t signal);
// Private finally entry uses an enclosing-frame flag and ECX=0.
void fun_005dbfc5(int32_t global_action);
// Source outlining of the original protected writes, not an original entry.
// The separate TU keeps asynchronous faults inside the real compiler SEH call.
void recovered_signal_reset(int32_t signal, OriginalPerThreadData* data, void** slot,
                            RecoveredSignalContext* saved);
[[noreturn]] void fun_005d0ba9();
int32_t raise(int32_t signal);
[[noreturn]] void abort();
}
