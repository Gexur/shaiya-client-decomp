#include "network/outbound.h"
#include "core/string_format.h"
#include "runtime/allocations.h"
#include "startup/global_initializers_strings.h"
#include "archive/saf_open.h"
#include <stdarg.h>

namespace {
uint32_t word(const void* pointer) {
    uint32_t value;
    __asm__ __volatile__("movl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
struct MessageUnwind {
    shaiya::startup::String_00405710* value;
    bool active = true;
    ~MessageUnwind() noexcept(false) {
        if (active)
            FUN_00529db0(value);
    }
};
} // namespace

// Original 0x0044cd20..0x0044cda6. The format helper completes before the
// caller's site/category words and the three site fields are read.
extern "C" void PACKET_CDECL fun_0044cd20(const PacketDumpSite* location, uint32_t category,
                                          const char* format, ...) {
    va_list words;
    va_start(words, format);
    shaiya::startup::String_00405710 message;
    fun_005bf0c0(&message, format, words);
    va_end(words);
    MessageUnwind unwind{&message};
    const auto* site = reinterpret_cast<const PacketDumpSite*>(uintptr_t(word(&location)));
    const uint32_t line = word(&site->line);
    const char* file = reinterpret_cast<const char*>(uintptr_t(word(&site->file)));
    const char* procedure = reinterpret_cast<const char*>(uintptr_t(word(&site->procedure)));
    const uint32_t flags = word(&category);
    OriginalSafLogger* logger = fun_0040ae80(&dat_0070ca70);
    fun_005ba070(logger, flags, procedure, file, line, &message);
    if (message.capacity_018 >= 16)
        fun_005cc620(*reinterpret_cast<void**>(message.storage_004));
    unwind.active = false;
}
