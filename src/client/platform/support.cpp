#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "../runtime/file_ops.h"

#include "support.hpp"

// Recovered from client/game.exe SHA256
// 796af141fd13451bab67ae0bae02d2177b1fe60af51775f296bec7b0eff752da.
// Binary instructions and dependency locations:
// evidence/cpp-platform-original-disassembly.txt, cpp-platform-recovery.json.
static_assert(sizeof(void*) == 4);
static_assert(sizeof(long) == 4);
static_assert(sizeof(MSG) == 0x1c);
static_assert(__builtin_offsetof(MSG, hwnd) == 0);

extern "C" unsigned int __cdecl FUN_00409ff0() {
    // 0x00409ff0..0x0040a033. The ANSI path excludes null-window messages
    // from translation/dispatch, while still reporting a consumed message.
    MSG message;
    if (PeekMessageA(&message, nullptr, 0, 0, 1)) {
        if (message.hwnd != nullptr) {
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }
        return 1;
    }
    return 0;
}

extern "C" unsigned int __cdecl FUN_0040cf40() {
    // 0x0040cf40..0x0040cf7c. Unlike 0x409ff0, the binary has no HWND guard.
    MSG message;
    if (PeekMessageW(&message, nullptr, 0, 0, 1)) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
        return 1;
    }
    return 0;
}

extern "C" long __cdecl FUN_0040a040(const char* path) {
    // 0x0040a040..0x0040a077. Seek and close results are intentionally ignored;
    // the original returns tell's result, including an error, after open succeeds.
    long length = 0;
    int descriptor = _open(path, 0);
    if (descriptor != -1) {
        _lseek(descriptor, 0, 2);
        length = _tell(descriptor);
        _close(descriptor);
    }
    return length;
}

extern "C" int __cdecl FUN_0040d020(void* buffer, unsigned int element_size,
                                    unsigned int element_count, int descriptor) {
    // 0x0040d020..0x0040d03c. IMUL retains the low 32 product bits, and EAX
    // from _read is returned directly. The bulk decompiler's void type loses
    // that observed return value. Unsigned multiplication preserves wrapping.
    return _read(descriptor, buffer, element_size * element_count);
}
