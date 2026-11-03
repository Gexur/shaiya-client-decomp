#pragma once
#include "ui/constructors.hpp"
using OriginalOwner112 = shaiya::ui::Object_0052d480;
using OriginalOwner112Fields = shaiya::ui::Fields_0052d480_04c;
namespace owner112_detail {
inline void store32(void* object, unsigned offset, unsigned value) {
    auto* at = static_cast<unsigned char*>(object) + offset;
    __asm__ __volatile__("movl %1,(%0)" ::"r"(at), "r"(value) : "memory");
}
inline void store8(void* object, unsigned offset, unsigned char value) {
    auto* at = static_cast<unsigned char*>(object) + offset;
    __asm__ __volatile__("movb %1,(%0)" ::"r"(at), "q"(value) : "memory");
}
} // namespace owner112_detail
namespace shaiya::ui {
extern "C" {
void __attribute__((thiscall)) FUN_004ce800(OriginalOwner112Fields*);
void __attribute__((thiscall)) FUN_00447020(OriginalOwner112Fields*);
void __attribute__((thiscall)) FUN_0052d2f0(OriginalOwner112*);
void __attribute__((thiscall)) FUN_0052d500(OriginalOwner112*);
OriginalOwner112* __attribute__((thiscall)) FUN_0052d550(OriginalOwner112*, u32);
}
} // namespace shaiya::ui
extern "C" {
extern OriginalOwner112 dat_00865170, dat_008651e0;
void fun_006b6180();
void fun_006b61a0();
void fun_006b8a00();
void fun_006b8a10();
}
