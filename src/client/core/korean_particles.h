#pragma once
#include <stdint.h>
extern "C" {
extern const uint8_t dat_006bca64[3], dat_006bca68[3], dat_006bca6c[3], dat_006bca70[3],
    dat_006bca74[3], dat_006bca78[3], dat_006bca7c[5], dat_006bca84[3];
/**
 * @brief Test the converted first character for a Hangul final consonant.
 * @param particle_context Unused original thiscall receiver, retained for ABI.
 * @param input NUL-terminated text converted using the current client codepage.
 * @return One when the signed Hangul remainder is nonzero; zero otherwise or
 *         when allocation fails. The original conversion failures are unchecked.
 */
uint8_t __attribute__((thiscall)) has_hangul_final_consonant(void* particle_context,
                                                             const char* input);
/**
 * @brief Classify an ASCII digit or letter for Korean particle selection.
 * @param particle_context Unused original thiscall receiver, retained for ABI.
 * @param character_word Low byte contains the character to classify.
 * @return The low byte is one for 0, 1, 3, 6, 7, 8, L, M, N, or R (case
 *         insensitive), otherwise zero. Upper EAX bits retain original path-dependent values.
 */
uint32_t __attribute__((thiscall)) classify_ascii_final_consonant(void* particle_context,
                                                                  uint32_t character_word);
/**
 * @brief Select the Korean topic particle eun/neun for a text ending.
 * @param particle_context Original thiscall receiver forwarded to classification.
 * @param text Nonempty NUL-terminated text in the client encoding.
 * @return Borrowed NUL-terminated CP949 bytes for eun or neun.
 * @note DBCS detection examines the penultimate byte; ASCII uses the literal
 *       digit/letter classification. Empty input retains the original preceding-byte read.
 */
const uint8_t* __attribute__((thiscall)) select_korean_topic_particle(void* particle_context,
                                                                      const char* text);
/**
 * @brief Select the Korean subject particle i/ga for a text ending.
 * @param particle_context Original thiscall receiver forwarded to classification.
 * @param text Nonempty NUL-terminated text in the client encoding.
 * @return Borrowed NUL-terminated CP949 bytes for i or ga.
 */
const uint8_t* __attribute__((thiscall)) select_korean_subject_particle(void* particle_context,
                                                                        const char* text);
/**
 * @brief Select the Korean object particle eul/reul using the original byte tests.
 * @param particle_context Original thiscall receiver forwarded to classification.
 * @param text Nonempty NUL-terminated text in the client encoding.
 * @return Borrowed NUL-terminated CP949 bytes for eul or reul.
 * @note Unlike the other selectors, DBCS detection checks the first byte and a
 *       false Hangul result still falls through to ASCII classification.
 */
const uint8_t* __attribute__((thiscall)) select_korean_object_particle(void* particle_context,
                                                                       const char* text);
/**
 * @brief Select the Korean instrumental particle euro/ro for a text ending.
 * @param particle_context Original thiscall receiver forwarded to classification.
 * @param text Nonempty NUL-terminated text in the client encoding.
 * @return Borrowed NUL-terminated CP949 bytes for euro or ro, or null if the
 *         second conversion allocation fails. A Hangul rieul ending selects ro.
 */
const uint8_t* __attribute__((thiscall)) select_korean_instrumental_particle(void* particle_context,
                                                                             const char* text);
}
