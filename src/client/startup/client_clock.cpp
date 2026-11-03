#include "client_clock.h"
#include "../core/int64_divide.h"
#include <windows.h>
#include <mmsystem.h>
extern "C" {
// Reuse the original identities already owned by floating/text, packed-trig,
// and surface write-transform recovery. No duplicate constant storage.
extern const uint32_t dat_006bb5f0[2], dat_006bb5f8, dat_006bb5fc[1];
uint32_t dat_00708568 = 1;
uint32_t dat_00719188[2] = {0, 0}, dat_00719190[2] = {0, 0}, dat_00719198[2] = {0, 0};
uint32_t dat_007191a0[2] = {0, 0}, dat_007191a8[2] = {0, 0}, dat_007191b0[2] = {0, 0},
         dat_007191b8[2] = {0, 0};
uint32_t dat_007191c0 = 0, dat_007191c4 = 0;
extern const uint32_t dat_006bb5d8[2] = {0xa0000000u, 0x3fb99999u};
extern const uint32_t dat_006bb5e0[2] = {0xd2f1a9fcu, 0x3f50624du};
extern const uint32_t dat_006bb5e8[2] = {0x00000000u, 0x41f00000u};
extern const uint32_t dat_006bb600 = 0x3c23d70au;
extern const uint32_t dat_006bb604 = 0x34000000u;
}
namespace {
uint32_t word(const uint32_t* p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void store(uint32_t* p, uint32_t v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
uint64_t pair(const uint32_t* p) {
    const uint32_t low = word(p), high = word(p + 1);
    return (uint64_t(high) << 32) | low;
}
void store_pair(uint32_t* p, uint64_t value) {
    store(p, uint32_t(value));
    store(p + 1, uint32_t(value >> 32));
}
void load_float(const uint32_t* p) {
    __asm__ volatile("flds (%0)" ::"r"(p) : "st", "memory");
}
void load_double(const uint32_t* p) {
    __asm__ volatile("fldl (%0)" ::"r"(p) : "st", "memory");
}
void store_double(uint32_t* p) {
    __asm__ volatile("fstpl (%0)" ::"r"(p) : "st", "memory");
}
void keep_double(uint32_t* p) {
    __asm__ volatile("fstl (%0)" ::"r"(p) : "memory");
}
void pop() {
    __asm__ volatile("fstp %%st(0)" ::: "st");
}
void zero_result() {
    load_float(dat_006bb5fc);
}
void ratio(uint64_t numerator) {
    __asm__ volatile("fildll %0\n\tfildll %1\n\tfdivrp %%st(0),%%st(1)" ::"m"(numerator),
                     "m"(dat_007191b8)
                     : "st", "st(1)", "memory");
}
void minimum_delta() {
    uint16_t sw;
    __asm__ volatile("fcoms %1\n\tfnstsw %%ax" : "=a"(sw) : "m"(dat_006bb604) : "memory");
    const uint32_t condition = sw & 0x0500u;
    if (condition != 0 && condition != 0x0500u) {
        pop();
        load_float(&dat_006bb600);
    }
}
bool cached_milliseconds() {
    uint16_t sw;
    __asm__ volatile("fldl %1\n\tfldl %2\n\tfucompp\n\tfnstsw %%ax"
                     : "=a"(sw)
                     : "m"(dat_006bb5f0), "m"(dat_00719198)
                     : "st", "st(1)", "memory");
    const uint32_t condition = sw & 0x4400u;
    return condition == 0 || condition == 0x4400u;
}
} // namespace
// Complete original 0x00405840..0x00405c10: performance-counter/fallback
// clock, pause/resume/reset/advance commands and original minimum delta.
// Floating primitives leave the original physical ST0 result in place; only
// integer control flow is compiled around them, with no host clock/math model.
extern "C" __attribute__((noinline)) void aligned_00405840(uint32_t* actual_arguments) {
    LARGE_INTEGER current;
    uint32_t performance;
    if (word(&dat_007191c4) == 0) {
        store(&dat_007191c4, 1);
        performance = uint32_t(QueryPerformanceFrequency(&current));
        store(&dat_007191c0, performance);
        if (performance != 0)
            store_pair(dat_007191b8, uint64_t(current.QuadPart));
    } else
        performance = word(&dat_007191c0);
    const int32_t command = int32_t(word(actual_arguments));
    if (performance != 0) {
        uint64_t paused = pair(dat_007191b0);
        uint64_t now;
        if (paused == 0 || command == 1 || command == 4) {
            QueryPerformanceCounter(&current);
            now = uint64_t(current.QuadPart);
            paused = pair(dat_007191b0);
        } else
            now = paused;
        if (command == 6) {
            const uint64_t previous = pair(dat_007191a8);
            store_pair(dat_007191a8, now);
            ratio(now - previous);
            minimum_delta();
            return;
        }
        if (command == 5) {
            ratio(now - pair(dat_007191a0));
            minimum_delta();
            return;
        }
        if (command == 0) {
            store_pair(dat_007191a0, now);
            store_pair(dat_007191a8, now);
            store_pair(dat_007191b0, 0);
            store(&dat_00708568, 0);
            zero_result();
            return;
        }
        if (command == 1) {
            if (word(&dat_00708568) != 0)
                store_pair(dat_007191a0, pair(dat_007191a0) + (now - paused));
            store_pair(dat_007191b0, 0);
            store_pair(dat_007191a8, now);
            store(&dat_00708568, 0);
            zero_result();
            return;
        }
        if (command == 2) {
            if (word(&dat_00708568) == 0) {
                store_pair(dat_007191b0, now);
                store_pair(dat_007191a8, now);
                store(&dat_00708568, 1);
            }
            zero_result();
            return;
        }
        if (command == 3) {
            const uint32_t high = word(dat_007191b8 + 1), low = word(dat_007191b8);
            const uint64_t step = fun_005ccfd0(low, high, 10, 0);
            const uint64_t advanced = paused + step;
            store(dat_007191b0 + 1, uint32_t(advanced >> 32));
            store(dat_007191b0, uint32_t(advanced));
            zero_result();
            return;
        }
        if (command == 4) {
            ratio(now);
            return;
        }
        load_float(&dat_006bb5f8);
        return;
    }
    const bool cached = cached_milliseconds();
    if (cached && command != 1 && command != 4)
        load_double(dat_00719198);
    else {
        const uint32_t tick = timeGetTime();
        store(actual_arguments, tick);
        __asm__ volatile("fildl %0" ::"m"(tick) : "st");
        if (tick & 0x80000000u)
            __asm__ volatile("faddl %0" ::"m"(dat_006bb5e8) : "memory");
        __asm__ volatile("fmull %0" ::"m"(dat_006bb5e0) : "memory");
    }
    if (command == 6) {
        uint32_t rounded[2];
        __asm__ volatile("fldl %0\n\tfsubr %%st(1),%%st(0)\n\tfstpl %1" ::"m"(dat_00719190),
                         "m"(rounded)
                         : "st", "memory");
        store_double(dat_00719190);
        load_double(rounded);
        minimum_delta();
        return;
    }
    if (command == 5) {
        __asm__ volatile("fsubl %0" ::"m"(dat_00719188) : "memory");
        minimum_delta();
        return;
    }
    if (command == 0) {
        keep_double(dat_00719188);
        store_double(dat_00719190);
        store(&dat_00708568, 0);
        load_double(dat_006bb5f0);
        store_double(dat_00719198);
        zero_result();
        return;
    }
    if (command == 1) {
        if (word(&dat_00708568) != 0)
            __asm__ volatile(
                "fldl %0\n\tfsubr %%st(1),%%st(0)\n\tfaddl %1\n\tfstpl %1" ::"m"(dat_00719198),
                "m"(dat_00719188)
                : "st", "memory");
        load_double(dat_006bb5f0);
        store_double(dat_00719198);
        store(&dat_00708568, 0);
        store_double(dat_00719190);
        zero_result();
        return;
    }
    if (command == 2) {
        if (word(&dat_00708568) == 0) {
            keep_double(dat_00719198);
            store_double(dat_00719190);
            store(&dat_00708568, 1);
        } else
            pop();
        zero_result();
        return;
    }
    if (command == 3) {
        pop();
        load_double(dat_00719198);
        __asm__ volatile("faddl %0" ::"m"(dat_006bb5d8) : "memory");
        store_double(dat_00719198);
        zero_result();
        return;
    }
    if (command == 4)
        return;
    pop();
    load_float(&dat_006bb5f8);
}
// Original stdcall RET4 and extended-precision physical ST0 return. A normal
// C++ return through binary32/binary64 would introduce an absent conversion.
extern "C" __attribute__((naked, stdcall)) long double FUN_00405840(int32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcall _aligned_00405840\n\taddl $4,%esp\n\tretl $4");
}
