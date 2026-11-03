#include "startup_filter.h"
#include "thread_data.h"

extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall)) UnhandledExceptionFilter(void*);
int32_t dat_0070eda8 = 3;
int32_t dat_0070edac = 7;
uint32_t dat_0070edb4 = 10;
}

namespace {
void*& exception_context(OriginalPerThreadData* data) {
    return *reinterpret_cast<void**>(data->undecoded_58);
}
uint32_t& floating_code(OriginalPerThreadData* data) {
    return *reinterpret_cast<uint32_t*>(data->undecoded_58 + 4);
}
int32_t signed_sum(int32_t first, int32_t second) {
    return static_cast<int32_t>(static_cast<uint32_t>(first) + static_cast<uint32_t>(second));
}
OriginalExceptionAction* add_entries(OriginalExceptionAction* table, uint32_t entries) {
    return reinterpret_cast<OriginalExceptionAction*>(reinterpret_cast<uint32_t>(table) +
                                                      entries * 12);
}
} // namespace

// Original5d8af4..5d8c57. Action1 ignores, action5 resets and handles, while
// other nonnull actions call the original one/two-argument signal convention.
extern "C" int32_t fun_005d8af4(uint32_t code, void* pointers) {
    auto* data = static_cast<OriginalPerThreadData*>(fun_005d2659());
    OriginalExceptionAction* table = data->exception_actions;
    OriginalExceptionAction* entry = table;
    const uint32_t count = dat_0070edb4;
    do {
        if (entry->exception_code == code)
            break;
        entry = add_entries(entry, 1);
    } while (reinterpret_cast<uint32_t>(entry) <
             reinterpret_cast<uint32_t>(add_entries(table, count)));
    if (reinterpret_cast<uint32_t>(entry) >=
            reinterpret_cast<uint32_t>(add_entries(table, count)) ||
        entry->exception_code != code)
        entry = nullptr;
    if (entry == nullptr || entry->action == nullptr)
        return UnhandledExceptionFilter(pointers);
    void* action = entry->action;
    if (action == reinterpret_cast<void*>(5)) {
        entry->action = nullptr;
        return 1;
    }
    if (action != reinterpret_cast<void*>(1)) {
        void* saved_context = exception_context(data);
        exception_context(data) = pointers;
        const int32_t signal = entry->signal_number;
        if (signal == 8) {
            int32_t index = dat_0070eda8;
            uint32_t offset = static_cast<uint32_t>(index) * 12;
            while (index < signed_sum(dat_0070eda8, dat_0070edac)) {
                auto* slot = reinterpret_cast<OriginalExceptionAction*>(
                    reinterpret_cast<uint32_t>(data->exception_actions) + offset);
                slot->action = nullptr;
                index = signed_sum(index, 1);
                offset += 12;
            }
            const uint32_t saved_floating_code = floating_code(data);
            switch (entry->exception_code) {
            case 0xc000008e:
                floating_code(data) = 0x83;
                break;
            case 0xc0000090:
                floating_code(data) = 0x81;
                break;
            case 0xc0000091:
                floating_code(data) = 0x84;
                break;
            case 0xc0000093:
                floating_code(data) = 0x85;
                break;
            case 0xc000008d:
                floating_code(data) = 0x82;
                break;
            case 0xc000008f:
                floating_code(data) = 0x86;
                break;
            case 0xc0000092:
                floating_code(data) = 0x8a;
                break;
            default:
                break;
            }
            reinterpret_cast<void(__attribute__((cdecl))*)(int32_t, uint32_t)>(action)(
                8, floating_code(data));
            floating_code(data) = saved_floating_code;
        } else {
            entry->action = nullptr;
            reinterpret_cast<void(__attribute__((cdecl))*)(int32_t)>(action)(signal);
        }
        exception_context(data) = saved_context;
    }
    return -1;
}
