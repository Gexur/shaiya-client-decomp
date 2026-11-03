#pragma once
#include <stdint.h>

// x86 RTL_CRITICAL_SECTION, as consumed by the actual Win32 imports. A local
// layout avoids depending on GNU SDK headers in the MSVC-target SEH unit.
struct OriginalCriticalSection {
    void* debug_information;
    int32_t lock_count;
    int32_t recursion_count;
    void* owning_thread;
    void* semaphore;
    uint32_t spin_count;
};

struct OriginalLockEntry {
    OriginalCriticalSection* section;
    int32_t static_storage;
};
static_assert(sizeof(OriginalCriticalSection) == 24);
static_assert(sizeof(OriginalLockEntry) == 8);

using CriticalSectionInitializer = int32_t(__attribute__((stdcall)) *)(OriginalCriticalSection*,
                                                                       uint32_t);

extern "C" {
// Original .data table: 36 pointer/kind pairs, initially null pointers.
extern OriginalLockEntry dat_0070e990[36];
// Exactly fourteen kind==1 entries consume this zero-initialized .bss span.
extern OriginalCriticalSection dat_0224ee80[14];
extern CriticalSectionInitializer dat_0224f2b4;

int32_t fun_005d6448();
void fun_005d6491();
void fun_005d64e6(int32_t lock_index);
int32_t fun_005d64fb(int32_t lock_index);
void fun_005d6592();
void fun_005d659b(int32_t lock_index);
int32_t __attribute__((stdcall)) fun_005de960(OriginalCriticalSection*, uint32_t spin_count);
int32_t fun_005de970(OriginalCriticalSection*, uint32_t spin_count);

int32_t* fun_005d589a();
// The returned CRT per-thread block has the original errno DWORD at +8.
// Its allocation/TLS/termination behavior is a real unrecovered dependency.
void* fun_005d2659();
void fun_005d098b(int32_t runtime_message);
}
