#include "graphics/render_interpolate_dispatch.h"
#include "graphics/render_interpolate.h"
#include "startup/math_dispatch_state.h"
namespace {
inline uint32_t word_at(uint32_t address) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(address) : "memory");
    return value;
}
using Target = decltype(&FUN_005e3ddd);
} // namespace
// The originals call the real initializer before any incoming word is loaded,
// FLD/FSTP the coefficient into the outgoing slot, push the other words in
// reverse order, then load the selected canonical table entry at the CALL.
extern "C" void* recovered_interpolation_dispatch(uint32_t slot, uint32_t* arguments) {
    FUN_005fd1f8(1);
    const uint32_t incoming = reinterpret_cast<uint32_t>(arguments);
    uint32_t coefficient;
    __asm__ volatile("flds (%1)\n\tfstps %0" : "=m"(coefficient) : "r"(incoming + 20) : "memory");
    const uint32_t fifth = word_at(incoming + 16);
    const uint32_t fourth = word_at(incoming + 12);
    const uint32_t third = word_at(incoming + 8);
    const uint32_t second = word_at(incoming + 4);
    const uint32_t first = word_at(incoming);
    return reinterpret_cast<Target>(dat_0070f370.entries[slot])(
        reinterpret_cast<void*>(first), reinterpret_cast<const void*>(second),
        reinterpret_cast<const void*>(third), reinterpret_cast<const void*>(fourth),
        reinterpret_cast<const void*>(fifth), coefficient);
}
#define ORIGINAL_INTERPOLATION_DISPATCH(address, slot)                                             \
    extern "C" __attribute__((naked)) void* __attribute__((stdcall)) FUN_##address(                \
        void*, const void*, const void*, const void*, const void*, uint32_t) {                     \
        __asm__ volatile(                                                                          \
            "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl $" #slot                                     \
            "\n\tcalll _recovered_interpolation_dispatch\n\taddl $8,%esp\n\tretl $24");            \
    }
ORIGINAL_INTERPOLATION_DISPATCH(005e3db1, 18)
ORIGINAL_INTERPOLATION_DISPATCH(005e3e6d, 48)
ORIGINAL_INTERPOLATION_DISPATCH(005e40f1, 50)
ORIGINAL_INTERPOLATION_DISPATCH(005e41cd, 51)
ORIGINAL_INTERPOLATION_DISPATCH(005e4855, 53)
ORIGINAL_INTERPOLATION_DISPATCH(005e4954, 54)
