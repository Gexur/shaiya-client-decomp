#include "common_string_operations.h"
#include "core/string_internal.h"
#include "core/string_append.h"
#include "runtime/exit_registry.h"
namespace {
using String = shaiya::startup::String_00405710;
void initialize(String* s) {
    s->capacity_018 = 15;
    s->size_014 = 0;
    s->storage_004[0] = 0;
}
struct Cleanup {
    String* s;
    ~Cleanup() noexcept(false) {
        FUN_00529db0(s);
    }
};
using shaiya::recovered_string::data;
} // namespace
extern "C" {
String dat_0224eaac = {};
uint32_t dat_0224eac8 = 0;
}
extern "C" String* __attribute__((thiscall)) FUN_005341e0(String* self, const char* bytes,
                                                          uint32_t count) {
    const uint32_t source = reinterpret_cast<uint32_t>(bytes);
    const uint32_t start = reinterpret_cast<uint32_t>(data(self));
    if (start <= source && source < reinterpret_cast<uint32_t>(data(self)) + self->size_014)
        return FUN_00533d50(self, self, source - reinterpret_cast<uint32_t>(data(self)), count);
    if (0xffffffffu - self->size_014 <= count)
        FUN_005e1951(self);
    if (count) {
        const uint32_t total = self->size_014 + count;
        if (total == 0xffffffffu)
            FUN_005e1951(self);
        if (self->capacity_018 < total)
            FUN_004054e0(self, total, self->size_014);
        else if (total == 0) {
            self->size_014 = 0;
            data(self)[0] = 0;
            return self;
        }
        if (total) {
            shaiya::recovered_string::copy(data(self) + self->size_014,
                                           reinterpret_cast<const unsigned char*>(bytes), count);
            self->size_014 = total;
            data(self)[total] = 0;
        }
    }
    return self;
}
extern "C" String* FUN_005b9020(String* output, const String* left, const char* right) {
    String temporary;
    initialize(&temporary);
    FUN_00405620(&temporary, left, 0, 0xffffffffu);
    Cleanup cleanup{&temporary};
    uint32_t count = 0;
    while (right[count])
        ++count;
    String* joined = FUN_005341e0(&temporary, right, count);
    initialize(output);
    FUN_00405620(output, joined, 0, 0xffffffffu);
    return output;
}
extern "C" void* fun_005d12f0(const void* input, int32_t value, uint32_t count) {
    auto* p = static_cast<const uint8_t*>(input);
    while (count--) {
        if (*p == uint8_t(value))
            return const_cast<uint8_t*>(p);
        ++p;
    }
    return nullptr;
}
extern "C" uint32_t __attribute__((thiscall)) FUN_005bece0(const String* self, const void* set,
                                                           uint32_t position, uint32_t count) {
    if (count && position < self->size_014) {
        const unsigned char *begin = data(self), *end = begin + self->size_014;
        for (const unsigned char* p = data(self) + position; p < end; ++p)
            if (fun_005d12f0(set, int8_t(*p), count))
                return uint32_t(p - data(self));
    }
    return 0xffffffffu;
}
extern "C" uint32_t __attribute__((thiscall)) FUN_005bed70(const String* self, const void* set,
                                                           uint32_t position, uint32_t count) {
    if (position < self->size_014) {
        const unsigned char *begin = data(self), *end = begin + self->size_014;
        for (const unsigned char* p = data(self) + position; p < end; ++p)
            if (!fun_005d12f0(set, int8_t(*p), count))
                return uint32_t(p - data(self));
    }
    return 0xffffffffu;
}
extern "C" uint32_t __attribute__((thiscall)) FUN_005bedf0(const String* self, const void* set,
                                                           uint32_t position, uint32_t count) {
    if (self->size_014) {
        if (self->size_014 <= position)
            position = self->size_014 - 1;
        const unsigned char* p = data(self) + position;
        for (;;) {
            if (!fun_005d12f0(set, int8_t(*p), count))
                return uint32_t(p - data(self));
            if (p == data(self))
                break;
            --p;
        }
    }
    return 0xffffffffu;
}
extern "C" String* FUN_005befd0(String* self) {
    if ((dat_0224eac8 & 1) == 0) {
        dat_0224eac8 |= 1;
        initialize(&dat_0224eaac);
        FUN_00405710(&dat_0224eaac, " \t\r", 3);
        (void)fun_005ccf60(fun_006bac70);
    }
    uint32_t last = FUN_005bedf0(self, data(&dat_0224eaac), 0xffffffffu, dat_0224eaac.size_014);
    FUN_00405460(self, last + 1, 0xffffffffu);
    uint32_t first = FUN_005bed70(self, data(&dat_0224eaac), 0, dat_0224eaac.size_014);
    return FUN_00405460(self, 0, first);
}
extern "C" void fun_006bac70() {
    FUN_00529db0(&dat_0224eaac);
}
