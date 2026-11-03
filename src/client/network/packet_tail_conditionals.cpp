#include "packet_tail_conditionals.h"
namespace {
uint32_t word(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
uint32_t byte(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movzbl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
void put(uint32_t* target, uint32_t value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(target), "r"(value) : "memory");
}
void session(uint32_t* state) {
    const uint32_t receiver = word(&dat_0224a328);
    const uint32_t table = word(reinterpret_cast<void*>(receiver));
    put(state, receiver);
    put(state + 1, table);
}
} // namespace
extern "C" __attribute__((noinline)) void prepare_00590e80(PacketReader* reader, uint8_t* frame,
                                                           uint32_t* state) {
    read_packet_bytes_with_diagnostic(reader, frame, 1);
    uint32_t count_word = word(frame);
    uint8_t index = 0;
    if (static_cast<uint8_t>(count_word)) {
        do {
            read_packet_bytes_with_diagnostic(reader, frame + 24 + index, 1);
            read_packet_bytes_with_diagnostic(reader, frame + 4 + index, 1);
            count_word = word(frame);
            index = static_cast<uint8_t>(index + 1);
        } while (index < static_cast<uint8_t>(count_word));
    }
    put(state + 2, count_word); // Original EAX is cached before session loads.
    put(state + 3, index);
    session(state);
}
extern "C" __attribute__((noinline)) void prepare_00595740(PacketReader* reader, uint8_t* frame,
                                                           uint32_t* state) {
    __asm__ volatile("movb $0,(%0)" ::"r"(frame) : "memory");
    read_packet_bytes_with_diagnostic(reader, frame + 4, 1);
    if (byte(frame + 4) == 1) {
        read_packet_bytes_with_diagnostic(reader, frame + 8, 2);
        const uint32_t cursor = word(&reader->cursor);
        const uint32_t length = word(&reader->length);
        if (cursor - reinterpret_cast<uintptr_t>(reader) < length)
            read_packet_bytes_with_diagnostic(reader, frame, 1);
    }
    put(state + 2, word(frame)); // Cached optional flag DWORD precedes session.
    session(state);
}
extern "C" __attribute__((noinline)) void prepare_005957c0(PacketReader* reader, uint8_t* frame,
                                                           uint32_t* state) {
    read_packet_bytes_with_diagnostic(reader, frame + 8, 4);
    read_packet_bytes_with_diagnostic(reader, frame + 4, 1);
    if (byte(frame + 4)) {
        read_packet_bytes_with_diagnostic(reader, frame + 3, 1);
        const uint32_t length = byte(frame + 3);
        read_available_packet_bytes(reader, frame + 12, length);
    }
    session(state);
}
// Helpers finish below the original public frames before any virtual callback.
// No array bounds, initialization of inherited bytes, or rejection is invented.
extern "C" __attribute__((naked)) void fun_00590e80(PacketReader*) {
    __asm__ volatile(
        "subl $44,%esp\n\tpushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tmovl 60(%esp),%edi\n\t"
        "subl $16,%esp\n\tmovl %esp,%eax\n\tleal 28(%esp),%edx\n\tpushl %eax\n\tpushl %edx\n\tpushl %edi\n\t"
        "calll _prepare_00590e80\n\taddl $12,%esp\n\tmovl (%esp),%ecx\n\tmovl 4(%esp),%edx\n\t"
        "movb 12(%esp),%bl\n\tmovl 8(%esp),%eax\n\taddl $16,%esp\n\t"
        "leal 16(%esp),%esi\n\tpushl %esi\n\tleal 40(%esp),%esi\n\tpushl %esi\n\tpushl %eax\n\tcalll *0x1b0(%edx)\n\t"
        "popl %edi\n\tpopl %esi\n\tpopl %ebx\n\taddl $44,%esp\n\tretl");
}
extern "C" __attribute__((naked)) void fun_00595740(PacketReader*) {
    __asm__ volatile(
        "subl $12,%esp\n\tpushl %esi\n\tmovl 20(%esp),%esi\n\tsubl $12,%esp\n\t"
        "movl %esp,%eax\n\tleal 16(%esp),%edx\n\tpushl %eax\n\tpushl %edx\n\tpushl %esi\n\t"
        "calll _prepare_00595740\n\taddl $12,%esp\n\tmovl (%esp),%ecx\n\tmovl 4(%esp),%edx\n\t"
        "movl 8(%esp),%eax\n\taddl $12,%esp\n\tpushl %eax\n\tmovl 16(%esp),%eax\n\tpushl %eax\n\t"
        "movl 16(%esp),%eax\n\tpushl %eax\n\tcalll *0x498(%edx)\n\tpopl %esi\n\taddl $12,%esp\n\tretl");
}
extern "C" __attribute__((naked)) void fun_005957c0(PacketReader*) {
    __asm__ volatile(
        "subl $136,%esp\n\tpushl %esi\n\tmovl 144(%esp),%esi\n\tsubl $8,%esp\n\t"
        "movl %esp,%eax\n\tleal 12(%esp),%edx\n\tpushl %eax\n\tpushl %edx\n\tpushl %esi\n\t"
        "calll _prepare_005957c0\n\taddl $12,%esp\n\tmovl (%esp),%ecx\n\tmovl 4(%esp),%edx\n\taddl $8,%esp\n\t"
        "leal 16(%esp),%eax\n\tpushl %eax\n\tmovl 12(%esp),%eax\n\tpushl %eax\n\tmovl 20(%esp),%eax\n\t"
        "pushl %eax\n\tcalll *0x49c(%edx)\n\tpopl %esi\n\taddl $136,%esp\n\tretl");
}
