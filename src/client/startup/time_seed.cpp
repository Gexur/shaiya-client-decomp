#include "time_seed.h"
#include "../network/crypto_state.h"

struct FileTimeWords {
    uint32_t low;
    uint32_t high;
};
extern "C" __declspec(dllimport) void __attribute__((stdcall))
GetSystemTimeAsFileTime(FileTimeWords* system_time);

/**
 * Convert Windows system FILETIME to the original unsigned 32-bit Unix-time bits.
 * @param destination Optional writable result pointer; null requests only the return value.
 * @return Low 32 bits of whole seconds since the Unix epoch, using the original
 * unsigned FILETIME offset adjustment and division by 10,000,000.
 * Preserves the two-word addition's carry and the original time32 wraparound.
 * Original entry: 0x5ceb00.
 */
extern "C" uint32_t __cdecl read_unix_time32(uint32_t* destination) {
    FileTimeWords timestamp;
    GetSystemTimeAsFileTime(&timestamp);
    const uint32_t low = timestamp.low + 0x2ac18000u;
    const uint32_t high = timestamp.high + 0xfe624e21u + (low < timestamp.low);
    const uint64_t adjusted = (uint64_t(high) << 32) | low;
    const uint32_t result = uint32_t(adjusted / 10000000u);
    if (destination != nullptr)
        *destination = result;
    return result;
}

/**
 * Initialize the canonical client PRNG seed from the current 32-bit Unix-time bits.
 * Writes client_crypto_state.prng_seed; startup ordering remains controlled by the
 * recovered initializer table entry at 0x6b56a0 in the startup manifest.
 */
extern "C" void __cdecl initialize_client_prng_seed() {
    client_crypto_state.prng_seed = read_unix_time32(nullptr);
}
