#pragma once
#include "constructors.hpp"

namespace shaiya::ui {
extern "C" {
// Original caller supplies ECX and no stack operands; RET preserves the
// selected backend's EAX. The semantic use of that return is not inferred.
u32 __attribute__((thiscall)) FUN_004a0720(Object_004a0fd0*);

// Genuine unresolved original dependencies. Pointer types below describe
// the observed register/stack contracts, not unrecovered concrete classes.
u32 __attribute__((thiscall)) FUN_00426740(void*);
u32 __attribute__((thiscall)) FUN_0049fba0(Object_004a0fd0*);
u32 __attribute__((thiscall)) FUN_004a0390(Object_004a0fd0*);
u32 __attribute__((thiscall)) FUN_00529040(void*);
u32 __attribute__((thiscall)) FUN_004a3400(Object_004230b0*, u32, u32, u32, u32, u32, u32, u32,
                                           u32);
u32 __attribute__((thiscall)) FUN_004a7680(Object_004230b0*, u32, u32, u32, u32, u32, u32, u32,
                                           u32);

// Original loader-zero storage is deliberately left unresolved. Its full
// record layout, ownership and extent have not been recovered here.
extern u32 dat_0071c2a4, dat_0071c2a8;
extern u8 dat_021fed65[];
}
} // namespace shaiya::ui
