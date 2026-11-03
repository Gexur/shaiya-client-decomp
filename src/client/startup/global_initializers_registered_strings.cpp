// Original registration-only callbacks and their concrete string destructors.
#include "global_initializers_registered_strings.h"
#include "../runtime/exit_registry.h"
#include "../runtime/allocations.h"

extern "C" {
shaiya::startup::String_00405710 dat_0070cb00 = {{}, {}, 0, 15};
shaiya::startup::String_00405710 dat_0070cfd4 = {{}, {}, 0, 15};
shaiya::startup::String_00405710 dat_0070cff0 = {{}, {}, 0, 15};
}

extern "C" void fun_006b78b0() {
    (void)fun_005ccf60(fun_006bacd0);
}
extern "C" void fun_006b7900() {
    (void)fun_005ccf60(fun_006bad70);
}
extern "C" void fun_006b7910() {
    (void)fun_005ccf60(fun_006bada0);
}

extern "C" void fun_006bacd0() {
    if (dat_0070cb00.capacity_018 >= 16)
        fun_005cc620(*reinterpret_cast<void**>(dat_0070cb00.storage_004));
    dat_0070cb00.capacity_018 = 15;
    dat_0070cb00.size_014 = 0;
    dat_0070cb00.storage_004[0] = 0;
}
extern "C" void fun_006bad70() {
    if (dat_0070cfd4.capacity_018 >= 16)
        fun_005cc620(*reinterpret_cast<void**>(dat_0070cfd4.storage_004));
    dat_0070cfd4.capacity_018 = 15;
    dat_0070cfd4.size_014 = 0;
    dat_0070cfd4.storage_004[0] = 0;
}
extern "C" void fun_006bada0() {
    if (dat_0070cff0.capacity_018 >= 16)
        fun_005cc620(*reinterpret_cast<void**>(dat_0070cff0.storage_004));
    dat_0070cff0.capacity_018 = 15;
    dat_0070cff0.size_014 = 0;
    dat_0070cff0.storage_004[0] = 0;
}
