#include "graphics/render_leaf_dispatch.h"
#include "startup/math_dispatch_state.h"
#include "graphics/render_matrix_constants.h"
#include "graphics/render_matrix_transpose.h"
#include "graphics/render_plane_point.h"
#include "graphics/render_barycentric.h"

namespace {
inline uint32_t word_at(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
inline uint32_t rounded_word(const uint32_t* pointer) {
    uint32_t value;
    __asm__ volatile("flds (%1)\n\tfstps %0" : "=m"(value) : "r"(pointer) : "memory");
    return value;
}
template <class Target> inline Target selected(unsigned slot) {
    return reinterpret_cast<Target>(word_at(&dat_0070f370.entries[slot]));
}
} // namespace

// The actual incoming slots remain live across the real initializer. This
// preserves callback changes to caller arguments before the subsequent reads.
extern "C" void* recovered_translation_dispatch(const uint32_t* incoming) {
    FUN_005fd1f8(1);
    const uint32_t z = rounded_word(incoming + 3);
    const uint32_t y = rounded_word(incoming + 2);
    const uint32_t x = rounded_word(incoming + 1);
    void* output = reinterpret_cast<void*>(word_at(incoming));
    return selected<decltype(&FUN_005e5755)>(27)(output, x, y, z);
}
extern "C" void* recovered_transpose_dispatch(const uint32_t* incoming) {
    FUN_005fd1f8(1);
    const void* input = reinterpret_cast<const void*>(word_at(incoming + 1));
    void* output = reinterpret_cast<void*>(word_at(incoming));
    return selected<decltype(&FUN_005e500f)>(38)(output, input);
}
extern "C" float* recovered_plane_point_dispatch(const uint32_t* incoming) {
    FUN_005fd1f8(1);
    const volatile float* normal = reinterpret_cast<const volatile float*>(word_at(incoming + 2));
    const volatile float* point = reinterpret_cast<const volatile float*>(word_at(incoming + 1));
    float* output = reinterpret_cast<float*>(word_at(incoming));
    return selected<decltype(&FUN_005e7126)>(13)(output, point, normal);
}
extern "C" float* recovered_barycentric_dispatch(unsigned slot, const uint32_t* incoming) {
    FUN_005fd1f8(1);
    // The original rounds/quietens g, then f, into copied outgoing slots.
    float g, f;
    __asm__ volatile("flds (%1)\n\tfstps %0" : "=m"(g) : "r"(incoming + 5) : "memory");
    __asm__ volatile("flds (%1)\n\tfstps %0" : "=m"(f) : "r"(incoming + 4) : "memory");
    const volatile float* third = reinterpret_cast<const volatile float*>(word_at(incoming + 3));
    const volatile float* second = reinterpret_cast<const volatile float*>(word_at(incoming + 2));
    const volatile float* first = reinterpret_cast<const volatile float*>(word_at(incoming + 1));
    float* output = reinterpret_cast<float*>(word_at(incoming));
    return selected<decltype(&FUN_005e3f7b)>(slot)(output, first, second, third, f, g);
}

// Textual entry adapters expose the original argument slots to the C++ body;
// the calculations and selected table calls above are ordinary source code.
extern "C" __attribute__((naked)) void* __attribute__((stdcall)) FUN_005e571f(void*, uint32_t,
                                                                              uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_translation_dispatch\n\taddl $4,%esp\n\tretl $16");
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall)) FUN_005e4ff6(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_transpose_dispatch\n\taddl $4,%esp\n\tretl $8");
}
extern "C" __attribute__((naked)) float* __attribute__((stdcall))
FUN_005e7113(float*, const volatile float*, const volatile float*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_plane_point_dispatch\n\taddl $4,%esp\n\tretl $12");
}
#define BARYCENTRIC_DISPATCH(address, slot)                                                        \
    extern "C" __attribute__((naked)) float* __attribute__((stdcall)) FUN_##address(               \
        float*, const volatile float*, const volatile float*, const volatile float*, float,        \
        float) {                                                                                   \
        __asm__ volatile("leal 4(%esp),%eax\n\tpushl %eax\n\tpushl $" #slot                        \
                         "\n\tcalll _recovered_barycentric_dispatch\n\taddl $8,%esp\n\tretl $24"); \
    }
BARYCENTRIC_DISPATCH(005e3f4a, 49)
BARYCENTRIC_DISPATCH(005e42cc, 52)
BARYCENTRIC_DISPATCH(005e4a75, 55)
