#pragma once
#include "file_ops.h"
extern "C" {
extern uint32_t dat_0224ee74;
extern uint32_t dat_0224ede4;
// Original5cd72f uses ECX for sharing and five stack operands; the explicit
// final sharing parameter is its normalized source interface.
int32_t fun_005cd72f(int32_t* locked, int32_t* descriptor, const char* path, uint32_t flags,
                     uint32_t permissions, uint32_t sharing);
int32_t fun_005cda16(const char* path, uint32_t flags, uint32_t permissions);
void fun_005cda5b(int32_t locked, int32_t descriptor);
int32_t fun_005d5b1d(int32_t descriptor, int32_t handle);
int32_t fun_005d5d1b();
void fun_005d5df4();
void fun_005d5e8e();
int32_t fun_005d5e97(int32_t descriptor, int32_t size);
int32_t fun_005de9fb(int32_t descriptor, int32_t mode);
int32_t _open(const char* path, int32_t flags, ...);
}
