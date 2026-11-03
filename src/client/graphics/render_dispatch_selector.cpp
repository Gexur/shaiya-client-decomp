#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "startup/math_dispatch_state.h"
#include "graphics/render_allocator_check.h"
#include "graphics/render_dispatch_config.h"
#include "graphics/render_backend_patches.h"
#include "graphics/render_cpu_probe.h"
#include "graphics/render_sse_patch.h"

extern "C" {
// Actual selector5fd293 captures the import slot's target once. Addressing the
// SDK function symbol can capture an import-library trampoline instead, which
// would reload the slot later. Bind this real IAT symbol explicitly.
extern BOOL(WINAPI* feature_import_005fd293)(DWORD) __asm__("__imp__IsProcessorFeaturePresent@4");
}
namespace {
struct HardwareWord {
    unsigned char bytes[4];
};
uint32_t hardware_word(const unsigned char* bytes) {
    uint32_t value;
    __asm__ __volatile__("movl %1,%0"
                         : "=r"(value)
                         : "m"(*reinterpret_cast<const HardwareWord*>(bytes)));
    return value;
}
} // namespace

extern "C" int32_t __attribute__((stdcall)) FUN_005fd1f8(int32_t request) {
    FUN_005e9bf2();
    if (request == 0) {
        dat_0070ff04 = 0xffff;
        dat_0070f370 = dat_0070f498;
    } else if (dat_0070ff04 == 0xffff) {
        dat_0070ff04 = 0;
        dat_0070f370 = dat_0070f498;
        FUN_0064f62a(&dat_0070f370);
        if (FUN_005fd01e(4, "DisablePSGP", &request, 4) == 0)
            request = 0;
        alignas(uint32_t) unsigned char override_value[4];
        if (FUN_005fd01e(4, "DisableD3DXPSGP", override_value, 4) != 0)
            request = static_cast<int32_t>(hardware_word(override_value));
        if (request != 1) {
            auto query = feature_import_005fd293;
            if (request == 2 || query(7) == FALSE) {
                if ((FUN_005fd157() & 8) != 0) {
                    FUN_006516d0(&dat_0070f370);
                    dat_0070ff04 = 2;
                } else if (query(6) != FALSE) {
                    FUN_0065155d(&dat_0070f370);
                    dat_0070ff04 = 3;
                }
            } else {
                FUN_0065191f(&dat_0070f370);
                dat_0070ff04 = 1;
            }
        }
    }
    return static_cast<int32_t>(dat_0070ff04);
}
