#pragma once
#include <stdint.h>
extern "C" {
// Original custom ABI: ESI=source_count, EDI=destination_count, one actual
// stack flag and RET4. A caller must supply both evidenced register inputs.
void* __attribute__((stdcall)) FUN_005eea1a(uint32_t);
void* recovered_005eea1a(const uint32_t*, uint32_t, uint32_t);
}
