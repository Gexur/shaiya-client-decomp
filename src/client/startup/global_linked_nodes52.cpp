#include "core/linked_nodes52.h"
#include "runtime/allocations.h"
#include "runtime/exit_registry.h"

extern "C" OriginalLinkedNodes52 dat_0224e6ac = {nullptr, nullptr};
extern "C" void fun_006b7740() {
    auto* node = static_cast<OriginalLinkedNode52*>(fun_005cc96d(52));
    dat_0224e6ac.head = node;
    // The original publishes the allocation before this store. A null result
    // faults here; it does not install a substitute node or register cleanup.
    __asm__ volatile("movl $0, (%0)" ::"r"(node) : "memory");
    dat_0224e6ac.current = dat_0224e6ac.head;
    (void)fun_005ccf60(fun_006ba890);
}
extern "C" void fun_006ba890() {
    FUN_005b4ec0(&dat_0224e6ac);
}

__asm__(".globl _dat_0224e6b0\n.set _dat_0224e6b0, _dat_0224e6ac+4\n");
