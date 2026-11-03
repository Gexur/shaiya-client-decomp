#include "logger.h"
#include "../runtime/allocations.h"
namespace {
struct StringUnwind {
    shaiya::startup::String_00405710* value;
    bool active = true;
    ~StringUnwind() noexcept(false) {
        if (active)
            FUN_00529db0(value);
    }
};
void store32(uint32_t* pointer, uint32_t value) {
    __asm__ __volatile__("movl %1,(%0)" ::"r"(pointer), "r"(value) : "memory");
}
void store8(uint8_t* pointer, uint8_t value) {
    __asm__ __volatile__("movb %1,(%0)" ::"r"(pointer), "q"(value) : "memory");
}
} // namespace
extern "C" void __attribute__((thiscall)) fun_005b9bd0(OriginalSafLogger* self) {
    StringUnwind name{&self->name};
    StringUnwind path{&self->path};
    fun_005b9180(self);
    if (self->path.capacity_018 >= 16)
        fun_005cc620(*reinterpret_cast<void**>(self->path.storage_004));
    store32(&self->path.capacity_018, 15);
    store32(&self->path.size_014, 0);
    store8(self->path.storage_004, 0);
    if (self->name.capacity_018 >= 16)
        fun_005cc620(*reinterpret_cast<void**>(self->name.storage_004));
    store32(&self->name.size_014, 0);
    store32(&self->name.capacity_018, 15);
    store8(self->name.storage_004, 0);
    path.active = false;
    name.active = false;
}
