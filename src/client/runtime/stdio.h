#pragma once
#include <stdint.h>
#include <stddef.h>
#include "locks.h"

struct OriginalFile {
    char* cursor;
    int32_t count;
    char* base;
    uint32_t flags;
    int32_t descriptor;
    uint32_t character_buffer;
    int32_t buffer_size;
    char* temporary_name;
};
struct OriginalDynamicFile {
    OriginalFile file;
    OriginalCriticalSection section;
};
static_assert(sizeof(OriginalFile) == 32);
static_assert(offsetof(OriginalFile, flags) == 12);
static_assert(offsetof(OriginalDynamicFile, section) == 32);
extern "C" {
extern OriginalFile dat_0070e240[20];
extern char dat_02253640[4096];
extern OriginalFile** dat_02253624;
extern int32_t dat_02254640;
extern uint8_t dat_0224ee20; // canonical storage belongs to original CRT exit.

int32_t fun_005d00a9();
int32_t fun_005d0152();
int32_t fun_005cfef0(OriginalFile*);
int32_t fun_005cff4d(OriginalFile*);
int32_t fun_005cff7b(int32_t mode);
int32_t fun_005d0050(OriginalFile*);
int32_t fun_005d00a0();
void fun_005d0166(OriginalFile*);
void fun_005d0195(int32_t index, OriginalFile*);
void fun_005d01b8(OriginalFile*);
void fun_005d01e7(int32_t index, OriginalFile*);
void fun_005d5fdc(OriginalFile*);
int32_t fun_005cdaef(OriginalFile*);
int32_t fun_005cdb3b(OriginalFile*);
int32_t fun_005da58b();
int32_t fun_006abadc();

// Original private finally entries consume an enclosing frame or saved register.
// These explicit argument interfaces normalize those observed operands.
void fun_005d001b(int32_t index);
void fun_005d0047();
void fun_005d0096(OriginalFile*);
void fun_005cdb84(OriginalFile*);
void fun_005da61d();
void fun_006abb52(int32_t index);
void fun_006abb75();

// Actual, still separate low-level descriptor operations; no replacement bodies.
int32_t fun_005d0e1e(int32_t descriptor, const void* buffer, uint32_t count);
int32_t fun_005da4cf(int32_t descriptor);
int32_t fun_005cd564(int32_t descriptor);
}
