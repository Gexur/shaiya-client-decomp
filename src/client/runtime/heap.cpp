#include "heap.h"

extern "C" {
__declspec(dllimport) void* __attribute__((stdcall)) HeapCreate(uint32_t, uint32_t, uint32_t);
__declspec(dllimport) int32_t __attribute__((stdcall)) HeapDestroy(void*);

// Each original location is in the PE loader's zero-filled storage. The SBH
// algorithms and CRT startup share these canonical variables after relocation.
uint32_t dat_0224ede8 = 0;
uint32_t dat_0224edf4 = 0;
OriginalNewHandler dat_0224f0b4 = nullptr;
int32_t dat_0224f0b8 = 0;
SmallBlockRegion* dat_022532a8 = nullptr;
uint32_t dat_022532ac = 0;
SmallBlockRegion* dat_022532b0 = nullptr;
uint32_t dat_022532b4 = 0;
SmallBlockRegion* dat_022532b8 = nullptr;
uint32_t dat_022532bc = 0;
uint32_t dat_022532c0 = 0;
void* dat_022532c4 = nullptr;
uint32_t dat_022532c8 = 0;
}

// Original finally entries invoke the recovered lock release. The heap _seh
// translation unit emits real scope tables for exceptional as well as ordinary exits.
extern "C" void fun_005cfaa9() {
    fun_005d64e6(4);
}
extern "C" void fun_005cfb43() {
    fun_005d64e6(4);
}
extern "C" void fun_005d0372() {
    fun_005d64e6(4);
}

extern "C" uint32_t fun_005d96fd() {
    // CMP/JB is unsigned, despite the provider's signed-looking pseudocode.
    return dat_0224ede8 == 2 && dat_0224edf4 >= 5 ? 1 : 3;
}

extern "C" int32_t fun_005d9717(int32_t multithreaded) {
    dat_022532c4 = HeapCreate(uint32_t(multithreaded == 0), 0x1000, 0);
    if (dat_022532c4 == nullptr)
        return 0;
    dat_022532c8 = fun_005d96fd();
    if (dat_022532c8 == 3 && fun_005d9768(0x3f8) == 0) {
        HeapDestroy(dat_022532c4);
        return 0;
    }
    return 1;
}

extern "C" int32_t fun_005da28b(uint32_t bytes) {
    OriginalNewHandler handler = dat_0224f0b4;
    return handler != nullptr && handler(bytes) != 0 ? 1 : 0;
}

extern "C" void* fun_005cfab2(uint32_t bytes, int32_t use_new_handler) {
    if (bytes > 0xffffffe0u)
        return nullptr;
    do {
        void* result = fun_005cfa37(bytes);
        if (result != nullptr || use_new_handler == 0)
            return result;
    } while (fun_005da28b(bytes) != 0);
    return nullptr;
}

extern "C" void* fun_005cfade(uint32_t bytes) {
    return fun_005cfab2(bytes, dat_0224f0b8);
}
