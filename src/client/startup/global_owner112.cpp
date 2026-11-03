#include "core/owner112.h"
#include "runtime/exit_registry.h"
extern "C" {
OriginalOwner112 dat_00865170{}, dat_008651e0{};
void fun_006b6180() {
    shaiya::ui::FUN_0052d480(&dat_00865170);
    fun_005ccf60(fun_006b8a00);
}
void fun_006b61a0() {
    shaiya::ui::FUN_0052d480(&dat_008651e0);
    fun_005ccf60(fun_006b8a10);
}
void fun_006b8a00() {
    shaiya::ui::FUN_0052d500(&dat_00865170);
}
void fun_006b8a10() {
    shaiya::ui::FUN_0052d500(&dat_008651e0);
}
}
