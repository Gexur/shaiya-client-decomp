// Original005CEDE4's handler at005CEE18 stores a null result and resumes the
// common return. Its original C++ catch-all metadata is recorded separately.
// The compiler's CxxFrameHandler3 ABI remains an explicit runtime dependency
// until its adapter to the recovered original C++ handler is implemented.
#include "allocations.h"

extern "C" void* fun_005cede4(uint32_t bytes, const void* /*unused_tag*/) {
    try {
        return fun_005cc96d(bytes);
    } catch (...) {
        return nullptr;
    }
}
