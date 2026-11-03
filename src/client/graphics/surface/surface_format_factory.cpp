#include "graphics/surface/surface_format_factory.h"
#include "runtime/allocations.h"
extern "C" uint32_t __attribute__((thiscall)) FUN_005f699e(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f69bf(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f69e0(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f6d1c(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f6d3d(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f6d5e(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f6d7f(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f6da0(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f6dc1(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f6de2(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f6e03(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f713d(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f715e(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f717f(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f71a0(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f71c1(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f71e2(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7203(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f75d0(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f75f1(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7612(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7633(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7675(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7696(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f76b7(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f794f(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7970(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7991(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7dce(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7654(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7def(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f79b2(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7e10(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7e31(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7e52(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7e73(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7e94(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7eb5(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f79d3(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb3a1(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb3be(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb367(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb3db(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb3f8(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb415(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f82ae(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005f82cf(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb34a(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb384(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb32d(void*, void*);
extern "C" int32_t __attribute__((thiscall)) FUN_005f20b5(void*, void*);
namespace {
using u32 = uint32_t;
using Constructor = u32(__attribute__((thiscall)) *)(void*, void*);
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
u32 construct(Constructor code, u32 object, u32 descriptor) {
    u32 result = object;
    __asm__ volatile("pushl %3\n\tcalll *%2"
                     : "+a"(result), "+c"(object)
                     : "r"(code), "r"(descriptor)
                     : "edx", "memory", "cc");
    return result;
}
void deleting(u32 object) {
    u32 table = word(object);
    const u32 code = word(table);
    __asm__ volatile("pushl $1\n\tcalll *%2"
                     : "+a"(table), "+c"(object)
                     : "r"(code)
                     : "edx", "memory", "cc");
}
void finalize(u32 object) {
    u32 table = word(object);
    const u32 code = word(table + 12);
    __asm__ volatile("calll *%2" : "+a"(table), "+c"(object) : "r"(code) : "edx", "memory", "cc");
}
} // namespace
// Complete original5fb453..5fbbcf. Every branch keeps its actual allocation
// size and constructor; format-specific constructors/methods remain genuine
// external dependencies until their own instruction-derived recoveries exist.
extern "C" u32 __attribute__((stdcall)) FUN_005fb453(void* descriptor_pointer) {
    const u32 descriptor = reinterpret_cast<uintptr_t>(descriptor_pointer);
    const u32 format = word(descriptor + 4);
    u32 size;
    Constructor constructor;
    switch (format) {
    case 0x00000014u:
        size = 0x80;
        constructor = &FUN_005f699e;
        break;
    case 0x00000015u:
        size = 0x80;
        constructor = &FUN_005f69bf;
        break;
    case 0x00000016u:
        size = 0x80;
        constructor = &FUN_005f69e0;
        break;
    case 0x00000017u:
        size = 0x80;
        constructor = &FUN_005f6d1c;
        break;
    case 0x00000018u:
        size = 0x80;
        constructor = &FUN_005f6d3d;
        break;
    case 0x00000019u:
        size = 0x80;
        constructor = &FUN_005f6d5e;
        break;
    case 0x0000001au:
        size = 0x80;
        constructor = &FUN_005f6d7f;
        break;
    case 0x0000001bu:
        size = 0x80;
        constructor = &FUN_005f6da0;
        break;
    case 0x0000001cu:
        size = 0x80;
        constructor = &FUN_005f6dc1;
        break;
    case 0x0000001du:
        size = 0x80;
        constructor = &FUN_005f6de2;
        break;
    case 0x0000001eu:
        size = 0x80;
        constructor = &FUN_005f6e03;
        break;
    case 0x0000001fu:
        size = 0x80;
        constructor = &FUN_005f713d;
        break;
    case 0x00000020u:
        size = 0x80;
        constructor = &FUN_005f715e;
        break;
    case 0x00000021u:
        size = 0x80;
        constructor = &FUN_005f717f;
        break;
    case 0x00000022u:
        size = 0x80;
        constructor = &FUN_005f71a0;
        break;
    case 0x00000023u:
        size = 0x80;
        constructor = &FUN_005f71c1;
        break;
    case 0x00000024u:
        size = 0x80;
        constructor = &FUN_005f71e2;
        break;
    case 0x00000028u:
        size = 0x80;
        constructor = &FUN_005f7203;
        break;
    case 0x00000029u:
        size = 0x80;
        constructor = &FUN_005f75d0;
        break;
    case 0x00000032u:
        size = 0x80;
        constructor = &FUN_005f75f1;
        break;
    case 0x00000033u:
        size = 0x80;
        constructor = &FUN_005f7612;
        break;
    case 0x00000034u:
        size = 0x80;
        constructor = &FUN_005f7633;
        break;
    case 0x0000003cu:
        size = 0x80;
        constructor = &FUN_005f7675;
        break;
    case 0x0000003du:
        size = 0x80;
        constructor = &FUN_005f7696;
        break;
    case 0x0000003eu:
        size = 0x80;
        constructor = &FUN_005f76b7;
        break;
    case 0x0000003fu:
        size = 0x80;
        constructor = &FUN_005f794f;
        break;
    case 0x00000040u:
        size = 0x80;
        constructor = &FUN_005f7970;
        break;
    case 0x00000043u:
        size = 0x80;
        constructor = &FUN_005f7991;
        break;
    case 0x00000046u:
        size = 0x80;
        constructor = &FUN_005f7dce;
        break;
    case 0x00000051u:
        size = 0x80;
        constructor = &FUN_005f7654;
        break;
    case 0x00000052u:
        size = 0x80;
        constructor = &FUN_005f7def;
        break;
    case 0x0000006eu:
        size = 0x80;
        constructor = &FUN_005f79b2;
        break;
    case 0x0000006fu:
        size = 0x80;
        constructor = &FUN_005f7e10;
        break;
    case 0x00000070u:
        size = 0x80;
        constructor = &FUN_005f7e31;
        break;
    case 0x00000071u:
        size = 0x80;
        constructor = &FUN_005f7e52;
        break;
    case 0x00000072u:
        size = 0x80;
        constructor = &FUN_005f7e73;
        break;
    case 0x00000073u:
        size = 0x80;
        constructor = &FUN_005f7e94;
        break;
    case 0x00000074u:
        size = 0x80;
        constructor = &FUN_005f7eb5;
        break;
    case 0x00000075u:
        size = 0x80;
        constructor = &FUN_005f79d3;
        break;
    case 0x31545844u:
        size = 0x100;
        constructor = &FUN_005fb3a1;
        break;
    case 0x32545844u:
        size = 0x100;
        constructor = &FUN_005fb3be;
        break;
    case 0x32595559u:
        size = 0xb0;
        constructor = &FUN_005fb367;
        break;
    case 0x33545844u:
        size = 0x100;
        constructor = &FUN_005fb3db;
        break;
    case 0x34545844u:
        size = 0x100;
        constructor = &FUN_005fb3f8;
        break;
    case 0x35545844u:
        size = 0x100;
        constructor = &FUN_005fb415;
        break;
    case 0x36314c41u:
        size = 0x80;
        constructor = &FUN_005f82ae;
        break;
    case 0x36315220u:
        size = 0x80;
        constructor = &FUN_005f82cf;
        break;
    case 0x42475247u:
        size = 0xb0;
        constructor = &FUN_005fb34a;
        break;
    case 0x47424752u:
        size = 0xb0;
        constructor = &FUN_005fb384;
        break;
    case 0x59565955u:
        size = 0xb0;
        constructor = &FUN_005fb32d;
        break;
    default:
        return 0;
    }
    const u32 allocation = reinterpret_cast<uintptr_t>(fun_005cc96d(size));
    if (!allocation)
        return 0;
    const u32 object = construct(constructor, allocation, descriptor);
    if (!object)
        return 0;
    if (word(object + 0x1c)) {
        const int32_t status =
            FUN_005f20b5(reinterpret_cast<void*>(object), reinterpret_cast<void*>(descriptor));
        if (status < 0) {
            deleting(object);
            return 0;
        }
    }
    if (word(object + 0x18))
        finalize(object);
    return object;
}
