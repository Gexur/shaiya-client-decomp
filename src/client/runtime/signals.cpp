#include "signals.h"
#include "locks.h"
extern "C" {
void* dat_0224f224 = nullptr;
void* dat_0224f228 = nullptr;
void* dat_0224f22c = nullptr;
void* dat_0224f230 = nullptr;
}
extern "C" OriginalExceptionAction* fun_005dbe5c(OriginalExceptionAction* table, int32_t signal) {
    auto* entry = table;
    const uint32_t end = reinterpret_cast<uint32_t>(table) + dat_0070edb4 * 12u;
    do {
        if (entry->signal_number == signal)
            break;
        entry = reinterpret_cast<OriginalExceptionAction*>(reinterpret_cast<uint32_t>(entry) + 12u);
    } while (reinterpret_cast<uint32_t>(entry) < end);
    if (reinterpret_cast<uint32_t>(entry) >= end || entry->signal_number != signal)
        return nullptr;
    return entry;
}
extern "C" void fun_005dbfc5(int32_t global_action) {
    if (global_action)
        fun_005d64e6(0);
}
extern "C" int32_t raise(int32_t signal) {
    return fun_005dbe8a(signal);
}

extern "C" void recovered_signal_reset(int32_t signal, OriginalPerThreadData* data, void** slot,
                                       RecoveredSignalContext* saved) {
    if (signal == 4 || signal == 8 || signal == 11) {
        saved->exception_context = *reinterpret_cast<void**>(data->undecoded_58);
        *reinterpret_cast<void**>(data->undecoded_58) = nullptr;
        if (signal == 8) {
            saved->floating_code = *reinterpret_cast<uint32_t*>(data->undecoded_58 + 4);
            *reinterpret_cast<uint32_t*>(data->undecoded_58 + 4) = 0x8c;
        }
    }
    if (signal == 8) {
        for (int32_t index = dat_0070eda8;
             index < int32_t(uint32_t(dat_0070eda8) + uint32_t(dat_0070edac)); ++index) {
            auto* entry = reinterpret_cast<OriginalExceptionAction*>(
                reinterpret_cast<uint32_t>(data->exception_actions) + uint32_t(index) * 12u);
            entry->action = nullptr;
        }
    } else
        *slot = nullptr;
}
