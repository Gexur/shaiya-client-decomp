#include "startup/global_resource_lists28.h"
#include "runtime/array_lifetime.h"
#include "runtime/exit_registry.h"

extern "C" {
OriginalResourceLists28 dat_0220f2a8[40] = {};
void fun_006b7330() {
    fun_005ce6bb(dat_0220f2a8, 28, 40, reinterpret_cast<OriginalElementCallback>(FUN_00556cd0),
                 reinterpret_cast<OriginalElementCallback>(FUN_005571c0));
    (void)fun_005ccf60(fun_006ba350);
}
void fun_006ba350() {
    fun_005cdcbc(dat_0220f2a8, 28, 40, reinterpret_cast<OriginalElementCallback>(FUN_005571c0));
}
}

__asm__(".globl _dat_0220f3e8\n.set _dat_0220f3e8, _dat_0220f2a8+320\n");

__asm__(".globl _dat_0220f3f4\n.set _dat_0220f3f4, _dat_0220f2a8+332\n");

__asm__(".globl _dat_0220f3e0\n.set _dat_0220f3e0, _dat_0220f2a8+312\n");

__asm__(".globl _dat_0220f3ec\n.set _dat_0220f3ec, _dat_0220f2a8+324\n");

__asm__(".globl _dat_0220f3e4\n.set _dat_0220f3e4, _dat_0220f2a8+316\n");

__asm__(".globl _dat_0220f3f0\n.set _dat_0220f3f0, _dat_0220f2a8+328\n");
