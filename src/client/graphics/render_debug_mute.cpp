#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "graphics/render_debug_mute.h"
#include "graphics/render_dispatch_config.h"
extern "C" {
DebugMuteCodeAddress dat_0224f358 = nullptr, dat_0224f354 = nullptr;
int32_t dat_0070f5c0 = -1;
const char dat_006de95c[9] = "d3d9.dll", dat_006de940[10] = "d3d9d.dll",
           dat_006de94c[13] = "DebugSetMute", dat_006de930[14] = "D3DXDoNotMute";
using Module = HMODULE(WINAPI*)(LPCSTR);
using Procedure = FARPROC(WINAPI*)(HMODULE, LPCSTR);
extern Module imported_mute_get_module __asm__("__imp__GetModuleHandleA@4");
extern Module imported_mute_load_library __asm__("__imp__LoadLibraryA@4");
extern Procedure imported_mute_get_proc __asm__("__imp__GetProcAddress@8");
}
namespace {
using u32 = uint32_t;
u32 word(const void* p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(void* p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
u32 call_mute(u32 callback, u32 value) {
    u32 result;
    // Original uses cdecl PUSH/CALL/POP. EAX is residual machine state; no C++
    // return type is invented for the external DebugSetMute implementation.
    __asm__ volatile("pushl %2\n\tcalll *%1\n\tpopl %%ecx"
                     : "=a"(result)
                     : "r"(callback), "r"(value)
                     : "ecx", "edx", "cc", "memory");
    return result;
}
} // namespace
// Complete original005e9b1d..005e9bf2. Imported LoadLibrary/GetProc targets are
// captured only after the first GetModuleHandle returns; the second module
// query and both callback slots/arguments remain fresh reads.
extern "C" uint32_t recovered_005e9b1d(const uint32_t* argument, uint32_t incoming_eax) {
    u32 result = incoming_eax;
    if (word(&dat_0224f358) == 0 && word(&dat_0224f354) == 0) {
        result = reinterpret_cast<u32>(
            reinterpret_cast<Module>(word(&imported_mute_get_module))(dat_006de95c));
        const auto procedure = reinterpret_cast<Procedure>(word(&imported_mute_get_proc));
        const auto load = reinterpret_cast<Module>(word(&imported_mute_load_library));
        if (result) {
            result = reinterpret_cast<u32>(load(dat_006de95c));
            if (result) {
                result = reinterpret_cast<u32>(
                    procedure(reinterpret_cast<HMODULE>(result), dat_006de94c));
                put(&dat_0224f358, result);
            }
        }
        result = reinterpret_cast<u32>(
            reinterpret_cast<Module>(word(&imported_mute_get_module))(dat_006de940));
        if (result) {
            result = reinterpret_cast<u32>(load(dat_006de940));
            if (result) {
                result = reinterpret_cast<u32>(
                    procedure(reinterpret_cast<HMODULE>(result), dat_006de94c));
                put(&dat_0224f354, result);
            }
        }
    }
    if (word(&dat_0070f5c0) == 0xffffffffu) {
        result = static_cast<u32>(FUN_005fd01e(4, dat_006de930, &dat_0070f5c0, 4));
        if (result == 0)
            __asm__ volatile("andl %1,%0" : "+m"(dat_0070f5c0) : "r"(result) : "cc", "memory");
        if (word(&dat_0070f5c0) != 0)
            put(&dat_0070f5c0, 1);
        else
            goto callbacks;
    }
    if (word(&dat_0070f5c0) != 0)
        return result;
callbacks:
    result = word(&dat_0224f358);
    if (result)
        result = call_mute(result, word(argument));
    result = word(&dat_0224f354);
    if (result)
        result = call_mute(result, word(argument));
    return result;
}
extern "C" __attribute__((naked, stdcall)) void FUN_005e9b1d(uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%edx\n\tpushl %eax\n\tpushl %edx\n\tcalll _recovered_005e9b1d\n\taddl $8,%esp\n\tretl $4");
}
