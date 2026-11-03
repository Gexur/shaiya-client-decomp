#include "graphics/native_font.h"
#include "graphics/native_render_passes.h"
#include "graphics/native_resources.h"
#include "graphics/native_render_target.h"
#include <new>

namespace shaiya::graphics::native {
namespace {
constexpr UINT atlas_size = 1024;
using Analyse = HRESULT(WINAPI*)(HDC, const void*, int, int, int, DWORD, int, const void*,
                                 const void*, const int*, const void*, const BYTE*, void**);
using AnalysisSize = const SIZE*(WINAPI*)(void*);
using AnalysisOut = HRESULT(WINAPI*)(void*, int, int, UINT, const RECT*, int, int, BOOL);
using AnalysisFree = HRESULT(WINAPI*)(void**);
using AnalysisPosition = HRESULT(WINAPI*)(void*, int, BOOL, int*);
void* allocate(SIZE_T size) {
    return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
}
void dispose(void* value) {
    if (value)
        HeapFree(GetProcessHeap(), 0, value);
}
struct Atlas {
    Texture2D* image = nullptr;
    UINT x = 1, y = 1, row_height = 0;
};
struct Run {
    Run* next = nullptr;
    Texture2D* image = nullptr;
    WCHAR* text = nullptr;
    int count = 0, advance = 0;
    UINT x = 0, y = 0, width = 0, height = 0;
    bool dedicated = false;
};
int text_length(const WCHAR* text, int count) {
    if (!text)
        return 0;
    if (count < 0) {
        count = 0;
        while (count < 32767 && text[count])
            ++count;
    }
    return count > 32767 ? 32767 : count;
}
bool same_text(const Run& run, const WCHAR* text, int count) {
    if (run.count != count)
        return false;
    for (int i = 0; i < count; ++i)
        if (run.text[i] != text[i])
            return false;
    return true;
}
} // namespace

struct NativeFont {
    HDC dc = nullptr;
    HFONT font = nullptr;
    HGDIOBJ previous_font = nullptr;
    HMODULE uniscribe = nullptr;
    Analyse analyse = nullptr;
    AnalysisSize size = nullptr;
    AnalysisOut out = nullptr;
    AnalysisFree free = nullptr;
    AnalysisPosition position = nullptr;
    int line_height = 0;
    Atlas pages[4];
    UINT page_count = 0, run_count = 0;
    Run* runs = nullptr;
};

namespace {
void clear_runs(NativeFont& font) {
    while (font.runs) {
        Run* run = font.runs;
        font.runs = run->next;
        if (run->dedicated)
            run->image->release();
        dispose(run->text);
        dispose(run);
    }
    for (UINT i = 0; i < font.page_count; ++i) {
        font.pages[i].image->release();
        font.pages[i] = Atlas{};
    }
    font.page_count = font.run_count = 0;
}
HRESULT shape(NativeFont& font, const WCHAR* text, int count, void** analysis) {
    *analysis = nullptr;
    return font.analyse(font.dc, text, count, count * 3 / 2 + 16, -1, 0x10a0, 0, nullptr, nullptr,
                        nullptr, nullptr, nullptr, analysis);
}
SIZE line_size(NativeFont& font, const WCHAR* text, int count) {
    SIZE result = {0, font.line_height};
    if (!count)
        return result;
    for (Run* run = font.runs; run; run = run->next)
        if (same_text(*run, text, count)) {
            result.cx = run->advance;
            return result;
        }
    void* analysis = nullptr;
    if (SUCCEEDED(shape(font, text, count, &analysis))) {
        if (const SIZE* value = font.size(analysis))
            result.cx = value->cx;
    } else
        GetTextExtentPoint32W(font.dc, text, count, &result);
    if (analysis)
        font.free(&analysis);
    return result;
}
HRESULT empty_texture(NativeRenderer& renderer, UINT width, UINT height, Texture2D** result) {
    SIZE_T bytes = SIZE_T(width) * height * 4;
    void* blank = allocate(bytes);
    if (!blank)
        return E_OUTOFMEMORY;
    TextureMip mip = {blank, width * 4, UINT(bytes)};
    HRESULT status = create_texture(renderer, width, height, DXGI_FORMAT_B8G8R8A8_UNORM, &mip, 1,
                                    D3D11_BIND_SHADER_RESOURCE, result);
    dispose(blank);
    return status;
}
HRESULT raster(NativeFont& font, const WCHAR* text, int count, UINT width, UINT height,
               unsigned char** pixels) {
    *pixels = nullptr;
    BITMAPINFO info = {};
    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biWidth = LONG(width);
    info.bmiHeader.biHeight = -LONG(height);
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;
    void* dib_pixels = nullptr;
    HBITMAP bitmap = CreateDIBSection(font.dc, &info, DIB_RGB_COLORS, &dib_pixels, nullptr, 0);
    if (!bitmap)
        return E_FAIL;
    HGDIOBJ previous = SelectObject(font.dc, bitmap);
    SIZE_T bytes = SIZE_T(width) * height * 4;
    auto* dib = static_cast<unsigned char*>(dib_pixels);
    for (SIZE_T i = 0; i < bytes; ++i)
        dib[i] = 0;
    void* analysis = nullptr;
    HRESULT status = shape(font, text, count, &analysis);
    if (SUCCEEDED(status)) {
        bool ascii = true;
        for (int i = 0; i < count; ++i)
            if (text[i] < 0x20 || text[i] > 0x7e)
                ascii = false;
        if (ascii)
            for (int i = 0; i < count; ++i) {
                int pen = 0;
                WORD glyph = 0;
                ABC abc = {};
                status = font.position(analysis, i, FALSE, &pen);
                if (FAILED(status) ||
                    GetGlyphIndicesW(font.dc, text + i, 1, &glyph, 1) == GDI_ERROR ||
                    !GetCharABCWidthsI(font.dc, 0, 1, &glyph, &abc)) {
                    status = E_FAIL;
                    break;
                }
                int cell = abc.abcA + int(abc.abcB);
                if (cell > 0) {
                    RECT clip = {pen + 1, 1, pen + 1 + cell, LONG(height)};
                    if (!ExtTextOutW(font.dc, pen + 1, 1, ETO_GLYPH_INDEX | ETO_CLIPPED, &clip,
                                     reinterpret_cast<const WCHAR*>(&glyph), 1, nullptr)) {
                        status = E_FAIL;
                        break;
                    }
                }
            }
        else
            status = font.out(analysis, 1, 1, 0, nullptr, 0, 0, FALSE);
    }
    GdiFlush();
    if (SUCCEEDED(status)) {
        auto* output = static_cast<unsigned char*>(allocate(bytes));
        if (!output)
            status = E_OUTOFMEMORY;
        else {
            for (SIZE_T i = 0; i < bytes; i += 4) {
                output[i] = output[i + 1] = output[i + 2] = 255;
                output[i + 3] = dib[i];
            }
            *pixels = output;
        }
    }
    if (analysis)
        font.free(&analysis);
    SelectObject(font.dc, previous);
    DeleteObject(bitmap);
    return status;
}
Run* cached_run(NativeRenderer& renderer, NativeFont& font, const WCHAR* text, int count) {
    for (Run* run = font.runs; run; run = run->next)
        if (same_text(*run, text, count))
            return run;
    if (font.run_count >= 1024)
        clear_runs(font);
    SIZE measured = line_size(font, text, count);
    UINT width = UINT(measured.cx > 0 ? measured.cx : 1) + 4, height = UINT(font.line_height) + 2;
    if (width > 16384 || height >= atlas_size - 2)
        return nullptr;
    void* memory = allocate(sizeof(Run));
    if (!memory)
        return nullptr;
    auto* run = new (memory) Run{};
    run->text = static_cast<WCHAR*>(allocate(SIZE_T(count) * sizeof(WCHAR)));
    if (!run->text) {
        dispose(run);
        return nullptr;
    }
    for (int i = 0; i < count; ++i)
        run->text[i] = text[i];
    run->count = count;
    run->advance = measured.cx;
    run->width = width;
    run->height = height;
    run->dedicated = width >= atlas_size - 2;
    HRESULT status = S_OK;
    if (run->dedicated)
        status = empty_texture(renderer, width, height, &run->image);
    else {
        Atlas* page = font.page_count ? &font.pages[font.page_count - 1] : nullptr;
        if (page && page->x + width >= atlas_size) {
            page->x = 1;
            page->y += page->row_height + 1;
            page->row_height = 0;
        }
        if (!page || page->y + height >= atlas_size) {
            if (font.page_count == 4)
                clear_runs(font);
            page = &font.pages[font.page_count];
            status = empty_texture(renderer, atlas_size, atlas_size, &page->image);
            if (SUCCEEDED(status))
                ++font.page_count;
        }
        if (SUCCEEDED(status)) {
            run->image = page->image;
            run->x = page->x;
            run->y = page->y;
            page->x += width + 1;
            if (page->row_height < height)
                page->row_height = height;
        }
    }
    unsigned char* pixels = nullptr;
    if (SUCCEEDED(status))
        status = raster(font, text, count, width, height, &pixels);
    if (SUCCEEDED(status)) {
        D3D11_BOX box = {run->x, run->y, 0, run->x + width, run->y + height, 1};
        renderer.context->UpdateSubresource(run->image->gpu, 0, &box, pixels, width * 4, 0);
        run->next = font.runs;
        font.runs = run;
        ++font.run_count;
    } else {
        if (run->dedicated && run->image)
            run->image->release();
        dispose(run->text);
        dispose(run);
        run = nullptr;
    }
    dispose(pixels);
    return run;
}
} // namespace
HRESULT create_font(const FontOptions& options, NativeFont** result) {
    if (!result || !options.height)
        return E_INVALIDARG;
    *result = nullptr;
    void* memory = allocate(sizeof(NativeFont));
    if (!memory)
        return E_OUTOFMEMORY;
    auto* font = new (memory) NativeFont{};
    font->uniscribe = LoadLibraryW(L"usp10.dll");
    if (font->uniscribe) {
        font->analyse =
            reinterpret_cast<Analyse>(GetProcAddress(font->uniscribe, "ScriptStringAnalyse"));
        font->size =
            reinterpret_cast<AnalysisSize>(GetProcAddress(font->uniscribe, "ScriptString_pSize"));
        font->out =
            reinterpret_cast<AnalysisOut>(GetProcAddress(font->uniscribe, "ScriptStringOut"));
        font->free =
            reinterpret_cast<AnalysisFree>(GetProcAddress(font->uniscribe, "ScriptStringFree"));
        font->position = reinterpret_cast<AnalysisPosition>(
            GetProcAddress(font->uniscribe, "ScriptStringCPtoX"));
    }
    if (!font->analyse || !font->size || !font->out || !font->free || !font->position) {
        release_font(font);
        return E_NOINTERFACE;
    }
    font->dc = CreateCompatibleDC(nullptr);
    font->font =
        CreateFontA(options.height, int(options.width), 0, 0, int(options.weight), options.italic,
                    0, 0, options.charset, options.output_precision, CLIP_DEFAULT_PRECIS,
                    options.quality, options.pitch_family, options.face);
    if (!font->dc || !font->font) {
        release_font(font);
        return E_FAIL;
    }
    font->previous_font = SelectObject(font->dc, font->font);
    TEXTMETRICW metrics = {};
    GetTextMetricsW(font->dc, &metrics);
    font->line_height = metrics.tmHeight;
    SetTextColor(font->dc, RGB(255, 255, 255));
    SetBkColor(font->dc, RGB(0, 0, 0));
    SetBkMode(font->dc, TRANSPARENT);
    SetTextAlign(font->dc, TA_LEFT | TA_TOP);
    *result = font;
    return S_OK;
}
void release_font(NativeFont* font) {
    if (!font)
        return;
    clear_runs(*font);
    if (font->dc && font->previous_font)
        SelectObject(font->dc, font->previous_font);
    if (font->font)
        DeleteObject(font->font);
    if (font->dc)
        DeleteDC(font->dc);
    if (font->uniscribe)
        FreeLibrary(font->uniscribe);
    dispose(font);
}
HDC font_dc(NativeFont* font) {
    return font ? font->dc : nullptr;
}
SIZE measure_text(NativeFont* font, const WCHAR* text, int count) {
    if (!font || !text)
        return {};
    count = text_length(text, count);
    SIZE result = {0, font->line_height};
    int start = 0;
    for (int i = 0; i <= count; ++i)
        if (i == count || text[i] == L'\n') {
            SIZE line = line_size(*font, text + start, i - start);
            if (result.cx < line.cx)
                result.cx = line.cx;
            if (i != count)
                result.cy += font->line_height;
            start = i + 1;
        }
    return result;
}
int draw_text(NativeRenderer& renderer, NativeFont* font, const WCHAR* text, int count,
              RECT& rectangle, UINT flags, uint32_t argb) {
    FrameRenderScope serialization(renderer);
    UiImageScope preserve_image(renderer);
    if (!font || !text)
        return 0;
    count = text_length(text, count);
    SIZE measured = measure_text(font, text, count);
    if (flags & DT_CALCRECT) {
        rectangle.right = rectangle.left + measured.cx;
        rectangle.bottom = rectangle.top + measured.cy;
        return measured.cy;
    }
    float y = float(rectangle.top);
    if (flags & DT_VCENTER)
        y += float(rectangle.bottom - rectangle.top - measured.cy) * 0.5f;
    else if (flags & DT_BOTTOM)
        y += float(rectangle.bottom - rectangle.top - measured.cy);
    int start = 0;
    for (int i = 0; i <= count; ++i)
        if (i == count || text[i] == L'\n') {
            int length = i - start;
            if (length && text[start + length - 1] == L'\r')
                --length;
            if (length) {
                Run* run = cached_run(renderer, *font, text + start, length);
                if (!run)
                    return 0;
                float x = float(rectangle.left);
                if (flags & DT_CENTER)
                    x += float(rectangle.right - rectangle.left - run->advance) * 0.5f;
                else if (flags & DT_RIGHT)
                    x += float(rectangle.right - rectangle.left - run->advance);
                float left = x - 1.5f, top = y - 1.5f, right = left + float(run->width),
                      bottom = top + float(run->height);
                float u0 = float(run->x) / float(run->image->width),
                      v0 = float(run->y) / float(run->image->height);
                float u1 = float(run->x + run->width) / float(run->image->width),
                      v1 = float(run->y + run->height) / float(run->image->height);
                UiVertex vertices[4] = {{left, top, 0, 1, argb, u0, v0},
                                        {right, top, 0, 1, argb, u1, v0},
                                        {right, bottom, 0, 1, argb, u1, v1},
                                        {left, bottom, 0, 1, argb, u0, v1}};
                UiDraw draw;
                draw.vertices = vertices;
                draw.vertex_count = 4;
                draw.primitive = UiPrimitive::quad;
                draw.image = run->image->view;
                draw.style.blend = Blend::alpha;
                draw.style.depth = Depth::disabled;
                draw.style.cull = Cull::none;
                draw.style.sampling = Sampling::point_clamp;
                draw.style.alpha_cutoff = 0;
                if (!(flags & DT_NOCLIP))
                    draw.scissor = &rectangle;
                if (FAILED(draw_ui(renderer, draw)))
                    return 0;
            }
            y += float(font->line_height);
            start = i + 1;
        }
    return measured.cy;
}
int draw_text_ansi(NativeRenderer& renderer, NativeFont* font, const char* text, int count,
                   RECT& rectangle, UINT flags, uint32_t argb, UINT codepage) {
    if (!text)
        return 0;
    int length = MultiByteToWideChar(codepage, 0, text, count, nullptr, 0);
    if (length <= 0)
        return 0;
    auto* wide = static_cast<WCHAR*>(allocate(SIZE_T(length) * sizeof(WCHAR)));
    if (!wide)
        return 0;
    int result = 0;
    if (MultiByteToWideChar(codepage, 0, text, count, wide, length))
        result = draw_text(renderer, font, wide, count < 0 ? length - 1 : length, rectangle, flags,
                           argb);
    dispose(wide);
    return result;
}
HRESULT outlined_text_texture(NativeRenderer& renderer, NativeFont* font, const WCHAR* text,
                              int count, Texture2D** result) {
    FrameRenderScope serialization(renderer);
    struct FontTargetClip {
        NativeRenderer& renderer;
        bool enabled;
        explicit FontTargetClip(NativeRenderer& value)
            : renderer(value), enabled(value.ui_scissor_enabled) {
            renderer.ui_scissor_enabled = false;
        }
        ~FontTargetClip() {
            renderer.ui_scissor_enabled = enabled;
        }
    } preserve_clip(renderer);
    if (!font || !text || !result)
        return E_INVALIDARG;
    *result = nullptr;
    count = text_length(text, count);
    struct Segment {
        int start, count;
    };
    Segment segments[3] = {{0, count}, {count, 0}, {count, 0}};
    int marker = -1;
    for (int i = 0; i + 1 < count; ++i)
        if (text[i] == L'<' && text[i + 1] == L'<') {
            marker = i;
            break;
        }
    if (marker >= 0 && count - marker >= 8 && text[marker + 5] == L'c') {
        int requested = 0, index = 0, sign = 1;
        while (index < 3 && text[marker + 2 + index] == L' ')
            ++index;
        if (index < 3 && (text[marker + 2 + index] == L'+' || text[marker + 2 + index] == L'-')) {
            sign = text[marker + 2 + index] == L'-' ? -1 : 1;
            ++index;
        }
        while (index < 3 && text[marker + 2 + index] >= L'0' && text[marker + 2 + index] <= L'9') {
            requested = requested * 10 + text[marker + 2 + index] - L'0';
            ++index;
        }
        requested *= sign;
        if (requested > 0) {
            int start = marker + 8, end = start + requested;
            if (end > count)
                end = count;
            segments[0] = {0, marker};
            segments[1] = {start, end - start};
            segments[2] = {end, count - end};
        }
    }
    UINT width = 2, height = UINT(font->line_height) + 2;
    for (const auto& segment : segments)
        width += UINT(line_size(*font, text + segment.start, segment.count).cx);
    if (width > 16384 || height > 16384)
        return E_INVALIDARG;
    Texture2D* target = nullptr;
    TargetScope* scope = nullptr;
    HRESULT status = create_texture(renderer, width, height, DXGI_FORMAT_B8G8R8A8_UNORM, nullptr, 1,
                                    D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE, &target);
    if (SUCCEEDED(status))
        status = create_target_scope(renderer, width, height, false, &scope);
    float blue[4] = {0, 0, 1, 1};
    if (SUCCEEDED(status))
        status = begin_target(*scope, *target, nullptr, blue);
    if (SUCCEEDED(status)) {
        int cursor = 0;
        const int dx[5] = {1, 1, 0, 2, 1}, dy[5] = {0, 2, 1, 1, 1};
        for (const auto& segment : segments) {
            if (segment.count) {
                for (int pass = 0; pass < 5; ++pass) {
                    RECT rect = {cursor + dx[pass], dy[pass], 0, 0};
                    if (!draw_text(renderer, font, text + segment.start, segment.count, rect,
                                   DT_NOCLIP, pass == 4 ? 0xffffffffu : 0xff000000u))
                        status = E_FAIL;
                }
                cursor += line_size(*font, text + segment.start, segment.count).cx;
            }
        }
        HRESULT restored = end_target(*scope);
        if (SUCCEEDED(status))
            status = restored;
    }
    ID3D11Texture2D* staging = nullptr;
    unsigned char* pixels = nullptr;
    if (SUCCEEDED(status)) {
        D3D11_TEXTURE2D_DESC desc = {};
        target->gpu->GetDesc(&desc);
        desc.BindFlags = 0;
        desc.MiscFlags = 0;
        desc.Usage = D3D11_USAGE_STAGING;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        status = renderer.device->CreateTexture2D(&desc, nullptr, &staging);
    }
    if (SUCCEEDED(status)) {
        renderer.context->CopyResource(staging, target->gpu);
        D3D11_MAPPED_SUBRESOURCE mapped = {};
        status = renderer.context->Map(staging, 0, D3D11_MAP_READ, 0, &mapped);
        if (SUCCEEDED(status)) {
            pixels = static_cast<unsigned char*>(allocate(SIZE_T(width) * height * 4));
            if (!pixels)
                status = E_OUTOFMEMORY;
            else
                for (UINT y = 0; y < height; ++y) {
                    const auto* row = reinterpret_cast<const uint32_t*>(
                        static_cast<const unsigned char*>(mapped.pData) +
                        SIZE_T(y) * mapped.RowPitch);
                    auto* output = reinterpret_cast<uint32_t*>(pixels + SIZE_T(y) * width * 4);
                    for (UINT x = 0; x < width; ++x) {
                        uint32_t value = row[x];
                        output[x] = ((value >> 16 & 255) < 128 && (value & 255) >= 128)
                                        ? 0
                                        : value | 0xff000000u;
                    }
                }
            renderer.context->Unmap(staging, 0);
        }
    }
    if (SUCCEEDED(status)) {
        TextureMip mip = {pixels, width * 4, width * height * 4};
        status = create_texture(renderer, width, height, DXGI_FORMAT_B8G8R8A8_UNORM, &mip, 1,
                                D3D11_BIND_SHADER_RESOURCE, result);
    }
    dispose(pixels);
    if (staging)
        staging->Release();
    if (scope)
        release_target_scope(scope);
    if (target)
        target->release();
    return status;
}
HRESULT draw_label_texture(NativeRenderer& renderer, const LabelTexture& label, int x, int y,
                           float depth, uint32_t argb) {
    if (!label.texture)
        return S_FALSE;
    float l = float(x) - 0.5f, t = float(y) - 0.5f, r = float(x + int(label.width)) - 0.5f,
          b = float(y + int(label.height)) - 0.5f;
    UiVertex vertices[4] = {{l, t, depth, 1, argb, 0, 0},
                            {r, t, depth, 1, argb, 1, 0},
                            {r, b, depth, 1, argb, 1, 1},
                            {l, b, depth, 1, argb, 0, 1}};
    UiDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = 4;
    draw.primitive = UiPrimitive::quad;
    draw.image = label.texture->view;
    draw.style.blend = Blend::opaque;
    draw.style.depth = Depth::write;
    draw.style.alpha_cutoff = 7.5f / 255.0f;
    return draw_ui(renderer, draw);
}
} // namespace shaiya::graphics::native

extern "C" int __attribute__((stdcall))
native_font_draw_ansi(shaiya::graphics::native::NativeFont* font, void*, const char* text,
                      int count, RECT* rectangle, UINT flags, uint32_t argb) {
    using namespace shaiya::graphics::native;
    return font && text && rectangle
               ? draw_text_ansi(*renderer(), font, text, count, *rectangle, flags, argb)
               : 0;
}
extern "C" int __attribute__((stdcall))
native_font_draw_wide(shaiya::graphics::native::NativeFont* font, void*, const WCHAR* text,
                      int count, RECT* rectangle, UINT flags, uint32_t argb) {
    using namespace shaiya::graphics::native;
    return font && text && rectangle
               ? draw_text(*renderer(), font, text, count, *rectangle, flags, argb)
               : 0;
}
