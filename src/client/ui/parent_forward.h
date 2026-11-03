#pragma once
#include "parent_draw.h"
#include "startup/game_init.h"
#include "network/packets.h"
namespace shaiya::ui {
extern "C" {
u32 __attribute__((thiscall)) FUN_004a75f0(Object_004230b0*, u32 argument_word);
// Explicit normalized view of original75f0's incoming-EAX-dependent early
// return. The original entry adapter captures ECX, stack+4 and EAX exactly.
u32 recovered_004a75f0(Object_004230b0*, u32 argument_word, u32 incoming_eax);

// Raw stack words deliberately avoid inferring rendering/data semantics.
u32 __attribute__((thiscall)) FUN_004a3950(Object_004230b0*, u32, u32, u32, u32, u32, u32, u32, u32,
                                           u32, u32);
u32 __attribute__((thiscall)) FUN_004c8fb0(void*, u32);
u32 __attribute__((thiscall)) find_item_record(void*, u32, u32);
extern u8 dat_0086de50[], dat_008666dd[];
}
} // namespace shaiya::ui
