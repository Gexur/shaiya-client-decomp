#pragma once
#include <stdint.h>
#include "../core/extended96_format.h"
using OriginalRuntimeExit = void(__attribute__((cdecl)) *)(int32_t);
using OriginalRuntimeBanner = void(__attribute__((cdecl)) *)();
using OriginalSecurityReporter = void(__attribute__((cdecl)) *)(int32_t, const void*);
using OriginalMessageBox = int32_t(__attribute__((stdcall)) *)(void*, const char*, const char*,
                                                               uint32_t);
using OriginalActiveWindow = void*(__attribute__((stdcall)) *)();
using OriginalActivePopup = void*(__attribute__((stdcall)) *)(void*);
using OriginalWindowStation = void*(__attribute__((stdcall)) *)();
using OriginalUserInformation = int32_t(__attribute__((stdcall)) *)(void*, int32_t, void*, uint32_t,
                                                                    uint32_t*);
struct OriginalRuntimeErrorRecord {
    uint32_t code;
    const char* text;
};
struct OriginalRuntimeErrorStorage {
    OriginalRuntimeErrorRecord records[19];
    OriginalExtended96Format conversion_formats[2];
};
static_assert(sizeof(OriginalRuntimeErrorStorage) == 200);
extern "C" {
extern OriginalRuntimeErrorStorage dat_0070ee30;
extern const char dat_006daaf0[], dat_006dab18[], dat_006dab1c[], dat_006dab38[], dat_006dab6c[];
extern const char dat_006dab78[], dat_006dac18[], dat_006dac38[], dat_006dacec[], dat_006bfb38[];
extern uint32_t dat_0224ee40;
extern OriginalRuntimeExit dat_0070e4d0;
extern OriginalRuntimeBanner dat_0224f110;
extern OriginalSecurityReporter dat_0224f23c;
extern OriginalMessageBox dat_0224f2c0;
extern OriginalActiveWindow dat_0224f2c4;
extern OriginalActivePopup dat_0224f2c8;
extern OriginalWindowStation dat_0224f2cc;
extern OriginalUserInformation dat_0224f2d0;
void fun_005d098b(int32_t);
[[noreturn]] void fun_005d09b0(int32_t);
void fun_005db857(int32_t);
void fun_005db9cf();
int32_t fun_005e02eb(const char*, const char*, uint32_t);
[[noreturn]] void fun_005dc223(int32_t, const void*);
char* fun_005cd0f0(char*, const char*, uint32_t);
}
