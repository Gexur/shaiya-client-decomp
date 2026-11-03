#include "global_com_owners.h"
#include "../runtime/array_lifetime.h"
#include "../runtime/exit_registry.h"
namespace {
void __attribute__((thiscall)) construct_buffer(void* value) {
    (void)FUN_0040e590(static_cast<OriginalComBuffer*>(value));
}
void __attribute__((thiscall)) destroy_buffer(void* value) {
    FUN_0040ef00(&static_cast<OriginalComBuffer*>(value)->owner);
}
} // namespace
extern "C" {
OriginalComOwner dat_007086a8 = {&dat_006bc858, nullptr}, dat_007089b0 = {&dat_006bc858, nullptr};
OriginalComBuffer dat_0071cb50[4] = {};
void fun_006b7c30() {
    FUN_0040ef00(&dat_007086a8);
}
void fun_006b5760() {
    (void)fun_005ccf60(fun_006b7c30);
}
void fun_006b7f30() {
    FUN_0040ef00(&dat_007089b0);
}
void fun_006b5a10() {
    (void)fun_005ccf60(fun_006b7f30);
}
void fun_006b7f10() {
    fun_005cdcbc(dat_0071cb50, 0x110, 4, destroy_buffer);
}
void fun_006b59c0() {
    fun_005ce6bb(dat_0071cb50, 0x110, 4, construct_buffer, destroy_buffer);
    (void)fun_005ccf60(fun_006b7f10);
}
}
