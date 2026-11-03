// Generated from fully operand-checked original instructions.

#include "global_ownership.h"

#include "runtime/allocations.h"

#include "runtime/exit_registry.h"
#include "graphics/native_resources.h"

namespace {

void release_slot(OriginalComObject*& slot) {

    OriginalComObject* current = slot;

    if (current != nullptr) {

        shaiya::graphics::native::release_asset_resource(current);

        slot = nullptr;
    }
}

} // namespace

extern "C" {

OriginalRawVector dat_00864d4c = {};

void fun_006b8390() {

    if (dat_00864d4c.begin != nullptr)
        fun_005cc620(dat_00864d4c.begin);

    dat_00864d4c.begin = nullptr;
    dat_00864d4c.end = nullptr;
    dat_00864d4c.capacity_end = nullptr;
}

void fun_006b5d60() {
    (void)fun_005ccf60(fun_006b8390);
}

OriginalRawVector dat_00864d3c = {};

void fun_006b83d0() {

    if (dat_00864d3c.begin != nullptr)
        fun_005cc620(dat_00864d3c.begin);

    dat_00864d3c.begin = nullptr;
    dat_00864d3c.end = nullptr;
    dat_00864d3c.capacity_end = nullptr;
}

void fun_006b5d70() {
    (void)fun_005ccf60(fun_006b83d0);
}

OriginalRawVector dat_00864d1c = {};

void fun_006b8410() {

    if (dat_00864d1c.begin != nullptr)
        fun_005cc620(dat_00864d1c.begin);

    dat_00864d1c.begin = nullptr;
    dat_00864d1c.end = nullptr;
    dat_00864d1c.capacity_end = nullptr;
}

void fun_006b5d80() {
    (void)fun_005ccf60(fun_006b8410);
}

OriginalRawVector dat_00864d2c = {};

void fun_006b8450() {

    if (dat_00864d2c.begin != nullptr)
        fun_005cc620(dat_00864d2c.begin);

    dat_00864d2c.begin = nullptr;
    dat_00864d2c.end = nullptr;
    dat_00864d2c.capacity_end = nullptr;
}

void fun_006b5d90() {
    (void)fun_005ccf60(fun_006b8450);
}

OriginalRawVector dat_0220aa34 = {};

void fun_006b9c80() {

    if (dat_0220aa34.begin != nullptr)
        fun_005cc620(dat_0220aa34.begin);

    dat_0220aa34.begin = nullptr;
    dat_0220aa34.end = nullptr;
    dat_0220aa34.capacity_end = nullptr;
}

void fun_006b6e80() {
    (void)fun_005ccf60(fun_006b9c80);
}

OriginalRawVector dat_0224e710 = {};

void fun_006bab40() {

    if (dat_0224e710.begin != nullptr)
        fun_005cc620(dat_0224e710.begin);

    dat_0224e710.begin = nullptr;
    dat_0224e710.end = nullptr;
    dat_0224e710.capacity_end = nullptr;
}

void fun_006b77f0() {
    (void)fun_005ccf60(fun_006bab40);
}

OriginalTextureComOwner16 dat_0071cfc8 = {};

void fun_006b7fc0() {

    release_slot(dat_0071cfc8.first);

    release_slot(dat_0071cfc8.second);
}

void fun_006b5a60() {
    (void)fun_005ccf60(fun_006b7fc0);
}

OriginalComPair dat_00864d68 = {};

void fun_006b84f0() {

    release_slot(dat_00864d68.first);

    release_slot(dat_00864d68.second);
}

void fun_006b5e00() {
    (void)fun_005ccf60(fun_006b84f0);
}

OriginalTextureComOwner16 dat_00864e8c = {};

void fun_006b8a60() {

    release_slot(dat_00864e8c.first);

    release_slot(dat_00864e8c.second);
}

void fun_006b6220() {
    (void)fun_005ccf60(fun_006b8a60);
}

OriginalTextureComOwner16 dat_00864e9c = {};

void fun_006b8ac0() {

    release_slot(dat_00864e9c.first);

    release_slot(dat_00864e9c.second);
}

void fun_006b6260() {
    (void)fun_005ccf60(fun_006b8ac0);
}

OriginalTextureComOwner16 dat_00864eac = {};

void fun_006b8b20() {

    release_slot(dat_00864eac.first);

    release_slot(dat_00864eac.second);
}

void fun_006b62a0() {
    (void)fun_005ccf60(fun_006b8b20);
}

OriginalTextureComOwner16 dat_00864ebc = {};

void fun_006b8b60() {

    release_slot(dat_00864ebc.first);

    release_slot(dat_00864ebc.second);
}

void fun_006b62b0() {
    (void)fun_005ccf60(fun_006b8b60);
}

OriginalTextureComOwner16 dat_02202044 = {};

void fun_006b9280() {

    release_slot(dat_02202044.first);

    release_slot(dat_02202044.second);
}

void fun_006b67d0() {
    (void)fun_005ccf60(fun_006b9280);
}

OriginalTextureComOwner16 dat_022032fc = {};

void fun_006b94d0() {

    release_slot(dat_022032fc.first);

    release_slot(dat_022032fc.second);
}

void fun_006b6950() {
    (void)fun_005ccf60(fun_006b94d0);
}

OriginalTextureComOwner16 dat_0220330c = {};

void fun_006b9510() {

    release_slot(dat_0220330c.first);

    release_slot(dat_0220330c.second);
}

void fun_006b6960() {
    (void)fun_005ccf60(fun_006b9510);
}

OriginalTextureComOwner16 dat_0220331c = {};

void fun_006b9550() {

    release_slot(dat_0220331c.first);

    release_slot(dat_0220331c.second);
}

void fun_006b6970() {
    (void)fun_005ccf60(fun_006b9550);
}

OriginalTextureComOwner16 dat_0220332c = {};

void fun_006b9590() {

    release_slot(dat_0220332c.first);

    release_slot(dat_0220332c.second);
}

void fun_006b6980() {
    (void)fun_005ccf60(fun_006b9590);
}

OriginalTextureComOwner16 dat_0220333c = {};

void fun_006b95d0() {

    release_slot(dat_0220333c.first);

    release_slot(dat_0220333c.second);
}

void fun_006b6990() {
    (void)fun_005ccf60(fun_006b95d0);
}

OriginalTextureComOwner16 dat_02203368 = {};

void fun_006b9730() {

    release_slot(dat_02203368.first);

    release_slot(dat_02203368.second);
}

void fun_006b6a60() {
    (void)fun_005ccf60(fun_006b9730);
}
}

__asm__(".globl _dat_00864d50\n.set _dat_00864d50, _dat_00864d4c+4\n");

__asm__(".globl _dat_00864d54\n.set _dat_00864d54, _dat_00864d4c+8\n");

__asm__(".globl _dat_00864d40\n.set _dat_00864d40, _dat_00864d3c+4\n");

__asm__(".globl _dat_00864d44\n.set _dat_00864d44, _dat_00864d3c+8\n");

__asm__(".globl _dat_00864d20\n.set _dat_00864d20, _dat_00864d1c+4\n");

__asm__(".globl _dat_00864d24\n.set _dat_00864d24, _dat_00864d1c+8\n");

__asm__(".globl _dat_00864d30\n.set _dat_00864d30, _dat_00864d2c+4\n");

__asm__(".globl _dat_00864d34\n.set _dat_00864d34, _dat_00864d2c+8\n");

__asm__(".globl _dat_00864d18\n.set _dat_00864d18, _dat_00864d1c-4\n");

__asm__(".globl _dat_00864d28\n.set _dat_00864d28, _dat_00864d2c-4\n");

__asm__(".globl _dat_00864d38\n.set _dat_00864d38, _dat_00864d3c-4\n");

__asm__(".globl _dat_00864d48\n.set _dat_00864d48, _dat_00864d4c-4\n");
