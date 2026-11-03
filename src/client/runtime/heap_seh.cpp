// Real x86 SEH scope tables require the MSVC target used by build_cpp.py.
#include "heap.h"
#include "../core/memory.h"

extern "C" {
__declspec(dllimport) void* __attribute__((stdcall)) HeapAlloc(void*, uint32_t, uint32_t);
__declspec(dllimport) int32_t __attribute__((stdcall)) HeapFree(void*, uint32_t, void*);
__declspec(dllimport) void* __attribute__((stdcall)) HeapReAlloc(void*, uint32_t, void*, uint32_t);
}

extern "C" void* fun_005cfa37(uint32_t bytes) {
    if (dat_022532c8 == 3 && bytes <= dat_022532b4) {
        fun_005d659b(4);
        void* result;
        __try {
            result = fun_005d9f8f(bytes);
        } __finally {
            fun_005cfaa9();
        }
        if (result != nullptr)
            return result;
    }
    if (bytes == 0)
        bytes = 1;
    if (dat_022532c8 != 1)
        bytes = (bytes + 15) & 0xfffffff0u;
    return HeapAlloc(dat_022532c4, 0, bytes);
}

extern "C" void fun_005cfaf0(void* pointer) {
    if (pointer == nullptr)
        return;
    if (dat_022532c8 == 3) {
        fun_005d659b(4);
        SmallBlockRegion* region;
        __try {
            region = fun_005d97b0(pointer);
            if (region != nullptr)
                fun_005d97db(region, pointer);
        } __finally {
            fun_005cfb43();
        }
        if (region != nullptr)
            return;
    }
    HeapFree(dat_022532c4, 0, pointer);
}

extern "C" void* fun_005d020a(void* pointer, uint32_t bytes) {
    if (pointer == nullptr)
        return fun_005cfade(bytes);
    if (bytes == 0) {
        fun_005cfaf0(pointer);
        return nullptr;
    }
    if (dat_022532c8 == 3) {
        do {
            if (bytes > 0xffffffe0u) {
                fun_005da28b(bytes);
                return nullptr;
            }
            void* result = nullptr;
            fun_005d659b(4);
            SmallBlockRegion* region;
            __try {
                region = fun_005d97b0(pointer);
                if (region != nullptr) {
                    if (bytes <= dat_022532b4) {
                        if (fun_005d9cb0(region, pointer, bytes) != 0) {
                            result = pointer;
                        } else {
                            result = fun_005d9f8f(bytes);
                            if (result != nullptr) {
                                uint32_t old_bytes = static_cast<uint32_t*>(pointer)[-1] - 1;
                                if (bytes <= old_bytes)
                                    old_bytes = bytes;
                                fun_005d8d30(result, pointer, old_bytes);
                                region = fun_005d97b0(pointer);
                                fun_005d97db(region, pointer);
                            }
                        }
                    }
                    if (result == nullptr) {
                        if (bytes == 0)
                            bytes = 1;
                        bytes = (bytes + 15) & 0xfffffff0u;
                        result = HeapAlloc(dat_022532c4, 0, bytes);
                        if (result != nullptr) {
                            uint32_t old_bytes = static_cast<uint32_t*>(pointer)[-1] - 1;
                            if (bytes <= old_bytes)
                                old_bytes = bytes;
                            fun_005d8d30(result, pointer, old_bytes);
                            fun_005d97db(region, pointer);
                        }
                    }
                }
            } __finally {
                fun_005d0372();
            }
            if (region == nullptr) {
                if (bytes == 0)
                    bytes = 1;
                bytes = (bytes + 15) & 0xfffffff0u;
                result = HeapReAlloc(dat_022532c4, 0, pointer, bytes);
            }
            if (result != nullptr || dat_0224f0b8 == 0)
                return result;
        } while (fun_005da28b(bytes) != 0);
    } else {
        do {
            if (bytes > 0xffffffe0u) {
                fun_005da28b(bytes);
                return nullptr;
            }
            if (bytes == 0)
                bytes = 1;
            void* result = HeapReAlloc(dat_022532c4, 0, pointer, bytes);
            if (result != nullptr || dat_0224f0b8 == 0)
                return result;
        } while (fun_005da28b(bytes) != 0);
    }
    return nullptr;
}
