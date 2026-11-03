#include "cxx_dispatch.h"

extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall)) IsBadReadPtr(const void*, uint32_t);
__declspec(dllimport) int32_t __attribute__((stdcall)) IsBadWritePtr(void*, uint32_t);
__declspec(dllimport) int32_t __attribute__((stdcall)) IsBadCodePtr(void*);
}
extern "C" int32_t fun_005dc907(const void* address, uint32_t bytes) {
    return IsBadReadPtr(address, bytes) == 0;
}
extern "C" int32_t fun_005dc923(void* address, uint32_t bytes) {
    return IsBadWritePtr(address, bytes) == 0;
}
extern "C" int32_t fun_005dc93f(void* function) {
    return IsBadCodePtr(function) == 0;
}
