#pragma once
#include "runtime/timezone.h"

struct OriginalSystemTime16 {
    uint16_t year, month, weekday, day, hour, minute, second, millis;
};
struct OriginalTimeZoneInformation172 {
    int32_t bias;
    uint16_t standard_name[32];
    OriginalSystemTime16 standard_date;
    int32_t standard_bias;
    uint16_t daylight_name[32];
    OriginalSystemTime16 daylight_date;
    int32_t daylight_bias;
};
static_assert(sizeof(OriginalSystemTime16) == 16 && sizeof(OriginalTimeZoneInformation172) == 172);
static_assert(offsetof(OriginalTimeZoneInformation172, standard_date) == 68 &&
              offsetof(OriginalTimeZoneInformation172, daylight_date) == 152);
extern "C" {
extern char dat_0070eaf0[64], dat_0070eb30[64];
extern char* dat_0070eb70[2];
extern volatile int32_t dat_0070eb78, dat_0070eb7c, dat_0070eb80, dat_0070eb84, dat_0070eb88,
    dat_0070eb8c;
extern OriginalTimeZoneInformation172 dat_0224eff8;
extern uint32_t dat_0224f0a4;
extern char* dat_0224f0a8;
extern volatile uint32_t dat_0224f0ac;
// Original private779e takes month in EAX, hour in ECX and nine stack
// arguments. The normalized C++ interface names both register inputs.
void fun_005d779e(int32_t month, int32_t hour, int32_t transition, int32_t relative, int32_t year,
                  int32_t week, int32_t weekday, int32_t day, int32_t minute, int32_t second,
                  int32_t millis);
// Original private7956 consumes its tm pointer in EBX.
int32_t fun_005d7956(const OriginalTm*);
void fun_005d7711();
void fun_005d7b20();
void fun_005d7b5e();
// Original tzset's protected preparation and unprotected parser are split at
// its actual unlock7 boundary. These adapters add no original entries.
const char* timezone_prepare();
void timezone_parse(const char*);
}
