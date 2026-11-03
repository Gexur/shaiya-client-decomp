#include "textured_quad.h"
#include "ordered_stores.h"
#include "graphics/native_render_passes.h"
#include "graphics/native_renderer.h"
#include "graphics/native_resources.h"
extern "C" shaiya::graphics::native::NativeRenderer* dat_02209400;

namespace {
using u32 = uint32_t;
using Device = shaiya::graphics::native::NativeRenderer;
using namespace shaiya::ui::ordered_detail;
struct Vertex {
    u32 x, y, z, rhw, color, u, v;
};
static_assert(sizeof(Vertex) == 0x1c);
Device* device() {
    u32 value;
    __asm__ volatile("movl %1,%0" : "=r"(value) : "m"(dat_02209400) : "memory");
    return reinterpret_cast<Device*>(value);
}
// Actual549ffd..54a0ef x87 expression order: x is first rounded to a
// DWORD float before adding width, while y remains extended before height.
// Width/height are FLD/FADD float operands, despite Ghidra's int-field hint.
// All stores are text x87 mnemonics and original numeric constants.
void coordinates(void* self, u32 x, u32 y, u32& left, u32& top, u32& right, u32& bottom) {
    static const float half = 0.5f;
    u32 rounded_x;
    const auto* width = static_cast<const unsigned char*>(self) + 8;
    const auto* height = static_cast<const unsigned char*>(self) + 12;
    __asm__ volatile(
        "fildl %[x]\n\t"
        "fsts %[rounded]\n\t"
        "fsubs %[half]\n\t"
        "fildl %[y]\n\t"
        "flds %[half]\n\t"
        "fsubr %%st(1),%%st\n\t"
        "flds %[rounded]\n\t"
        "fadds (%[width])\n\t"
        "fsubs %[half]\n\t"
        "fsts %[right]\n\t"
        "fxch %%st(1)\n\t"
        "fstps %[top]\n\t"
        "fstps %[right]\n\t"
        "fadds (%[height])\n\t"
        "fsubs %[half]\n\t"
        "fsts %[bottom]\n\t"
        "fxch %%st(1)\n\t"
        "fstps %[left]\n\t"
        "fstps %[bottom]\n\t"
        : [rounded] "=m"(rounded_x), [left] "=m"(left), [top] "=m"(top), [right] "=m"(right),
          [bottom] "=m"(bottom)
        : [x] "m"(x), [y] "m"(y), [half] "m"(half), [width] "r"(width), [height] "r"(height)
        : "st", "st(1)", "st(2)", "st(3)", "cc", "memory");
}
} // namespace

// Source-only normalized entry. incoming_eax records the otherwise untouched
// register result of the original null-texture branch.
extern "C" uint32_t recovered_00549ff0(void* self, u32 color, u32 x, u32 y, u32 incoming_eax) {
    const u32 texture = load32(self, 0);
    if (texture == 0)
        return incoming_eax;
    auto* current = device();
    u32 left, top, right, bottom;
    coordinates(self, x, y, left, top, right, bottom);
    constexpr u32 one = 0x3f800000u;
    const Vertex vertices[4] = {{left, top, one, one, color, 0, 0},
                                {right, top, one, one, color, one, 0},
                                {right, bottom, one, one, color, one, one},
                                {left, bottom, one, one, color, 0, one}};
    using namespace shaiya::graphics::native;
    if (!current)
        return UINT(E_INVALIDARG);
    const auto* image = reinterpret_cast<Texture2D*>(texture);
    UiDraw draw;
    draw.vertices = reinterpret_cast<const UiVertex*>(vertices);
    draw.vertex_count = 4;
    draw.primitive = UiPrimitive::quad;
    draw.image = image->view;
    return UINT(draw_ui(*current, draw));
}

extern "C" __attribute__((naked)) uint32_t __attribute__((thiscall))
FUN_00549ff0(void*, uint32_t, uint32_t, uint32_t) {
    __asm__ volatile("pushl %eax\n\t"
                     "pushl 16(%esp)\n\t"
                     "pushl 16(%esp)\n\t"
                     "pushl 16(%esp)\n\t"
                     "pushl %ecx\n\t"
                     "call _recovered_00549ff0\n\t"
                     "addl $20,%esp\n\t"
                     "retl $12\n\t");
}
