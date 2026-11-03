#pragma once
#include <stdint.h>

extern "C" {
// Original time32 returns/stores the low 32 result bits. The unsigned interface
// preserves those bits when the original signed time_t is negative or wraps.
uint32_t __cdecl read_unix_time32(uint32_t* destination);
// Original application/global initializer; sets the canonical PRNG seed only.
void __cdecl initialize_client_prng_seed();
}
