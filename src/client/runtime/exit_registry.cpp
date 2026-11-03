#include "exit_registry.h"
#include "heap.h"

extern "C" {
OriginalExitCallback* dat_0225464c = nullptr;
OriginalExitCallback* dat_02254648 = nullptr;
}

extern "C" int32_t fun_005ccf00() {
    dat_0225464c = static_cast<OriginalExitCallback*>(fun_005cfade(128));
    if (dat_0225464c == nullptr)
        return 24;
    *dat_0225464c = nullptr;
    dat_02254648 = dat_0225464c;
    return 0;
}

extern "C" OriginalExitCallback fun_005cce80(OriginalExitCallback callback) {
    uint32_t capacity = fun_005d2a5a(dat_0225464c);
    uint32_t begin = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(dat_0225464c));
    uint32_t end = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(dat_02254648));
    if (capacity < end - begin + 4) {
        uint32_t growth = capacity < 2048 ? capacity : 2048;
        void* allocation = fun_005d020a(dat_0225464c, capacity + growth);
        if (allocation == nullptr) {
            allocation = fun_005d020a(dat_0225464c, capacity + 16);
            if (allocation == nullptr)
                return nullptr;
        }
        // Original SAR(delta,2), then LEA(base + index*4), discards low bits
        // while retaining exact DWORD wrapping rather than rejecting input.
        const uint32_t delta = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(dat_02254648)) -
                               static_cast<uint32_t>(reinterpret_cast<uintptr_t>(dat_0225464c));
        dat_0225464c = static_cast<OriginalExitCallback*>(allocation);
        dat_02254648 = reinterpret_cast<OriginalExitCallback*>(
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(allocation)) + (delta & 0xfffffffcu));
    }
    *dat_02254648 = callback;
    ++dat_02254648;
    return callback;
}
extern "C" void fun_005cdfc9() {
    fun_005d659b(8);
}
extern "C" void fun_005cdfd2() {
    fun_005d64e6(8);
}
extern "C" void fun_005ccf5a() {
    fun_005cdfd2();
}
extern "C" int32_t fun_005ccf60(OriginalExitCallback callback) {
    return fun_005ccf28(callback) != nullptr ? 0 : -1;
}

// Actual CRT entry aliases used by recovered source and compiler libraries.
// They name the real functions above, not a substitute host CRT registry.
extern "C" int32_t atexit(OriginalExitCallback) __attribute__((alias("fun_005ccf60")));

extern "C" void fun_005d2ac7() {
    fun_005d64e6(4);
}
