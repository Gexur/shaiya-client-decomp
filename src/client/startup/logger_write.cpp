#include "logger.h"
#include "../core/string_internal.h"
#include "../runtime/stdio_format.h"
extern "C" void __attribute__((thiscall))
fun_005ba070(OriginalSafLogger* self, uint32_t flags, const char* function, const char* file,
             uint32_t line, const shaiya::startup::String_00405710* message) {
    if ((self->flags & flags) != flags || flags == 0x1000)
        return;
    fun_005b8b80(&self->name, flags, function, file, line, message);
    if (self->file == nullptr)
        return;
    if (file == nullptr)
        file = "UnknownFileName";
    if (function == nullptr)
        function = "UnknownFunction";
    const char* text = reinterpret_cast<const char*>(shaiya::recovered_string::data(message));
    auto* level = fun_005b9340(flags);
    const char* label = reinterpret_cast<const char*>(shaiya::recovered_string::data(level));
    const char* timestamp = fun_005c3a00("%H:%M:%S");
    (void)fun_005cdb8c(self->file, "[%s] [%s] %s %s(%ld)\r\n\t%s\r\n", timestamp, label, function,
                       file, line, text);
    (void)fun_005d0050(self->file);
}
