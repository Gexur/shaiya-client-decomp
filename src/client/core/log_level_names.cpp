#include "log_level_names.h"

using shaiya::startup::String_00405710;
extern "C" {
volatile uint32_t dat_0224e86c = 0;
String_00405710 dat_0224e850{}, dat_0224e834{}, dat_0224e818{}, dat_0224e7fc{};
String_00405710 dat_0224e7e0{}, dat_0224e7c4{}, dat_0224e78c{}, dat_0224e7a8{};
String_00405710 dat_0224e770{}, dat_0224e71c{}, dat_0224e738{}, dat_0224e754{};

// These are ordinary exit callbacks. The original bodies reset the String,
// but leave its lazy-initialization flag set.
void fun_006baae0() {
    FUN_00529db0(&dat_0224e850);
}
void fun_006baab0() {
    FUN_00529db0(&dat_0224e834);
}
void fun_006baa80() {
    FUN_00529db0(&dat_0224e818);
}
void fun_006baa50() {
    FUN_00529db0(&dat_0224e7fc);
}
void fun_006baa20() {
    FUN_00529db0(&dat_0224e7e0);
}
void fun_006ba9f0() {
    FUN_00529db0(&dat_0224e7c4);
}
void fun_006ba9c0() {
    FUN_00529db0(&dat_0224e78c);
}
void fun_006ba990() {
    FUN_00529db0(&dat_0224e7a8);
}
void fun_006ba960() {
    FUN_00529db0(&dat_0224e770);
}
void fun_006ba930() {
    FUN_00529db0(&dat_0224e71c);
}
void fun_006ba900() {
    FUN_00529db0(&dat_0224e738);
}
void fun_006ba8d0() {
    FUN_00529db0(&dat_0224e754);
}
}
