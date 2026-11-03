#include "locks.h"
#include "heap.h"

extern "C" {
__declspec(dllimport) void __attribute__((stdcall)) DeleteCriticalSection(OriginalCriticalSection*);
__declspec(dllimport) void __attribute__((stdcall)) LeaveCriticalSection(OriginalCriticalSection*);
__declspec(dllimport) void __attribute__((stdcall)) EnterCriticalSection(OriginalCriticalSection*);
__declspec(dllimport) void __attribute__((stdcall))
InitializeCriticalSection(OriginalCriticalSection*);
OriginalLockEntry dat_0070e990[36] = {
    {nullptr, 1}, {nullptr, 1}, {nullptr, 0}, {nullptr, 1}, {nullptr, 1}, {nullptr, 0},
    {nullptr, 1}, {nullptr, 1}, {nullptr, 1}, {nullptr, 0}, {nullptr, 1}, {nullptr, 0},
    {nullptr, 1}, {nullptr, 1}, {nullptr, 1}, {nullptr, 0}, {nullptr, 1}, {nullptr, 1},
    {nullptr, 1}, {nullptr, 0}, {nullptr, 0}, {nullptr, 0}, {nullptr, 0}, {nullptr, 0},
    {nullptr, 0}, {nullptr, 0}, {nullptr, 0}, {nullptr, 0}, {nullptr, 0}, {nullptr, 0},
    {nullptr, 0}, {nullptr, 0}, {nullptr, 0}, {nullptr, 0}, {nullptr, 0}, {nullptr, 0}};
OriginalCriticalSection dat_0224ee80[14] = {};
CriticalSectionInitializer dat_0224f2b4 = nullptr;
}

extern "C" int32_t fun_005d6448() {
    OriginalCriticalSection* next_static = dat_0224ee80;
    for (int32_t index = 0; index < 36; ++index) {
        if (dat_0070e990[index].static_storage == 1) {
            dat_0070e990[index].section = next_static++;
            if (fun_005de970(dat_0070e990[index].section, 4000) == 0) {
                dat_0070e990[index].section = nullptr;
                return 0;
            }
        }
    }
    return 1;
}

extern "C" void fun_005d6491() {
    for (int32_t index = 0; index < 36; ++index) {
        OriginalLockEntry* entry = &dat_0070e990[index];
        OriginalCriticalSection* section = entry->section;
        if (section != nullptr && entry->static_storage != 1) {
            DeleteCriticalSection(section);
            fun_005cfaf0(section);
            entry->section = nullptr;
        }
    }
    for (int32_t index = 0; index < 36; ++index) {
        OriginalLockEntry* entry = &dat_0070e990[index];
        if (entry->section != nullptr && entry->static_storage == 1) {
            DeleteCriticalSection(entry->section);
        }
    }
}

extern "C" void fun_005d64e6(int32_t lock_index) {
    LeaveCriticalSection(dat_0070e990[lock_index].section);
}

extern "C" int32_t* fun_005d589a() {
    return reinterpret_cast<int32_t*>(static_cast<uint8_t*>(fun_005d2659()) + 8);
}

extern "C" void fun_005d6592() {
    fun_005d64e6(10);
}

extern "C" void fun_005d659b(int32_t lock_index) {
    OriginalLockEntry* entry = &dat_0070e990[lock_index];
    if (entry->section == nullptr && fun_005d64fb(lock_index) == 0) {
        fun_005d098b(17);
    }
    EnterCriticalSection(entry->section);
}

extern "C" int32_t __attribute__((stdcall)) fun_005de960(OriginalCriticalSection* section,
                                                         uint32_t /*spin_count*/) {
    InitializeCriticalSection(section);
    return 1;
}
