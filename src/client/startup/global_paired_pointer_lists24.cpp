#include "startup/global_paired_pointer_lists24.h"
#include "runtime/exit_registry.h"
extern "C" {
OriginalPairedPointerLists24 dat_0070be74 = {dat_006ccb64, nullptr, nullptr, nullptr, 0, 0};
void fun_006b7450() {
    (void)fun_005ccf60(fun_006ba440);
}
void fun_006ba440() {
    dat_0070be74.vtable = dat_006ccb64;
    (void)FUN_0055ab50(&dat_0070be74);
}
}

__asm__(".globl _dat_0070be84\n.set _dat_0070be84, _dat_0070be74+16\n");

__asm__(".globl _dat_0070be7c\n.set _dat_0070be7c, _dat_0070be74+8\n");

__asm__(".globl _dat_0070be78\n.set _dat_0070be78, _dat_0070be74+4\n");

__asm__(".globl _dat_0070be88\n.set _dat_0070be88, _dat_0070be74+20\n");

__asm__(".globl _dat_0070be80\n.set _dat_0070be80, _dat_0070be74+12\n");
