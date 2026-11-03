#include "graphics/render_barycentric.h"
namespace {
template <unsigned Components>
float* interpolate(float* output, const volatile float* first, const volatile float* second,
                   const volatile float* third, float f, float g) {
    for (unsigned i = 0; i < Components; ++i) {
        const long double left =
            (static_cast<long double>(second[i]) - static_cast<long double>(first[i])) *
            static_cast<long double>(f);
        const long double right =
            (static_cast<long double>(third[i]) - static_cast<long double>(first[i])) *
            static_cast<long double>(g);
        const long double sum = (left + right) + static_cast<long double>(first[i]);
        static_cast<volatile float*>(output)[i] = static_cast<float>(sum);
    }
    return output;
}
} // namespace
extern "C" float* __attribute__((stdcall)) FUN_005e3f7b(float* output, const volatile float* first,
                                                        const volatile float* second,
                                                        const volatile float* third, float f,
                                                        float g) {
    return interpolate<2>(output, first, second, third, f, g);
}
extern "C" float* __attribute__((stdcall)) FUN_005e42fd(float* output, const volatile float* first,
                                                        const volatile float* second,
                                                        const volatile float* third, float f,
                                                        float g) {
    return interpolate<3>(output, first, second, third, f, g);
}
extern "C" float* __attribute__((stdcall)) FUN_005e4aa6(float* output, const volatile float* first,
                                                        const volatile float* second,
                                                        const volatile float* third, float f,
                                                        float g) {
    return interpolate<4>(output, first, second, third, f, g);
}
