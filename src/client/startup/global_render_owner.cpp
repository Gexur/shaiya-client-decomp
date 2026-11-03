#include "graphics/render_owner.h"

#include "runtime/exit_registry.h"

extern "C" unsigned char dat_02209408[0x1628] = {};

// Original6b6e60..6b6e76 and6b9c40..6b9c4a, exact canonical receiver.

extern "C" void fun_006b6e60() {
    FUN_005435d0(dat_02209408);
    (void)fun_005ccf60(fun_006b9c40);
}

extern "C" void fun_006b9c40() {
    (void)FUN_00543870(dat_02209408);
}

__asm__(".globl _dat_02209774\n.set _dat_02209774, _dat_02209408+876\n");

__asm__(".globl _dat_022094c8\n.set _dat_022094c8, _dat_02209408+192\n");

__asm__(".globl _dat_0220981c\n.set _dat_0220981c, _dat_02209408+1044\n");

__asm__(".globl _dat_022097b4\n.set _dat_022097b4, _dat_02209408+940\n");

__asm__(".globl _dat_02209810\n.set _dat_02209810, _dat_02209408+1032\n");

__asm__(".globl _dat_02209768\n.set _dat_02209768, _dat_02209408+864\n");
