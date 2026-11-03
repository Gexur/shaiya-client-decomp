#include "graphics/render_rotation_axis.h"
namespace {
using u32 = uint32_t;
struct TrigWords {
    u32 cosine, sine;
};
// The original first stores cosine and then sine to binary32 private slots.
// FSINCOS executes as hardware, including its masked exceptional/range behavior.
TrigWords trig(const void* angle) {
    TrigWords v;
    __asm__ volatile("flds %2\n\tfsincos\n\tfstps %0\n\tfstps %1"
                     : "=m"(v.cosine), "=m"(v.sine)
                     : "m"(*static_cast<const unsigned char (*)[4]>(angle))
                     : "st", "st(1)", "memory");
    return v;
}
u32 word(const void* p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(void* p, u32 value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(value) : "memory");
}
void zero(void* p) {
    __asm__ volatile("fldz\n\tfstps %0"
                     : "=m"(*static_cast<unsigned char (*)[4]>(p))::"st", "memory");
}
void one(void* p) {
    __asm__ volatile("fld1\n\tfstps %0"
                     : "=m"(*static_cast<unsigned char (*)[4]>(p))::"st", "memory");
}
void copy(void* p, const u32& v) {
    __asm__ volatile("flds %1\n\tfstps %0"
                     : "=m"(*static_cast<unsigned char (*)[4]>(p))
                     : "m"(v)
                     : "st", "memory");
}
void negative(void* p, const u32& v) {
    __asm__ volatile("flds %1\n\tfchs\n\tfstps %0"
                     : "=m"(*static_cast<unsigned char (*)[4]>(p))
                     : "m"(v)
                     : "st", "memory");
}
} // namespace
// Original005e57d9..005e5855. Private x87 temporary lifetimes are normalized;
// the original binary32 spills and every defined output store are retained.
extern "C" void* recovered_005e57d9(const u32* arguments) {
    const TrigWords v = trig(arguments + 1);
    auto* out = reinterpret_cast<unsigned char*>(word(arguments));
    one(out);
    zero(out + 4);
    put(out + 0x18, v.sine);
    zero(out + 8);
    zero(out + 0xc);
    zero(out + 0x10);
    copy(out + 0x14, v.cosine);
    zero(out + 0x1c);
    zero(out + 0x20);
    negative(out + 0x24, v.sine);
    copy(out + 0x28, v.cosine);
    zero(out + 0x2c);
    zero(out + 0x30);
    zero(out + 0x34);
    zero(out + 0x38);
    one(out + 0x3c);
    return out;
}
// Original005e587b..005e58f8.
extern "C" void* recovered_005e587b(const u32* arguments) {
    const TrigWords v = trig(arguments + 1);
    auto* out = reinterpret_cast<unsigned char*>(word(arguments));
    copy(out, v.cosine);
    zero(out + 4);
    negative(out + 8, v.sine);
    zero(out + 0xc);
    zero(out + 0x10);
    one(out + 0x14);
    zero(out + 0x18);
    zero(out + 0x1c);
    copy(out + 0x20, v.sine);
    zero(out + 0x24);
    copy(out + 0x28, v.cosine);
    zero(out + 0x2c);
    zero(out + 0x30);
    zero(out + 0x34);
    zero(out + 0x38);
    one(out + 0x3c);
    return out;
}
// Original005e591e..005e599c.
extern "C" void* recovered_005e591e(const u32* arguments) {
    const TrigWords v = trig(arguments + 1);
    auto* out = reinterpret_cast<unsigned char*>(word(arguments));
    copy(out, v.cosine);
    put(out + 4, v.sine);
    zero(out + 8);
    zero(out + 0xc);
    negative(out + 0x10, v.sine);
    copy(out + 0x14, v.cosine);
    zero(out + 0x18);
    zero(out + 0x1c);
    zero(out + 0x20);
    zero(out + 0x24);
    one(out + 0x28);
    zero(out + 0x2c);
    zero(out + 0x30);
    zero(out + 0x34);
    zero(out + 0x38);
    one(out + 0x3c);
    return out;
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e57d9(void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e57d9\n\taddl $4,%esp\n\tretl $8");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e587b(void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e587b\n\taddl $4,%esp\n\tretl $8");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e591e(void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e591e\n\taddl $4,%esp\n\tretl $8");
}
