#include "thread_data.h"
#include "locks.h"
#include "allocations.h"

extern "C" {
using Win32Function = int32_t(__attribute__((stdcall)) *)();
__declspec(dllimport) uint32_t __attribute__((stdcall)) TlsAlloc();
__declspec(dllimport) void* __attribute__((stdcall)) TlsGetValue(uint32_t);
__declspec(dllimport) int32_t __attribute__((stdcall)) TlsSetValue(uint32_t, void*);
__declspec(dllimport) int32_t __attribute__((stdcall)) TlsFree(uint32_t);
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetLastError();
__declspec(dllimport) void __attribute__((stdcall)) SetLastError(uint32_t);
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetCurrentThreadId();
__declspec(dllimport) void* __attribute__((stdcall)) GetModuleHandleA(const char*);
__declspec(dllimport) Win32Function __attribute__((stdcall)) GetProcAddress(void*, const char*);

uint32_t dat_0070e4f4 = 0xffffffffu;
OriginalFlsAlloc dat_0224ee50 = nullptr;
OriginalFlsGet dat_0224ee54 = nullptr;
OriginalFlsSet dat_0224ee58 = nullptr;
OriginalFlsFree dat_0224ee5c = nullptr;
OriginalExceptionAction dat_0070ed30[10] = {{0xc0000005u, 11, nullptr}, {0xc000001du, 4, nullptr},
                                            {0xc0000096u, 4, nullptr},  {0xc000008du, 8, nullptr},
                                            {0xc000008eu, 8, nullptr},  {0xc000008fu, 8, nullptr},
                                            {0xc0000090u, 8, nullptr},  {0xc0000091u, 8, nullptr},
                                            {0xc0000092u, 8, nullptr},  {0xc0000093u, 8, nullptr}};
}

extern "C" uint32_t __attribute__((stdcall)) fun_005d2620(OriginalFlsDestructor) {
    return TlsAlloc();
}

extern "C" void fun_005d2629() {
    if (dat_0070e4f4 != 0xffffffffu) {
        dat_0224ee5c(dat_0070e4f4);
        dat_0070e4f4 = 0xffffffffu;
    }
    fun_005d6491();
}

extern "C" void fun_005d2646(OriginalPerThreadData* data) {
    data->exception_actions = dat_0070ed30;
    data->random_state = 1;
}

extern "C" void* fun_005d2659() {
    uint32_t saved_error = GetLastError();
    auto* data = static_cast<OriginalPerThreadData*>(dat_0224ee54(dat_0070e4f4));
    if (data == nullptr) {
        data = static_cast<OriginalPerThreadData*>(fun_005d8c58(1, 0x8c));
        if (data != nullptr && dat_0224ee58(dat_0070e4f4, data) != 0) {
            data->exception_actions = dat_0070ed30;
            data->random_state = 1;
            uint32_t thread_id = GetCurrentThreadId();
            data->thread_handle = 0xffffffffu;
            data->thread_id = thread_id;
        } else {
            fun_005d098b(16);
        }
    }
    SetLastError(saved_error);
    return data;
}

extern "C" void fun_005d27fc() {
    fun_005d64e6(13);
}
extern "C" void fun_005d2808() {
    fun_005d64e6(12);
}

extern "C" void fun_005d2811(void* data) {
    if (dat_0070e4f4 != 0xffffffffu) {
        if (data == nullptr)
            data = dat_0224ee54(dat_0070e4f4);
        fun_005d26ca(data);
        dat_0224ee58(dat_0070e4f4, nullptr);
    }
}

extern "C" int32_t fun_005d2840() {
    if (fun_005d6448() == 0) {
        fun_005d2629();
        return 0;
    }
    void* kernel = GetModuleHandleA("kernel32.dll");
    if (kernel != nullptr) {
        dat_0224ee50 = reinterpret_cast<OriginalFlsAlloc>(GetProcAddress(kernel, "FlsAlloc"));
        dat_0224ee54 = reinterpret_cast<OriginalFlsGet>(GetProcAddress(kernel, "FlsGetValue"));
        dat_0224ee58 = reinterpret_cast<OriginalFlsSet>(GetProcAddress(kernel, "FlsSetValue"));
        dat_0224ee5c = reinterpret_cast<OriginalFlsFree>(GetProcAddress(kernel, "FlsFree"));
        if (dat_0224ee54 == nullptr) {
            dat_0224ee54 = TlsGetValue;
            dat_0224ee58 = TlsSetValue;
            dat_0224ee50 = fun_005d2620;
            dat_0224ee5c = TlsFree;
        }
    }
    // The original checks neither the other three resolved FLS pointers nor
    // GetModuleHandleA failure before this indirect call. Preserve that branch.
    dat_0070e4f4 = dat_0224ee50(fun_005d26ca);
    if (dat_0070e4f4 != 0xffffffffu) {
        auto* data = static_cast<OriginalPerThreadData*>(fun_005d8c58(1, 0x8c));
        if (data != nullptr && dat_0224ee58(dat_0070e4f4, data) != 0) {
            data->exception_actions = dat_0070ed30;
            data->random_state = 1;
            uint32_t thread_id = GetCurrentThreadId();
            data->thread_handle = 0xffffffffu;
            data->thread_id = thread_id;
            return 1;
        }
    }
    fun_005d2629();
    return 0;
}
