#pragma once
#include "core/string.h"
extern "C" {
shaiya::startup::String_00405710* FUN_005b8f80(shaiya::startup::String_00405710* output,
                                               const shaiya::startup::String_00405710* left,
                                               const shaiya::startup::String_00405710* right);
shaiya::startup::String_00405710* FUN_005b90d0(shaiya::startup::String_00405710* output,
                                               const char* left,
                                               const shaiya::startup::String_00405710* right);
shaiya::startup::String_00405710* __attribute__((thiscall))
FUN_005bef20(const shaiya::startup::String_00405710* self, shaiya::startup::String_00405710* output,
             uint32_t position, uint32_t count);
uint32_t __attribute__((thiscall)) FUN_005bfb80(const shaiya::startup::String_00405710* self,
                                                const char* text, uint32_t position,
                                                uint32_t count);
shaiya::startup::String_00405710* FUN_005c3e50(shaiya::startup::String_00405710* output,
                                               const shaiya::startup::String_00405710* path,
                                               shaiya::startup::String_00405710* filename);
}
