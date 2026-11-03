#include "allocations.h"

extern "C" void* fun_005cc96d(uint32_t bytes) {
    return fun_005cfab2(bytes, 1);
}

// The three original jump-only aliases each have a real target body. These
// wrappers preserve those targets; they do not invent allocator results.
extern "C" void* fun_005cde20(uint32_t bytes) {
    return fun_005cc96d(bytes);
}
extern "C" void fun_005cc620(void* pointer) {
    fun_005cfaf0(pointer);
}
extern "C" void fun_005cdc59(void* pointer) {
    fun_005cc620(pointer);
}

extern "C" void fun_005d8d1e() {
    fun_005d64e6(4);
}

// Earlier recovered callers use uppercase address names for these same real
// original entries. These same-TU aliases add no body, behavior or procedure.
extern "C" void* FUN_005cc96d(uint32_t) __attribute__((alias("fun_005cc96d")));
extern "C" void FUN_005cc620(void*) __attribute__((alias("fun_005cc620")));
extern "C" void* FUN_005cde20(uint32_t) __attribute__((alias("fun_005cde20")));
extern "C" void FUN_005cdc59(void*) __attribute__((alias("fun_005cdc59")));
