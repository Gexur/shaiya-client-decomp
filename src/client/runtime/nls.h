#pragma once
#include <stdint.h>
#include "locale.h"

extern "C" {
extern uint32_t dat_0224f238; // GetStringType API selection: original BSS zero.
extern uint32_t dat_0224f0b0; // LCMapString API selection: original BSS zero.
extern uint32_t dat_0224f248; // Original default LCID, BSS zero.

int32_t fun_005dc003(uint32_t information, const char* source, int32_t length, uint16_t* types,
                     uint32_t code_page, uint32_t locale, int32_t strict);
uint32_t fun_005d9327(uint32_t locale, uint32_t flags, const char* source, int32_t length,
                      char* output, int32_t capacity, uint32_t code_page, int32_t strict);
int32_t fun_005df112(uint32_t locale);
char* fun_005df159(uint32_t from, uint32_t to, const char* source, int32_t* length, char* output,
                   int32_t capacity);
int32_t fun_005cfb61();
int32_t fun_005cd2dd(const char* source);
int32_t fun_005cd365(const char* source);
uint32_t fun_005d0beb(const OriginalLocaleStorage* locale, int32_t character, uint32_t mask);
OriginalLocaleStorage* fun_005d4e4b();
OriginalLocaleStorage* fun_005d505a();
void fun_005d508c();
}
