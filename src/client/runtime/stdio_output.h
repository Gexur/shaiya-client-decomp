#pragma once
#include "stdio.h"
#include "io.h"
extern "C" {
extern uint32_t dat_0224ee34;
extern char* dat_0224ee78[2];
extern OriginalIoEntry dat_0070e968;
void fun_005dd081(OriginalFile* file);
int32_t fun_005dd0c5(int32_t descriptor);
int32_t fun_005d353d(int32_t character, OriginalFile* file);
// Original custom operands: AL character, ECX file, ESI result-count pointer.
void fun_005d3656(uint8_t character, OriginalFile* file, int32_t* count);
// Original EAX count pointer plus three stack arguments.
void fun_005d3689(uint32_t character, int32_t repeat, OriginalFile* file, int32_t* count);
// Original EAX count pointer, ECX bytes, EDI file, one stack length argument.
void fun_005d36ad(const char* text, int32_t length, OriginalFile* file, int32_t* count);
int32_t fun_005d6007(OriginalFile* file);
void fun_005d608f(int32_t active, OriginalFile* file);
uint32_t fun_005d049a(const void* buffer, uint32_t size, uint32_t count, OriginalFile* file);
uint32_t fun_005d05a1(const void* buffer, uint32_t size, uint32_t count, OriginalFile* file);
// Private finally uses file from its enclosing frame; explicit normalized arg.
void fun_005d05e3(OriginalFile* file);
}
