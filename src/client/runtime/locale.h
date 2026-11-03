#pragma once
#include <stddef.h>
#include <stdint.h>

struct OriginalLocaleConversions {
    void* strings[10];
    uint8_t numeric[8];
};
struct OriginalLocaleCategory {
    const char* strings[43];
    uint32_t language;
    uint32_t flag;
    int32_t references;
};
struct OriginalLocaleStorage {
    int32_t references;
    uint32_t undecoded_004[8];
    uint32_t invariant_024, invariant_028;
    int32_t* reference_02c;
    int32_t* reference_030;
    int32_t* reference_034;
    OriginalLocaleConversions* conversions_038;
    OriginalLocaleConversions* allocation_03c;
    int32_t* reference_040;
    void* allocation_044;
    const uint16_t* table_048;
    OriginalLocaleCategory* category_04c;
    OriginalLocaleCategory* allocation_050;
};
static_assert(sizeof(OriginalLocaleConversions) == 0x30);
static_assert(sizeof(OriginalLocaleCategory) == 0xb8);
static_assert(sizeof(OriginalLocaleStorage) == 0x54);
static_assert(offsetof(OriginalLocaleStorage, reference_02c) == 0x2c);
static_assert(offsetof(OriginalLocaleStorage, category_04c) == 0x4c);
static_assert(offsetof(OriginalLocaleCategory, references) == 0xb4);

extern "C" {
extern OriginalLocaleStorage dat_0070e628;
extern void* dat_0070e67c;
extern int32_t* dat_022533e4;
extern void* dat_0224f264;
extern void* dat_0224f268;
extern int32_t* dat_02253298;
extern int32_t* dat_0225329c;
extern int32_t* dat_022532a4;
extern OriginalLocaleConversions dat_0070ef08;
extern OriginalLocaleConversions* dat_0070ef38;
extern OriginalLocaleCategory dat_0070e188;
extern char dat_0070ef04[4];
extern char dat_0224f260;
extern const uint16_t dat_006d62c6[257];

void fun_005d4d7b(void* locale);
void fun_005dd634(void* category);
void fun_005dd823(void* conversions);
void fun_005dda4f(void* conversions);
}
