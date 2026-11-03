#include "graphics/surface/surface_area_weights.h"
#include "runtime/x87_convert64.h"
#include "runtime/allocations.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void zero(volatile float& v) {
    __asm__ volatile("fldz\n\tfstps %0" : "=m"(v)::"st", "memory");
}
long double signed_word(u32 value) {
    long double result;
    __asm__ volatile("fildl %1" : "=t"(result) : "m"(value));
    return result;
}
long double unsigned_word(u32 value) {
    const volatile long double first = signed_word(value);
    if (value & 0x80000000u) {
        const volatile long double corrected = first + 4294967296.0L;
        return corrected;
    }
    return first;
}
u32 truncate(const volatile long double& value) {
    u32 low, high;
    const auto target = &FUN_005d0bc4;
    __asm__ volatile("fldt %2\n\tcalll *%3"
                     : "=a"(low), "=d"(high)
                     : "m"(value), "r"(target)
                     : "ecx", "st", "memory", "cc");
    return low;
}
uint16_t compare(const volatile long double& a, const volatile long double& b) {
    uint16_t status;
    __asm__ volatile("fldt %2\n\tfldt %1\n\tfcompp\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "m"(a), "m"(b)
                     : "st", "st(1)", "memory");
    return status;
}
bool less(const volatile long double& a, const volatile long double& b) {
    return (compare(a, b) & 0x0500) == 0x0100;
}
bool greater(const volatile long double& a, const volatile long double& b) {
    return (compare(a, b) & 0x4100) == 0;
}
bool signed_less(u32 a, u32 b) {
    return (a ^ 0x80000000u) < (b ^ 0x80000000u);
}
} // namespace
// Draft complete original5eca09..5eccc7. This remains outside production until
// it is compared through the genuine6aa710 floor family and actual5d0bc4.
extern "C" void* recovered_005eca09(const uint32_t* arguments) {
    const u32 slots = reinterpret_cast<uintptr_t>(arguments), first_count = word(slots);
    if (!first_count)
        return nullptr;
    const u32 second_count = word(slots + 4);
    if (!second_count)
        return nullptr;
    const volatile long double second_extended = unsigned_word(second_count);
    volatile float second_float = static_cast<float>(second_extended);
    const volatile long double first_extended = unsigned_word(first_count);
    volatile float first_float = static_cast<float>(first_extended);
    const volatile long double numerator = static_cast<long double>(second_float);
    const u32 flag = word(slots + 8) != 0;
    const volatile long double ratio = numerator / first_extended;
    volatile float ratio_float = static_cast<float>(ratio);
    const volatile long double reciprocal_half = 0.5L / ratio;
    volatile float half_float = static_cast<float>(reciprocal_half);
    u32 bytes = 16, index = 0;
    const volatile long double flag_extended = unsigned_word(flag);
    do {
        const volatile long double i = unsigned_word(index);
        const volatile long double before = i - 0.5L;
        const volatile long double low = before * ratio;
        const volatile long double high = low + ratio;
        const volatile long double difference = high - low;
        const volatile long double flagged = difference + flag_extended;
        const volatile long double size = flagged + 1.0L;
        const u32 integer = truncate(size);
        bytes += 12 + (integer << 4);
    } while (++index < first_count);
    void* allocation = fun_005cc96d(bytes);
    if (!allocation)
        return nullptr;
    const u32 result = reinterpret_cast<uintptr_t>(allocation);
    u32 previous = 0, outer = 0, offset = 4;
    volatile float accumulated;
    zero(accumulated);
    if (word(slots))
        do {
            u32 pass = 0;
            const volatile long double outer_extended = unsigned_word(outer);
            volatile float outer_float = static_cast<float>(outer_extended);
            const u32 record = result + offset, record_offset = offset;
            offset += 4;
            do {
                const volatile long double pass_extended = unsigned_word(pass);
                const bool clamp = word(slots + 8) == 0;
                const volatile long double shifted =
                    pass_extended + static_cast<long double>(outer_float);
                const volatile long double position = shifted - 0.5L;
                volatile float position_float = static_cast<float>(position);
                const volatile long double scaled =
                    position * static_cast<long double>(ratio_float);
                volatile float lower_float = static_cast<float>(scaled);
                const volatile long double following =
                    static_cast<long double>(ratio_float) + scaled;
                volatile float upper_float = static_cast<float>(following);
                volatile long double lower_extended = scaled;
                if (clamp) {
                    const volatile long double empty = 0.0L;
                    if (less(lower_extended, empty)) {
                        lower_extended = 0.0L;
                        lower_float = 0.0f;
                    }
                    const volatile long double upper = static_cast<long double>(upper_float),
                                               maximum = static_cast<long double>(second_float);
                    if (greater(upper, maximum))
                        upper_float = second_float;
                }
                volatile float floor_argument = static_cast<float>(lower_extended);
                const volatile long double floor_value =
                    FUN_005ec9e8(word(reinterpret_cast<uintptr_t>(&floor_argument)));
                u32 current = truncate(floor_value);
                volatile long double running = signed_word(current);
                const volatile long double upper_bound = static_cast<long double>(upper_float);
                if (less(running, upper_bound)) {
                    u32 difference = current - word(slots + 4);
                    do {
                        const volatile long double next_extended = 1.0L + running;
                        volatile float next_float = static_cast<float>(next_extended);
                        u32 candidate;
                        if (current & 0x80000000u)
                            candidate = current + word(slots + 4);
                        else
                            candidate =
                                signed_less(current, word(slots + 4)) ? current : difference;
                        if (candidate != previous) {
                            const volatile long double old = static_cast<long double>(accumulated),
                                                       epsilon = 0x1.4f8b58p-17L;
                            if (greater(old, epsilon)) {
                                put(result + offset, previous);
                                put(result + offset + 4,
                                    word(reinterpret_cast<uintptr_t>(&accumulated)));
                                offset += 8;
                            }
                            zero(accumulated);
                            previous = candidate;
                        }
                        const volatile long double lower = static_cast<long double>(lower_float);
                        if (less(running, lower))
                            running = lower;
                        const volatile long double next = static_cast<long double>(next_float),
                                                   upper = static_cast<long double>(upper_float);
                        if (greater(next, upper))
                            next_float = upper_float;
                        volatile long double weight;
                        bool formula = true;
                        if (word(slots + 8) == 0) {
                            const volatile long double position_copy =
                                                           static_cast<long double>(position_float),
                                                       empty = 0.0L;
                            if (less(position_copy, empty)) {
                                weight = 1.0L;
                                formula = false;
                            } else {
                                const volatile long double position_plus_one =
                                    static_cast<long double>(position_float) + 1.0L;
                                const volatile long double limit =
                                    static_cast<long double>(first_float);
                                // Original TEST AH,1: unordered retains the formula route too.
                                if (!(compare(position_plus_one, limit) & 0x0100)) {
                                    weight = 0.0L;
                                    formula = false;
                                }
                            }
                        }
                        if (formula) {
                            const volatile long double sum =
                                static_cast<long double>(next_float) + running;
                            const volatile long double scaled_sum =
                                sum * static_cast<long double>(half_float);
                            weight = scaled_sum - static_cast<long double>(position_float);
                        }
                        if (pass) {
                            const volatile long double complement = 1.0L - weight;
                            weight = complement;
                        }
                        const volatile long double span =
                            static_cast<long double>(next_float) - running;
                        ++current;
                        ++difference;
                        const volatile long double weighted = span * weight;
                        const volatile long double added =
                            weighted + static_cast<long double>(accumulated);
                        accumulated = static_cast<float>(added);
                        running = signed_word(current);
                    } while (less(running, upper_bound));
                }
            } while (++pass < 2);
            const volatile long double total = static_cast<long double>(accumulated),
                                       epsilon = 0x1.4f8b58p-17L;
            if (greater(total, epsilon)) {
                put(result + offset, previous);
                put(result + offset + 4, word(reinterpret_cast<uintptr_t>(&accumulated)));
                offset += 8;
            }
            zero(accumulated);
            put(record, offset - record_offset);
            ++outer;
        } while (outer < word(slots));
    put(result, offset);
    return allocation;
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005eca09(uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005eca09\n\taddl $4,%esp\n\tretl $12");
}
