#include "packet_byvalue_storage.h"
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
// Complete original58d790..58d7d3. Its first scalar is read before the
// current session/table; remaining reads interleave with outgoing DWORD stores.
// Callback state is an adapter-local record, not a recovered client type.
// The C++ helper returns before the callback uses the outgoing stack area,
// leaving no suspended helper frame for a real callback to overwrite.
extern "C" __attribute__((noinline)) void byvalue_storage_0058d790(const void* arguments,
                                                                   uint8_t* frame,
                                                                   uint8_t* outgoing,
                                                                   uint32_t* callback_state) {
    auto* reader = reinterpret_cast<PacketReader*>(word(arguments));
    read_packet_bytes_with_diagnostic(reader, frame, 16);
    const uint32_t first = word(frame);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    put(outgoing, first);
    put(outgoing + 4, word(frame + 4));
    put(outgoing + 8, word(frame + 8));
    const uint32_t last = word(frame + 12);
    put(outgoing + 12, last);
    put(callback_state, reinterpret_cast<uint32_t>(receiver));
    put(callback_state + 1, table);
    put(callback_state + 2, last);
}
extern "C" __attribute__((naked)) void fun_0058d790(PacketReader*) {
    __asm__ volatile(
        "subl $16,%esp\n\tpushl %esi\n\tsubl $16,%esp\n\tsubl $16,%esp\n\tmovl %esp,%eax\n\tleal 16(%esp),%edx\n\tleal 36(%esp),%ecx\n\tpushl %eax\n\tpushl %edx\n\tpushl %ecx\n\tleal 68(%esp),%eax\n\tpushl %eax\n\tcall _byvalue_storage_0058d790\n\taddl $16,%esp\n\tmovl (%esp),%ecx\n\tmovl 4(%esp),%edx\n\tmovl 8(%esp),%esi\n\tleal 16(%esp),%eax\n\taddl $16,%esp\n\tcall *(%edx)\n\tpopl %esi\n\taddl $16,%esp\n\tret");
}
