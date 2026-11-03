#include "startup/global_input_owner15016.h"

#include "core/input_owner15016.h"

#include "runtime/exit_registry.h"

extern "C" alignas(4) uint8_t dat_02203678[0x3aa8] = {};

extern "C" void fun_006b6c50() {
    FUN_00531580(dat_02203678);
    fun_005ccf60(fun_006b99e0);
}

extern "C" void fun_006b99e0() {
    FUN_005315f0(dat_02203678);
}

__asm__(".globl _dat_02203adc\n.set _dat_02203adc, _dat_02203678+1124\n");

__asm__(".globl _DAT_0220711c\n.set _DAT_0220711c, _dat_02203678+15012\n");

__asm__(".globl _dat_02203690\n.set _dat_02203690, _dat_02203678+24\n");

__asm__(".globl _dat_02203694\n.set _dat_02203694, _dat_02203678+28\n");

__asm__(".globl _dat_02203688\n.set _dat_02203688, _dat_02203678+16\n");

__asm__(".globl _dat_0220368c\n.set _dat_0220368c, _dat_02203678+20\n");
