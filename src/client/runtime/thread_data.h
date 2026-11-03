#pragma once
#include <stdint.h>
#include <stddef.h>
#include "locale.h"

struct OriginalExceptionAction {
    uint32_t exception_code;
    int32_t signal_number;
    void* action;
};
struct OriginalPerThreadData {
    uint32_t thread_id;     // +00
    uint32_t thread_handle; // +04
    int32_t error_number;   // +08
    uint8_t undecoded_0c[8];
    uint32_t random_state; // +14
    uint8_t undecoded_18[12];
    void* allocation_24;
    uint8_t undecoded_28[4];
    void* allocation_2c;
    uint8_t undecoded_30[4];
    void* allocation_34;
    uint8_t undecoded_38[4];
    void* allocation_3c;
    uint8_t undecoded_40[4];
    void* allocation_44;
    void* allocation_48;
    uint8_t undecoded_4c[8];
    OriginalExceptionAction* exception_actions; // +54
    uint8_t undecoded_58[8];
    int32_t* reference_counted_60;
    void* locale_64;
    uint8_t undecoded_68[0x24];
};
static_assert(sizeof(OriginalExceptionAction) == 12);
static_assert(sizeof(OriginalPerThreadData) == 0x8c);
static_assert(offsetof(OriginalPerThreadData, error_number) == 8);
static_assert(offsetof(OriginalPerThreadData, random_state) == 0x14);
static_assert(offsetof(OriginalPerThreadData, exception_actions) == 0x54);
static_assert(offsetof(OriginalPerThreadData, reference_counted_60) == 0x60);
static_assert(offsetof(OriginalPerThreadData, locale_64) == 0x64);

using OriginalFlsDestructor = void(__attribute__((stdcall)) *)(void*);
using OriginalFlsAlloc = uint32_t(__attribute__((stdcall)) *)(OriginalFlsDestructor);
using OriginalFlsGet = void*(__attribute__((stdcall)) *)(uint32_t);
using OriginalFlsSet = int32_t(__attribute__((stdcall)) *)(uint32_t, void*);
using OriginalFlsFree = int32_t(__attribute__((stdcall)) *)(uint32_t);

extern "C" {
extern uint32_t dat_0070e4f4;
extern OriginalFlsAlloc dat_0224ee50;
extern OriginalFlsGet dat_0224ee54;
extern OriginalFlsSet dat_0224ee58;
extern OriginalFlsFree dat_0224ee5c;
extern OriginalExceptionAction dat_0070ed30[10];

uint32_t __attribute__((stdcall)) fun_005d2620(OriginalFlsDestructor ignored_destructor);
void fun_005d2629();
void fun_005d2646(OriginalPerThreadData*);
void* fun_005d2659();
void __attribute__((stdcall)) fun_005d26ca(void* per_thread_data);
void fun_005d27fc();
void fun_005d2808();
void fun_005d2811(void* optional_per_thread_data);
int32_t fun_005d2840();
}
