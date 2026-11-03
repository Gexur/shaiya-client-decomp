#include "fpmath.h"
extern "C" {
// Address-only declarations preserve the original stores without calling
// incompatible function types through the opaque callback-slot storage.
extern const unsigned char code_005d2ed8[] __asm__("_fun_005d2ed8");
extern const unsigned char code_005d2b58[] __asm__("_fun_005d2b58");
extern const unsigned char code_005d2bbd[] __asm__("_fun_005d2bbd");
extern const unsigned char code_005d2b1c[] __asm__("_fun_005d2b1c");
extern const unsigned char code_005d2ba3[] __asm__("_fun_005d2ba3");
}
extern "C" void __cdecl fun_005ccf72() {
    dat_0070e500 =
        reinterpret_cast<FloatingRoutineAddress>(const_cast<unsigned char*>(code_005d2ed8));
    dat_0070e504 =
        reinterpret_cast<FloatingRoutineAddress>(const_cast<unsigned char*>(code_005d2b58));
    dat_0070e508 =
        reinterpret_cast<FloatingRoutineAddress>(const_cast<unsigned char*>(code_005d2bbd));
    dat_0070e50c =
        reinterpret_cast<FloatingRoutineAddress>(const_cast<unsigned char*>(code_005d2b1c));
    dat_0070e510 =
        reinterpret_cast<FloatingRoutineAddress>(const_cast<unsigned char*>(code_005d2ba3));
    dat_0070e514 =
        reinterpret_cast<FloatingRoutineAddress>(const_cast<unsigned char*>(code_005d2ed8));
}
