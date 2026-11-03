#include "entry.h"
#include "heap.h"
#include "thread_data.h"

struct HINSTANCE__;
using ModuleHandleQuery = HINSTANCE__*(__attribute__((stdcall)) *)(const char*);
extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall)) GetVersionExA(void* version);
// Bind the actual import slot as data so the compiler retains the original
// one-time capture; a dllimport function expression may reload the slot later.
extern ModuleHandleQuery imported_get_module __asm__("__imp__GetModuleHandleA@4");
__declspec(dllimport) char* __attribute__((stdcall)) GetCommandLineA();
__declspec(dllimport) void __attribute__((stdcall)) GetStartupInfoA(void* startup_info);
unsigned long _exception_code();
void* _exception_info();

void fun_005d09b0(int32_t error);
void fun_005d098b(int32_t error);
void fun_005d672e();
int32_t fun_005d591f();
void* fun_005dbd3a();
int32_t fun_005dbc98();
int32_t fun_005dba65();
int32_t fun_005cdff3(int32_t initialize);
char* fun_005dba08();
int32_t __attribute__((stdcall)) run_client_application(HINSTANCE__*, HINSTANCE__*, char*, int32_t);
void fun_005ce120(int32_t status);
void fun_005ce131(int32_t status);
void fun_005ce142();
void fun_005ce151();
int32_t fun_005d8af4(uint32_t exception_code, void* exception_pointers);
}

namespace {
uint32_t raw32(const void* storage, uint32_t offset) {
    uint32_t value;
    const auto* pointer = static_cast<const uint8_t*>(storage) + offset;
    // GetVersionExA failure leaves private stack bytes unspecified in the
    // original. Preserve actual byte reads instead of inventing default fields.
    __asm__ volatile("movl (%1), %0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
uint32_t raw16(const void* storage, uint32_t offset) {
    uint32_t value;
    const auto* pointer = static_cast<const uint8_t*>(storage) + offset;
    __asm__ volatile("movzwl (%1), %0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
bool managed_image(HINSTANCE__* module) {
    if (raw16(module, 0) != 0x5a4d)
        return false;
    const auto* nt = reinterpret_cast<const uint8_t*>(module) + raw32(module, 0x3c);
    if (raw32(nt, 0) != 0x4550)
        return false;
    const uint32_t magic = raw16(nt, 0x18);
    if (magic == 0x10b)
        return raw32(nt, 0x74) > 14 && raw32(nt, 0xe8) != 0;
    if (magic == 0x20b)
        return raw32(nt, 0x84) > 14 && raw32(nt, 0xf8) != 0;
    return false;
}
} // namespace

// Genuine original PE entry5d09d4, including its protected startup interval,
// managed-image exit decision, original exception filter and quick-exit path.
// This remains an unlinked source routine until all real dependencies exist.
extern "C" int32_t fun_005d09d4() {
    alignas(4) uint8_t version[0x94];
    *reinterpret_cast<uint32_t*>(version) = 0x94;
    GetVersionExA(version);
    dat_0224ede8 = raw32(version, 0x10);
    dat_0224edf4 = raw32(version, 4);
    dat_0224edf8 = raw32(version, 8);
    dat_0224edec = raw32(version, 0x0c) & 0x7fff;
    if (dat_0224ede8 != 2)
        dat_0224edec |= 0x8000;
    dat_0224edf0 = (dat_0224edf4 << 8) + dat_0224edf8;
    // The original captures this IAT target once and reuses it for WinMain.
    ModuleHandleQuery const get_module = imported_get_module;
    const bool managed = managed_image(get_module(nullptr));
    if (fun_005d9717(1) == 0)
        fun_005d09b0(28);
    if (fun_005d2840() == 0)
        fun_005d09b0(16);
    fun_005d672e();
    uint32_t exception_code;
    int32_t status;
    __try {
        if (fun_005d591f() < 0)
            fun_005d098b(27);
        dat_02253620 = GetCommandLineA();
        dat_0224ee38 = fun_005dbd3a();
        if (fun_005dbc98() < 0)
            fun_005d098b(8);
        if (fun_005dba65() < 0)
            fun_005d098b(9);
        const int32_t initialized = fun_005cdff3(1);
        if (initialized != 0)
            fun_005d098b(initialized);
        alignas(4) uint8_t startup[0x44];
        *reinterpret_cast<uint32_t*>(startup + 0x2c) = 0;
        GetStartupInfoA(startup);
        char* command_line = fun_005dba08();
        const uint32_t show = (raw32(startup, 0x2c) & 1) != 0 ? raw16(startup, 0x30) : 10;
        status = run_client_application(get_module(nullptr), nullptr, command_line,
                                        static_cast<int32_t>(show));
        if (!managed)
            fun_005ce120(status);
        fun_005ce142();
    } __except (
        (exception_code = _exception_code(), fun_005d8af4(exception_code, _exception_info()))) {
        status = static_cast<int32_t>(exception_code);
        if (!managed)
            fun_005ce131(status);
        fun_005ce151();
    }
    return status;
}
