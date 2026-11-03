#include "thread_data.h"
#include "locks.h"
#include "heap.h"

namespace {
int32_t*& reference_at(void* storage, uint32_t offset) {
    return *reinterpret_cast<int32_t**>(static_cast<uint8_t*>(storage) + offset);
}
int32_t& count_at(void* storage, uint32_t offset) {
    return *reinterpret_cast<int32_t*>(static_cast<uint8_t*>(storage) + offset);
}
// Clang's x86 SEH lowering drops the active scope around direct memory
// accesses, even with -fasync-exceptions. These two private outlines preserve
// the original protected operations behind real call boundaries. Native AV
// tests verify both resulting finally paths; these are compiler integration
// helpers, not additional recovered original functions.
__declspec(noinline) void release_reference(OriginalPerThreadData* data) {
    int32_t* reference = data->reference_counted_60;
    if (reference != nullptr) {
        *reinterpret_cast<uint32_t*>(reference) -= 1;
        if (*reference == 0 && reference != dat_022533e4)
            fun_005cfaf0(reference);
    }
}
__declspec(noinline) void release_locale(OriginalPerThreadData* data) {
    void* locale = data->locale_64;
    if (locale != nullptr) {
        count_at(locale, 0) = static_cast<int32_t>(static_cast<uint32_t>(count_at(locale, 0)) - 1);
        const uint32_t offsets[] = {0x2cu, 0x34u, 0x30u, 0x40u};
        for (uint32_t offset : offsets) {
            int32_t* reference = reference_at(locale, offset);
            if (reference != nullptr)
                *reinterpret_cast<uint32_t*>(reference) -= 1;
        }
        int32_t* category = reference_at(locale, 0x4c);
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(category) + 0xb4) -= 1;
        if (locale != dat_0070e67c && locale != &dat_0070e628 && count_at(locale, 0) == 0) {
            fun_005d4d7b(locale);
        }
    }
}
} // namespace

extern "C" void __attribute__((stdcall)) fun_005d26ca(void* pointer) {
    auto* data = static_cast<OriginalPerThreadData*>(pointer);
    if (data == nullptr)
        return;
    if (data->allocation_24 != nullptr)
        fun_005cfaf0(data->allocation_24);
    if (data->allocation_2c != nullptr)
        fun_005cfaf0(data->allocation_2c);
    if (data->allocation_34 != nullptr)
        fun_005cfaf0(data->allocation_34);
    if (data->allocation_3c != nullptr)
        fun_005cfaf0(data->allocation_3c);
    if (data->allocation_44 != nullptr)
        fun_005cfaf0(data->allocation_44);
    if (data->allocation_48 != nullptr)
        fun_005cfaf0(data->allocation_48);
    if (data->exception_actions != dat_0070ed30)
        fun_005cfaf0(data->exception_actions);
    fun_005d659b(13);
    __try {
        release_reference(data);
    } __finally {
        fun_005d27fc();
    }
    fun_005d659b(12);
    __try {
        release_locale(data);
    } __finally {
        fun_005d2808();
    }
    fun_005cfaf0(data);
}
