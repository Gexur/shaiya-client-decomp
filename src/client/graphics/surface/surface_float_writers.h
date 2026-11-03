#pragma once
#include <stdint.h>
extern "C" {
#define ROW(n) uint32_t __attribute__((thiscall)) FUN_##n(void*, uint32_t, uint32_t, const void*);
ROW(005f8751)
ROW(005f879e)
ROW(005f87f6)
ROW(005f884f)
ROW(005f8890)
ROW(005f88e3)
#undef ROW
}
