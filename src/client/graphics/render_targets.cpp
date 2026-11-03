#include "graphics/render_targets.h"
#include "graphics/native_render_target.h"

namespace {
using namespace shaiya::graphics::native;
void** slot(void* self, UINT offset) {
    return reinterpret_cast<void**>(static_cast<unsigned char*>(self) + offset);
}
UINT create(void* self, UINT offset, UINT size, bool depth) {
    auto* current = renderer();
    Texture2D* texture = nullptr;
    TargetScope* scope = nullptr;
    HRESULT result = create_render_texture(*current, size, size, &texture);
    if (SUCCEEDED(result))
        result = create_target_scope(*current, size, size, depth, &scope);
    if (FAILED(result)) {
        if (texture != nullptr)
            texture->release();
        release_target_scope(scope);
        return 0;
    }
    release_target_scope(static_cast<TargetScope*>(*slot(self, offset)));
    auto* old_texture = static_cast<Texture2D*>(*slot(self, offset + 8));
    if (old_texture != nullptr)
        old_texture->release();
    *slot(self, offset) = scope;
    *slot(self, offset + 4) = texture->target; // Borrowed native RTV; texture owns it.
    *slot(self, offset + 8) = texture;
    return 1;
}
} // namespace
extern "C" uint32_t __attribute__((thiscall)) FUN_005481e0(void* self) {
    return create(self, 0x1408, 128, false);
}
extern "C" uint32_t __attribute__((thiscall)) FUN_00546260(void* self) {
    return create(self, 8, 64, true);
}
