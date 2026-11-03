#include "cxx_typeinfo.h"

// Original006D5F18 contains this one deleting-destructor pointer. The compiler
// alias supplies the same genuine table to its emitted x86 TypeDescriptors.
extern "C" const OriginalTypeInfoDeletingDestructor dat_006d5f18[1] = {fun_005cde04};
__asm__(".globl \"??_7type_info@@6B@\"\n\t.set \"??_7type_info@@6B@\", _dat_006d5f18\n\t");
