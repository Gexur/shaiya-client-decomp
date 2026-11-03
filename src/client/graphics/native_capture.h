#pragma once
#include "graphics/native_renderer.h"
namespace shaiya::graphics::native {
HRESULT capture_jpeg(NativeRenderer& renderer, const char* filename, float quality = .9f);
}
