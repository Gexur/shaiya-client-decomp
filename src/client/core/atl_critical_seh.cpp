#include "atl_modules.h"
extern "C" {
__declspec(dllimport) void __attribute__((stdcall))
InitializeCriticalSection(OriginalCriticalSection*);
unsigned long _exception_code();
}
// Original filter0051A7F4 accepts every exception and retains its actual code.
// Its handler maps STATUS_NO_MEMORY to8007000E, all other codes to80004005.
extern "C" int32_t __attribute__((thiscall)) fun_0051a7c0(OriginalCriticalSection* self) {
    uint32_t exception_code;
    __try {
        InitializeCriticalSection(self);
    } __except ((exception_code = _exception_code(), 1)) {
        return int32_t(exception_code == 0xc0000017u ? 0x8007000eu : 0x80004005u);
    }
    return 0;
}
