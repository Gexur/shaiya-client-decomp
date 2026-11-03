#pragma once
#include <stdint.h>
/**
 * @brief Copy a NUL-terminated sequence of 16-bit code units forward.
 * @param destination Writable storage with room for the source and terminator.
 * @param source Readable NUL-terminated code units.
 * @return The original destination pointer.
 * @note The terminator is copied. Overlap retains forward-copy behavior; no
 *       overlap check or length limit is imposed.
 */
extern "C" uint16_t* copy_utf16_string_forward(uint16_t* destination, const uint16_t* source);
