#include "string_internal.h"
#include "memory.h"
#include "../runtime/allocations.h"

using shaiya::recovered_string::copy;
using shaiya::recovered_string::data;
using shaiya::startup::String_00405710;

extern "C" String_00405710* __attribute__((thiscall))
FUN_00405460(String_00405710* self, uint32_t position, uint32_t count) {
    if (self->size_014 < position)
        FUN_005e1911();
    const uint32_t remaining = self->size_014 - position;
    if (remaining < count)
        count = remaining;
    if (count != 0) {
        fun_005cc630(data(self) + position, data(self) + position + count, remaining - count);
        self->size_014 -= count;
        data(self)[self->size_014] = 0;
    }
    return self;
}

extern "C" unsigned char* FUN_0040557c(String_00405710* self, unsigned char* new_storage,
                                       uint32_t capacity, uint32_t old_size) {
    if (old_size != 0)
        copy(new_storage, data(self), old_size);
    if (self->capacity_018 >= 16)
        fun_005cc620(data(self));
    self->storage_004[0] = 0;
    *reinterpret_cast<unsigned char**>(self->storage_004) = new_storage;
    self->capacity_018 = capacity;
    self->size_014 = old_size;
    unsigned char* result = capacity < 16 ? self->storage_004 : new_storage;
    result[old_size] = 0;
    return result;
}

extern "C" String_00405710* __attribute__((thiscall)) FUN_00405620(String_00405710* self,
                                                                   const String_00405710* source,
                                                                   uint32_t position,
                                                                   uint32_t count) {
    if (source->size_014 < position)
        FUN_005e1911();
    uint32_t size = source->size_014 - position;
    if (count < size)
        size = count;
    if (self == source) {
        FUN_00405460(self, size + position, 0xffffffffu);
        FUN_00405460(self, 0, position);
        return self;
    }
    if (size == 0xffffffffu)
        FUN_005e1951(self);
    if (self->capacity_018 < size)
        FUN_004054e0(self, size, self->size_014);
    else if (size == 0) {
        self->size_014 = 0;
        data(self)[0] = 0;
        return self;
    }
    if (size != 0) {
        copy(data(self), data(source) + position, size);
        self->size_014 = size;
        data(self)[size] = 0;
    }
    return self;
}

extern "C" String_00405710* __attribute__((thiscall))
FUN_00405710(String_00405710* self, const char* source, uint32_t size) {
    const uint32_t address = reinterpret_cast<uint32_t>(source);
    const uint32_t begin = reinterpret_cast<uint32_t>(data(self));
    if (begin <= address && address < begin + self->size_014)
        return FUN_00405620(self, self, address - reinterpret_cast<uint32_t>(data(self)), size);
    if (size == 0xffffffffu)
        FUN_005e1951(self);
    if (self->capacity_018 < size)
        FUN_004054e0(self, size, self->size_014);
    else if (size == 0) {
        self->size_014 = 0;
        data(self)[0] = 0;
        return self;
    }
    if (size != 0) {
        copy(data(self), reinterpret_cast<const unsigned char*>(source), size);
        self->size_014 = size;
        data(self)[size] = 0;
    }
    return self;
}
