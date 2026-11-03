#include "quad_draw.h"
#include "graphics/native_render_passes.h"
#include "graphics/native_renderer.h"
#include "graphics/native_resources.h"
extern "C" shaiya::graphics::native::NativeRenderer* dat_02209400;

namespace {
using u32 = uint32_t;
using Device = shaiya::graphics::native::NativeRenderer;
struct Vertex {
    u32 x, y, z, rhw, color, u, v;
};
static_assert(sizeof(Vertex) == 28);
u32 word(const void* self, u32 offset) {
    u32 result;
    const auto* p = reinterpret_cast<const unsigned char*>(reinterpret_cast<u32>(self) + offset);
    __asm__ volatile("movl (%1),%0" : "=r"(result) : "r"(p) : "memory");
    return result;
}
// Exact549a7d..549b6c x87 arithmetic. The original FST rounds x before
// width is added, but retains integer y in extended precision for height.
// Width/height are actual float memory operands at+8/+c, not integer fields.
// The canonical device load remains between x's FSUB and its first FST.
Device* positions_00549a70(void* self, u32 x, u32 y, u32& left, u32& top, u32& right, u32& bottom) {
    static const float half = 0.5f;
    u32 rounded_x, current;
    __asm__ volatile(
        "fildl %[x]\n\t"
        "fsts %[rounded]\n\t"
        "fsubs %[half]\n\t"
        "movl %[device],%[current]\n\t"
        "fsts %[left]\n\t"
        "fildl %[y]\n\t"
        "flds %[half]\n\t"
        "fsubr %%st(1),%%st\n\t"
        "fsts %[top]\n\t"
        "flds %[rounded]\n\t"
        "fadds 8(%[self])\n\t"
        "fsubs %[half]\n\t"
        "fsts %[right]\n\t"
        "fxch %%st(1)\n\t"
        "fstps %[top]\n\t"
        "fstps %[right]\n\t"
        "fadds 12(%[self])\n\t"
        "fsubs %[half]\n\t"
        "fsts %[bottom]\n\t"
        "fxch %%st(1)\n\t"
        "fstps %[left]\n\t"
        "fstps %[bottom]\n\t"
        : [rounded] "=m"(rounded_x), [current] "=&r"(current), [left] "=m"(left), [top] "=m"(top),
          [right] "=m"(right), [bottom] "=m"(bottom)
        : [x] "m"(x), [y] "m"(y), [half] "m"(half), [self] "r"(self), [device] "m"(dat_02209400)
        : "st", "st(1)", "st(2)", "st(3)", "memory", "cc");
    return reinterpret_cast<Device*>(current);
}

// Actual549bad..549cae uses wrapped integer sums for right/bottom,
// unlike549a70's float width/height. No host floating-point routine is used.
Device* positions_00549ba0(u32 x, u32 y, u32 width, u32 height, u32& left, u32& top, u32& right,
                           u32& bottom) {
    static const float half = 0.5f;
    const u32 last_x = x + width, last_y = y + height;
    u32 current;
    __asm__ volatile("fildl %[x]\n\t"
                     "fsubs %[half]\n\t"
                     "fsts %[left]\n\t"
                     "fildl %[y]\n\t"
                     "fsubs %[half]\n\t"
                     "fsts %[top]\n\t"
                     "fildl %[last_x]\n\t"
                     "fsubs %[half]\n\t"
                     "fsts %[right]\n\t"
                     "fxch %%st(1)\n\t"
                     "fstps %[top]\n\t"
                     "fstps %[right]\n\t"
                     "fildl %[last_y]\n\t"
                     "fsubs %[half]\n\t"
                     "movl %[device],%[current]\n\t"
                     "fsts %[bottom]\n\t"
                     "fxch %%st(1)\n\t"
                     "fstps %[left]\n\t"
                     "fstps %[bottom]\n\t"
                     : [current] "=r"(current), [left] "=m"(left), [top] "=m"(top),
                       [right] "=m"(right), [bottom] "=m"(bottom)
                     : [x] "m"(x), [y] "m"(y), [last_x] "m"(last_x), [last_y] "m"(last_y),
                       [half] "m"(half), [device] "m"(dat_02209400)
                     : "st", "st(1)", "st(2)", "memory", "cc");
    return reinterpret_cast<Device*>(current);
}
u32 submit(Device* current, u32 texture, const Vertex* vertices) {
    using namespace shaiya::graphics::native;
    if (!current)
        return UINT(E_INVALIDARG);
    const auto* image = reinterpret_cast<Texture2D*>(texture);
    UiDraw draw;
    draw.vertices = reinterpret_cast<const UiVertex*>(vertices);
    draw.vertex_count = 4;
    draw.primitive = UiPrimitive::quad;
    draw.image = image->view;
    // Icon helpers encode atlas columns with wrapped, sometimes negative UVs.
    draw.style.sampling = Sampling::linear_wrap;
    return UINT(draw_ui(*current, draw));
}
} // namespace

extern "C" u32 recovered_00549a70(void* self, u32 x, u32 y, u32 incoming_eax) {
    const u32 texture = word(self, 0);
    if (texture == 0)
        return incoming_eax;
    u32 left, top, right, bottom;
    Device* current = positions_00549a70(self, x, y, left, top, right, bottom);
    constexpr u32 one = 0x3f800000u;
    const Vertex vertices[4] = {{left, top, one, one, 0xffffffffu, 0, 0},
                                {right, top, one, one, 0xffffffffu, one, 0},
                                {right, bottom, one, one, 0xffffffffu, one, one},
                                {left, bottom, one, one, 0xffffffffu, 0, one}};
    return submit(current, texture, vertices);
}
extern "C" u32 recovered_00549ba0(void* self, u32 color, u32 x, u32 y, u32 width, u32 height,
                                  u32 u0, u32 u1, u32 v0, u32 v1, u32 incoming_eax) {
    const u32 texture = word(self, 0);
    if (texture == 0)
        return incoming_eax;
    u32 left, top, right, bottom;
    Device* current = positions_00549ba0(x, y, width, height, left, top, right, bottom);
    constexpr u32 one = 0x3f800000u;
    const Vertex vertices[4] = {{left, top, one, one, color, u0, v0},
                                {right, top, one, one, color, u1, v0},
                                {right, bottom, one, one, color, u1, v1},
                                {left, bottom, one, one, color, u0, v1}};
    return submit(current, texture, vertices);
}

extern "C" u32 recovered_server_row_highlight(void* self, u32 color, u32 x, u32 y, u32 width,
                                              u32 height, u32, u32, u32, u32, u32 incoming_eax) {
    const u32 texture = word(self, 0);
    if (texture == 0)
        return incoming_eax;
    u32 left, top, right, bottom;
    Device* current = positions_00549ba0(x, y, width, height, left, top, right, bottom);
    if (!current)
        return UINT(E_INVALIDARG);
    constexpr u32 one = 0x3f800000u;
    const Vertex vertices[4] = {{left, top, one, one, color, 0, 0},
                                {right, top, one, one, color, one, 0},
                                {right, bottom, one, one, color, one, one},
                                {left, bottom, one, one, color, 0, one}};
    using namespace shaiya::graphics::native;
    UiDraw draw;
    draw.vertices = reinterpret_cast<const UiVertex*>(vertices);
    draw.vertex_count = 4;
    draw.primitive = UiPrimitive::quad;
    // The selected row uses authored vertex RGB and twice the square of its
    // alpha. Its panel atlas is bound by the caller but contributes no color.
    draw.style.tint.a = 2.0f * float(color >> 24) / 255.0f;
    draw.style.alpha_cutoff = 0;
    const u32 result = UINT(draw_ui(*current, draw));
    current->set_ui_image(reinterpret_cast<Texture2D*>(texture)->view);
    return result;
}

// Text-only ABI adapters preserve incomingEAX on the original null-resource
// branches. They implement no additional original procedures or algorithms.
extern "C" __attribute__((naked)) u32 __attribute__((thiscall)) FUN_00549a70(void*, u32, u32) {
    __asm__ volatile(
        "pushl %eax\n\tpushl 12(%esp)\n\tpushl 12(%esp)\n\tpushl %ecx\n\tcalll _recovered_00549a70\n\taddl $16,%esp\n\tretl $8");
}
extern "C" __attribute__((naked)) u32 __attribute__((thiscall))
FUN_00549ba0(void*, u32, u32, u32, u32, u32, u32, u32, u32, u32) {
    __asm__ volatile(
        "pushl %eax\n\tpushl 40(%esp)\n\tpushl 40(%esp)\n\tpushl 40(%esp)\n\tpushl 40(%esp)\n\tpushl 40(%esp)\n\tpushl 40(%esp)\n\tpushl 40(%esp)\n\tpushl 40(%esp)\n\tpushl 40(%esp)\n\tpushl %ecx\n\tcalll _recovered_00549ba0\n\taddl $44,%esp\n\tretl $36");
}

extern "C" __attribute__((naked)) u32 __attribute__((thiscall))
native_server_row_highlight(void*, u32, u32, u32, u32, u32, u32, u32, u32, u32) {
    __asm__ volatile(
        "pushl %eax\n\tpushl 40(%esp)\n\tpushl 40(%esp)\n\tpushl 40(%esp)\n\tpushl 40(%esp)\n\tpushl 40(%esp)\n\tpushl 40(%esp)\n\tpushl 40(%esp)\n\tpushl 40(%esp)\n\tpushl 40(%esp)\n\tpushl %ecx\n\tcalll _recovered_server_row_highlight\n\taddl $44,%esp\n\tretl $36");
}
