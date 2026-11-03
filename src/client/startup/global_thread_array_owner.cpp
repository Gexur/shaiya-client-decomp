#include "global_thread_array_owner.h"
#include "../runtime/array_lifetime.h"
#include "../runtime/exit_registry.h"
extern "C" {
OriginalThreadArrayOwner32 dat_0220f068[16] = {};
void fun_006b71a0() {
    fun_005ce6bb(dat_0220f068, 32, 16, reinterpret_cast<OriginalElementCallback>(FUN_005535d0),
                 reinterpret_cast<OriginalElementCallback>(FUN_00553600));
    (void)fun_005ccf60(fun_006ba150);
}
void fun_006ba150() {
    fun_005cdcbc(dat_0220f068, 32, 16, reinterpret_cast<OriginalElementCallback>(FUN_00553600));
}
}
