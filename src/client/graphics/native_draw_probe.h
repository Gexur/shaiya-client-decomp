#pragma once

// Temporary opt-in diagnostic for a single native world frame. A request file
// is consumed only when SHAIYA_D3D11_DRAW_PROBE=1; ordinary draws never read GPU
// pixels or touch files. Only this render-pass translation unit includes it.
namespace shaiya::graphics::native {
namespace {
struct DrawProbe {
    int enabled = -1;
    bool active = false, complete = false;
    LONG checked_frame = -1, frame = -1;
    HANDLE file = INVALID_HANDLE_VALUE;
    ID3D11Texture2D* staging = nullptr;
    ID3D11Texture2D* full_staging = nullptr;
    UINT width = 0, height = 0, draws = 0, changes = 0;
    UINT sample_x[2] = {}, sample_y[2] = {}, capture = 0;
    bool images = false;
    UINT color[2] = {}, vertex = 0, pixel = 0, layout = 0;
    Matrix world;
    DrawStyle style;
    ID3D11ShaderResourceView *image = nullptr, *secondary = nullptr;
};
DrawProbe draw_probe;
void probe_write(const char* text, int size) {
    DWORD written;
    WriteFile(draw_probe.file, text, UINT(size), &written, nullptr);
}
void probe_close() {
    auto& probe = draw_probe;
    char text[128];
    int size = wsprintfA(text, "{\"event\":\"end\",\"draws\":%u,\"changes\":%u}\n", probe.draws,
                         probe.changes);
    probe_write(text, size);
    FlushFileBuffers(probe.file);
    CloseHandle(probe.file);
    probe.file = INVALID_HANDLE_VALUE;
    if (probe.staging)
        probe.staging->Release();
    probe.staging = nullptr;
    if (probe.full_staging)
        probe.full_staging->Release();
    probe.full_staging = nullptr;
    probe.active = false;
}
void probe_request_pixels() {
    auto& probe = draw_probe;
    probe.sample_x[0] = probe.width / 4;
    probe.sample_x[1] = probe.width * 3 / 4;
    probe.sample_y[0] = probe.sample_y[1] = probe.height / 2;
    probe.images = false;
    HANDLE request = CreateFileA("d3d11-draw-probe.request", GENERIC_READ, FILE_SHARE_READ, nullptr,
                                 OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (request == INVALID_HANDLE_VALUE)
        return;
    char text[128] = {};
    DWORD count = 0;
    ReadFile(request, text, 127, &count, nullptr);
    CloseHandle(request);
    UINT values[4] = {}, parsed = 0, at = 0;
    for (; parsed < 4; ++parsed) {
        while (at < count &&
               (text[at] == ' ' || text[at] == '\n' || text[at] == '\r' || text[at] == '\t'))
            ++at;
        if (at == count || text[at] < '0' || text[at] > '9')
            break;
        while (at < count && text[at] >= '0' && text[at] <= '9') {
            values[parsed] = values[parsed] * 10 + UINT(text[at++] - '0');
            if (values[parsed] > 65535)
                return;
        }
    }
    if (parsed == 4 && values[0] < probe.width && values[1] < probe.height &&
        values[2] < probe.width && values[3] < probe.height) {
        probe.sample_x[0] = values[0];
        probe.sample_y[0] = values[1];
        probe.sample_x[1] = values[2];
        probe.sample_y[1] = values[3];
    }
    while (at < count &&
           (text[at] == ' ' || text[at] == '\n' || text[at] == '\r' || text[at] == '\t'))
        ++at;
    probe.images = at < count && text[at] == 'i';
}
bool probe_image(NativeRenderer& renderer, char* filename) {
    auto& probe = draw_probe;
    if (!probe.images || probe.changes > 32)
        return false;
    if (!probe.full_staging) {
        D3D11_TEXTURE2D_DESC description = {};
        renderer.backbuffer->GetDesc(&description);
        if (description.Format != DXGI_FORMAT_B8G8R8A8_UNORM)
            return false;
        description.BindFlags = description.MiscFlags = 0;
        description.Usage = D3D11_USAGE_STAGING;
        description.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        if (FAILED(renderer.device->CreateTexture2D(&description, nullptr, &probe.full_staging)))
            return false;
    }
    renderer.context->CopyResource(probe.full_staging, renderer.backbuffer);
    D3D11_MAPPED_SUBRESOURCE mapped = {};
    if (FAILED(renderer.context->Map(probe.full_staging, 0, D3D11_MAP_READ, 0, &mapped)))
        return false;
    wsprintfA(filename, "d3d11-draw-probe-%02u-%04u.bmp", probe.capture, probe.draws);
    HANDLE file = CreateFileA(filename, GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        renderer.context->Unmap(probe.full_staging, 0);
        return false;
    }
    BITMAPFILEHEADER header = {};
    BITMAPINFOHEADER info = {};
    info.biSize = sizeof(info);
    info.biWidth = LONG(probe.width);
    info.biHeight = -LONG(probe.height);
    info.biPlanes = 1;
    info.biBitCount = 32;
    info.biSizeImage = probe.width * probe.height * 4;
    header.bfType = 0x4d42;
    header.bfOffBits = sizeof(header) + sizeof(info);
    header.bfSize = header.bfOffBits + info.biSizeImage;
    DWORD written;
    WriteFile(file, &header, sizeof(header), &written, nullptr);
    WriteFile(file, &info, sizeof(info), &written, nullptr);
    for (UINT row = 0; row < probe.height; ++row)
        WriteFile(file, static_cast<unsigned char*>(mapped.pData) + row * mapped.RowPitch,
                  probe.width * 4, &written, nullptr);
    CloseHandle(file);
    renderer.context->Unmap(probe.full_staging, 0);
    return true;
}
void probe_prepare(NativeRenderer& renderer, UINT vertex, UINT pixel, UINT layout,
                   const Matrix& world, const DrawStyle& style, ID3D11ShaderResourceView* image,
                   ID3D11ShaderResourceView* secondary) {
    auto& probe = draw_probe;
    if (probe.enabled < 0) {
        char option[8] = {};
        probe.enabled =
            GetEnvironmentVariableA("SHAIYA_D3D11_DRAW_PROBE", option, 8) > 0 && option[0] == '1';
    }
    if (!probe.enabled || probe.complete)
        return;
    const LONG frame = InterlockedCompareExchange(&renderer.presented_frames, 0, 0);
    if (probe.active && frame != probe.frame) {
        probe_close();
    }
    if (!probe.active && probe.checked_frame != frame) {
        probe.checked_frame = frame;
        if (GetFileAttributesA("d3d11-draw-probe.request") == INVALID_FILE_ATTRIBUTES)
            return;
        D3D11_TEXTURE2D_DESC description = {};
        renderer.backbuffer->GetDesc(&description);
        probe.width = description.Width;
        probe.height = description.Height;
        probe_request_pixels();
        description.Width = 2;
        description.Height = 1;
        description.MipLevels = description.ArraySize = 1;
        description.BindFlags = description.MiscFlags = 0;
        description.Usage = D3D11_USAGE_STAGING;
        description.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        if (FAILED(renderer.device->CreateTexture2D(&description, nullptr, &probe.staging))) {
            probe.complete = true;
            return;
        }
        probe.file = CreateFileA("d3d11-draw-probe.jsonl", GENERIC_WRITE, FILE_SHARE_READ, nullptr,
                                 CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (probe.file == INVALID_HANDLE_VALUE) {
            probe.staging->Release();
            probe.staging = nullptr;
            probe.complete = true;
            return;
        }
        DeleteFileA("d3d11-draw-probe.request");
        probe.active = true;
        probe.frame = frame;
        probe.draws = probe.changes = 0;
        ++probe.capture;
        char text[256];
        int size = wsprintfA(
            text,
            "{\"event\":\"begin\",\"frame\":%u,\"thread\":%u,\"width\":%u,\"height\":%u,\"capture\":%u,\"samples\":[[%u,%u],[%u,%u]],\"images\":%u}\n",
            UINT(frame), GetCurrentThreadId(), probe.width, probe.height, probe.capture,
            probe.sample_x[0], probe.sample_y[0], probe.sample_x[1], probe.sample_y[1],
            UINT(probe.images));
        probe_write(text, size);
    }
    if (!probe.active)
        return;
    probe.vertex = vertex;
    probe.pixel = pixel;
    probe.layout = layout;
    probe.world = world;
    probe.style = style;
    probe.image = image;
    probe.secondary = secondary;
}
void probe_after_draw(NativeRenderer& renderer, const void* vertices = nullptr, UINT bytes = 0) {
    auto& probe = draw_probe;
    if (!probe.active)
        return;
    ID3D11RenderTargetView* target = nullptr;
    renderer.context->OMGetRenderTargets(1, &target, nullptr);
    ID3D11Resource* resource = nullptr;
    if (target) {
        target->GetResource(&resource);
        target->Release();
    }
    const bool main_target = resource == renderer.backbuffer;
    if (resource)
        resource->Release();
    if (!main_target)
        return;
    if (++probe.draws > 8192) {
        probe_close();
        return;
    }
    for (UINT point = 0; point < 2; ++point) {
        UINT x = probe.sample_x[point], y = probe.sample_y[point];
        const D3D11_BOX box = {x, y, 0, x + 1, y + 1, 1};
        renderer.context->CopySubresourceRegion(probe.staging, 0, point, 0, 0, renderer.backbuffer,
                                                0, &box);
    }
    D3D11_MAPPED_SUBRESOURCE mapped = {};
    if (FAILED(renderer.context->Map(probe.staging, 0, D3D11_MAP_READ, 0, &mapped)))
        return;
    const UINT color[2] = {static_cast<const UINT*>(mapped.pData)[0],
                           static_cast<const UINT*>(mapped.pData)[1]};
    renderer.context->Unmap(probe.staging, 0);
    if (probe.draws != 1 && color[0] == probe.color[0] && color[1] == probe.color[1])
        return;
    ++probe.changes;
    probe.color[0] = color[0];
    probe.color[1] = color[1];
    char filename[64] = {};
    probe_image(renderer, filename);
    char text[4096];
    int size = wsprintfA(
        text,
        "{\"event\":\"draw\",\"draw\":%u,\"vertex\":%u,\"pixel\":%u,\"layout\":%u,\"rgba\":[\"%08x\",\"%08x\"],\"image\":\"%p\",\"secondary\":\"%p\",\"blend\":%u,\"depth\":%u,\"cull\":%u,\"source\":%u,\"destination\":%u,\"world_bits\":[",
        probe.draws, probe.vertex, probe.pixel, probe.layout, color[0], color[1], probe.image,
        probe.secondary, UINT(probe.style.blend), UINT(probe.style.depth), UINT(probe.style.cull),
        UINT(probe.style.source_blend), UINT(probe.style.destination_blend));
    for (UINT index = 0; index < 16; ++index)
        size += wsprintfA(text + size, "%s\"%08x\"", index ? "," : "",
                          reinterpret_cast<const UINT*>(&probe.world)[index]);
    size += wsprintfA(text + size, "],\"vp_bits\":[");
    for (UINT index = 0; index < 16; ++index)
        size += wsprintfA(text + size, "%s\"%08x\"", index ? "," : "",
                          reinterpret_cast<const UINT*>(&renderer.scene.view_projection)[index]);
    size += wsprintfA(text + size, "],\"vertex_bits\":[");
    if (bytes > 84)
        bytes = 84;
    for (UINT index = 0; vertices && index < bytes / 4; ++index)
        size += wsprintfA(text + size, "%s\"%08x\"", index ? "," : "",
                          static_cast<const UINT*>(vertices)[index]);
    void* stack[12];
    const USHORT count = CaptureStackBackTrace(0, 12, stack, nullptr);
    size += wsprintfA(text + size, "],\"stack\":[");
    for (USHORT index = 0; index < count; ++index)
        size += wsprintfA(text + size, "%s\"%p\"", index ? "," : "", stack[index]);
    size += wsprintfA(text + size, "],\"snapshot\":\"%s\"}\n", filename);
    probe_write(text, size);
}
} // namespace
} // namespace shaiya::graphics::native
