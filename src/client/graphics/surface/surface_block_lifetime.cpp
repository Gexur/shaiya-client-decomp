#include "graphics/surface/surface_block_lifetime.h"
#include "runtime/allocations.h"
#include "graphics/surface/surface_lifetimes.h"
#include "graphics/surface/surface_format_tables.h"
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
} // namespace
// Original005f1c43..005f1cc8. The dirty flag is read before installing
// the block vtable. The original four-byte cursor remains observable across
// CRT frees; row bounds and the outer bound are freshly read each iteration.
extern "C" void recovered_005f1c43(u32 self, u32 cursor) {
    const u32 dirty = word(self + 0xf4);
    put(self, reinterpret_cast<uintptr_t>(dat_006df3f4));
    if (dirty) {
        const u32 table = word(self + 0xf8);
        if (table) {
            u32 y = word(self + 0xd4);
            const bool rows = y < word(self + 0xd8);
            put(cursor, table);
            if (rows) {
                do {
                    u32 x = word(self + 0xc8);
                    while (x < word(self + 0xd0)) {
                        fun_005cc620(reinterpret_cast<void*>(word(word(cursor) + 4)));
                        put(cursor, word(cursor) + 8);
                        x += 4;
                    }
                    ++y;
                } while (y < word(self + 0xd8));
            }
        }
    }
    fun_005cc620(reinterpret_cast<void*>(word(self + 0xf0)));
    fun_005cc620(reinterpret_cast<void*>(word(self + 0xf8)));
    FUN_005f0d79(reinterpret_cast<void*>(self));
}
extern "C" __attribute__((naked, thiscall)) void FUN_005f1c43(void*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl %ecx\n\tleal -4(%ebp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f1c43\n\taddl $8,%esp\n\tleave\n\tretl");
}
// Original005fb432..005fb453. Preserve the caller's flag byte until after
// destruction, then optionally free the receiver and return it with RET4.
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005fb432(void*, uint32_t) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl %esi\n\tmovl %ecx,%esi\n\tcalll _FUN_005f1c43\n\ttestb $1,8(%ebp)\n\tje 1f\n\tpushl %esi\n\tcalll _fun_005cc620\n\tpopl %ecx\n\t1: movl %esi,%eax\n\tpopl %esi\n\tpopl %ebp\n\tretl $4");
}
