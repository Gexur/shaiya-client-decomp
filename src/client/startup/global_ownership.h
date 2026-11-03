#pragma once
#include <stdint.h>
#include <stddef.h>
struct OriginalRawVector {
    void* begin;
    void* end;
    void* capacity_end;
};
struct OriginalComObject {
    void** vtable;
};
struct OriginalComPair {
    OriginalComObject* first;
    OriginalComObject* second;
};
static_assert(sizeof(OriginalRawVector) == 12);
static_assert(sizeof(OriginalComPair) == 8);
// These receivers have original float stores at+8/+c in texture loader5497a0.
struct OriginalTextureComOwner16 {
    OriginalComObject* first;
    OriginalComObject* second;
    float width;
    float height;
};
static_assert(sizeof(OriginalTextureComOwner16) == 16);
static_assert(offsetof(OriginalTextureComOwner16, width) == 8 &&
              offsetof(OriginalTextureComOwner16, height) == 12);
extern "C" {
extern OriginalRawVector dat_00864d4c;
void fun_006b5d60();
void fun_006b8390();
extern OriginalRawVector dat_00864d3c;
void fun_006b5d70();
void fun_006b83d0();
extern OriginalRawVector dat_00864d1c;
void fun_006b5d80();
void fun_006b8410();
extern OriginalRawVector dat_00864d2c;
void fun_006b5d90();
void fun_006b8450();
extern OriginalRawVector dat_0220aa34;
void fun_006b6e80();
void fun_006b9c80();
extern OriginalRawVector dat_0224e710;
void fun_006b77f0();
void fun_006bab40();
extern OriginalTextureComOwner16 dat_0071cfc8;
void fun_006b5a60();
void fun_006b7fc0();
extern OriginalComPair dat_00864d68;
void fun_006b5e00();
void fun_006b84f0();
extern OriginalTextureComOwner16 dat_00864e8c;
void fun_006b6220();
void fun_006b8a60();
extern OriginalTextureComOwner16 dat_00864e9c;
void fun_006b6260();
void fun_006b8ac0();
extern OriginalTextureComOwner16 dat_00864eac;
void fun_006b62a0();
void fun_006b8b20();
extern OriginalTextureComOwner16 dat_00864ebc;
void fun_006b62b0();
void fun_006b8b60();
extern OriginalTextureComOwner16 dat_02202044;
void fun_006b67d0();
void fun_006b9280();
extern OriginalTextureComOwner16 dat_022032fc;
void fun_006b6950();
void fun_006b94d0();
extern OriginalTextureComOwner16 dat_0220330c;
void fun_006b6960();
void fun_006b9510();
extern OriginalTextureComOwner16 dat_0220331c;
void fun_006b6970();
void fun_006b9550();
extern OriginalTextureComOwner16 dat_0220332c;
void fun_006b6980();
void fun_006b9590();
extern OriginalTextureComOwner16 dat_0220333c;
void fun_006b6990();
void fun_006b95d0();
extern OriginalTextureComOwner16 dat_02203368;
void fun_006b6a60();
void fun_006b9730();
}
