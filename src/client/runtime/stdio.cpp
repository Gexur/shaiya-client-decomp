#include "runtime/stdio.h"
#include "runtime/io.h"
#include "runtime/allocations.h"

extern "C" {
__declspec(dllimport) void __attribute__((stdcall)) EnterCriticalSection(OriginalCriticalSection*);
__declspec(dllimport) void __attribute__((stdcall)) LeaveCriticalSection(OriginalCriticalSection*);

char dat_02253640[4096] = {};
OriginalFile dat_0070e240[20] = {{dat_02253640, 0, dat_02253640, 0x101, 0, 0, 4096, nullptr},
                                 {nullptr, 0, nullptr, 2, 1, 0, 0, nullptr},
                                 {nullptr, 0, nullptr, 2, 2, 0, 0, nullptr}};
OriginalFile** dat_02253624 = nullptr;
int32_t dat_02254640 = 0;
}

extern "C" int32_t fun_005d00a9() {
    if (!dat_02254640)
        dat_02254640 = 512;
    else if (dat_02254640 < 20)
        dat_02254640 = 20;
    dat_02253624 = static_cast<OriginalFile**>(fun_005d8c58(dat_02254640, 4));
    if (!dat_02253624) {
        dat_02254640 = 20;
        dat_02253624 = static_cast<OriginalFile**>(fun_005d8c58(20, 4));
        if (!dat_02253624)
            return 26;
    }
    for (uint32_t i = 0; i < 20; ++i)
        dat_02253624[i] = &dat_0070e240[i];
    for (uint32_t i = 0; i < 3; ++i) {
        const uintptr_t handle = reinterpret_cast<uintptr_t>(dat_022532e0[i >> 5][i & 31].handle);
        if (!handle || handle == 0xffffffffu)
            dat_0070e240[i].descriptor = -1;
    }
    return 0;
}

extern "C" int32_t fun_005cfef0(OriginalFile* file) {
    int32_t result = 0;
    if ((file->flags & 3u) == 2 && (file->flags & 0x108u)) {
        const uint32_t count =
            reinterpret_cast<uint32_t>(file->cursor) - reinterpret_cast<uint32_t>(file->base);
        if (int32_t(count) > 0) {
            if (uint32_t(fun_005d0e1e(file->descriptor, file->base, count)) == count) {
                if (file->flags & 0x80u)
                    file->flags &= ~2u;
            } else {
                file->flags |= 0x20u;
                result = -1;
            }
        }
    }
    file->count = 0;
    file->cursor = file->base;
    return result;
}

extern "C" int32_t fun_005cff4d(OriginalFile* file) {
    if (fun_005cfef0(file))
        return -1;
    if (file->flags & 0x4000u)
        return fun_005da4cf(file->descriptor) ? -1 : 0;
    return 0;
}

static int32_t static_index(const OriginalFile* file) {
    return int32_t(reinterpret_cast<uint32_t>(file) - reinterpret_cast<uint32_t>(dat_0070e240)) >>
           5;
}
static bool is_static(const OriginalFile* file) {
    const uint32_t pointer = reinterpret_cast<uint32_t>(file);
    return pointer >= reinterpret_cast<uint32_t>(dat_0070e240) &&
           pointer <= reinterpret_cast<uint32_t>(&dat_0070e240[19]);
}
static OriginalCriticalSection* file_section(OriginalFile* file) {
    return reinterpret_cast<OriginalCriticalSection*>(reinterpret_cast<uint8_t*>(file) + 32);
}
extern "C" void fun_005d0166(OriginalFile* file) {
    if (is_static(file))
        fun_005d659b(static_index(file) + 16);
    else
        EnterCriticalSection(file_section(file));
}
extern "C" void fun_005d01b8(OriginalFile* file) {
    if (is_static(file))
        fun_005d64e6(static_index(file) + 16);
    else
        LeaveCriticalSection(file_section(file));
}
extern "C" void fun_005d0195(int32_t index, OriginalFile* file) {
    if (index < 20)
        fun_005d659b(int32_t(uint32_t(index) + 16u));
    else
        EnterCriticalSection(file_section(file));
}
extern "C" void fun_005d01e7(int32_t index, OriginalFile* file) {
    if (index < 20)
        fun_005d64e6(int32_t(uint32_t(index) + 16u));
    else
        LeaveCriticalSection(file_section(file));
}

extern "C" void fun_005d5fdc(OriginalFile* file) {
    if ((file->flags & 0x83u) && (file->flags & 8u)) {
        fun_005cfaf0(file->base);
        file->flags &= 0xfffffbf7u;
        file->cursor = nullptr;
        file->base = nullptr;
        file->count = 0;
    }
}

extern "C" int32_t fun_005cdaef(OriginalFile* file) {
    int32_t result = -1;
    if (file->flags & 0x83u) {
        result = fun_005cfef0(file);
        fun_005d5fdc(file);
        if (fun_005cd564(file->descriptor) < 0)
            result = -1;
        else if (file->temporary_name) {
            fun_005cfaf0(file->temporary_name);
            file->temporary_name = nullptr;
        }
    }
    file->flags = 0;
    return result;
}

extern "C" int32_t fun_005d0152() {
    const int32_t result = fun_005d00a0();
    if (dat_0224ee20)
        return fun_005da58b();
    return result;
}

extern "C" void fun_005d0047() {
    fun_005d64e6(1);
}
extern "C" void fun_005d0096(OriginalFile* file) {
    fun_005d01b8(file);
}
extern "C" void fun_005cdb84(OriginalFile* file) {
    fun_005d01b8(file);
}
extern "C" void fun_005da61d() {
    fun_005d64e6(1);
}
extern "C" void fun_006abb75() {
    fun_005d64e6(1);
}
extern "C" void fun_005d001b(int32_t index) {
    fun_005d01e7(index, dat_02253624[index]);
}
extern "C" void fun_006abb52(int32_t index) {
    fun_005d01e7(index, dat_02253624[index]);
}

__asm__(".globl _dat_0070e260\n.set _dat_0070e260, _dat_0070e240+32\n");

__asm__(".globl _dat_0070e280\n.set _dat_0070e280, _dat_0070e240+64\n");
