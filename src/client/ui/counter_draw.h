#pragma once
#include "parent_draw.h"
#include "font_clipped.h"
namespace shaiya::ui {
extern "C" {
// Exact observed method contract; complete class/storage layout is unknown.
extern u8 dat_02203adc[], dat_02209408[];
extern const char dat_006be170[3], dat_006bc494[5];
u32 __attribute__((thiscall)) FUN_00549a70(void*, u32, u32);
u32 __attribute__((thiscall)) FUN_00532400(void*, u32, u32, u32, u32);
u32 __attribute__((thiscall)) FUN_00545ed0(void*, u32, u32, u32, u32, u32);
u32 __attribute__((thiscall)) FUN_00531b30(void*);
u32 __attribute__((thiscall)) FUN_00532eb0(void*);
u32 __attribute__((thiscall)) FUN_00532dc0(void*);
u32 __attribute__((thiscall)) FUN_00528b00(void*, u32, u32);
}
} // namespace shaiya::ui
