#include "character_span.h"
#include "core/x86_memory.h"
#include "startup/client_locale.h"
namespace {
using IsLeadByteEx = uint32_t(__attribute__((stdcall)) *)(uint32_t, uint32_t);
using IsLeadByte = uint32_t(__attribute__((stdcall)) *)(uint32_t);
extern "C" IsLeadByteEx imported_span_ex __asm__("__imp__IsDBCSLeadByteEx@8");
extern "C" IsLeadByte imported_span __asm__("__imp__IsDBCSLeadByte@4");

/**
 * @brief Store a byte length through the current original output argument.
 * @param arguments Original character word followed by the output address.
 * @param length Encoded byte length to store.
 * @return Zero for length one, otherwise one.
 */
uint32_t write_character_length(const uint32_t* arguments, uint32_t length) {
    // Reload the actual output argument after any Win32 call: callbacks and
    // argument/output aliases can retarget it before the original final store.
    const uint32_t output_address =
        client::x86::load_word(reinterpret_cast<uint32_t>(arguments) + 4);
    client::x86::store_word(output_address, length);
    return length == 1 ? 0 : 1;
}
} // namespace
/**
 * @brief Classify a character while retaining access to mutable stack arguments.
 * @param arguments Original character word and byte-length output address.
 * @return Zero for a single-byte character, otherwise one.
 * @see get_encoded_character_length
 */
extern "C" uint32_t get_encoded_character_length_from_stack(const uint32_t* arguments) {
    using client::x86::load;
    uint32_t locale = load<uint32_t>(&dat_00708598);
    const uint32_t character = load<uint32_t>(arguments);
    const uint8_t first_byte = static_cast<uint8_t>(character);
    if (locale == 3) {
        if ((first_byte & 0x80) == 0)
            return write_character_length(arguments, 1);
        if ((first_byte & 0xf0) == 0xf0)
            return write_character_length(arguments, 4);
        if ((first_byte & 0xe0) == 0xe0)
            return write_character_length(arguments, 3);
        if ((first_byte & 0xc0) == 0xc0)
            return write_character_length(arguments, 2);
    } else {
        const IsLeadByteEx is_lead_byte_ex = load<IsLeadByteEx>(&imported_span_ex);
        if (locale == 4) {
            if (is_lead_byte_ex(932, character) != 0)
                return write_character_length(arguments, 2);
            locale = load<uint32_t>(&dat_00708598);
        }
        if (locale == 5 || locale == 9)
            return write_character_length(arguments, is_lead_byte_ex(950, character) != 0 ? 2 : 1);
    }
    const IsLeadByte is_lead_byte = load<IsLeadByte>(&imported_span);
    return write_character_length(arguments, is_lead_byte(character) != 0 ? 2 : 1);
}
/**
 * @brief Determine a character's encoded byte length using the client locale.
 * @param character_word Original first stack word; bit tests inspect its low byte.
 * @param length Receives a byte length from one through four.
 * @return Zero for a single-byte character, otherwise one.
 * @note Locale 3 uses leading-bit UTF-8 classification without validating the
 *       sequence. Other paths consult Win32 DBCS APIs with the full input word.
 *       Output storage is reread after callbacks to retain aliasing behavior.
 */
extern "C" __attribute__((naked)) uint32_t get_encoded_character_length(uint32_t character_word,
                                                                        uint32_t* length) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _get_encoded_character_length_from_stack\n\taddl $4,%esp\n\tretl");
}
