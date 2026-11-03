#include "floor_data.h"
extern "C" {
// Existing canonical string objects in core/math_error.cpp remain shared.
extern const char s_006d6cb0[];
extern const char s_006d6cb8[];
extern const char s_006d6cc0[];
extern const char s_006d6cc8[];
extern const char s_006d6ce8[];
extern const char s_006d6cec[];
extern const char s_006d6cf0[];
extern const char s_006d6cf8[];
extern const char s_006d6d1c[11] = "_nextafter"; // Exact observed NUL-terminated span only.
extern const char s_006d6d28[6] = "_logb";       // Exact observed NUL-terminated span only.
extern const char s_006d6d30[4] = "_yn";         // Exact observed NUL-terminated span only.
extern const char s_006d6d34[4] = "_y1";         // Exact observed NUL-terminated span only.
extern const char s_006d6d38[4] = "_y0";         // Exact observed NUL-terminated span only.
extern const char s_006d6d3c[6] = "frexp";       // Exact observed NUL-terminated span only.
extern const char s_006d6d44[5] = "fmod";        // Exact observed NUL-terminated span only.
extern const char s_006d6d4c[7] = "_hypot";      // Exact observed NUL-terminated span only.
extern const char s_006d6d54[6] = "_cabs";       // Exact observed NUL-terminated span only.
extern const char s_006d6d5c[6] = "ldexp";       // Exact observed NUL-terminated span only.
extern const char s_006d6d64[5] = "fabs";        // Exact observed NUL-terminated span only.
extern const char s_006d6d6c[4] = "tan";         // Exact observed NUL-terminated span only.
extern const char s_006d6d70[4] = "cos";         // Exact observed NUL-terminated span only.
extern const char s_006d6d74[4] = "sin";         // Exact observed NUL-terminated span only.
extern const char s_006d6d78[5] = "sqrt";        // Exact observed NUL-terminated span only.
extern const char s_006d6d80[6] = "atan2";       // Exact observed NUL-terminated span only.
extern const char s_006d6d88[5] = "acos";        // Exact observed NUL-terminated span only.
extern const char s_006d6d90[5] = "asin";        // Exact observed NUL-terminated span only.
extern const char s_006d6d98[5] = "tanh";        // Exact observed NUL-terminated span only.
extern const char s_006d6da0[5] = "cosh";        // Exact observed NUL-terminated span only.
extern const char s_006d6da8[5] = "sinh";        // Exact observed NUL-terminated span only.
OriginalMathName dat_0070ec30[29] = {
    {0x14u, s_006d6cf8}, {0x1du, s_006d6ce8}, {0x1au, s_006d6cec}, {0x1bu, s_006d6cf0},
    {0x1fu, s_006d6da8}, {0x13u, s_006d6da0}, {0x21u, s_006d6d98}, {0xeu, s_006d6d90},
    {0xdu, s_006d6d88},  {0xfu, s_006d6cb0},  {0x10u, s_006d6d80}, {0x5u, s_006d6d78},
    {0x1eu, s_006d6d74}, {0x12u, s_006d6d70}, {0x20u, s_006d6d6c}, {0xcu, s_006d6cb8},
    {0xbu, s_006d6cc0},  {0x15u, s_006d6d64}, {0x1cu, s_006d6cc8}, {0x19u, s_006d6d5c},
    {0x11u, s_006d6d54}, {0x18u, s_006d6d4c}, {0x16u, s_006d6d44}, {0x17u, s_006d6d3c},
    {0x22u, s_006d6d38}, {0x23u, s_006d6d34}, {0x24u, s_006d6d30}, {0x25u, s_006d6d28},
    {0x26u, s_006d6d1c},
};
uint32_t dat_00719090 = 0x173f; // Original file-backed DWORD, not assumed host rounding mode.
extern const OriginalFloorVector dat_006f7420 = {
    {UINT64_C(0x3ff0000000000000), UINT64_C(0x3ff0000000000000)}};
extern const OriginalFloorVector dat_006f7430 = {{UINT64_C(0x433), UINT64_C(0x433)}};
extern const OriginalFloorVector dat_006f7440 = {
    {UINT64_C(0xbff0000000000000), UINT64_C(0x4330000000000000)}};
extern const OriginalFloorVector dat_006f7450 = {
    {UINT64_C(0x8000000000000000), UINT64_C(0x8000000000000000)}};
extern const OriginalFloorVector dat_006f7460 = {{UINT64_C(0x7ff), UINT64_C(0x0)}};
}
