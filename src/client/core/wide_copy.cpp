#include "wide_copy.h"
#include "core/x86_memory.h"

/**
 * @brief Copy a NUL-terminated sequence of 16-bit code units forward.
 * @param destination Writable storage with room for the source and terminator.
 * @param source Readable NUL-terminated code units.
 * @return The original destination pointer.
 * @note The terminator is copied. Overlap retains forward-copy behavior; no
 *       overlap check or length limit is imposed.
 */
extern "C" uint16_t* copy_utf16_string_forward(uint16_t* destination, const uint16_t* source) {
    uint16_t* const destination_start = destination;
    uint16_t character;
    do {
        // Copy one whole WORD before advancing: overlapping strings retain
        // the original forward-copy behavior, including the terminating NUL.
        character = client::x86::load<uint16_t>(source);
        client::x86::store(destination, character);
        ++source;
        ++destination;
    } while (character != 0);
    return destination_start;
}
