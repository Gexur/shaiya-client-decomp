#include "runtime_error.h"
#include "crt_exit.h"
#include "strings.h"
extern "C" {
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetModuleFileNameA(void*, char*, uint32_t);
}
extern "C" [[noreturn]] void fun_005dc223(int32_t kind, const void* context) {
    OriginalSecurityReporter callback = dat_0224f23c;
    if (callback != nullptr) {
        __try {
            callback(kind, context);
        } __except (1) {
        }
    } else {
        const char* prefix = kind == 1 ? dat_006dac18 : dat_006dacec;
        const char* message = kind == 1 ? dat_006dab78 : dat_006dac38;
        const uint32_t fixed_size = kind == 1 ? 185u : 212u;
        char program[261];
        program[260] = 0;
        if (GetModuleFileNameA(nullptr, program, 260) == 0)
            fun_005d6350(program, dat_006dab38);
        char* shown = program;
        if (fun_005d4cf0(shown) + 11 > 60) {
            shown = program + fun_005d4cf0(shown) - 49;
            fun_005cd0f0(shown, dat_006bfb38, 3);
        }
        const uint32_t allocation = (fun_005d4cf0(shown) + fixed_size + 12 + 3) & ~3u;
        char* output = static_cast<char*>(__builtin_alloca(allocation));
        fun_005d6350(output, prefix);
        fun_005d6360(output, dat_006dab18);
        fun_005d6360(output, dat_006dab6c);
        fun_005d6360(output, shown);
        fun_005d6360(output, dat_006dab18);
        fun_005d6360(output, message);
        (void)fun_005e02eb(output, dat_006daaf0, 0x12010);
    }
    fun_005ce131(3);
    __asm__ volatile("int3");
    __builtin_unreachable();
}
