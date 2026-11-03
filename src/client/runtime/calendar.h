#pragma once
#include "runtime/timezone.h"
extern "C" {
extern int32_t dat_0070eb90[13], dat_0070ebc4[13];
extern OriginalTm dat_0224efd0;
extern uint32_t dat_0224eca4;
extern char dat_0224eca8[128];
OriginalTm* fun_005d73ef(const int32_t*);
OriginalTm* fun_005ce980(const int32_t*);
uint32_t fun_005cf877(char*, uint32_t, const char*, const OriginalTm*);
const char* fun_005c3a00(const char*);
}
