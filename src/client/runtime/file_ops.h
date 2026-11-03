#pragma once
#include "descriptor_io.h"
static inline OriginalIoEntry* file_io_entry(int32_t descriptor) {
    return &dat_022532e0[descriptor >> 5][uint32_t(descriptor) & 31u];
}
extern "C" {
int32_t fun_005cd5ff(int32_t descriptor);
int32_t fun_005cd610(int32_t descriptor, int32_t offset, int32_t origin);
int32_t fun_005cd684(int32_t descriptor, int32_t offset, int32_t origin);
void fun_005cd70b(int32_t descriptor);
int32_t fun_005ce360(int32_t descriptor, char* buffer, uint32_t count);
int32_t fun_005ce53d(int32_t descriptor, void* buffer, uint32_t count);
void fun_005ce5c4(int32_t descriptor);

// Compiler-facing MSVCRT names are adapters to these original recovered bodies.
int32_t _lseek(int32_t descriptor, int32_t offset, int32_t origin);
int32_t _tell(int32_t descriptor);
int32_t _read(int32_t descriptor, void* buffer, uint32_t count);
int32_t _close(int32_t descriptor);
int32_t _open(const char* path, int32_t flags, ...);
}
