#include "signals.h"
#include "runtime_error.h"
#include "crt_exit.h"

extern "C" [[noreturn]] void fun_005d0ba9() {
    fun_005db857(10);
    fun_005dbe8a(22);
    fun_005ce131(3);
    __asm__ volatile("int3");
    __builtin_unreachable();
}
extern "C" [[noreturn]] void abort() {
    fun_005d0ba9();
}
