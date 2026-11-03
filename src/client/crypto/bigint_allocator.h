#pragma once

#include "bigint.h"

using BigIntAllocate = void*(__attribute__((cdecl)) *)(uint32_t bytes);
using BigIntReallocate = void*(__attribute__((cdecl)) *)(void* pointer, uint32_t old_bytes,
                                                         uint32_t new_bytes);
using BigIntFree = void(__attribute__((cdecl)) *)(void* pointer, uint32_t bytes);
static_assert(__is_same(decltype(dat_0070c0d0), BigIntAllocate));
static_assert(__is_same(decltype(dat_0070c0d4), BigIntReallocate));
static_assert(__is_same(decltype(dat_0070c0d8), BigIntFree));

extern "C" {
SHAIYA_BIGINT_EXPORT void* fun_00586ea0(uint32_t bytes);
SHAIYA_BIGINT_EXPORT void* fun_00586ed0(void* pointer, uint32_t old_bytes, uint32_t new_bytes);
SHAIYA_BIGINT_EXPORT void fun_00586f10(void* pointer, uint32_t bytes);

// Actual original CRT boundaries. Their heap, stream, formatting and process
// termination implementations remain unrecovered; these declarations supply no
// successful allocation, fake FILE object, diagnostic, or fatal-path substitute.
struct OriginalCrtFile;
extern OriginalCrtFile dat_0070e280; // original CRT stderr stream storage
void* fun_005cfade(uint32_t bytes);  // original malloc
void fun_005cfaf0(void* pointer);    // original free, which returns normally
int fun_005cdb8c(OriginalCrtFile* stream, const char* format, ...); // narrow fprintf
[[noreturn]] void fun_005d0ba9();                                   // original abort
}
