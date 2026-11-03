#include "packet_record_loop.h"
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
extern "C" __attribute__((noinline)) void read_count_00596950(PacketReader* reader, uint8_t* frame,
                                                              uint32_t) {
    read_packet_bytes_with_diagnostic(reader, frame, 1);
}
// Complete original596950..5969aa algorithm. The original private payload is
// only60 bytes. There is no original rejection/truncation for count>4: retain
// its unchecked reader calls rather than introducing a new protocol policy.
extern "C" __attribute__((noinline)) void
read_records_00596950(PacketReader* reader, uint8_t* frame, uint32_t* callback_state) {
    uint32_t count = word(frame), index = 0;
    if ((count & 255u) != 0) {
        uint8_t* output = frame + 4;
        do {
            read_packet_bytes_with_diagnostic(reader, output, 15);
            count = word(frame);
            ++index;
            output += 15;
        } while (static_cast<int32_t>(index) < static_cast<int32_t>(count & 255u));
    }
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    put(callback_state, reinterpret_cast<uint32_t>(receiver));
    put(callback_state + 1, table);
    put(callback_state + 2, count);
}
extern "C" __attribute__((naked)) void fun_00596950(PacketReader*) {
    // Exact64-byte frame and callbackSP E-84. C++ preparation is complete
    // before the real virtual call; no helper frame is suspended below it.
    __asm__ volatile(
        "subl $64,%esp\n\tpushl %ebx\n\tmovl 72(%esp),%ebx\n\tpushl %esi\n\tpushl $1\n\tleal 12(%esp),%eax\n\tpushl %eax\n\tpushl %ebx\n\tcall _read_count_00596950\n\taddl $12,%esp\n\tsubl $12,%esp\n\tmovl %esp,%eax\n\tleal 20(%esp),%ecx\n\tpushl %eax\n\tpushl %ecx\n\tpushl %ebx\n\tcall _read_records_00596950\n\taddl $12,%esp\n\tmovl (%esp),%ecx\n\tmovl 4(%esp),%edx\n\tmovl 8(%esp),%eax\n\taddl $12,%esp\n\tleal 12(%esp),%esi\n\tpushl %esi\n\tpushl %eax\n\tcall *0x52c(%edx)\n\tpopl %esi\n\tpopl %ebx\n\taddl $64,%esp\n\tret");
}
