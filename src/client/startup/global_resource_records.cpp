#include "global_resource_records.h"
#include "../runtime/array_lifetime.h"
#include "../runtime/exit_registry.h"
namespace {
// The original iterator discards each constructor's EAX result. These explicit
// type adapters retain that operation without incompatible function signatures.
void __attribute__((thiscall)) construct_record(void* value) {
    (void)FUN_0040efe0(static_cast<OriginalResourceRecord*>(value));
}
void __attribute__((thiscall)) destroy_record(void* value) {
    FUN_0040f010(static_cast<OriginalResourceRecord*>(value));
}
} // namespace
extern "C" {
OriginalResourceRecord dat_00719e88 = {}, dat_0071c570 = {}, dat_0220df28 = {};
OriginalResourceRecord dat_0071c6a0[4] = {};
void fun_006b7c90() {
    FUN_0040f010(&dat_00719e88);
}
void fun_006b5770() {
    (void)FUN_0040efe0(&dat_00719e88);
    (void)fun_005ccf60(fun_006b7c90);
}
void fun_006b7fb0() {
    FUN_0040f010(&dat_0071c570);
}
void fun_006b59f0() {
    (void)FUN_0040efe0(&dat_0071c570);
    (void)fun_005ccf60(fun_006b7fb0);
}
void fun_006b9f80() {
    FUN_0040f010(&dat_0220df28);
}
void fun_006b7020() {
    (void)FUN_0040efe0(&dat_0220df28);
    (void)fun_005ccf60(fun_006b9f80);
}
void fun_006b7f90() {
    fun_005cdcbc(dat_0071c6a0, 0x12c, 4, destroy_record);
}
void fun_006b5990() {
    fun_005ce6bb(dat_0071c6a0, 0x12c, 4, construct_record, destroy_record);
    (void)fun_005ccf60(fun_006b7f90);
}
}
