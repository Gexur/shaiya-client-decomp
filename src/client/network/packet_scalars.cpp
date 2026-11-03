#include "packet_scalars.h"

namespace {
/**
 * @brief Read one unaligned DWORD with the original access and compiler barrier.
 * @param address Readable client storage, including partially written scratch words.
 * @return All four observed bytes, without masking unused field bytes.
 */
inline uint32_t read_word(const void* address) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(address) : "memory");
    return value;
}
} // namespace

// Original 0x0058e160..0x0058e182; read 1 byte(s), virtual slot 0x40.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x040.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_040(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x40(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x040.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_040(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_040\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x0058e1e0..0x0058e202; read 1 byte(s), virtual slot 0x50.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x050.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_050(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x50(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x050.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_050(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_050\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x0058e210..0x0058e232; read 2 byte(s), virtual slot 0x58.
/**
 * @brief Decode a 2-byte field and invoke session vtable byte offset 0x058.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 2 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u16_to_session_slot_058(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 2);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x58(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x058.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u16_to_session_slot_058(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u16_to_session_slot_058\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x0058e330..0x0058e352; read 4 byte(s), virtual slot 0x64.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x064.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_064(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x64(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x064.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_064(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_064\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x0058eea0..0x0058eec5; read 1 byte(s), virtual slot 0x8c.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x08c.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_08c(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x8c(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x08c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_08c(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_08c\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x0058ef30..0x0058ef55; read 4 byte(s), virtual slot 0x98.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x098.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_098(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x98(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x098.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_098(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_098\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x0058f3e0..0x0058f405; read 4 byte(s), virtual slot 0xd0.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x0d0.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_0d0(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0xd0(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x0d0.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_0d0(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_0d0\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x0058f460..0x0058f485; read 4 byte(s), virtual slot 0xd8.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x0d8.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_0d8(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0xd8(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x0d8.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_0d8(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_0d8\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x0058f610..0x0058f635; read 2 byte(s), virtual slot 0x128.
/**
 * @brief Decode a 2-byte field and invoke session vtable byte offset 0x128.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 2 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u16_to_session_slot_128(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 2);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x128(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x128.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u16_to_session_slot_128(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u16_to_session_slot_128\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x0058fde0..0x0058fe05; read 4 byte(s), virtual slot 0x13c.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x13c.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_13c(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x13c(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x13c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_13c(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_13c\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00590bd0..0x00590bf5; read 4 byte(s), virtual slot 0x194.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x194.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_194(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x194(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x194.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_194(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_194\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00590c70..0x00590c95; read 4 byte(s), virtual slot 0x19c.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x19c.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_19c(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x19c(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x19c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_19c(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_19c\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00591d40..0x00591d65; read 2 byte(s), virtual slot 0x208.
/**
 * @brief Decode a 2-byte field and invoke session vtable byte offset 0x208.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 2 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u16_to_session_slot_208(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 2);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x208(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x208.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u16_to_session_slot_208(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u16_to_session_slot_208\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00591fb0..0x00591fd5; read 4 byte(s), virtual slot 0x218.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x218.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_218(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x218(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x218.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_218(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_218\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x005927e0..0x00592805; read 4 byte(s), virtual slot 0x260.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x260.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_260(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x260(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x260.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_260(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_260\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00592810..0x00592835; read 4 byte(s), virtual slot 0x264.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x264.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_264(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x264(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x264.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_264(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_264\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00592840..0x00592865; read 4 byte(s), virtual slot 0x268.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x268.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_268(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x268(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x268.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_268(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_268\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00592c90..0x00592cb5; read 4 byte(s), virtual slot 0x29c.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x29c.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_29c(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x29c(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x29c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_29c(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_29c\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00592d10..0x00592d35; read 1 byte(s), virtual slot 0x2a4.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x2a4.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_2a4(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x2a4(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x2a4.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_2a4(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_2a4\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00592f20..0x00592f45; read 1 byte(s), virtual slot 0x2cc.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x2cc.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_2cc(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x2cc(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x2cc.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_2cc(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_2cc\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00592ff0..0x00593015; read 4 byte(s), virtual slot 0x2d4.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x2d4.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_2d4(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x2d4(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x2d4.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_2d4(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_2d4\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x005930a0..0x005930c5; read 4 byte(s), virtual slot 0x2dc.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x2dc.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_2dc(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x2dc(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x2dc.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_2dc(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_2dc\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00593470..0x00593495; read 1 byte(s), virtual slot 0x2f0.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x2f0.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_2f0(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x2f0(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x2f0.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_2f0(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_2f0\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00593b80..0x00593ba5; read 2 byte(s), virtual slot 0x314.
/**
 * @brief Decode a 2-byte field and invoke session vtable byte offset 0x314.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 2 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u16_to_session_slot_314(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 2);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x314(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x314.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u16_to_session_slot_314(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u16_to_session_slot_314\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00593bb0..0x00593bd5; read 2 byte(s), virtual slot 0x318.
/**
 * @brief Decode a 2-byte field and invoke session vtable byte offset 0x318.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 2 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u16_to_session_slot_318(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 2);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x318(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x318.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u16_to_session_slot_318(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u16_to_session_slot_318\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00594390..0x005943b5; read 2 byte(s), virtual slot 0x380.
/**
 * @brief Decode a 2-byte field and invoke session vtable byte offset 0x380.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 2 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u16_to_session_slot_380(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 2);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x380(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x380.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u16_to_session_slot_380(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u16_to_session_slot_380\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x005943c0..0x005943e5; read 2 byte(s), virtual slot 0x384.
/**
 * @brief Decode a 2-byte field and invoke session vtable byte offset 0x384.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 2 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u16_to_session_slot_384(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 2);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x384(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x384.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u16_to_session_slot_384(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u16_to_session_slot_384\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x005943f0..0x00594415; read 2 byte(s), virtual slot 0x388.
/**
 * @brief Decode a 2-byte field and invoke session vtable byte offset 0x388.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 2 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u16_to_session_slot_388(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 2);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x388(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x388.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u16_to_session_slot_388(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u16_to_session_slot_388\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00594420..0x00594445; read 2 byte(s), virtual slot 0x38c.
/**
 * @brief Decode a 2-byte field and invoke session vtable byte offset 0x38c.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 2 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u16_to_session_slot_38c(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 2);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x38c(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x38c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u16_to_session_slot_38c(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u16_to_session_slot_38c\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00594450..0x00594475; read 2 byte(s), virtual slot 0x390.
/**
 * @brief Decode a 2-byte field and invoke session vtable byte offset 0x390.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 2 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u16_to_session_slot_390(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 2);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x390(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x390.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u16_to_session_slot_390(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u16_to_session_slot_390\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x005944d0..0x005944f5; read 2 byte(s), virtual slot 0x39c.
/**
 * @brief Decode a 2-byte field and invoke session vtable byte offset 0x39c.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 2 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u16_to_session_slot_39c(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 2);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x39c(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x39c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u16_to_session_slot_39c(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u16_to_session_slot_39c\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00594500..0x00594525; read 1 byte(s), virtual slot 0x3a0.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x3a0.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_3a0(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x3a0(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x3a0.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_3a0(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_3a0\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00594530..0x00594555; read 1 byte(s), virtual slot 0x3a4.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x3a4.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_3a4(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x3a4(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x3a4.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_3a4(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_3a4\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x005946b0..0x005946d5; read 4 byte(s), virtual slot 0x3b8.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x3b8.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_3b8(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x3b8(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x3b8.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_3b8(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_3b8\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x005946e0..0x00594705; read 1 byte(s), virtual slot 0x3bc.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x3bc.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_3bc(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x3bc(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x3bc.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_3bc(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_3bc\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00594710..0x00594735; read 4 byte(s), virtual slot 0x3c0.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x3c0.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_3c0(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x3c0(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x3c0.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_3c0(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_3c0\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00594790..0x005947b5; read 1 byte(s), virtual slot 0x3c8.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x3c8.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_3c8(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x3c8(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x3c8.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_3c8(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_3c8\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00594830..0x00594855; read 1 byte(s), virtual slot 0x3d0.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x3d0.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_3d0(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x3d0(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x3d0.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_3d0(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_3d0\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00594a30..0x00594a55; read 4 byte(s), virtual slot 0x3f0.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x3f0.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_3f0(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x3f0(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x3f0.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_3f0(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_3f0\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00594bd0..0x00594bf5; read 4 byte(s), virtual slot 0x404.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x404.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_404(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x404(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x404.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_404(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_404\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00594ca0..0x00594cc5; read 4 byte(s), virtual slot 0x410.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x410.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_410(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x410(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x410.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_410(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_410\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00594e90..0x00594eb5; read 1 byte(s), virtual slot 0x428.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x428.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_428(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x428(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x428.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_428(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_428\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00594fa0..0x00594fc5; read 1 byte(s), virtual slot 0x434.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x434.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_434(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x434(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x434.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_434(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_434\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00594fd0..0x00594ff5; read 4 byte(s), virtual slot 0x43c.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x43c.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_43c(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x43c(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x43c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_43c(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_43c\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00595060..0x00595085; read 1 byte(s), virtual slot 0x444.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x444.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_444(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x444(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x444.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_444(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_444\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00595220..0x00595245; read 1 byte(s), virtual slot 0x460.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x460.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_460(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x460(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x460.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_460(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_460\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x005952b0..0x005952d5; read 4 byte(s), virtual slot 0x468.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x468.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_468(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x468(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x468.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_468(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_468\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00595490..0x005954b5; read 4 byte(s), virtual slot 0x47c.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x47c.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_47c(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x47c(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x47c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_47c(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_47c\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00595530..0x00595555; read 1 byte(s), virtual slot 0x484.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x484.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_484(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x484(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x484.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_484(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_484\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00595560..0x00595585; read 1 byte(s), virtual slot 0x488.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x488.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_488(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x488(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x488.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_488(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_488\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x005958b0..0x005958d5; read 1 byte(s), virtual slot 0x4b4.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x4b4.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_4b4(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x4b4(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x4b4.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_4b4(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_4b4\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00595c40..0x00595c65; read 4 byte(s), virtual slot 0x4dc.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x4dc.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_4dc(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x4dc(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x4dc.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_4dc(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_4dc\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00595cc0..0x00595ce5; read 4 byte(s), virtual slot 0x4e4.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x4e4.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_4e4(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x4e4(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x4e4.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_4e4(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_4e4\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00595cf0..0x00595d15; read 1 byte(s), virtual slot 0x4e8.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x4e8.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_4e8(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x4e8(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x4e8.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_4e8(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_4e8\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00595f00..0x00595f25; read 1 byte(s), virtual slot 0x4fc.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x4fc.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_4fc(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x4fc(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x4fc.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_4fc(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_4fc\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00596080..0x005960a5; read 1 byte(s), virtual slot 0x514.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x514.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_514(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x514(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x514.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_514(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_514\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x005961e0..0x00596205; read 4 byte(s), virtual slot 0x524.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x524.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_524(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x524(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x524.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_524(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_524\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00596260..0x00596285; read 4 byte(s), virtual slot 0x530.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x530.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_530(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x530(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x530.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_530(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_530\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x005962e0..0x00596305; read 2 byte(s), virtual slot 0x538.
/**
 * @brief Decode a 2-byte field and invoke session vtable byte offset 0x538.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 2 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u16_to_session_slot_538(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 2);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x538(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x538.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u16_to_session_slot_538(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u16_to_session_slot_538\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00596400..0x00596425; read 4 byte(s), virtual slot 0x544.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x544.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_544(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x544(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x544.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_544(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_544\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00596430..0x00596455; read 4 byte(s), virtual slot 0x54c.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x54c.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_54c(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x54c(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x54c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_54c(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_54c\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00596460..0x00596485; read 1 byte(s), virtual slot 0x550.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x550.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_550(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x550(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x550.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_550(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_550\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00596500..0x00596525; read 4 byte(s), virtual slot 0x558.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x558.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_558(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x558(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x558.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_558(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_558\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00596530..0x00596555; read 4 byte(s), virtual slot 0x55c.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x55c.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_55c(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x55c(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x55c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_55c(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_55c\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00596560..0x00596585; read 4 byte(s), virtual slot 0x560.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x560.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_560(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x560(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x560.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_560(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_560\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00596590..0x005965b5; read 4 byte(s), virtual slot 0x564.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x564.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_564(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x564(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x564.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_564(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_564\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x005965c0..0x005965e5; read 4 byte(s), virtual slot 0x568.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x568.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_568(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x568(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x568.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_568(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_568\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00596dc0..0x00596de5; read 4 byte(s), virtual slot 0x584.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x584.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_584(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x584(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x584.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_584(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_584\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00596df0..0x00596e15; read 4 byte(s), virtual slot 0x588.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x588.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_588(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x588(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x588.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_588(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_588\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00596fa0..0x00596fc5; read 1 byte(s), virtual slot 0x2c4.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x2c4.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_2c4(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x2c4(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x2c4.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_2c4(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_2c4\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00597220..0x00597245; read 4 byte(s), virtual slot 0x5b4.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x5b4.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_5b4(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x5b4(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x5b4.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_5b4(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_5b4\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x005976a0..0x005976c5; read 1 byte(s), virtual slot 0x604.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x604.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_604(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x604(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x604.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_604(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_604\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x005978c0..0x005978e5; read 4 byte(s), virtual slot 0x5ec.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x5ec.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_5ec(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x5ec(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x5ec.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_5ec(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_5ec\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00597a00..0x00597a25; read 4 byte(s), virtual slot 0x60c.
/**
 * @brief Decode a 4-byte field and invoke session vtable byte offset 0x60c.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u32_to_session_slot_60c(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x60c(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x60c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u32_to_session_slot_60c(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u32_to_session_slot_60c\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}

// Original 0x00597d40..0x00597d65; read 1 byte(s), virtual slot 0x618.
/**
 * @brief Decode a 1-byte field and invoke session vtable byte offset 0x618.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original four-byte PUSH ECX slot; unread upper bytes retain incoming ECX.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_u8_to_session_slot_618(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch, 1);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value = read_word(scratch);
    uint32_t result;
    __asm__ volatile("movl %1,%%ecx\n\tmovl %2,%%eax\n\t"
                     "movl (%%ecx),%%edx\n\tpushl %%eax\n\tcall *0x618(%%edx)"
                     : "=a"(result)
                     : "m"(receiver), "m"(value)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
// Preserve PUSH ECX inherited upper bytes and actual private address. Only
// this architecture storage/entry bridge is assembly; consumer logic is C++.
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x618.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_u8_to_session_slot_618(PacketReader* reader) {
    __asm__ volatile("pushl %ecx\n\tleal 8(%esp),%eax\n\tmovl %esp,%edx\n\t"
                     "pushl %edx\n\tpushl %eax\n\tcall _decode_packet_u8_to_session_slot_618\n\t"
                     "addl $8,%esp\n\tpopl %ecx\n\tret");
}
