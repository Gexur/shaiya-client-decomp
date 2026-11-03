#include "io.h"
#include "heap.h"

namespace {
struct StartupInformation32 {
    uint8_t unused_00[0x32];
    uint16_t inherited_bytes;
    uint8_t* inherited_data;
    void* standard_input;
    void* standard_output;
    void* standard_error;
};
static_assert(sizeof(StartupInformation32) == 0x44);
static_assert(offsetof(StartupInformation32, inherited_bytes) == 0x32);
static_assert(offsetof(StartupInformation32, inherited_data) == 0x34);
void initialize_block(OriginalIoEntry* block) {
    for (uint32_t index = 0; index < 32; ++index) {
        block[index].handle = reinterpret_cast<void*>(0xffffffffu);
        block[index].section_initialized = 0;
        block[index].flags = 0;
        block[index].lookahead = 10;
    }
}
} // namespace
extern "C" {
__declspec(dllimport) void __attribute__((stdcall)) GetStartupInfoA(StartupInformation32*);
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetFileType(void*);
__declspec(dllimport) void* __attribute__((stdcall)) GetStdHandle(int32_t);
__declspec(dllimport) uint32_t __attribute__((stdcall)) SetHandleCount(uint32_t);
int32_t dat_022532d4 = 0;
OriginalIoEntry* dat_022532e0[64] = {};
}

extern "C" int32_t fun_005d591f() {
    auto* first = static_cast<OriginalIoEntry*>(fun_005cfade(0x480));
    if (first == nullptr)
        return -1;
    dat_022532e0[0] = first;
    dat_022532d4 = 32;
    initialize_block(first);
    StartupInformation32 startup;
    GetStartupInfoA(&startup);
    if (startup.inherited_bytes != 0 && startup.inherited_data != nullptr) {
        int32_t inherited = *reinterpret_cast<int32_t*>(startup.inherited_data);
        uint8_t* flags = startup.inherited_data + 4;
        // The handle array starts after the original count, before the signed
        // clamp to2048. Do not recompute this pointer from the clamped count.
        uint8_t* handles = flags + static_cast<uint32_t>(inherited);
        if (inherited >= 2048)
            inherited = 2048;
        uint32_t block_index = 1;
        while (dat_022532d4 < inherited) {
            auto* block = static_cast<OriginalIoEntry*>(fun_005cfade(0x480));
            if (block == nullptr) {
                inherited = dat_022532d4;
                break;
            }
            dat_022532d4 += 32;
            dat_022532e0[block_index++] = block;
            initialize_block(block);
        }
        for (int32_t index = 0; index < inherited; ++index) {
            void* handle = *reinterpret_cast<void**>(handles);
            uint8_t mode = *flags;
            if (handle != reinterpret_cast<void*>(0xffffffffu) && (mode & 1) != 0 &&
                ((mode & 8) != 0 || GetFileType(handle) != 0)) {
                OriginalIoEntry* entry = &dat_022532e0[index >> 5][index & 31];
                entry->handle = handle;
                entry->flags = mode;
                if (fun_005de970(&entry->section, 4000) == 0)
                    return -1;
                ++entry->section_initialized;
            }
            handles += 4;
            ++flags;
        }
    }
    for (int32_t index = 0; index < 3; ++index) {
        OriginalIoEntry* entry = &dat_022532e0[0][index];
        if (entry->handle == reinterpret_cast<void*>(0xffffffffu)) {
            entry->flags = 0x81;
            void* handle = GetStdHandle(-10 - index);
            if (handle == reinterpret_cast<void*>(0xffffffffu)) {
                entry->flags |= 0x40;
            } else {
                uint32_t type = GetFileType(handle);
                if (type == 0) {
                    entry->flags |= 0x40;
                } else {
                    entry->handle = handle;
                    if ((type & 0xff) == 2)
                        entry->flags |= 0x40;
                    else if ((type & 0xff) == 3)
                        entry->flags |= 8;
                    if (fun_005de970(&entry->section, 4000) == 0)
                        return -1;
                    ++entry->section_initialized;
                }
            }
        } else {
            entry->flags |= 0x80;
        }
    }
    SetHandleCount(static_cast<uint32_t>(dat_022532d4));
    return 0;
}
