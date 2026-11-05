#pragma once
#include "file_ops.h"
extern "C" {
extern uint32_t dat_0224ee74;
extern uint32_t dat_0224ede4;
// Normalized source interface of original 5cd72f, with sharing as an explicit
// final parameter. Native callers use this.
int32_t open_file_descriptor(int32_t* locked, int32_t* descriptor, const char* path,
                             uint32_t flags, uint32_t permissions, uint32_t sharing);
// Original 5cd72f entry for the recovered _sopen (5cda6b): five cdecl stack
// operands with sharing in ECX. It forwards to open_file_descriptor.
int32_t fun_005cd72f(int32_t* locked, int32_t* descriptor, const char* path, uint32_t flags,
                     uint32_t permissions);
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
