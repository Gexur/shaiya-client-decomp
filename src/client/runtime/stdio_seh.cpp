#include "stdio.h"
#include "heap.h"

extern "C" __declspec(dllimport) void __attribute__((stdcall))
DeleteCriticalSection(OriginalCriticalSection*);

extern "C" int32_t fun_005cff7b(int32_t mode) {
    int32_t count = 0, result = 0;
    fun_005d659b(1);
    __try {
        for (int32_t index = 0; index < dat_02254640; ++index) {
            auto* file = dat_02253624[index];
            if (file && (file->flags & 0x83u)) {
                fun_005d0195(index, file);
                __try {
                    file = dat_02253624[index];
                    if (file->flags & 0x83u) {
                        if (mode == 1) {
                            if (fun_005cff4d(file) != -1)
                                ++count;
                        } else if (mode == 0 && (file->flags & 2u)) {
                            if (fun_005cff4d(file) == -1)
                                result = -1;
                        }
                    }
                } __finally {
                    fun_005d001b(index);
                }
            }
        }
    } __finally {
        fun_005d0047();
    }
    return mode == 1 ? count : result;
}

extern "C" int32_t fun_005d0050(OriginalFile* file) {
    if (!file)
        return fun_005cff7b(0);
    fun_005d0166(file);
    int32_t result;
    __try {
        result = fun_005cff4d(file);
    } __finally {
        fun_005d0096(file);
    }
    return result;
}
extern "C" int32_t fun_005d00a0() {
    return fun_005cff7b(1);
}

extern "C" int32_t fun_005cdb3b(OriginalFile* file) {
    if (file->flags & 0x40u) {
        file->flags = 0;
        return -1;
    }
    fun_005d0166(file);
    int32_t result;
    __try {
        result = fun_005cdaef(file);
    } __finally {
        fun_005cdb84(file);
    }
    return result;
}

extern "C" int32_t fun_005da58b() {
    int32_t count = 0;
    fun_005d659b(1);
    __try {
        for (int32_t index = 3; index < dat_02254640; ++index) {
            auto* file = dat_02253624[index];
            if (file) {
                if ((file->flags & 0x83u) && fun_005cdb3b(file) != -1)
                    ++count;
                if (index >= 20) {
                    file = dat_02253624[index];
                    DeleteCriticalSection(reinterpret_cast<OriginalCriticalSection*>(
                        reinterpret_cast<uint8_t*>(file) + 32));
                    fun_005cfaf0(dat_02253624[index]);
                    dat_02253624[index] = nullptr;
                }
            }
        }
    } __finally {
        fun_005da61d();
    }
    return count;
}

extern "C" int32_t fun_006abadc() {
    int32_t count = 0;
    fun_005d659b(1);
    __try {
        for (int32_t index = 0; index < dat_02254640; ++index) {
            auto* file = dat_02253624[index];
            if (file && (file->flags & 0x83u)) {
                fun_005d0195(index, file);
                __try {
                    file = dat_02253624[index];
                    if ((file->flags & 0x83u) && file->temporary_name) {
                        fun_005cdaef(file);
                        ++count;
                    }
                } __finally {
                    fun_006abb52(index);
                }
            }
        }
    } __finally {
        fun_006abb75();
    }
    return count;
}
