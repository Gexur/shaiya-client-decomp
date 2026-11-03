#pragma once
#include <stdint.h>
#include <stddef.h>

struct OriginalTm {
    int32_t sec, min, hour, mday, mon, year, wday, yday, isdst;
};
static_assert(sizeof(OriginalTm) == 36 && offsetof(OriginalTm, yday) == 28 &&
              offsetof(OriginalTm, isdst) == 32);
extern "C" {
extern int32_t dat_0070eae0;
extern int32_t dat_0070eae4;
extern int32_t dat_0070eae8;
extern int32_t dat_0070eb90[13];
extern int32_t dat_0070ebc4[13];
void fun_005d74f6();
void fun_005d7add();
int32_t fun_005d7b29(const OriginalTm*);
}
