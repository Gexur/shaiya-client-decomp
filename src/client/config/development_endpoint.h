#pragma once
#include <stdint.h>

// Development feature added to the rebuilt client, not original recovered
// behavior. SHAIYA_LOGIN_HOST optionally selects a real IPv4 login endpoint.
// Only four decimal octets in0..255 without leading zeros are accepted.
// Returns1 after copying a valid address through NUL into destination; returns0
// and leaves every destination byte unchanged when absent, empty, invalid,
// null, or too small. Capacity includes the required terminator.
// This changes an actual connection target, never network state or packets.
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Copy the SHAIYA_LOGIN_HOST IPv4 development override when it is valid and fits.
 *
 * Accepts exactly four decimal octets from 0 to 255, without leading zeros; added development behavior.
 * @param destination Writable destination storage; string capacity includes its terminator.
 * @param capacity Writable destination byte capacity, including space for NUL.
 * @return One after copying through NUL; otherwise zero with the destination unchanged.
 */
int shaiya_apply_development_login_host(char* destination, uint32_t capacity);
#ifdef __cplusplus
}
#endif
