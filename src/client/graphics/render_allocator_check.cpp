#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "graphics/render_allocator_check.h"
#include "runtime/allocations.h"

extern "C" uint32_t dat_0224f35c = 0;
extern "C" void __cdecl FUN_005e9bf2() {
    if (dat_0224f35c != 0)
        return;
    dat_0224f35c = 1;
    void* first = fun_005cc96d(0);
    void* second = fun_005cc96d(0);
    const bool failure = first == nullptr || second == nullptr || first == second;
    if (first != nullptr)
        fun_005cc620(first);
    if (second != nullptr && second != first)
        fun_005cc620(second);
    fun_005cc620(nullptr);
    if (failure) {
        auto debug = OutputDebugStringA;
        debug(
            "D3DX: (WARN) Overloaded ::new and ::delete operators do not conform to C++ standards:\r\n");
        debug(
            "D3DX: (WARN) An allocation of zero bytes should return a unique non-null pointer to at\r\n");
        debug(
            "D3DX: (WARN) least zero bytes. Deletion of a null pointer should quietly do nothing.\r\n");
        debug("D3DX: (WARN) D3DX relies upon this behavior.\r\n");
    }
}
