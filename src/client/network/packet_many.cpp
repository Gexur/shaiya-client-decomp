#include "packet_many.h"

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

// Original 0x0058f880..0x0058f97f, 12readers; exact owned load order below.
/**
 * @brief Decode 12 fields and invoke session vtable byte offset 0x0fc.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original 48-byte uninitialized frame, one DWORD slot per field.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_12_dwords_to_session_slot_0fc(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 44, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 40, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 36, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 32, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t table = read_word(receiver);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t value_7 = read_word(scratch + 28);
    const uint32_t value_8 = read_word(scratch + 32);
    const uint32_t value_9 = read_word(scratch + 36);
    const uint32_t value_10 = read_word(scratch + 40);
    const uint32_t value_11 = read_word(scratch + 44);
    const uint32_t call_words[12] = {value_0, value_1, value_2, value_3, value_4,  value_5,
                                     value_6, value_7, value_8, value_9, value_10, value_11};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl 0(%%edx)\n\tpushl 4(%%edx)\n\tpushl 8(%%edx)\n\tpushl 12(%%edx)\n\tpushl 16(%%edx)\n\tpushl 20(%%edx)\n\tpushl 24(%%edx)\n\tpushl 28(%%edx)\n\tpushl 32(%%edx)\n\tpushl 36(%%edx)\n\tpushl 40(%%edx)\n\tmovl 44(%%edx),%%edx\n\tpushl %%edx\n\tcall *0xfc(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
/**
 * @brief Read 12 fields (48 wire bytes) and call session vtable byte offset 0x0fc.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_12_dwords_to_session_slot_0fc(PacketReader* reader) {
    __asm__ volatile(
        "subl $48,%esp\n\tpushl %esi\n\tleal 56(%esp),%eax\n\t"
        "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _decode_packet_12_dwords_to_session_slot_0fc\n\t"
        "addl $8,%esp\n\tpopl %esi\n\taddl $48,%esp\n\tret");
}

// Original 0x00590030..0x0059011c, 11readers; exact owned load order below.
/**
 * @brief Decode 11 fields and invoke session vtable byte offset 0x150.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original 44-byte uninitialized frame, one DWORD slot per field.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1, 4, 4, 2, 1, 2, 2, 2, 2, 2, 2 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_11_mixed_fields_to_session_slot_150(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 40, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 36, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 32, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t value_7 = read_word(scratch + 28);
    const uint32_t value_8 = read_word(scratch + 32);
    const uint32_t value_9 = read_word(scratch + 36);
    const uint32_t value_10 = read_word(scratch + 40);
    const uint32_t call_words[11] = {value_0, value_1, value_2, value_3, value_4, value_5,
                                     value_6, value_7, value_8, value_9, value_10};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tpushl 24(%%eax)\n\tpushl 28(%%eax)\n\tpushl 32(%%eax)\n\tpushl 36(%%eax)\n\tmovl 40(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x150(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
/**
 * @brief Read 11 fields (24 wire bytes) and call session vtable byte offset 0x150.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1, 4, 4, 2, 1, 2, 2, 2, 2, 2, 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_11_mixed_fields_to_session_slot_150(PacketReader* reader) {
    __asm__ volatile(
        "subl $44,%esp\n\tpushl %esi\n\tleal 52(%esp),%eax\n\t"
        "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _decode_packet_11_mixed_fields_to_session_slot_150\n\t"
        "addl $8,%esp\n\tpopl %esi\n\taddl $44,%esp\n\tret");
}

// Original 0x00590430..0x0059051c, 11readers; exact owned load order below.
/**
 * @brief Decode 11 fields and invoke session vtable byte offset 0x168.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original 44-byte uninitialized frame, one DWORD slot per field.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1, 4, 4, 2, 1, 2, 2, 2, 2, 2, 2 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_11_mixed_fields_to_session_slot_168(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 40, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 36, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 32, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t value_7 = read_word(scratch + 28);
    const uint32_t value_8 = read_word(scratch + 32);
    const uint32_t value_9 = read_word(scratch + 36);
    const uint32_t value_10 = read_word(scratch + 40);
    const uint32_t call_words[11] = {value_0, value_1, value_2, value_3, value_4, value_5,
                                     value_6, value_7, value_8, value_9, value_10};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tpushl 24(%%eax)\n\tpushl 28(%%eax)\n\tpushl 32(%%eax)\n\tpushl 36(%%eax)\n\tmovl 40(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x168(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
/**
 * @brief Read 11 fields (24 wire bytes) and call session vtable byte offset 0x168.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1, 4, 4, 2, 1, 2, 2, 2, 2, 2, 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_11_mixed_fields_to_session_slot_168(PacketReader* reader) {
    __asm__ volatile(
        "subl $44,%esp\n\tpushl %esi\n\tleal 52(%esp),%eax\n\t"
        "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _decode_packet_11_mixed_fields_to_session_slot_168\n\t"
        "addl $8,%esp\n\tpopl %esi\n\taddl $44,%esp\n\tret");
}

// Original 0x005907a0..0x00590866, 9readers; exact owned load order below.
/**
 * @brief Decode 9 fields and invoke session vtable byte offset 0x17c.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original 36-byte uninitialized frame, one DWORD slot per field.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1, 4, 4, 1, 2, 1, 2, 2, 2 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_9_mixed_fields_to_session_slot_17c(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 32, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    const uint32_t value_1 = read_word(scratch + 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t table = read_word(receiver);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t value_7 = read_word(scratch + 28);
    const uint32_t value_8 = read_word(scratch + 32);
    const uint32_t call_words[9] = {value_0, value_1, value_2, value_3, value_4,
                                    value_5, value_6, value_7, value_8};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl 0(%%edx)\n\tpushl 4(%%edx)\n\tpushl 8(%%edx)\n\tpushl 12(%%edx)\n\tpushl 16(%%edx)\n\tpushl 20(%%edx)\n\tpushl 24(%%edx)\n\tpushl 28(%%edx)\n\tmovl 32(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x17c(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
/**
 * @brief Read 9 fields (19 wire bytes) and call session vtable byte offset 0x17c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1, 4, 4, 1, 2, 1, 2, 2, 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_9_mixed_fields_to_session_slot_17c(PacketReader* reader) {
    __asm__ volatile(
        "subl $36,%esp\n\tpushl %esi\n\tleal 44(%esp),%eax\n\t"
        "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _decode_packet_9_mixed_fields_to_session_slot_17c\n\t"
        "addl $8,%esp\n\tpopl %esi\n\taddl $36,%esp\n\tret");
}

// Original 0x00590870..0x0059096f, 12readers; exact owned load order below.
/**
 * @brief Decode 12 fields and invoke session vtable byte offset 0x180.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original 48-byte uninitialized frame, one DWORD slot per field.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1, 4, 4, 1, 2, 1, 2, 2, 2, 2, 2, 2 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_12_mixed_fields_to_session_slot_180(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 44, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 40, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 36, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 32, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 2);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t table = read_word(receiver);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t value_7 = read_word(scratch + 28);
    const uint32_t value_8 = read_word(scratch + 32);
    const uint32_t value_9 = read_word(scratch + 36);
    const uint32_t value_10 = read_word(scratch + 40);
    const uint32_t value_11 = read_word(scratch + 44);
    const uint32_t call_words[12] = {value_0, value_1, value_2, value_3, value_4,  value_5,
                                     value_6, value_7, value_8, value_9, value_10, value_11};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%edx\n\tmovl %3,%%eax\n\tpushl 0(%%edx)\n\tpushl 4(%%edx)\n\tpushl 8(%%edx)\n\tpushl 12(%%edx)\n\tpushl 16(%%edx)\n\tpushl 20(%%edx)\n\tpushl 24(%%edx)\n\tpushl 28(%%edx)\n\tpushl 32(%%edx)\n\tpushl 36(%%edx)\n\tpushl 40(%%edx)\n\tmovl 44(%%edx),%%edx\n\tpushl %%edx\n\tcall *0x180(%%eax)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
/**
 * @brief Read 12 fields (25 wire bytes) and call session vtable byte offset 0x180.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1, 4, 4, 1, 2, 1, 2, 2, 2, 2, 2, 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_12_mixed_fields_to_session_slot_180(PacketReader* reader) {
    __asm__ volatile(
        "subl $48,%esp\n\tpushl %esi\n\tleal 56(%esp),%eax\n\t"
        "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _decode_packet_12_mixed_fields_to_session_slot_180\n\t"
        "addl $8,%esp\n\tpopl %esi\n\taddl $48,%esp\n\tret");
}

// Original 0x00591690..0x005917a2, 13readers; exact owned load order below.
/**
 * @brief Decode 13 fields and invoke session vtable byte offset 0x1c8.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original 52-byte uninitialized frame, one DWORD slot per field.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_13_mixed_fields_to_session_slot_1c8(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 48, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 44, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 40, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 36, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 32, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 4);
    const uint32_t value_0 = read_word(scratch + 0);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t table = read_word(receiver);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t value_7 = read_word(scratch + 28);
    const uint32_t value_8 = read_word(scratch + 32);
    const uint32_t value_9 = read_word(scratch + 36);
    const uint32_t value_10 = read_word(scratch + 40);
    const uint32_t value_11 = read_word(scratch + 44);
    const uint32_t value_12 = read_word(scratch + 48);
    const uint32_t call_words[13] = {value_0,  value_1,  value_2, value_3, value_4,
                                     value_5,  value_6,  value_7, value_8, value_9,
                                     value_10, value_11, value_12};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tpushl 24(%%eax)\n\tpushl 28(%%eax)\n\tpushl 32(%%eax)\n\tpushl 36(%%eax)\n\tpushl 40(%%eax)\n\tpushl 44(%%eax)\n\tmovl 48(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x1c8(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
/**
 * @brief Read 13 fields (16 wire bytes) and call session vtable byte offset 0x1c8.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_13_mixed_fields_to_session_slot_1c8(PacketReader* reader) {
    __asm__ volatile(
        "subl $52,%esp\n\tpushl %esi\n\tleal 60(%esp),%eax\n\t"
        "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _decode_packet_13_mixed_fields_to_session_slot_1c8\n\t"
        "addl $8,%esp\n\tpopl %esi\n\taddl $52,%esp\n\tret");
}

// Original 0x00591c00..0x00591cd9, 10readers; exact owned load order below.
/**
 * @brief Decode 10 fields and invoke session vtable byte offset 0x200.
 * @param actual_arguments Address of the original cdecl reader argument word.
 * @param scratch Original 40-byte uninitialized frame, one DWORD slot per field.
 * @return Physical EAX left by the virtual callback; its semantic result is unknown.
 * @note Wire read widths, in order: 4, 2, 1, 1, 4, 4, 1, 1, 1, 1 byte(s).
 *       Each call argument is loaded as a full DWORD, including untouched scratch bytes.
 *       Reader callback effects, receiver reload timing, and ignored read results are preserved.
 */
extern "C" __attribute__((noinline)) uint32_t
decode_packet_10_mixed_fields_to_session_slot_200(const void* actual_arguments, uint8_t* scratch) {
    auto* reader = reinterpret_cast<PacketReader*>(read_word(actual_arguments));
    read_packet_bytes_with_diagnostic(reader, scratch + 36, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 32, 2);
    read_packet_bytes_with_diagnostic(reader, scratch + 28, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 24, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 20, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 16, 4);
    read_packet_bytes_with_diagnostic(reader, scratch + 12, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 8, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 4, 1);
    read_packet_bytes_with_diagnostic(reader, scratch + 0, 1);
    const uint32_t value_0 = read_word(scratch + 0);
    const uint32_t value_1 = read_word(scratch + 4);
    const uint32_t value_2 = read_word(scratch + 8);
    auto* receiver = reinterpret_cast<SessionPrefix*>(read_word(&dat_0224a328));
    const uint32_t value_3 = read_word(scratch + 12);
    const uint32_t table = read_word(receiver);
    const uint32_t value_4 = read_word(scratch + 16);
    const uint32_t value_5 = read_word(scratch + 20);
    const uint32_t value_6 = read_word(scratch + 24);
    const uint32_t value_7 = read_word(scratch + 28);
    const uint32_t value_8 = read_word(scratch + 32);
    const uint32_t value_9 = read_word(scratch + 36);
    const uint32_t call_words[10] = {value_0, value_1, value_2, value_3, value_4,
                                     value_5, value_6, value_7, value_8, value_9};
    uint32_t result;
    __asm__ volatile(
        "movl %1,%%ecx\n\tmovl %2,%%eax\n\tmovl %3,%%edx\n\tpushl 0(%%eax)\n\tpushl 4(%%eax)\n\tpushl 8(%%eax)\n\tpushl 12(%%eax)\n\tpushl 16(%%eax)\n\tpushl 20(%%eax)\n\tpushl 24(%%eax)\n\tpushl 28(%%eax)\n\tpushl 32(%%eax)\n\tmovl 36(%%eax),%%eax\n\tpushl %%eax\n\tcall *0x200(%%edx)"
        : "=a"(result)
        : "m"(receiver), "r"(call_words), "m"(table)
        : "ecx", "edx", "memory", "cc");
    return result;
}
/**
 * @brief Read 10 fields (20 wire bytes) and call session vtable byte offset 0x200.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4, 2, 1, 1, 4, 4, 1, 1, 1, 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
extern "C" __attribute__((naked)) void
dispatch_packet_10_mixed_fields_to_session_slot_200(PacketReader* reader) {
    __asm__ volatile(
        "subl $40,%esp\n\tpushl %esi\n\tleal 48(%esp),%eax\n\t"
        "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcall _decode_packet_10_mixed_fields_to_session_slot_200\n\t"
        "addl $8,%esp\n\tpopl %esi\n\taddl $40,%esp\n\tret");
}
