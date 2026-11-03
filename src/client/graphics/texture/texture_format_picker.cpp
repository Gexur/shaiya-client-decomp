#include "graphics/texture/texture_format_picker.h"
/** @brief Set the render diagnostic mute state used around Direct3D probing. */
extern "C" void __attribute__((stdcall)) FUN_005e9b1d(uint32_t mute);
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
inline void* pointer_from_address(u32 value) {
    return reinterpret_cast<void*>(value);
}
/**
 * @brief Read a COM method through the object's current vtable.
 * @tparam Target Function pointer type including the original calling convention.
 * @param object COM interface whose first word contains the vtable address.
 * @param slot Byte offset of the method within that vtable.
 * @return The method pointer, without validating the interface or slot.
 */
template <class Target> Target load_vtable_method(void* object, u32 slot) {
    return reinterpret_cast<Target>(read_word(pointer_from_address(read_word(object) + slot)));
}
} // namespace

// Complete original5e1c00..5e1cfe. The actual340-byte private backing retains
// ignored COM-output failures; its304/16/16/4-byte regions are never zero-filled.
/**
 * @brief Select a texture format using the original stack words and COM scratch storage.
 * @param arguments Device, usage, resource type, and desired-descriptor argument words.
 * @param frame Original 340-byte uninitialized scratch area for COM outputs.
 * @return The chosen Direct3D format value, or zero if no candidate is selected.
 * @note Acquired Direct3D interfaces are released. COM results, aliases, and
 *       argument rereads retain their original order, including ignored failures.
 * @see choose_supported_texture_format
 */
extern "C" uint32_t choose_supported_texture_format_from_stack(uint32_t* arguments,
                                                               unsigned char* frame) {
    auto* d3d_slot = reinterpret_cast<u32*>(frame + 0x150);
    write_word(d3d_slot, 0);
    FUN_005e9b1d(1);
    void* device = pointer_from_address(read_word(arguments));
    if (device) {
        using GetOutput = int32_t(__attribute__((stdcall))*)(void*, void*);
        load_vtable_method<GetOutput>(device, 0x18)(device, d3d_slot);
        load_vtable_method<GetOutput>(device, 0x1c)(device, frame);
        using GetDisplayMode = int32_t(__attribute__((stdcall))*)(void*, u32, void*);
        load_vtable_method<GetDisplayMode>(device, 0x20)(device, 0, frame + 0x130);
        if (read_word(arguments + 1) & 0x100000) {
            load_vtable_method<GetOutput>(device, 0x24)(device, frame + 0x140);
            u32 behavior;
            __asm__ volatile("movzbl (%1),%0" : "=r"(behavior) : "r"(frame + 0x14c) : "memory");
            if (behavior & 0x20)
                write_word(arguments + 1, read_word(arguments + 1) | 0x10);
        }
    }
    u32 current = reinterpret_cast<u32>(dat_006dbd08);
    u32 best_score = 0xffffffff;
    u32 chosen = reinterpret_cast<u32>(&dat_006dbce0);
    if (current < read_word(&dat_0070f36c)) {
        do {
            const u32 candidate_format = read_word(pointer_from_address(current));
            bool supported = candidate_format != 0;
            if (supported) {
                void* d3d = pointer_from_address(read_word(d3d_slot));
                if (d3d) {
                    const u32 table = read_word(d3d);
                    const u32 type = read_word(arguments + 2), usage = read_word(arguments + 1);
                    const u32 display_format = read_word(frame + 0x13c);
                    const u32 device_type = read_word(frame), adapter = read_word(frame + 4);
                    using Check =
                        int32_t(__attribute__((stdcall))*)(void*, u32, u32, u32, u32, u32, u32);
                    supported =
                        reinterpret_cast<Check>(read_word(pointer_from_address(table + 0x28)))(
                            d3d, adapter, device_type, display_format, usage, type,
                            candidate_format) >= 0;
                }
            }
            if (supported) {
                const auto* desired =
                    reinterpret_cast<const TextureFormatRecord*>(read_word(arguments + 3));
                if (read_word(desired) == read_word(pointer_from_address(current))) {
                    chosen = current;
                    break;
                }
                if (read_word(pointer_from_address(current + 32))) {
                    const u32 score = score_texture_format_conversion(
                        desired, reinterpret_cast<const TextureFormatRecord*>(current));
                    if (score != 0xffffffff && score <= best_score) {
                        bool better = score != best_score;
                        if (!better) {
                            const u32 candidate_bits = read_word(pointer_from_address(current + 8));
                            better = candidate_bits < read_word(pointer_from_address(chosen + 8));
                        }
                        if (better) {
                            best_score = score;
                            chosen = current;
                        }
                    }
                }
            }
            current += 36;
        } while (current < read_word(&dat_0070f36c));
    }
    void* d3d = pointer_from_address(read_word(d3d_slot));
    if (d3d) {
        using Release = u32(__attribute__((stdcall))*)(void*);
        load_vtable_method<Release>(d3d, 8)(d3d);
        write_word(d3d_slot, 0);
    }
    FUN_005e9b1d(0);
    return read_word(pointer_from_address(chosen));
}

/**
 * @brief Choose a supported texture format closest to the desired descriptor.
 * @param device Direct3D device queried for capabilities, or null to skip support checks.
 * @param usage Resource usage flags; original local argument updates are retained.
 * @param resource_type Direct3D resource type supplied to CheckDeviceFormat.
 * @param desired_format Requested format descriptor.
 * @return The chosen Direct3D format value, or zero when no candidate is selected.
 * @note Exact matches win. Scored ties prefer fewer storage bits, then retain
 *       the earlier entry. Failed COM output calls retain original uninitialized storage.
 */
extern "C" __attribute__((naked)) uint32_t __attribute__((stdcall))
choose_supported_texture_format(void* device, uint32_t usage, uint32_t resource_type,
                                const TextureFormatRecord* desired_format) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $0x154,%esp\n\tleal -0x154(%ebp),%ecx\n\tleal 8(%ebp),%eax\n\tpushl %ecx\n\tpushl %eax\n\tcalll _choose_supported_texture_format_from_stack\n\taddl $8,%esp\n\tleave\n\tretl $16");
}
