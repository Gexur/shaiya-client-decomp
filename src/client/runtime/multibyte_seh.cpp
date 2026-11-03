#include "multibyte.h"
#include "thread_data.h"
#include "heap.h"

extern "C" {
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetOEMCP();
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetACP();
}
namespace {
// These genuine operations are outlined to retain active protected-call
// intervals around faulting memory accesses on Clang's x86 SEH target.
__declspec(noinline) int32_t* refresh_thread_data() {
    auto* data = static_cast<OriginalPerThreadData*>(fun_005d2659());
    int32_t* current = data->reference_counted_60;
    if (current != dat_022533e4) {
        if (current != nullptr) {
            *reinterpret_cast<uint32_t*>(current) -= 1;
            if (*current == 0)
                fun_005cfaf0(current);
        }
        data->reference_counted_60 = dat_022533e4;
        current = dat_022533e4;
        *reinterpret_cast<uint32_t*>(current) += 1;
    }
    return current;
}
__declspec(noinline) int32_t change_code_page(uint32_t code_page) {
    int32_t result = -1;
    dat_0224ee64 = 0;
    if (code_page == 0xfffffffeu) {
        dat_0224ee64 = 1;
        code_page = GetOEMCP();
    } else if (code_page == 0xfffffffdu) {
        dat_0224ee64 = 1;
        code_page = GetACP();
    } else if (code_page == 0xfffffffcu) {
        dat_0224ee64 = 1;
        code_page = dat_0224f258;
    }
    if (code_page == dat_02253504)
        return 0;
    auto* storage = reinterpret_cast<OriginalMultibyteData*>(dat_022533e4);
    if (storage == nullptr || storage->references != 0)
        storage = static_cast<OriginalMultibyteData*>(fun_005cfade(0x220));
    if (storage != nullptr) {
        result = fun_005d3206(code_page);
        if (result == 0) {
            storage->references = 0;
            storage->code_page = dat_02253504;
            storage->multibyte = dat_022533e8;
            storage->locale = dat_022533e0;
            for (uint32_t i = 0; i < 5; ++i)
                storage->information[i] = dat_02253510[i];
            for (uint32_t i = 0; i < 257; ++i)
                storage->classification[i] = dat_02253400[i];
            for (uint32_t i = 0; i < 256; ++i)
                storage->case_map[i] = dat_02253520[i];
            dat_022533e4 = reinterpret_cast<int32_t*>(storage);
        }
    }
    if (result == -1 && storage != reinterpret_cast<OriginalMultibyteData*>(dat_022533e4))
        fun_005cfaf0(storage);
    return result;
}
} // namespace
extern "C" void fun_005d31fd() {
    fun_005d64e6(13);
}
extern "C" void fun_005d34e1() {
    fun_005d64e6(13);
}
extern "C" int32_t* fun_005d3197() {
    fun_005d659b(13);
    __try {
        return refresh_thread_data();
    } __finally {
        fun_005d31fd();
    }
}
extern "C" int32_t fun_005d339a(uint32_t code_page) {
    fun_005d659b(13);
    __try {
        return change_code_page(code_page);
    } __finally {
        fun_005d34e1();
    }
}
