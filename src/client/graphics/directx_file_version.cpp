#include "graphics/directx_version.h"
#include "runtime/allocations.h"
#include <windows.h>
extern "C" const char s_006bb608[] = "\\";
// Original005471c0..00547283, cdecl RET. The59fc90/96/9c entries
// are direct import thunks for these actual Win32 version APIs.
extern "C" int32_t __attribute__((cdecl)) FUN_005471c0(const char* filename, uint32_t* output) {
    using namespace directx_version_detail;
    if (filename == nullptr || output == nullptr)
        return int32_t(0x80070057u);
    DWORD handle;
    const DWORD size = GetFileVersionInfoSizeA(filename, &handle);
    if (size == 0)
        return int32_t(0x80004005u);
    void* data = fun_005cc96d(size);
    if (data == nullptr)
        return int32_t(0x8007000eu);
    if (GetFileVersionInfoA(filename, 0, size, data) != 0) {
        void* info = nullptr;
        UINT length;
        if (VerQueryValueA(data, s_006bb608, &info, &length) != 0 && info != nullptr) {
            // Original writes high DWORD first and then reads low DWORD.
            // Byte-safe C++ accesses also support unaligned output storage.
            store32(reinterpret_cast<uint8_t*>(output) + 4,
                    load32(static_cast<uint8_t*>(info) + 8));
            store32(output, load32(static_cast<uint8_t*>(info) + 12));
            fun_005cc620(data);
            return 0;
        }
    }
    fun_005cc620(data);
    return int32_t(0x80004005u);
}
// Original00547290..005472b6 compares high words unsigned before low
// words. Four stack DWORDs, cdecl RET; no host64-bit comparator substitute.
extern "C" int32_t __attribute__((cdecl)) FUN_00547290(uint32_t a_low, uint32_t a_high,
                                                       uint32_t b_low, uint32_t b_high) {
    if (a_high > b_high)
        return 1;
    if (a_high < b_high)
        return -1;
    if (a_low > b_low)
        return 1;
    return a_low < b_low ? -1 : 0;
}
