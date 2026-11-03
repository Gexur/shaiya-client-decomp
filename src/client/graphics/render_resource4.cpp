#include "graphics/render_resource4.h"
namespace {
using u32 = uint32_t;
void clear(void* self, u32 offset) {
    auto* at = static_cast<unsigned char*>(self) + offset;
    __asm__ volatile("movl $0,(%0)" ::"r"(at) : "memory");
}
} // namespace
// Label rendering no longer stores GPU ownership in this old scratch prefix.
// Native label generation owns and releases its explicit local target scope.
extern "C" uint32_t __attribute__((thiscall)) FUN_0054a480(void* self) {
    for (u32 offset = 0; offset < 16; offset += 4)
        clear(self, offset);
    return 0;
}
