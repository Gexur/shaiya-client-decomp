// Typed original RTTI/throw metadata; no executable byte arrays.
#include "string_errors.h"

extern "C" {
OriginalRttiType<sizeof(".?AVexception@@")> dat_007085e0 = {{dat_006d5f18, nullptr},
                                                            ".?AVexception@@"};
OriginalRttiType<sizeof(".?AVlogic_error@std@@")> dat_007085f8 = {{dat_006d5f18, nullptr},
                                                                  ".?AVlogic_error@std@@"};
OriginalRttiType<sizeof(".?AVlength_error@std@@")> dat_00708618 = {{dat_006d5f18, nullptr},
                                                                   ".?AVlength_error@std@@"};
OriginalRttiType<sizeof(".?AVout_of_range@std@@")> dat_0070865c = {{dat_006d5f18, nullptr},
                                                                   ".?AVout_of_range@std@@"};
OriginalRttiType<sizeof(".?AVtype_info@@")> dat_0070e150 = {{dat_006d5f18, nullptr},
                                                            ".?AVtype_info@@"};
extern const OriginalRttiBase dat_006fa284 = {&dat_007085e0.prefix, 0, {0, -1, 0}, 0};
extern const OriginalRttiBase dat_006fa2c8 = {&dat_0070e150.prefix, 0, {0, -1, 0}, 0};
extern const OriginalRttiBase dat_006fa30c = {&dat_007085f8.prefix, 1, {0, -1, 0}, 0};
extern const OriginalRttiBase dat_006fa354 = {&dat_00708618.prefix, 2, {0, -1, 0}, 0};
extern const OriginalRttiBase dat_006fa3a0 = {&dat_0070865c.prefix, 2, {0, -1, 0}, 0};
const OriginalRttiBase* const dat_006fa29c[1] = {&dat_006fa284};
const OriginalRttiBase* const dat_006fa2e0[1] = {&dat_006fa2c8};
const OriginalRttiBase* const dat_006fa324[2] = {&dat_006fa30c, &dat_006fa284};
const OriginalRttiBase* const dat_006fa36c[3] = {&dat_006fa354, &dat_006fa30c, &dat_006fa284};
const OriginalRttiBase* const dat_006fa3b8[3] = {&dat_006fa3a0, &dat_006fa30c, &dat_006fa284};
extern const OriginalRttiHierarchy dat_006fa2a4 = {0, 0, 1, dat_006fa29c};
extern const OriginalRttiHierarchy dat_006fa2e8 = {0, 0, 1, dat_006fa2e0};
extern const OriginalRttiHierarchy dat_006fa330 = {0, 0, 2, dat_006fa324};
extern const OriginalRttiHierarchy dat_006fa37c = {0, 0, 3, dat_006fa36c};
extern const OriginalRttiHierarchy dat_006fa3c8 = {0, 0, 3, dat_006fa3b8};
extern const OriginalRttiLocator dat_006fa2b4 = {0, 0, 0, &dat_007085e0.prefix, &dat_006fa2a4};
extern const OriginalRttiLocator dat_006fa2f8 = {0, 0, 0, &dat_0070e150.prefix, &dat_006fa2e8};
extern const OriginalRttiLocator dat_006fa340 = {0, 0, 0, &dat_007085f8.prefix, &dat_006fa330};
extern const OriginalRttiLocator dat_006fa38c = {0, 0, 0, &dat_00708618.prefix, &dat_006fa37c};
extern const OriginalRttiLocator dat_006fa3d8 = {0, 0, 0, &dat_0070865c.prefix, &dat_006fa3c8};
extern const OriginalErrorVtableWithLocator dat_006d5ef4 = {&dat_006fa2b4,
                                                            {fun_005cdda2, fun_005cdd95}};
extern const OriginalErrorVtableWithLocator dat_006dbc70 = {&dat_006fa340,
                                                            {FUN_0040d230, FUN_0040abb0}};
extern const OriginalErrorVtableWithLocator dat_006dbc7c = {&dat_006fa38c,
                                                            {FUN_0040d230, FUN_0040abb0}};
extern const OriginalErrorVtableWithLocator dat_006dbc88 = {&dat_006fa3d8,
                                                            {FUN_0040d230, FUN_0040abb0}};
}

__asm__(".globl _dat_006d5ef8\n\t.set _dat_006d5ef8, _dat_006d5ef4+4\n\t");
__asm__(".globl _dat_006dbc74\n\t.set _dat_006dbc74, _dat_006dbc70+4\n\t");
__asm__(".globl _dat_006dbc80\n\t.set _dat_006dbc80, _dat_006dbc7c+4\n\t");
__asm__(".globl _dat_006dbc8c\n\t.set _dat_006dbc8c, _dat_006dbc88+4\n\t");

extern "C" {
extern const CxxCatchableType dat_006fa4c8 = {
    0, &dat_007085e0.prefix, {0, -1, 0}, 12, reinterpret_cast<void*>(fun_005cdd2d)};
extern const CxxCatchableType dat_006fa4e4 = {
    0, &dat_007085f8.prefix, {0, -1, 0}, 40, reinterpret_cast<void*>(FUN_0040b040)};
extern const CxxCatchableType dat_006fa500 = {
    0, &dat_00708618.prefix, {0, -1, 0}, 40, reinterpret_cast<void*>(FUN_0040b0b0)};
extern const CxxCatchableType dat_006fa6b0 = {
    0, &dat_0070865c.prefix, {0, -1, 0}, 40, reinterpret_cast<void*>(FUN_0040d830)};
struct OriginalCatchableArray3 {
    int32_t count;
    CxxCatchableType* entries[3];
};
extern const OriginalCatchableArray3 dat_006fa51c = {
    3,
    {const_cast<CxxCatchableType*>(&dat_006fa500), const_cast<CxxCatchableType*>(&dat_006fa4e4),
     const_cast<CxxCatchableType*>(&dat_006fa4c8)}};
extern const CxxThrowInfo dat_006fa52c = {
    0, reinterpret_cast<void*>(FUN_0040ab70), nullptr,
    reinterpret_cast<CxxCatchableTypes*>(const_cast<OriginalCatchableArray3*>(&dat_006fa51c))};
extern const OriginalCatchableArray3 dat_006fa6cc = {
    3,
    {const_cast<CxxCatchableType*>(&dat_006fa6b0), const_cast<CxxCatchableType*>(&dat_006fa4e4),
     const_cast<CxxCatchableType*>(&dat_006fa4c8)}};
extern const CxxThrowInfo dat_006fa6dc = {
    0, reinterpret_cast<void*>(FUN_0040ab70), nullptr,
    reinterpret_cast<CxxCatchableTypes*>(const_cast<OriginalCatchableArray3*>(&dat_006fa6cc))};
}
