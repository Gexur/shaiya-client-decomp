#include "crt_exit.h"

extern "C" {
using CorExitProcess = void(__attribute__((stdcall)) *)(uint32_t);
__declspec(dllimport) void* __attribute__((stdcall)) GetModuleHandleA(const char*);
__declspec(dllimport) CorExitProcess __attribute__((stdcall)) GetProcAddress(void*, const char*);
__declspec(dllimport) void __attribute__((stdcall)) ExitProcess(uint32_t);
}

extern "C" [[noreturn]] void fun_005cdf99(int32_t status) {
    void* module = GetModuleHandleA("mscoree.dll");
    if (module != nullptr) {
        CorExitProcess managed_exit = GetProcAddress(module, "CorExitProcess");
        if (managed_exit != nullptr)
            managed_exit(static_cast<uint32_t>(status));
    }
    ExitProcess(static_cast<uint32_t>(status));
    __builtin_unreachable();
}
extern "C" void fun_005ce120(int32_t status) {
    fun_005ce05d(static_cast<uint32_t>(status), 0, 0);
}
extern "C" void FUN_005ce120(int32_t) __attribute__((alias("fun_005ce120")));
extern "C" void fun_005ce131(int32_t status) {
    fun_005ce05d(static_cast<uint32_t>(status), 1, 0);
}
extern "C" void fun_005ce142() {
    fun_005ce05d(0, 0, 1);
}
extern "C" void fun_005ce151() {
    fun_005ce05d(0, 1, 1);
}
