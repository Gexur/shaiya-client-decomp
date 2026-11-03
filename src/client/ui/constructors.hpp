#pragma once

// Address-derived names deliberately avoid assigning unproved UI meanings.
// Original0052d480's first-member unwind action is recovered in
// core/owner112_seh.cpp. Parent primary-exception cleanup is recovered
// in ui/nested_owner_seh.cpp and ui/parent_owner_seh.cpp; secondary cleanup
// exception equivalence remains pending.
namespace shaiya::ui {
using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
static_assert(sizeof(void*) == 4, "The recovered client has an x86 ABI");
static_assert(sizeof(u32) == 4);

struct Object_00527000 {
    const void* vtable_000;
    u8 field_004, field_005, field_006, unknown_007;
    u32 field_008;
    u8 unknown_00c, field_00d, unknown_00e[0x3a];
    u32 fields_048[5];
    u32 fields_05c[5];
    u32 fields_070[5];
    u32 fields_084[5];
    u32 field_098, field_09c;
    u8 field_0a0, field_0a1, field_0a2, field_0a3, field_0a4;
    u8 unknown_0a5[0x0f];
    u32 fields_0b4[4];
    u32 fields_0c4[0x100];
    u8 field_4c4, unknown_4c5[0x103];
    u32 field_5c8, field_5cc;
    u8 field_5d0, unknown_5d1[3];
    u32 field_5d4;
};

struct Fields_0052d480_04c {
    u32 unknown_000;
    void* field_004;
    u32 field_008;
};

struct Object_0052d480 {
    const void* vtable_000;
    u8 field_004, unknown_005[0x1b];
    u32 field_020;
    u8 unknown_024[0x18];
    u32 field_03c;
    u8 unknown_040[4];
    u32 field_044;
    u8 field_048, unknown_049[3];
    Fields_0052d480_04c fields_04c, fields_058;
    u32 field_064, field_068, field_06c;
};

struct Object_004230b0 {
    u32 field_000;
    u8 field_004, field_005;
    u16 field_006;
    u8 field_008, unknown_009[3];
    u32 field_00c;
    u8 unknown_010[0x18];
    u8 fields_028[0x10];
    u32 field_038, field_03c;
    Object_0052d480 subobject_040;
};

struct Object_004a0fd0 {
    const void* vtable_000;
    u32 fields_004[10];
    u32 fields_02c[5][4];
    Object_00527000 subobject_07c;
    Object_004230b0 subobject_654;
    u32 field_704;
    u8 field_708, field_709, field_70a, unknown_70b;
    u32 field_70c;
    u8 unknown_710[0x110];
    u32 field_820, field_824, unknown_828;
    u32 fields_82c[0x20], fields_8ac[0x20];
    u32 field_92c;
};

#define SHAIYA_UI_OFFSET(type, field, address)                                                     \
    static_assert(__builtin_offsetof(type, field) == address)
static_assert(sizeof(Object_00527000) == 0x5d8);
SHAIYA_UI_OFFSET(Object_00527000, field_00d, 0x0d);
SHAIYA_UI_OFFSET(Object_00527000, fields_048, 0x48);
SHAIYA_UI_OFFSET(Object_00527000, fields_0c4, 0xc4);
SHAIYA_UI_OFFSET(Object_00527000, field_4c4, 0x4c4);
SHAIYA_UI_OFFSET(Object_00527000, field_5d4, 0x5d4);
static_assert(sizeof(Object_0052d480) == 0x70);
SHAIYA_UI_OFFSET(Object_0052d480, fields_04c, 0x4c);
SHAIYA_UI_OFFSET(Object_0052d480, field_06c, 0x6c);
static_assert(sizeof(Object_004230b0) == 0xb0);
SHAIYA_UI_OFFSET(Object_004230b0, fields_028, 0x28);
SHAIYA_UI_OFFSET(Object_004230b0, subobject_040, 0x40);
static_assert(sizeof(Object_004a0fd0) == 0x930);
SHAIYA_UI_OFFSET(Object_004a0fd0, fields_02c, 0x2c);
SHAIYA_UI_OFFSET(Object_004a0fd0, subobject_07c, 0x7c);
SHAIYA_UI_OFFSET(Object_004a0fd0, subobject_654, 0x654);
SHAIYA_UI_OFFSET(Object_004a0fd0, field_704, 0x704);
SHAIYA_UI_OFFSET(Object_004a0fd0, fields_82c, 0x82c);
SHAIYA_UI_OFFSET(Object_004a0fd0, fields_8ac, 0x8ac);
SHAIYA_UI_OFFSET(Object_004a0fd0, field_92c, 0x92c);
#undef SHAIYA_UI_OFFSET

extern "C" {
// Data declarations only: no fabricated vtable definitions or function entries.
using VtableAddress = void (*)();
extern const VtableAddress PTR_FUN_006c18d8[10];
using Deleting_00527760 = Object_00527000*(__attribute__((thiscall)) *)(Object_00527000*, u32);
extern const Deleting_00527760 PTR_FUN_006c57cc[1];
using Deleting_0052d550 = Object_0052d480*(__attribute__((thiscall)) *)(Object_0052d480*, u32);
extern const Deleting_0052d550 PTR_FUN_006c5850[1];
extern u8 DAT_022012e4;

// The original CRT allocation boundary remains unresolved. Both recovered
// helpers below ignore ECX in the original and return EAX.
void* FUN_005cc96d(u32 size);
void* FUN_0052cf70();
void* FUN_0052cf90();

Object_00527000* __attribute__((thiscall)) FUN_00527000(Object_00527000* self);
Object_0052d480* __attribute__((thiscall)) FUN_0052d480(Object_0052d480* self);
Object_004230b0* __attribute__((thiscall)) FUN_004230b0(Object_004230b0* self);
Object_004a0fd0* __attribute__((thiscall)) FUN_004a0fd0(Object_004a0fd0* self);

// These small vtable targets have these exact bodies in the binary. Their
// argument words are ABI placeholders; original parameter types are unknown.
u32 __attribute__((thiscall)) FUN_004a1110(void* self);
void __attribute__((thiscall)) FUN_005bfb50(void* self);
void __attribute__((thiscall)) FUN_0040a790(void* self, u32 stack_004);
void __attribute__((thiscall)) FUN_00422c10(void* self, u32 stack_004, u32 stack_008, u32 stack_00c,
                                            u32 stack_010, u32 stack_014, u32 stack_018,
                                            u32 stack_01c);
}
} // namespace shaiya::ui
