#include "client_locale.h"
extern "C" {
using ConvertMultibyte = int32_t(__attribute__((stdcall)) *)(uint32_t, uint32_t, const char*,
                                                             int32_t, wchar_t*, int32_t);
extern ConvertMultibyte imported_multibyte __asm__("__imp__MultiByteToWideChar@24");
wchar_t dat_0220bf28[4096] = {};
}
static_assert(sizeof(wchar_t) == 2);
namespace {
uint32_t byte_length(const char* input) {
    uint32_t length = 0, value;
    do {
        __asm__ __volatile__("movzbl (%1),%0" : "=r"(value) : "r"(input + length) : "memory");
        ++length;
    } while (value != 0);
    return length - 1;
}
} // namespace
extern "C" uint32_t fun_0040a550() {
    switch (dat_00708598) {
    case 3:
        return 65001;
    case 4:
        return 932;
    case 5:
    case 8:
    case 9:
        return 950;
    case 12:
        return 1254;
    case 15:
        return 1250;
    default:
        return 0;
    }
}
extern "C" const wchar_t* fun_0054bd80(const char* input) {
    // The original clears exactly0x800 DWORDs before reading its input.
    for (uint32_t i = 0; i < 2048; ++i) {
        auto* const address = reinterpret_cast<uint8_t*>(dat_0220bf28) + i * 4;
        __asm__ __volatile__("movl $0,(%0)" ::"r"(address) : "memory");
    }
    const int32_t first_length = int32_t(byte_length(input));
    const uint32_t first_codepage = fun_0040a550();
    // Original0054bdb6 captures the IAT once; both calls use that capturedEDI.
    const ConvertMultibyte convert = imported_multibyte;
    const int32_t count = convert(first_codepage, 0, input, first_length, nullptr, 0);
    const int32_t second_length = int32_t(byte_length(input));
    const uint32_t second_codepage = fun_0040a550();
    convert(second_codepage, 0, input, second_length, dat_0220bf28, count);
    return dat_0220bf28;
}
extern "C" uint32_t FUN_0040a550() __attribute__((alias("fun_0040a550")));
extern "C" const wchar_t* FUN_0054bd80(const char*) __attribute__((alias("fun_0054bd80")));
