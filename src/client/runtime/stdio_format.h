#pragma once
#include "stdio_output.h"
extern "C" {
extern const uint8_t dat_006d68b0[89];
extern const char dat_006d691c[7];
extern const uint16_t dat_006d690c[7];
extern const char* dat_0070e610;
extern const uint16_t* dat_0070e614;
int32_t fun_005d36e4(OriginalFile* file, const char* format, const void* argument_words);
int32_t fun_005cd214(char* output, uint32_t capacity, const char* format, ...);
int32_t fun_005cd489(char* output, const char* format, ...);
int32_t fun_005ceb39(char* output, const char* format, const void* argument_words);
int32_t fun_005d139d(char* output, uint32_t capacity, const char* format,
                     const void* argument_words);
int32_t fun_005cdb8c(OriginalFile* file, const char* format, ...);
void fun_005cdbe0(OriginalFile* file);
}
