#pragma once
#include <stdint.h>
extern "C" {
// Original machine ABI: consume implicit ST0, preserve remaining x87 entries,
// truncate under a temporary CW and return physical EDX:EAX; no stack args.
// A C++ caller must explicitly supply ST0 rather than call with a fake operand.
uint64_t FUN_005d0bc4();
}
