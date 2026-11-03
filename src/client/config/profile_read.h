#pragma once
#include "core/string.h"
namespace shaiya::startup {
struct Pair_0040abc0;
}

/**
 * @brief Read an INI string using the stored filename, selected section and supplied default.
 *
 * The x86 bridge preserves argument-read order, stack layout, security-cookie checks and RET12. Recovered Ep5.4 entry: 0x005c0de0.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param key Configuration key whose stored bytes and length are used.
 * @param output_and_default Initialized default string replaced with the profile-read result.
 * @param optional_section Requested section, or the sentinel that keeps the stored section unchanged.
 * @return The original register result with AL set to one.
 */
extern "C" uint32_t __attribute__((thiscall))
read_profile_string(shaiya::startup::Pair_0040abc0* self,
                    const shaiya::startup::String_00405710* key,
                    shaiya::startup::String_00405710* output_and_default,
                    const shaiya::startup::String_00405710* optional_section);
