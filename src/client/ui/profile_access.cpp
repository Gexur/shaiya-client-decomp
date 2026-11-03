#include "ui/profile_access.h"
#include "config/initialization.hpp"
#include "runtime/nls.h"
#include "runtime/stdio_format.h"

namespace shaiya::ui {
extern "C" {
char dat_02203440[34] = {}, dat_02203548[34] = {};
extern const char dat_006bb5d5[1] __attribute__((visibility("hidden")));
const char dat_006bcafc[3] = "%d";
const char dat_006c5714[16] = "INTERFACE_%dX%d";
const char dat_006c5724[19] = "INTERFACE_1600X900";
const char dat_006c5738[19] = "INTERFACE_1280X720";
const char dat_006c574c[20] = "INTERFACE_1680X1050";
const char dat_006c5760[20] = "INTERFACE_1920X1200";
const char dat_006c5774[19] = "INTERFACE_1360X768";
const char dat_006c5788[20] = "INTERFACE_1280X1024";
const char dat_006c579c[19] = "INTERFACE_1024X768";
const char dat_006c57b0[18] = "INTERFACE_800X600";
}
namespace {
using ReadProfile = uint32_t(__attribute__((stdcall)) *)(const char*, const char*, const char*,
                                                         char*, uint32_t, const char*);
using WriteProfile = int32_t(__attribute__((stdcall)) *)(const char*, const char*, const char*,
                                                         const char*);
extern "C" ReadProfile imported_read_profile __asm__("__imp__GetPrivateProfileStringA@24");
extern "C" WriteProfile imported_write_profile __asm__("__imp__WritePrivateProfileStringA@16");
uint32_t load32(const void* at) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(at) : "memory");
    return v;
}
uint16_t load16(const void* at) {
    uint16_t v;
    __asm__ volatile("movw (%1),%0" : "=r"(v) : "r"(at) : "memory");
    return v;
}
uint8_t load8(const void* at) {
    uint8_t v;
    __asm__ volatile("movb (%1),%0" : "=q"(v) : "r"(at) : "memory");
    return v;
}
void store32(void* at, uint32_t v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(at), "r"(v) : "memory");
}
void store16(void* at, uint16_t v) {
    __asm__ volatile("movw %1,(%0)" ::"r"(at), "r"(v) : "memory");
}
void store8(void* at, uint8_t v) {
    __asm__ volatile("movb %1,(%0)" ::"r"(at), "q"(v) : "memory");
}
void clear_buffer(char* at) {
    uint32_t count = 0x41;
    __asm__ volatile("rep stosl" : "+D"(at), "+c"(count) : "a"(0) : "memory");
}
template <unsigned N> void literal_section(char* output, const char (&literal)[N]) {
    static_assert(N == 18 || N == 19 || N == 20);
    const uint32_t first = load32(literal), second = load32(literal + 4),
                   third = load32(literal + 8);
    store32(output, first);
    const uint32_t fourth = load32(literal + 12);
    store32(output + 4, second);
    if constexpr (N == 20) {
        const uint32_t tail = load32(literal + 16);
        store32(output + 8, third);
        store32(output + 12, fourth);
        store32(output + 16, tail);
    } else {
        const uint16_t tail = load16(literal + 16);
        store32(output + 8, third);
        if constexpr (N == 19) {
            const uint8_t last = load8(literal + 18);
            store32(output + 12, fourth);
            store16(output + 16, tail);
            store8(output + 18, last);
        } else {
            store32(output + 12, fourth);
            store16(output + 16, tail);
        }
    }
}
void section(char* output) {
    using namespace shaiya::config;
    switch (load32(&DAT_007198dc)) {
    case 0:
        literal_section(output, dat_006c57b0);
        break;
    case 1:
        literal_section(output, dat_006c579c);
        break;
    case 2:
        literal_section(output, dat_006c5788);
        break;
    case 3:
        literal_section(output, dat_006c5774);
        break;
    case 4:
        literal_section(output, dat_006c5760);
        break;
    case 5:
        literal_section(output, dat_006c574c);
        break;
    case 6:
        literal_section(output, dat_006c5738);
        break;
    case 7:
        literal_section(output, dat_006c5724);
        break;
    default: {
        const int32_t height = static_cast<int32_t>(load32(&DAT_007085a0));
        const int32_t width = static_cast<int32_t>(load32(&DAT_0070859c));
        fun_005cd489(output, dat_006c5714, width, height);
        break;
    }
    }
}
} // namespace

// Original526820's signed comparisons use wrapped DWORD addition/subtraction.
extern "C" void __attribute__((thiscall)) FUN_00526820(void* self) {
    using namespace shaiya::config;
    auto* p = static_cast<uint8_t*>(self);
    const uint32_t w = load32(p + 12), screen_w = load32(&DAT_0070859c), x = load32(p + 4);
    if (static_cast<int32_t>(x + w) > static_cast<int32_t>(screen_w))
        store32(p + 4, screen_w - w);
    else if (static_cast<int32_t>(x) < 0)
        store32(p + 4, 0);
    const uint32_t h = load32(p + 16), y = load32(p + 8), screen_h = load32(&DAT_007085a0);
    if (static_cast<int32_t>(y + h) > static_cast<int32_t>(screen_h))
        store32(p + 8, screen_h - h);
    else if (static_cast<int32_t>(y) < 0)
        store32(p + 8, 0);
}

extern "C" char* __attribute__((thiscall)) FUN_00526870(void* self, const char* first_key,
                                                        const char* second_key, int32_t clamp) {
    using namespace shaiya::config;
    auto* p = static_cast<uint8_t*>(self);
    char text[0x104];
    clear_buffer(text);
    section(dat_02203440);
    // Original526ae3 captures the IAT target once for all calls in this entry.
    const ReadProfile read = imported_read_profile;
    uint32_t found = read(dat_02203440, first_key, dat_006bb5d5, text, 0x104, DAT_007191e0);
    if (found != 0)
        store32(p + 4, static_cast<uint32_t>(fun_005cd365(text)));
    else {
        found = read(dat_006c579c, first_key, dat_006bb5d5, text, 0x104, DAT_007191e0);
        if (found != 0) {
            store32(p + 4, static_cast<uint32_t>(fun_005cd365(text)));
            literal_section(dat_02203440, dat_006c579c);
        }
    }
    found = read(dat_02203440, second_key, dat_006bb5d5, text, 0x104, DAT_007191e0);
    if (found == 0)
        found = read(dat_006c579c, second_key, dat_006bb5d5, text, 0x104, DAT_007191e0);
    if (found != 0)
        store32(p + 8, static_cast<uint32_t>(fun_005cd365(text)));
    if (clamp == 1)
        FUN_00526820(self);
    return dat_02203440;
}

extern "C" char* __attribute__((thiscall)) FUN_00526c30(void* self, const char* first_key,
                                                        const char* second_key) {
    using namespace shaiya::config;
    auto* p = static_cast<uint8_t*>(self);
    char text[0x104];
    clear_buffer(text);
    section(dat_02203548);
    fun_005cd489(text, dat_006bcafc, static_cast<int32_t>(load32(p + 4)));
    // Original526eb5 captures the write target after the first sprintf.
    const WriteProfile write = imported_write_profile;
    (void)write(dat_02203548, first_key, text, DAT_007191e0);
    fun_005cd489(text, dat_006bcafc, static_cast<int32_t>(load32(p + 8)));
    (void)write(dat_02203548, second_key, text, DAT_007191e0);
    return dat_02203548;
}
} // namespace shaiya::ui
