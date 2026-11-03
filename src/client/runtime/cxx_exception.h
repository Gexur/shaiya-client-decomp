#pragma once
#include <stdint.h>
#include <stddef.h>
#include "exception.h"

struct CxxRegistration {
    void* previous;
    void* dispatcher;
    int32_t state;
};
struct CxxFrameInfo {
    void* object;
    CxxFrameInfo* next;
};
struct CxxHandlerType {
    uint32_t adjectives;
    const void* type_header; // Original type name starts eight bytes later.
    int32_t catch_object_displacement;
    void* handler;
};
struct CxxTryBlock {
    int32_t try_low;
    int32_t try_high;
    int32_t catch_high;
    int32_t catch_count;
    CxxHandlerType* handlers;
};
struct CxxUnwindEntry {
    int32_t enclosing_state;
    void* action;
};
struct CxxFuncInfo {
    uint32_t magic_and_flags;
    int32_t maximum_state;
    CxxUnwindEntry* unwind_map;
    uint32_t try_count;
    CxxTryBlock* try_map;
    uint32_t ip_map_count;
    void* ip_map;
};
struct CxxPointerDisplacement {
    int32_t member;
    int32_t vbtable;
    int32_t vbase;
};
struct CxxCatchableType {
    uint32_t properties;
    const void* type_header;
    CxxPointerDisplacement displacement;
    int32_t size_or_offset;
    void* copy_function;
};
struct CxxCatchableTypes {
    int32_t count;
    CxxCatchableType* first;
};
using CxxForwardHandler = int32_t (*)(OriginalExceptionRecord*, CxxRegistration*, void*, void*,
                                      CxxFuncInfo*, int32_t, void*, uint32_t);
struct CxxThrowInfo {
    uint32_t attributes;
    void* unwind_function;
    CxxForwardHandler forward_handler;
    CxxCatchableTypes* catchable_types;
};
struct CxxCatchGuard {
    void* previous;
    void* dispatcher;
    uint32_t cookie;
    CxxFuncInfo* information;
    CxxRegistration* frame;
    int32_t catch_depth;
};
static_assert(sizeof(CxxRegistration) == 12 && sizeof(CxxFrameInfo) == 8);
static_assert(sizeof(CxxHandlerType) == 16 && sizeof(CxxTryBlock) == 20);
static_assert(sizeof(CxxUnwindEntry) == 8 && sizeof(CxxFuncInfo) == 28);
static_assert(sizeof(CxxCatchableType) == 28 && sizeof(CxxThrowInfo) == 16);
static_assert(sizeof(CxxCatchGuard) == 24);

extern "C" {
extern uint32_t dat_0070e4ec;
extern void (*dat_0070e4f8)();

int32_t fun_005d65d0(const char* left, const char* right);
// Original005D1D76 receives handler inESI, catchable inEDI and only throw_info
// on the cdecl stack. This explicit normalized interface preserves all three.
int32_t fun_005d1d76(const CxxHandlerType*, const CxxCatchableType*, const CxxThrowInfo*);
CxxTryBlock* fun_005ccbee(const CxxFuncInfo*, int32_t catch_depth, int32_t state, uint32_t* first,
                          uint32_t* end);
CxxFrameInfo* fun_005ccc68(CxxFrameInfo*, void* object);
int32_t fun_005ccc90(void* object);
void fun_005cccb1(CxxFrameInfo*);
int32_t fun_005d257e(OriginalExceptionRecord*, CxxRegistration*, void* context,
                     void* dispatcher_context, CxxFuncInfo*, int32_t catch_depth, void* guard_frame,
                     uint32_t recursive);
// The original Windows four-stack-argument handler additionally receives its
// CxxFuncInfo pointer inEAX. The source body is an architectural ABI bridge.
int32_t fun_005cca04(OriginalExceptionRecord*, CxxRegistration*, void*, void*);
int32_t fun_005cca3a(OriginalExceptionRecord*, CxxCatchGuard*, void*, void*);
void* __attribute__((stdcall)) fun_005d29a0(void* action, CxxRegistration*,
                                            uint32_t notification_code);
void __attribute__((stdcall)) fun_005cc9ab(void* object, void* member_function);
// Original005D1EF6 consumes object inEAX and displacement inECX.
void* fun_005d1ef6(void* object, const CxxPointerDisplacement*);
int32_t fun_005d1dc5(OriginalExceptionPointers*);
void fun_005d1e96();
void fun_005d1eb1(OriginalExceptionRecord*, uint32_t terminate_on_exception);
[[noreturn]] void fun_005d292f();
void* fun_005cccfd(CxxRegistration*, CxxFuncInfo*, void* handler, int32_t catch_depth,
                   uint32_t code);
void* fun_005cede4(uint32_t bytes, const void* unused_tag);

// Actual original dependencies are retained explicitly while their bodies are
// recovered. None of these declarations supplies a result or bypass branch.
[[noreturn]] void fun_005d2964();
void fun_005d1de3(CxxRegistration*, void* dispatcher_context, CxxFuncInfo*, int32_t state);
void fun_005d237a(OriginalExceptionRecord*, CxxRegistration*, void* context,
                  void* dispatcher_context, CxxFuncInfo*, uint32_t recursive, int32_t catch_depth,
                  void* guard_frame);
}
