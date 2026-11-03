#include "archive/saf_open.h"

#include "archive/saf.h"
#include "runtime/file_open.h"

namespace {

constexpr int32_t binary_read_flags = 0x8000;
constexpr int32_t text_read_flags = 0x4000;
constexpr int32_t text_create_truncate_flags = 0x4301;
constexpr int32_t append_update_flags = 0x800a;
constexpr int32_t owner_write_permission = 0x80;

/**
 * @brief Compare exactly the requested number of mode bytes, including a supplied NUL.
 * @param mode Exact supported mode string: rb, rt, wt or a+t.
 * @param expected Expected mode bytes, including NUL when part of byte_count.
 * @param byte_count Exact number of bytes to compare.
 * @return True if every compared byte matches.
 */
bool mode_matches(const char* mode, const char* expected, uint32_t byte_count) {
    for (uint32_t index = 0; index < byte_count; ++index) {
        const uint8_t character = *reinterpret_cast<const volatile uint8_t*>(mode + index);
        if (character != uint8_t(expected[index])) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Log an archive-open failure using its original source location.
 * @param path NUL-terminated file path to resolve or open.
 * @param source_line Recovered SAFile.cpp source line attached to the failure.
 * @return Zero, matching the original file-open failure result.
 */
int32_t report_open_failure(const char* path, uint32_t source_line) {
    const OriginalSafSourceLocation location = {"safopen", "D:\\ENGLISH\\GAME\\SAFile.cpp",
                                                source_line};
    log_archive_message(&location, "File Not Open [%s]", path);
    return 0;
}

} // namespace

/**
 * @brief Open a supported file mode, resolving read paths through data.saf first.
 *
 * Read modes require data.saf to open before loose-file fallback is attempted. Recovered Ep5.4 entry: 0x0040d2e0.
 * @param path NUL-terminated file path to resolve or open.
 * @param mode Exact supported mode string: rb, rt, wt or a+t.
 * @return The opened descriptor, or zero after reporting an open failure.
 */
extern "C" int32_t open_archive_or_loose_file(const char* path, const char* mode) {
    if (!mode_matches(mode, "rb", 3) && !mode_matches(mode, "rt", 3)) {
        int32_t descriptor;
        if (mode_matches(mode, "wt", 3)) {
            descriptor = _open(path, text_create_truncate_flags, owner_write_permission);
        } else if (mode_matches(mode, "a+t", 4)) {
            descriptor = _open(path, append_update_flags);
        } else {
            return report_open_failure(path, 0x1bc);
        }
        return descriptor != -1 ? descriptor : report_open_failure(path, 0x1bc);
    }

    int32_t descriptor;
    if (mode_matches(mode, "rb", 3)) {
        descriptor = _open("data.saf", binary_read_flags);
    } else if (mode_matches(mode, "rt", 3)) {
        descriptor = _open("data.saf", text_read_flags);
    } else {
        return report_open_failure(path, 0x1c8);
    }
    // The original requires data.saf to open before trying a loose file.
    if (descriptor == -1) {
        return report_open_failure(path, 0x1c8);
    }
    const int32_t archive_descriptor = descriptor;
    if (seek_archive_entry(&descriptor, path)) {
        return archive_descriptor;
    }
    _close(archive_descriptor);
    descriptor = archive_descriptor;
    // Mode bytes are intentionally reread across the preceding calls.
    if (mode_matches(mode, "rb", 3)) {
        descriptor = _open(path, binary_read_flags);
    } else if (mode_matches(mode, "rt", 3)) {
        descriptor = _open(path, text_read_flags);
    }
    return descriptor != -1 ? descriptor : report_open_failure(path, 0x1d6);
}
