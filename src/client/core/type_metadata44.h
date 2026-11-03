#pragma once
#include "string.h"
struct OriginalTypeMetadata44;
using OriginalTypeMetadataDeleting =
    OriginalTypeMetadata44*(__attribute__((thiscall)) *)(OriginalTypeMetadata44*, uint32_t);
struct OriginalTypeMetadata44 {
    const OriginalTypeMetadataDeleting* vtable;
    uint32_t value04;
    OriginalTypeMetadata44* parent08;
    shaiya::startup::String_00405710 name0c;
    uint32_t value28;
};
static_assert(sizeof(OriginalTypeMetadata44) == 44);
static_assert(offsetof(OriginalTypeMetadata44, name0c) == 12);
static_assert(offsetof(OriginalTypeMetadata44, value28) == 40);
extern "C" {
extern const OriginalTypeMetadataDeleting dat_006d22d4[1];
extern const char dat_006d22d8[], dat_006d239c[], dat_006d23a4[], dat_006d23b0[];
extern OriginalTypeMetadata44 dat_0224ed2c, dat_0224ed58, dat_0224ed84, dat_0224edb0;
OriginalTypeMetadata44* __attribute__((thiscall)) FUN_005c45f0(OriginalTypeMetadata44*, const char*,
                                                               uint32_t value28, uint32_t value04,
                                                               OriginalTypeMetadata44* parent08);
uint32_t __attribute__((thiscall)) FUN_005c45a0(OriginalTypeMetadata44*);
OriginalTypeMetadata44* __attribute__((thiscall)) FUN_005c45d0(OriginalTypeMetadata44*,
                                                               uint32_t flags);
void fun_006b79a0();
void fun_006b79f0();
void fun_006b7a20();
void fun_006b7a50();
void fun_006bae90();
void fun_006baed0();
void fun_006baee0();
void fun_006baef0();
}
