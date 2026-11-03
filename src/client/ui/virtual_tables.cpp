#include "ui/parent_release.h"
#include "ui/parent_draw.h"
#include "ui/profile_access.h"
#include "runtime/purecall.h"

namespace shaiya::ui {
// These are address-only four-byte entries, not inferred C++ virtual method
// prototypes. Calls use the separately recovered interfaces. Each array's
// ten original entries are independently checked against its original PE
// locations; no RTTI prefix, adjacent literals or terminator is invented.
extern "C" const VtableAddress PTR_FUN_006bcc18[10] = {
    reinterpret_cast<VtableAddress>(FUN_00422c20), reinterpret_cast<VtableAddress>(fun_005ce71d),
    reinterpret_cast<VtableAddress>(fun_005ce71d), reinterpret_cast<VtableAddress>(FUN_005bfb50),
    reinterpret_cast<VtableAddress>(FUN_005bfb50), reinterpret_cast<VtableAddress>(FUN_0040a790),
    reinterpret_cast<VtableAddress>(FUN_005bfb50), reinterpret_cast<VtableAddress>(FUN_00526870),
    reinterpret_cast<VtableAddress>(FUN_00526c30), reinterpret_cast<VtableAddress>(FUN_00422c10),
};
extern "C" const VtableAddress PTR_FUN_006c18d8[10] = {
    reinterpret_cast<VtableAddress>(FUN_004a14f0), reinterpret_cast<VtableAddress>(FUN_004a1110),
    reinterpret_cast<VtableAddress>(FUN_004a0720), reinterpret_cast<VtableAddress>(FUN_005bfb50),
    reinterpret_cast<VtableAddress>(FUN_005bfb50), reinterpret_cast<VtableAddress>(FUN_0040a790),
    reinterpret_cast<VtableAddress>(FUN_005bfb50), reinterpret_cast<VtableAddress>(FUN_00526870),
    reinterpret_cast<VtableAddress>(FUN_00526c30), reinterpret_cast<VtableAddress>(FUN_00422c10),
};
static_assert(sizeof(VtableAddress) == 4 && sizeof(PTR_FUN_006bcc18) == 40 &&
              sizeof(PTR_FUN_006c18d8) == 40);
} // namespace shaiya::ui
