#include "graphics/native_font.h"
#include "graphics/native_resources.h"
#include "runtime/allocations.h"
#include "startup/application.h"

using namespace shaiya::graphics::native;
extern "C" unsigned char dat_02209408[];

extern "C" LabelTexture* __attribute__((thiscall)) FUN_0054a770(void*, const char* text) {
    if (!text || !dat_02209400)
        return nullptr;
    int count = MultiByteToWideChar(CP_ACP, 0, text, -1, nullptr, 0);
    if (count <= 0)
        return nullptr;
    auto* wide = static_cast<WCHAR*>(HeapAlloc(GetProcessHeap(), 0, SIZE_T(count) * sizeof(WCHAR)));
    if (!wide)
        return nullptr;
    Texture2D* texture = nullptr;
    HRESULT status = E_FAIL;
    auto* font = *reinterpret_cast<NativeFont**>(dat_02209408 + 0x3a8);
    if (MultiByteToWideChar(CP_ACP, 0, text, -1, wide, count))
        status = outlined_text_texture(*dat_02209400, font, wide, count - 1, &texture);
    HeapFree(GetProcessHeap(), 0, wide);
    if (FAILED(status))
        return nullptr;
    auto* label = static_cast<LabelTexture*>(fun_005cc96d(sizeof(LabelTexture)));
    if (!label) {
        texture->release();
        return nullptr;
    }
    *label = {texture, texture->width, texture->height};
    return label;
}
extern "C" uint32_t native_ui_0054a4f0(const uint32_t* args) {
    auto* label = reinterpret_cast<const LabelTexture*>(args[0]);
    if (!label || !dat_02209400)
        return uint32_t(E_INVALIDARG);
    return uint32_t(draw_label_texture(*dat_02209400, *label, int32_t(args[1]), int32_t(args[2]),
                                       *reinterpret_cast<const float*>(args + 3), args[4]));
}
extern "C" __attribute__((naked)) void FUN_0054a4f0(void*, int, int, float, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _native_ui_0054a4f0\n\taddl $4,%esp\n\tretl $20");
}
