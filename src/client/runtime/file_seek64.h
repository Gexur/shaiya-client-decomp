#pragma once
#include "file_ops.h"
extern "C" {
int64_t fun_005ce2a2(int32_t descriptor, int64_t offset, int32_t origin);
int64_t fun_005ce731(int32_t descriptor);
// Original normal entry consumes EBX=descriptor; the compiler unwind entry
//005CE337 reloads it from the protected parent frame. This API makes it explicit.
void fun_005ce33a(int32_t descriptor);
int64_t _lseeki64(int32_t descriptor, int64_t offset, int32_t origin);
int64_t _telli64(int32_t descriptor);
}
