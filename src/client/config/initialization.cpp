#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "initialization.hpp"

// Original executable SHA256:
// 796af141fd13451bab67ae0bae02d2177b1fe60af51775f296bec7b0eff752da.
// Full instruction evidence: evidence/cpp-config-original-disassembly.txt.
// Strings/table provenance: evidence/cpp-config-recovery.json.
// This file retains the original endpoints; local-server policy is a separate
// source change, not inferred original behavior.
namespace shaiya::config {
namespace {
// Array index is the observed locale value; index 0 is the default branch.
const char* const locale_endpoints[] = {
    "172.17.10.205",   // Default: 0x006bbb58.
    "222.122.78.211",  // 1: 0x006bbc60.
    "61.129.54.66",    // 2: 0x006bbc50.
    "221.132.38.2",    // 3: 0x006bbc40.
    "203.92.6.66",     // 4: 0x006bbc34.
    "60.199.180.40",   // 5: 0x006bbc24.
    "174.142.118.105", // 6: 0x006bbc14.
    "217.111.23.8",    // 7: 0x006bbc04.
    "113.23.164.48",   // 8: 0x006bbbf4.
    "61.93.186.11",    // 9: 0x006bbbe4.
    "217.111.23.18",   // 10: 0x006bbbd4.
    "217.197.126.150", // 11: 0x006bbbc4.
    "217.111.23.28",   // 12: 0x006bbbb4.
    "174.120.131.85",  // 13: 0x006bbba4.
    "174.120.131.20",  // 14: 0x006bbb94.
    "213.131.234.68",  // 15: 0x006bbb84.
    "217.111.23.169",  // 16: 0x006bbb74.
    "125.5.4.14",      // 17: 0x006bbb68.
};

struct CountryEndpoint {
    const char* selector;
    const char* endpoint;
};

const CountryEndpoint test_endpoints[] = {
    {"KOREA", "172.17.10.205"},
    {"CHINA", "61.142.166.112"},
    {"CHINAPASSPOD", "61.142.166.109"},
    {"VIETNAM", "202.78.230.116"},
    {"TAIWAN", "210.242.174.104"},
    {"HONGKONG", "61.93.186.19"},
    {"JAPAN", "10.2.140.8"},
    {"ENGLISH", "174.142.118.109"},
    {"GERMANY", "217.111.23.6"},
    {"FRANCE", "217.111.23.16"},
    {"SINGA_MALA", "113.23.164.47"},
    {"RUSSIA", "195.128.95.37"},
    {"TURKEY", "217.111.23.26"},
    {"BRAZIL", "174.120.131.26"},
    {"LATIN_AMERICA", "174.120.131.12"},
    {"POLAND", "213.131.234.70"},
    {"ITALY", "217.111.23.166"},
    {"PHILIPPINES", "203.115.180.41"},
};

const CountryEndpoint internal_test_endpoints[] = {
    {"ENGLISH", "172.17.10.209"},       {"CHINA", "172.17.10.210"},   {"JAPAN", "172.17.10.211"},
    {"GERMANY", "172.17.10.212"},       {"FRANCE", "172.17.10.213"},  {"TURKEY", "172.17.10.214"},
    {"LATIN_AMERICA", "172.17.10.215"}, {"RUSSIA", "172.17.10.216"},  {"BRAZIL", "172.17.10.217"},
    {"PHILIPPINES", "172.17.10.218"},   {"VIETNAM", "172.17.10.219"}, {"TAIWAN", "172.17.10.208"},
};

// These normalize the original unrolled literal copies and fixed-length
// comparisons. Copy only through NUL; bytes beyond the copied string remain
// untouched, including when a shorter endpoint replaces a longer one.
/**
 * @brief Copy a NUL-terminated literal through its terminator without touching later bytes.
 * @param destination Writable destination storage; string capacity includes its terminator.
 * @param source Source object to copy; it retains ownership of its storage.
 */
void copy_terminated_string(char* destination, const char* source) {
    do {
        *destination++ = *source;
    } while (*source++ != '\0');
}

/**
 * @brief Compare two NUL-terminated setting strings exactly.
 * @param first First string or signed source-byte pointer, as required by the function.
 * @param second Second NUL-terminated string used for exact comparison.
 * @return True if the strings match through NUL.
 */
bool setting_strings_equal(const char* first, const char* second) {
    while (*first == *second) {
        if (*second == '\0')
            return true;
        ++first;
        ++second;
    }
    return false;
}

/**
 * @brief Select the login endpoint for an exact country selector, if present in the table.
 *
 * Leaves the current endpoint unchanged for an unrecognized selector.
 * @param country_selector Exact country token read from the LOGIN configuration section.
 * @param endpoints Table mapping country selectors to fixed login endpoints.
 */
template <unsigned count>
void select_country_endpoint(const char* country_selector,
                             const CountryEndpoint (&endpoints)[count]) {
    for (const CountryEndpoint& endpoint : endpoints) {
        if (setting_strings_equal(country_selector, endpoint.selector)) {
            copy_terminated_string(DAT_007198b0, endpoint.endpoint);
            return;
        }
    }
}

/**
 * @brief Read a setting whose only false literal is the exact uppercase string FALSE.
 * @param section NUL-terminated INI section name.
 * @param key NUL-terminated INI setting key.
 * @param fallback Setting value returned when the INI field is absent or empty.
 * @param buffer Caller-owned scratch storage of at least 0x104 bytes.
 * @return The fallback for an absent/empty setting, zero for FALSE, otherwise one.
 */
u32 read_boolean_setting(const char* section, const char* key, u32 fallback, char* buffer) {
    if (GetPrivateProfileStringA(section, key, "", buffer, 0x104, DAT_007191e0) == 0)
        return fallback;
    return setting_strings_equal(buffer, "FALSE") ? 0 : 1;
}

/**
 * @brief Read a decimal setting using the original CRT parser.
 * @param section NUL-terminated INI section name.
 * @param key NUL-terminated INI setting key.
 * @param fallback Setting value returned when the INI field is absent or empty.
 * @param buffer Caller-owned scratch storage of at least 0x104 bytes.
 * @return The fallback for an absent/empty setting, otherwise the parsed low 32 bits.
 */
u32 read_integer_setting(const char* section, const char* key, u32 fallback, char* buffer) {
    if (GetPrivateProfileStringA(section, key, "", buffer, 0x104, DAT_007191e0) == 0)
        return fallback;
    return static_cast<u32>(FUN_005cd365(buffer));
}

/**
 * @brief Convert an integer volume setting to the original x87 attenuation argument.
 *
 * Preserves the original extended-precision intermediate arithmetic for all int32 inputs.
 * @param volume_setting Original signed volume setting from CONFIG.INI.
 * @return The low 32 bits of the truncated extended-precision result.
 */
int32_t volume_setting_to_attenuation(int32_t volume_setting) {
    // 0x408a86..0x408af9 uses FILD; FMUL float(0x3e2aaaab);
    // FMUL float(0x459c4000); FSUB float(0x459c4000), then CRT 0x5cd414
    // truncates the finite result to int64 and only EAX is passed onward.
    // Preserve x87 intermediate arithmetic and truncate by its 80-bit format
    // to avoid C++ float->int32 overflow for large original DWORD settings.
    // Input int32 bounds keep this result finite and below 2^41 in magnitude.
    const long double scaled = static_cast<long double>(volume_setting) *
                                   static_cast<long double>(0x1.555556p-3f) * 5000.0L -
                               5000.0L;
    static_assert(sizeof(long double) == 12, "Recovered x86 GNU long-double ABI required");
    struct ExtendedValue {
        u32 low, high;
        uint16_t sign_exponent;
    } words;
    static_assert(__builtin_offsetof(ExtendedValue, sign_exponent) == 8);
    // Copy the ten meaningful bytes only; long-double ABI padding is not data.
    __builtin_memcpy(&words, &scaled, 10);
    const unsigned exponent = words.sign_exponent & 0x7fff;
    if (exponent < 16383)
        return 0;
    const unsigned long long significand =
        (static_cast<unsigned long long>(words.high) << 32) | words.low;
    u32 result = static_cast<u32>(significand >> (16383 + 63 - exponent));
    if (words.sign_exponent & 0x8000)
        result = 0u - result;
    return static_cast<int32_t>(result);
}
} // namespace

/**
 * @brief Forward attenuation to the audio interface at object offset 0x840.
 *
 * The interface is required to be non-null. Recovered Ep5.4 entry: 0x005a87d0.
 * @param object Recovered owning object whose evidenced layout is required.
 * @param attenuation Signed attenuation value passed through the original audio interface.
 * @return The result from interface vtable slot 0x3c.
 */
extern "C" int32_t __attribute__((thiscall)) set_audio_object_attenuation(void* object,
                                                                          int32_t attenuation) {
    // 0x005a87d0..0x005a87e3. The original has no null guard and passes both
    // object and attenuation on the stack; the indirect callee pops 8 bytes.
    auto* self = static_cast<Fields_005a87d0*>(object);
    Interface_005a87d0* target = self->field_840;
    return target->callbacks->callback_03c(target, attenuation);
}

/**
 * @brief Query bit zero of the status returned through audio interface vtable slot 0x24.
 *
 * Recovered Ep5.4 entry: 0x005a8820.
 * @param object Recovered owning object whose evidenced layout is required.
 * @return Zero for a null interface; otherwise the queried status masked to bit zero.
 */
extern "C" u32 __attribute__((thiscall)) audio_object_status_bit(void* object) {
    // 0x005a8820..0x005a884e. The original masks bit 0 of the local output
    // DWORD; Ghidra's pointer-based result is wrong.
    auto* self = static_cast<Fields_005a87d0*>(object);
    Interface_005a87d0* target = self->field_840;
    if (target == nullptr)
        return 0;
    u32 value = 0;
    target->callbacks->callback_024(target, &value);
    return value & 1;
}

/**
 * @brief Store background-music attenuation and apply it to the three current music objects.
 *
 * Values at or below -5000 become -10000; later members are reloaded after callbacks. Recovered Ep5.4 entry: 0x00539db0.
 * @param object Recovered owning object whose evidenced layout is required.
 * @param attenuation Signed attenuation value passed through the original audio interface.
 */
extern "C" void __attribute__((thiscall)) set_background_music_attenuation(void* object,
                                                                           int32_t attenuation) {
    // 0x00539db0..0x00539e0c. Keep each later member load after the preceding
    // call: a dependency may change the manager's pointers or stored value.
    auto* self = static_cast<Fields_00539db0*>(object);
    if (attenuation <= -5000)
        attenuation = -10000;
    self->field_d2c = attenuation;
    if (self->field_ca0)
        set_audio_object_attenuation(self->field_ca0, attenuation);
    if (self->field_cac)
        set_audio_object_attenuation(self->field_cac, self->field_d2c);
    if (self->field_cb8)
        set_audio_object_attenuation(self->field_cb8, self->field_d2c);
}

/**
 * @brief Store effect-sound attenuation, mapping values at or below -5000 to -10000.
 *
 * Recovered Ep5.4 entry: 0x00539e10.
 * @param object Recovered owning object whose evidenced layout is required.
 * @param attenuation Signed attenuation value passed through the original audio interface.
 */
extern "C" void __attribute__((thiscall)) set_effect_sound_attenuation(void* object,
                                                                       int32_t attenuation) {
    // 0x00539e10..0x00539e28.
    auto* self = static_cast<Fields_00539db0*>(object);
    if (attenuation <= -5000)
        attenuation = -10000;
    self->field_d30 = attenuation;
}

/**
 * @brief Store world-sound attenuation, restarting the first world object when its status requires it.
 *
 * Values at or below -5000 become -10000; both current world objects receive the stored value. Recovered Ep5.4 entry: 0x00539e30.
 * @param object Recovered owning object whose evidenced layout is required.
 * @param attenuation Signed attenuation value passed through the original audio interface.
 */
extern "C" void __attribute__((thiscall)) set_world_sound_attenuation(void* object,
                                                                      int32_t attenuation) {
    // 0x00539e30..0x00539e9a. Original status is tested in AL, not full EAX.
    auto* self = static_cast<Fields_00539db0*>(object);
    if (attenuation <= -5000)
        attenuation = -10000;
    self->field_d34 = attenuation;
    if (self->field_cc4 &&
        static_cast<unsigned char>(audio_object_status_bit(self->field_cc4)) == 0)
        FUN_005a8bd0(self->field_cc4);
    if (self->field_cc4)
        set_audio_object_attenuation(self->field_cc4, self->field_d34);
    if (self->field_cd0)
        set_audio_object_attenuation(self->field_cd0, self->field_d34);
}

/**
 * @brief Apply the low, middle or high view-distance constants to their original globals.
 *
 * Only values zero, one and two update the preset globals. Recovered Ep5.4 entry: 0x00408160.
 * @param range_preset View-range selector: zero low, one middle and two high.
 */
extern "C" void __attribute__((stdcall)) apply_view_range_preset(int32_t range_preset) {
    if (range_preset == 0) {
        DAT_00719874 = 0x43480000;
        DAT_00719884 = 0x43160000;
        DAT_00719888 = 0x43480000;
        DAT_00719898 = 0x43480000;
        DAT_0071989c = 0x42a00000;
        DAT_007198a0 = 0x42700000;
    } else if (range_preset == 1) {
        DAT_00719874 = 0x43960000;
        DAT_00719884 = 0x43480000;
        DAT_00719888 = 0x43960000;
        DAT_00719898 = 0x437a0000;
        DAT_0071989c = 0x42c80000;
        DAT_007198a0 = 0x42a00000;
    } else if (range_preset == 2) {
        DAT_00719874 = 0x43c80000;
        DAT_00719884 = 0x43480000;
        DAT_00719888 = 0x43c80000;
        DAT_00719898 = 0x43af0000;
        DAT_0071989c = 0x43160000;
        DAT_007198a0 = 0x42c80000;
    }
}

/**
 * @brief Read tutorial and video settings from CONFIG.INI into the client globals.
 *
 * Retains the original defaults and exact string comparisons for range and texture quality. Recovered Ep5.4 entry: 0x00408240.
 */
extern "C" void __cdecl load_tutorial_and_video_settings() {
    char value[0x104];
    for (char& byte : value)
        byte = 0;
    DAT_007198d8 = 0;
    DAT_00719850 = read_boolean_setting("TUTORIAL", "MOUSE", 1, value);
    DAT_00719854 = read_boolean_setting("TUTORIAL", "MOVE", 1, value);
    DAT_00719858 = read_boolean_setting("TUTORIAL", "SKILL", 1, value);
    DAT_0071985c = read_boolean_setting("TUTORIAL", "QUEST", 1, value);
    DAT_00719860 = read_boolean_setting("TUTORIAL", "LEVELUP", 1, value);
    DAT_00719864 = read_boolean_setting("TUTORIAL", "ITEM", 1, value);
    DAT_00719a44 = read_boolean_setting("VIDEO", "FULLSCREEN", 1, value);
    if (GetPrivateProfileStringA("VIDEO", "SIZE_X", "", value, 0x104, DAT_007191e0) != 0)
        DAT_0070859c = static_cast<int32_t>(FUN_005cd365(value));
    if (GetPrivateProfileStringA("VIDEO", "SIZE_Y", "", value, 0x104, DAT_007191e0) != 0)
        DAT_007085a0 = static_cast<int32_t>(FUN_005cd365(value));

    // Unrecognized dimensions leave the original SIZE globals unchanged but
    // select index 1 and the literal ratio 1.25. No guessed resize correction.
    DAT_007198dc = 1;
    bool divide_ratio = false;
    if (DAT_0070859c == 800 && DAT_007085a0 == 600)
        DAT_007198dc = 0;
    else if (DAT_0070859c == 1280 && DAT_007085a0 == 1024)
        DAT_007198dc = 2;
    else if (DAT_0070859c == 1360 && DAT_007085a0 == 768) {
        DAT_007198dc = 3;
        divide_ratio = true;
    } else if (DAT_0070859c == 1920 && DAT_007085a0 == 1200) {
        DAT_007198dc = 4;
        divide_ratio = true;
    } else if (DAT_0070859c == 1680 && DAT_007085a0 == 1050) {
        DAT_007198dc = 5;
        divide_ratio = true;
    } else if (DAT_0070859c == 1280 && DAT_007085a0 == 720) {
        DAT_007198dc = 6;
        divide_ratio = true;
    } else if (DAT_0070859c == 1600 && DAT_007085a0 == 900) {
        DAT_007198dc = 7;
        divide_ratio = true;
    }
    DAT_007085b8 = divide_ratio ? static_cast<float>(static_cast<long double>(DAT_0070859c) /
                                                     static_cast<long double>(DAT_007085a0))
                                : 1.25f;

    if (GetPrivateProfileStringA("VIDEO", "COLOR", "", value, 0x104, DAT_007191e0) == 0)
        DAT_0071987c = 1;
    else
        DAT_0071987c = FUN_005cd365(value) != 16;
    DAT_007198e0 = read_integer_setting("VIDEO", "GLOW_LEVEL", 2, value);
    DAT_007198e8 = read_integer_setting("VIDEO", "GAMMA", 2, value);
    if (GetPrivateProfileStringA("VIDEO", "RANGE", "", value, 0x104, DAT_007191e0) == 0 ||
        setting_strings_equal(value, "MIDDLE")) {
        DAT_007198e4 = 1;
        apply_view_range_preset(1);
    } else if (setting_strings_equal(value, "HIGH")) {
        DAT_007198e4 = 2;
        apply_view_range_preset(2);
    } else if (setting_strings_equal(value, "LOW")) {
        DAT_007198e4 = 0;
        apply_view_range_preset(0);
    }
    if (GetPrivateProfileStringA("VIDEO", "TEXTURE", "", value, 0x104, DAT_007191e0) == 0 ||
        setting_strings_equal(value, "HIGH")) {
        DAT_007198ac = 0xffffffff;
        DAT_007198ec = 2;
    } else if (setting_strings_equal(value, "MIDDLE")) {
        DAT_007198ec = 1;
        DAT_007198ac = 0x80;
    } else if (setting_strings_equal(value, "LOW")) {
        DAT_007198ec = 0;
        DAT_007198ac = 0x40;
    }
    DAT_00719870 = read_boolean_setting("VIDEO", "SHADOW", 1, value);
    DAT_0071986c = read_boolean_setting("VIDEO", "WATER", 0, value);
    DAT_007198f0 = read_boolean_setting("VIDEO", "CLOAK", 1, value);
    DAT_007198f4 = read_boolean_setting("VIDEO", "HELMET", 1, value);
    DAT_007198f8 = read_boolean_setting("VIDEO", "WEAPONEFF", 1, value);
    DAT_007198fc = read_boolean_setting("VIDEO", "SKILLWNDLOCK", 0, value);
}

/**
 * @brief Read sound settings, apply the three volume attenuations and update voice flags.
 *
 * Recovered Ep5.4 entry: 0x004089a0.
 */
extern "C" void __cdecl load_sound_settings() {
    char value[0x104];
    for (char& byte : value)
        byte = 0;
    DAT_00719900 = static_cast<int32_t>(read_integer_setting("SOUND", "VOL_BGM", 6, value));
    DAT_00719904 = static_cast<int32_t>(read_integer_setting("SOUND", "VOL_EFFECT", 6, value));
    DAT_00719908 = static_cast<int32_t>(read_integer_setting("SOUND", "VOL_WORLD", 6, value));
    set_background_music_attenuation(DAT_022071e0, volume_setting_to_attenuation(DAT_00719900));
    set_effect_sound_attenuation(DAT_022071e0, volume_setting_to_attenuation(DAT_00719904));
    set_world_sound_attenuation(DAT_022071e0, volume_setting_to_attenuation(DAT_00719908));
    DAT_0071990c = read_boolean_setting("SOUND", "VOICE_CHAR", 1, value);
    DAT_00719910 = read_boolean_setting("SOUND", "VOICE_NPC", 1, value);
    DAT_00719914 = read_boolean_setting("SOUND", "DANGER_DETECT", 1, value);
}

/**
 * @brief Read input, visibility and interaction settings and apply the locale-specific filter override.
 *
 * Recovered Ep5.4 entry: 0x00408bf0.
 */
extern "C" void __cdecl load_user_settings() {
    char value[0x104];
    for (char& byte : value)
        byte = 0;
    DAT_00719918 = read_boolean_setting("USER", "USE_MOUSE", 1, value);
    DAT_0071991c = read_boolean_setting("USER", "INV_MOUSE", 0, value);
    DAT_00719920 = read_boolean_setting("USER", "INV_MOUSE_UPDOWN", 0, value);
    DAT_00719924 = read_integer_setting("USER", "MOUSE_SENSITIVITY", 3, value);
    DAT_0220711c = DAT_00719924;
    DAT_00719928 = read_boolean_setting("USER", "MY_NAME", 1, value);
    DAT_0071992c = read_boolean_setting("USER", "USER_NAME", 1, value);
    DAT_00719930 = read_boolean_setting("USER", "MONSTER_NAME", 1, value);
    DAT_00719934 = read_boolean_setting("USER", "USE_FILTER", 1, value);
    if (dat_00708598 == 11)
        DAT_00719934 = 1;
    DAT_007198c4 = read_boolean_setting("USER", "SHOW_INTERFACE", 1, value);
    DAT_00719938 = DAT_007198c4;
    DAT_00719940 = read_boolean_setting("USER", "REJECT_FIGHT", 0, value);
    DAT_00719944 = read_boolean_setting("USER", "REJECT_PARTY", 0, value);
    DAT_00719948 = read_boolean_setting("USER", "WARNING_MSG", 1, value);
    DAT_0071994c = read_boolean_setting("USER", "REJECT_TRADE", 0, value);
    DAT_00719950 = read_boolean_setting("USER", "UI_REOPEN", 1, value);
    DAT_00719960 = 0;
    DAT_00719954 = read_boolean_setting("USER", "SCREEN_SWING", 1, value);
    DAT_00719958 = read_boolean_setting("USER", "TALK_BALLOON", 1, value);
    DAT_0071995c = read_boolean_setting("USER", "HIDE_DAMAGE", 0, value);
}

/**
 * @brief Read twenty primary and ten additional key bindings, using their original defaults.
 *
 * Recovered Ep5.4 entry: 0x00409130.
 */
extern "C" void __cdecl load_key_binding_settings() {
    // Original range 0x00409130..0x00409243. Default arrays retain their original
    // symbolic storage; their values and mutation policy are not guessed here.
    char key[0x104];
    char value[0x104];
    for (int index = 0; index != 20; ++index) {
        FUN_005cd489(key, "KEY%d", index);
        for (char& byte : value)
            byte = 0;
        if (GetPrivateProfileStringA("OPTION", key, "", value, 0x104, DAT_007191e0) == 0)
            DAT_00719990[index] = DAT_0070a4f0[index];
        else
            DAT_00719990[index] = static_cast<u32>(FUN_005cd365(value));
    }
    for (int index = 0; index != 10; ++index) {
        FUN_005cd489(key, "ADD_KEY%d", index);
        for (char& byte : value)
            byte = 0;
        if (GetPrivateProfileStringA("OPTION", key, "", value, 0x104, DAT_007191e0) == 0)
            DAT_00719968[index] = DAT_0070a5e0[index];
        else
            DAT_00719968[index] = static_cast<u32>(FUN_005cd365(value));
    }
}

/**
 * @brief Initialize configuration globals, load CONFIG.INI and choose the locale login endpoint.
 *
 * TEST_IP and INTERNAL_TEST_IP select known countries; they are not arbitrary address overrides. Recovered Ep5.4 entry: 0x00409250.
 */
extern "C" void __cdecl initialize_client_configuration() {
    // Original range 0x00409250..0x00409eb8. No stack parameters.
    char value[0x104];
    for (char& byte : value)
        byte = 0;
    DAT_0071993c = 1;
    DAT_007198c4 = 1;
    DAT_007198cc = 1;
    DAT_0071987c = 1;
    DAT_007198a8 = 1;
    DAT_007198c8 = 0;
    DAT_0071986c = 0;
    DAT_00719870 = 0;
    DAT_00719880 = 0x40a00000;

    const u32 locale = static_cast<u32>(dat_00708598);
    copy_terminated_string(DAT_007198b0,
                           locale_endpoints[locale >= 1 && locale <= 17 ? locale : 0]);

    // Keep the exact observed 32-bit values; float meanings are not required
    // to recover these initialization stores.
    DAT_00719878 = 0x3dcccccd;
    DAT_00719874 = 0x43c80000;
    DAT_00719884 = 0x43480000;
    DAT_00719888 = 0x43c80000;
    DAT_00719898 = 0x43af0000;
    DAT_0071989c = 0x43160000;
    DAT_007198a4 = 0x41200000;
    DAT_007198a0 = 0x42b40000;

    GetModuleFileNameA(static_cast<HMODULE>(DAT_00719a40), DAT_007191e0, 0x104);
    int length = 0;
    while (DAT_007191e0[length] != '\0')
        ++length;
    for (int i = length - 1; i >= 0; --i) {
        if (DAT_007191e0[i] == '\\') {
            DAT_007191e0[i + 1] = '\0';
            break;
        }
    }
    length = 0;
    while (DAT_007191e0[length] != '\0')
        ++length;
    copy_terminated_string(DAT_007191e0 + length, "CONFIG.INI");

    load_tutorial_and_video_settings();
    load_sound_settings();
    load_user_settings();
    load_key_binding_settings();
    DAT_00719894 = 0;
    DAT_0071988c = DAT_00719884;
    DAT_00719890 = DAT_00719888;

    // TEST_IP is a country selector, not a free-form IP override. The original
    // returns before reading INTERNAL_TEST_IP when TEST_IP is absent/empty.
    if (GetPrivateProfileStringA("LOGIN", "TEST_IP", "", value, 0x104, DAT_007191e0) == 0)
        return;
    select_country_endpoint(value, test_endpoints);
    if (GetPrivateProfileStringA("LOGIN", "INTERNAL_TEST_IP", "", value, 0x104, DAT_007191e0) != 0)
        select_country_endpoint(value, internal_test_endpoints);
}
} // namespace shaiya::config
