#include "path_ops.h"
#include "descriptor_io.h"
#include "locks.h"
extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall)) MoveFileA(const char*, const char*);
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetFileAttributesA(const char*);
__declspec(dllimport) int32_t __attribute__((stdcall)) RemoveDirectoryA(const char*);
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetLastError();
}
extern "C" int32_t fun_005cdeb6(const char* source, const char* destination) {
    const uint32_t error = MoveFileA(source, destination) ? 0 : GetLastError();
    if (error) {
        fun_005d58ac(error);
        return -1;
    }
    return 0;
}
extern "C" int32_t fun_005cdee4(const char* path, int32_t mode) {
    const uint32_t attributes = GetFileAttributesA(path);
    if (attributes == 0xffffffffu) {
        fun_005d58ac(GetLastError());
        return -1;
    }
    if (!(attributes & 1) || !(uint8_t(mode) & 2))
        return 0;
    *fun_005d589a() = 13;
    *fun_005d58a3() = 5;
    return -1;
}
extern "C" int32_t fun_005cdf2a(const char* path) {
    const uint32_t error = RemoveDirectoryA(path) ? 0 : GetLastError();
    if (error) {
        fun_005d58ac(error);
        return -1;
    }
    return 0;
}
extern "C" int32_t FUN_005cdeb6(const char*, const char*) __attribute__((alias("fun_005cdeb6")));
extern "C" int32_t FUN_005cdee4(const char*, int32_t) __attribute__((alias("fun_005cdee4")));
extern "C" int32_t FUN_005cdf2a(const char*) __attribute__((alias("fun_005cdf2a")));
