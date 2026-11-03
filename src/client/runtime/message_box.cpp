#include "runtime_error.h"
#include "heap.h"
extern "C" {
__declspec(dllimport) void* __attribute__((stdcall)) LoadLibraryA(const char*);
using ProcedureQuery = void*(__attribute__((stdcall)) *)(void*, const char*);
extern ProcedureQuery imported_procedure_query __asm__("__imp__GetProcAddress@8");
OriginalMessageBox dat_0224f2c0 = nullptr;
OriginalActiveWindow dat_0224f2c4 = nullptr;
OriginalActivePopup dat_0224f2c8 = nullptr;
OriginalWindowStation dat_0224f2cc = nullptr;
OriginalUserInformation dat_0224f2d0 = nullptr;
}
extern "C" int32_t fun_005e02eb(const char* text, const char* caption, uint32_t flags) {
    void* window = nullptr;
    if (dat_0224f2c0 == nullptr) {
        void* module = LoadLibraryA("user32.dll");
        if (module == nullptr)
            return 0;
        const ProcedureQuery query = imported_procedure_query;
        dat_0224f2c0 = reinterpret_cast<OriginalMessageBox>(query(module, "MessageBoxA"));
        if (dat_0224f2c0 == nullptr)
            return 0;
        dat_0224f2c4 = reinterpret_cast<OriginalActiveWindow>(query(module, "GetActiveWindow"));
        dat_0224f2c8 = reinterpret_cast<OriginalActivePopup>(query(module, "GetLastActivePopup"));
        if (dat_0224ede8 == 2) {
            dat_0224f2d0 = reinterpret_cast<OriginalUserInformation>(
                query(module, "GetUserObjectInformationA"));
            if (dat_0224f2d0 != nullptr)
                dat_0224f2cc = reinterpret_cast<OriginalWindowStation>(
                    query(module, "GetProcessWindowStation"));
        }
    }
    bool interactive = true;
    const OriginalWindowStation station_query = dat_0224f2cc;
    if (station_query != nullptr) {
        void* station = station_query();
        interactive = false;
        if (station != nullptr) {
            uint8_t information[12];
            uint32_t needed;
            if (dat_0224f2d0(station, 1, information, 12, &needed) != 0) {
                uint32_t low_flags;
                __asm__ volatile("movzbl (%1),%0"
                                 : "=r"(low_flags)
                                 : "r"(information + 8)
                                 : "memory");
                interactive = (low_flags & 1) != 0;
            }
        }
        if (!interactive)
            flags |= dat_0224edf4 >= 4 ? 0x200000u : 0x40000u;
    }
    if (interactive) {
        const OriginalActiveWindow active_query = dat_0224f2c4;
        if (active_query != nullptr) {
            window = active_query();
            const OriginalActivePopup popup_query = dat_0224f2c8;
            if (window != nullptr && popup_query != nullptr)
                window = popup_query(window);
        }
    }
    return dat_0224f2c0(window, text, caption, flags);
}
