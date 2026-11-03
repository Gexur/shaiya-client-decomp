#include "bigint.h"

// These are literal original branch thresholds and original dependencies. Larger
// recursive/FFT callees stay unresolved until their implementations are recovered.
extern "C" void fun_00586f70(uint32_t* output, const uint32_t* input, int32_t count) {
    if (count == 0)
        return;
    if (count < 58) {
        fun_0058b0e0(output, input, count);
        return;
    }
    if (count < 226) {
        uint32_t* scratch = static_cast<uint32_t*>(__builtin_alloca(uint32_t(count) * 8 + 0x100));
        fun_00587bb0(output, input, uint32_t(count), scratch);
        return;
    }
    if (count < 6780) {
        uint32_t bytes = (uint32_t(count) * 2 + 0x60) * 4;
        uint32_t* scratch = static_cast<uint32_t*>(dat_0070c0d0(bytes));
        fun_00588790(output, input, count, scratch);
        dat_0070c0d8(scratch, bytes);
        return;
    }
    fun_0058b030(output, input, count, input, count);
}

extern "C" void fun_00588b40(uint32_t* output, const uint32_t* left, const uint32_t* right,
                             int32_t count) {
    if (count < 22) {
        fun_0058b2f0(output, left, count, right, count);
        return;
    }
    if (count < 278) {
        uint32_t scratch[2472 / 4];
        fun_00587720(output, left, right, count, scratch);
        return;
    }
    if (count < 8340) {
        uint32_t bytes = (uint32_t(count) * 2 + 0x60) * 4;
        uint32_t* scratch = static_cast<uint32_t*>(dat_0070c0d0(bytes));
        fun_00587e90(output, left, right, count, scratch);
        dat_0070c0d8(scratch, bytes);
        return;
    }
    fun_0058b030(output, left, count, right, count);
}

extern "C" void fun_00586b90(uint32_t* remainder, const uint32_t* numerator,
                             int32_t numerator_count, const uint32_t* denominator,
                             int32_t denominator_count) {
    uint32_t bytes = (uint32_t(numerator_count) - uint32_t(denominator_count) + 1) * 4;
    uint32_t* quotient = static_cast<uint32_t*>(__builtin_alloca(bytes));
    fun_00588c30(quotient, remainder, 0, numerator, numerator_count, denominator,
                 denominator_count);
}
