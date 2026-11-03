#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "development_version.h"

namespace {
constexpr uint32_t original_client_version = 0x11122200u;
}

extern "C" {
uint32_t shaiya_client_version = original_client_version;
}

extern "C" void shaiya_apply_development_client_version() {
    shaiya_client_version = original_client_version;
    char candidate[32] = {};
    const DWORD length = GetEnvironmentVariableA("SHAIYA_CLIENT_VERSION", candidate,
                                                 sizeof(candidate));
    if (length == 0 || length >= sizeof(candidate) || candidate[length] != 0)
        return;

    uint32_t base = 10, cursor = 0;
    if (length >= 2 && candidate[0] == '0' &&
        (candidate[1] == 'x' || candidate[1] == 'X')) {
        base = 16;
        cursor = 2;
    }
    if (cursor == length)
        return;

    uint32_t value = 0;
    for (; cursor < length; ++cursor) {
        const char character = candidate[cursor];
        uint32_t digit;
        if (character >= '0' && character <= '9')
            digit = uint32_t(character - '0');
        else if (base == 16 && character >= 'a' && character <= 'f')
            digit = uint32_t(character - 'a') + 10;
        else if (base == 16 && character >= 'A' && character <= 'F')
            digit = uint32_t(character - 'A') + 10;
        else
            return;
        if (value > (0xffffffffu - digit) / base)
            return;
        value = value * base + digit;
    }
    shaiya_client_version = value;
}
