#include "timezone_internal.h"
#include "runtime/heap.h"
#include "runtime/strings.h"
#include "runtime/runtime_error.h"
#include "runtime/cxx_exception.h"
#include "runtime/multibyte.h"
#include "runtime/nls.h"
extern "C" {
__declspec(dllimport) uint32_t __attribute__((stdcall))
GetTimeZoneInformation(OriginalTimeZoneInformation172*);
using TimeZoneNameConverter = int32_t(__attribute__((stdcall)) *)(uint32_t, uint32_t,
                                                                  const uint16_t*, int32_t, char*,
                                                                  int32_t, const char*, int32_t*);
extern TimeZoneNameConverter timezone_conversion_slot __asm__("__imp__WideCharToMultiByte@32");
char* fun_005dec3d(const char*);

int32_t dat_0070eae0 = 28800, dat_0070eae4 = 1, dat_0070eae8 = -3600;
char dat_0070eaf0[64] = "PST", dat_0070eb30[64] = "PDT";
char* dat_0070eb70[2] = {dat_0070eaf0, dat_0070eb30};
volatile int32_t dat_0070eb78 = -1, dat_0070eb7c = 0, dat_0070eb80 = 0, dat_0070eb84 = -1,
                 dat_0070eb88 = 0, dat_0070eb8c = 0;
OriginalTimeZoneInformation172 dat_0224eff8{};
uint32_t dat_0224f0a4 = 0;
char* dat_0224f0a8 = nullptr;
volatile uint32_t dat_0224f0ac = 0;
}
namespace {
int32_t add(int32_t a, int32_t b) {
    return int32_t(uint32_t(a) + uint32_t(b));
}
int32_t sub(int32_t a, int32_t b) {
    return int32_t(uint32_t(a) - uint32_t(b));
}
int32_t mul(int32_t a, int32_t b) {
    return int32_t(uint32_t(a) * uint32_t(b));
}
bool leap(int32_t year) {
    return (year % 4 == 0 && year % 100 != 0) || add(year, 1900) % 400 == 0;
}
int32_t previous_day(int32_t month, bool is_leap) {
    // Month0 reaches the actual preceding DWORD in the original image. Keep
    // these observed aliases despite independently relocated canonical tables.
    if (month == 0)
        return is_leap ? dat_0070eb8c : dat_0070eb90[12];
    return (is_leap ? dat_0070eb90 : dat_0070ebc4)[uint32_t(month) - 1];
}
int32_t raw_default(const int32_t* value) {
    int32_t result;
    __asm__ volatile("movl (%1),%0" : "=r"(result) : "r"(value) : "memory");
    return result;
}
} // namespace
extern "C" void fun_005d779e(int32_t month, int32_t hour, int32_t transition, int32_t relative,
                             int32_t year, int32_t week, int32_t weekday, int32_t day,
                             int32_t minute, int32_t second, int32_t millis) {
    const bool is_leap = leap(year);
    int32_t yday = previous_day(month, is_leap);
    if (relative == 1) {
        yday = add(yday, 1);
        const int32_t first_weekday =
            add(add(add(mul(year, 365), sub(add(year, 299) / 400, sub(year, 1) / 100)),
                    sub(year, 1) / 4),
                sub(yday, 25563)) %
            7;
        const int32_t delta = add(sub(mul(week, 7), first_weekday), weekday);
        yday = add(yday, first_weekday <= weekday ? sub(delta, 7) : delta);
        if (week == 5 && yday > (is_leap ? dat_0070eb90 : dat_0070ebc4)[uint32_t(month)])
            yday = sub(yday, 7);
    } else
        yday = add(yday, day);
    int32_t time = mul(add(mul(hour, 60), minute), 60);
    if (transition == 1) {
        time = add(time, second);
        dat_0070eb7c = yday;
        time = add(mul(time, 1000), millis);
        dat_0070eb78 = year;
        dat_0070eb80 = time;
    } else {
        time = add(time, dat_0070eae8);
        dat_0070eb88 = yday;
        time = add(mul(add(time, second), 1000), millis);
        dat_0070eb8c = time;
        if (time < 0) {
            time = add(time, 86400000);
            yday = sub(yday, 1);
            dat_0070eb8c = time;
            dat_0070eb88 = yday;
        } else if (time >= 86400000) {
            time = sub(time, 86400000);
            yday = add(yday, 1);
            dat_0070eb8c = time;
            dat_0070eb88 = yday;
        }
        dat_0070eb84 = year;
    }
}
extern "C" int32_t fun_005d7956(const OriginalTm* tm) {
    if (dat_0070eae4 == 0)
        return 0;
    const int32_t year = tm->year;
    if (year != dat_0070eb78 || year != dat_0070eb84) {
        if (dat_0224f0a4 != 0) {
            const auto& start = dat_0224eff8.daylight_date;
            fun_005d779e(start.month, start.hour, 1, start.year == 0 ? 1 : 0, year,
                         start.year == 0 ? start.day : 0, start.year == 0 ? start.weekday : 0,
                         start.year == 0 ? 0 : start.day, start.minute, start.second, start.millis);
            const auto& end = dat_0224eff8.standard_date;
            fun_005d779e(end.month, end.hour, 0, end.year == 0 ? 1 : 0, year,
                         end.year == 0 ? end.day : 0, end.year == 0 ? end.weekday : 0,
                         end.year == 0 ? 0 : end.day, end.minute, end.second, end.millis);
        } else {
            fun_005d779e(4, 2, 1, 1, year, 1, 0, 0, 0, 0, 0);
            fun_005d779e(10, 2, 0, 1, year, 5, 0, 0, 0, 0, 0);
        }
    }
    const int32_t start_day = dat_0070eb7c, end_day = dat_0070eb88, yday = tm->yday;
    if (start_day < end_day) {
        if (yday < start_day || yday > end_day)
            return 0;
        if (yday > start_day && yday < end_day)
            return 1;
    } else {
        if (yday < end_day || yday > start_day)
            return 1;
        if (yday > end_day && yday < start_day)
            return 0;
    }
    const int32_t time = mul(add(mul(add(mul(tm->hour, 60), tm->min), 60), tm->sec), 1000);
    if (yday == start_day)
        return time >= dat_0070eb80 ? 1 : 0;
    return time < dat_0070eb8c ? 1 : 0;
}
extern "C" const char* timezone_prepare() {
    const uint32_t code_page = dat_0224f258;
    dat_0224f0a4 = 0;
    dat_0070eb84 = -1;
    dat_0070eb78 = -1;
    const char* env = fun_005dec3d("TZ");
    if (env != nullptr && *env != 0) {
        if (dat_0224f0a8 != nullptr && fun_005d65d0(env, dat_0224f0a8) == 0)
            return nullptr;
        if (dat_0224f0a8 != nullptr)
            fun_005cfaf0(dat_0224f0a8);
        dat_0224f0a8 = static_cast<char*>(fun_005cfade(fun_005d4cf0(env) + 1));
        if (dat_0224f0a8 == nullptr)
            return nullptr;
        fun_005d6350(dat_0224f0a8, env);
        return env;
    }
    if (dat_0224f0a8 != nullptr) {
        fun_005cfaf0(dat_0224f0a8);
        dat_0224f0a8 = nullptr;
    }
    if (GetTimeZoneInformation(&dat_0224eff8) == 0xffffffffu)
        return nullptr;
    dat_0224f0a4 = 1;
    int32_t bias = mul(dat_0224eff8.bias, 60);
    dat_0070eae0 = bias;
    if (dat_0224eff8.standard_date.month != 0) {
        bias = add(bias, mul(dat_0224eff8.standard_bias, 60));
        dat_0070eae0 = bias;
    }
    if (dat_0224eff8.daylight_date.month != 0 && dat_0224eff8.daylight_bias != 0) {
        dat_0070eae4 = 1;
        dat_0070eae8 = mul(sub(dat_0224eff8.daylight_bias, dat_0224eff8.standard_bias), 60);
    } else {
        dat_0070eae4 = 0;
        dat_0070eae8 = 0;
    }
    int32_t used_default;
    TimeZoneNameConverter const convert = timezone_conversion_slot;
    int32_t result = convert(code_page, 0, dat_0224eff8.standard_name, -1, dat_0070eb70[0], 63,
                             nullptr, &used_default);
    if (result != 0 && raw_default(&used_default) == 0)
        dat_0070eb70[0][63] = 0;
    else
        dat_0070eb70[0][0] = 0;
    result = convert(code_page, 0, dat_0224eff8.daylight_name, -1, dat_0070eb70[1], 63, nullptr,
                     &used_default);
    if (result != 0 && raw_default(&used_default) == 0)
        dat_0070eb70[1][63] = 0;
    else
        dat_0070eb70[1][0] = 0;
    return nullptr;
}
extern "C" void timezone_parse(const char* env) {
    fun_005cd0f0(dat_0070eb70[0], env, 3);
    dat_0070eb70[0][3] = 0;
    env += 3;
    const bool negative = *env == '-';
    if (negative)
        ++env;
    dat_0070eae0 = mul(fun_005cd2dd(env), 3600);
    while (*env == '+' || (int8_t(*env) >= '0' && int8_t(*env) <= '9'))
        ++env;
    if (*env == ':') {
        ++env;
        dat_0070eae0 = add(dat_0070eae0, mul(fun_005cd2dd(env), 60));
        while (int8_t(*env) >= '0' && int8_t(*env) <= '9')
            ++env;
        if (*env == ':') {
            ++env;
            dat_0070eae0 = add(dat_0070eae0, fun_005cd2dd(env));
            while (int8_t(*env) >= '0' && int8_t(*env) <= '9')
                ++env;
        }
    }
    if (negative)
        dat_0070eae0 = sub(0, dat_0070eae0);
    dat_0070eae4 = int8_t(*env);
    if (dat_0070eae4 != 0) {
        fun_005cd0f0(dat_0070eb70[1], env, 3);
        dat_0070eb70[1][3] = 0;
    } else
        dat_0070eb70[1][0] = 0;
}
