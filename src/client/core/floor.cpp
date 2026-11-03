#include "floor.h"
#include "floor_data.h"
#include "floor_errors.h"
#include "core/fp_exception_support.h"
#include "core/math_error.h"
#include "core/x87_pow_special.h"
extern "C" const uint64_t dat_006cf0a0;
namespace {
using u32 = uint32_t;
using V = double __attribute__((vector_size(16)));
struct B8 {
    unsigned char bytes[8];
};
struct B16 {
    unsigned char bytes[16];
};
#define SIMD __attribute__((target("sse2"), always_inline)) inline
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
SIMD V input(u32 p) {
    V v;
    __asm__ volatile("movq %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return v;
}
SIMD V table(const OriginalFloorVector& v) {
    V r;
    __asm__ volatile("movapd %1,%0" : "=x"(r) : "m"(v) : "memory");
    return r;
}
SIMD V right52(V v) {
    __asm__ volatile("psrlq $52,%0" : "+x"(v));
    return v;
}
SIMD u32 low(V v) {
    u32 r;
    __asm__ volatile("movd %1,%0" : "=r"(r) : "x"(v));
    return r;
}
SIMD V and_table(V v, const OriginalFloorVector& t) {
    __asm__ volatile("andpd %1,%0" : "+x"(v) : "m"(t) : "memory");
    return v;
}
SIMD V or_table(V v, const OriginalFloorVector& t) {
    __asm__ volatile("orpd %1,%0" : "+x"(v) : "m"(t) : "memory");
    return v;
}
SIMD V subtract_words(V a, V b) {
    __asm__ volatile("psubd %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V right(V a, V count) {
    __asm__ volatile("psrlq %1,%0" : "+x"(a) : "x"(count));
    return a;
}
SIMD V left(V a, V count) {
    __asm__ volatile("psllq %1,%0" : "+x"(a) : "x"(count));
    return a;
}
SIMD V less(V a, V b) {
    __asm__ volatile("cmpltpd %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V less_table(V a, const OriginalFloorVector& t) {
    __asm__ volatile("cmpltpd %1,%0" : "+x"(a) : "m"(t) : "memory");
    return a;
}
SIMD V subtract_low(V a, V b) {
    __asm__ volatile("subsd %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD void output(u32 p, V v) {
    __asm__ volatile("movq %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "x"(v) : "memory");
}
SIMD bool unordered(V v) {
    unsigned char result;
    __asm__ volatile("ucomisd %1,%1\n\tsetp %0" : "=qm"(result) : "x"(v) : "cc");
    return result != 0;
}
long double load(u32 p) {
    long double v;
    __asm__ volatile("fldl (%1)" : "=t"(v) : "r"(p) : "memory");
    return v;
}
long double zero() {
    long double v;
    __asm__ volatile("fldz" : "=t"(v));
    return v;
}
void quiet(double& out, u32 p) {
    __asm__ volatile("fldl (%1)\n\tfstpl %0" : "=m"(out) : "r"(p) : "st", "memory");
}
void add_one(double& out, u32 p) {
    __asm__ volatile("fldl (%1)\n\tfaddl %2\n\tfstpl %0"
                     : "=m"(out)
                     : "r"(p), "m"(dat_006cf0a0)
                     : "st", "memory");
}
void bits(u32* out, const double& v) {
    out[0] = word(reinterpret_cast<u32>(&v));
    out[1] = word(reinterpret_cast<u32>(&v) + 4);
}
// The actual C-call arguments are raw stored F64 words, not a host operation.
u32 classify(const double& v) {
    const double* p = &v;
    u32 result;
    __asm__ volatile("pushl 4(%1)\n\tpushl (%1)\n\tcalll _FUN_005d8053\n\taddl $8,%%esp"
                     : "=a"(result)
                     : "r"(p)
                     : "ecx", "edx", "cc", "memory");
    return result;
}
void round_stored(double& out, const double& v) {
    const double* p = &v;
    __asm__ volatile("pushl 4(%1)\n\tpushl (%1)\n\tcalll _FUN_005decc1\n\taddl $8,%%esp\n\tfstpl %0"
                     : "=m"(out)
                     : "r"(p)
                     : "eax", "ecx", "edx", "st", "memory", "cc");
}
bool different(u32 actual, const double& result) {
    unsigned char parity;
    __asm__ volatile("fldl (%1)\n\tfldl %2\n\tfucompp\n\tfnstsw %%ax\n\ttestb $0x44,%%ah\n\tsetp %0"
                     : "=qm"(parity)
                     : "r"(actual), "m"(result)
                     : "eax", "st", "memory", "cc");
    return parity != 0;
}
long double qnan(const double& arg, u32 control) {
    u32 words[4];
    words[0] = 0xb;
    bits(words + 1, arg);
    words[3] = control;
    long double answer;
    __asm__ volatile(
        "pushl 12(%1)\n\tpushl 8(%1)\n\tpushl 4(%1)\n\tpushl (%1)\n\tcalll _FUN_005d8726\n\taddl $16,%%esp"
        : "=t"(answer)
        : "r"(words)
        : "eax", "ecx", "edx", "memory", "cc");
    return answer;
}
long double error(u32 flags, const double& arg, const double& result, u32 control) {
    u32 words[7];
    words[0] = flags;
    words[1] = 0xb;
    bits(words + 2, arg);
    bits(words + 4, result);
    words[6] = control;
    long double answer;
    __asm__ volatile(
        "pushl 24(%1)\n\tpushl 20(%1)\n\tpushl 16(%1)\n\tpushl 12(%1)\n\tpushl 8(%1)\n\tpushl 4(%1)\n\tpushl (%1)\n\tcalll _FUN_005d87d8\n\taddl $28,%%esp"
        : "=t"(answer)
        : "r"(words)
        : "eax", "ecx", "edx", "memory", "cc");
    return answer;
}
} // namespace

// Complete6aa750..6aa831. The packed shifts and comparisons are the actual
// instruction-derived algorithm, including the negative exceptional compare.
extern "C" __attribute__((target("sse2"))) long double
recovered_006aa750(unsigned char* arguments) {
    const u32 arg = reinterpret_cast<u32>(arguments);
    const V original = input(arg); // 6aa750
    V count = table(dat_006f7430); // 6aa756
    V shifted = original;
    V exponent = right52(original);
    const u32 sign_and_exponent = low(exponent); // 6aa76b
    exponent = and_table(exponent, dat_006f7460);
    count = subtract_words(count, exponent);
    shifted = right(shifted, count);
    if ((sign_and_exponent & 0x800) == 0) {
        if (sign_and_exponent < 0x3ff)
            return zero(); // 6aa80a
        shifted = left(shifted, count);
        if (sign_and_exponent <= 0x432) {
            output(arg, shifted);
            return load(arg);
        }
    } else {
        V current = input(arg); // fresh6aa7d2 read
        shifted = left(shifted, count);
        V small = current;
        current = less(current, shifted); // also executed for NaNs
        if (sign_and_exponent < 0xbff) {
            small = less_table(small, dat_006f7450);
            small = or_table(small, dat_006f7450); // distinct actual read
            small = and_table(small, dat_006f7440);
            output(arg, small);
            return load(arg);
        }
        if (sign_and_exponent <= 0xc32) {
            current = and_table(current, dat_006f7420);
            shifted = subtract_low(shifted, current);
            output(arg, shifted);
            return load(arg);
        }
    }
    if (unordered(original))
        FUN_005d7bd8(reinterpret_cast<double*>(arg), reinterpret_cast<double*>(arg),
                     reinterpret_cast<double*>(arg), 0x3ed);
    return load(arg);
}

// Complete6ab0bf..6ab192. The four-byte classification load at actual arg+6
// intentionally includes two adjacent caller bytes; only its low WORD tests
// the exponent. This is an observed read extent, not an extra C++ parameter.
extern "C" long double recovered_006ab0bf(unsigned char* arguments) {
    const u32 arg = reinterpret_cast<u32>(arguments);
    const u32 previous = FUN_005d8978(word(reinterpret_cast<u32>(&dat_00719090)), 0xffff);
    double rounded_input;
    u32 high;
    __asm__ volatile("fldl (%2)\n\tmovl 6(%2),%0\n\tfstpl %1"
                     : "=r"(high), "=m"(rounded_input)
                     : "r"(arg)
                     : "st", "memory");
    if ((high & 0x7ff0) == 0x7ff0) {
        const int32_t subtype = static_cast<int32_t>(classify(rounded_input));
        if (subtype > 0 && subtype <= 2) {
            FUN_005d8978(previous, 0xffff);
            return load(arg);
        }
        if (subtype == 3) {
            double value;
            quiet(value, arg);
            return qnan(value, previous);
        }
        double result, first;
        add_one(result, arg);
        quiet(first, arg);
        return error(8, first, result, previous);
    }
    double result;
    round_stored(result, rounded_input);
    if (!different(arg, result) || (previous & 0x20)) {
        FUN_005d8978(previous, 0xffff);
        return load(reinterpret_cast<u32>(&result));
    }
    double argument, result_copy;
    quiet(result_copy, reinterpret_cast<u32>(&result));
    quiet(argument, arg);
    return error(0x10, argument, result_copy, previous);
}

// Original selection precedes every argument read and tails into the actual
// chosen kernel. This bridge retains the original stack-double entry ABI.
extern "C" __attribute__((naked)) long double __cdecl FUN_006aa710(double) {
    __asm__ volatile(
        "cmpl $0,_dat_022532cc\n\tje _FUN_006ab0bf\n\tsubl $8,%esp\n\tstmxcsr 4(%esp)\n\tmovl 4(%esp),%eax\n\tandl $0x1f80,%eax\n\tcmpl $0x1f80,%eax\n\tjne 1f\n\tfnstcw (%esp)\n\tmovw (%esp),%ax\n\tandw $0x7f,%ax\n\tcmpw $0x7f,%ax\n1:\n\tleal 8(%esp),%esp\n\tjne _FUN_006ab0bf\n\tjmp _FUN_006aa750");
}
extern "C" __attribute__((naked)) long double __cdecl FUN_006aa750(double) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_006aa750\n\taddl $4,%esp\n\tretl");
}
extern "C" __attribute__((naked)) long double __cdecl FUN_006ab0bf(double) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_006ab0bf\n\taddl $4,%esp\n\tretl");
}
