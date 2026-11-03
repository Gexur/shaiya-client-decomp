#include <stdint.h>
extern "C" {
struct RgbByte {
    uint8_t red, green, blue;
};
struct IntegerXY {
    int32_t x, y;
};
struct FirstSkillReadRegion {
    const unsigned char* preceding_window_title;
    uint32_t numeric_values[31];
};
struct AtlTypeInfoHolder28 {
    const unsigned char* iid;
    const unsigned char* libid;
    uint16_t major, minor;
    void* type_info;
    uint32_t references;
    void* descriptor_map;
    uint32_t descriptor_count;
};
struct WindowRect16 {
    int32_t left, top, right, bottom;
};
using WindowProc32 = int32_t(__attribute__((stdcall)) *)(void*, uint32_t, uint32_t, int32_t);
struct WindowClassEx48 {
    uint32_t size, style;
    WindowProc32 procedure;
    int32_t class_extra, window_extra;
    void* instance;
    void* icon;
    void* cursor;
    void* brush;
    const char* menu;
    const char* class_name;
    void* small_icon;
};
struct WindowClassInfo80 {
    WindowClassEx48 wc;
    const char* original_name;
    WindowProc32 original_procedure;
    const char* cursor_id;
    int32_t system_cursor;
    uint16_t atom;
    char automatic_name[13];
};
struct NothrowAllocationTag {};
static_assert(sizeof(RgbByte) == 3 && sizeof(IntegerXY) == 8 &&
              sizeof(FirstSkillReadRegion) == 128 && sizeof(AtlTypeInfoHolder28) == 28 &&
              sizeof(WindowRect16) == 16 && sizeof(WindowClassEx48) == 48 &&
              sizeof(WindowClassInfo80) == 80 && sizeof(NothrowAllocationTag) == 1);
extern const unsigned char eventlog_window_text[] __asm__("_dat_006bb5bc");
extern const unsigned char interface_guid[] __asm__("_dat_006c5290");
extern const unsigned char module_guid[] __asm__("_dat_022033d8");
extern int32_t __attribute__((stdcall)) actual_window_proc(void*, uint32_t, uint32_t,
                                                           int32_t) __asm__("_FUN_00525510");
RgbByte dat_00708d24[11] = {{255, 255, 255}, {128, 255, 255}, {0, 128, 255},   {0, 255, 64},
                            {255, 255, 0},   {255, 128, 0},   {200, 200, 255}, {255, 0, 255},
                            {128, 0, 255},   {255, 128, 255}, {128, 0, 255}};
IntegerXY dat_007097e0[6] = {{270, 206}, {309, 206}, {348, 206},
                             {387, 206}, {426, 206}, {465, 206}};
FirstSkillReadRegion dat_0070b164 = {
    eventlog_window_text, {1,  2,  3,  5,  10, 15, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19,
                           19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21}};
uint32_t dat_0070b1e4[32] = {0,  1,  3,  5,  7,  12, 15, 18, 21, 21, 22, 22, 22, 23, 23, 23,
                             24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26};
uint32_t dat_0070b264[32] = {0,  1,  3,  5,  7,  12, 18, 20, 22, 24, 26, 26, 26, 27, 27, 27,
                             28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30};
uint32_t dat_0070b364[32] = {0,       100,     200,     500,     1000,    5000,    10000,
                             20000,   50000,   100000,  200000,  300000,  400000,  500000,
                             650000,  800000,  1000000, 1200000, 1400000, 1600000, 1800000,
                             2000000, 2200000, 2400000, 2600000, 2800000, 3000000, 3200000,
                             3400000, 3600000, 3800000, 4000000};
AtlTypeInfoHolder28 dat_0070b484 = {interface_guid, module_guid, 0xffff,  0xffff,
                                    nullptr,        0,           nullptr, 0};
WindowRect16 dat_0070b450 = {INT32_MIN, INT32_MIN, 0, 0};
WindowClassInfo80 dat_0070b4a0 = {{48, 11, actual_window_proc, 0, 0, nullptr, nullptr, nullptr,
                                   reinterpret_cast<void*>(6), nullptr, nullptr, nullptr},
                                  nullptr,
                                  nullptr,
                                  reinterpret_cast<const char*>(32512),
                                  1,
                                  0,
                                  {}};
WindowClassInfo80 dat_0070b508 = {{48, 11, actual_window_proc, 0, 0, nullptr, nullptr, nullptr,
                                   reinterpret_cast<void*>(6), nullptr, nullptr, nullptr},
                                  nullptr,
                                  nullptr,
                                  reinterpret_cast<const char*>(32512),
                                  1,
                                  0,
                                  {}};
char dat_0071c3e8[21] = {};
char dat_0071c400[63] = {};
NothrowAllocationTag dat_0224ee30 = {};
uint32_t dat_0224e384 = 0;
__asm__(".globl _dat_007097e4\n.set _dat_007097e4, _dat_007097e0+4\n");
__asm__(".globl _dat_00709808\n.set _dat_00709808, _dat_007097e0+40\n");
__asm__(".globl _dat_00708d26\n.set _dat_00708d26, _dat_00708d24+2\n");
__asm__(".globl _dat_00708d25\n.set _dat_00708d25, _dat_00708d24+1\n");
__asm__(".globl _dat_0070b490\n.set _dat_0070b490, _dat_0070b484+12\n");
__asm__(".globl _dat_0070b498\n.set _dat_0070b498, _dat_0070b484+20\n");
__asm__(".globl _dat_0070b4d0\n.set _dat_0070b4d0, _dat_0070b4a0+48\n");
__asm__(".globl _dat_0070b538\n.set _dat_0070b538, _dat_0070b508+48\n");
__asm__(".globl _dat_0071c3ec\n.set _dat_0071c3ec, _dat_0071c3e8+4\n");
__asm__(".globl _dat_0071c3f0\n.set _dat_0071c3f0, _dat_0071c3e8+8\n");
__asm__(".globl _dat_0071c3f4\n.set _dat_0071c3f4, _dat_0071c3e8+12\n");
__asm__(".globl _dat_0071c3f8\n.set _dat_0071c3f8, _dat_0071c3e8+16\n");
}
