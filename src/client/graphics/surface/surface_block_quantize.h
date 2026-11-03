#pragma once
#include <stdint.h>
extern "C" {
// Actual ECX RGB input; no stackarguments/RET0. Physical EAX packedword,
// ECX greeninteger and EDX blueinteger. Explicit literal x87/CW behavior.
uint32_t __attribute__((thiscall)) FUN_0064f776(const void* color);
extern const uint32_t dat_006c651c;
extern const uint32_t dat_006df408;
}
