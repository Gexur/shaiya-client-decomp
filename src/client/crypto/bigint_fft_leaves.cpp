#include "bigint.h"

namespace {
// Original signed32-bit threshold rows at006CD5D8, selected by the caller's
// same-input-square flag(0/1). All32 entries, including zero tails, are checked
// against original data in the differential harness.
constexpr int32_t fft_thresholds[2][16] = {
    {1112, 2224, 4448, 8896, 26688, 80064, 0},
    {904, 1808, 3616, 7232, 21696, 65088, 0},
};
} // namespace

extern "C" int32_t fun_00589960(int32_t count, int32_t square_selector) {
    const int32_t* thresholds = fft_thresholds[square_selector];
    int32_t index = 0;
    while (thresholds[index] != 0) {
        if (count < thresholds[index])
            return index + 4;
        ++index;
    }
    if (index != 0 && int32_t(uint32_t(thresholds[index - 1]) * 4) <= count)
        return index + 5;
    return index + 4;
}

extern "C" int32_t fun_005899c0(int32_t count, uint32_t shift) {
    int32_t bits = int32_t(uint32_t(count) << 5);
    int32_t quantum = int32_t(1u << (shift & 31));
    if (bits % quantum != 0)
        bits = int32_t(uint32_t(bits / quantum + 1) * uint32_t(quantum));
    int32_t quotient = bits / quantum;
    if (quotient % 32 != 0)
        bits = int32_t(uint32_t(quotient / 32 + 1) * uint32_t(quantum) * 32);
    return bits / 32;
}

extern "C" void fun_00589de0(uint32_t** levels, int32_t depth) {
    levels[0][0] = 0;
    int32_t width = 2;
    for (int32_t level = 0; level < depth; ++level) {
        int32_t half = width / 2;
        for (int32_t i = 0; i < half; ++i) {
            levels[level + 1][i] = levels[level][i] << 1;
            levels[level + 1][i + half] = levels[level + 1][i] + 1;
        }
        width = int32_t(uint32_t(width) * 2);
    }
}
