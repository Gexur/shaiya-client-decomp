#include "resource_tree72_allocate.h"
#include "runtime/allocations.h"
extern "C" OriginalNestedNode72* FUN_005b8ac0() {
    auto* node = static_cast<OriginalNestedNode72*>(fun_005cc96d(72));
    const uint32_t address = reinterpret_cast<uint32_t>(node);
    if (address != 0)
        *reinterpret_cast<volatile uint32_t*>(address) = 0;
    if (address + 4u != 0)
        *reinterpret_cast<volatile uint32_t*>(address + 4u) = 0;
    if (address + 8u != 0)
        *reinterpret_cast<volatile uint32_t*>(address + 8u) = 0;
    *reinterpret_cast<volatile uint8_t*>(address + 0x44u) = 1;
    *reinterpret_cast<volatile uint8_t*>(address + 0x45u) = 0;
    return node;
}
