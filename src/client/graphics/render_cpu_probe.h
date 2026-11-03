#pragma once
#include <stdint.h>
struct D3dxProbeWords {
    uint32_t eax, ebx, ecx, edx;
};
extern "C" {
uint32_t __cdecl FUN_005fd157();
uint32_t __cdecl recovered_d3dx_feature_mask();
// EAX selects the leaf and ECX its subleaf; all four fields receive the result.
void __cdecl recovered_d3dx_cpuid(D3dxProbeWords*);
}
