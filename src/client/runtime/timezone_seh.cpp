#include "timezone_internal.h"
#include "runtime/heap.h"
extern "C" void fun_005d7711() {
    fun_005d64e6(7);
}
extern "C" void fun_005d7b20() {
    fun_005d64e6(6);
}
extern "C" void fun_005d7b5e() {
    fun_005d64e6(6);
}
extern "C" void fun_005d74f6() {
    const char* env;
    fun_005d659b(7);
    __try {
        env = timezone_prepare();
    } __finally {
        fun_005d7711();
    }
    if (env != nullptr)
        timezone_parse(env);
}
extern "C" void fun_005d7add() {
    if (dat_0224f0ac != 0)
        return;
    fun_005d659b(6);
    __try {
        if (dat_0224f0ac == 0) {
            fun_005d74f6();
            dat_0224f0ac = dat_0224f0ac + 1u;
        }
    } __finally {
        fun_005d7b20();
    }
}
extern "C" int32_t fun_005d7b29(const OriginalTm* value) {
    int32_t result;
    fun_005d659b(6);
    __try {
        result = fun_005d7956(value);
    } __finally {
        fun_005d7b5e();
    }
    return result;
}
