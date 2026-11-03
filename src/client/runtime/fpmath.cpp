#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "runtime/fpmath.h"
#include "runtime/security.h"

extern "C" {
void fun_005d098b(int32_t);
int32_t __cdecl FUN_005cdf60(const char*, const char*, uint32_t);
uint32_t dat_0224ede0 = 0, dat_022532d0 = 0;
}

extern "C" void __cdecl fun_005ccfaa(int32_t precision) {
    fun_005ccf72();
    dat_0224ede0 = uint32_t(fun_005d2f7b());
    if (precision != 0)
        fun_005d2f29();
    __asm__ __volatile__("fnclex"); // Actual5ccfc5, omitted by Ghidra's pseudo-C.
}
extern "C" void __cdecl fun_005d2f29() {
    fun_005dd06b(0x10000, 0x30000);
}
extern "C" int32_t __cdecl fun_005d2f3b() {
    // Original volatile double stores precede the actual FDIV/FMUL/FSUBR test.
    // No assumption is made that the processor necessarily passes it.
    const volatile double divisor = 3145727.0;
    const volatile double numerator = 4195835.0;
    const volatile double difference = static_cast<double>(
        static_cast<long double>(numerator) -
        (static_cast<long double>(numerator) / static_cast<long double>(divisor)) *
            static_cast<long double>(divisor));
    return difference > 1.0 ? 1 : 0;
}
extern "C" int32_t __cdecl fun_005d2f7b() {
    HMODULE module = GetModuleHandleA("KERNEL32");
    if (module != nullptr) {
        FARPROC address = GetProcAddress(module, "IsProcessorFeaturePresent");
        if (address != nullptr)
            return reinterpret_cast<BOOL(WINAPI*)(DWORD)>(address)(0);
    }
    return fun_005d2f3b();
}

namespace {
uint32_t abstract_word(uint32_t word) {
    uint32_t value = 0;
    if (word & 1)
        value = 0x10;
    if (word & 4)
        value |= 8;
    if (word & 8)
        value |= 4;
    if (word & 0x10)
        value |= 2;
    if (word & 0x20)
        value |= 1;
    if (word & 2)
        value |= 0x80000;
    value |= (word & 0xc00) >> 2;
    if ((word & 0x300) == 0)
        value |= 0x20000;
    else if ((word & 0x300) == 0x200)
        value |= 0x10000;
    if (word & 0x1000)
        value |= 0x40000;
    return value;
}
uint32_t hardware_word(uint32_t word) {
    uint32_t value = 0;
    if (word & 0x10)
        value = 1;
    if (word & 8)
        value |= 4;
    if (word & 4)
        value |= 8;
    if (word & 2)
        value |= 0x10;
    if (word & 1)
        value |= 0x20;
    if (word & 0x80000)
        value |= 2;
    value |= (word & 0x300) << 2;
    if ((word & 0x30000) == 0)
        value |= 0x300;
    else if ((word & 0x30000) == 0x10000)
        value |= 0x200;
    if (word & 0x40000)
        value |= 0x1000;
    return value;
}
struct CpuIdWords {
    uint32_t eax, ebx, ecx, edx;
};
CpuIdWords cpuid(uint32_t leaf, uint32_t ecx) {
    CpuIdWords result;
    __asm__ __volatile__("cpuid"
                         : "=a"(result.eax), "=b"(result.ebx), "=c"(result.ecx), "=d"(result.edx)
                         : "a"(leaf), "c"(ecx)
                         : "cc");
    return result;
}
struct IdProbe {
    uint32_t flags, changed;
};
IdProbe toggle_id() {
    IdProbe result;
    // Original toggles EFLAGS.ID and tests subtraction from the saved flags.
    // Restore is conditional exactly as the actual successful-toggle branch.
    __asm__ __volatile__(
        "pushfl\n\tpopl %0\n\tmovl %0,%1\n\txorl $0x200000,%1\n\tpushl %1\n\tpopfl\n\tpushfl\n\tpopl %1\n\tsubl %0,%1\n\tjz 1f\n\tpushl %0\n\tpopfl\n\t1:"
        : "=&r"(result.flags), "=&r"(result.changed)::"cc", "memory");
    return result;
}
} // namespace

// Integration adapters retain the original EBX-input entry ABI while the
// actual bit mappings above are expressed in C++ and independently tested.
extern "C" uint32_t __cdecl abstract_cw_005dcf19(uint32_t word) {
    return abstract_word(uint16_t(word));
}
extern "C" uint32_t __cdecl hardware_cw_005dcfab(uint32_t word) {
    return hardware_word(word);
}
extern "C" __attribute__((naked)) uint32_t __cdecl fun_005dcf19() {
    __asm__ __volatile__("pushl %ebx\n\tcall _abstract_cw_005dcf19\n\taddl $4,%esp\n\tretl");
}
extern "C" __attribute__((naked)) uint32_t __cdecl fun_005dcfab() {
    __asm__ __volatile__("pushl %ebx\n\tcall _hardware_cw_005dcfab\n\taddl $4,%esp\n\tretl");
}
extern "C" uint32_t __cdecl fun_005dd039(uint32_t value, uint32_t mask) {
    uint16_t control;
    __asm__ __volatile__("fwait\n\tfnstcw %0" : "=m"(control));
    const uint32_t merged = (abstract_word(control) & ~mask) | (value & mask);
    control = uint16_t(hardware_word(merged));
    __asm__ __volatile__("fldcw %0" ::"m"(control));
    return merged;
}
extern "C" uint32_t __cdecl fun_005dd06b(uint32_t value, uint32_t mask) {
    return fun_005dd039(value, mask & 0xfff7ffffu);
}

extern "C" int32_t __cdecl fun_005d7e84() {
    // Preserve the original cookie/check dependency, with this recompiled
    // routine's real stack slot rather than a fabricated original frame.
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    uint32_t features = 0, version = 0;
    unsigned char vendor[12];
    vendor[0] = 0;
    const IdProbe probe = toggle_id();
    if (probe.changed != 0) {
        CpuIdWords words = cpuid(0, probe.flags);
        const uint32_t parts[] = {words.ebx, words.edx, words.ecx};
        for (uint32_t index = 0; index < 3; ++index)
            for (uint32_t byte = 0; byte < 4; ++byte)
                vendor[index * 4 + byte] = uint8_t(parts[index] >> (byte * 8));
        words = cpuid(1, words.ecx);
        features = words.edx;
        version = words.eax;
    }
    dat_022532d0 = 0;
    dat_022532cc = 0;
    if ((features & 0x4000000) != 0 && fun_005d7e4f() != 0) {
        dat_022532d0 = 1;
        if (FUN_005cdf60("AuthenticAMD", reinterpret_cast<const char*>(vendor), 12) != 0)
            dat_022532cc = 1;
        else {
            const uint32_t family = (version >> 8) & 15;
            const uint32_t effective_family = family + (family == 15 ? ((version >> 20) & 255) : 0);
            if (effective_family != 15)
                dat_022532cc = 1;
        }
    }
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
    return 0;
}
