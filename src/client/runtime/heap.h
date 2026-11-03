#pragma once
#include <stdint.h>
#include <stddef.h>

// The original header stride is0x14. Its reserved region is1MiB and the
// separately allocated metadata block is0x41c4 bytes. Fields follow actual
// DWORD accesses; allocation ownership and list operations remain in SBH code.
struct SmallBlockRegion {
    uint32_t class_mask_low;
    uint32_t class_mask_high;
    uint32_t uncommitted_group_mask;
    uint8_t* reserved_memory;
    uint8_t* metadata;
};
static_assert(sizeof(void*) == 4 && sizeof(SmallBlockRegion) == 0x14);
static_assert(offsetof(SmallBlockRegion, reserved_memory) == 0x0c);
static_assert(offsetof(SmallBlockRegion, metadata) == 0x10);

using OriginalNewHandler = int32_t(__attribute__((cdecl)) *)(uint32_t);

extern "C" {
extern uint32_t dat_0224ede8;
extern uint32_t dat_0224edf4;
extern OriginalNewHandler dat_0224f0b4;
extern int32_t dat_0224f0b8;
extern SmallBlockRegion* dat_022532a8;
extern uint32_t dat_022532ac;
extern SmallBlockRegion* dat_022532b0;
extern uint32_t dat_022532b4;
extern SmallBlockRegion* dat_022532b8;
extern uint32_t dat_022532bc;
extern uint32_t dat_022532c0;
extern void* dat_022532c4;
extern uint32_t dat_022532c8;

void* fun_005cfa37(uint32_t bytes);
void* fun_005cfab2(uint32_t bytes, int32_t use_new_handler);
void* fun_005cfade(uint32_t bytes);
void fun_005cfaf0(void* pointer);
void* fun_005d020a(void* pointer, uint32_t bytes);
uint32_t fun_005d96fd();
int32_t fun_005d9717(int32_t multithreaded);
int32_t fun_005da28b(uint32_t bytes);
void fun_005cfaa9();
void fun_005cfb43();
void fun_005d0372();

// Real recovered lock and small-block dependencies; these declarations never
// supply model return values or bypass an unrecovered branch.
void fun_005d659b(int32_t lock_index);
void fun_005d64e6(int32_t lock_index);
int32_t fun_005d9768(uint32_t threshold);
SmallBlockRegion* fun_005d97b0(const void* pointer);
void fun_005d97db(SmallBlockRegion* region, void* pointer);
SmallBlockRegion* fun_005d9af3();
int32_t fun_005d9baa(SmallBlockRegion* region);
int32_t fun_005d9cb0(SmallBlockRegion* region, void* pointer, uint32_t bytes);
void* fun_005d9f8f(uint32_t bytes);
}
