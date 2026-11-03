#include "multibyte.h"
#include "locale.h"
#include "security.h"
#include "nls.h"

extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall)) GetCPInfo(uint32_t, OriginalCodePageInfo*);

uint32_t dat_0224ee64 = 0, dat_0224f258 = 0;
uint32_t dat_022533e0 = 0, dat_022533e8 = 0, dat_02253504 = 0;
uint16_t dat_02253510[6] = {};
uint8_t dat_02253400[257] = {}, dat_02253520[256] = {};
uint32_t dat_02254650 = 0;
const uint16_t* dat_0070e4d8 = &dat_006d62c6[1];
}

namespace {
uint8_t raw8(const uint8_t* pointer) {
    uint32_t value;
    __asm__ volatile("movzbl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return static_cast<uint8_t>(value);
}
uint16_t raw16(const uint16_t* pointer) {
    uint32_t value;
    __asm__ volatile("movzwl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return static_cast<uint16_t>(value);
}
void clear_classification() {
    for (uint32_t i = 0; i < 257; ++i)
        dat_02253400[i] = 0;
}
} // namespace

extern "C" uint32_t fun_005d2fa4(uint32_t code_page) {
    switch (code_page) {
    case 932:
        return 0x411;
    case 936:
        return 0x804;
    case 949:
        return 0x412;
    case 950:
        return 0x404;
    default:
        return 0;
    }
}
extern "C" void fun_005d2fd3() {
    clear_classification();
    dat_02253504 = 0;
    dat_022533e8 = 0;
    dat_022533e0 = 0;
    for (uint32_t i = 0; i < 6; ++i)
        dat_02253510[i] = 0;
}
extern "C" void fun_005d2ffc() {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    OriginalCodePageInfo info;
    if (GetCPInfo(dat_02253504, &info) == 1) {
        uint8_t input[256], lower[256], upper[256];
        uint16_t types[256];
        for (uint32_t i = 0; i < 256; ++i)
            input[i] = static_cast<uint8_t>(i);
        input[0] = 0x20;
        const uint8_t* range = info.lead_bytes;
        while (range[0] != 0) {
            for (uint32_t i = range[0]; i <= range[1]; ++i)
                input[i] = 0x20;
            range += 2;
        }
        // Return values are ignored by the binary. Raw loads retain its
        // unspecified private outputs on API failure; no fallback is invented.
        fun_005dc003(1, reinterpret_cast<const char*>(input), 256, types, dat_02253504,
                     dat_022533e0, 0);
        fun_005d9327(dat_022533e0, 0x100, reinterpret_cast<const char*>(input), 256,
                     reinterpret_cast<char*>(lower), 256, dat_02253504, 0);
        fun_005d9327(dat_022533e0, 0x200, reinterpret_cast<const char*>(input), 256,
                     reinterpret_cast<char*>(upper), 256, dat_02253504, 0);
        for (uint32_t i = 0; i < 256; ++i) {
            const uint16_t kind = raw16(types + i);
            if ((kind & 1) != 0) {
                dat_02253400[i + 1] |= 0x10;
                dat_02253520[i] = raw8(lower + i);
            } else if ((kind & 2) != 0) {
                dat_02253400[i + 1] |= 0x20;
                dat_02253520[i] = raw8(upper + i);
            } else
                dat_02253520[i] = 0;
        }
    } else {
        for (uint32_t i = 0; i < 256; ++i) {
            if (i >= 0x41 && i <= 0x5a) {
                dat_02253400[i + 1] |= 0x10;
                dat_02253520[i] = static_cast<uint8_t>(i + 0x20);
            } else if (i >= 0x61 && i <= 0x7a) {
                dat_02253400[i + 1] |= 0x20;
                dat_02253520[i] = static_cast<uint8_t>(i - 0x20);
            } else
                dat_02253520[i] = 0;
        }
    }
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
}
extern "C" int32_t fun_005d3206(uint32_t code_page) {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    int32_t result = 0;
    if (code_page == 0)
        fun_005d2fd3();
    else {
        uint32_t index = 0;
        while (index < 5 && dat_0070e520[index].code_page != code_page)
            ++index;
        if (index < 5) {
            clear_classification();
            const auto& page = dat_0070e520[index];
            for (uint32_t kind = 0; kind < 4; ++kind) {
                const uint8_t* range = page.ranges[kind];
                while (range[0] != 0 && range[1] != 0) {
                    for (uint32_t i = range[0]; i <= range[1]; ++i)
                        dat_02253400[i + 1] |= dat_0070e518[kind];
                    range += 2;
                }
            }
            dat_02253504 = code_page;
            dat_022533e8 = 1;
            dat_022533e0 = fun_005d2fa4(code_page);
            for (uint32_t i = 0; i < 6; ++i)
                dat_02253510[i] = page.information[i];
        } else {
            OriginalCodePageInfo info;
            if (GetCPInfo(code_page, &info) == 1) {
                clear_classification();
                dat_02253504 = code_page;
                dat_022533e0 = 0;
                if (info.maximum_character_bytes <= 1)
                    dat_022533e8 = 0;
                else {
                    const uint8_t* range = info.lead_bytes;
                    while (range[0] != 0 && range[1] != 0) {
                        for (uint32_t i = range[0]; i <= range[1]; ++i)
                            dat_02253400[i + 1] |= 4;
                        range += 2;
                    }
                    for (uint32_t i = 1; i < 255; ++i)
                        dat_02253400[i + 1] |= 8;
                    dat_022533e0 = fun_005d2fa4(code_page);
                    dat_022533e8 = 1;
                }
                for (uint32_t i = 0; i < 6; ++i)
                    dat_02253510[i] = 0;
            } else if (dat_0224ee64 == 0)
                result = -1;
            else
                fun_005d2fd3();
        }
    }
    if (result == 0)
        fun_005d2ffc();
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
    return result;
}
extern "C" int32_t fun_005d34ea() {
    if (dat_02254650 == 0) {
        fun_005d339a(0xfffffffdu);
        dat_02254650 = 1;
    }
    return 0;
}
extern "C" int32_t fun_005e03e4(uint32_t character, uint32_t wide_mask, uint32_t byte_mask) {
    const uint32_t value = static_cast<uint8_t>(character);
    if ((dat_02253400[value + 1] & static_cast<uint8_t>(byte_mask)) != 0)
        return 1;
    return wide_mask != 0 && (dat_0070e4d8[value] & wide_mask) != 0 ? 1 : 0;
}
extern "C" int32_t fun_005e0417(uint32_t character) {
    return fun_005e03e4(character, 0, 4);
}
