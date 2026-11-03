#pragma once
#include <stdint.h>
extern "C" {
/**
 * @brief Determine a character's encoded byte length using the client locale.
 * @param character_word Original first stack word; bit tests inspect its low byte.
 * @param length Receives a byte length from one through four.
 * @return Zero for a single-byte character, otherwise one.
 * @note Locale 3 uses leading-bit UTF-8 classification without validating the
 *       sequence. Other paths consult Win32 DBCS APIs with the full input word.
 *       Output storage is reread after callbacks to retain aliasing behavior.
 */
uint32_t get_encoded_character_length(uint32_t character_word, uint32_t* length);
}
