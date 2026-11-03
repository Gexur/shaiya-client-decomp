#include <stdint.h>
extern "C" {
// Original454110 clears exactly these ten bytes before bounded numeric text.
char dat_00864d58[10] = {};
__asm__(".globl _dat_00864d5c\n.set _dat_00864d5c, _dat_00864d58+4\n");
__asm__(".globl _dat_00864d60\n.set _dat_00864d60, _dat_00864d58+8\n");
}
