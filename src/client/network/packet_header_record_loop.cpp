#include "packet_header_record_loop.h"
namespace {
uint32_t word(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
void put(void* pointer, uint32_t value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(pointer), "r"(value) : "memory");
}
} // namespace
extern "C" __attribute__((noinline)) void read_header_005970e0(PacketReader* reader, uint8_t* frame,
                                                               uint32_t) {
    read_packet_bytes_with_diagnostic(reader, frame + 4, 4);
}
extern "C" __attribute__((noinline)) void read_count_005970e0(PacketReader* reader, uint8_t* frame,
                                                              uint32_t) {
    read_packet_bytes_with_diagnostic(reader, frame, 1);
}
// Complete original5970e0..59715c algorithm. The actual2908-byte frame owns
// only2900 payload bytes. Counts above100 remain unchecked, as in the binary.
extern "C" __attribute__((noinline)) void
read_records_005970e0(PacketReader* reader, uint8_t* frame, uint32_t* outgoing, uint32_t* state) {
    uint32_t count = word(frame), index = 0;
    if ((count & 255u) != 0) {
        uint8_t* output = frame + 8;
        do {
            read_packet_bytes_with_diagnostic(reader, output, 29);
            count = word(frame);
            ++index;
            output += 29;
        } while (static_cast<int32_t>(index) < static_cast<int32_t>(count & 255u));
    }
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    put(outgoing + 2, reinterpret_cast<uint32_t>(frame + 8));
    put(outgoing + 1, count);
    put(outgoing, word(frame + 4)); // original late header reload after table
    put(state, reinterpret_cast<uint32_t>(receiver));
    put(state + 1, table);
}
extern "C" __attribute__((naked)) void fun_005970e0(PacketReader*) {
    // Exact original frame, EBX reader/ESI payload and callbackSP E-2932.
    // C++ preparation is finished before the actual virtual call.
    __asm__ volatile(
        "subl $2908,%esp\n\tpushl %ebx\n\tmovl 2916(%esp),%ebx\n\tpushl %esi\n\tpushl $4\n\tleal 12(%esp),%eax\n\tpushl %eax\n\tpushl %ebx\n\tcall _read_header_005970e0\n\taddl $12,%esp\n\tpushl $1\n\tleal 12(%esp),%eax\n\tpushl %eax\n\tpushl %ebx\n\tcall _read_count_005970e0\n\taddl $12,%esp\n\tsubl $20,%esp\n\tmovl %esp,%eax\n\tleal 8(%esp),%edx\n\tleal 28(%esp),%ecx\n\tpushl %eax\n\tpushl %edx\n\tpushl %ecx\n\tpushl %ebx\n\tcall _read_records_005970e0\n\taddl $16,%esp\n\tmovl (%esp),%ecx\n\tmovl 4(%esp),%edx\n\taddl $8,%esp\n\tleal 28(%esp),%esi\n\tmovl (%esp),%eax\n\tcall *0x5ac(%edx)\n\tpopl %esi\n\tpopl %ebx\n\taddl $2908,%esp\n\tret");
}
