#include "common_path_strings.h"
#include "core/string_append.h"
#include "startup/global_initializers_strings.h"
namespace {
using String = shaiya::startup::String_00405710;
void initialize(String* s) {
    s->capacity_018 = 15;
    s->size_014 = 0;
    s->storage_004[0] = 0;
}
const char* data(const String* s) {
    return s->capacity_018 < 16 ? reinterpret_cast<const char*>(s->storage_004)
                                : *reinterpret_cast<const char* const*>(s->storage_004);
}
char* data(String* s) {
    return const_cast<char*>(data(static_cast<const String*>(s)));
}
struct Cleanup {
    String* s;
    bool active = true;
    ~Cleanup() noexcept(false) {
        if (active)
            FUN_00529db0(s);
    }
};
} // namespace
extern "C" String* FUN_005b8f80(String* output, const String* left, const String* right) {
    String temporary;
    initialize(&temporary);
    FUN_00405620(&temporary, left, 0, 0xffffffffu);
    Cleanup cleanup{&temporary};
    String* joined = FUN_00533d50(&temporary, right, 0, 0xffffffffu);
    initialize(output);
    FUN_00405620(output, joined, 0, 0xffffffffu);
    return output;
}
extern "C" String* FUN_005b90d0(String* output, const char* left, const String* right) {
    String temporary;
    initialize(&temporary);
    uint32_t length = 0;
    while (left[length])
        ++length;
    FUN_00405710(&temporary, left, length);
    Cleanup cleanup{&temporary};
    String* joined = FUN_00533d50(&temporary, right, 0, 0xffffffffu);
    initialize(output);
    FUN_00405620(output, joined, 0, 0xffffffffu);
    return output;
}
extern "C" String* __attribute__((thiscall)) FUN_005bef20(const String* self, String* output,
                                                          uint32_t position, uint32_t count) {
    output->size_014 = 0;
    output->capacity_018 = 15;
    output->storage_004[0] = 0;
    FUN_00405620(output, self, position, count);
    return output;
}
extern "C" uint32_t __attribute__((thiscall)) FUN_005bfb80(const String* self, const char* text,
                                                           uint32_t position, uint32_t count) {
    if (count == 0)
        return self->size_014 <= position ? self->size_014 : position;
    if (count > self->size_014)
        return 0xffffffffu;
    uint32_t index = self->size_014 - count;
    if (position < index)
        index = position;
    const char* bytes = data(self);
    for (;;) {
        if (bytes[index] == text[0]) {
            uint32_t i = 0;
            while (i < count && bytes[index + i] == text[i])
                ++i;
            if (i == count)
                return index;
        }
        if (index == 0)
            break;
        --index;
    }
    return 0xffffffffu;
}
extern "C" String* FUN_005c3e50(String* output, const String* path, String* filename) {
    String temporary;
    initialize(&temporary);
    FUN_00405620(&temporary, path, 0, 0xffffffffu);
    Cleanup cleanup{&temporary};
    char* first = data(&temporary);
    char* end = first + temporary.size_014;
    uint32_t length = temporary.size_014;
    for (char* p = first; p != end; ++p)
        if (*p == '\\') {
            *p = '/';
            length = temporary.size_014;
        }
    const char separator = '/';
    uint32_t position = FUN_005bfb80(&temporary, &separator, 0xffffffffu, 1);
    if (position == 0xffffffffu) {
        if (filename)
            FUN_00405620(filename, &temporary, 0, 0xffffffffu);
        initialize(output);
        FUN_00405620(output, &dat_0070d030, 0, 0xffffffffu);
    } else {
        if (filename) {
            String tail;
            FUN_005bef20(&temporary, &tail, position + 1, length - position - 1);
            Cleanup tail_cleanup{&tail};
            FUN_00405620(filename, &tail, 0, 0xffffffffu);
        }
        FUN_005bef20(&temporary, output, 0, position + 1);
    }
    return output;
}
