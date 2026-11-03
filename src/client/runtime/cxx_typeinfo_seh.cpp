#include "cxx_typeinfo.h"
#include "heap.h"
#include "allocations.h"

extern "C" void fun_005cddfb() {
    fun_005d64e6(14);
}

extern "C" void __attribute__((thiscall)) fun_005cddbe(OriginalTypeInfo* information) {
    information->vtable = dat_006d5f18;
    fun_005d659b(14);
    __try {
        if (information->allocated_name != nullptr)
            fun_005cfaf0(information->allocated_name);
    } __finally {
        fun_005cddfb();
    }
}

extern "C" OriginalTypeInfo* __attribute__((thiscall)) fun_005cde04(OriginalTypeInfo* information,
                                                                    uint32_t deletion_flags) {
    fun_005cddbe(information);
    if ((deletion_flags & 1) != 0)
        fun_005cc620(information);
    return information;
}
