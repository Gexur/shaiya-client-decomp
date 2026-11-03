#include "crt_exit.h"

// Actual loader-zero storage, shared with stdio shutdown and runtime startup.
extern "C" {
uint8_t dat_0224ee20 = 0;
uint32_t dat_0224ee24 = 0, dat_0224ee28 = 0;
}
