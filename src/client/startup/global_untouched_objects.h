#pragma once
#include <stdint.h>
extern "C" {
// The120-byte span covers the original24-byte prefix and six16-byte members.
extern uint8_t dat_0224e420[120];
// Original absolute x87 stores prove the three consecutive DWORDs674/678/67c.
// No neighboring float/vector state starting680 is included or initialized.
extern uint32_t dat_0224e674[3];
void fun_006b7680();
void fun_006ba830();
void fun_006b7720();
void fun_006ba880();
}
