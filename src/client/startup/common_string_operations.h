#pragma once
#include "core/string.h"
extern "C" {
shaiya::startup::String_00405710* __attribute__((thiscall))
FUN_005341e0(shaiya::startup::String_00405710*, const char*, uint32_t);
shaiya::startup::String_00405710* FUN_005b9020(shaiya::startup::String_00405710* output,
                                               const shaiya::startup::String_00405710* left,
                                               const char* right);
uint32_t __attribute__((thiscall)) FUN_005bece0(const shaiya::startup::String_00405710*,
                                                const void*, uint32_t, uint32_t);
uint32_t __attribute__((thiscall)) FUN_005bed70(const shaiya::startup::String_00405710*,
                                                const void*, uint32_t, uint32_t);
uint32_t __attribute__((thiscall)) FUN_005bedf0(const shaiya::startup::String_00405710*,
                                                const void*, uint32_t, uint32_t);
shaiya::startup::String_00405710* FUN_005befd0(shaiya::startup::String_00405710*);
void* fun_005d12f0(const void*, int32_t, uint32_t);
void fun_006bac70();
extern shaiya::startup::String_00405710 dat_0224eaac;
extern uint32_t dat_0224eac8;
}
