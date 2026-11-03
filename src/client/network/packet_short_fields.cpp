#include "packet_short_fields.h"
namespace {
uint32_t byte(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movzbl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
void zero51(void* pointer) {
    uint32_t count = 12;
    __asm__ volatile("rep stosl\n\tstosw\n\tstosb"
                     : "+D"(pointer), "+c"(count)
                     : "a"(0u)
                     : "memory");
}
} // namespace
// Complete original 005952e0..0059534a and 005954c0..0059552a.
// Precisely 51 bytes are initialized; the remaining original frame is inherited.
extern "C" __attribute__((noinline)) void prepare_short_text(PacketReader* reader, uint8_t* frame) {
    zero51(frame + 8);
    read_packet_bytes_with_diagnostic(reader, frame + 4, 4);
    read_packet_bytes_with_diagnostic(reader, frame, 1);
    const uint32_t length = byte(frame);
    read_available_packet_bytes(reader, frame + 8, length);
}
extern "C" __attribute__((naked)) void fun_005952e0(PacketReader*) {
    __asm__ volatile(
        "subl $60,%esp\n\tpushl %esi\n\tmovl 68(%esp),%esi\n\tpushl %edi\n\t"
        "leal 8(%esp),%edx\n\tpushl %edx\n\tpushl %esi\n\tcalll _prepare_short_text\n\taddl $8,%esp\n\t"
        "leal 67(%esp),%edi\n\tmovl _dat_0224a328,%ecx\n\tmovl (%ecx),%edx\n\t"
        "leal 16(%esp),%eax\n\tpushl %eax\n\tmovl 12(%esp),%eax\n\tpushl %eax\n\t"
        "movl 20(%esp),%eax\n\tpushl %eax\n\tcalll *0x46c(%edx)\n\t"
        "popl %edi\n\tpopl %esi\n\taddl $60,%esp\n\tretl");
}
extern "C" __attribute__((naked)) void fun_005954c0(PacketReader*) {
    __asm__ volatile(
        "subl $60,%esp\n\tpushl %esi\n\tmovl 68(%esp),%esi\n\tpushl %edi\n\t"
        "leal 8(%esp),%edx\n\tpushl %edx\n\tpushl %esi\n\tcalll _prepare_short_text\n\taddl $8,%esp\n\t"
        "leal 67(%esp),%edi\n\tmovl _dat_0224a328,%ecx\n\tmovl (%ecx),%edx\n\t"
        "leal 16(%esp),%eax\n\tpushl %eax\n\tmovl 12(%esp),%eax\n\tpushl %eax\n\t"
        "movl 20(%esp),%eax\n\tpushl %eax\n\tcalll *0x480(%edx)\n\t"
        "popl %edi\n\tpopl %esi\n\taddl $60,%esp\n\tretl");
}
// Complete original 00592e80..00592f14. Only status == 1 reads further fields.
extern "C" __attribute__((noinline)) void prepare_00592e80(PacketReader* reader, uint8_t* frame) {
    read_packet_bytes_with_diagnostic(reader, frame, 1);
    if (byte(frame) == 1) {
        read_packet_bytes_with_diagnostic(reader, frame + 20, 2);
        read_packet_bytes_with_diagnostic(reader, frame + 16, 2);
        read_packet_bytes_with_diagnostic(reader, frame + 12, 1);
        read_packet_bytes_with_diagnostic(reader, frame + 8, 1);
        read_packet_bytes_with_diagnostic(reader, frame + 4, 1);
    }
}
extern "C" __attribute__((naked)) void fun_00592e80(PacketReader*) {
    __asm__ volatile(
        "subl $24,%esp\n\tpushl %esi\n\tmovl 32(%esp),%esi\n\t"
        "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %esi\n\tcalll _prepare_00592e80\n\taddl $8,%esp\n\t"
        "movl 8(%esp),%edx\n\tmovl _dat_0224a328,%ecx\n\tmovl (%ecx),%eax\n\tpushl %edx\n\t"
        "movl 16(%esp),%edx\n\tpushl %edx\n\tmovl 24(%esp),%edx\n\tpushl %edx\n\t"
        "movl 32(%esp),%edx\n\tpushl %edx\n\tmovl 40(%esp),%edx\n\tpushl %edx\n\t"
        "movl 24(%esp),%edx\n\tpushl %edx\n\tcalll *0x2c8(%eax)\n\t"
        "popl %esi\n\taddl $24,%esp\n\tretl");
}
// Complete original 00595680..0059573a. Full DWORD callback loads are retained.
extern "C" __attribute__((noinline)) void prepare_00595680(PacketReader* reader, uint8_t* frame) {
    read_packet_bytes_with_diagnostic(reader, frame, 1);
    if (byte(frame) == 1) {
        read_packet_bytes_with_diagnostic(reader, frame + 28, 2);
        read_packet_bytes_with_diagnostic(reader, frame + 24, 2);
        read_packet_bytes_with_diagnostic(reader, frame + 20, 2);
        read_packet_bytes_with_diagnostic(reader, frame + 16, 2);
        read_packet_bytes_with_diagnostic(reader, frame + 12, 2);
        read_packet_bytes_with_diagnostic(reader, frame + 8, 2);
        read_packet_bytes_with_diagnostic(reader, frame + 4, 2);
    }
}
extern "C" __attribute__((naked)) void fun_00595680(PacketReader*) {
    __asm__ volatile(
        "subl $32,%esp\n\tpushl %esi\n\tmovl 40(%esp),%esi\n\t"
        "leal 4(%esp),%edx\n\tpushl %edx\n\tpushl %esi\n\tcalll _prepare_00595680\n\taddl $8,%esp\n\t"
        "movl 8(%esp),%eax\n\tmovl _dat_0224a328,%ecx\n\tpushl %eax\n\tmovl 16(%esp),%eax\n\t"
        "movl (%ecx),%edx\n\tpushl %eax\n\tmovl 24(%esp),%eax\n\tpushl %eax\n\t"
        "movl 32(%esp),%eax\n\tpushl %eax\n\tmovl 40(%esp),%eax\n\tpushl %eax\n\t"
        "movl 48(%esp),%eax\n\tpushl %eax\n\tmovl 56(%esp),%eax\n\tpushl %eax\n\t"
        "movl 32(%esp),%eax\n\tpushl %eax\n\tcalll *0x494(%edx)\n\t"
        "popl %esi\n\taddl $32,%esp\n\tretl");
}
