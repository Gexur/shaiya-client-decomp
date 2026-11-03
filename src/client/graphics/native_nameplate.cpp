#include "graphics/native_font.h"
#include "graphics/native_resources.h"
#include "runtime/allocations.h"
#include "core/x87_runtime.h"
#include "game/player/player_state_owner.h"

extern "C" {
extern uint32_t dat_0070882c, DAT_00719930;
extern unsigned char* dat_0085cfbc;
extern unsigned char dat_0071d0f0[], dat_02209408[];
void* __attribute__((thiscall)) FUN_00447ac0(void*, uint32_t);
void* __attribute__((thiscall)) FUN_00460900(void*, uint32_t);
uint32_t __attribute__((thiscall)) FUN_004cb250(void*, uint32_t);
const char* __cdecl FUN_0041d4a0(uint32_t);
shaiya::graphics::native::LabelTexture* __attribute__((thiscall)) FUN_0054a770(void*, const char*);
void __attribute__((thiscall)) FUN_00542e20(void*, float*, const float*);
}

namespace {
using namespace shaiya::graphics::native;
uint32_t& word(void* self, UINT offset) {
    return *reinterpret_cast<uint32_t*>(static_cast<unsigned char*>(self) + offset);
}
bool equal(const char* first, const char* second) {
    while (*first != 0 && *first == *second) {
        ++first;
        ++second;
    }
    return *first == *second;
}
} // namespace

extern "C" int __attribute__((stdcall)) native_candidate_text(NativeFont* font, const WCHAR* text,
                                                              int count, RECT* rectangle,
                                                              UINT flags, UINT argb) {
    return rectangle != nullptr ? draw_text(*renderer(), font, text, count, *rectangle, flags, argb)
                                : 0;
}

extern "C" void __attribute__((thiscall)) FUN_0041ffd0(void* self) {
    if (dat_0070882c == 0xffffffffu || dat_0085cfbc == nullptr || DAT_00719930 == 0 ||
        (word(&original_player_state_storage, 10144) == 0 &&
         word(dat_0085cfbc, 0x16c) == dat_0070882c))
        return;
    auto* target = static_cast<unsigned char*>(FUN_00447ac0(dat_0071d0f0, dat_0070882c));
    if (target == nullptr)
        return;
    auto* names = reinterpret_cast<unsigned char*>(&original_player_state_storage) + 34920;
    auto* name = static_cast<unsigned char*>(
        FUN_00460900(names, *reinterpret_cast<uint16_t*>(target + 0x2c)));
    const char* text =
        name != nullptr ? *reinterpret_cast<const char**>(name) : FUN_0041d4a0(0x1391);
    const uint32_t color = name != nullptr ? FUN_004cb250(&original_player_state_storage,
                                                          *reinterpret_cast<uint16_t*>(name + 6))
                                           : 0xff00ff00;
    if (text == nullptr)
        return;
    auto* cached_text = reinterpret_cast<char*>(static_cast<unsigned char*>(self) + 0xe8);
    auto* label = reinterpret_cast<LabelTexture*>(word(self, 0xe0));
    if (label == nullptr || !equal(text, cached_text)) {
        if (label != nullptr) {
            if (label->texture != nullptr)
                label->texture->release();
            fun_005cc620(label);
        }
        label = FUN_0054a770(nullptr, text);
        word(self, 0xe0) = reinterpret_cast<uint32_t>(label);
        word(self, 0xe4) = label != nullptr ? (label->width > 2 ? (label->width - 2) / 2 : 0) : 0;
        UINT index = 0;
        while (index < 259 && text[index] != 0) {
            cached_text[index] = text[index];
            ++index;
        }
        cached_text[index] = 0;
    }
    if (label == nullptr)
        return;
    const auto* position = reinterpret_cast<const float*>(target + 4);
    const float location[3] = {
        position[0], position[1] + *reinterpret_cast<const float*>(target + 0x8c), position[2]};
    float screen[3];
    FUN_00542e20(dat_02209408, screen, location);
    const int x =
        static_cast<int>(x87_to_integer_005cd414(screen[0] - static_cast<int>(word(self, 0xe4))));
    const int y = static_cast<int>(x87_to_integer_005cd414(screen[1]));
    draw_label_texture(*renderer(), *label, x, y, screen[2], color);
}
