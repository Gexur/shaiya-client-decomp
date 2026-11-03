#include <stdint.h>
#include <stddef.h>
// This preserves original zero-storage addresses, not an erased C++ buffer size.
struct OriginalSessionMessageZeroSpan {
    uint32_t known_state_223f104;
    uint32_t known_state_223f108;
    unsigned char unclassified_zero_addresses_223f10c[4];
    char character_address_view_223f110[0x804];
    uint32_t known_state_223f914;
};
static_assert(sizeof(OriginalSessionMessageZeroSpan) == 0x814);
static_assert(offsetof(OriginalSessionMessageZeroSpan, known_state_223f108) == 4);
static_assert(offsetof(OriginalSessionMessageZeroSpan, character_address_view_223f110) == 12);
static_assert(offsetof(OriginalSessionMessageZeroSpan, known_state_223f914) == 0x810);
extern "C" {
OriginalSessionMessageZeroSpan dat_0223f104 = {};
__asm__(".globl _dat_0223f108\n.set _dat_0223f108, _dat_0223f104+4\n");
__asm__(".globl _dat_0223f110\n.set _dat_0223f110, _dat_0223f104+12\n");
__asm__(".globl _dat_0223f914\n.set _dat_0223f914, _dat_0223f104+2064\n");
}
