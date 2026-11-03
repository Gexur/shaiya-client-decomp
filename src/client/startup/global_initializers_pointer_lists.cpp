#include "global_initializers_pointer_lists.h"
#include "../runtime/array_lifetime.h"
#include "../runtime/exit_registry.h"

extern "C" OriginalPointerList16 dat_0220f268[4] = {};
extern "C" void fun_006b72a0() {
    fun_005ce6bb(dat_0220f268, 16, 4, reinterpret_cast<OriginalElementCallback>(FUN_00554cf0),
                 reinterpret_cast<OriginalElementCallback>(FUN_00554ef0));
    (void)fun_005ccf60(fun_006ba270);
}
extern "C" void fun_006ba270() {
    fun_005cdcbc(dat_0220f268, 16, 4, reinterpret_cast<OriginalElementCallback>(FUN_00554ef0));
}
