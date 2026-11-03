#include "calendar.h"
#include "runtime/thread_data.h"
#include "runtime/heap.h"
namespace {
uint32_t word(const void* p) {
    uint32_t v;
    __asm__ __volatile__("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
int32_t signed_word(const void* p) {
    return int32_t(word(p));
}
void store(void* p, uint32_t v) {
    __asm__ __volatile__("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
int32_t add(int32_t a, int32_t b) {
    return int32_t(uint32_t(a) + uint32_t(b));
}
int32_t sub(int32_t a, int32_t b) {
    return int32_t(uint32_t(a) - uint32_t(b));
}
} // namespace
extern "C" OriginalTm* fun_005d73ef(const int32_t* epoch) {
    int32_t seconds = signed_word(epoch);
    auto* ptd = static_cast<OriginalPerThreadData*>(fun_005d2659());
    if (seconds < 0)
        return nullptr;
    OriginalTm* result;
    if (word(&ptd->allocation_44) == 0) {
        void* allocation = fun_005cfade(36);
        store(&ptd->allocation_44, uint32_t(uintptr_t(allocation)));
        result = allocation == nullptr
                     ? &dat_0224efd0
                     : reinterpret_cast<OriginalTm*>(uintptr_t(word(&ptd->allocation_44)));
    } else
        result = reinterpret_cast<OriginalTm*>(uintptr_t(word(&ptd->allocation_44)));
    const int32_t period = seconds / 126230400;
    seconds -= period * 126230400;
    int32_t year = period * 4 + 70;
    bool leap = false;
    if (seconds >= 31536000) {
        seconds -= 31536000;
        ++year;
        if (seconds >= 31536000) {
            seconds -= 31536000;
            ++year;
            if (seconds < 31622400)
                leap = true;
            else {
                ++year;
                seconds -= 31622400;
            }
        }
    }
    store(&result->year, uint32_t(year));
    const int32_t days = seconds / 86400;
    store(&result->yday, uint32_t(days));
    seconds -= days * 86400;
    int32_t* const months = leap ? dat_0070eb90 : dat_0070ebc4;
    const int32_t day = signed_word(&result->yday);
    int32_t month = 1;
    while (signed_word(months + month) < day)
        ++month;
    --month;
    store(&result->mon, uint32_t(month));
    store(&result->mday, uint32_t(sub(day, signed_word(months + month))));
    store(&result->wday, uint32_t((signed_word(epoch) / 86400 + 4) % 7));
    const int32_t hours = seconds / 3600;
    store(&result->hour, uint32_t(hours));
    seconds -= hours * 3600;
    const int32_t minutes = seconds / 60;
    store(&result->min, uint32_t(minutes));
    seconds -= minutes * 60;
    store(&result->isdst, 0);
    store(&result->sec, uint32_t(seconds));
    return result;
}
extern "C" OriginalTm* fun_005ce980(const int32_t* epoch) {
    if (signed_word(epoch) < 0)
        return nullptr;
    fun_005d7add();
    const int32_t seconds = signed_word(epoch);
    OriginalTm* result;
    if (seconds > 0x3f480 && seconds < 0x7ffc0b7f) {
        int32_t adjusted = sub(seconds, signed_word(&dat_0070eae0));
        result = fun_005d73ef(&adjusted);
        if (word(&dat_0070eae4) != 0 && fun_005d7b29(result) != 0) {
            adjusted = sub(adjusted, signed_word(&dat_0070eae8));
            result = fun_005d73ef(&adjusted);
            store(&result->isdst, 1);
        }
        return result;
    }
    result = fun_005d73ef(epoch);
    int32_t adjusted;
    if (word(&dat_0070eae4) != 0 && fun_005d7b29(result) != 0) {
        adjusted = sub(sub(signed_word(&result->sec), signed_word(&dat_0070eae8)),
                       signed_word(&dat_0070eae0));
        store(&result->isdst, 1);
    } else
        adjusted = sub(signed_word(&result->sec), signed_word(&dat_0070eae0));
    int32_t remainder = adjusted % 60;
    store(&result->sec, uint32_t(remainder));
    if (remainder < 0) {
        store(&result->sec, uint32_t(remainder + 60));
        adjusted = sub(adjusted, 60);
    }
    adjusted = add(adjusted / 60, signed_word(&result->min));
    remainder = adjusted % 60;
    store(&result->min, uint32_t(remainder));
    if (remainder < 0) {
        store(&result->min, uint32_t(remainder + 60));
        adjusted = sub(adjusted, 60);
    }
    adjusted = add(adjusted / 60, signed_word(&result->hour));
    remainder = adjusted % 24;
    store(&result->hour, uint32_t(remainder));
    if (remainder < 0) {
        store(&result->hour, uint32_t(remainder + 24));
        adjusted = sub(adjusted, 24);
    }
    const int32_t day_change = adjusted / 24;
    if (day_change > 0) {
        store(&result->wday, uint32_t(add(signed_word(&result->wday), day_change) % 7));
        store(&result->mday, uint32_t(add(signed_word(&result->mday), day_change)));
        store(&result->yday, uint32_t(add(signed_word(&result->yday), day_change)));
    } else if (day_change < 0) {
        store(&result->wday, uint32_t(add(add(signed_word(&result->wday), day_change), 7) % 7));
        const int32_t mday = add(signed_word(&result->mday), day_change);
        store(&result->mday, uint32_t(mday));
        if (mday <= 0) {
            store(&result->year, uint32_t(sub(signed_word(&result->year), 1)));
            store(&result->mday, uint32_t(mday + 31));
            store(&result->yday, 364);
            store(&result->mon, 11);
        } else
            store(&result->yday, uint32_t(add(signed_word(&result->yday), day_change)));
    }
    return result;
}
