#include "byte_utilities.h"

// Original SHA256: 796af141fd13451bab67ae0bae02d2177b1fe60af51775f296bec7b0eff752da
// Instruction evidence: evidence/cpp-utility-original-disassembly.txt.
// No raw executable code, original image addresses, or external implementation.
extern "C" uint32_t __attribute__((cdecl)) fun_0040d040(const uint8_t* input, uint32_t length) {
    // 0040D054 MOVSX is essential: bytes >=128 contribute a negative value.
    // Unsigned accumulation makes the original IMUL/ADD modulo 2^32 explicit.
    uint32_t result = 0x1505;
    while (length != 0) {
        const uint32_t byte = *input++;
        int32_t value =
            byte < 0x80 ? static_cast<int32_t>(byte) : static_cast<int32_t>(byte) - 0x100;
        if (value > 0x40 && value < 0x5b)
            value += 0x20;
        result = result * 0x21u + static_cast<uint32_t>(value);
        --length;
    }
    return result;
}

extern "C" void __attribute__((stdcall)) fun_0040a6f0(char* text) {
    // 0040A6F6 reserves 0x400 bytes, 0040A70C zeroes them. The source is
    // scanned before filtering. Only space, TAB and LF are removed; CR stays.
    char temporary[0x400]{};
    uint32_t length = 0;
    while (text[length] != '\0')
        ++length;
    uint32_t written = 0;
    for (uint32_t index = 0; index < length && text[index] != '\0'; ++index) {
        const char byte = text[index];
        if (byte != ' ' && byte != '\t' && byte != '\n')
            temporary[written++] = byte;
    }
    uint32_t index = 0;
    do {
        text[index] = temporary[index];
    } while (temporary[index++] != '\0');
}

extern "C" void __attribute__((cdecl)) fun_0041d3b0(char* destination, const char* source) {
    if (destination == nullptr || source == nullptr)
        return;
    const char* end = source;
    while (*end != '\0')
        ++end;
    if (end == source)
        return;
    char byte;
    do {
        byte = *source++;
        *destination++ = byte;
    } while (byte != '\0');
}
