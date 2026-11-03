#include "module_array320.h"
#include "core/triple_list32.h"
#include "runtime/allocations.h"
#include "runtime/array_lifetime.h"
#include "graphics/native_render_target.h"
namespace {
using Word = uint32_t __attribute__((may_alias));
Word& word(void* self, uint32_t offset) {
    return *reinterpret_cast<Word*>(static_cast<uint8_t*>(self) + offset);
}
void __attribute__((thiscall)) construct_element(void* self) {
    (void)FUN_00548bc0(self);
}
} // namespace
extern "C" void* __attribute__((thiscall)) FUN_00548bc0(void* self) {
    for (uint32_t offset : (const uint32_t[14]){0x30, 0x34, 0x28, 0x2c, 0, 4, 0xc, 0x14, 0x10, 0x18,
                                                8, 0x1c, 0x20, 0x24})
        word(self, offset) = 0;
    *reinterpret_cast<volatile uint16_t*>(static_cast<uint8_t*>(self) + 0x13c) = 0;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_00548c00(void* self) {
    FUN_00550710(self);
}
extern "C" void* __attribute__((thiscall)) FUN_00548c10(void* self) {
    *reinterpret_cast<const OriginalModuleArrayDeleting**>(self) = dat_006c977c;
    fun_005ce6bb(static_cast<uint8_t*>(self) + 4, 0x140, 16, construct_element, FUN_00548c00);
    word(self, 0x1408) = 0;
    word(self, 0x140c) = 0;
    word(self, 0x1410) = 0;
    word(self, 0x1404) = 0x3f000000;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_00434d20(void* self) {
    uint8_t* current = static_cast<uint8_t*>(self) + 0x144;
    for (uint32_t outer = 4; outer != 0; --outer)
        for (uint32_t inner = 2; inner != 0; --inner) {
            FUN_00550710(current - 0x140);
            FUN_00550710(current);
            current += 0x280;
        }
}
extern "C" void __attribute__((thiscall)) FUN_00434cc0(void* self) {
    using namespace shaiya::graphics::native;
    release_target_scope(reinterpret_cast<TargetScope*>(word(self, 0x1408)));
    auto* texture = reinterpret_cast<Texture2D*>(word(self, 0x1410));
    if (texture != nullptr)
        texture->release();
    word(self, 0x1408) = 0;
    word(self, 0x140c) = 0; // Borrowed RTV owned by the typed texture.
    word(self, 0x1410) = 0;
}
extern "C" void* __attribute__((thiscall)) FUN_00549780(void* self, uint32_t flags) {
    FUN_00549710(self);
    if (uint8_t(flags) & 1)
        fun_005cc620(self);
    return self;
}
extern "C" const OriginalModuleArrayDeleting dat_006c977c[1] = {FUN_00549780};
