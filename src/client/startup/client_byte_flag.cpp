#include "client_byte_flag.h"
extern "C" uint8_t dat_02203674 = 0;
// Complete original 0x0052ccf0..0x0052ccfa. This tiny field setter has a
// register contract as well as a byte store: it replaces only AL, preserves
// every other register and flag, and reads only one byte of its stack word.
extern "C" __attribute__((naked, cdecl)) void FUN_0052ccf0(uint32_t) {
    __asm__ volatile("movb 4(%esp),%al\n\tmovb %al,_dat_02203674\n\tretl");
}
