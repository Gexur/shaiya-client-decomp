#include "graphics/render_cpu_features.h"
#include "graphics/render_cpu_probe.h"

extern "C" uint64_t __cdecl FUN_00651839() {
    D3dxProbeWords words{0, 0, 0, 0};
    recovered_d3dx_cpuid(&words);
    uint32_t flags = 1;
    words.eax = 0;
    recovered_d3dx_cpuid(&words);
    if (words.eax != 0) {
        flags |= 2;
        words.eax = 1;
        recovered_d3dx_cpuid(&words);
        if (words.edx & 0x00800000)
            flags |= 0x20;
        words.ecx = (words.edx & 0x02000000) ? 0x40 : 0;
        flags |= words.ecx;
        words.eax = 0x80000000;
        recovered_d3dx_cpuid(&words);
        if (words.eax > 0x80000000) {
            flags |= 4;
            words.eax = 0x80000001;
            recovered_d3dx_cpuid(&words);
            if (words.edx & 0x80000000)
                flags |= 0x80;
            // Original6518df..6518eb compares12 vendor bytes, then every
            // condition flag is overwritten before any branch or return.
            // The two following feature masks apply regardless of vendor.
            if (words.edx & 0x40000000)
                flags |= 0x100;
            if (words.edx & 0x00400000)
                flags |= 0x200;
        }
    }
    // Original retains the final CPUID EDX while returning flags in EAX.
    return uint64_t(words.edx) << 32 | flags;
}
