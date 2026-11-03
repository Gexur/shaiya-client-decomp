#include "graphics/texture/texture_requirements.h"
#include "graphics/texture/texture_format.h"
#include "graphics/texture/texture_format_picker.h"
namespace {
using u32 = uint32_t;
/** @brief Read a 32-bit word with the original access and compiler barrier. */
inline u32 read_word(const void* address) {
    u32 value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(address) : "memory");
    return value;
}
/** @brief Write a 32-bit word with the original access and compiler barrier. */
inline void write_word(void* address, u32 value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(address), "r"(value) : "memory");
}
/** @brief Reinterpret a 32-bit client address without dereferencing it. */
inline void* pointer_from_address(u32 address) {
    return reinterpret_cast<void*>(address);
}
/** @brief Return the smaller unsigned operand. */
inline u32 minimum_unsigned(u32 left, u32 right) {
    return left < right ? left : right;
}
/** @brief Test whether a format is one of the DXT1 through DXT5 FourCC values. */
inline bool is_dxt_compressed(u32 format) {
    return format == 0x31545844 || format == 0x32545844 || format == 0x33545844 ||
           format == 0x34545844 || format == 0x35545844;
}
/**
 * @brief Round upward to a power of two, retaining the original shift loop.
 * @param value Requested dimension; callers supply values whose result fits in 32 bits.
 * @return The first power of two at least as large as value, or one for zero.
 */
u32 round_up_to_power_of_two(u32 value) {
    u32 result = 1;
    while (result < value)
        result <<= 1;
    return result;
}
/** @brief Return the significant bit width, used as the full mip-chain level count. */
u32 bit_width(u32 value) {
    u32 result = 0;
    while (value) {
        value >>= 1;
        ++result;
    }
    return result;
}
} // namespace

// Original5e1ee3..5e2298. Actual slots are reread at the points where the
// original rereads them; this includes callbacks and output-pointer aliases.
/**
 * @brief Normalize texture requests through their original mutable argument words.
 * @param device Direct3D device captured from the original implicit EDX argument.
 * @param arguments Eight original words: dimension pointers, usage, format pointer,
 *                  pool, and resource type. Stores and callbacks may alias these words.
 * @param caps Original uninitialized capability buffer, at least 304 bytes.
 * @return Original HRESULT bits: success, invalid call, or unsupported format.
 * @note Reads and final optional-output writes retain their original order.
 * @see normalize_texture_requirements
 */
extern "C" uint32_t normalize_texture_requirements_from_stack(void* device, uint32_t* arguments,
                                                              uint32_t* caps) {
    const u32 initial_pool = read_word(arguments + 6);
    const u32 initial_format_pointer = read_word(arguments + 5);
    const u32 initial_width_pointer = read_word(arguments);
    if (!device)
        return 0x8876086c;
    if (read_word(arguments + 4) == 0xffffffff)
        write_word(arguments + 4, 0);
    if (read_word(arguments + 4) & 0xffe039ec)
        return 0x8876086c;
    if (initial_pool > 3)
        return 0x8876086c;
    u32 format =
        initial_format_pointer ? read_word(pointer_from_address(initial_format_pointer)) : 0;
    if (initial_pool == 3) {
        if (!format)
            format = 0x15;
    } else {
        const auto* info = find_texture_format_record(format);
        const u32 type = read_word(arguments + 7), usage = read_word(arguments + 4);
        format = choose_supported_texture_format(device, usage, type, info);
        if (!format)
            return 0x8876086a;
    }
    u32 width =
        initial_width_pointer ? read_word(pointer_from_address(initial_width_pointer)) : 0xffffffff;
    u32 output_address = read_word(arguments + 1);
    u32 height = output_address ? read_word(pointer_from_address(output_address)) : 0xffffffff;
    output_address = read_word(arguments + 2);
    u32 depth = output_address ? read_word(pointer_from_address(output_address)) : 0xffffffff;
    output_address = read_word(arguments + 3);
    u32 levels = output_address ? read_word(pointer_from_address(output_address)) : 0xffffffff;
    if (width == 0xffffffff && height == 0xffffffff) {
        width = 0x100;
        height = 0x100;
    } else {
        if (width == 0xffffffff)
            width = height;
        else if (height == 0xffffffff)
            height = width;
        if (!width)
            width = 1;
        if (!height)
            height = 1;
    }
    if (read_word(arguments + 7) == 5) {
        height = width > height ? width : height;
        width = height;
    }
    if (!depth || depth == 0xffffffff)
        depth = 1;
    u32 texture_caps;
    if (read_word(arguments + 6) != 3) {
        const u32 table = read_word(device);
        using GetCaps = int32_t(__attribute__((stdcall))*)(void*, void*);
        reinterpret_cast<GetCaps>(read_word(pointer_from_address(table + 0x1c)))(device, caps);
        const u32 type = read_word(arguments + 7);
        texture_caps = read_word(caps + 0x3c / 4);
        if (type == 4) {
            const u32 maximum = read_word(caps + 0x60 / 4);
            depth = minimum_unsigned(depth, maximum);
            width = minimum_unsigned(width, maximum);
            height = minimum_unsigned(height, maximum);
        } else {
            width = minimum_unsigned(width, read_word(caps + 0x58 / 4));
            height = minimum_unsigned(height, read_word(caps + 0x5c / 4));
            if (read_word(arguments + 7) == 3) {
                const u32 aspect = (texture_caps & 0x20) ? 1 : read_word(caps + 0x68 / 4);
                if (aspect) {
                    width = minimum_unsigned(width, aspect * height);
                    height = minimum_unsigned(height, aspect * width);
                }
            }
        }
        const u32 type_for_power = read_word(arguments + 7);
        u32 power_mask = type_for_power == 3   ? 2
                         : type_for_power == 4 ? 0x40000
                         : type_for_power == 5 ? 0x20000
                                               : type_for_power;
        if (levels == 1 && (texture_caps & 0x100) && !is_dxt_compressed(format))
            power_mask = 0;
        if (texture_caps & power_mask) {
            width = round_up_to_power_of_two(width);
            height = round_up_to_power_of_two(height);
            depth = round_up_to_power_of_two(depth);
        }
    } else
        texture_caps = read_word(caps + 0x3c / 4);
    if (is_dxt_compressed(format)) {
        width = (width + 3) & 0xfffffffc;
        height = (height + 3) & 0xfffffffc;
    }
    const u32 type_for_mips = read_word(arguments + 7);
    const u32 mip_mask = type_for_mips == 3   ? 0x4000
                         : type_for_mips == 4 ? 0x8000
                         : type_for_mips == 5 ? 0x10000
                                              : type_for_mips;
    if (read_word(arguments + 6) == 3 ||
        ((texture_caps & mip_mask) &&
         (!(texture_caps & 0x100) ||
          (!(width & (width - 1)) && !(height & (height - 1)) && !(depth & (depth - 1)))))) {
        const u32 w_bits = bit_width(width), h_bits = bit_width(height), d_bits = bit_width(depth);
        u32 maximum = w_bits > h_bits ? w_bits : h_bits;
        if (read_word(arguments + 7) == 4 && d_bits > maximum)
            maximum = d_bits;
        if (levels > maximum || !levels)
            levels = maximum;
        if (levels != 1 && (read_word(arguments + 4) & 0x400))
            levels = 0;
    } else
        levels = 1;
    output_address = read_word(arguments);
    if (output_address)
        write_word(pointer_from_address(output_address), width);
    output_address = read_word(arguments + 1);
    if (output_address)
        write_word(pointer_from_address(output_address), height);
    output_address = read_word(arguments + 2);
    if (output_address)
        write_word(pointer_from_address(output_address), depth);
    output_address = read_word(arguments + 3);
    if (output_address)
        write_word(pointer_from_address(output_address), levels);
    output_address = read_word(arguments + 5);
    if (output_address)
        write_word(pointer_from_address(output_address), format);
    return 0;
}

// Preserve the actual uninitialized304-byte GetDeviceCaps buffer at entryESP-
// 0x148. The original ignores the callback HRESULT; no zeroed fallback is added.
/**
 * @brief Normalize texture dimensions, format, and mip levels for device support.
 * @param width Optional in/out width; UINT32_MAX requests the default.
 * @param height Optional in/out height; UINT32_MAX requests the default.
 * @param depth Optional in/out volume depth.
 * @param mip_levels Optional in/out level count; zero requests the full chain.
 * @param usage Direct3D usage flags; UINT32_MAX is normalized to zero locally.
 * @param format Optional in/out Direct3D format value.
 * @param pool Direct3D memory pool from zero through three.
 * @param resource_type Direct3D texture, volume-texture, or cube-texture type.
 * @return Zero on success, D3DERR_INVALIDCALL for rejected arguments, or
 *         D3DERR_NOTAVAILABLE when no supported format can be chosen.
 * @note Custom ABI: the device arrives implicitly in EDX, followed by eight
 *       stack words and RET32. Callers require an explicit architecture bridge.
 *       Failed capability queries retain the original uninitialized scratch data.
 */
extern "C" __attribute__((naked)) int32_t __attribute__((stdcall))
normalize_texture_requirements(uint32_t* width, uint32_t* height, uint32_t* depth,
                               uint32_t* mip_levels, uint32_t usage, int32_t* format, uint32_t pool,
                               uint32_t resource_type) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $0x144,%esp\n\tleal 8(%ebp),%eax\n\tleal -0x144(%ebp),%ecx\n\tpushl %ecx\n\tpushl %eax\n\tpushl %edx\n\tcalll _normalize_texture_requirements_from_stack\n\taddl $12,%esp\n\tleave\n\tretl $32");
}
