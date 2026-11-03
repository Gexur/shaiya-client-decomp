#include "profile_read.h"
#include "startup/application.h"
#include "core/string_compare.h"
#include "startup/global_initializers_strings.h"
#include "runtime/security.h"

namespace {
using u32 = uint32_t;
using String = shaiya::startup::String_00405710;
using Pair = shaiya::startup::Pair_0040abc0;
/// Imported Windows INI reader, retaining the original six-argument stdcall ABI.
using ReadProfile = u32(__attribute__((stdcall)) *)(const char* section, const char* key,
                                                    const char* fallback, char* output,
                                                    u32 capacity, const char* filename);
extern "C" ReadProfile imported_profile_read __asm__("__imp__GetPrivateProfileStringA@24");
/**
 * @brief Load an original 32-bit field without widening or combining neighboring accesses.
 * @param object Recovered owning object whose evidenced layout is required.
 * @param offset Byte offset of the original 32-bit field within the object.
 * @return The field value at the supplied byte offset.
 */
u32 read_profile_word(const void* object, u32 offset) {
    u32 value;
    const auto* at = reinterpret_cast<const unsigned char*>(object) + offset;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
/**
 * @brief Read one unsigned byte with the original zero-extending x86 access.
 * @param address Address of the byte to read.
 * @return The loaded byte widened to 32 bits.
 */
u32 read_profile_byte(const void* address) {
    u32 value;
    __asm__ volatile("movzbl (%1),%0" : "=r"(value) : "r"(address) : "memory");
    return value;
}
/**
 * @brief Select a recovered string inline buffer or heap pointer from its capacity.
 * @param string Recovered string whose existing stored bytes are modified in place.
 * @return A borrowed NUL-terminated buffer pointer.
 */
const char* profile_string_data(const String* string) {
    return read_profile_word(string, 0x18) < 16
               ? reinterpret_cast<const char*>(string->storage_004)
               : reinterpret_cast<const char*>(read_profile_word(string, 4));
}
} // namespace

// Original005c0de0..005c0ed3. The entry below has already read/cached the
// three actual arguments and the sentinel capacity in their original order.
/**
 * @brief Implement profile section selection and copying for the preserved x86 entry bridge.
 *
 * The sentinel capacity was cached by the entry bridge before this body executes. Recovered Ep5.4 entry: 0x005c0de0.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param key Configuration key whose stored bytes and length are used.
 * @param output_and_default Initialized default string replaced with the profile-read result.
 * @param optional_section Requested section, or the sentinel that keeps the stored section unchanged.
 * @param buffer Caller-owned 1024-byte scratch area for the Windows profile read.
 * @param sentinel_capacity Previously cached capacity of the optional-section sentinel string.
 * @return The reconstructed output-string address before the entry bridge sets AL.
 */
extern "C" u32 read_profile_string_body(Pair* self, const String* key, String* output_and_default,
                                        const String* optional_section, char* buffer,
                                        u32 sentinel_capacity) {
    // Original loads the storage DWORD even when its inline address is used.
    const u32 stored = read_profile_word(&dat_0070cb1c, 4);
    const auto* sentinel = sentinel_capacity < 16 ? dat_0070cb1c.storage_004
                                                  : reinterpret_cast<const uint8_t*>(stored);
    const u32 sentinel_size = read_profile_word(&dat_0070cb1c, 0x14),
              section_size = read_profile_word(optional_section, 0x14);
    if (FUN_0040a670(const_cast<String*>(optional_section), 0, section_size, sentinel,
                     sentinel_size) != 0)
        (void)FUN_00405620(&self->second_01c, optional_section, 0, 0xffffffffu);

    const char* filename = profile_string_data(&self->first_000);
    const char* fallback = profile_string_data(output_and_default);
    const char* key_text = profile_string_data(key);
    const char* section_text = profile_string_data(&self->second_01c);
    ReadProfile read_profile;
    __asm__ volatile("movl %1,%0" : "=r"(read_profile) : "m"(imported_profile_read) : "memory");
    (void)read_profile(section_text, key_text, fallback, buffer, 1024, filename);
    u32 length = 0;
    while (read_profile_byte(buffer + length) != 0)
        ++length;
    return reinterpret_cast<u32>(FUN_00405710(output_and_default, buffer, length));
}

// Architecture-only bridge: exact original stack reservation, cached incoming
// arguments/capacity, cookie storage/check, AL-only result and RET12. All
// profile selection/comparison/copying/control remains the C++ body above.
/**
 * @brief Read an INI string using the stored filename, selected section and supplied default.
 *
 * The x86 bridge preserves argument-read order, stack layout, security-cookie checks and RET12. Recovered Ep5.4 entry: 0x005c0de0.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param key Configuration key whose stored bytes and length are used.
 * @param output_and_default Initialized default string replaced with the profile-read result.
 * @param optional_section Requested section, or the sentinel that keeps the stored section unchanged.
 * @return The original register result with AL set to one.
 */
extern "C" __attribute__((naked, thiscall)) u32 read_profile_string(
    Pair* self, const String* key, String* output_and_default, const String* optional_section) {
    __asm__ volatile("subl $0x404,%esp\n\t"
                     "movl _dat_0070e4ec,%eax\n\t"
                     "xorl %esp,%eax\n\t"
                     "pushl %ebx\n\t"
                     "movl 0x40c(%esp),%ebx\n\t"
                     "pushl %ebp\n\t"
                     "movl 0x414(%esp),%ebp\n\t"
                     "movl %eax,0x408(%esp)\n\t"
                     "movl _dat_0070cb1c+24,%eax\n\t"
                     "pushl %esi\n\t"
                     "movl 0x41c(%esp),%esi\n\t"
                     "pushl %edi\n\t"
                     "leal 0x10(%esp),%edx\n\t"
                     "pushl %eax\n\t"
                     "pushl %edx\n\t"
                     "pushl %esi\n\t"
                     "pushl %ebp\n\t"
                     "pushl %ebx\n\t"
                     "pushl %ecx\n\t"
                     "calll _read_profile_string_body\n\t"
                     "addl $24,%esp\n\t"
                     "movl 0x410(%esp),%ecx\n\t"
                     "popl %edi\n\t"
                     "popl %esi\n\t"
                     "popl %ebp\n\t"
                     "popl %ebx\n\t"
                     "xorl %esp,%ecx\n\t"
                     "movb $1,%al\n\t"
                     // The canonical normalized C++ cookie API has a void return and may
                     // use EAX, whereas the original private checker preserves it.
                     "pushl %eax\n\t"
                     "calll @fun_005d0efa@4\n\t"
                     "popl %eax\n\t"
                     "addl $0x404,%esp\n\t"
                     "retl $12");
}
