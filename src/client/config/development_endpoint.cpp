#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "development_endpoint.h"

// Explicit development configuration, not a transcription of original code.
/**
 * @brief Copy the SHAIYA_LOGIN_HOST IPv4 development override when it is valid and fits.
 *
 * Accepts exactly four decimal octets from 0 to 255, without leading zeros; added development behavior.
 * @param destination Writable destination storage; string capacity includes its terminator.
 * @param capacity Writable destination byte capacity, including space for NUL.
 * @return One after copying through NUL; otherwise zero with the destination unchanged.
 */
extern "C" int shaiya_apply_development_login_host(char* destination, uint32_t capacity) {
    if (destination == nullptr || capacity == 0)
        return 0;
    char candidate[16] = {};
    const DWORD length = GetEnvironmentVariableA("SHAIYA_LOGIN_HOST", candidate, sizeof(candidate));
    if (length == 0 || length >= sizeof(candidate) || candidate[length] != 0 || capacity <= length)
        return 0;

    uint32_t cursor = 0;
    for (uint32_t octet = 0; octet != 4; ++octet) {
        const uint32_t first = cursor;
        uint32_t value = 0;
        while (cursor < length && candidate[cursor] >= '0' && candidate[cursor] <= '9') {
            if (cursor - first == 3)
                return 0;
            value = value * 10 + uint32_t(candidate[cursor] - '0');
            ++cursor;
        }
        if (cursor == first || value > 255 || (cursor - first > 1 && candidate[first] == '0'))
            return 0;
        if (octet != 3) {
            if (cursor == length || candidate[cursor] != '.')
                return 0;
            ++cursor;
        } else if (cursor != length) {
            return 0;
        }
    }
    for (uint32_t index = 0; index <= length; ++index)
        destination[index] = candidate[index];
    return 1;
}
