#pragma once
#include "io.h"
struct OriginalDosError {
    uint32_t system_error;
    int32_t c_error;
};
extern "C" {
extern uint32_t dat_0070e4d4;
extern const OriginalDosError dat_0070e800[45];
uint32_t* fun_005d58a3();
void fun_005d58ac(uint32_t error);
int32_t fun_005d5b99(int32_t descriptor);
int32_t fun_005d5c18(int32_t descriptor);
int32_t fun_005d5c59(int32_t descriptor);
void fun_005d5cf0();
void fun_005d5cf9(int32_t descriptor);
int64_t fun_005ce21f(int32_t descriptor, int32_t low, int32_t high, uint32_t origin);
int32_t fun_005cd4e1(int32_t descriptor);
int32_t fun_005cd564(int32_t descriptor);
void fun_005cd5db(int32_t descriptor);
int32_t fun_005d0c62(int32_t descriptor, const char* buffer, uint32_t count);
int32_t fun_005d0e1e(int32_t descriptor, const void* buffer, uint32_t count);
void fun_005d0ea5(int32_t descriptor);
int32_t fun_005da4cf(int32_t descriptor);
void fun_005da56f(int32_t descriptor);
}
inline OriginalIoEntry* original_io_entry(int32_t descriptor) {
    return &dat_022532e0[descriptor >> 5][uint32_t(descriptor) & 31u];
}
