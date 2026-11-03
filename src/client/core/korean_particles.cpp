#include "korean_particles.h"
#include "core/x86_memory.h"
#include "startup/client_locale.h"
#include "runtime/allocations.h"
#include <windows.h>
extern "C" {
using KoreanConvert = int32_t(__attribute__((stdcall)) *)(uint32_t, uint32_t, const char*, int32_t,
                                                          wchar_t*, int32_t);
extern KoreanConvert korean_multibyte_import __asm__("__imp__MultiByteToWideChar@24");
// Original CP949 literals, typed individually through their actual NULs.
extern const uint8_t dat_006bca64[3] = {0xb4, 0xc2, 0};
extern const uint8_t dat_006bca68[3] = {0xc0, 0xba, 0};
extern const uint8_t dat_006bca6c[3] = {0xb0, 0xa1, 0};
extern const uint8_t dat_006bca70[3] = {0xc0, 0xcc, 0};
extern const uint8_t dat_006bca74[3] = {0xb8, 0xa6, 0};
extern const uint8_t dat_006bca78[3] = {0xc0, 0xbb, 0};
extern const uint8_t dat_006bca7c[5] = {0xc0, 0xb8, 0xb7, 0xce, 0};
extern const uint8_t dat_006bca84[3] = {0xb7, 0xce, 0};
}
namespace {
/** @brief Read one byte with the original aliasable volatile access. */
uint8_t read_byte(const char* address) {
    return client::x86::load<uint8_t>(address);
}
/** @brief Count bytes before the NUL terminator without validating the encoding. */
uint32_t byte_length(const char* text) {
    uint32_t length = 0;
    while (read_byte(text + length) != 0)
        ++length;
    return length;
}
/**
 * @brief Compute the first UTF-16 code unit's signed Hangul-final remainder.
 * @param character_address Storage containing at least one readable 16-bit unit.
 * @return (code unit - 0xac00) modulo 28, retaining negative remainders outside Hangul.
 */
int32_t hangul_remainder(const void* character_address) {
    constexpr int32_t first_hangul_syllable = 0xac00;
    constexpr int32_t final_consonant_count = 28;
    const int32_t character = client::x86::load<uint16_t>(character_address);
    // C++17 signed remainder matches IDIV, including negative values outside
    // the Hangul syllable range. This bounded numerator cannot overflow.
    return (character - first_hangul_syllable) % final_consonant_count;
}
/** @brief Test the client's literal ASCII digit/letter set for a final consonant. */
bool has_ascii_final_consonant(uint8_t character) {
    if (character >= 'A' && character <= 'Z')
        character += 'a' - 'A';
    switch (character) {
    case '0':
    case '1':
    case '3':
    case '6':
    case '7':
    case '8':
    case 'l':
    case 'm':
    case 'n':
    case 'r':
        return true;
    default:
        return false;
    }
}
} // namespace
// Complete original0x0041cb60..0x0041cbd9. Both conversions use a freshly
// queried original client codepage; the API slot is captured after its first
// codepage call. The second API result is ignored before the actual WORD read.
/**
 * @brief Test the converted first character for a Hangul final consonant.
 * @param particle_context Unused original thiscall receiver, retained for ABI.
 * @param input NUL-terminated text converted using the current client codepage.
 * @return One when the signed Hangul remainder is nonzero; zero otherwise or
 *         when allocation fails. The original conversion failures are unchecked.
 */
extern "C" uint8_t __attribute__((noinline, thiscall))
has_hangul_final_consonant(void* particle_context, const char* input) {
    const uint32_t first_codepage = fun_0040a550();
    const KoreanConvert convert = korean_multibyte_import;
    const int32_t wide_character_count = convert(first_codepage, 0, input, -1, nullptr, 0);
    void* wide_text = fun_005cde20(uint32_t(wide_character_count) * 2u);
    if (wide_text == nullptr)
        return 0;
    const uint32_t second_codepage = fun_0040a550();
    convert(second_codepage, 0, input, -1, static_cast<wchar_t*>(wide_text), wide_character_count);
    const bool has_final_consonant = hangul_remainder(wide_text) != 0;
    fun_005cdc59(wide_text);
    return uint8_t(has_final_consonant);
}
// Original0x0041cbe0..0x0041cc3a, with two original dispatch tables decoded
// to their actual digit/letter sets. High EAX survives nonletter paths.
/**
 * @brief Classify the original ASCII argument while preserving upper EAX bits.
 * @param argument Address of the original character argument; only its low byte is read.
 * @param incoming_eax EAX captured before the adapter modifies it.
 * @return The final-consonant flag in AL with the original path's upper EAX bits.
 */
extern "C" __attribute__((noinline)) uint32_t
classify_ascii_final_consonant_from_stack(const char* argument, uint32_t incoming_eax) {
    uint8_t character = read_byte(argument);
    uint32_t result = (incoming_eax & 0xffffff00u) | character;
    if (character >= '0' && character <= '9')
        return (result & 0xffffff00u) | uint32_t(has_ascii_final_consonant(character));
    if (character >= 'A' && character <= 'Z') {
        character = uint8_t(character + 'a' - 'A');
        result = (result & 0xffffff00u) | character;
    }
    // The original letter dispatch indexes through EAX, clearing its upper bits;
    // digit and nonletter paths leave those incoming bits unchanged.
    if (character >= 'a' && character <= 'z')
        result = uint32_t(character - 'a');
    return (result & 0xffffff00u) | uint32_t(has_ascii_final_consonant(character));
}
/**
 * @brief Classify an ASCII digit or letter for Korean particle selection.
 * @param particle_context Unused original thiscall receiver, retained for ABI.
 * @param character_word Low byte contains the character to classify.
 * @return The low byte is one for 0, 1, 3, 6, 7, 8, L, M, N, or R (case
 *         insensitive), otherwise zero. Upper EAX bits retain original path-dependent values.
 */
extern "C" __attribute__((naked, thiscall)) uint32_t
classify_ascii_final_consonant(void* particle_context, uint32_t character_word) {
    __asm__ volatile(
        "pushl %eax\n\tleal 8(%esp),%eax\n\tpushl %eax\n\tcall _classify_ascii_final_consonant_from_stack\n\tleal 8(%esp),%esp\n\tretl $4");
}
// Complete original0x0041cc80..0x0041cd1c; its digit dispatch table is
// embedded after the code and has the same literal digit classification.
/**
 * @brief Select the Korean topic particle eun/neun for a text ending.
 * @param particle_context Original thiscall receiver forwarded to classification.
 * @param text Nonempty NUL-terminated text in the client encoding.
 * @return Borrowed NUL-terminated CP949 bytes for eun or neun.
 * @note DBCS detection examines the penultimate byte; ASCII uses the literal
 *       digit/letter classification. Empty input retains the original preceding-byte read.
 */
extern "C" const uint8_t* __attribute__((thiscall))
select_korean_topic_particle(void* particle_context, const char* text) {
    const uint32_t text_length = byte_length(text);
    if (int32_t(text_length) > 1 && IsDBCSLeadByte(read_byte(text + text_length - 2)) != 0)
        return has_hangul_final_consonant(particle_context, text + text_length - 2) != 0
                   ? dat_006bca68
                   : dat_006bca64;
    return has_ascii_final_consonant(read_byte(text + text_length - 1)) ? dat_006bca68
                                                                        : dat_006bca64;
}
// Complete original0x0041cd30..0x0041cd92.
/**
 * @brief Select the Korean subject particle i/ga for a text ending.
 * @param particle_context Original thiscall receiver forwarded to classification.
 * @param text Nonempty NUL-terminated text in the client encoding.
 * @return Borrowed NUL-terminated CP949 bytes for i or ga.
 */
extern "C" const uint8_t* __attribute__((thiscall))
select_korean_subject_particle(void* particle_context, const char* text) {
    const uint32_t text_length = byte_length(text);
    uint8_t has_final_consonant;
    if (int32_t(text_length) > 1 && IsDBCSLeadByte(read_byte(text + text_length - 2)) != 0)
        has_final_consonant = has_hangul_final_consonant(particle_context, text + text_length - 2);
    else
        has_final_consonant = uint8_t(
            classify_ascii_final_consonant(particle_context, read_byte(text + text_length - 1)));
    return has_final_consonant != 0 ? dat_006bca70 : dat_006bca6c;
}
// Complete original0x0041cda0..0x0041ce0b. It tests the FIRST byte for DBCS
// and falls through to an ASCII reread even after a false Hangul result.
/**
 * @brief Select the Korean object particle eul/reul using the original byte tests.
 * @param particle_context Original thiscall receiver forwarded to classification.
 * @param text Nonempty NUL-terminated text in the client encoding.
 * @return Borrowed NUL-terminated CP949 bytes for eul or reul.
 * @note Unlike the other selectors, DBCS detection checks the first byte and a
 *       false Hangul result still falls through to ASCII classification.
 */
extern "C" const uint8_t* __attribute__((thiscall))
select_korean_object_particle(void* particle_context, const char* text) {
    const uint32_t last_byte = byte_length(text) - 1u;
    if (last_byte != 0 && IsDBCSLeadByte(read_byte(text)) != 0 &&
        has_hangul_final_consonant(particle_context, text + last_byte - 1) != 0)
        return dat_006bca78;
    return uint8_t(classify_ascii_final_consonant(particle_context, read_byte(text + last_byte))) !=
                   0
               ? dat_006bca78
               : dat_006bca74;
}
// Complete original0x0041ce10..0x0041cf31, preserving the separate second
// conversion/allocation and its null result after successful classification.
/**
 * @brief Select the Korean instrumental particle euro/ro for a text ending.
 * @param particle_context Original thiscall receiver forwarded to classification.
 * @param text Nonempty NUL-terminated text in the client encoding.
 * @return Borrowed NUL-terminated CP949 bytes for euro or ro, or null if the
 *         second conversion allocation fails. A Hangul rieul ending selects ro.
 */
extern "C" const uint8_t* __attribute__((thiscall))
select_korean_instrumental_particle(void* particle_context, const char* text) {
    const uint32_t text_length = byte_length(text);
    if (int32_t(text_length) > 1 && IsDBCSLeadByte(read_byte(text + text_length - 2)) != 0) {
        const char* ending = text + text_length - 2;
        if (has_hangul_final_consonant(particle_context, ending) == 0)
            return dat_006bca84;
        const uint32_t first_codepage = fun_0040a550();
        const KoreanConvert convert = korean_multibyte_import;
        const int32_t wide_character_count = convert(first_codepage, 0, ending, -1, nullptr, 0);
        void* wide_text = fun_005cde20(uint32_t(wide_character_count) * 2u);
        if (wide_text == nullptr)
            return nullptr;
        const uint32_t second_codepage = fun_0040a550();
        convert(second_codepage, 0, ending, -1, static_cast<wchar_t*>(wide_text),
                wide_character_count);
        const bool ends_with_rieul = hangul_remainder(wide_text) == 8;
        fun_005cdc59(wide_text);
        return ends_with_rieul ? dat_006bca84 : dat_006bca7c;
    }
    uint8_t character = read_byte(text + text_length - 1);
    if (character >= '0' && character <= '9')
        return character == '0' || character == '3' || character == '6' ? dat_006bca7c
                                                                        : dat_006bca84;
    if (character >= 'A' && character <= 'Z')
        character = uint8_t(character + 'a' - 'A');
    return character == 'm' || character == 'n' ? dat_006bca7c : dat_006bca84;
}
