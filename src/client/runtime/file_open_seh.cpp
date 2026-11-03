#include "file_open.h"
#include "heap.h"
extern "C" {
__declspec(dllimport) void __attribute__((stdcall)) EnterCriticalSection(OriginalCriticalSection*);
__declspec(dllimport) void __attribute__((stdcall)) LeaveCriticalSection(OriginalCriticalSection*);
}
extern "C" void fun_005d5df4() {
    fun_005d64e6(10);
}
extern "C" void fun_005d5e8e() {
    fun_005d64e6(11);
}
extern "C" int32_t fun_005d5d1b() {
    int32_t result = -1;
    if (!fun_005d64fb(11))
        return -1;
    fun_005d659b(11);
    __try {
        for (uint32_t group = 0; group < 64; ++group) {
            auto* entry = dat_022532e0[group];
            if (!entry) {
                auto* block = static_cast<OriginalIoEntry*>(fun_005cfade(0x480));
                if (block) {
                    dat_022532e0[group] = block;
                    dat_022532d4 = int32_t(uint32_t(dat_022532d4) + 32u);
                    while (reinterpret_cast<uint32_t>(block) <
                           reinterpret_cast<uint32_t>(dat_022532e0[group]) + 0x480u) {
                        block->flags = 0;
                        block->handle = reinterpret_cast<void*>(0xffffffffu);
                        block->lookahead = 10;
                        block->section_initialized = 0;
                        ++block;
                    }
                    result = int32_t(group << 5);
                    if (!fun_005d5c59(result))
                        result = -1;
                }
                break;
            }
            while (reinterpret_cast<uint32_t>(entry) <
                   reinterpret_cast<uint32_t>(dat_022532e0[group]) + 0x480u) {
                if (!(entry->flags & 1u)) {
                    if (!entry->section_initialized) {
                        fun_005d659b(10);
                        bool ready = true;
                        __try {
                            if (!entry->section_initialized) {
                                if (!fun_005de970(&entry->section, 4000))
                                    ready = false;
                                else
                                    ++entry->section_initialized;
                            }
                        } __finally {
                            fun_005d5df4();
                        }
                        if (!ready)
                            return -1;
                    }
                    EnterCriticalSection(&entry->section);
                    if (!(entry->flags & 1u)) {
                        entry->handle = reinterpret_cast<void*>(0xffffffffu);
                        const int32_t displacement =
                            int32_t(reinterpret_cast<uint32_t>(entry) -
                                    reinterpret_cast<uint32_t>(dat_022532e0[group]));
                        result = int32_t(uint32_t(displacement / 36) + (group << 5));
                        break;
                    }
                    LeaveCriticalSection(&entry->section);
                }
                ++entry;
            }
            if (result != -1)
                break;
        }
    } __finally {
        fun_005d5e8e();
    }
    return result;
}
extern "C" void fun_005cda5b(int32_t locked, int32_t descriptor) {
    if (locked)
        fun_005d5cf9(descriptor);
}
extern "C" int32_t fun_005cda16(const char* path, uint32_t flags, uint32_t permissions) {
    int32_t locked = 0, descriptor;
    int32_t result;
    __try {
        result = fun_005cd72f(&locked, &descriptor, path, flags, permissions, 0x40);
    } __finally {
        if (locked)
            fun_005cda5b(locked, descriptor);
    }
    return result;
}
