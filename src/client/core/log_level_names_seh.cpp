#include "log_level_names.h"
#include "../runtime/exit_registry.h"

namespace {
using shaiya::startup::String_00405710;
struct InitializationUnwind {
    uint32_t mask;
    bool active = true;
    ~InitializationUnwind() noexcept(false) {
        if (active)
            dat_0224e86c = dat_0224e86c & ~mask;
    }
};

// The eight low-bit cases read a byte, then OR the live DWORD in memory.
// The remaining cases read a DWORD and store that cached value with its bit
// added. Keep those distinct original accesses, including their interleaving.
template <uint32_t Mask> bool needs_initialization() {
    if constexpr (Mask < 0x100) {
        if ((*reinterpret_cast<volatile unsigned char*>(&dat_0224e86c) & Mask) != 0)
            return false;
        __asm__ volatile("orl %1,%0" : "+m"(dat_0224e86c) : "r"(Mask) : "cc", "memory");
    } else {
        const uint32_t flags = dat_0224e86c;
        if ((flags & Mask) != 0)
            return false;
        dat_0224e86c = flags | Mask;
    }
    return true;
}

__declspec(noinline) void construct_name(String_00405710* value, const char* text) {
    FUN_00405800(value, text);
}
__declspec(noinline) void register_name(OriginalExitCallback callback) {
    (void)fun_005ccf60(callback);
}

template <uint32_t Mask>
String_00405710* select_name(String_00405710* value, const char* text,
                             OriginalExitCallback callback) {
    if (needs_initialization<Mask>()) {
        // FuncInfo00704a3c has one action per case. It clears only this bit
        // after an exception from either call; it does not destroy the String.
        InitializationUnwind unwind{Mask};
        construct_name(value, text);
        register_name(callback);
        unwind.active = false;
    }
    return value;
}
} // namespace

extern "C" shaiya::startup::String_00405710* fun_005b9340(uint32_t code) {
    switch (code) {
    case 0:
        return select_name<0x001>(&dat_0224e850, "NONE  ", fun_006baae0);
    case 1:
        return select_name<0x002>(&dat_0224e834, "ERROR ", fun_006baab0);
    case 2:
        return select_name<0x004>(&dat_0224e818, "WARN  ", fun_006baa80);
    case 4:
        return select_name<0x008>(&dat_0224e7fc, "TRACE ", fun_006baa50);
    case 8:
        return select_name<0x010>(&dat_0224e7e0, "INFO  ", fun_006baa20);
    case 0x10:
        return select_name<0x020>(&dat_0224e7c4, "DUMP  ", fun_006ba9f0);
    case 0x20:
        return select_name<0x040>(&dat_0224e78c, "MEMORY", fun_006ba9c0);
    case 0x40:
        return select_name<0x080>(&dat_0224e7a8, "NET   ", fun_006ba990);
    case 0x80:
        return select_name<0x100>(&dat_0224e770, "LOG   ", fun_006ba960);
    case 0x100:
        return select_name<0x200>(&dat_0224e71c, "DEBUG ", fun_006ba930);
    case 0x200:
        return select_name<0x400>(&dat_0224e738, "SCRIPT", fun_006ba900);
    default:
        return select_name<0x800>(&dat_0224e754, "USER  ", fun_006ba8d0);
    }
}
