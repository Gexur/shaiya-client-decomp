#include "cinit.h"
extern "C" void fun_005cdfdb(OriginalCppInitializer* first, OriginalCppInitializer* last) {
    for (; reinterpret_cast<uint32_t>(first) < reinterpret_cast<uint32_t>(last); ++first) {
        OriginalCppInitializer callback = *first;
        if (callback != nullptr)
            callback();
    }
}
