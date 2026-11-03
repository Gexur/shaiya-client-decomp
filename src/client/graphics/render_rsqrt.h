#pragma once
#include <stdint.h>
struct RsqrtCoefficients {
    float multiplier, addend;
};
static_assert(sizeof(RsqrtCoefficients) == 8);
extern "C" {
extern RsqrtCoefficients dat_00715908[512];
float* __attribute__((stdcall)) FUN_0064f3e9(float*, const float*);
}
