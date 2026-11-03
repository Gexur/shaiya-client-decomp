#include "graphics/render_cpu_probe.h"

// Supported client CPUs provide CPUID, as guaranteed by x86-64. Pre-CPUID
// 32-bit CPUs are outside the client platform requirements. The old probe's
// illegal-instruction handler and inherited scratch registers are unnecessary.
extern "C" uint32_t __cdecl recovered_d3dx_feature_mask() {
    D3dxProbeWords words{0, 0, 0, 0};
    recovered_d3dx_cpuid(&words);
    if (words.eax == 0)
        return 0;
    words.eax = 1;
    recovered_d3dx_cpuid(&words);
    uint32_t result = 0;
    if (words.edx & 0x02000000)
        result |= 4;
    if (words.edx & 0x04000000)
        result |= 8;
    return result;
}
