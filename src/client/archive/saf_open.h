#pragma once

#include "core/string.h"

struct OriginalSafSourceLocation {
    const char* function;
    const char* file;
    uint32_t line;
};
static_assert(sizeof(OriginalSafSourceLocation) == 12);
static_assert(offsetof(OriginalSafSourceLocation, function) == 0);
static_assert(offsetof(OriginalSafSourceLocation, file) == 4);
static_assert(offsetof(OriginalSafSourceLocation, line) == 8);

struct OriginalSafLogger;

extern "C" {
/**
 * @brief Open a supported file mode, resolving read paths through data.saf first.
 *
 * Read modes require data.saf to open before loose-file fallback is attempted. Recovered Ep5.4 entry: 0x0040d2e0.
 * @param path NUL-terminated file path to resolve or open.
 * @param mode Exact supported mode string: rb, rt, wt or a+t.
 * @return The opened descriptor, or zero after reporting an open failure.
 */
int32_t open_archive_or_loose_file(const char* path, const char* mode);

/**
 * @brief Format a message and send it to the archive logger with source metadata.
 *
 * Preserves line, file and function reads before logger lookup and unwinding cleanup. Recovered Ep5.4 entry: 0x0040d250.
 * @param location Function, source-file and line metadata for the log record.
 * @param format NUL-terminated printf-style format string.
 */
void log_archive_message(const OriginalSafSourceLocation* location, const char* format, ...);
/**
 * @brief Look up the logger selected by its recovered string name.
 *
 * Recovered Ep5.4 entry: 0x0040ae80.
 * @param name Recovered logger-name string in the client string representation.
 * @return The logger object returned by the recovered logging subsystem.
 */
OriginalSafLogger* fun_0040ae80(const shaiya::startup::String_00405710* name);
/**
 * @brief Write a formatted message and source location through the recovered logger.
 *
 * Recovered Ep5.4 entry: 0x005ba070.
 * @param logger Recovered logger object that receives the message.
 * @param flags Recovered flags word, with only the documented bits interpreted here.
 * @param function Function name recorded with the message.
 * @param file Source-file name recorded with the message.
 * @param line Source line recorded with the message.
 * @param message Formatted recovered string to write.
 */
void __attribute__((thiscall)) fun_005ba070(OriginalSafLogger* logger, uint32_t flags,
                                            const char* function, const char* file, uint32_t line,
                                            const shaiya::startup::String_00405710* message);
}
