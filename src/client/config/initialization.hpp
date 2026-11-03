#pragma once

#include <stdint.h>

namespace shaiya::config {
using u32 = unsigned int;

// Only the offsets accessed by the three audio setters are represented. This
// is an observed storage prefix, not a claim about an original class name.
struct Fields_00539db0 {
    unsigned char unknown_000[0xca0];
    void* field_ca0;
    unsigned char unknown_ca4[8];
    void* field_cac;
    unsigned char unknown_cb0[8];
    void* field_cb8;
    unsigned char unknown_cbc[8];
    void* field_cc4;
    unsigned char unknown_cc8[8];
    void* field_cd0;
    unsigned char unknown_cd4[0x58];
    int32_t field_d2c, field_d30, field_d34;
};
static_assert(__builtin_offsetof(Fields_00539db0, field_ca0) == 0xca0);
static_assert(__builtin_offsetof(Fields_00539db0, field_cd0) == 0xcd0);
static_assert(__builtin_offsetof(Fields_00539db0, field_d2c) == 0xd2c);
static_assert(sizeof(Fields_00539db0) == 0xd38);

struct Interface_005a87d0;
/// Query audio status through an output DWORD; callers consume only bit zero.
using Callback_024 = int32_t(__attribute__((stdcall)) *)(Interface_005a87d0* audio_interface,
                                                         u32* status);
/// Apply a signed attenuation value through the recovered audio interface.
using Callback_03c = int32_t(__attribute__((stdcall)) *)(Interface_005a87d0* audio_interface,
                                                         int32_t attenuation);
struct VtableFields_005a87d0 {
    unsigned char unknown_000[0x24];
    Callback_024 callback_024;
    unsigned char unknown_028[0x14];
    Callback_03c callback_03c;
};
struct Interface_005a87d0 {
    VtableFields_005a87d0* callbacks;
};
struct Fields_005a87d0 {
    unsigned char unknown_000[0x840];
    Interface_005a87d0* field_840;
};
static_assert(__builtin_offsetof(VtableFields_005a87d0, callback_024) == 0x24);
static_assert(__builtin_offsetof(VtableFields_005a87d0, callback_03c) == 0x3c);
static_assert(__builtin_offsetof(Fields_005a87d0, field_840) == 0x840);

extern "C" {
// Shared original storage at 0x00708598; canonical definition is in
// startup/client_locale_storage.cpp. Keep its int32_t type across all units.
extern int32_t dat_00708598;
extern char DAT_007191e0[0x104];
extern char DAT_007198b0[16];
extern void* DAT_00719a40;
extern u32 DAT_0071993c, DAT_007198c4, DAT_007198cc, DAT_0071987c;
extern u32 DAT_007198a8, DAT_007198c8, DAT_0071986c, DAT_00719870;
extern u32 DAT_00719880, DAT_00719878, DAT_00719874, DAT_00719884;
extern u32 DAT_00719888, DAT_00719898, DAT_0071989c, DAT_007198a4;
extern u32 DAT_007198a0, DAT_00719894, DAT_0071988c, DAT_00719890;
extern u32 DAT_00719990[20], DAT_00719968[10];
extern u32 DAT_0070a4f0[20], DAT_0070a5e0[10];
extern u32 DAT_00719850, DAT_00719854, DAT_00719858, DAT_0071985c;
extern u32 DAT_00719860, DAT_00719864, DAT_007198d8, DAT_00719a44;
extern int32_t DAT_0070859c, DAT_007085a0;
extern float DAT_007085b8;
extern u32 DAT_007198dc, DAT_007198e0, DAT_007198e4, DAT_007198e8;
extern u32 DAT_007198ec, DAT_007198ac, DAT_007198f0, DAT_007198f4;
extern u32 DAT_007198f8, DAT_007198fc;
extern int32_t DAT_00719900, DAT_00719904, DAT_00719908;
extern u32 DAT_0071990c, DAT_00719910, DAT_00719914;
extern u32 DAT_00719918, DAT_0071991c, DAT_00719920, DAT_00719924;
extern u32 DAT_00719928, DAT_0071992c, DAT_00719930, DAT_00719934;
extern u32 DAT_00719938, DAT_00719940, DAT_00719944, DAT_00719948;
extern u32 DAT_0071994c, DAT_00719950, DAT_00719954, DAT_00719958;
extern u32 DAT_0071995c, DAT_00719960, DAT_0220711c;
extern unsigned char DAT_022071e0[];

// Recovered thiscall setters. The caller loads ECX with the opaque object
// address 0x022071e0 and pushes one 32-bit attenuation argument.
/**
 * @brief Store background-music attenuation and apply it to the three current music objects.
 *
 * Values at or below -5000 become -10000; later members are reloaded after callbacks. Recovered Ep5.4 entry: 0x00539db0.
 * @param object Recovered owning object whose evidenced layout is required.
 * @param attenuation Signed attenuation value passed through the original audio interface.
 */
void __attribute__((thiscall)) set_background_music_attenuation(void* object, int32_t attenuation);
/**
 * @brief Store effect-sound attenuation, mapping values at or below -5000 to -10000.
 *
 * Recovered Ep5.4 entry: 0x00539e10.
 * @param object Recovered owning object whose evidenced layout is required.
 * @param attenuation Signed attenuation value passed through the original audio interface.
 */
void __attribute__((thiscall)) set_effect_sound_attenuation(void* object, int32_t attenuation);
/**
 * @brief Store world-sound attenuation, restarting the first world object when its status requires it.
 *
 * Values at or below -5000 become -10000; both current world objects receive the stored value. Recovered Ep5.4 entry: 0x00539e30.
 * @param object Recovered owning object whose evidenced layout is required.
 * @param attenuation Signed attenuation value passed through the original audio interface.
 */
void __attribute__((thiscall)) set_world_sound_attenuation(void* object, int32_t attenuation);
// Recovered audio-object wrappers; only the evidenced vtable slots are typed.
/**
 * @brief Forward attenuation to the audio interface at object offset 0x840.
 *
 * The interface is required to be non-null. Recovered Ep5.4 entry: 0x005a87d0.
 * @param object Recovered owning object whose evidenced layout is required.
 * @param attenuation Signed attenuation value passed through the original audio interface.
 * @return The result from interface vtable slot 0x3c.
 */
int32_t __attribute__((thiscall)) set_audio_object_attenuation(void* object, int32_t attenuation);
/**
 * @brief Query bit zero of the status returned through audio interface vtable slot 0x24.
 *
 * Recovered Ep5.4 entry: 0x005a8820.
 * @param object Recovered owning object whose evidenced layout is required.
 * @return Zero for a null interface; otherwise the queried status masked to bit zero.
 */
u32 __attribute__((thiscall)) audio_object_status_bit(void* object);
// Remaining actual audio restart dependency; no production substitute.
/**
 * @brief Invoke the recovered audio restart dependency for a world-sound object.
 *
 * Recovered Ep5.4 entry: 0x005a8bd0.
 * @param object Recovered owning object whose evidenced layout is required.
 */
void __attribute__((thiscall)) FUN_005a8bd0(void* object);
// Original statically linked CRT boundaries; no substitute implementations.
/**
 * @brief Format text through the original statically linked CRT formatting entry.
 *
 * Recovered Ep5.4 entry: 0x005cd489.
 * @param destination Writable destination storage; string capacity includes its terminator.
 * @param format NUL-terminated printf-style format string.
 * @return The CRT formatting result.
 */
int __cdecl FUN_005cd489(char* destination, const char* format, ...);
/**
 * @brief Parse a decimal setting through the original statically linked CRT entry.
 *
 * Recovered Ep5.4 entry: 0x005cd365.
 * @param text NUL-terminated decimal setting text.
 * @return The recovered CRT long-integer result.
 */
long __cdecl FUN_005cd365(const char* text);

/**
 * @brief Read twenty primary and ten additional key bindings, using their original defaults.
 *
 * Recovered Ep5.4 entry: 0x00409130.
 */
__declspec(dllexport) void __cdecl load_key_binding_settings();
/**
 * @brief Apply the low, middle or high view-distance constants to their original globals.
 *
 * Only values zero, one and two update the preset globals. Recovered Ep5.4 entry: 0x00408160.
 * @param range_preset View-range selector: zero low, one middle and two high.
 */
__declspec(dllexport) void __attribute__((stdcall)) apply_view_range_preset(int32_t range_preset);
/**
 * @brief Read tutorial and video settings from CONFIG.INI into the client globals.
 *
 * Retains the original defaults and exact string comparisons for range and texture quality. Recovered Ep5.4 entry: 0x00408240.
 */
__declspec(dllexport) void __cdecl load_tutorial_and_video_settings();
/**
 * @brief Read sound settings, apply the three volume attenuations and update voice flags.
 *
 * Recovered Ep5.4 entry: 0x004089a0.
 */
__declspec(dllexport) void __cdecl load_sound_settings();
/**
 * @brief Read input, visibility and interaction settings and apply the locale-specific filter override.
 *
 * Recovered Ep5.4 entry: 0x00408bf0.
 */
__declspec(dllexport) void __cdecl load_user_settings();
/**
 * @brief Initialize configuration globals, load CONFIG.INI and choose the locale login endpoint.
 *
 * TEST_IP and INTERNAL_TEST_IP select known countries; they are not arbitrary address overrides. Recovered Ep5.4 entry: 0x00409250.
 */
__declspec(dllexport) void __cdecl initialize_client_configuration();
}
} // namespace shaiya::config
