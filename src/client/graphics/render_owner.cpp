#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "graphics/render_owner.h"
#include "graphics/render_scale_dispatch.h"
#include "graphics/render_resource4.h"
#include "graphics/native_renderer.h"
#include "graphics/native_resources.h"
#include "graphics/native_font.h"
#include "runtime/allocations.h"
extern "C" {
extern HWND dat_00719a3c;
}
namespace {
using u32 = uint32_t;
u32 read(const void* self, u32 offset) {
    u32 v;
    const auto* p = static_cast<const unsigned char*>(self) + offset;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void write(void* self, u32 offset, u32 value) {
    auto* p = static_cast<unsigned char*>(self) + offset;
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(value) : "memory");
}
} // namespace
// Original5435d0..543864, RET0/EAX=self. Order and widths are evidenced stores.
extern "C" void* __attribute__((thiscall)) FUN_005435d0(void* self) {
    for (u32 offset :
         (const u32[]){0x38u, 0x34u, 0x30u, 0x2cu, 0x24u, 0x20u, 0x1cu, 0x18u, 0x10u, 0xcu, 8u, 4u})
        write(self, offset, 0);
    for (u32 offset : (const u32[]){0x3cu, 0x28u, 0x14u, 0u})
        write(self, offset, 0x3f800000);
    (void)FUN_005e56bb(static_cast<unsigned char*>(self) + 0x1bc, 0x3f800000, 0x3f800000,
                       0x3f800000);
    write(self, 0xc0, 0);
    write(self, 0xc4, 0x3fc00000);
    write(self, 0xc8, 0xc0400000);
    write(self, 0xcc, 0);
    write(self, 0xd0, 0x3f333333);
    write(self, 0xd4, 0);
    write(self, 0xd8, 0);
    write(self, 0xdc, 0x3f800000);
    write(self, 0xe0, 0);
    write(self, 0xe4, 0);
    write(self, 0xe8, 0);
    write(self, 0xec, 0);
    write(self, 0xf0, 0x40a00000);
    write(self, 0xf4, 0);
    write(self, 0xf8, 0);
    for (u32 offset : (const u32[]){0x40cu, 0x404u, 0x408u, 0x33cu, 0x414u, 0x3acu, 0x3a8u, 0x39cu,
                                    0x3a0u, 0x3a4u, 0x358u, 0x35cu, 0x360u, 0x410u, 0x418u})
        write(self, offset, 0);
    for (u32 offset : (const u32[]){0x134u, 0x130u, 0x12cu, 0x128u, 0x120u, 0x11cu, 0x118u, 0x114u,
                                    0x10cu, 0x108u, 0x104u, 0x100u})
        write(self, offset, 0);
    for (u32 offset : (const u32[]){0x138u, 0x124u, 0x110u, 0xfcu})
        write(self, offset, 0x3f800000);
    for (u32 offset : (const u32[]){0x174u, 0x170u, 0x16cu, 0x168u, 0x160u, 0x15cu, 0x158u, 0x154u,
                                    0x14cu, 0x148u, 0x144u, 0x140u})
        write(self, offset, 0);
    for (u32 offset : (const u32[]){0x178u, 0x164u, 0x150u, 0x13cu})
        write(self, offset, 0x3f800000);
    for (u32 offset : (const u32[]){0x1b4u, 0x1b0u, 0x1acu, 0x1a8u, 0x1a0u, 0x19cu, 0x198u, 0x194u,
                                    0x18cu, 0x188u, 0x184u, 0x180u})
        write(self, offset, 0);
    for (u32 offset : (const u32[]){0x1b8u, 0x1a4u, 0x190u, 0x17cu})
        write(self, offset, 0x3f800000);
    write(self, 0x101c, 0);
    write(self, 0x1620, 0);
    write(self, 0x1624, 0xff000000);
    return self;
}
// Release typed native asset/font ownership, then the D3D11 renderer. These
// engine owner slots no longer contain D3D9 COM interfaces.
extern "C" u32 __attribute__((thiscall)) FUN_00543870(void* self) {
    using namespace shaiya::graphics::native;
    for (u32 offset : (const u32[]){0x358u, 0x35cu}) {
        auto* buffer = reinterpret_cast<Buffer*>(read(self, offset));
        if (buffer != nullptr)
            buffer->release();
        write(self, offset, 0);
    }
    const u32 member = read(self, 0x414);
    if (member != 0) {
        FUN_0054a480(reinterpret_cast<void*>(member));
        fun_005cc620(reinterpret_cast<void*>(member));
        write(self, 0x414, 0);
    }
    DeleteObject(reinterpret_cast<HGDIOBJ>(read(self, 0x3ac)));
    write(self, 0x3ac, 0);
    for (u32 offset : (const u32[]){0x3a8u, 0x39cu, 0x3a0u, 0x3a4u}) {
        release_font(reinterpret_cast<NativeFont*>(read(self, offset)));
        write(self, offset, 0);
    }
    auto* current = reinterpret_cast<NativeRenderer*>(read(self, 0x408));
    if (current != nullptr)
        current->shutdown();
    write(self, 0x408, 0);
    write(self, 0x404, 0);
    write(self, 0x360, 0);
    write(self, 0x101c, 0);
    return 0;
}
