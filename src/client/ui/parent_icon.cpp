#include "parent_icon.h"
#include "ordered_stores.h"
namespace shaiya::ui {
extern "C" const char dat_006c1020[4] = "%3d";
namespace {
using namespace ordered_detail;
u32 argument(u32* words, u32 index) {
    return load32(words, index * 4);
}
u8 low(const void* pointer) {
    u8 value;
    __asm__ volatile("movb (%1),%0" : "=q"(value) : "r"(pointer) : "memory");
    return value;
}
u32 callback() {
    auto* current =
        reinterpret_cast<shaiya::startup::CallbackObject_00405cc0*>(load32(&dat_007191d4, 0));
    auto target = reinterpret_cast<shaiya::startup::Callback_004>(
        load32(reinterpret_cast<void*>(load32(current, 0)), 4));
    return target(current, 0x2f);
}
u32 classify(u32 code, u32 incoming) {
    u32 result;
    __asm__ volatile("pushl %2\n\tmovl %3,%%ecx\n\tcall _FUN_004cba90"
                     : "=a"(result)
                     : "0"(incoming), "r"(code), "r"(&dat_008655e8)
                     : "ecx", "edx", "cc", "memory");
    return result;
}
struct UV {
    u32 u0, u1, v0, v1;
};
u32 draw(void* atlas, u32 incoming, u32 color, u32 x, u32 y, u32 width, u32 height, u32 u0, u32 u1,
         u32 v0, u32 v1) {
    const u32 words[9] = {color, x, y, width, height, u0, u1, v0, v1};
    u32 result;
    // The real549ba0 null-texture path preserves incomingEAX. Original3400
    // supplies color on its main/early calls and x-1 on its overlay call.
    __asm__ volatile(
        "pushl 32(%2)\n\tpushl 28(%2)\n\tpushl 24(%2)\n\tpushl 20(%2)\n\tpushl 16(%2)\n\t"
        "pushl 12(%2)\n\tpushl 8(%2)\n\tpushl 4(%2)\n\tpushl (%2)\n\tmovl %3,%%ecx\n\tcall _FUN_00549ba0"
        : "=a"(result)
        : "0"(incoming), "r"(words), "r"(atlas)
        : "ecx", "edx", "cc", "memory");
    return result;
}
UV coordinates(u32 index, u32 row, u32 step) {
    static const float one = 1.0f, vstep = 0.0625f;
    UV out;
    //35c3..3616. Entry-relative private slots are -4=index/u0,-8=u1,
    //-c=row/v0,-10=v1. PUSH2f at35ed is included in this ledger.
    __asm__ volatile(
        "flds %[step]\n\tfildl %[index]\n\tfld %%st(0)\n\tfmul %%st(2),%%st\n\tfstps %[u0]\n\t"
        "fadds %[one]\n\tfmul %%st(1),%%st\n\tfstps %[u1]\n\tfstp %%st(0)\n\t"
        "fildl %[row]\n\tflds %[vstep]\n\tfmul %%st(1),%%st\n\tfstps %[v0]\n\t"
        "fadds %[one]\n\tfmuls %[vstep]\n\tfstps %[v1]"
        : [u0] "=m"(out.u0), [u1] "=m"(out.u1), [v0] "=m"(out.v0), [v1] "=m"(out.v1)
        : [step] "m"(step), [index] "m"(index), [row] "m"(row), [one] "m"(one), [vstep] "m"(vstep)
        : "st", "st(1)", "st(2)", "cc", "memory");
    return out;
}
void overlay_uv(u32* args, u32& left, u32& right) {
    static const float eighth = 0.125f;
    __asm__ volatile(
        "fildl 8(%2)\n\tfmuls %3\n\tfsts 4(%2)\n\tfadds %3\n\tmovl 4(%2),%0\n\tfstps 8(%2)\n\tmovl 8(%2),%1"
        : "=&r"(left), "=r"(right)
        : "r"(args), "m"(eighth)
        : "st", "cc", "memory");
}
bool grid16(u32 type) {
    switch (type) {
    case 0x19:
    case 0x2c:
    case 0x26:
    case 0x29:
    case 0x4e:
    case 0x4f:
    case 0x50:
    case 0x2a:
    case 100:
    case 101:
    case 102:
    case 103:
    case 0x2b:
    case 0x5e:
        return true;
    default:
        return false;
    }
}
u32 text(u32 x, u32 y, u32 channel, u32 count) {
    return FUN_00541820(dat_02209408, x, y, channel, channel, channel, 0, dat_006c1020, count);
}
} // namespace

extern "C" u32 recovered_004a3400(u32* args) {
    if (low(reinterpret_cast<u8*>(args) + 28) == 0)
        store32(args, 0, 0xff505050u);
    u32 type = argument(args, 3), index, grid, step;
    store8(args, 28, 0);
    if (type == 255) {
        index = 255;
        grid = 4;
        step = 0x3e800000;
    } else if (type == 200) {
        index = argument(args, 4);
        if (static_cast<int32_t>(index) >= 1000) {
            type = 102;
            index -= 1000;
        } else
            type = 100;
        store32(args, 12, type);
        grid = 16;
        step = 0x3d800000;
    } else {
        const u32 record = find_item_record(dat_0086de50, type, argument(args, 4));
        if (record == 0)
            return 0;
        index = static_cast<u32>(low(reinterpret_cast<const u8*>(record) + 0xb)) - 1;
        if (grid16(type)) {
            grid = 16;
            step = 0x3d800000;
        } else if (type == 30 || type == 95) {
            grid = 8;
            step = 0x3e000000;
        } else if (type == 99) {
            type = 28;
            grid = 8;
            step = 0x3e000000;
        } else if (type == 27 || type == 28 || type == 29) {
            type = 27;
            grid = 8;
            step = 0x3e000000;
        } else {
            grid = 4;
            step = 0x3e800000;
        }
    }
    // Original3582 adjustment is used only by the quarter-grid and remapped
    //27/28 paths. The 30/95 eighth-grid route bypasses that adjustment.
    if (grid == 4 || (grid == 8 && type != 30 && type != 95)) {
        if (static_cast<int32_t>(index) >= 100) {
            index -= 100;
            store8(args, 28, 1);
        }
    }
    if (index == 255) {
        const u32 y = argument(args, 2), x = argument(args, 1), color = argument(args, 0);
        return draw(&dat_00864e8c, color, color, x, y, 32, 32, 0, 0x3f800000, 0, 0x3f800000);
    }
    u32 row = 0;
    if (static_cast<int32_t>(index) >= static_cast<int32_t>(grid)) {
        row = static_cast<u32>(static_cast<int32_t>(index) / static_cast<int32_t>(grid));
        index = (1u - grid) * index;
    }
    const u8 flag = low(reinterpret_cast<u8*>(args) + 24);
    const u8 size = static_cast<u8>((flag ? 0xf0u : 0u) + 0x20u);
    const UV uv = coordinates(index, row, step);
    u32 result = callback();
    const u32 y = argument(args, 2), x = argument(args, 1);
    if (static_cast<u8>(result) != 0 && size == 32) {
        const u32 second = argument(args, 4), first = argument(args, 3);
        const u32 record = find_item_record(dat_0086de50, first, second);
        result = record;
        if (record != 0) {
            u8 tile = low(reinterpret_cast<const u8*>(record) + 0x18);
            if (tile < 8) {
                store32(args, 16, 0);
                store32(args, 24, 0x3f000000);
            } else {
                tile = static_cast<u8>(tile - 8);
                store32(args, 16, 0x3f000000);
                store32(args, 24, 0x3f800000);
            }
            const u32 v1 = argument(args, 6), v0 = argument(args, 4);
            store32(args, 8, tile);
            u32 u0, u1;
            overlay_uv(args, u0, u1);
            result = draw(&dat_00864eac, x - 1, 0xb2ffffffu, x - 1, y - 1, 34, 34, u0, u1, v0, v1);
        }
    }
    void* atlas;
    switch (type) {
    case 100:
    case 101:
        atlas = &dat_008654f0[0];
        break;
    case 102:
    case 103:
        atlas = &dat_008654f0[1];
        break;
    case 0x4e:
    case 0x4f:
    case 0x50:
        atlas = &dat_00864ebc;
        break;
    case 0x2a:
        atlas = &dat_00864ed0[25];
        break;
    case 99:
        atlas = &dat_00864ed0[28];
        break;
    default:
        result = classify(type, result);
        type = static_cast<u8>(result);
        if (type < 1 || type > 41)
            return result;
        atlas = low(reinterpret_cast<u8*>(args) + 28) != 0
                    ? static_cast<void*>(&dat_00865250[type])
                    : static_cast<void*>(&dat_00864ed0[type]);
        break;
    }
    const u32 color = argument(args, 0);
    result = draw(atlas, color, color, x, y, size, size, uv.u0, uv.u1, uv.v0, uv.v1);
    if (size != 32)
        return result;
    const u8 count = low(reinterpret_cast<u8*>(args) + 20);
    //37fe is a partial AL write even when the subsequent count/show tests
    //return early. The upper24 backend bits remain observable in EAX.
    result = (result & 0xffffff00u) | count;
    if (count == 0)
        return result;
    bool show;
    switch (type) {
    case 0x19:
    case 0x2c:
    case 0x26:
    case 0x29:
    case 0x4e:
    case 0x4f:
    case 0x50:
    case 0x5e:
    case 100:
    case 101:
    case 102:
    case 103:
    case 27:
        show = true;
        break;
    default:
        show = argument(args, 3) == 99 || type == 30;
        break;
    }
    if (!show)
        return result;
    u32 final_count = count;
    if (type == 100) {
        text(x + 13, y + 16, 0, count);
        text(x + 11, y + 16, 0, count);
        text(x + 12, y + 15, 0, count);
        text(x + 12, y + 17, 0, count);
        text(x + 13, y + 17, 0, count);
        final_count = low(reinterpret_cast<u8*>(args) + 20);
    }
    return text(x + 12, y + 16, 255, final_count);
}

// Only the actual argument block is captured. ECX is unused by original3400;
// all algorithm/control/data effects above are C++, including writes to the
// original eight stack words. No presumed UV/private-stack values are supplied.
extern "C" __attribute__((naked)) u32 __attribute__((thiscall))
FUN_004a3400(Object_004230b0*, u32, u32, u32, u32, u32, u32, u32, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcall _recovered_004a3400\n\taddl $4,%esp\n\tretl $32");
}
} // namespace shaiya::ui
