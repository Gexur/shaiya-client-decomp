#include "cinit.h"
#include "stdio.h"
#include "cxx_filter.h"

extern "C" void terminate_stdio_005d0152() {
    (void)fun_005d0152();
}
extern "C" void terminate_temporary_files_006abadc() {
    (void)fun_006abadc();
}
extern "C" void restore_exception_filter_005d2a4d() {
    (void)fun_005d2a4d();
}
extern "C" {
// Actual original slots708504..70850c and708514..708518, respectively.
OriginalCppInitializer dat_00708504[3] = {nullptr, terminate_stdio_005d0152,
                                          terminate_temporary_files_006abadc};
OriginalCppInitializer dat_00708514[2] = {nullptr, restore_exception_filter_005d2a4d};
}
