#include "graphics/native_renderer.h"
#include "graphics/native_scene_ports.h"
#include "core/quad_draw.h"
#include <mmsystem.h>
using namespace shaiya::graphics::native;
extern "C" {
extern unsigned char dat_02209408[];
extern UINT dat_007198d4, dat_008655bc;
extern const float dat_006c21a0;
extern float dat_00709cf4, dat_00709d00, dat_00709d0c, dat_00709d10, dat_00709d14, dat_00709d18;
void __attribute__((thiscall)) FUN_00542d40(void*);
void __attribute__((thiscall)) FUN_004b7ff0(void*);
void __cdecl FUN_005980b0();
void __cdecl FUN_005ceea8(UINT);
}
namespace {
template <class T> T& field(void* owner, UINT offset) {
    return *reinterpret_cast<T*>(static_cast<unsigned char*>(owner) + offset);
}
void draw_loading(void* owner) {
    auto& current = *renderer();
    if (!current.device)
        return;
    const float black[] = {0, 0, 0, 1};
    current.begin_frame(black);
    FUN_00542d40(dat_02209408);
    auto* bytes = static_cast<unsigned char*>(owner);
    FUN_00549a70(bytes + 0xc, 0, 0);
    const int progress = int(field<float>(owner, 0x4c) * dat_006c21a0),
              x = field<int>(owner, 0x65e8), y = field<int>(owner, 0x65ec);
    FUN_00549a70(bytes + 0x2c, UINT(x), UINT(y));
    const float fraction = float(progress) / dat_00709cf4;
    const UINT fraction_word = __builtin_bit_cast(UINT, fraction);
    FUN_00549ba0(bytes + 0x3c, 0xffffffff, UINT(int(float(x) + dat_00709d0c)),
                 UINT(int(float(y) + dat_00709d10)), UINT(progress), UINT(int(dat_00709d00)), 0,
                 fraction_word, 0, 0x3f800000);
    FUN_00549a70(bytes + 0x1c, UINT(int(float(x + progress) + dat_00709d14)),
                 UINT(int(float(y) + dat_00709d18)));
}
} // namespace
extern "C" void __attribute__((thiscall)) FUN_004b7d30(void* owner) {
    draw_loading(owner);
}
extern "C" UINT WINAPI FUN_004b8150(void*) __asm__("_FUN_004b8150");
extern "C" UINT WINAPI FUN_004b8150(void* owner) {
    if (owner) {
        while (!field<UINT>(owner, 4)) {
            Sleep(5000);
            if (field<UINT>(owner, 4))
                break;
            if (dat_007198d4) {
                FrameRenderScope serialization(*renderer());
                auto* lock = &field<CRITICAL_SECTION>(owner, 0x65f0);
                EnterCriticalSection(lock);
                draw_loading(owner);
                FUN_004b7ff0(owner);
                renderer()->present();
                LeaveCriticalSection(lock);
            }
            const DWORD now = timeGetTime();
            if (now - dat_008655bc > 120000) {
                dat_008655bc = now;
                FUN_005980b0();
            }
            MSG message;
            if (PeekMessageA(&message, nullptr, 0, 0, PM_NOREMOVE)) {
                if (!GetMessageA(&message, nullptr, 0, 0))
                    return UINT(message.wParam);
                TranslateMessage(&message);
                DispatchMessageA(&message);
            }
        }
        SetEvent(field<HANDLE>(owner, 8));
    }
    FUN_005ceea8(0);
    return 0;
}
extern "C" void __attribute__((thiscall)) FUN_004b82e0(void* owner, float progress) {
    auto& current = *renderer();
    FrameRenderScope serialization(current);
    const bool outer_frame_active = DWORD(InterlockedCompareExchange(&current.automatic_frame_owner,
                                                                     0, 0)) == GetCurrentThreadId();
    auto* lock = &field<CRITICAL_SECTION>(owner, 0x65f0);
    EnterCriticalSection(lock);
    field<float>(owner, 0x4c) = progress;
    draw_loading(owner);
    FUN_004b7ff0(owner);
    if (!outer_frame_active)
        current.present();
    LeaveCriticalSection(lock);
}
