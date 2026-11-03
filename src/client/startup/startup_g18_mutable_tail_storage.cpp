#include <stdint.h>
extern "C" {
struct FloatXY {
    float x, y;
};
struct KeyboardBinding24 {
    uint32_t scan_code;
    char display_name[20];
};
struct KeyboardName {
    uint32_t scan_code;
    const unsigned char* display_name;
};
struct RgbDword {
    uint32_t red, green, blue;
};
struct IconHeader {
    uint32_t x, y, flags, item_id;
};
struct IconRecord {
    IconHeader header;
    float uv[4];
};
struct IconTable {
    IconRecord rows[12];
    IconHeader sentinel;
};
struct AtlClassIdTerminator {
    const void* class_id;
};
#pragma pack(push, 1)
struct AtlExceptionType {
    const void* vtable;
    void* cached_name;
    char name[24];
};
#pragma pack(pop)
static_assert(sizeof(FloatXY) == 8 && sizeof(KeyboardBinding24) == 24 &&
              sizeof(KeyboardName) == 8 && sizeof(RgbDword) == 12 && sizeof(IconTable) == 400 &&
              sizeof(AtlExceptionType) == 32);
extern const unsigned char external_0[] __asm__("_dat_006c3f8c");
extern const unsigned char external_1[] __asm__("_dat_006c3f88");
extern const unsigned char external_2[] __asm__("_dat_006c3f84");
extern const unsigned char external_3[] __asm__("_dat_006c3f80");
extern const unsigned char external_4[] __asm__("_dat_006c3f7c");
extern const unsigned char external_5[] __asm__("_dat_006c3f78");
extern const unsigned char external_6[] __asm__("_dat_006c3f74");
extern const unsigned char external_7[] __asm__("_dat_006c3f70");
extern const unsigned char external_8[] __asm__("_dat_006c3f6c");
extern const unsigned char external_9[] __asm__("_dat_006c3f68");
extern const unsigned char external_10[] __asm__("_dat_006bfb24");
extern const unsigned char external_11[] __asm__("_dat_006c174c");
extern const unsigned char external_12[] __asm__("_dat_006c3f64");
extern const unsigned char external_13[] __asm__("_dat_006c3f5c");
extern const unsigned char external_14[] __asm__("_dat_006c3f58");
extern const unsigned char external_15[] __asm__("_dat_006c3f54");
extern const unsigned char external_16[] __asm__("_dat_006c33f8");
extern const unsigned char external_17[] __asm__("_dat_006c3f50");
extern const unsigned char external_18[] __asm__("_dat_006c3798");
extern const unsigned char external_19[] __asm__("_dat_006c3f4c");
extern const unsigned char external_20[] __asm__("_dat_006c33fc");
extern const unsigned char external_21[] __asm__("_dat_006c3f48");
extern const unsigned char external_22[] __asm__("_dat_006c3f44");
extern const unsigned char external_23[] __asm__("_dat_006c3f40");
extern const unsigned char external_24[] __asm__("_dat_006c3f3c");
extern const unsigned char external_25[] __asm__("_dat_006c3f30");
extern const unsigned char external_26[] __asm__("_dat_006c3f24");
extern const unsigned char external_27[] __asm__("_dat_006c3f1c");
extern const unsigned char external_28[] __asm__("_dat_006c3f10");
extern const unsigned char external_29[] __asm__("_dat_006c3f0c");
extern const unsigned char external_30[] __asm__("_dat_006c3f08");
extern const unsigned char external_31[] __asm__("_dat_006c3f04");
extern const unsigned char external_32[] __asm__("_dat_006c3f00");
extern const unsigned char external_33[] __asm__("_dat_006c3efc");
extern const unsigned char external_34[] __asm__("_dat_006c3ef8");
extern const unsigned char external_35[] __asm__("_dat_006c3ef4");
extern const unsigned char external_36[] __asm__("_dat_006c3ef0");
extern const unsigned char external_37[] __asm__("_dat_006c3eec");
extern const unsigned char external_38[] __asm__("_dat_006c3ee8");
extern const unsigned char external_39[] __asm__("_dat_006c3edc");
extern const unsigned char external_40[] __asm__("_dat_006c3ed4");
extern const unsigned char external_41[] __asm__("_dat_006c3ecc");
extern const unsigned char external_42[] __asm__("_dat_006bb608");
extern const unsigned char external_43[] __asm__("_dat_006c33f4");
extern const unsigned char external_44[] __asm__("_dat_006c33f0");
extern const unsigned char external_45[] __asm__("_dat_006c3ec8");
extern const unsigned char external_46[] __asm__("_dat_006c3ec4");
extern const unsigned char external_47[] __asm__("_dat_006c3ec0");
extern const unsigned char external_48[] __asm__("_dat_006c3ebc");
extern const unsigned char external_49[] __asm__("_dat_006c3eb8");
extern const unsigned char external_50[] __asm__("_dat_006c0310");
extern const unsigned char external_51[] __asm__("_dat_006c3eb4");
extern const unsigned char external_52[] __asm__("_dat_006c3eb0");
extern const unsigned char external_53[] __asm__("_dat_006c3ea8");
extern const unsigned char external_54[] __asm__("_dat_006c3ea4");
extern const unsigned char external_55[] __asm__("_dat_006c3e9c");
extern const unsigned char external_56[] __asm__("_dat_006c3e94");
extern const unsigned char external_57[] __asm__("_dat_006c3e8c");
extern const unsigned char external_58[] __asm__("_dat_006c3e88");
extern const unsigned char external_59[] __asm__("_dat_006c3e84");
extern const unsigned char external_60[] __asm__("_dat_006c3e80");
extern const unsigned char external_61[] __asm__("_dat_006c3e7c");
extern const unsigned char external_62[] __asm__("_dat_006c3e78");
extern const unsigned char external_63[] __asm__("_dat_006c3e74");
extern const unsigned char external_64[] __asm__("_dat_006c3e70");
extern const unsigned char external_65[] __asm__("_dat_006c3e6c");
extern const unsigned char external_66[] __asm__("_dat_006c3e68");
extern const unsigned char external_67[] __asm__("_dat_006c3e64");
extern const unsigned char external_68[] __asm__("_dat_006c3e5c");
extern const unsigned char external_69[] __asm__("_dat_006c3e54");
extern const unsigned char external_70[] __asm__("_dat_006c3e4c");
extern const unsigned char external_71[] __asm__("_dat_006c3e44");
extern const unsigned char external_72[] __asm__("_dat_006c3e3c");
extern const unsigned char external_73[] __asm__("_dat_006c3e34");
extern const unsigned char external_74[] __asm__("_dat_006c3e2c");
extern const unsigned char external_75[] __asm__("_dat_006c3e24");
extern const unsigned char external_76[] __asm__("_dat_006c3e20");
extern const unsigned char external_77[] __asm__("_dat_006c3e18");
extern const unsigned char external_78[] __asm__("_dat_006c3e10");
extern const unsigned char external_79[] __asm__("_dat_006c3e08");
extern const unsigned char external_80[] __asm__("_dat_006c3e00");
extern const unsigned char external_81[] __asm__("_dat_006c3df8");
extern const unsigned char external_82[] __asm__("_dat_006c3df4");
extern const unsigned char external_83[] __asm__("_dat_006c3df0");
extern const unsigned char external_84[] __asm__("_dat_006c3dec");
extern const unsigned char external_85[] __asm__("_dat_006c3de8");
extern const unsigned char external_86[] __asm__("_dat_006c3de4");
extern const unsigned char external_87[] __asm__("_dat_006c3ddc");
extern const unsigned char external_88[] __asm__("_dat_006c3dd8");
extern const unsigned char external_89[] __asm__("_dat_006c3dd0");
extern const unsigned char external_90[] __asm__("_dat_006c3dc4");
extern const unsigned char external_91[] __asm__("_dat_006c3dc0");
extern const unsigned char external_92[] __asm__("_dat_006c3dbc");
extern const unsigned char external_93[] __asm__("_dat_006c3db4");
extern const unsigned char external_94[] __asm__("_dat_006c3da8");
extern const unsigned char external_95[] __asm__("_dat_006c3da0");
extern const unsigned char external_96[] __asm__("_dat_006c3d98");
extern const unsigned char external_97[] __asm__("_dat_006c3d94");
extern const unsigned char external_98[] __asm__("_dat_006c3d88");
extern const unsigned char external_99[] __asm__("_dat_006c3d80");
extern const unsigned char external_100[] __asm__("_dat_006c3d74");
extern const unsigned char external_101[] __asm__("_dat_006c3d68");
extern const unsigned char external_102[] __asm__("_dat_006c3d60");
extern const unsigned char external_103[] __asm__("_dat_006c3d58");
extern const unsigned char external_104[] __asm__("_dat_006c3d50");
extern const unsigned char external_105[] __asm__("_dat_006c3d4c");
extern const unsigned char external_106[] __asm__("_dat_006c3d44");
extern const unsigned char external_107[] __asm__("_dat_006c3d3c");
extern const unsigned char external_108[] __asm__("_dat_006c3d34");
extern const unsigned char external_109[] __asm__("_dat_006c3d30");
extern const unsigned char external_110[] __asm__("_dat_006c3d28");
extern const unsigned char external_111[] __asm__("_dat_006c3d20");
extern const unsigned char external_112[] __asm__("_dat_006c3d18");
extern const unsigned char external_113[] __asm__("_dat_006c3d10");
extern const unsigned char external_114[] __asm__("_dat_006d5f18");
FloatXY dat_0070a2f8[14] = {
    {0x1.8000000000000p+4f, 0x1.a800000000000p+5f}, {0x1.8000000000000p+4f, 0x1.7400000000000p+6f},
    {0x1.8000000000000p+4f, 0x1.0a00000000000p+7f}, {0x1.8000000000000p+4f, 0x1.5a00000000000p+7f},
    {0x1.8000000000000p+4f, 0x1.aa00000000000p+7f}, {0x1.8800000000000p+7f, 0x1.0a00000000000p+7f},
    {0x1.8800000000000p+7f, 0x1.5a00000000000p+7f}, {0x1.8800000000000p+7f, 0x1.aa00000000000p+7f},
    {0x1.7e00000000000p+7f, 0x1.a800000000000p+5f}, {0x1.7e00000000000p+7f, 0x1.3400000000000p+6f},
    {0x1.ae00000000000p+7f, 0x1.3400000000000p+6f}, {0x1.7e00000000000p+7f, 0x1.9400000000000p+6f},
    {0x1.ae00000000000p+7f, 0x1.9400000000000p+6f}, {0x1.ae00000000000p+7f, 0x1.a800000000000p+5f}};
uint32_t dat_0070a608[31] = {59,  60, 61, 62, 63, 64, 65, 66, 67, 68, 87, 88,  183, 70,  197, 56,
                             184, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  200, 203, 205, 208};
uint32_t dat_0070a688[16] = {1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0};
uint32_t dat_02201c48[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int32_t dat_02201d68[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint32_t dat_02201db8[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int32_t dat_02202004[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
KeyboardBinding24 dat_02201ca0[8] = {};
__asm__(".globl _dat_02201ca4\n.set _dat_02201ca4, _dat_02201ca0+4\n");
KeyboardName dat_0070a6d0[120] = {
    {1, external_0},     {2, external_1},     {3, external_2},     {4, external_3},
    {5, external_4},     {6, external_5},     {7, external_6},     {8, external_7},
    {9, external_8},     {10, external_9},    {11, external_10},   {12, external_11},
    {13, external_12},   {14, external_13},   {15, external_14},   {16, external_15},
    {17, external_16},   {18, external_17},   {19, external_18},   {20, external_19},
    {21, external_20},   {22, external_21},   {23, external_22},   {24, external_23},
    {25, external_24},   {26, external_25},   {27, external_26},   {28, external_27},
    {29, external_28},   {30, external_29},   {31, external_30},   {32, external_31},
    {33, external_32},   {34, external_33},   {35, external_34},   {36, external_35},
    {37, external_36},   {38, external_37},   {39, external_38},   {40, external_39},
    {41, external_40},   {42, external_41},   {43, external_42},   {44, external_43},
    {45, external_44},   {46, external_45},   {47, external_46},   {48, external_47},
    {49, external_48},   {50, external_49},   {51, external_50},   {52, external_51},
    {53, external_52},   {54, external_53},   {55, external_54},   {56, external_55},
    {57, external_56},   {58, external_57},   {59, external_58},   {60, external_59},
    {61, external_60},   {62, external_61},   {63, external_62},   {64, external_63},
    {65, external_64},   {66, external_65},   {67, external_66},   {68, external_67},
    {69, external_68},   {70, external_69},   {71, external_70},   {72, external_71},
    {73, external_72},   {74, external_11},   {75, external_73},   {76, external_74},
    {77, external_75},   {78, external_76},   {79, external_77},   {80, external_78},
    {81, external_79},   {82, external_80},   {83, external_51},   {86, external_81},
    {87, external_82},   {88, external_83},   {100, external_84},  {101, external_85},
    {102, external_86},  {112, external_87},  {115, external_88},  {121, external_89},
    {123, external_90},  {125, external_91},  {126, external_51},  {141, external_12},
    {145, external_92},  {146, external_93},  {147, external_94},  {148, external_95},
    {149, external_96},  {150, external_97},  {151, external_98},  {156, external_99},
    {157, external_100}, {179, external_50},  {181, external_52},  {183, external_101},
    {184, external_102}, {197, external_103}, {199, external_104}, {200, external_105},
    {201, external_106}, {203, external_107}, {205, external_108}, {207, external_109},
    {208, external_110}, {209, external_111}, {210, external_112}, {211, external_113}};
__asm__(".globl _dat_0070a6d4\n.set _dat_0070a6d4, _dat_0070a6d0+4\n");
RgbDword dat_007091a8[36] = {{200, 0, 0},     {122, 0, 4},     {211, 73, 0},    {255, 142, 9},
                             {255, 144, 116}, {40, 0, 0},      {251, 232, 6},   {190, 201, 0},
                             {120, 120, 0},   {168, 161, 73},  {243, 231, 171}, {40, 40, 0},
                             {0, 200, 0},     {131, 238, 144}, {51, 113, 48},   {0, 122, 0},
                             {0, 41, 0},      {0, 43, 46},     {1, 0, 207},     {39, 120, 199},
                             {36, 203, 195},  {0, 120, 120},   {0, 0, 114},     {2, 0, 40},
                             {190, 3, 216},   {253, 196, 189}, {194, 125, 190}, {120, 1, 119},
                             {119, 124, 182}, {44, 0, 40},     {0, 0, 0},       {120, 120, 120},
                             {200, 200, 200}, {214, 214, 212}, {39, 40, 122},   {255, 255, 255}};
__asm__(".globl _dat_007091ac\n.set _dat_007091ac, _dat_007091a8+4\n");
__asm__(".globl _dat_007091b0\n.set _dat_007091b0, _dat_007091a8+8\n");
IconTable dat_0070ab20 = {
    {{{88, 83, 0, 145},
      {0x1.0000000000000p-3f, 0x1.0000000000000p-2f, 0x0.0p+0f, 0x1.0000000000000p-1f}},
     {{34, 173, 3, 311},
      {0x1.0000000000000p-2f, 0x1.8000000000000p-2f, 0x0.0p+0f, 0x1.0000000000000p-1f}},
     {{143, 173, 0, 150},
      {0x1.8000000000000p-2f, 0x1.0000000000000p-1f, 0x0.0p+0f, 0x1.0000000000000p-1f}},
     {{143, 271, 1, 64},
      {0x1.0000000000000p-1f, 0x1.4000000000000p-1f, 0x0.0p+0f, 0x1.0000000000000p-1f}},
     {{283, 83, 0, 104},
      {0x1.4000000000000p-1f, 0x1.8000000000000p-1f, 0x0.0p+0f, 0x1.0000000000000p-1f}},
     {{229, 173, 1, 161},
      {0x1.8000000000000p-1f, 0x1.c000000000000p-1f, 0x0.0p+0f, 0x1.0000000000000p-1f}},
     {{338, 173, 0, 61},
      {0x1.c000000000000p-1f, 0x1.0000000000000p+0f, 0x0.0p+0f, 0x1.0000000000000p-1f}},
     {{338, 271, 3, 312},
      {0x0.0p+0f, 0x1.0000000000000p-3f, 0x1.0000000000000p-1f, 0x1.0000000000000p+0f}},
     {{479, 83, 0, 135},
      {0x1.0000000000000p-3f, 0x1.0000000000000p-2f, 0x1.0000000000000p-1f, 0x1.0000000000000p+0f}},
     {{425, 173, 3, 313},
      {0x1.0000000000000p-2f, 0x1.8000000000000p-2f, 0x1.0000000000000p-1f, 0x1.0000000000000p+0f}},
     {{534, 173, 0, 79},
      {0x1.8000000000000p-2f, 0x1.0000000000000p-1f, 0x1.0000000000000p-1f, 0x1.0000000000000p+0f}},
     {{534, 271, 1, 94}, {0x0.0p+0f, 0x0.0p+0f, 0x0.0p+0f, 0x0.0p+0f}}},
    {0xffffffffu, 0xffffffffu, 0u, 0xffffffffu}};
__asm__(".globl _dat_0070ab24\n.set _dat_0070ab24, _dat_0070ab20+4\n");
__asm__(".globl _dat_0070ab2c\n.set _dat_0070ab2c, _dat_0070ab20+12\n");
uint32_t dat_0070a398[6] = {7, 4, 9, 1, 1, 1};
AtlExceptionType dat_0070b464 = {external_114, nullptr, ".?AVCAtlException@ATL@@"};
AtlClassIdTerminator dat_02203378 = {nullptr};
uint32_t dat_007090c0 = 0x81u;
uint32_t dat_007090c4 = 0xe4u;
float dat_007090e4 = 0x1.6c00000000000p+7f;
__asm__(".globl _dat_0070a2fc\n.set _dat_0070a2fc, _dat_0070a2f8+4\n");
__asm__(".globl _dat_0070a340\n.set _dat_0070a340, _dat_0070a2f8+72\n");
__asm__(".globl _dat_0070a344\n.set _dat_0070a344, _dat_0070a2f8+76\n");
__asm__(".globl _dat_0070a348\n.set _dat_0070a348, _dat_0070a2f8+80\n");
__asm__(".globl _dat_0070a34c\n.set _dat_0070a34c, _dat_0070a2f8+84\n");
__asm__(".globl _dat_0070a350\n.set _dat_0070a350, _dat_0070a2f8+88\n");
__asm__(".globl _dat_0070a354\n.set _dat_0070a354, _dat_0070a2f8+92\n");
__asm__(".globl _dat_0070a358\n.set _dat_0070a358, _dat_0070a2f8+96\n");
__asm__(".globl _dat_0070a35c\n.set _dat_0070a35c, _dat_0070a2f8+100\n");
__asm__(".globl _dat_0070a360\n.set _dat_0070a360, _dat_0070a2f8+104\n");
__asm__(".globl _dat_0070a364\n.set _dat_0070a364, _dat_0070a2f8+108\n");
float dat_0070a368 = 0x1.6000000000000p+3f;
float dat_0070a36c = 0x1.c800000000000p+5f;
float dat_0070a370 = 0x1.d000000000000p+5f;
float dat_0070a374 = 0x1.a000000000000p+6f;
float dat_0070a378 = 0x1.a400000000000p+6f;
float dat_0070a37c = 0x1.2e00000000000p+7f;
float dat_0070a380 = 0x1.3000000000000p+7f;
float dat_0070a384 = 0x1.8c00000000000p+7f;
float dat_0070a388 = 0x1.8e00000000000p+7f;
float dat_0070a38c = 0x1.e800000000000p+7f;
uint32_t dat_0070a6c8 = 0x8u;
uint32_t dat_02201c98 = 0x0u;
uint32_t dat_02201d60 = 0x0u;
uint32_t dat_02201d64 = 0x0u;
uint32_t dat_02201de0 = 0x0u;
uint32_t dat_02201de4 = 0x0u;
float dat_02201de8 = 0x0.0p+0f;
uint32_t dat_02201dec = 0x0u;
uint32_t dat_0220202c = 0x0u;
uint32_t dat_02202030 = 0x0u;
uint32_t dat_02202034 = 0x0u;
uint8_t dat_0220203e = 0x0u;
uint8_t dat_02202041 = 0x0u;
}
