#pragma once
#include <stdint.h>

struct OriginalExceptionRecord {
    uint32_t code;
    uint32_t flags;
    OriginalExceptionRecord* nested;
    void* address;
    uint32_t parameter_count;
    uint32_t parameters[15];
};
struct OriginalExceptionPointers {
    OriginalExceptionRecord* record;
    void* context;
};
struct OriginalScopeEntry {
    int32_t enclosing_level;
    void* filter;
    void* handler;
};
struct OriginalExceptionRegistration {
    void* previous;
    void* dispatcher;
    OriginalScopeEntry* scope_table;
    int32_t scope_level;
};
struct OriginalUnwindRegistration {
    void* previous;
    void* dispatcher;
    int32_t enclosing_level;
    OriginalExceptionRegistration* frame;
};
struct OriginalNlgInformation {
    uint32_t signature;
    void* destination;
    uint32_t code;
    void* frame_pointer;
};
static_assert(sizeof(OriginalScopeEntry) == 12);
static_assert(sizeof(OriginalExceptionRegistration) == 16);
static_assert(sizeof(OriginalUnwindRegistration) == 16);
static_assert(sizeof(OriginalNlgInformation) == 16);

extern "C" {
extern OriginalNlgInformation dat_0070e120;
int32_t fun_005cfc4c(OriginalExceptionRecord*, OriginalExceptionRegistration*, void* context,
                     void* dispatcher_context);
int32_t fun_005ccd78(OriginalExceptionRecord*, OriginalUnwindRegistration*, void* context,
                     void** dispatcher_context);
void fun_005ccd58(OriginalExceptionRegistration* target);
// The original __local_unwind2 ABI additionally consumes its caller's EBP.
void fun_005ccd9a(OriginalExceptionRegistration*, int32_t target_level);
int32_t fun_005cce02();
// Architecture-specific NLG notification entries. EAX=destination, EBP=frame;
// 5cce25 takes the code in ECX, while 5cce2e reads DWORD [EBP+8]. Both RET 4.
void fun_005cce25();
void fun_005cce2e();
// Real validation dependency, recovered separately with Win32 VirtualQuery.
int32_t fun_005da2a6(const void* registration_frame);
}
