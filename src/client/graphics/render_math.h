#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9types.h>
extern "C" {
D3DMATRIX* __attribute__((stdcall)) FUN_005e65c3(D3DMATRIX*, float, float, float, float);
D3DMATRIX* __attribute__((stdcall)) FUN_005e646b(D3DMATRIX*, const void*, const void*, const void*);
}
