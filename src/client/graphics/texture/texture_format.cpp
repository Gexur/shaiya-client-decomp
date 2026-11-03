#include "graphics/texture/texture_format.h"
namespace {
using u32 = uint32_t;
/** @brief Read a 32-bit word while retaining the original access and compiler barrier. */
inline u32 read_word(const void* address) {
    u32 value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(address) : "memory");
    return value;
}
/** @brief Reinterpret an original 32-bit client address without dereferencing it. */
inline const void* pointer_from_address(u32 value) {
    return reinterpret_cast<const void*>(value);
}
} // namespace
/**
 * @brief Look up a format through its original mutable stack argument.
 * @param argument Original format argument storage, reread once per table entry.
 * @return Borrowed format descriptor or the shared unknown-format descriptor.
 */
extern "C" const TextureFormatRecord*
find_texture_format_record_from_stack(const uint32_t* argument) {
    const u32 limit = read_word(&dat_0070f36c);
    u32 current = reinterpret_cast<u32>(dat_006dbd08);
    while (current < limit) {
        const u32 format = read_word(argument);
        if (format == read_word(pointer_from_address(current)))
            return reinterpret_cast<const TextureFormatRecord*>(current);
        current += 36;
    }
    return &dat_006dbce0;
}
/**
 * @brief Find the descriptor for a Direct3D format in the client table.
 * @param format Direct3D format value to find.
 * @return A borrowed matching record, or the shared unknown-format descriptor.
 * @note The table's current end pointer is read at entry. The format argument
 *       is reread during traversal to retain original alias-dependent behavior.
 */
extern "C" __attribute__((naked)) const TextureFormatRecord* __attribute__((stdcall))
find_texture_format_record(uint32_t format) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _find_texture_format_record_from_stack\n\taddl $4,%esp\n\tretl $4");
}
/**
 * @brief Score the cost of converting a source format to a target format.
 * @param source Desired format descriptor, passed in ECX.
 * @param target Candidate descriptor, passed in EDX.
 * @return An asymmetric conversion penalty, or UINT32_MAX for incompatibility
 *         or loss of every nonzero source comparison field. Lower scores are preferred.
 * @note Uses the original two-register ABI with no stack arguments or callee pop.
 */
extern "C" uint32_t __attribute__((fastcall))
score_texture_format_conversion(const TextureFormatRecord* source,
                                const TextureFormatRecord* target) {
    const u32 source_kind = read_word(source->words + 1);
    const u32 target_kind = read_word(target->words + 1);
    const u32 compatibility_address =
        reinterpret_cast<u32>(dat_006dc510) + 4 * (source_kind * 5 + target_kind);
    if (!read_word(pointer_from_address(compatibility_address)))
        return 0xffffffff;
    u32 score = 0, source_nonzero = 0;
    for (unsigned i = 0; i < 5; ++i) {
        const u32 from = read_word(source->words + 3 + i);
        if (from)
            ++source_nonzero;
        const u32 to = read_word(target->words + 3 + i);
        if (from < to)
            score += from ? to - from : 0x100;
        else if (from > to)
            score += to ? (from - to) << 16 : 0x1000000;
    }
    return source_nonzero == (score >> 24) ? 0xffffffff : score;
}
