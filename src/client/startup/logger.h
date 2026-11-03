#pragma once
#include "archive/saf_open.h"
#include "../runtime/stdio.h"
#include "../core/log_level_names.h"
#include "global_tree48_map.h"
#include "global_ownership.h"
// Original5B8F10 initializes these two exact28-byte string subobjects. This is
// the same64-byte logger used by the existing SAF consumer interface.
struct OriginalSafLogger {
    OriginalFile* file;
    shaiya::startup::String_00405710 name, path;
    uint32_t flags;
};
static_assert(sizeof(OriginalSafLogger) == 64 && offsetof(OriginalSafLogger, name) == 4 &&
              offsetof(OriginalSafLogger, path) == 0x20 &&
              offsetof(OriginalSafLogger, flags) == 0x3c);
struct OriginalLogListener;
using OriginalLogNotification = void(__attribute__((thiscall)) *)(
    OriginalLogListener*, const shaiya::startup::String_00405710*, uint32_t, const char*,
    const char*, uint32_t, const shaiya::startup::String_00405710*);
struct OriginalLogListenerVtable {
    void* deleting_destructor;
    OriginalLogNotification notify;
};
struct OriginalLogListener {
    OriginalLogListenerVtable* vtable;
};
extern "C" {
extern OriginalSafLogger dat_0224e6c0;
extern uint8_t dat_0224e6b8;
OriginalSafLogger* __attribute__((thiscall))
fun_005b8f10(OriginalSafLogger*, const shaiya::startup::String_00405710* name, uint32_t flags);
void __attribute__((thiscall)) fun_005b9bd0(OriginalSafLogger*);
void fun_006b77b0();
void fun_006bab80();
void fun_005b8b80(const shaiya::startup::String_00405710* name, uint32_t flags,
                  const char* function, const char* file, uint32_t line,
                  const shaiya::startup::String_00405710* message);
// Real application dependencies. These declarations supply no substitute body.
OriginalSafLogger* fun_005bacc0(const shaiya::startup::String_00405710* name, uint32_t flags);
void __attribute__((thiscall)) fun_005b9180(OriginalSafLogger*);
const char* fun_005c3a00(const char* format);
}
