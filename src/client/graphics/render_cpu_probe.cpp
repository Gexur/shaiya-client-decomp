#include "graphics/render_cpu_probe.h"
#include <intrin.h>

extern "C" uint32_t __cdecl FUN_005fd157() {
    return recovered_d3dx_feature_mask();
}

extern "C" void __cdecl recovered_d3dx_cpuid(D3dxProbeWords* words) {
    int result[4];
    __cpuidex(result, static_cast<int>(words->eax), static_cast<int>(words->ecx));
    words->eax = static_cast<uint32_t>(result[0]);
    words->ebx = static_cast<uint32_t>(result[1]);
    words->ecx = static_cast<uint32_t>(result[2]);
    words->edx = static_cast<uint32_t>(result[3]);
}
