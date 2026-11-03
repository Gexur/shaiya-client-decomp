// This translation unit requires x86-windows-msvc, -fexceptions and
// -fms-extensions. The generated __except_handler3 / __local_unwind2 references
// remain actual CRT dependencies until their original bodies are recovered.
#include "locks.h"
#include "heap.h"

extern "C" {
using ResolvedWin32Function = int32_t(__attribute__((stdcall)) *)();
__declspec(dllimport) void* __attribute__((stdcall)) GetModuleHandleA(const char*);
__declspec(dllimport) ResolvedWin32Function __attribute__((stdcall)) GetProcAddress(void*,
                                                                                    const char*);
__declspec(dllimport) void __attribute__((stdcall)) SetLastError(uint32_t);
unsigned long _exception_code();
}

extern "C" int32_t fun_005d64fb(int32_t lock_index) {
    OriginalLockEntry* entry = &dat_0070e990[lock_index];
    if (entry->section != nullptr) {
        return 1;
    }
    OriginalCriticalSection* allocated = static_cast<OriginalCriticalSection*>(fun_005cfade(24));
    if (allocated == nullptr) {
        *fun_005d589a() = 12;
        return 0;
    }
    fun_005d659b(10);
    __try {
        if (entry->section != nullptr) {
            fun_005cfaf0(allocated);
        } else {
            if (fun_005de970(allocated, 4000) == 0) {
                fun_005cfaf0(allocated);
                *fun_005d589a() = 12;
                return 0;
            }
            entry->section = allocated;
        }
    } __finally {
        fun_005d6592();
    }
    return 1;
}

extern "C" int32_t fun_005de970(OriginalCriticalSection* section, uint32_t spin_count) {
    CriticalSectionInitializer initialize = dat_0224f2b4;
    if (initialize == nullptr) {
        if (dat_0224ede8 != 1) {
            void* kernel = GetModuleHandleA("kernel32.dll");
            if (kernel != nullptr) {
                initialize = reinterpret_cast<CriticalSectionInitializer>(
                    GetProcAddress(kernel, "InitializeCriticalSectionAndSpinCount"));
                dat_0224f2b4 = initialize;
            }
        }
        if (initialize == nullptr) {
            initialize = fun_005de960;
            dat_0224f2b4 = initialize;
        }
    }
    uint32_t exception_code;
    __try {
        return initialize(section, spin_count);
    } __except ((exception_code = _exception_code(), 1)) {
        if (exception_code == 0xc0000017u) {
            SetLastError(8);
        }
        return 0;
    }
}
