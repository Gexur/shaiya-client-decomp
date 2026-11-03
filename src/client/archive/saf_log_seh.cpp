#include "archive/saf_open.h"

#include "core/string_format.h"
#include "startup/global_initializers_strings.h"
#include "runtime/allocations.h"
#include <stdarg.h>

namespace {

struct MessageCleanup {
    shaiya::startup::String_00405710* message;
    bool active = true;
    /**
     * @brief Destroy the formatted message if logging unwinds before normal cleanup.
     */
    ~MessageCleanup() noexcept(false) {
        if (active) {
            FUN_00529db0(message);
        }
    }
};

} // namespace

/**
 * @brief Format a message and send it to the archive logger with source metadata.
 *
 * Preserves line, file and function reads before logger lookup and unwinding cleanup. Recovered Ep5.4 entry: 0x0040d250.
 * @param location Function, source-file and line metadata for the log record.
 * @param format NUL-terminated printf-style format string.
 */
extern "C" void log_archive_message(const OriginalSafSourceLocation* location, const char* format,
                                    ...) {
    va_list arguments;
    va_start(arguments, format);
    shaiya::startup::String_00405710 message;
    fun_005bf0c0(&message, format, arguments);
    va_end(arguments);
    MessageCleanup cleanup{&message};

    // Read metadata in the original order, with one x86 load per field.
    const volatile OriginalSafSourceLocation* source = location;
    const uint32_t source_line = source->line;
    const char* const source_file = source->file;
    const char* const source_function = source->function;
    OriginalSafLogger* const logger = fun_0040ae80(&dat_0070ca70);
    fun_005ba070(logger, 1, source_function, source_file, source_line, &message);
    if (message.capacity_018 >= 16) {
        fun_005cc620(*reinterpret_cast<void**>(message.storage_004));
    }
    cleanup.active = false;
}
