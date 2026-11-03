#include "graphics/native_capture.h"
#include "graphics/native_resources.h"
#include "graphics/native_scene_ports.h"
#include "core/quad_draw.h"
#include <wincodec.h>
using namespace shaiya::graphics::native;
extern "C" {
extern const char dat_006c8478[], dat_006bcc50[];
UINT __attribute__((thiscall)) FUN_005497a0(void*, const char*, const char*, int, int);
void __attribute__((thiscall)) FUN_00542d40(void*);
extern unsigned char dat_02209408[];
}
namespace {
template <class T> void release(T*& value) {
    if (value)
        value->Release();
    value = nullptr;
}
bool same_guid(const GUID& a, const GUID& b) {
    return a.Data1 == b.Data1 && a.Data2 == b.Data2 && a.Data3 == b.Data3 &&
           *reinterpret_cast<const uint64_t*>(a.Data4) ==
               *reinterpret_cast<const uint64_t*>(b.Data4);
}
HRESULT write_jpeg(const char* filename, UINT width, UINT height, unsigned char* pixels,
                   float quality) {
    const GUID factory_class = {
        0xcacaf262, 0x9370, 0x4615, {0xa1, 0x3b, 0x9f, 0x55, 0x39, 0xda, 0x4c, 0x0a}};
    const GUID factory_interface = {
        0xec5ec8a9, 0xc395, 0x4314, {0x9c, 0x77, 0x54, 0xd7, 0xa9, 0x35, 0xff, 0x70}};
    const GUID jpeg = {
        0x19e4a5aa, 0x5662, 0x4fc5, {0xa0, 0xc0, 0x17, 0x58, 0x02, 0x8e, 0x10, 0x57}};
    const GUID bgr = {0x6fddc324, 0x4e03, 0x4bfe, {0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x0c}};
    wchar_t wide[32768];
    if (!MultiByteToWideChar(CP_ACP, 0, filename, -1, wide, 32768))
        return HRESULT_FROM_WIN32(GetLastError());
    const HRESULT initialized = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(initialized) && initialized != RPC_E_CHANGED_MODE)
        return initialized;
    IWICImagingFactory* factory = nullptr;
    IWICStream* stream = nullptr;
    IWICBitmapEncoder* encoder = nullptr;
    IWICBitmapFrameEncode* frame = nullptr;
    IPropertyBag2* properties = nullptr;
    HRESULT result = CoCreateInstance(factory_class, nullptr, CLSCTX_INPROC_SERVER,
                                      factory_interface, reinterpret_cast<void**>(&factory));
    if (SUCCEEDED(result))
        result = factory->CreateStream(&stream);
    if (SUCCEEDED(result))
        result = stream->InitializeFromFilename(wide, GENERIC_WRITE);
    if (SUCCEEDED(result))
        result = factory->CreateEncoder(jpeg, nullptr, &encoder);
    if (SUCCEEDED(result))
        result = encoder->Initialize(stream, WICBitmapEncoderNoCache);
    if (SUCCEEDED(result))
        result = encoder->CreateNewFrame(&frame, &properties);
    if (SUCCEEDED(result)) {
        PROPBAG2 option = {};
        option.pstrName = const_cast<wchar_t*>(L"ImageQuality");
        VARIANT value = {};
        value.vt = VT_R4;
        value.fltVal = quality;
        result = properties->Write(1, &option, &value);
    }
    if (SUCCEEDED(result))
        result = frame->Initialize(properties);
    if (SUCCEEDED(result))
        result = frame->SetSize(width, height);
    GUID format = bgr;
    if (SUCCEEDED(result))
        result = frame->SetPixelFormat(&format);
    if (SUCCEEDED(result) && !same_guid(format, bgr))
        result = E_NOTIMPL;
    if (SUCCEEDED(result))
        result = frame->WritePixels(height, width * 3, width * height * 3, pixels);
    if (SUCCEEDED(result))
        result = frame->Commit();
    if (SUCCEEDED(result))
        result = encoder->Commit();
    release(properties);
    release(frame);
    release(encoder);
    release(stream);
    release(factory);
    if (SUCCEEDED(initialized))
        CoUninitialize();
    return result;
}
} // namespace
namespace shaiya::graphics::native {
HRESULT capture_jpeg(NativeRenderer& current, const char* filename, float quality) {
    if (!filename || !current.device || !current.context || !current.backbuffer ||
        !(quality >= 0 && quality <= 1))
        return E_INVALIDARG;
    D3D11_TEXTURE2D_DESC description = {};
    current.backbuffer->GetDesc(&description);
    const bool rgba = description.Format == DXGI_FORMAT_R8G8B8A8_UNORM ||
                      description.Format == DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    const bool bgra = description.Format == DXGI_FORMAT_B8G8R8A8_UNORM ||
                      description.Format == DXGI_FORMAT_B8G8R8X8_UNORM;
    if (!rgba && !bgra)
        return E_NOTIMPL;
    ID3D11Texture2D* source = current.backbuffer;
    ID3D11Texture2D* resolved = nullptr;
    ID3D11Texture2D* staging = nullptr;
    HRESULT result = S_OK;
    if (description.SampleDesc.Count != 1) {
        description.SampleDesc = {1, 0};
        description.BindFlags = 0;
        description.MiscFlags = 0;
        result = current.device->CreateTexture2D(&description, nullptr, &resolved);
        if (SUCCEEDED(result)) {
            current.context->ResolveSubresource(resolved, 0, source, 0, description.Format);
            source = resolved;
        }
    }
    description.BindFlags = 0;
    description.MiscFlags = 0;
    description.Usage = D3D11_USAGE_STAGING;
    description.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    if (SUCCEEDED(result))
        result = current.device->CreateTexture2D(&description, nullptr, &staging);
    unsigned char* pixels = nullptr;
    D3D11_MAPPED_SUBRESOURCE mapped = {};
    if (SUCCEEDED(result)) {
        current.context->CopyResource(staging, source);
        result = current.context->Map(staging, 0, D3D11_MAP_READ, 0, &mapped);
    }
    if (SUCCEEDED(result)) {
        pixels = static_cast<unsigned char*>(
            HeapAlloc(GetProcessHeap(), 0, size_t(description.Width) * description.Height * 3));
        if (!pixels)
            result = E_OUTOFMEMORY;
        else
            for (UINT y = 0; y < description.Height; ++y)
                for (UINT x = 0; x < description.Width; ++x) {
                    const auto* from = static_cast<const unsigned char*>(mapped.pData) +
                                       size_t(y) * mapped.RowPitch + x * 4;
                    auto* to = pixels + (size_t(y) * description.Width + x) * 3;
                    to[0] = from[rgba ? 2 : 0];
                    to[1] = from[1];
                    to[2] = from[rgba ? 0 : 2];
                }
        current.context->Unmap(staging, 0);
    }
    if (SUCCEEDED(result))
        result = write_jpeg(filename, description.Width, description.Height, pixels, quality);
    if (pixels)
        HeapFree(GetProcessHeap(), 0, pixels);
    release(staging);
    release(resolved);
    return result;
}
} // namespace shaiya::graphics::native
extern "C" void __attribute__((thiscall)) FUN_00543fc0(void*, char* output_name) {
    auto& current = *renderer();
    FrameRenderScope serialization(current);
    if (!current.device || !output_name)
        return;
    struct Image {
        Texture2D* first;
        Texture2D* second;
        float width, height;
    } image = {};
    {
        SceneDrawScope preserve;
        if (FUN_005497a0(&image, dat_006bcc50, dat_006c8478, 512, 128)) {
            FUN_00542d40(dat_02209408);
            FUN_00549a70(&image, current.width - 512, current.height - 128);
        }
    }
    if (image.first)
        image.first->release();
    if (image.second)
        image.second->release();
    char directory[260];
    DWORD length = GetCurrentDirectoryA(260, directory);
    if (!length || length > 240)
        return;
    const char suffix[] = "\\SCREENSHOT";
    for (UINT i = 0; i < sizeof(suffix); ++i)
        directory[length + i] = suffix[i];
    if (!CreateDirectoryA(directory, nullptr) && GetLastError() != ERROR_ALREADY_EXISTS)
        return;
    char filename[64], path[340];
    bool reserved = false;
    for (UINT index = 0; index < 1000000; ++index) {
        wsprintfA(filename, "Shaiya%04u.jpg", index);
        wsprintfA(path, "%s\\%s", directory, filename);
        HANDLE file = CreateFileA(path, GENERIC_WRITE, 0, nullptr, CREATE_NEW,
                                  FILE_ATTRIBUTE_NORMAL, nullptr);
        if (file != INVALID_HANDLE_VALUE) {
            CloseHandle(file);
            reserved = true;
            break;
        }
        if (GetLastError() != ERROR_FILE_EXISTS && GetLastError() != ERROR_ALREADY_EXISTS)
            return;
    }
    if (!reserved)
        return;
    if (FAILED(capture_jpeg(current, path, .9f))) {
        DeleteFileA(path);
        return;
    }
    UINT i = 0;
    do {
        output_name[i] = filename[i];
    } while (filename[i++]);
}
