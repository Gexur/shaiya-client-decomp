#include "graphics/native_render_target.h"
#include "graphics/native_water_draw.h"
extern "C" HRESULT __attribute__((stdcall))
native_portrait_preserve_state(shaiya::graphics::native::TargetScope*);

extern "C" void __attribute__((stdcall)) native_capture_water_reflection(void* owner) {
    shaiya::graphics::native::capture_water_reflection(owner);
}
extern "C" void __attribute__((stdcall)) native_capture_water_refraction(void* owner) {
    shaiya::graphics::native::capture_water_refraction(owner);
}

extern "C" HRESULT __attribute__((stdcall)) native_portrait_begin(void* owner) {
    using namespace shaiya::graphics::native;
    auto* bytes = static_cast<unsigned char*>(owner);
    auto* scope = *reinterpret_cast<TargetScope**>(bytes + 8);
    auto* texture = *reinterpret_cast<Texture2D**>(bytes + 0x10);
    if (!scope || !texture)
        return E_POINTER;
    const float transparent[4] = {};
    HRESULT result = begin_target(*scope, *texture, nullptr, transparent);
    if (FAILED(result))
        return result;
    result = native_portrait_preserve_state(scope);
    if (FAILED(result))
        end_target(*scope);
    return result;
}
