#include "floating_text.h"
#include "character_case.h"
extern "C" {
char dat_0070e4e4[4] = {'.', 0, 0, 0};
}
extern "C" void fun_005d2b1c(char* buffer) {
    if (fun_005d0969(static_cast<int8_t>(*buffer)) != 'e') {
        do {
            ++buffer;
        } while (fun_005d9235(static_cast<int8_t>(*buffer)));
    }
    char carry = *buffer;
    *buffer = dat_0070e4e4[0];
    do {
        ++buffer;
        const char next = *static_cast<volatile char*>(buffer);
        *buffer = carry;
        carry = next;
    } while (*buffer);
}
extern "C" void fun_005d2b58(char* buffer) {
    const char point = dat_0070e4e4[0];
    while (*buffer && *buffer != point)
        ++buffer;
    if (!*buffer++)
        return;
    while (*buffer && *buffer != 'e' && *buffer != 'E')
        ++buffer;
    char* suffix = buffer;
    do {
        --buffer;
    } while (*buffer == '0');
    if (*buffer == point)
        --buffer;
    char copied;
    do {
        copied = *suffix++;
        *++buffer = copied;
    } while (copied);
}
extern "C" uint32_t fun_005d2ba3(const void* binary64) {
    uint16_t status;
    __asm__ volatile("fldl (%1)\n\tfcompl _dat_006bb5f0\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "r"(binary64)
                     : "st", "cc", "memory");
    return (status & 0x100) ? 0 : 1;
}
