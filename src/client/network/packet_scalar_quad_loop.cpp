#include "packet_scalar_quad_loop.h"
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
extern "C" __attribute__((noinline)) uint32_t read_count_scalar_quad(PacketReader* reader,
                                                                     uint8_t* frame, uint32_t) {
    return read_packet_bytes_with_diagnostic(reader, frame + 3, 1);
}
// Original5969b0..596a3b and596aa0..596b2b share this complete reader/
// argument preparation. Each BYTE is read into an inherited DWORD; none of
// its upper bytes is cleared. The fourth scalar precedes the session lookup,
// and the other three are loaded after the table, in reverse argument order.
extern "C" __attribute__((noinline)) void read_scalar_quad(PacketReader* reader, uint8_t* frame,
                                                           uint32_t* outgoing, uint32_t* state) {
    read_packet_bytes_with_diagnostic(reader, frame + 16, 1);
    read_packet_bytes_with_diagnostic(reader, frame + 12, 1);
    read_packet_bytes_with_diagnostic(reader, frame + 8, 1);
    read_packet_bytes_with_diagnostic(reader, frame + 4, 1);
    const uint32_t fourth = word(frame + 4);
    auto* receiver = reinterpret_cast<SessionPrefix*>(word(&dat_0224a328));
    const uint32_t table = word(receiver);
    put(outgoing + 3, fourth);
    put(outgoing + 2, word(frame + 8));
    put(outgoing + 1, word(frame + 12));
    put(outgoing, word(frame + 16));
    put(state, reinterpret_cast<uint32_t>(receiver));
    put(state + 1, table);
}
// The small entry adapters retain the actual twenty-byte original frame,
// count-AL merge, ESI reader / EDI index, callbackSP E-48 and four stack
// DWORDs. Preparation has returned before the callback; it may use its full
// stack. Fresh MOVZX count after each call preserves callback-returned EAX.
#define SCALAR_QUAD_ENTRY(name, slot)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
    extern "C" __attribute__((naked)) void name(PacketReader*) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   \
        __asm__ volatile(                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          \
            "subl $20,%esp\n\tpushl %esi\n\tmovl 28(%esp),%esi\n\tpushl %edi\n\tpushl $1\n\tleal 12(%esp),%eax\n\tpushl %eax\n\tpushl %esi\n\tcall _read_count_scalar_quad\n\taddl $12,%esp\n\tmovb 11(%esp),%al\n\txorl %edi,%edi\n\ttestb %al,%al\n\tjbe 2f\n\t1:\n\tsubl $24,%esp\n\tmovl %esp,%eax\n\tleal 8(%esp),%edx\n\tleal 32(%esp),%ecx\n\tpushl %eax\n\tpushl %edx\n\tpushl %ecx\n\tpushl %esi\n\tcall _read_scalar_quad\n\taddl $16,%esp\n\tmovl (%esp),%ecx\n\tmovl 4(%esp),%edx\n\taddl $8,%esp\n\tmovl (%esp),%eax\n\tcall *" #slot \
            "(%edx)\n\tmovzbl 11(%esp),%ecx\n\tincl %edi\n\tcmpl %ecx,%edi\n\tjl 1b\n\t2:\n\tpopl %edi\n\tpopl %esi\n\taddl $20,%esp\n\tret");                                                                                                                                                                                                                                                                                                                                                                                                     \
    }
SCALAR_QUAD_ENTRY(fun_005969b0, 0x578)
SCALAR_QUAD_ENTRY(fun_00596aa0, 0x590)
#undef SCALAR_QUAD_ENTRY
