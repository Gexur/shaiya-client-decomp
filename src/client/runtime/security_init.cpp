#include "security.h"
extern "C" {
__declspec(dllimport) void __attribute__((stdcall)) GetSystemTimeAsFileTime(void*);
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetCurrentProcessId();
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetCurrentThreadId();
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetTickCount();
__declspec(dllimport) int32_t __attribute__((stdcall)) QueryPerformanceCounter(void*);
}
namespace {
uint32_t raw_word(const uint8_t* bytes) {
    uint32_t value;
    __asm__ volatile("movl (%1), %0" : "=r"(value) : "r"(bytes) : "memory");
    return value;
}
} // namespace
// 005DC1BD..005DC222. QueryPerformanceCounter's return is ignored, exactly as
// in the original. Raw byte storage retains an unwritten API output without
// inventing a value or promoting an indeterminate C++ integer.
extern "C" void fun_005dc1bd() {
    if (dat_0070e4ec != 0 && dat_0070e4ec != 0xbb40e64eu)
        return;
    uint8_t file_time[8], counter[8];
    GetSystemTimeAsFileTime(file_time);
    uint32_t value = raw_word(file_time + 4) ^ raw_word(file_time);
    value ^= GetCurrentProcessId();
    value ^= GetCurrentThreadId();
    value ^= GetTickCount();
    (void)QueryPerformanceCounter(counter);
    value ^= raw_word(counter + 4) ^ raw_word(counter);
    dat_0070e4ec = value != 0 ? value : 0xbb40e64eu;
}
