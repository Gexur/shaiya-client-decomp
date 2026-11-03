#include "logger.h"
#include "global_initializers_strings.h"
#include "../runtime/exit_registry.h"
namespace {
void store32(void* pointer, uint32_t value) {
    __asm__ __volatile__("movl %1,(%0)" ::"r"(pointer), "r"(value) : "memory");
}
void store8(uint8_t* pointer, uint8_t value) {
    __asm__ __volatile__("movb %1,(%0)" ::"r"(pointer), "q"(value) : "memory");
}
} // namespace
extern "C" OriginalSafLogger* __attribute__((thiscall))
fun_005b8f10(OriginalSafLogger* self, const shaiya::startup::String_00405710* name,
             uint32_t flags) {
    store32(&self->file, 0);
    store32(&self->name.capacity_018, 15);
    store32(&self->name.size_014, 0);
    store8(self->name.storage_004, 0);
    FUN_00405620(&self->name, name, 0, 0xffffffffu);
    store32(&self->path.size_014, 0);
    store32(&self->path.capacity_018, 15);
    store8(self->path.storage_004, 0);
    store32(&self->flags, flags);
    return self;
}
extern "C" void fun_006b77b0() {
    fun_005b8f10(&dat_0224e6c0, &dat_0070ca70, 3);
    (void)fun_005ccf60(fun_006bab80);
}
extern "C" void fun_006bab80() {
    fun_005b9bd0(&dat_0224e6c0);
}
