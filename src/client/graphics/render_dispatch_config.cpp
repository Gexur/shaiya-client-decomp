#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "graphics/render_dispatch_config.h"

extern "C" int32_t __attribute__((stdcall)) FUN_005fd01e(uint32_t expected_type, const char* name,
                                                         void* output, uint32_t capacity) {
    HKEY key = nullptr;
    if (RegOpenKeyA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Direct3D", &key) != ERROR_SUCCESS)
        return 0;
    // Original API overwrites the caller-argument slot which initially held
    // output; retain that exact initial DWORD if the API leaves type untouched.
    DWORD type = static_cast<DWORD>(reinterpret_cast<uintptr_t>(output));
    DWORD bytes = capacity;
    const LSTATUS status =
        RegQueryValueExA(key, name, nullptr, &type, static_cast<BYTE*>(output), &bytes);
    RegCloseKey(key);
    return status == ERROR_SUCCESS && type == expected_type ? 1 : 0;
}
