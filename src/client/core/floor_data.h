#pragma once
#include <stdint.h>
struct OriginalMathName {
    uint32_t operation;
    const char* name;
};
static_assert(sizeof(OriginalMathName) == 8, "Original70ec30 table stride");
struct alignas(16) OriginalFloorVector {
    uint64_t words[2];
};
static_assert(sizeof(OriginalFloorVector) == 16, "Original SSE operand extent");
extern "C" {
extern OriginalMathName dat_0070ec30[29];
extern uint32_t dat_00719090;
extern const OriginalFloorVector dat_006f7420, dat_006f7430, dat_006f7440, dat_006f7450,
    dat_006f7460;
}
