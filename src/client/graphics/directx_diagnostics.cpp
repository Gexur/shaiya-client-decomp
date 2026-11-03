#include "graphics/directx_version.h"
#define CINTERFACE
#include <windows.h>
#include <oleauto.h>
#include <dxdiag.h>
extern "C" {
extern const GUID dat_006c8630 = {
    0x9c6b4cb0, 0x23f8, 0x49cc, {0xa3, 0xed, 0x45, 0xa5, 0x50, 0x00, 0xa6, 0xd2}};
extern const GUID dat_006c8640 = {
    0xa65b8071, 0x3bfe, 0x4213, {0x9a, 0x5b, 0x49, 0x1d, 0xa4, 0x46, 0x1c, 0xa7}};
extern const wchar_t s_006c8650[] = L"szDirectXVersionLetter";
extern const wchar_t s_006c8680[] = L"dwDirectXVersionMinor";
extern const wchar_t s_006c86ac[] = L"dwDirectXVersionMajor";
extern const wchar_t s_006c86d8[] = L"DxDiag_SystemInfo";
}
static_assert(sizeof(wchar_t) == 2);
// Original00546fb0..005471b4. Real COM vtable self/stdcall arguments are
// recovered from each PUSH sequence, not the broken hidden-argument export.
extern "C" int32_t __attribute__((cdecl)) FUN_00546fb0(uint32_t* major, uint32_t* minor,
                                                       char* letter) {
    using namespace directx_version_detail;
    bool major_ok = false, minor_ok = false, letter_ok = false, complete = false;
    const HRESULT initialized = CoInitialize(nullptr);
    IDxDiagProvider* provider = nullptr;
    if (CoCreateInstance(dat_006c8640, nullptr, 1, dat_006c8630,
                         reinterpret_cast<void**>(&provider)) >= 0) {
        DXDIAG_INIT_PARAMS params = {sizeof(DXDIAG_INIT_PARAMS), 111, 0, nullptr};
        if (provider->lpVtbl->Initialize(provider, &params) >= 0) {
            IDxDiagContainer* root = nullptr;
            IDxDiagContainer* child = nullptr;
            if (provider->lpVtbl->GetRootContainer(provider, &root) >= 0) {
                if (root->lpVtbl->GetChildContainer(root, s_006c86d8, &child) >= 0) {
                    VARIANT value;
                    VariantInit(&value);
                    if (child->lpVtbl->GetProp(child, s_006c86ac, &value) >= 0 &&
                        V_VT(&value) == 19) {
                        if (major != nullptr)
                            store32(major, V_UI4(&value));
                        major_ok = true;
                    }
                    VariantClear(&value);
                    if (child->lpVtbl->GetProp(child, s_006c8680, &value) >= 0 &&
                        V_VT(&value) == 19) {
                        if (minor != nullptr)
                            store32(minor, V_UI4(&value));
                        minor_ok = true;
                    }
                    VariantClear(&value);
                    if (child->lpVtbl->GetProp(child, s_006c8650, &value) >= 0 &&
                        V_VT(&value) == 8 && SysStringLen(V_BSTR(&value)) != 0) {
                        char converted[10];
                        // Original ignores conversion HRESULT/byte count and
                        // reads the actual first private byte even on failure.
                        WideCharToMultiByte(0, 0, V_BSTR(&value), -1, converted, 10, nullptr,
                                            nullptr);
                        if (letter != nullptr)
                            store8(letter, load8(converted));
                        letter_ok = true;
                    }
                    VariantClear(&value);
                    complete = major_ok && minor_ok && letter_ok;
                    child->lpVtbl->Release(child);
                }
                root->lpVtbl->Release(root);
            }
        }
        provider->lpVtbl->Release(provider);
    }
    if (initialized >= 0)
        CoUninitialize();
    return complete ? 0 : int32_t(0x80004005u);
}
