#include "sentinel_list12.h"
#include "../runtime/allocations.h"
#include "../runtime/exit_registry.h"
namespace {
inline uint32_t read_word(uint32_t p) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(p) : "memory");
    return value;
}
inline void write_word(uint32_t p, uint32_t value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(value) : "memory");
}
} // namespace
extern "C" OriginalSentinelList12 dat_022032b4 = {};
extern "C" OriginalSentinelNode12* FUN_004ce840() {
    auto* node = static_cast<OriginalSentinelNode12*>(fun_005cc96d(12));
    const uint32_t address = reinterpret_cast<uint32_t>(node);
    if (address != 0)
        write_word(address, address);
    const uint32_t previous = address + 4;
    // This is the original second test. Null allocation faults at address4;
    // replacing it with a conventional null guard would change the program.
    if (previous != 0)
        write_word(previous, address);
    return node;
}
extern "C" void fun_006b6800() {
    dat_022032b4.sentinel04 = FUN_004ce840();
    dat_022032b4.count08 = 0;
    (void)fun_005ccf60(fun_006b92f0);
}
extern "C" void fun_006b92f0() {
    OriginalSentinelNode12* sentinel = dat_022032b4.sentinel04;
    auto* node =
        reinterpret_cast<OriginalSentinelNode12*>(read_word(reinterpret_cast<uint32_t>(sentinel)));
    write_word(reinterpret_cast<uint32_t>(sentinel), reinterpret_cast<uint32_t>(sentinel));
    sentinel = dat_022032b4.sentinel04;
    write_word(reinterpret_cast<uint32_t>(sentinel) + 4, reinterpret_cast<uint32_t>(sentinel));
    sentinel = dat_022032b4.sentinel04;
    dat_022032b4.count08 = 0;
    while (node != sentinel) {
        auto* next =
            reinterpret_cast<OriginalSentinelNode12*>(read_word(reinterpret_cast<uint32_t>(node)));
        fun_005cc620(node);
        sentinel = dat_022032b4.sentinel04;
        node = next;
    }
    fun_005cc620(sentinel);
    dat_022032b4.sentinel04 = nullptr;
}
