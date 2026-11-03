#include "file_ops.h"
extern "C" {
__declspec(dllimport) uint32_t __attribute__((stdcall)) SetFilePointer(void*, int32_t, int32_t*,
                                                                       uint32_t);
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetLastError();
}
extern "C" int32_t fun_005cd610(int32_t descriptor, int32_t offset, int32_t origin) {
    const int32_t handle = fun_005d5c18(descriptor);
    if (handle == -1) {
        *fun_005d589a() = 9;
        return -1;
    }
    uint32_t result = SetFilePointer(reinterpret_cast<void*>(handle), offset, nullptr, origin);
    const uint32_t error = result == 0xffffffffu ? GetLastError() : 0;
    if (error) {
        fun_005d58ac(error);
        result = 0xffffffffu;
    } else
        file_io_entry(descriptor)->flags &= 0xfdu;
    return int32_t(result);
}
extern "C" int32_t fun_005cd5ff(int32_t descriptor) {
    return fun_005cd684(descriptor, 0, 1);
}
extern "C" int32_t _lseek(int32_t descriptor, int32_t offset, int32_t origin) {
    return fun_005cd684(descriptor, offset, origin);
}
extern "C" int32_t _tell(int32_t descriptor) {
    return fun_005cd5ff(descriptor);
}
extern "C" int32_t _close(int32_t descriptor) {
    return fun_005cd564(descriptor);
}
