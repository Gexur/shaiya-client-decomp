#include "numeric_initializer.h"
extern "C" {
float dat_0070a1c4 = 31.0f, dat_0070a1c8 = 78.0f;
float dat_02201c1c = 0.0f, dat_02201c20 = 0.0f;
const float dat_006bc9cc = 4.0f;
}
// Actual006B6700..006B6725: retain both original x87 additions and DWORD
// stores, including directed rounding, exception flags and live-stack state.
extern "C" void fun_006b6700() {
    __asm__ volatile("flds %2\n\t"
                     "fadds %3\n\t"
                     "fstps %0\n\t"
                     "flds %4\n\t"
                     "fadds %3\n\t"
                     "fstps %1"
                     : "=m"(dat_02201c1c), "=m"(dat_02201c20)
                     : "m"(dat_0070a1c4), "m"(dat_006bc9cc), "m"(dat_0070a1c8)
                     : "st", "memory");
}
