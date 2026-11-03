#include "graphics/native_render_passes.h"
#include "graphics/native_resources.h"
#include "startup/application.h"
#include <stdint.h>
extern "C" int32_t dat_0070b910, dat_0070b914;
extern "C" unsigned char dat_00864e8c[];
namespace {
using namespace shaiya::graphics::native;
using u32 = uint32_t;
float number(const u32* argument) {
    return *reinterpret_cast<const float*>(argument);
}
u32 submit(void* object, u32 color, const float* p, u32 incoming) {
    auto* texture = *static_cast<Texture2D**>(object);
    if (!texture)
        return incoming;
    UiVertex vertices[4] = {{p[0], p[1], 1, 1, color, 0, 0},
                            {p[2], p[3], 1, 1, color, 1, 0},
                            {p[4], p[5], 1, 1, color, 1, 1},
                            {p[6], p[7], 1, 1, color, 0, 1}};
    UiDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = 4;
    draw.primitive = UiPrimitive::quad;
    draw.image = texture->view;
    return u32(draw_ui(*dat_02209400, draw));
}
u32 polygon(void* object, const u32* args, u32 color, u32 incoming) {
    float p[8];
    float x = float(int32_t(args[0])), y = float(int32_t(args[1]));
    for (UINT i = 0; i < 4; ++i) {
        p[i * 2] = x + number(args + 2 + i * 2) - 0.5f;
        p[i * 2 + 1] = y + number(args + 3 + i * 2) - 0.5f;
    }
    return submit(object, color, p, incoming);
}
} // namespace
extern "C" u32 native_ui_00549d00(void* object, const u32* args, u32 incoming) {
    return polygon(object, args, 0xffffffffu, incoming);
}
extern "C" u32 native_ui_00549e70(void* object, const u32* args, u32 incoming) {
    return polygon(object, args + 1, args[0], incoming);
}
extern "C" u32 native_ui_0054a120(void* object, const u32* args, u32 incoming) {
    float x = number(args), y = number(args + 1), r = x + number(args + 2),
          b = y + number(args + 3);
    float p[8] = {x - 0.5f, y - 0.5f, r - 0.5f, y - 0.5f, r - 0.5f, b - 0.5f, x - 0.5f, b - 0.5f};
    return submit(object, 0xffffffffu, p, incoming);
}

namespace {
u32 rectangle(Texture2D* image, const u32* args, float depth, const float* uv, u32 incoming,
              Depth depth_test = Depth::disabled) {
    if (!image)
        return incoming;
    float l = float(int32_t(args[0])) - 0.5f, t = float(int32_t(args[1])) - 0.5f;
    float r = float(int32_t(args[0] + args[2])) - 0.5f,
          b = float(int32_t(args[1] + args[3])) - 0.5f;
    UiVertex vertices[4] = {{l, t, depth, 1, 0xffffffffu, uv[0], uv[2]},
                            {r, t, depth, 1, 0xffffffffu, uv[1], uv[2]},
                            {r, b, depth, 1, 0xffffffffu, uv[1], uv[3]},
                            {l, b, depth, 1, 0xffffffffu, uv[0], uv[3]}};
    UiDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = 4;
    draw.primitive = UiPrimitive::quad;
    draw.image = image->view;
    draw.style.depth = depth_test;
    return u32(draw_ui(*dat_02209400, draw));
}
} // namespace
extern "C" u32 native_ui_005498b0(void* object, const u32* args, u32 incoming) {
    auto* image = *static_cast<Texture2D**>(object);
    if (!image)
        return incoming;
    float x = float(int32_t(args[0])), y = float(int32_t(args[1]));
    const auto* dimensions = static_cast<const float*>(object);
    float points[8] = {x - 0.5f,
                       y - 0.5f,
                       x + dimensions[2] - 0.5f,
                       y - 0.5f,
                       x + dimensions[2] - 0.5f,
                       y + dimensions[3] - 0.5f,
                       x - 0.5f,
                       y + dimensions[3] - 0.5f};
    UiVertex vertices[4];
    const float u[4] = {0, 1, 1, 0}, v[4] = {0, 0, 1, 1};
    for (UINT i = 0; i < 4; ++i)
        vertices[i] = {points[i * 2], points[i * 2 + 1], number(args + 2), 1, 0xffffffffu, u[i],
                       v[i]};
    UiDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = 4;
    draw.primitive = UiPrimitive::quad;
    draw.image = image->view;
    draw.style.depth = Depth::read;
    return u32(draw_ui(*dat_02209400, draw));
}
extern "C" u32 native_ui_0054a270(void* object, const u32* args, u32 incoming) {
    u32 dimensions[4] = {args[1], args[2], args[4], args[5]};
    float uv[4] = {number(args + 6), number(args + 7), number(args + 8), number(args + 9)};
    return rectangle(*static_cast<Texture2D**>(object), dimensions, number(args + 3), uv, incoming,
                     Depth::read);
}
extern "C" u32 dat_0085d3a4;
extern "C" u32 native_ui_004c56d0(void* object, const u32* args, u32 incoming) {
    if (!dat_0085d3a4)
        return dat_0085d3a4;
    auto* image = *reinterpret_cast<Texture2D**>(static_cast<unsigned char*>(object) + 0x2c);
    float uv[4] = {number(args + 4), number(args + 5), number(args + 6), number(args + 7)};
    return rectangle(image, args, 1.0f, uv, incoming);
}
extern "C" __attribute__((naked)) void __attribute__((thiscall)) FUN_005498b0(void*, int, int,
                                                                              float) {
    __asm__ volatile(
        "pushl %eax\n\tleal 8(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _native_ui_005498b0\n\taddl $12,%esp\n\tretl $12");
}
extern "C" __attribute__((naked)) void __attribute__((thiscall))
FUN_0054a270(void*, u32, int, int, float, int, int, float, float, float, float) {
    __asm__ volatile(
        "pushl %eax\n\tleal 8(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _native_ui_0054a270\n\taddl $12,%esp\n\tretl $40");
}
extern "C" __attribute__((naked)) void __attribute__((thiscall))
FUN_004c56d0(void*, int, int, int, int, float, float, float, float) {
    __asm__ volatile(
        "pushl %eax\n\tleal 8(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _native_ui_004c56d0\n\taddl $12,%esp\n\tretl $32");
}
extern "C" void __attribute__((thiscall)) FUN_00541d70(void*, int x, int y, int end) {
    int period = dat_0070b910 + dat_0070b914;
    if (period <= 0 || end <= x)
        return;
    int count = (end - x) / period + ((end - x) % period >= 3 ? 1 : 0);
    if (count <= 0)
        return;
    auto* vertices = static_cast<UiVertex*>(
        HeapAlloc(GetProcessHeap(), 0, SIZE_T(count) * 2 * sizeof(UiVertex)));
    if (!vertices)
        return;
    for (int i = 0; i < count; ++i) {
        int left = x + i * period, right = left + dat_0070b914;
        if (right > end)
            right = end;
        vertices[i * 2] = {float(left), float(y), 0, 1, 0xffc8c8beu, 0, 0};
        vertices[i * 2 + 1] = {float(right), float(y), 0, 1, 0xffc8c8beu, 0, 0};
    }
    UiDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = UINT(count) * 2;
    draw.primitive = UiPrimitive::lines;
    draw_ui(*dat_02209400, draw);
    HeapFree(GetProcessHeap(), 0, vertices);
}
extern "C" void __attribute__((thiscall)) FUN_00541e90(void*, int x, int y, int height) {
    UiVertex vertices[2] = {
        {float(x), float(y), 0, 1, 0xffffffffu, 0, 0},
        {float(x), float(int32_t(uint32_t(y) + uint32_t(height))), 0, 1, 0xffffffffu, 0, 0}};
    UiDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = 2;
    draw.primitive = UiPrimitive::lines;
    draw_ui(*dat_02209400, draw);
}
extern "C" __attribute__((naked)) void __attribute__((thiscall))
FUN_00549d00(void*, int, int, float, float, float, float, float, float, float, float) {
    __asm__ volatile(
        "pushl %eax\n\tleal 8(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _native_ui_00549d00\n\taddl $12,%esp\n\tretl $40");
}
extern "C" __attribute__((naked)) void __attribute__((thiscall))
FUN_00549e70(void*, u32, int, int, float, float, float, float, float, float, float, float) {
    __asm__ volatile(
        "pushl %eax\n\tleal 8(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _native_ui_00549e70\n\taddl $12,%esp\n\tretl $44");
}
extern "C" __attribute__((naked)) void __attribute__((thiscall)) FUN_0054a120(void*, float, float,
                                                                              float, float) {
    __asm__ volatile(
        "pushl %eax\n\tleal 8(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _native_ui_0054a120\n\taddl $12,%esp\n\tretl $16");
}

extern "C" void __cdecl FUN_004a2690(u32 color, int x, int y, int width, int height) {
    // The authored solid rectangle selects vertex color. Keep the image that
    // its original quad owner selected for the subsequent cooldown overlay.
    auto* image = *reinterpret_cast<Texture2D**>(&dat_00864e8c);
    if (!image)
        return;
    const float l = float(x) - 0.5f, t = float(y) - 0.5f;
    const float r = float(int32_t(u32(x) + u32(width))) - 0.5f;
    const float b = float(int32_t(u32(y) + u32(height))) - 0.5f;
    UiVertex vertices[4] = {{l, t, 1, 1, color, 0, 0},
                            {r, t, 1, 1, color, 1, 0},
                            {r, b, 1, 1, color, 1, 1},
                            {l, b, 1, 1, color, 0, 1}};
    UiDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = 4;
    draw.primitive = UiPrimitive::quad;
    draw_ui(*dat_02209400, draw);
    dat_02209400->set_ui_image(image->view);
}

extern "C" void __attribute__((thiscall)) FUN_00546360(void* object, int x, int y, int width,
                                                       int height) {
    auto* image = *reinterpret_cast<Texture2D**>(static_cast<unsigned char*>(object) + 0x10);
    const float l = float(x) - 0.5f, t = float(y) - 0.5f;
    const float r = float(int32_t(u32(x) + u32(width))) - 0.5f;
    const float b = float(int32_t(u32(y) + u32(height))) - 0.5f;
    UiDualVertex36 vertices[4] = {{l, t, 1, 1, 0xffffffffu, 0, 0, 0, 0},
                                  {r, t, 1, 1, 0xffffffffu, 1, 0, 1, 0},
                                  {r, b, 1, 1, 0xffffffffu, 1, 1, 1, 1},
                                  {l, b, 1, 1, 0xffffffffu, 0, 1, 0, 1}};
    UiDualDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = 4;
    draw.image = dat_02209400->ui_image;
    draw.mask = image ? image->view : nullptr;
    draw.use_mask_rgb = true;
    draw_ui_dual36(*dat_02209400, draw);
}
