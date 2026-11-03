#include "panel_frame.h"
#include "startup/application.h"
#include "startup/game_init.h"
#include "startup/global_ownership.h"
#include "core/quad_draw.h"
#include "graphics/native_render_passes.h"
#include "graphics/native_renderer.h"

// Already recovered original quad bodies, with their private incomingEAX
// argument made explicit. These calls preserve null-resource residual returns
// without inventing an ordinary C++ ABI contract for the original register.
extern "C" uint32_t recovered_00549a70(void*, uint32_t, uint32_t, uint32_t);
extern "C" uint32_t recovered_00549ba0(void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                                       uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

namespace {
using u32 = uint32_t;

u32 word(const void* base, u32 offset) {
    u32 result;
    const auto* at = reinterpret_cast<const unsigned char*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movl (%1),%0" : "=r"(result) : "r"(at) : "memory");
    return result;
}
void put(void* base, u32 offset, u32 value) {
    auto* at = reinterpret_cast<unsigned char*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movl %1,(%0)" ::"r"(at), "r"(value) : "memory");
}
u32 quad(u32 color, u32 x, u32 y, u32 width, u32 height, u32 u0, u32 u1, u32 v0, u32 v1,
         u32 incoming) {
    return recovered_00549ba0(&dat_022032fc, color, x, y, width, height, u0, u1, v0, v1, incoming);
}
u32 fill(u32 color, u32 x, u32 y, u32 width, u32 height) {
    using namespace shaiya::graphics::native;
    UiImageScope preserve_image(*dat_02209400);
    const float l = float(int32_t(x)) - 0.5f, t = float(int32_t(y)) - 0.5f;
    const float r = float(int32_t(x + width)) - 0.5f, b = float(int32_t(y + height)) - 0.5f;
    UiVertex vertices[4] = {{l, t, 1, 1, color, 0, 0},
                            {r, t, 1, 1, color, 1, 0},
                            {r, b, 1, 1, color, 1, 1},
                            {l, b, 1, 1, color, 0, 1}};
    UiDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = 4;
    draw.primitive = UiPrimitive::quad;
    return u32(draw_ui(*dat_02209400, draw));
}
} // namespace

extern "C" u32 recovered_0050ff10(u32* arguments) {
    u32 result = word(arguments, 20);
    if (result != 0) {
        auto* callback =
            reinterpret_cast<shaiya::startup::CallbackObject_00405cc0*>(word(&dat_007191d4, 0));
        using Callback =
            u32(__attribute__((thiscall))*)(shaiya::startup::CallbackObject_00405cc0*, u32);
        auto function =
            reinterpret_cast<Callback>(word(reinterpret_cast<void*>(word(callback, 0)), 4));
        result = function(callback, 0x4e);
        if (uint8_t(result) != 0) {
            u32 y = word(arguments, 4);
            const u32 x = word(arguments, 0);
            result = recovered_00549a70(&dat_0220331c, x, y, result);
            const int32_t count = static_cast<int32_t>(word(arguments, 12)) / 15;
            result = static_cast<u32>(count);
            u32 repeats = 0;
            if (count > 0) {
                y += 8;
                repeats = static_cast<u32>(count);
                for (u32 remaining = repeats; remaining != 0; --remaining) {
                    result = recovered_00549a70(&dat_0220333c, x, y, result);
                    y += 15;
                }
                y = word(arguments, 4);
            }
            return recovered_00549a70(&dat_0220332c, x, repeats * 15 + y + 8, result);
        }
    }
    const u32 y = word(arguments, 4), x = word(arguments, 0);
    constexpr u32 quarter = 0x3e800000u, half = 0x3f000000u, three_quarters = 0x3f400000u,
                  one = 0x3f800000u;
    result = quad(0xffffffffu, x, y, 4, 4, 0, quarter, 0, quarter, result);
    const u32 width = word(arguments, 8), middle_x = x + 4;
    result = quad(0xffffffffu, middle_x, y, width, 4, quarter, half, 0, quarter, result);
    const u32 right_x = x + width + 4;
    put(arguments, 20, right_x);
    result = quad(0xffffffffu, right_x, y, 4, 4, half, three_quarters, 0, quarter, right_x);
    const u32 left_height = word(arguments, 12) + 4;
    result = quad(0xffffffffu, x, y + 4, 4, left_height, quarter, half, quarter, half, left_height);
    const u32 right_height = word(arguments, 12) + 4, right_edge = word(arguments, 20);
    result = quad(0xffffffffu, right_edge, y + 4, 4, right_height, three_quarters, one, quarter,
                  half, y + 4);
    const u32 middle_height = word(arguments, 12) + 4, color = word(arguments, 16);
    result = fill(color, middle_x, y + 4, width, middle_height);
    const u32 height = word(arguments, 12), bottom = y + height + 8;
    result = quad(0xffffffffu, x, bottom, 4, 4, 0, quarter, quarter, half, height);
    result = quad(0xffffffffu, middle_x, bottom, width, 4, three_quarters, one, 0, quarter, result);
    const u32 last_right = word(arguments, 20);
    return quad(0xffffffffu, last_right, bottom, 4, 4, half, three_quarters, quarter, half, result);
}

// Original50ff10's mutable incoming argument backing remains observable. Only
// this entry bridge is Assembly; all original branch/loop/draw control is C++.
extern "C" __attribute__((naked)) u32 FUN_0050ff10(u32, u32, u32, u32, u32, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0050ff10\n\taddl $4,%esp\n\tretl");
}
