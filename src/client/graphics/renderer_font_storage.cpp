#include <stdint.h>
extern "C" {
extern const unsigned char code_005df42a[] __asm__("_FUN_005df42a");
extern const unsigned char code_005df42e[] __asm__("_FUN_005df42e");
extern const unsigned char code_005df49c[] __asm__("_FUN_005df49c");
extern const unsigned char code_005df4a0[] __asm__("_FUN_005df4a0");
extern const unsigned char code_005fd2fb[] __asm__("_FUN_005fd2fb");
extern const unsigned char code_005fd341[] __asm__("_FUN_005fd341");
extern const unsigned char code_005fd36b[] __asm__("_FUN_005fd36b");
extern const unsigned char code_005fd396[] __asm__("_FUN_005fd396");
extern const unsigned char code_005fd444[] __asm__("_FUN_005fd444");
extern const unsigned char code_005fd4ee[] __asm__("_FUN_005fd4ee");
extern const unsigned char code_005fd9e2[] __asm__("_FUN_005fd9e2");
extern const unsigned char code_005fdb87[] __asm__("_FUN_005fdb87");
extern const unsigned char code_005fdc69[] __asm__("_FUN_005fdc69");
extern const unsigned char code_005fdd45[] __asm__("_FUN_005fdd45");
extern const unsigned char code_005fe4ae[] __asm__("_FUN_005fe4ae");
extern const unsigned char code_005fe9b1[] __asm__("_FUN_005fe9b1");
extern const unsigned char code_005fede9[] __asm__("_FUN_005fede9");
extern const unsigned char code_005fee06[] __asm__("_FUN_005fee06");
extern const unsigned char code_005fee4c[] __asm__("_FUN_005fee4c");
extern const unsigned char code_005feecd[] __asm__("_FUN_005feecd");
extern const unsigned char code_005fefc6[] __asm__("_FUN_005fefc6");
extern const unsigned char code_005fefde[] __asm__("_FUN_005fefde");
extern const unsigned char code_005ff000[] __asm__("_FUN_005ff000");
extern const unsigned char code_005ff00f[] __asm__("_FUN_005ff00f");
extern const unsigned char code_005ff030[] __asm__("_FUN_005ff030");
extern const unsigned char code_00600706[] __asm__("_FUN_00600706");
extern const unsigned char code_0060236c[] __asm__("_FUN_0060236c");
extern const unsigned char code_00602438[] __asm__("_FUN_00602438");
extern const unsigned char code_006024c8[] __asm__("_FUN_006024c8");
extern const unsigned char code_006025f3[] __asm__("_FUN_006025f3");
extern const unsigned char code_00602612[] __asm__("_FUN_00602612");
extern const unsigned char code_00602632[] __asm__("_FUN_00602632");
extern const unsigned char code_00602666[] __asm__("_FUN_00602666");
extern const unsigned char code_006026eb[] __asm__("_FUN_006026eb@8");
extern const unsigned char code_00620553[] __asm__("_FUN_00620553@4");
extern const void* const dat_006df828[18] = {
    code_005fee06, code_00620553, code_00600706, code_006026eb, code_005fee4c, code_005feecd,
    code_005fefc6, code_005fefde, code_005ff000, code_0060236c, code_006024c8, code_00602438,
    code_006025f3, code_00602612, code_00602632, code_00602666, code_005ff00f, code_005ff030};
extern const void* const dat_006df7dc[14] = {
    code_005fd2fb, code_00620553, code_005fede9, code_005fd341, code_005fd36b,
    code_005fd9e2, code_005fdb87, code_005fdc69, code_005fdd45, code_005fe4ae,
    code_005fe9b1, code_005fd396, code_005fd444, code_005fd4ee};
struct ScopeEntry {
    int32_t enclosing;
    const void* filter;
    const void* handler;
};
extern const ScopeEntry dat_006dbb90[2] = {{-1, code_005df42a, code_005df42e},
                                           {-1, code_005df49c, code_005df4a0}};
extern const uint16_t dat_006d6dbc[1] = {0};
extern const float dat_006be200 = -2.0f;
extern const char dat_006df870[] = "ScriptString_pSize";
extern const char dat_006df884[] = "ScriptStringCPtoX";
extern const char dat_006df898[] = "ScriptStringFree";
extern const char dat_006df8ac[] = "ScriptStringOut";
extern const char dat_006df8bc[] = "ScriptStringAnalyse";
extern const char dat_006df8d0[] = "ScriptGetFontProperties";
extern const char dat_006df8e8[] = "ScriptApplyDigitSubstitution";
extern const char dat_006df908[] = "ScriptRecordDigitSubstitution";
extern const char dat_006df928[] = "ScriptFreeCache";
extern const char dat_006df938[] = "ScriptGetProperties";
extern const char dat_006df94c[] = "ScriptTextOut";
extern const char dat_006df95c[] = "ScriptJustify";
extern const char dat_006df96c[] = "ScriptBreak";
extern const char dat_006df978[] = "ScriptPlace";
extern const char dat_006df984[] = "ScriptShape";
extern const char dat_006df990[] = "ScriptItemize";
extern const char dat_006df9a0[] = "usp10.dll";
extern const char dat_006df9ac[] = "GetFontUnicodeRanges";
extern const char dat_006df9c4[] = "GetCharWidthI";
extern const char dat_006df9d4[] = "GetCharABCWidthsI";
extern const char dat_006df9e8[] = "gdi32.dll";
struct GlyphMatrix {
    uint16_t xx_fraction;
    int16_t xx_integer;
    uint16_t xy_fraction;
    int16_t xy_integer;
    uint16_t yx_fraction;
    int16_t yx_integer;
    uint16_t yy_fraction;
    int16_t yy_integer;
};
extern const GlyphMatrix dat_006df814 = {0, 1, 0, 0, 0, 0, 0, 1};
struct VertexElement {
    uint16_t stream, offset;
    uint8_t type, method, usage, index;
};
extern const VertexElement dat_006df7bc[4] = {
    {0, 0, 2, 0, 0, 0}, {0, 12, 4, 0, 10, 0}, {0, 16, 1, 0, 5, 0}, {255, 0, 17, 0, 0, 0}};
struct InterfaceId {
    uint32_t first;
    uint16_t second, third;
    uint8_t tail[8];
};
extern const InterfaceId dat_006effe4 = {
    0xd79dbb70, 0x5f21, 0x4d36, {0xbb, 0xc2, 0xff, 0x52, 0x5c, 0x21, 0x3c, 0xdc}};
extern const InterfaceId dat_006efff4 = {
    0xba0b762d, 0x7d28, 0x43ec, {0xb9, 0xdc, 0x2f, 0x84, 0x44, 0x3b, 0x6, 0x14}};
extern const uint16_t dat_006d64ca[256] = {
    0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x68,  0x28,  0x28,  0x28,
    0x28,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,
    0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x48,  0x10,  0x10,  0x10,  0x10,  0x10,  0x10,
    0x10,  0x10,  0x10,  0x10,  0x10,  0x10,  0x10,  0x10,  0x10,  0x84,  0x84,  0x84,  0x84,
    0x84,  0x84,  0x84,  0x84,  0x84,  0x84,  0x10,  0x10,  0x10,  0x10,  0x10,  0x10,  0x10,
    0x181, 0x181, 0x181, 0x181, 0x181, 0x181, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101,
    0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101,
    0x10,  0x10,  0x10,  0x10,  0x10,  0x10,  0x182, 0x182, 0x182, 0x182, 0x182, 0x182, 0x102,
    0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102,
    0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x10,  0x10,  0x10,  0x10,  0x20,  0x20,  0x20,
    0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,
    0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,  0x20,
    0x20,  0x20,  0x20,  0x20,  0x48,  0x10,  0x10,  0x10,  0x10,  0x10,  0x10,  0x10,  0x10,
    0x10,  0x10,  0x10,  0x10,  0x10,  0x10,  0x10,  0x10,  0x10,  0x14,  0x14,  0x10,  0x10,
    0x10,  0x10,  0x10,  0x14,  0x10,  0x10,  0x10,  0x10,  0x10,  0x10,  0x101, 0x101, 0x101,
    0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101,
    0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x101, 0x10,  0x101, 0x101, 0x101, 0x101, 0x101,
    0x101, 0x101, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102,
    0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102,
    0x10,  0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102};
const uint16_t* dat_0070e4dc = dat_006d64ca;
uint32_t dat_0224f2bc = 0;
uint32_t dat_0224f34c = 0;
uint32_t dat_0224f350 = 0;
uint32_t dat_0224f360 = 0;
uint32_t dat_0224f364 = 0;
uint32_t dat_0224f368 = 0;
uint32_t dat_0224f36c = 0;
uint32_t dat_0224f370 = 0;
uint32_t dat_0224f374 = 0;
uint32_t dat_0224f378 = 0;
uint32_t dat_0224f37c = 0;
uint32_t dat_0224f380 = 0;
uint32_t dat_0224f384 = 0;
uint32_t dat_0224f388 = 0;
uint32_t dat_0224f38c = 0;
uint32_t dat_0224f390 = 0;
uint32_t dat_0224f394 = 0;
uint32_t dat_0224f398 = 0;
uint32_t dat_0224f39c = 0;
uint32_t dat_0224f3a0 = 0;
uint32_t dat_0224f3a4 = 0;
uint32_t dat_0224f3a8 = 0;
uint32_t dat_0224f3ac = 0;
uint32_t dat_0224f3b0 = 0;
uint32_t dat_0224f3b4[3] = {0, 0, 0};
uint32_t dat_0224f3c0 = 0;
}
