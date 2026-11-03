#pragma once
#include <stdint.h>
#include "entry.h"
extern "C" {
extern int32_t dat_0224edfc;
extern char** dat_0224ee00;
extern char* dat_0224ee18;
// The original 260-byte GetModuleFileName buffer has a zero sentinel at +260.
extern char dat_0224f118[261];
extern uint32_t dat_02254650;
extern uint8_t dat_02253400[257];
int32_t fun_005d34ea();
int32_t fun_005e0417(uint32_t character);
// Normalized original custom ABI: input=EAX, output_text=ECX,
// text_bytes=ESI; argv and argument_slots are original stack arguments.
void fun_005dbb2c(const uint8_t* input, char** argv, char* output_text, uint32_t* argument_slots,
                  uint32_t* text_bytes);
int32_t fun_005dbc98();
char* fun_005dba08();
}
