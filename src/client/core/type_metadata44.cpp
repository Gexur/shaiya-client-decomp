#include "type_metadata44.h"
#include "../runtime/allocations.h"
namespace {
inline void raw_store(void* p, uint32_t value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(value) : "memory");
}
inline uint8_t raw_byte(const char* p) {
    uint8_t value;
    __asm__ volatile("movb (%1),%0" : "=q"(value) : "r"(p) : "memory");
    return value;
}
} // namespace
extern "C" const OriginalTypeMetadataDeleting dat_006d22d4[1] = {FUN_005c45d0};
extern "C" OriginalTypeMetadata44* __attribute__((thiscall))
FUN_005c45f0(OriginalTypeMetadata44* object, const char* text, uint32_t value28, uint32_t value04,
             OriginalTypeMetadata44* parent08) {
    // Follow the original store order, including faults/aliases while scanning
    // the input. The final value28 store occurs only after string assignment.
    raw_store(&object->parent08, reinterpret_cast<uint32_t>(parent08));
    raw_store(&object->value04, value04);
    raw_store(&object->vtable, reinterpret_cast<uint32_t>(dat_006d22d4));
    raw_store(&object->name0c.capacity_018, 15);
    raw_store(&object->name0c.size_014, 0);
    *static_cast<volatile unsigned char*>(object->name0c.storage_004) = 0;
    uint32_t length = 0;
    while (raw_byte(text + length) != 0)
        ++length;
    FUN_00405710(&object->name0c, text, length);
    object->value28 = value28;
    return object;
}
extern "C" uint32_t __attribute__((thiscall)) FUN_005c45a0(OriginalTypeMetadata44* object) {
    object->vtable = dat_006d22d4;
    if (object->name0c.capacity_018 >= 16) {
        void* pointer;
        __asm__ volatile("movl (%1),%0"
                         : "=r"(pointer)
                         : "r"(object->name0c.storage_004)
                         : "memory");
        fun_005cc620(pointer);
    }
    object->name0c.capacity_018 = 15;
    object->name0c.size_014 = 0;
    object->name0c.storage_004[0] = 0;
    return 0;
}
extern "C" OriginalTypeMetadata44* __attribute__((thiscall))
FUN_005c45d0(OriginalTypeMetadata44* object, uint32_t flags) {
    (void)FUN_005c45a0(object);
    if (flags & 1)
        fun_005cc620(object);
    return object;
}
