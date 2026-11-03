#include "graphics/render_shader_owner.h"
extern "C" void __cdecl fun_005cc620(void*);
namespace {
using u32 = uint32_t;
inline u32 word(const void* self, u32 offset) {
    u32 value;
    const auto* p = static_cast<const unsigned char*>(self) + offset;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(p) : "memory");
    return value;
}
inline void clear(void* self, u32 offset) {
    auto* p = static_cast<unsigned char*>(self) + offset;
    __asm__ volatile("movl $0,(%0)" ::"r"(p) : "memory");
}
inline u32 release(void* self, u32 offset) {
    const u32 object = word(self, offset);
    if (!object)
        return 0;
    using Callback = u32(__attribute__((stdcall))*)(void*);
    const u32 table = word(reinterpret_cast<void*>(object), 0);
    const u32 result = reinterpret_cast<Callback>(word(reinterpret_cast<void*>(table), 8))(
        reinterpret_cast<void*>(object));
    clear(self, offset);
    return result;
}
inline u32 low_byte(const void* pointer) {
    u32 value;
    __asm__ volatile("movzbl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
} // namespace
// Complete543560..5435c9. The original order is not ascending field order;
// every later slot is reloaded after the preceding external COM callback.
extern "C" u32 __attribute__((thiscall, noinline)) FUN_00543560(void* self) {
    (void)release(self, 0x14);
    (void)release(self, 0x18);
    (void)release(self, 0x0c);
    (void)release(self, 0x10);
    (void)release(self, 0x1c);
    return release(self, 0x20);
}
// Complete543530..543554. Reinstall the genuine single-entry table before
// releases, then reload the original incoming flag byte and optionally free.
extern "C" void* __attribute__((thiscall)) FUN_00543530(void* self, u32 flags) {
    const u32 table = reinterpret_cast<u32>(dat_006c8398);
    __asm__ volatile("movl %1,(%0)" ::"r"(self), "r"(table) : "memory");
    (void)FUN_00543560(self);
    if (low_byte(&flags) & 1u)
        fun_005cc620(self);
    return self;
}
extern "C" const uintptr_t dat_006c8398[1] = {reinterpret_cast<uintptr_t>(&FUN_00543530)};
