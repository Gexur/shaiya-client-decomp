#pragma once
#include "parent_draw.h"
#include "core/item_classify.h"
#include "startup/global_ownership.h"
#include "startup/global_initializers_arrays.h"
#include "startup/game_init.h"
#include "network/packets.h"
namespace shaiya::ui {
extern "C" {
extern const char dat_006c1020[4];
extern u8 dat_0086de50[], dat_02209408[];
u32 __attribute__((thiscall)) find_item_record(void*, u32, u32);
u32 __attribute__((thiscall)) FUN_00549ba0(void*, u32, u32, u32, u32, u32, u32, u32, u32, u32);
// Actual stack formatter/drawing boundary: this address is cdecl variadic.
u32 FUN_00541820(void*, u32, u32, u32, u32, u32, u32, const char*, ...);
u32 recovered_004a3400(u32* original_arguments);
}
} // namespace shaiya::ui
