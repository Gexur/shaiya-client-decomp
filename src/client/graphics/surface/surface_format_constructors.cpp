#include "graphics/surface/surface_format_constructors.h"
#include "graphics/surface/surface_format_owner.h"
#include "graphics/surface/surface_format_tables.h"
extern "C" uint32_t __attribute__((thiscall)) FUN_005fa87f(void*, void*);
extern "C" uint32_t __attribute__((thiscall)) FUN_005faa99(void*, void*);
namespace {
void put(uint32_t p, uint32_t v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
} // namespace
// Original005f699e, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f699e(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x18u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df438));
    return self;
}
// Original005f69bf, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f69bf(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x20u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df448));
    return self;
}
// Original005f69e0, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f69e0(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x20u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df458));
    return self;
}
// Original005f6d1c, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f6d1c(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x10u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df468));
    return self;
}
// Original005f6d3d, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f6d3d(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x10u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df478));
    return self;
}
// Original005f6d5e, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f6d5e(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x10u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df488));
    return self;
}
// Original005f6d7f, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f6d7f(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x10u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df498));
    return self;
}
// Original005f6da0, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f6da0(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x8u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df4a8));
    return self;
}
// Original005f6dc1, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f6dc1(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x8u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df4b8));
    return self;
}
// Original005f6de2, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f6de2(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x10u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df4c8));
    return self;
}
// Original005f6e03, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f6e03(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x10u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df4d8));
    return self;
}
// Original005f713d, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f713d(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x20u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df4e8));
    return self;
}
// Original005f715e, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f715e(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x20u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df4f8));
    return self;
}
// Original005f717f, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f717f(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x20u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df508));
    return self;
}
// Original005f71a0, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f71a0(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x20u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df518));
    return self;
}
// Original005f71c1, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f71c1(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x20u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df528));
    return self;
}
// Original005f71e2, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f71e2(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x40u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df538));
    return self;
}
// Original005f7203, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7203(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x10u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df548));
    return self;
}
// Original005f75d0, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f75d0(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x8u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df558));
    return self;
}
// Original005f75f1, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f75f1(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x8u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df568));
    return self;
}
// Original005f7612, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7612(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x10u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df578));
    return self;
}
// Original005f7633, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7633(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x8u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df588));
    return self;
}
// Original005f7675, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7675(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x10u, 0x2u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df5a8));
    return self;
}
// Original005f7696, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7696(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x10u, 0x2u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df5b8));
    return self;
}
// Original005f76b7, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f76b7(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x20u, 0x2u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df5c8));
    return self;
}
// Original005f794f, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f794f(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x20u, 0x3u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df5dc));
    return self;
}
// Original005f7970, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7970(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x20u, 0x2u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df5ec));
    return self;
}
// Original005f7991, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7991(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x20u, 0x2u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df5fc));
    return self;
}
// Original005f7dce, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7dce(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x10u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df634));
    return self;
}
// Original005f7654, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7654(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x10u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df598));
    return self;
}
// Original005f7def, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7def(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x20u, 0x4u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df644));
    return self;
}
// Original005f79b2, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f79b2(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x40u, 0x3u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df60c));
    return self;
}
// Original005f7e10, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7e10(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x10u, 0x4u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df654));
    return self;
}
// Original005f7e31, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7e31(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x20u, 0x4u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df664));
    return self;
}
// Original005f7e52, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7e52(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x40u, 0x4u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df674));
    return self;
}
// Original005f7e73, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7e73(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x20u, 0x4u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df684));
    return self;
}
// Original005f7e94, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7e94(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x40u, 0x4u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df694));
    return self;
}
// Original005f7eb5, complete36B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f7eb5(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x80u, 0x4u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df6a4));
    return self;
}
// Original005f79d3, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f79d3(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x10u, 0x2u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df61c));
    return self;
}
// Original005fb3a1, complete29B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb3a1(void* object, void* descriptor) {
    FUN_005faa99(object, descriptor);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df724));
    return self;
}
// Original005fb3be, complete29B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb3be(void* object, void* descriptor) {
    FUN_005faa99(object, descriptor);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df734));
    return self;
}
// Original005fb367, complete29B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb367(void* object, void* descriptor) {
    FUN_005fa87f(object, descriptor);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df704));
    return self;
}
// Original005fb3db, complete29B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb3db(void* object, void* descriptor) {
    FUN_005faa99(object, descriptor);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df744));
    return self;
}
// Original005fb3f8, complete29B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb3f8(void* object, void* descriptor) {
    FUN_005faa99(object, descriptor);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df754));
    return self;
}
// Original005fb415, complete29B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb415(void* object, void* descriptor) {
    FUN_005faa99(object, descriptor);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df764));
    return self;
}
// Original005f82ae, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f82ae(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x20u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df6b4));
    return self;
}
// Original005f82cf, complete33B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005f82cf(void* object, void* descriptor) {
    FUN_005f1e45(object, descriptor, 0x30u, 0x1u);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df6c4));
    return self;
}
// Original005fb34a, complete29B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb34a(void* object, void* descriptor) {
    FUN_005fa87f(object, descriptor);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df6f4));
    return self;
}
// Original005fb384, complete29B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb384(void* object, void* descriptor) {
    FUN_005fa87f(object, descriptor);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df714));
    return self;
}
// Original005fb32d, complete29B/RET4.
extern "C" uint32_t __attribute__((thiscall)) FUN_005fb32d(void* object, void* descriptor) {
    FUN_005fa87f(object, descriptor);
    const uint32_t self = reinterpret_cast<uintptr_t>(object);
    put(self, reinterpret_cast<uintptr_t>(dat_006df6e4));
    return self;
}
