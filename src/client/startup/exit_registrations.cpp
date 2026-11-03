#include "exit_registrations.h"

// Genuine original CRT dependency at 0x5ccf60, identified by REA as cdecl
// atexit(callback). Its allocator/registry implementation is not replaced here.
extern "C" int __cdecl atexit(void(__cdecl* callback)());

// These four original callback bodies each consist of exactly one RET at the
// named address. They are recovered empty functions, not placeholder bodies for
// unknown destructor behavior. Original initializer pointers prove their use.
extern "C" void __cdecl fun_006b7b30() {}
extern "C" void __cdecl fun_006b7b40() {}
extern "C" void __cdecl fun_006b7b50() {}
extern "C" void __cdecl fun_006b7b60() {}

// Preserve the individual registrations and their distinct callback identities.
// Original initializers ignore atexit's result; no failure handling is invented.
extern "C" void __cdecl fun_006b5660() {
    (void)atexit(fun_006b7b30);
}
extern "C" void __cdecl fun_006b5670() {
    (void)atexit(fun_006b7b40);
}
extern "C" void __cdecl fun_006b5680() {
    (void)atexit(fun_006b7b50);
}
extern "C" void __cdecl fun_006b5690() {
    (void)atexit(fun_006b7b60);
}
