#include "entry.h"

// Original PE loader zero-filled storage. Kept separate from the actual entry
// body so runtime components share canonical storage without a game dependency.
extern "C" {
uint32_t dat_0224edec = 0, dat_0224edf0 = 0, dat_0224edf8 = 0;
char* dat_02253620 = nullptr;
void* dat_0224ee38 = nullptr;
}
