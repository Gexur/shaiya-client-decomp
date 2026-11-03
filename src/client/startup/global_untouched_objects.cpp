#include "startup/global_untouched_objects.h"
#include "core/untouched_lifetime.h"
#include "runtime/exit_registry.h"
extern "C" {
uint8_t dat_0224e420[120] = {};
uint32_t dat_0224e674[3] = {};
void fun_006b7680() {
    FUN_005af140(dat_0224e420);
    (void)fun_005ccf60(fun_006ba830);
}
void fun_006ba830() {
    FUN_005aeef0(dat_0224e420);
}
void fun_006b7720() {
    FUN_004441b0(dat_0224e674);
    (void)fun_005ccf60(fun_006ba880);
}
void fun_006ba880() {
    FUN_005bfb50(dat_0224e674);
}
}

__asm__(".globl _dat_0224e67c\n.set _dat_0224e67c, _dat_0224e674+8\n");

__asm__(".globl _dat_0224e678\n.set _dat_0224e678, _dat_0224e674+4\n");
