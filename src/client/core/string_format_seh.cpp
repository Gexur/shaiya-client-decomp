#include "string_format.h"
#include "../runtime/stdio_format.h"
#include "../runtime/allocations.h"
using shaiya::startup::String_00405710;
namespace {
uint32_t length(const char* text) {
    uint32_t count = 0, value;
    do {
        __asm__ __volatile__("movzbl (%1),%0" : "=r"(value) : "r"(text + count) : "memory");
        ++count;
    } while (value != 0);
    return count - 1;
}
void initialize(String_00405710* value) {
    value->capacity_018 = 15;
    value->size_014 = 0;
    value->storage_004[0] = 0;
}
// This guard expresses the original single unwind-map destructor. It becomes
// active only after the temporary string construction has returned normally.
struct TemporaryUnwind {
    String_00405710* value;
    bool active = true;
    ~TemporaryUnwind() noexcept(false) {
        if (active)
            FUN_00529db0(value);
    }
};
} // namespace
extern "C" String_00405710* fun_005bf0c0(String_00405710* output, const char* format,
                                         const void* argument_words) {
    char buffer[1024] = {};
    int32_t count = fun_005d139d(buffer, 1024, format, argument_words);
    if (count > 1000000)
        count = 1000000;
    else if (count <= 1024) {
        initialize(output);
        FUN_00405710(output, buffer, length(buffer));
        return output;
    }
    char* allocated = static_cast<char*>(fun_005cfade(uint32_t(count) + 1));
    (void)fun_005d139d(allocated, uint32_t(count), format, argument_words);
    allocated[uint32_t(count)] = 0;
    String_00405710 temporary;
    initialize(&temporary);
    FUN_00405710(&temporary, allocated, length(allocated));
    TemporaryUnwind unwind{&temporary};
    fun_005cfaf0(allocated);
    initialize(output);
    FUN_00405620(output, &temporary, 0, 0xffffffffu);
    if (temporary.capacity_018 >= 16)
        fun_005cc620(*reinterpret_cast<void**>(temporary.storage_004));
    unwind.active = false;
    return output;
}
