#include "bigint.h"

// Original 00586AE0 reduction loop. The low-word multiply chooses each addmul
// factor; its carry is accumulated one window-width above the current word.
// Preserve the original high-word-only conditional subtraction, rather than
// adding a canonical comparison that is absent from the instructions.
extern "C" void fun_00586ae0(uint32_t* output, const uint32_t* modulus, int32_t count,
                             uint32_t inverse, uint32_t* workspace) {
    workspace[uint32_t(count) * 2] = 0;
    uint32_t* current = workspace;
    if (count > 0) {
        uint32_t* upper = workspace + count + 1;
        for (int32_t i = 0; i < count; ++i) {
            uint32_t carry = fun_00589590(current, modulus, uint32_t(count), *current * inverse);
            uint32_t before = upper[-1];
            upper[-1] = before + carry;
            if (before + carry < carry) {
                uint32_t* ripple = upper;
                do {
                    ++*ripple;
                } while (*ripple++ == 0);
            }
            ++current;
            ++upper;
        }
    }
    if (current[count] != 0) {
        fun_00587610(output, current, modulus, uint32_t(count));
        return;
    }
    uint32_t remaining = uint32_t(count);
    if (remaining != 0)
        do {
            *output++ = *current++;
        } while (--remaining != 0);
}
