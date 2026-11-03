#include "../core/type_metadata44.h"
#include "../runtime/exit_registry.h"
extern "C" {
const char dat_006d22d8[] = "gsUnknown";
const char dat_006d239c[] = "gsFile";
const char dat_006d23a4[] = "gsMemFile";
const char dat_006d23b0[] = "gsLookFile";
OriginalTypeMetadata44 dat_0224ed2c = {}, dat_0224ed58 = {}, dat_0224ed84 = {}, dat_0224edb0 = {};
}
extern "C" void fun_006b79a0() {
    FUN_005c45f0(&dat_0224ed2c, dat_006d22d8, 4, 0, nullptr);
    (void)fun_005ccf60(fun_006bae90);
}
extern "C" void fun_006b79f0() {
    FUN_005c45f0(&dat_0224ed58, dat_006d239c, 40, 0, &dat_0224ed2c);
    (void)fun_005ccf60(fun_006baed0);
}
extern "C" void fun_006b7a20() {
    FUN_005c45f0(&dat_0224ed84, dat_006d23a4, 56, 0, &dat_0224ed58);
    (void)fun_005ccf60(fun_006baee0);
}
extern "C" void fun_006b7a50() {
    FUN_005c45f0(&dat_0224edb0, dat_006d23b0, 56, 0, &dat_0224ed58);
    (void)fun_005ccf60(fun_006baef0);
}
extern "C" void fun_006bae90() {
    (void)FUN_005c45a0(&dat_0224ed2c);
}
extern "C" void fun_006baed0() {
    (void)FUN_005c45a0(&dat_0224ed58);
}
extern "C" void fun_006baee0() {
    (void)FUN_005c45a0(&dat_0224ed84);
}
extern "C" void fun_006baef0() {
    (void)FUN_005c45a0(&dat_0224edb0);
}
