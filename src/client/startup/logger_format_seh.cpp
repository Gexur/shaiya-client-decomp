#include "logger_format.h"
#include "core/string_format.h"
#include "core/string_internal.h"
#include "runtime/allocations.h"
#include "runtime/stdio_format.h"
#include <stdarg.h>
namespace {
struct StringUnwind {
    shaiya::startup::String_00405710* value;
    bool active = true;
    ~StringUnwind() noexcept(false) {
        if (active)
            FUN_00529db0(value);
    }
};
uint32_t read32(const void* p) {
    uint32_t v;
    __asm__ __volatile__("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void store32(void* p, uint32_t v) {
    __asm__ __volatile__("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void store8(uint8_t* p, uint8_t v) {
    __asm__ __volatile__("movb %1,(%0)" ::"r"(p), "q"(v) : "memory");
}
} // namespace
extern "C" void fun_005b9f30(OriginalSafLogger* self, uint32_t flags, const char* format, ...) {
    if ((read32(&self->flags) & flags) != flags)
        return;
    if (read32(&self->file) == 0)
        return;
    if (flags == 0x1000)
        return;
    va_list words;
    va_start(words, format);
    shaiya::startup::String_00405710 message;
    fun_005bf0c0(&message, format, words);
    va_end(words);
    StringUnwind message_unwind{&message};
    const char* const time = fun_005c3a00("%H:%M:%S");
    shaiya::startup::String_00405710 timestamp;
    FUN_00405800(&timestamp, time);
    StringUnwind timestamp_unwind{&timestamp};
    const char* const text =
        reinterpret_cast<const char*>(shaiya::recovered_string::data(&message));
    const auto* const level = fun_005b9340(flags);
    const char* const label = reinterpret_cast<const char*>(shaiya::recovered_string::data(level));
    const char* const clock =
        reinterpret_cast<const char*>(shaiya::recovered_string::data(&timestamp));
    (void)fun_005cdb8c(self->file, "[%s] [%s] %s\r\n", clock, label, text);
    (void)fun_005d0050(self->file);
    if (timestamp.capacity_018 >= 16)
        fun_005cc620(*reinterpret_cast<void**>(timestamp.storage_004));
    store32(&timestamp.capacity_018, 15);
    store32(&timestamp.size_014, 0);
    store8(timestamp.storage_004, 0);
    if (message.capacity_018 >= 16)
        fun_005cc620(*reinterpret_cast<void**>(message.storage_004));
    timestamp_unwind.active = false;
    message_unwind.active = false;
}
extern "C" void FUN_005b9f30(OriginalSafLogger*, uint32_t, const char*, ...)
    __attribute__((alias("fun_005b9f30")));
