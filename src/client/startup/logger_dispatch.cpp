#include "logger.h"
namespace {
uint32_t read32(const void* pointer) {
    uint32_t value;
    __asm__ __volatile__("movl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
uint8_t read8(const void* pointer) {
    uint32_t value;
    __asm__ __volatile__("movzbl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return uint8_t(value);
}
} // namespace
extern "C" void fun_005b8b80(const shaiya::startup::String_00405710* name, uint32_t flags,
                             const char* function, const char* file, uint32_t line,
                             const shaiya::startup::String_00405710* message) {
    if (read8(&dat_0224e6b8) == 0)
        return;
    uint32_t begin = read32(&dat_0224e710.begin);
    const uint32_t count =
        begin == 0 ? 0 : uint32_t(int32_t(read32(&dat_0224e710.end) - begin) >> 2);
    if (count == 0)
        return;
    const uint32_t saved_line = line;
    const auto* const saved_message = message;
    for (uint32_t index = 0;;) {
        const auto* const current_file = reinterpret_cast<const char*>(uintptr_t(read32(&file)));
        auto* const listener = reinterpret_cast<OriginalLogListener*>(
            uintptr_t(read32(reinterpret_cast<const void*>(uintptr_t(begin + index * 4)))));
        auto* const vtable =
            reinterpret_cast<OriginalLogListenerVtable*>(uintptr_t(read32(&listener->vtable)));
        const auto* const current_function =
            reinterpret_cast<const char*>(uintptr_t(read32(&function)));
        const uint32_t current_flags = read32(&flags);
        const auto* const current_name =
            reinterpret_cast<const shaiya::startup::String_00405710*>(uintptr_t(read32(&name)));
        const auto notify =
            reinterpret_cast<OriginalLogNotification>(uintptr_t(read32(&vtable->notify)));
        notify(listener, current_name, current_flags, current_function, current_file, saved_line,
               saved_message);
        ++index;
        if (index >= count)
            return;
        begin = read32(&dat_0224e710.begin);
    }
}
