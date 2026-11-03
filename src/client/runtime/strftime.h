#pragma once
#include "calendar.h"
#include "runtime/locale.h"
extern "C" {
// The first three APIs normalize the original private register operands.
void fun_005ceff9(char** output, uint32_t* remaining, const char* source);
void fun_005cf019(char** output, uint32_t* remaining, int32_t value, uint32_t width,
                  int32_t alternate);
int32_t fun_005cf092(uint8_t code, OriginalLocaleStorage*, const OriginalTm*,
                     OriginalLocaleCategory*, int32_t alternate, char** output,
                     uint32_t* remaining);
int32_t fun_005cf2f8(OriginalLocaleStorage*, int32_t mode, const OriginalTm*, char** output,
                     uint32_t* remaining, OriginalLocaleCategory*);
uint32_t fun_005cf782(OriginalLocaleStorage*, char* output, uint32_t capacity, const char* format,
                      const OriginalTm*, OriginalLocaleCategory*);
uint32_t fun_005cf845(char* output, uint32_t capacity, const char* format, const OriginalTm*,
                      OriginalLocaleCategory*);
int32_t fun_005d9070(const char*, const char*);
extern char* dat_0070eb70[2];
}
