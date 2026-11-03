#pragma once
#include "core/string.h"
// Original thiscall; source, position, count occupy three actual DWORD slots.
// Returns self in EAX and removes twelve argument bytes.
extern "C" shaiya::startup::String_00405710* __attribute__((thiscall))
FUN_00533d50(shaiya::startup::String_00405710* self, const shaiya::startup::String_00405710* source,
             uint32_t position, uint32_t count);
