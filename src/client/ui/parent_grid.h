#pragma once
#include "parent_draw.h"
#include "font_text.h"
#include "config/initialization.hpp"

namespace shaiya::ui {
extern "C" {
// Three genuine original bodies. The first two return the selected signed
// DWORD index; the tab helper's emitted return retains the final offset312.
u32 __attribute__((thiscall)) FUN_0049ffd0(Object_004a0fd0*);

// Concrete backend bodies and complete storage extents remain unrecovered.
// Raw operands describe only the original register/stack calling contracts.
u32 __attribute__((thiscall)) FUN_00549a70(void*, u32, u32);
u32 __attribute__((thiscall)) FUN_00528b00(void*, u32, u32);
u32 __attribute__((thiscall)) FUN_00549ba0(void*, u32, u32, u32, u32, u32, u32, u32, u32, u32);
extern u8 dat_02209408[], dat_021fed20;
}
} // namespace shaiya::ui
