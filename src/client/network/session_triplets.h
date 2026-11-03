#pragma once
#include <stdint.h>
struct OriginalSessionTriplet {
    uint8_t first, second, third;
};
static_assert(sizeof(OriginalSessionTriplet) == 3, "Original index*3 stores");
extern "C" {
// Only the240 entries reached by original BYTEindex<240 are represented.
extern OriginalSessionTriplet dat_021fe736[240];
extern OriginalSessionTriplet dat_021fea06[240];
uint32_t __attribute__((thiscall)) fun_0056d4c0(void*, uint32_t, uint32_t, uint32_t, uint32_t);
uint32_t __attribute__((thiscall)) fun_0056d5b0(void*, uint32_t, uint32_t, uint32_t, uint32_t);
}
