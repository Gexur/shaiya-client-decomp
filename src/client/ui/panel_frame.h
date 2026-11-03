#pragma once
#include <stdint.h>

extern "C" {
// Originalcdecl: six DWORD arguments, caller pops24 bytes. The sixth word is
// overwritten with the computed right edge on the ordinary path.
uint32_t FUN_0050ff10(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color,
                      uint32_t alternate);
}
