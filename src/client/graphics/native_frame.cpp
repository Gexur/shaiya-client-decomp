#include "graphics/native_renderer.h"
#include "graphics/native_font.h"
#include "graphics/native_scene_ports.h"
#include "startup/client_clock.h"
#include "startup/application.h"
#include "core/x87_runtime.h"

extern "C" {
extern float dat_0220aa40, dat_0220aa48;
extern uint32_t dat_0220aa44, dat_0070b8f0, dat_008655ec;
extern unsigned char* dat_0085cfbc;
extern uint16_t dat_008666c4;
int __cdecl sprintf(char*, const char*, ...);
void __attribute__((stdcall)) native_scene_depth_test(UINT);
void __attribute__((stdcall)) native_scene_depth_write(UINT);
void __attribute__((stdcall)) native_scene_blending(UINT);
void __attribute__((stdcall)) native_scene_alpha_test(UINT);
void __attribute__((stdcall)) native_scene_lighting(UINT);
void __cdecl native_scene_cull_back();
}

namespace {
using namespace shaiya::graphics::native;
uint32_t word(void* self, UINT offset) {
    return *reinterpret_cast<uint32_t*>(static_cast<unsigned char*>(self) + offset);
}
void debug_line(NativeRenderer& current, NativeFont* font, const char* text, int y, UINT color) {
    const int offsets[5][2] = {{0, 0}, {2, 0}, {0, 2}, {2, 2}, {1, 1}};
    for (UINT index = 0; index < 5; ++index) {
        RECT rectangle = {4 + offsets[index][0], y + offsets[index][1],
                          static_cast<LONG>(current.width), static_cast<LONG>(current.height)};
        draw_text_ansi(current, font, text, -1, rectangle, DT_NOCLIP | DT_NOPREFIX,
                       index == 4 ? color : 0xff000000);
    }
}
} // namespace

extern "C" uint32_t __attribute__((thiscall)) FUN_00541700(void* self) {
    auto* current = reinterpret_cast<NativeRenderer*>(word(self, 0x408));
    if (current == nullptr || current->device == nullptr || current->device_removed)
        return 0;
    const UINT argb = word(self, 0x1624);
    const float color[4] = {float((argb >> 16) & 255) / 255, float((argb >> 8) & 255) / 255,
                            float(argb & 255) / 255, float(argb >> 24) / 255};
    current->begin_frame(color);
    *reinterpret_cast<uint32_t*>(static_cast<unsigned char*>(self) + 0x40c) = 0;
    const HRESULT result = begin_scene(*current, current->scene);
    if (FAILED(result))
        current->finish_frame();
    return SUCCEEDED(result);
}

extern "C" void __attribute__((thiscall)) FUN_00542870(void* self) {
    auto* current = reinterpret_cast<NativeRenderer*>(word(self, 0x408));
    if (current == nullptr || current->device == nullptr)
        return;
    const long double now = FUN_00405840(4);
    ++dat_0220aa44;
    if (now - dat_0220aa48 > 1) {
        dat_0220aa40 = static_cast<float>(dat_0220aa44 / (now - dat_0220aa48));
        dat_0220aa48 = static_cast<float>(now);
        dat_0220aa44 = 0;
    }
    if (word(self, 0x410) != 0 && dat_0070b8f0 != 0) {
        auto* font = reinterpret_cast<NativeFont*>(word(self, 0x3a8));
        char line[256];
        sprintf(line, "%3.2f fps", static_cast<double>(dat_0220aa40));
        debug_line(*current, font, line, 4, 0xffffff00);
        if (dat_0085cfbc != nullptr) {
            const auto* position = reinterpret_cast<const float*>(dat_0085cfbc + 0x10);
            if (dat_008655ec != 0)
                sprintf(line, "Player x:%3.3f y:%3.3f z:%3.3f, Map:%d",
                        static_cast<double>(position[0]), static_cast<double>(position[1]),
                        static_cast<double>(position[2]), static_cast<unsigned>(dat_008666c4));
            else
                sprintf(line, "Player x:%3.3f y:%3.3f z:%3.3f", static_cast<double>(position[0]),
                        static_cast<double>(position[1]), static_cast<double>(position[2]));
            debug_line(*current, font, line, 22, 0xffffffff);
        }
    }
    current->present();
    if (current->device_removed)
        dat_00719a4c = 1;
}

extern "C" void __attribute__((thiscall)) FUN_00542d40(void*) {
    scene_draw_context().ui_depth = Depth::disabled;
    native_scene_depth_test(0);
    native_scene_depth_write(0);
    native_scene_blending(1);
    native_scene_alpha_test(0);
    native_scene_cull_back();
    native_scene_lighting(0);
    // UI descriptors select immutable native state. Refresh current viewport
    // and camera constants at this whole engine operation boundary.
    auto* current = renderer();
    if (current->device != nullptr)
        begin_scene(*current, current->scene);
}
extern "C" void __cdecl native_splash_begin() {
    auto* current = renderer();
    const float black[4] = {0, 0, 0, 1};
    current->begin_frame(black);
    begin_scene(*current, current->scene);
}
extern "C" void __cdecl native_splash_present() {
    renderer()->present();
}

extern "C" void __cdecl native_splash_begin_white() {
    auto* current = renderer();
    const float white[4] = {1, 1, 1, 1};
    current->begin_frame(white);
    begin_scene(*current, current->scene);
}

extern "C" void __cdecl native_splash_begin_transparent() {
    auto* current = renderer();
    const float transparent[4] = {0, 0, 0, 0};
    current->begin_frame(transparent);
    begin_scene(*current, current->scene);
}

extern "C" uint32_t __attribute__((thiscall)) FUN_00420d90(void* self, UINT direction,
                                                           float speed) {
    auto* words = static_cast<uint32_t*>(self);
    auto* values = static_cast<float*>(self);
    // Native UI owns its upload buffer; the fade stores CPU color animation.
    words[1] = 0;
    values[2] = speed;
    words[3] = direction;
    values[4] = values[5] = values[6] = 0;
    values[7] = direction == 0 ? 1.0f : 0.0f;
    dat_00719a50 = static_cast<float>(FUN_00405840(5));
    dat_00719a54 = static_cast<float>(FUN_00405840(6));
    return 1;
}

extern "C" void __attribute__((thiscall)) FUN_00420ef0(void* self) {
    auto* current = renderer();
    const auto* values = static_cast<const float*>(self);
    auto channel = [](float value) -> UINT {
        return value <= 0   ? 0
               : value >= 1 ? 255
                            : static_cast<UINT>(
                                  x87_to_integer_005cd414(static_cast<long double>(value) * 255));
    };
    const UINT argb = (channel(values[7]) << 24) | (channel(values[4]) << 16) |
                      (channel(values[5]) << 8) | channel(values[6]);
    const float right = static_cast<float>(current->width) - 0.5f;
    const float bottom = static_cast<float>(current->height) - 0.5f;
    const UiVertex vertices[4] = {{-0.5f, -0.5f, 1, 1, argb, 0, 0},
                                  {right, -0.5f, 1, 1, argb, 1, 0},
                                  {right, bottom, 1, 1, argb, 1, 1},
                                  {-0.5f, bottom, 1, 1, argb, 0, 1}};
    UiDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = 4;
    draw.primitive = UiPrimitive::quad;
    draw.style.alpha_cutoff = 0;
    const bool scissor = current->ui_scissor_enabled;
    current->ui_scissor_enabled = false;
    {
        UiImageScope image(*current);
        current->set_ui_image(nullptr);
        draw_ui(*current, draw);
    }
    current->ui_scissor_enabled = scissor;
}
