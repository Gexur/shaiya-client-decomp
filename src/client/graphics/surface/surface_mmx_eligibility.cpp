#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "graphics/surface/surface_mmx_eligibility.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
u32 half(u32 p) {
    u32 v;
    __asm__ volatile("movzwl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
} // namespace
extern "C" {
int32_t dat_0070ff00 = -1; // Exact file-backed DWORD; independent of70ff04.
extern const char s_006de914[28] = "Software\\Microsoft\\Direct3D";
extern const char s_006df784[11] = "DisableMMX";
}
// Complete40-byte original5fd07d..5fd0a5. PUSHAL retains the actual full
// register set around CPUID; TEST flags survive POPAL for the final SETNE.
extern "C" __attribute__((naked)) uint32_t __cdecl FUN_005fd07d() {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl %ecx\n\tpushl %ebx\n\tpushl %esi\n\tpushl %edi\n\txorl %eax,%eax\n\tpushal\n\tmovl $1,%eax\n\tcpuid\n\ttestl $0x800000,%edx\n\tpopal\n\tsetne %al\n\tmovl %eax,-4(%ebp)\n\tmovl -4(%ebp),%eax\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tleave\n\tretl");
}
// Complete5fd0a5..5fd157. The raw52-byte original private area retains the
// actual uninitialized API outputs; no default type/value/SYSTEM_INFO is added.
extern "C" int32_t recovered_005fd0a5(unsigned char* scratch) {
    const u32 frame = reinterpret_cast<uintptr_t>(scratch),
              cache = reinterpret_cast<uintptr_t>(&dat_0070ff00);
    auto* key = reinterpret_cast<HKEY*>(frame + 48);
    if (RegOpenKeyA(HKEY_LOCAL_MACHINE, s_006de914, key) == ERROR_SUCCESS) {
        const HKEY current = reinterpret_cast<HKEY>(word(frame + 48));
        put(frame + 44, 4);
        const LSTATUS query = RegQueryValueExA(
            current, s_006df784, nullptr, reinterpret_cast<DWORD*>(frame + 40),
            reinterpret_cast<BYTE*>(frame + 36), reinterpret_cast<DWORD*>(frame + 44));
        if (query == ERROR_SUCCESS && word(frame + 40) == REG_DWORD && word(frame + 36) != 0) {
            RegCloseKey(reinterpret_cast<HKEY>(word(frame + 48)));
            put(cache, 0);
            return 0;
        }
        RegCloseKey(reinterpret_cast<HKEY>(word(frame + 48)));
    }
    if (word(cache) & 0x80000000u) {
        put(cache, 0);
        GetSystemInfo(reinterpret_cast<SYSTEM_INFO*>(frame));
        if (half(frame) == 0 && half(frame + 32) >= 5 && FUN_005fd07d() != 0) {
            __asm__ volatile("emms" ::: "memory");
            put(cache, 1);
        }
    }
    return static_cast<int32_t>(word(cache));
}
extern "C" __attribute__((naked)) int32_t __cdecl FUN_005fd0a5() {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tsubl $52,%esp\n\tpushl %edi\n\tleal -52(%ebp),%eax\n\tpushl %eax\n\tcalll _recovered_005fd0a5\n\taddl $4,%esp\n\tpopl %edi\n\tleave\n\tretl");
}
