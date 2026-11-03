#include "frame_release.h"
#include "startup/global_ownership.h"
#include "startup/game_init.h"
#include "graphics/native_resources.h"
namespace {
using u32 = uint32_t;
u32 word(const void* base, u32 offset) {
    u32 value;
    const auto* at = reinterpret_cast<const unsigned char*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
void clear(void* slot) {
    __asm__ volatile("movl $0,(%0)" ::"r"(slot) : "memory");
}
u32 release(void* slot) {
    const u32 current = word(slot, 0);
    if (current == 0)
        return current;
    auto* texture = reinterpret_cast<shaiya::graphics::native::Texture2D*>(current);
    const u32 result = static_cast<u32>(texture->references - 1);
    texture->release();
    // Clear after releasing this owner; later slots are freshly loaded.
    clear(slot);
    return result;
}
} // namespace
extern "C" u32 FUN_00510250() {
    (void)release(&dat_0220330c.first);
    (void)release(&dat_0220330c.second);
    (void)release(&dat_022032fc.first);
    (void)release(&dat_022032fc.second);
    auto* callback = reinterpret_cast<void*>(word(&dat_007191d4, 0));
    using Query = u32(__attribute__((thiscall))*)(void*, u32);
    const u32 target = word(reinterpret_cast<void*>(word(callback, 0)), 4);
    u32 result = reinterpret_cast<Query>(target)(callback, 0x4e);
    if (static_cast<uint8_t>(result) != 0) {
        result = release(&dat_0220331c.first);
        result = release(&dat_0220331c.second);
        result = release(&dat_0220332c.first);
        result = release(&dat_0220332c.second);
        result = release(&dat_0220333c.first);
        result = release(&dat_0220333c.second);
    }
    return result;
}
