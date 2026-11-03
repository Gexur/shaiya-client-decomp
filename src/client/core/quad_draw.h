#pragma once
#include <stdint.h>

extern "C" {
uint32_t __attribute__((thiscall)) FUN_00549a70(void*, uint32_t x, uint32_t y);
uint32_t __attribute__((thiscall)) FUN_00549ba0(void*, uint32_t color, uint32_t x, uint32_t y,
                                                uint32_t width, uint32_t height, uint32_t u0,
                                                uint32_t u1, uint32_t v0, uint32_t v1);
uint32_t __attribute__((thiscall))
native_server_row_highlight(void*, uint32_t color, uint32_t x, uint32_t y, uint32_t width,
                            uint32_t height, uint32_t u0, uint32_t u1, uint32_t v0, uint32_t v1);
}
