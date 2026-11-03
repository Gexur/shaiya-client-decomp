#include "startup/global_initializers_triple_lists.h"
#include "runtime/array_lifetime.h"
#include "runtime/exit_registry.h"

extern "C" {
OriginalTripleList32 dat_0220e468[96] = {};
OriginalTripleList32 dat_0220e268[16] = {};
void fun_006b71d0() {
    fun_005ce6bb(dat_0220e468, 32, 96, reinterpret_cast<OriginalElementCallback>(FUN_00553640),
                 reinterpret_cast<OriginalElementCallback>(FUN_00553660));
    (void)fun_005ccf60(fun_006ba170);
}
void fun_006ba170() {
    fun_005cdcbc(dat_0220e468, 32, 96, reinterpret_cast<OriginalElementCallback>(FUN_00553660));
}
void fun_006b7200() {
    fun_005ce6bb(dat_0220e268, 32, 16, reinterpret_cast<OriginalElementCallback>(FUN_00553640),
                 reinterpret_cast<OriginalElementCallback>(FUN_00553660));
    (void)fun_005ccf60(fun_006ba190);
}
void fun_006ba190() {
    fun_005cdcbc(dat_0220e268, 32, 16, reinterpret_cast<OriginalElementCallback>(FUN_00553660));
}
}

__asm__(".globl _dat_0220e278\n.set _dat_0220e278, _dat_0220e268+16\n");

__asm__(".globl _dat_0220e478\n.set _dat_0220e478, _dat_0220e468+16\n");
