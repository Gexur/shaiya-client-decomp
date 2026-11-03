#pragma once
#include <stdint.h>
struct TextureFormatRecord {
    // Format, compatibility class, storage bits, five comparison fields, selectable flag.
    uint32_t words[9];
};
static_assert(sizeof(TextureFormatRecord) == 36);
extern "C" {
extern const TextureFormatRecord dat_006dbce0, dat_006dbd08[57];
extern const uint32_t dat_006dc510[25];
extern const TextureFormatRecord* dat_0070f36c;
/**
 * @brief Find the descriptor for a Direct3D format in the client table.
 * @param format Direct3D format value to find.
 * @return A borrowed matching record, or the shared unknown-format descriptor.
 * @note The table's current end pointer is read at entry. The format argument
 *       is reread during traversal to retain original alias-dependent behavior.
 */
const TextureFormatRecord* __attribute__((stdcall)) find_texture_format_record(uint32_t format);
/**
 * @brief Score the cost of converting a source format to a target format.
 * @param source Desired format descriptor, passed in ECX.
 * @param target Candidate descriptor, passed in EDX.
 * @return An asymmetric conversion penalty, or UINT32_MAX for incompatibility
 *         or loss of every nonzero source comparison field. Lower scores are preferred.
 * @note Uses the original two-register ABI with no stack arguments or callee pop.
 */
uint32_t __attribute__((fastcall)) score_texture_format_conversion(
    const TextureFormatRecord* source,
    const TextureFormatRecord* target) __asm__("_score_texture_format_conversion");
}
