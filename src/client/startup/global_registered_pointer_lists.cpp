#include "startup/global_registered_pointer_lists.h"
#include "runtime/exit_registry.h"
extern "C" {
OriginalPointerList16 dat_0070bd48 = {dat_006cca28, 0, 0, {0, 0, 0}, nullptr};
OriginalPointerList16 dat_0070bd58 = {dat_006cca28, 0, 0, {0, 0, 0}, nullptr};
OriginalPointerList16 dat_0070bd68 = {dat_006cca28, 0, 0, {0, 0, 0}, nullptr};
}
extern "C" void fun_006b7270() {
    (void)fun_005ccf60(fun_006ba210);
}
extern "C" void fun_006b7280() {
    (void)fun_005ccf60(fun_006ba230);
}
extern "C" void fun_006b7290() {
    (void)fun_005ccf60(fun_006ba250);
}
extern "C" void fun_006ba210() {
    dat_0070bd48.vtable = dat_006cca28;
    FUN_00434c60(&dat_0070bd48);
}
extern "C" void fun_006ba230() {
    dat_0070bd58.vtable = dat_006cca28;
    FUN_00434c60(&dat_0070bd58);
}
extern "C" void fun_006ba250() {
    dat_0070bd68.vtable = dat_006cca28;
    FUN_00434c60(&dat_0070bd68);
}

__asm__(".globl _dat_0070bd4c\n.set _dat_0070bd4c, _dat_0070bd48+4\n");

__asm__(".globl _dat_0070bd54\n.set _dat_0070bd54, _dat_0070bd48+12\n");

__asm__(".globl _dat_0070bd5c\n.set _dat_0070bd5c, _dat_0070bd58+4\n");

__asm__(".globl _dat_0070bd64\n.set _dat_0070bd64, _dat_0070bd58+12\n");
