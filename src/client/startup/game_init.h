#pragma once
#include <stdint.h>
#include "archive/saf.h"

namespace shaiya::startup {
struct CallbackObject_00405cc0;
using Callback_004 = uint32_t(__attribute__((thiscall)) *)(CallbackObject_00405cc0*, uint32_t);
struct CallbackVtable_00405cc0 {
    void* unknown_000;
    Callback_004 callback_004;
};
struct CallbackObject_00405cc0 {
    CallbackVtable_00405cc0* callbacks;
};
static_assert(__builtin_offsetof(CallbackVtable_00405cc0, callback_004) == 4);
using StreamFields_00719e80 =
    OriginalSafFile; // Existing caller prefix now uses the canonical SAF record.
} // namespace shaiya::startup

extern "C" {
extern shaiya::startup::CallbackObject_00405cc0* dat_007191d4;
extern void* dat_00719318;
extern void* dat_0071931c;

// Actual GameInit caller control flow. Original constructor-failure unwind
// cleanups/FS registration remain pending; no guessed session/renderer exists.
__declspec(dllexport) int32_t __cdecl FUN_0040b2d0();
}
