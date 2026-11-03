// Actual constructor-iterator/atexit callbacks and their matching destructors.
#include "global_initializers_arrays.h"
#include "../core/string_default.h"
#include "../runtime/array_lifetime.h"
#include "../runtime/exit_registry.h"

extern "C" {
OriginalResourcePair dat_00864d78[8] = {};
OriginalResourcePair dat_00864ed0[42] = {};
OriginalResourcePair dat_00865250[42] = {};
OriginalResourcePair dat_00865510[10] = {};
OriginalResourcePair dat_008654f0[2] = {};
shaiya::startup::String_00405710 dat_0224ebf8[4] = {};
}

extern "C" void fun_006b5e10() {
    fun_005ce6bb(dat_00864d78, 16, 8, reinterpret_cast<OriginalElementCallback>(FUN_0041fef0),
                 reinterpret_cast<OriginalElementCallback>(FUN_0041ff00));
    (void)fun_005ccf60(fun_006b8530);
}
extern "C" void fun_006b8530() {
    fun_005cdcbc(dat_00864d78, 16, 8, reinterpret_cast<OriginalElementCallback>(FUN_0041ff00));
}
extern "C" void fun_006b61c0() {
    fun_005ce6bb(dat_00864ed0, 16, 42, reinterpret_cast<OriginalElementCallback>(FUN_0041fef0),
                 reinterpret_cast<OriginalElementCallback>(FUN_0041ff00));
    (void)fun_005ccf60(fun_006b8a20);
}
extern "C" void fun_006b8a20() {
    fun_005cdcbc(dat_00864ed0, 16, 42, reinterpret_cast<OriginalElementCallback>(FUN_0041ff00));
}
extern "C" void fun_006b61f0() {
    fun_005ce6bb(dat_00865250, 16, 42, reinterpret_cast<OriginalElementCallback>(FUN_0041fef0),
                 reinterpret_cast<OriginalElementCallback>(FUN_0041ff00));
    (void)fun_005ccf60(fun_006b8a40);
}
extern "C" void fun_006b8a40() {
    fun_005cdcbc(dat_00865250, 16, 42, reinterpret_cast<OriginalElementCallback>(FUN_0041ff00));
}
extern "C" void fun_006b6230() {
    fun_005ce6bb(dat_00865510, 16, 10, reinterpret_cast<OriginalElementCallback>(FUN_0041fef0),
                 reinterpret_cast<OriginalElementCallback>(FUN_0041ff00));
    (void)fun_005ccf60(fun_006b8aa0);
}
extern "C" void fun_006b8aa0() {
    fun_005cdcbc(dat_00865510, 16, 10, reinterpret_cast<OriginalElementCallback>(FUN_0041ff00));
}
extern "C" void fun_006b6270() {
    fun_005ce6bb(dat_008654f0, 16, 2, reinterpret_cast<OriginalElementCallback>(FUN_0041fef0),
                 reinterpret_cast<OriginalElementCallback>(FUN_0041ff00));
    (void)fun_005ccf60(fun_006b8b00);
}
extern "C" void fun_006b8b00() {
    fun_005cdcbc(dat_008654f0, 16, 2, reinterpret_cast<OriginalElementCallback>(FUN_0041ff00));
}
extern "C" void fun_006b7920() {
    fun_005ce6bb(dat_0224ebf8, 28, 4, reinterpret_cast<OriginalElementCallback>(FUN_0040ab50),
                 reinterpret_cast<OriginalElementCallback>(FUN_00529db0));
    (void)fun_005ccf60(fun_006badd0);
}
extern "C" void fun_006badd0() {
    fun_005cdcbc(dat_0224ebf8, 28, 4, reinterpret_cast<OriginalElementCallback>(FUN_00529db0));
}
