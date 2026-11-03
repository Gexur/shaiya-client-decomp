#include "runtime_error.h"
#include "crt_exit.h"
#include "security.h"
#include "strings.h"
#include "heap.h"

extern "C" {
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetModuleFileNameA(void*, char*, uint32_t);
__declspec(dllimport) void* __attribute__((stdcall)) GetStdHandle(int32_t);
__declspec(dllimport) int32_t __attribute__((stdcall)) WriteFile(void*, const void*, uint32_t,
                                                                 uint32_t*, void*);
extern uint32_t dat_0070e4d4;
uint32_t dat_0224ee40 = 0;
OriginalRuntimeExit dat_0070e4d0 = fun_005ce131;
OriginalRuntimeBanner dat_0224f110 = nullptr;
OriginalSecurityReporter dat_0224f23c = nullptr;
}

extern "C" void fun_005db857(int32_t message) {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    uint32_t index = 0;
    while (index < 19 && dat_0070ee30.records[index].code != uint32_t(message))
        ++index;
    const uint32_t code = index == 19
                              ? uint32_t(dat_0070ee30.conversion_formats[0].maximum_exponent)
                              : dat_0070ee30.records[index].code;
    if (code == uint32_t(message)) {
        const char* text = index == 19 ? reinterpret_cast<const char*>(uint32_t(
                                             dat_0070ee30.conversion_formats[0].minimum_exponent))
                                       : dat_0070ee30.records[index].text;
        if (dat_0224ee40 == 1 || (dat_0224ee40 == 0 && dat_0070e4d4 == 1)) {
            uint32_t written;
            const uint32_t length = fun_005d4cf0(text);
            void* output = GetStdHandle(-12);
            (void)WriteFile(output, text, length, &written, nullptr);
        } else if (message != 252) {
            char program[261];
            program[260] = 0;
            if (GetModuleFileNameA(nullptr, program, 260) == 0)
                fun_005d6350(program, dat_006dab38);
            char* shown = program;
            if (fun_005d4cf0(shown) + 1 > 60) {
                shown = program + fun_005d4cf0(shown) - 59;
                fun_005cd0f0(shown, dat_006bfb38, 3);
            }
            const uint32_t program_length = fun_005d4cf0(shown);
            const uint32_t text_length = fun_005d4cf0(text);
            const uint32_t allocation = (program_length + text_length + 28 + 3) & ~3u;
            char* output = static_cast<char*>(__builtin_alloca(allocation));
            fun_005d6350(output, dat_006dab1c);
            fun_005d6360(output, shown);
            fun_005d6360(output, dat_006dab18);
            fun_005d6360(output, text);
            (void)fun_005e02eb(output, dat_006daaf0, 0x12010);
        }
    }
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
}
extern "C" void fun_005db9cf() {
    if (dat_0224ee40 == 1 || (dat_0224ee40 == 0 && dat_0070e4d4 == 1)) {
        fun_005db857(252);
        OriginalRuntimeBanner callback = dat_0224f110;
        if (callback != nullptr)
            callback();
        fun_005db857(255);
    }
}
extern "C" void fun_005d098b(int32_t message) {
    if (dat_0224ee40 == 1)
        fun_005db9cf();
    fun_005db857(message);
    dat_0070e4d0(255);
}
extern "C" [[noreturn]] void fun_005d09b0(int32_t message) {
    if (dat_0224ee40 == 1)
        fun_005db9cf();
    fun_005db857(message);
    fun_005cdf99(255);
}
