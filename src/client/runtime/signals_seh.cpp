#include "signals.h"
#include "locks.h"
#include "crt_exit.h"

extern "C" int32_t fun_005dbe8a(int32_t signal) {
    void** slot;
    OriginalPerThreadData* data = nullptr; // normalized unused operand for global actions
    int32_t global = 0;
    switch (signal) {
    case 2:
        slot = &dat_0224f224;
        global = 1;
        break;
    case 15:
        slot = &dat_0224f230;
        global = 1;
        break;
    case 21:
        slot = &dat_0224f228;
        global = 1;
        break;
    case 22:
        slot = &dat_0224f22c;
        global = 1;
        break;
    case 4:
    case 8:
    case 11:
        data = static_cast<OriginalPerThreadData*>(fun_005d2659());
        slot = &fun_005dbe5c(data->exception_actions, signal)->action;
        break;
    default:
        return -1;
    }
    void* const action = *slot;
    if (action == reinterpret_cast<void*>(1))
        return 0;
    if (!action)
        fun_005ce131(3);
    if (global)
        fun_005d659b(0);
    RecoveredSignalContext saved;
    __try {
        recovered_signal_reset(signal, data, slot, &saved);
    } __finally {
        fun_005dbfc5(global);
    }
    if (signal == 8) {
        reinterpret_cast<void(__attribute__((cdecl))*)(int32_t, uint32_t)>(action)(
            8, *reinterpret_cast<uint32_t*>(data->undecoded_58 + 4));
    } else
        reinterpret_cast<void(__attribute__((cdecl))*)(int32_t)>(action)(signal);
    // Original callback lies outside the protected region. A callback exception
    // therefore leaves these two PTD fields changed; no restoration is invented.
    if (signal == 4 || signal == 8 || signal == 11) {
        *reinterpret_cast<void**>(data->undecoded_58) = saved.exception_context;
        if (signal == 8)
            *reinterpret_cast<uint32_t*>(data->undecoded_58 + 4) = saved.floating_code;
    }
    return 0;
}
