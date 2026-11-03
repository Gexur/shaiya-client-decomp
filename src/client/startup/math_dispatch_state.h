#pragma once
#include <stdint.h>
// Address-only callback storage. Unknown callable parameter/return types are
// deliberately not invented; known callers cast only their evidenced slot ABI.
using D3dxCodeAddress = void(__cdecl*)();
struct D3dxDispatchTable {
    D3dxCodeAddress entries[74];
};
static_assert(sizeof(D3dxDispatchTable) == 0x128);
extern "C" {
extern D3dxDispatchTable dat_0070f370, dat_0070f498;
extern uint32_t dat_0070ff04;
D3dxDispatchTable* __attribute__((stdcall)) FUN_0064f62a(D3dxDispatchTable*);
int32_t __attribute__((stdcall)) FUN_005fd1f8(int32_t);
}
