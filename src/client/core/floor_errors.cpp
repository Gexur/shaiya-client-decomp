#include "floor_errors.h"
#include "floor_data.h"
#include "core/fp_exception_support.h"
#include "core/math_error.h"
#include "runtime/locks.h"
#include "runtime/security.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
unsigned char byte(u32 p) {
    unsigned char v;
    __asm__ volatile("movb (%1),%0" : "=q"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void copy_bits(double* output, u32 source) {
    put(reinterpret_cast<u32>(output), word(source));
    put(reinterpret_cast<u32>(output) + 4, word(source + 4));
}
void put_pair(u32* output, const double& v) {
    output[0] = word(reinterpret_cast<u32>(&v));
    output[1] = word(reinterpret_cast<u32>(&v) + 4);
}
double quiet_copy(u32 p) {
    double v;
    __asm__ volatile("fldl (%1)\n\tfstpl %0" : "=m"(v) : "r"(p) : "st", "memory");
    return v;
}
long double load(u32 p) {
    long double v;
    __asm__ volatile("fldl (%1)" : "=t"(v) : "r"(p) : "memory");
    return v;
}
double zero() {
    double v;
    __asm__ volatile("fldz\n\tfstpl %0" : "=m"(v)::"st", "memory");
    return v;
}
long double invoke_name(u32 kind, u32 operation, const double& first, const double& second,
                        const double& result, u32 control) {
    u32 words[9];
    words[0] = kind;
    words[1] = operation;
    put_pair(words + 2, first);
    put_pair(words + 4, second);
    put_pair(words + 6, result);
    words[8] = control;
    long double answer;
    __asm__ volatile(
        "pushl 32(%1)\n\tpushl 28(%1)\n\tpushl 24(%1)\n\tpushl 20(%1)\n\tpushl 16(%1)\n\tpushl 12(%1)\n\tpushl 8(%1)\n\tpushl 4(%1)\n\tpushl (%1)\n\tcalll _FUN_005d8688\n\taddl $36,%%esp"
        : "=t"(answer)
        : "r"(words)
        : "eax", "ecx", "edx", "memory", "cc");
    return answer;
}
} // namespace
// Complete865b..8688; original reads only the actual lowBYTE argument.
extern "C" u32 recovered_005d865b(const unsigned char* arguments) {
    const unsigned char flags = byte(reinterpret_cast<u32>(arguments));
    if (flags & 0x20)
        return 5;
    if (flags & 8)
        return 1;
    if (flags & 4)
        return 2;
    if (flags & 1)
        return 3;
    return (flags & 2u) << 1;
}
// Complete8688..8726. The operation word is reloaded for every table row;
// record arguments are copied as integer words, retaining raw NaN payloads.
extern "C" long double recovered_005d8688(const unsigned char* arguments) {
    const u32 args = reinterpret_cast<u32>(arguments), table = reinterpret_cast<u32>(dat_0070ec30);
    u32 name = 0;
    for (u32 i = 0; i < 29; ++i) {
        const u32 operation = word(table + i * 8);
        if (operation == word(args + 4)) {
            name = word(table + i * 8 + 4);
            break;
        }
    }
    if (name) {
        PowerMathException record;
        record.name = reinterpret_cast<const char*>(name);
        copy_bits(&record.argument0, args + 8);
        copy_bits(&record.argument1, args + 16);
        const u32 kind = word(args);
        copy_bits(&record.result, args + 24);
        const u32 control = word(args + 32);
        record.kind = kind;
        FUN_005d8978(control, 0xffff);
        if (FUN_005decbe(&record) == 0)
            FUN_005d8633(kind); // Actual direct original call, not dat70ec00 dispatch.
        return load(reinterpret_cast<u32>(&record.result));
    }
    const u32 control = word(args + 32);
    FUN_005d8978(control, 0xffff);
    FUN_005d8633(word(args));
    return load(args + 24);
}
// Complete8726..8779. Adjacent8779 is a different binary helper and unowned.
extern "C" long double recovered_005d8726(const unsigned char* arguments) {
    const u32 args = reinterpret_cast<u32>(arguments);
    if (word(reinterpret_cast<u32>(&dat_0070ef40)) == 0) {
        const u32 control = word(args + 12);
        const double result = quiet_copy(args + 4), second = zero(), first = quiet_copy(args + 4);
        const u32 operation = word(args);
        return invoke_name(1, operation, first, second, result, control);
    }
    int32_t* error = fun_005d589a();
    const u32 control = word(args + 12);
    put(reinterpret_cast<u32>(error), 0x21);
    FUN_005d8978(control, 0xffff);
    return load(args + 4);
}
// Complete87d8..8894 normal/control flow. The original128-byte aligned area
// is supplied by its exact frame adapter below; its first124 bytes stay live
// original private input, including the actual flags RMW at offset64.
extern "C" long double recovered_005d87d8(unsigned char* arguments, unsigned char* ieee,
                                          u32 initial_control) {
    const u32 args = reinterpret_cast<u32>(arguments), record = reinterpret_cast<u32>(ieee);
    if (FUN_005d840f(word(args), reinterpret_cast<double*>(args + 16), initial_control) == 0) {
        __asm__ volatile("andl $-2,64(%0)" ::"r"(record) : "memory", "cc");
        const u32 operation = word(args + 4), flags = word(args);
        FUN_005d816a(ieee, reinterpret_cast<u32*>(args + 24), flags, operation,
                     reinterpret_cast<double*>(args + 8), reinterpret_cast<double*>(args + 16));
    }
    const u32 kind = FUN_005d865b(word(args));
    if (word(reinterpret_cast<u32>(&dat_0070ef40)) == 0 && kind) {
        const u32 control = word(args + 24);
        const double result = quiet_copy(args + 16), second = zero(), first = quiet_copy(args + 8);
        const u32 operation = word(args + 4);
        return invoke_name(kind, operation, first, second, result, control);
    }
    FUN_005d8633(kind);
    const u32 control = word(args + 24);
    FUN_005d8978(control, 0xffff);
    return load(args + 16);
}
extern "C" __attribute__((naked)) u32 __cdecl FUN_005d865b(u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005d865b\n\taddl $4,%esp\n\tretl");
}
extern "C" __attribute__((naked)) long double __cdecl FUN_005d8688(u32, u32, double, double, double,
                                                                   u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005d8688\n\taddl $4,%esp\n\tretl");
}
extern "C" __attribute__((naked)) long double __cdecl FUN_005d8726(u32, double, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005d8726\n\taddl $4,%esp\n\tretl");
}
extern "C" __attribute__((naked)) long double __cdecl FUN_005d87d8(u32, u32, double, double, u32) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-16,%esp\n\tsubl $128,%esp\n\tmovl _dat_0070e4ec,%eax\n\tmovl 32(%ebp),%edx\n\txorl %ebp,%eax\n\tmovl %eax,124(%esp)\n\tmovl %esp,%ecx\n\tleal 8(%ebp),%eax\n\tpushl %edx\n\tpushl %ecx\n\tpushl %eax\n\tcalll _recovered_005d87d8\n\taddl $12,%esp\n\tmovl 124(%esp),%ecx\n\txorl %ebp,%ecx\n\tcalll @fun_005d0efa@4\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tretl");
}
