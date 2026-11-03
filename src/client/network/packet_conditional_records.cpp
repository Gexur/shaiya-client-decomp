#include "packet_conditional_records.h"
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
uint32_t half(const void* pointer) {
    uint32_t value;
    __asm__ volatile("movzwl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
void zero_word(void* pointer) {
    __asm__ volatile("movl $0,(%0)" ::"r"(pointer) : "memory");
}
void zero_byte(void* pointer) {
    __asm__ volatile("movb $0,(%0)" ::"r"(pointer) : "memory");
}
void clear(void* pointer, uint32_t count) {
    __asm__ volatile("rep stosl" : "+D"(pointer), "+c"(count) : "a"(0u) : "memory");
}
void put(uint32_t* pointer, uint32_t value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(pointer), "r"(value) : "memory");
}
void session(uint32_t* state) {
    const uint32_t receiver = word(&dat_0224a328);
    const uint32_t table = word(reinterpret_cast<const void*>(receiver));
    put(state + 1, receiver);
    put(state + 2, table);
}
} // namespace
// Complete original005935a0..0059363d, including both RET0 branches.
extern "C" __attribute__((noinline)) void prepare_005935a0(const void* actual_arguments,
                                                           uint8_t* frame, uint32_t* state) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    put(state, reinterpret_cast<uint32_t>(reader));
    clear(frame + 16, 32);
    read_packet_bytes_with_diagnostic(reader, frame + 7, 1);
    read_packet_bytes_with_diagnostic(reader, frame + 12, 4);
    read_packet_bytes_with_diagnostic(reader, frame + 8, 1);
    const uint32_t length = byte(frame + 8);
    read_available_packet_bytes(reader, frame + 16, length);
    const uint32_t flag = byte(frame + 7);
    put(state + 3, flag ? 5u : 4u);
    session(state);
}
extern "C" __attribute__((naked)) void fun_005935a0(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $144,%esp\n\tpushl %esi\n\tpushl %edi\n\t"
        "leal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tsubl $16,%esp\n\tmovl %esp,%ecx\n\t"
        "pushl %ecx\n\tpushl %edx\n\tpushl %eax\n\tcalll _prepare_005935a0\n\taddl $12,%esp\n\t"
        "movl (%esp),%esi\n\tmovl 4(%esp),%ecx\n\tmovl 8(%esp),%edx\n\tmovl 12(%esp),%eax\n\taddl $16,%esp\n\t"
        "leal 152(%esp),%edi\n\tcmpl $4,%eax\n\tje 1f\n\t"
        "leal 24(%esp),%eax\n\tpushl %eax\n\tmovl 20(%esp),%eax\n\tpushl %eax\n\tleal 28(%esp),%eax\n\tpushl %eax\n\tpushl $5\n\tjmp 2f\n\t"
        "1: leal 24(%esp),%eax\n\tpushl %eax\n\tmovl 20(%esp),%eax\n\tpushl %eax\n\tleal 28(%esp),%eax\n\tpushl %eax\n\tpushl $4\n\t"
        "2: pushl $0\n\tpushl $0\n\tcalll *0x2ec(%edx)\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tretl");
}
// Complete original00593ab0..00593b78. The initial zero WORD skips all further
// parsing and callback, preserving the actual first reader's physical EAX.
extern "C" __attribute__((noinline)) void prepare_00593ab0(const void* actual_arguments,
                                                           uint8_t* frame, uint32_t* state) {
    zero_word(frame + 16);
    zero_word(frame + 20);
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    put(state, reinterpret_cast<uint32_t>(reader));
    zero_word(frame + 24);
    zero_word(frame + 28);
    zero_word(frame + 32);
    clear(frame + 40, 250);
    zero_byte(frame + 36);
    const uint32_t first_result = read_packet_bytes_with_diagnostic(reader, frame + 4, 2);
    const uint32_t status = half(frame + 4);
    if (status == 0) {
        put(state + 3, 0);
        put(state + 4, first_result);
        return;
    }
    read_packet_bytes_with_diagnostic(reader, frame + 12, 4);
    read_packet_bytes_with_diagnostic(reader, frame + 8, 4);
    read_available_packet_bytes(reader, frame + 16, 21);
    read_packet_bytes_with_diagnostic(reader, frame, 2);
    const uint32_t length = half(frame);
    read_available_packet_bytes(reader, frame + 40, length);
    session(state);
    put(state + 3, 1);
}
extern "C" __attribute__((naked)) void fun_00593ab0(PacketReader*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tandl $-8,%esp\n\tsubl $1040,%esp\n\tpushl %esi\n\tpushl %edi\n\t"
        "leal 8(%esp),%edx\n\tleal 8(%ebp),%eax\n\tsubl $20,%esp\n\tmovl %esp,%ecx\n\t"
        "pushl %ecx\n\tpushl %edx\n\tpushl %eax\n\tcalll _prepare_00593ab0\n\taddl $12,%esp\n\t"
        "movl (%esp),%esi\n\tleal 1068(%esp),%edi\n\tcmpl $0,12(%esp)\n\tje 1f\n\t"
        "movl 4(%esp),%ecx\n\tmovl 8(%esp),%edx\n\taddl $20,%esp\n\t"
        "leal 48(%esp),%eax\n\tpushl %eax\n\tmovl 12(%esp),%eax\n\tpushl %eax\n\tleal 32(%esp),%eax\n\tpushl %eax\n\t"
        "movl 28(%esp),%eax\n\tpushl %eax\n\tmovl 36(%esp),%eax\n\tpushl %eax\n\tmovl 32(%esp),%eax\n\tpushl %eax\n\t"
        "calll *0x310(%edx)\n\tjmp 2f\n\t1: movl 16(%esp),%eax\n\taddl $20,%esp\n\t"
        "2: popl %edi\n\tpopl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tretl");
}
// Complete original00597160..00597218. Count multiplication remains unchecked.
extern "C" __attribute__((noinline)) void prepare_00597160(const void* actual_arguments,
                                                           uint8_t* frame, uint32_t* state) {
    auto* reader = reinterpret_cast<PacketReader*>(word(actual_arguments));
    put(state, reinterpret_cast<uint32_t>(reader));
    read_packet_bytes_with_diagnostic(reader, frame + 4, 1);
    if (byte(frame + 4) == 0) {
        read_packet_bytes_with_diagnostic(reader, frame + 12, 4);
        read_available_packet_bytes(reader, frame + 20, 21);
        read_packet_bytes_with_diagnostic(reader, frame + 8, 4);
        read_packet_bytes_with_diagnostic(reader, frame + 16, 4);
        read_packet_bytes_with_diagnostic(reader, frame, 1);
        const uint32_t count = byte(frame);
        read_packet_bytes_with_diagnostic(reader, frame + 44, count * 5u);
    }
    session(state);
}
extern "C" __attribute__((naked)) void fun_00597160(PacketReader*) {
    __asm__ volatile(
        "subl $164,%esp\n\tpushl %esi\n\tleal 4(%esp),%edx\n\tleal 172(%esp),%eax\n\tsubl $12,%esp\n\tmovl %esp,%ecx\n\t"
        "pushl %ecx\n\tpushl %edx\n\tpushl %eax\n\tcalll _prepare_00597160\n\taddl $12,%esp\n\t"
        "movl (%esp),%esi\n\tmovl 4(%esp),%ecx\n\tmovl 8(%esp),%edx\n\taddl $12,%esp\n\t"
        "leal 48(%esp),%eax\n\tpushl %eax\n\tmovl 8(%esp),%eax\n\tpushl %eax\n\tmovl 28(%esp),%eax\n\tpushl %eax\n\t"
        "movl 24(%esp),%eax\n\tpushl %eax\n\tleal 40(%esp),%eax\n\tpushl %eax\n\tmovl 36(%esp),%eax\n\tpushl %eax\n\t"
        "movl 32(%esp),%eax\n\tpushl %eax\n\tcalll *0x5b0(%edx)\n\tpopl %esi\n\taddl $164,%esp\n\tretl");
}
