#pragma once
#include <stdint.h>
#include <stddef.h>

struct OriginalCodePageInfo {
    uint32_t maximum_character_bytes;
    uint8_t default_character[2];
    uint8_t lead_bytes[12];
    uint8_t padding_012[2];
};
struct OriginalBuiltInCodePage {
    uint32_t code_page;
    uint16_t information[6];
    uint8_t ranges[4][8];
};
struct OriginalMultibyteData {
    int32_t references;
    uint32_t code_page, multibyte, locale;
    uint16_t information[5];
    uint8_t padding_01a[2];
    uint8_t classification[257];
    uint8_t case_map[256];
    uint8_t padding_21d[3];
};
static_assert(sizeof(OriginalCodePageInfo) == 20);
static_assert(sizeof(OriginalBuiltInCodePage) == 0x30);
static_assert(sizeof(OriginalMultibyteData) == 0x220);
static_assert(offsetof(OriginalMultibyteData, classification) == 0x1c);
static_assert(offsetof(OriginalMultibyteData, case_map) == 0x11d);

extern "C" {
extern uint8_t dat_0070e518[4];
extern OriginalBuiltInCodePage dat_0070e520[5];
extern const uint16_t* dat_0070e4d8;
extern uint32_t dat_0224ee64, dat_0224f258;
extern uint32_t dat_022533e0, dat_022533e8, dat_02253504;
extern uint16_t dat_02253510[6];
extern uint8_t dat_02253400[257], dat_02253520[256];
extern uint32_t dat_02254650;

// Original helper5d2fa4 consumes code_page inEAX and preservesECX. Recovered
// callers use this explicit normalized interface and retain their own index.
uint32_t fun_005d2fa4(uint32_t code_page);
void fun_005d2fd3();
void fun_005d2ffc();
int32_t* fun_005d3197();
void fun_005d31fd();
int32_t fun_005d3206(uint32_t code_page);
int32_t fun_005d339a(uint32_t code_page);
void fun_005d34e1();
int32_t fun_005d34ea();
int32_t fun_005e03e4(uint32_t character, uint32_t wide_mask, uint32_t byte_mask);
int32_t fun_005e0417(uint32_t character);
}
