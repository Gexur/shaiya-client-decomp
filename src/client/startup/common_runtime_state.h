#pragma once
#include <stdint.h>
#include <stddef.h>
#include "core/string.h"
// Original005bcf40 clears exactly0x74DWORDs beginning0224e870.
struct CommonSystemState {
    char cpu_name[51], cpu_vendor[13];
    uint8_t reserved40[8];
    uint32_t cpu_speed[2];
    uint16_t cpu_identifiers[5], reserved5a;
    uint32_t cpu_features;
    char os_name[260];
    uint32_t os_version[8];
    uint16_t language;
    uint8_t is_64_bit, reserved187;
    uint32_t memory[6], display[12];
};
static_assert(sizeof(CommonSystemState) == 464);
static_assert(offsetof(CommonSystemState, cpu_speed) == 72);
static_assert(offsetof(CommonSystemState, os_name) == 96);
static_assert(offsetof(CommonSystemState, os_version) == 356);
static_assert(offsetof(CommonSystemState, display) == 416);
extern "C" {
extern CommonSystemState dat_0224e870;
}
