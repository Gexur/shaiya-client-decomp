#pragma once
#include <stdint.h>
struct __attribute__((packed)) X87PowerWords {
    uint64_t significand;
    uint16_t sign_exponent;
};
static_assert(sizeof(X87PowerWords) == 10, "Original x87 extended literals");
struct PowerMathException {
    uint32_t kind;
    const char* name;
    double argument0, argument1, result;
};
static_assert(sizeof(PowerMathException) == 32, "Original5d6990 record");
extern "C" {
extern uint32_t dat_0224eddc;
extern const uint64_t dat_0070e4c0;
extern const char s_0070e4c8[4];
extern const X87PowerWords dat_0070eab0, dat_0070edd0;
// Actual private entries: ST0/ST1, EAX/ECX/EDX, flags and caller-local saved CW
// vary by procedure. No ordinary C++ arguments fabricate those machine inputs.
void __cdecl FUN_005d068d();
void __cdecl FUN_005d0852();
void __cdecl FUN_005d6990();
void __cdecl FUN_005d69a7();
void __cdecl FUN_005d69f0();
void __cdecl FUN_005d6a05();
void __cdecl FUN_005d6a35();
void __cdecl FUN_005d6a8e();
void __cdecl FUN_005d6ad9();
void __cdecl FUN_005da930();
// Actual unresolved C-call boundaries, never dummy implementations.
int32_t __cdecl FUN_005db6f5(double, double, double*);
uint32_t __cdecl FUN_005dea67(uint32_t, PowerMathException*, uint16_t*);
}
