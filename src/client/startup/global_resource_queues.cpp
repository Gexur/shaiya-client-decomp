#include "global_resource_queues.h"
#include "core/resource_queue.h"
#include "runtime/exit_registry.h"
extern "C" {
alignas(4) uint8_t dat_0224e560[53] = {}, dat_0224e5a8[50] = {}, dat_0224e5f0[50] = {};
void fun_006b76c0() {
    FUN_005afe30(dat_0224e560);
    (void)fun_005ccf60(fun_006ba840);
}
void fun_006ba840() {
    FUN_005afea0(dat_0224e560);
}
void fun_006b76e0() {
    FUN_005afe30(dat_0224e5a8);
    (void)fun_005ccf60(fun_006ba850);
}
void fun_006ba850() {
    FUN_005afea0(dat_0224e5a8);
}
void fun_006b7700() {
    FUN_005b0890(dat_0224e5f0);
    (void)fun_005ccf60(fun_006ba860);
}
void fun_006ba860() {
    FUN_005b0900(dat_0224e5f0);
}
}

__asm__(".globl _dat_0224e591\n.set _dat_0224e591, _dat_0224e560+49\n");
