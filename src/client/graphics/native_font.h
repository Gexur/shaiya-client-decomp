#pragma once

#include "graphics/native_renderer.h"
#include <stdint.h>

namespace shaiya::graphics::native {
struct NativeFont;
struct Texture2D;
struct LabelTexture {
    Texture2D* texture;
    UINT width, height;
};
struct FontOptions {
    int height = 12;
    UINT width = 0, weight = FW_NORMAL;
    bool italic = false;
    BYTE charset = DEFAULT_CHARSET;
    BYTE output_precision = OUT_DEFAULT_PRECIS;
    BYTE quality = ANTIALIASED_QUALITY;
    BYTE pitch_family = DEFAULT_PITCH;
    const char* face = "Arial";
};

HRESULT create_font(const FontOptions& options, NativeFont** font);
void release_font(NativeFont* font);
HDC font_dc(NativeFont* font);
SIZE measure_text(NativeFont* font, const WCHAR* text, int count = -1);
int draw_text(NativeRenderer& renderer, NativeFont* font, const WCHAR* text, int count,
              RECT& rectangle, UINT flags, uint32_t argb);
int draw_text_ansi(NativeRenderer& renderer, NativeFont* font, const char* text, int count,
                   RECT& rectangle, UINT flags, uint32_t argb, UINT codepage = CP_ACP);
HRESULT outlined_text_texture(NativeRenderer& renderer, NativeFont* font, const WCHAR* text,
                              int count, Texture2D** texture);
HRESULT draw_label_texture(NativeRenderer& renderer, const LabelTexture& label, int x, int y,
                           float depth, uint32_t argb);
} // namespace shaiya::graphics::native
