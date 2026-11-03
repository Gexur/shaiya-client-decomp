#include "session_callback_leaves.h"
// Complete original x86 methods, preserving private/volatile/register ABI.

// Original 0x40a770, 1reachable instructions, RET24.
extern "C" __attribute__((naked)) void FUN_0040a770() {
    __asm__ volatile(".Lsession_leaf_0040a770: retl $0x18\n\t");
}

// Original 0x40a780, 1reachable instructions, RET20.
extern "C" __attribute__((naked)) void FUN_0040a780() {
    __asm__ volatile(".Lsession_leaf_0040a780: retl $0x14\n\t");
}

// Original 0x51e1b0, 1reachable instructions, RET8.
extern "C" __attribute__((naked)) void FUN_0051e1b0() {
    __asm__ volatile(".Lsession_leaf_0051e1b0: retl $8\n\t");
}

// Original 0x55f7e0, 5reachable instructions, RET16.
extern "C" __attribute__((naked)) void FUN_0055f7e0() {
    __asm__ volatile(".Lsession_leaf_0055f7e0: leal 4(%esp), %eax\n\t"
                     ".Lsession_leaf_0055f7e4: pushl %eax\n\t"
                     ".Lsession_leaf_0055f7e5: calll _FUN_005bfb50\n\t"
                     ".Lsession_leaf_0055f7ea: popl %ecx\n\t"
                     ".Lsession_leaf_0055f7eb: retl $0x10\n\t");
}

// Original 0x55fa80, 2reachable instructions, RET0.
extern "C" __attribute__((naked)) void FUN_0055fa80() {
    __asm__ volatile(".Lsession_leaf_0055fa80: movl $5, _dat_00719a5c\n\t"
                     ".Lsession_leaf_0055fa8a: retl\n\t");
}

// Original 0x55fc70, 7reachable instructions, RET8.
extern "C" __attribute__((naked)) void FUN_0055fc70() {
    __asm__ volatile(".Lsession_leaf_0055fc70: movb 4(%esp), %al\n\t"
                     ".Lsession_leaf_0055fc74: cmpb $3, %al\n\t"
                     ".Lsession_leaf_0055fc76: ja .Lsession_leaf_0055fc86\n\t"
                     ".Lsession_leaf_0055fc78: movl 8(%esp), %ecx\n\t"
                     ".Lsession_leaf_0055fc7c: movzbl %al, %eax\n\t"
                     ".Lsession_leaf_0055fc7f: movl %ecx, _dat_021fdefc(, %eax, 4)\n\t"
                     ".Lsession_leaf_0055fc86: retl $8\n\t");
}

// Original 0x55ff20, 7reachable instructions, RET8.
extern "C" __attribute__((naked)) void FUN_0055ff20() {
    __asm__ volatile(".Lsession_leaf_0055ff20: movb 4(%esp), %al\n\t"
                     ".Lsession_leaf_0055ff24: testb %al, %al\n\t"
                     ".Lsession_leaf_0055ff26: jne .Lsession_leaf_0055ff3c\n\t"
                     ".Lsession_leaf_0055ff28: movl 8(%esp), %eax\n\t"
                     ".Lsession_leaf_0055ff2c: movl $1, 0x1ec(%ecx)\n\t"
                     ".Lsession_leaf_0055ff36: movl %eax, 0x1f4(%ecx)\n\t"
                     ".Lsession_leaf_0055ff3c: retl $8\n\t");
}

// Original 0x55ff40, 6reachable instructions, RET8.
extern "C" __attribute__((naked)) void FUN_0055ff40() {
    __asm__ volatile(".Lsession_leaf_0055ff40: movb 4(%esp), %al\n\t"
                     ".Lsession_leaf_0055ff44: testb %al, %al\n\t"
                     ".Lsession_leaf_0055ff46: jne .Lsession_leaf_0055ff52\n\t"
                     ".Lsession_leaf_0055ff48: movl 8(%esp), %eax\n\t"
                     ".Lsession_leaf_0055ff4c: movl %eax, 0x1f4(%ecx)\n\t"
                     ".Lsession_leaf_0055ff52: retl $8\n\t");
}

// Original 0x5621f0, 2reachable instructions, RET0.
extern "C" __attribute__((naked)) void FUN_005621f0() {
    __asm__ volatile(".Lsession_leaf_005621f0: movl $1, _dat_0085d1cc\n\t"
                     ".Lsession_leaf_005621fa: retl\n\t");
}

// Original 0x562200, 3reachable instructions, RET4.
extern "C" __attribute__((naked)) void FUN_00562200() {
    __asm__ volatile(".Lsession_leaf_00562200: movl 4(%esp), %eax\n\t"
                     ".Lsession_leaf_00562204: movl %eax, _dat_008655f0\n\t"
                     ".Lsession_leaf_00562209: retl $4\n\t");
}

// Original 0x5628d0, 6reachable instructions, RET8.
extern "C" __attribute__((naked)) void FUN_005628d0() {
    __asm__ volatile(".Lsession_leaf_005628d0: movzbl 4(%esp), %eax\n\t"
                     ".Lsession_leaf_005628d5: movzbl 8(%esp), %ecx\n\t"
                     ".Lsession_leaf_005628da: movl %eax, _dat_02203354\n\t"
                     ".Lsession_leaf_005628df: movl %ecx, _dat_02203358\n\t"
                     ".Lsession_leaf_005628e5: movl $0x6c, _dat_00868dd4\n\t"
                     ".Lsession_leaf_005628ef: retl $8\n\t");
}

// Original 0x562900, 8reachable instructions, RET8.
extern "C" __attribute__((naked)) void FUN_00562900() {
    __asm__ volatile(".Lsession_leaf_00562900: movzbl 8(%esp), %ecx\n\t"
                     ".Lsession_leaf_00562905: movl $1, %eax\n\t"
                     ".Lsession_leaf_0056290a: movl %eax, _dat_02203350\n\t"
                     ".Lsession_leaf_0056290f: movl %eax, _dat_02203354\n\t"
                     ".Lsession_leaf_00562914: movzbl 4(%esp), %eax\n\t"
                     ".Lsession_leaf_00562919: movl %eax, _dat_02203358\n\t"
                     ".Lsession_leaf_0056291e: movl %ecx, _dat_0220335c\n\t"
                     ".Lsession_leaf_00562924: retl $8\n\t");
}

// Original 0x562930, 7reachable instructions, RET8.
extern "C" __attribute__((naked)) void FUN_00562930() {
    __asm__ volatile(".Lsession_leaf_00562930: movzbl 4(%esp), %eax\n\t"
                     ".Lsession_leaf_00562935: movl 8(%esp), %ecx\n\t"
                     ".Lsession_leaf_00562939: movl $1, _dat_02203350\n\t"
                     ".Lsession_leaf_00562943: movl $2, _dat_02203354\n\t"
                     ".Lsession_leaf_0056294d: movl %eax, _dat_02203358\n\t"
                     ".Lsession_leaf_00562952: movl %ecx, _dat_0220335c\n\t"
                     ".Lsession_leaf_00562958: retl $8\n\t");
}

// Original 0x562b10, 2reachable instructions, RET0.
extern "C" __attribute__((naked)) void FUN_00562b10() {
    __asm__ volatile(".Lsession_leaf_00562b10: movl $1, _dat_0071c510\n\t"
                     ".Lsession_leaf_00562b1a: retl\n\t");
}

// Original 0x562b20, 7reachable instructions, RET4.
extern "C" __attribute__((naked)) void FUN_00562b20() {
    __asm__ volatile(".Lsession_leaf_00562b20: movb 4(%esp), %al\n\t"
                     ".Lsession_leaf_00562b24: cmpb $2, %al\n\t"
                     ".Lsession_leaf_00562b26: movzbl %al, %ecx\n\t"
                     ".Lsession_leaf_00562b29: movl %ecx, _dat_0071c514\n\t"
                     ".Lsession_leaf_00562b2f: jne .Lsession_leaf_00562b38\n\t"
                     ".Lsession_leaf_00562b31: movb $1, _dat_0071c544\n\t"
                     ".Lsession_leaf_00562b38: retl $4\n\t");
}

// Original 0x562f00, 2reachable instructions, RET0.
extern "C" __attribute__((naked)) void FUN_00562f00() {
    __asm__ volatile(".Lsession_leaf_00562f00: movl $1, _dat_0071c528\n\t"
                     ".Lsession_leaf_00562f0a: retl\n\t");
}

// Original 0x562f30, 5reachable instructions, RET8.
extern "C" __attribute__((naked)) void FUN_00562f30() {
    __asm__ volatile(".Lsession_leaf_00562f30: movb 4(%esp), %al\n\t"
                     ".Lsession_leaf_00562f34: movb 8(%esp), %cl\n\t"
                     ".Lsession_leaf_00562f38: movb %al, _dat_021fe70c\n\t"
                     ".Lsession_leaf_00562f3d: movb %cl, _dat_021fe70d\n\t"
                     ".Lsession_leaf_00562f43: retl $8\n\t");
}

// Original 0x562fa0, 6reachable instructions, RET8.
extern "C" __attribute__((naked)) void FUN_00562fa0() {
    __asm__ volatile(".Lsession_leaf_00562fa0: movb 4(%esp), %al\n\t"
                     ".Lsession_leaf_00562fa4: movb 8(%esp), %cl\n\t"
                     ".Lsession_leaf_00562fa8: movb $1, _dat_00864e2a\n\t"
                     ".Lsession_leaf_00562faf: movb %al, _dat_00864e28\n\t"
                     ".Lsession_leaf_00562fb4: movb %cl, _dat_00864e18\n\t"
                     ".Lsession_leaf_00562fba: retl $8\n\t");
}

// Original 0x568ab0, 4reachable instructions, RET4.
extern "C" __attribute__((naked)) void FUN_00568ab0() {
    __asm__ volatile(".Lsession_leaf_00568ab0: movb 4(%esp), %al\n\t"
                     ".Lsession_leaf_00568ab4: movl $1, _dat_00864e34\n\t"
                     ".Lsession_leaf_00568abe: movb %al, _dat_00864e38\n\t"
                     ".Lsession_leaf_00568ac3: retl $4\n\t");
}

// Original 0x568ad0, 8reachable instructions, RET12.
extern "C" __attribute__((naked)) void FUN_00568ad0() {
    __asm__ volatile(".Lsession_leaf_00568ad0: movb 4(%esp), %al\n\t"
                     ".Lsession_leaf_00568ad4: movl 8(%esp), %ecx\n\t"
                     ".Lsession_leaf_00568ad8: movl 0xc(%esp), %edx\n\t"
                     ".Lsession_leaf_00568adc: movl $2, _dat_00864e34\n\t"
                     ".Lsession_leaf_00568ae6: movb %al, _dat_00864e38\n\t"
                     ".Lsession_leaf_00568aeb: movl %ecx, _dat_00864e48\n\t"
                     ".Lsession_leaf_00568af1: movl %edx, _dat_00864e4c\n\t"
                     ".Lsession_leaf_00568af7: retl $0xc\n\t");
}

// Original 0x568b90, 4reachable instructions, RET4.
extern "C" __attribute__((naked)) void FUN_00568b90() {
    __asm__ volatile(".Lsession_leaf_00568b90: movb 4(%esp), %al\n\t"
                     ".Lsession_leaf_00568b94: movl $4, _dat_00864e34\n\t"
                     ".Lsession_leaf_00568b9e: movb %al, _dat_00864e43\n\t"
                     ".Lsession_leaf_00568ba3: retl $4\n\t");
}

// Original 0x568bb0, 2reachable instructions, RET0.
extern "C" __attribute__((naked)) void FUN_00568bb0() {
    __asm__ volatile(".Lsession_leaf_00568bb0: movl $5, _dat_00864e34\n\t"
                     ".Lsession_leaf_00568bba: retl\n\t");
}

// Original 0x568bc0, 4reachable instructions, RET4.
extern "C" __attribute__((naked)) void FUN_00568bc0() {
    __asm__ volatile(".Lsession_leaf_00568bc0: movl 4(%esp), %eax\n\t"
                     ".Lsession_leaf_00568bc4: movl $6, _dat_00864e34\n\t"
                     ".Lsession_leaf_00568bce: movl %eax, _dat_00864e48\n\t"
                     ".Lsession_leaf_00568bd3: retl $4\n\t");
}

// Original 0x568be0, 8reachable instructions, RET12.
extern "C" __attribute__((naked)) void FUN_00568be0() {
    __asm__ volatile(".Lsession_leaf_00568be0: movb 4(%esp), %al\n\t"
                     ".Lsession_leaf_00568be4: movb 8(%esp), %cl\n\t"
                     ".Lsession_leaf_00568be8: movl 0xc(%esp), %edx\n\t"
                     ".Lsession_leaf_00568bec: movl $7, _dat_00864e34\n\t"
                     ".Lsession_leaf_00568bf6: movb %al, _dat_00864e43\n\t"
                     ".Lsession_leaf_00568bfb: movb %cl, _dat_00864e38\n\t"
                     ".Lsession_leaf_00568c01: movl %edx, _dat_00864e48\n\t"
                     ".Lsession_leaf_00568c07: retl $0xc\n\t");
}

// Original 0x568c10, 4reachable instructions, RET4.
extern "C" __attribute__((naked)) void FUN_00568c10() {
    __asm__ volatile(".Lsession_leaf_00568c10: movb 4(%esp), %al\n\t"
                     ".Lsession_leaf_00568c14: movl $8, _dat_00864e34\n\t"
                     ".Lsession_leaf_00568c1e: movb %al, _dat_00864e43\n\t"
                     ".Lsession_leaf_00568c23: retl $4\n\t");
}

// Original 0x568c30, 2reachable instructions, RET0.
extern "C" __attribute__((naked)) void FUN_00568c30() {
    __asm__ volatile(".Lsession_leaf_00568c30: movl $9, _dat_00864e34\n\t"
                     ".Lsession_leaf_00568c3a: retl\n\t");
}

// Original 0x568c90, 2reachable instructions, RET4.
extern "C" __attribute__((naked)) void FUN_00568c90() {
    __asm__ volatile(".Lsession_leaf_00568c90: movl $2, _dat_00868dd4\n\t"
                     ".Lsession_leaf_00568c9a: retl $4\n\t");
}

// Original 0x568ca0, 2reachable instructions, RET4.
extern "C" __attribute__((naked)) void FUN_00568ca0() {
    __asm__ volatile(".Lsession_leaf_00568ca0: movl $3, _dat_00868dd4\n\t"
                     ".Lsession_leaf_00568caa: retl $4\n\t");
}

// Original 0x568e20, 1reachable instructions, RET16.
extern "C" __attribute__((naked)) void FUN_00568e20() {
    __asm__ volatile(".Lsession_leaf_00568e20: retl $0x10\n\t");
}

// Original 0x5696a0, 7reachable instructions, RET12.
extern "C" __attribute__((naked)) void FUN_005696a0() {
    __asm__ volatile(".Lsession_leaf_005696a0: movl 4(%esp), %eax\n\t"
                     ".Lsession_leaf_005696a4: movl 8(%esp), %ecx\n\t"
                     ".Lsession_leaf_005696a8: movl 0xc(%esp), %edx\n\t"
                     ".Lsession_leaf_005696ac: movl %eax, _dat_02201398\n\t"
                     ".Lsession_leaf_005696b1: movl %ecx, _dat_022013a0\n\t"
                     ".Lsession_leaf_005696b7: movl %edx, _dat_0220139c\n\t"
                     ".Lsession_leaf_005696bd: retl $0xc\n\t");
}

// Original 0x569880, 3reachable instructions, RET4.
extern "C" __attribute__((naked)) void FUN_00569880() {
    __asm__ volatile(".Lsession_leaf_00569880: movl 4(%esp), %eax\n\t"
                     ".Lsession_leaf_00569884: movl %eax, _dat_022013a8\n\t"
                     ".Lsession_leaf_00569889: retl $4\n\t");
}

// Original 0x56bc30, 3reachable instructions, RET4.
extern "C" __attribute__((naked)) void FUN_0056bc30() {
    __asm__ volatile(".Lsession_leaf_0056bc30: movw 4(%esp), %ax\n\t"
                     ".Lsession_leaf_0056bc35: movw %ax, _dat_0086568a\n\t"
                     ".Lsession_leaf_0056bc3b: retl $4\n\t");
}

// Original 0x56cf60, 2reachable instructions, RET0.
extern "C" __attribute__((naked)) void FUN_0056cf60() {
    __asm__ volatile(".Lsession_leaf_0056cf60: movl $1, _dat_021fe5d0\n\t"
                     ".Lsession_leaf_0056cf6a: retl\n\t");
}

// Original 0x56d010, 4reachable instructions, RET4.
extern "C" __attribute__((naked)) void FUN_0056d010() {
    __asm__ volatile(".Lsession_leaf_0056d010: movzbl 4(%esp), %eax\n\t"
                     ".Lsession_leaf_0056d015: leal (%eax, %eax, 2), %eax\n\t"
                     ".Lsession_leaf_0056d018: movl $0, _dat_021fe1bc(, %eax, 4)\n\t"
                     ".Lsession_leaf_0056d023: retl $4\n\t");
}

// Original 0x56d030, 5reachable instructions, RET8.
extern "C" __attribute__((naked)) void FUN_0056d030() {
    __asm__ volatile(".Lsession_leaf_0056d030: movzbl 4(%esp), %eax\n\t"
                     ".Lsession_leaf_0056d035: movl 8(%esp), %ecx\n\t"
                     ".Lsession_leaf_0056d039: leal (%eax, %eax, 2), %eax\n\t"
                     ".Lsession_leaf_0056d03c: movl %ecx, _dat_021fe1c4(, %eax, 4)\n\t"
                     ".Lsession_leaf_0056d043: retl $8\n\t");
}

// Original 0x56d1e0, 5reachable instructions, RET8.
extern "C" __attribute__((naked)) void FUN_0056d1e0() {
    __asm__ volatile(".Lsession_leaf_0056d1e0: movl 8(%esp), %eax\n\t"
                     ".Lsession_leaf_0056d1e4: movl $0xe, _dat_00868dd4\n\t"
                     ".Lsession_leaf_0056d1ee: movl %eax, _dat_021fe5ec\n\t"
                     ".Lsession_leaf_0056d1f3: movl $0, _dat_021fe5e4\n\t"
                     ".Lsession_leaf_0056d1fd: retl $8\n\t");
}

// Original 0x56d200, 2reachable instructions, RET0.
extern "C" __attribute__((naked)) void FUN_0056d200() {
    __asm__ volatile(".Lsession_leaf_0056d200: movl $1, _dat_021fe5e4\n\t"
                     ".Lsession_leaf_0056d20a: retl\n\t");
}

// Original 0x56d2d0, 2reachable instructions, RET0.
extern "C" __attribute__((naked)) void FUN_0056d2d0() {
    __asm__ volatile(".Lsession_leaf_0056d2d0: movl $1, _dat_021fe5e8\n\t"
                     ".Lsession_leaf_0056d2da: retl\n\t");
}

// Original 0x56e2f0, 3reachable instructions, RET4.
extern "C" __attribute__((naked)) void FUN_0056e2f0() {
    __asm__ volatile(".Lsession_leaf_0056e2f0: movl 4(%esp), %eax\n\t"
                     ".Lsession_leaf_0056e2f4: movl %eax, _dat_021fe710\n\t"
                     ".Lsession_leaf_0056e2f9: retl $4\n\t");
}

// Original 0x571360, 7reachable instructions, RET8.
extern "C" __attribute__((naked)) void FUN_00571360() {
    __asm__ volatile(".Lsession_leaf_00571360: movb 4(%esp), %al\n\t"
                     ".Lsession_leaf_00571364: movb %al, _dat_021fd8d6\n\t"
                     ".Lsession_leaf_00571369: movb %al, _dat_00867d8c\n\t"
                     ".Lsession_leaf_0057136e: movb 8(%esp), %al\n\t"
                     ".Lsession_leaf_00571372: movb %al, _dat_021fd8d7\n\t"
                     ".Lsession_leaf_00571377: incl 0x1ec(%ecx)\n\t"
                     ".Lsession_leaf_0057137d: retl $8\n\t");
}

// Original 0x5757f0, 5reachable instructions, RET4.
extern "C" __attribute__((naked)) void FUN_005757f0() {
    __asm__ volatile(".Lsession_leaf_005757f0: movw 4(%esp), %ax\n\t"
                     ".Lsession_leaf_005757f5: movl $0x70, _dat_00868dd4\n\t"
                     ".Lsession_leaf_005757ff: movw %ax, _dat_0086de22\n\t"
                     ".Lsession_leaf_00575805: movb $2, _dat_0086de20\n\t"
                     ".Lsession_leaf_0057580c: retl $4\n\t");
}

// Original 0x57adc0, 5reachable instructions, RET0.
extern "C" __attribute__((naked)) void FUN_0057adc0() {
    __asm__ volatile(".Lsession_leaf_0057adc0: pushl $0\n\t"
                     ".Lsession_leaf_0057adc2: pushl $1\n\t"
                     ".Lsession_leaf_0057adc4: calll _FUN_0058d740\n\t"
                     ".Lsession_leaf_0057adc9: addl $8, %esp\n\t"
                     ".Lsession_leaf_0057adcc: retl\n\t");
}

// Original 0x58d740, 9reachable instructions, RET0.
extern "C" __attribute__((naked)) void FUN_0058d740() {
    __asm__ volatile(".Lsession_leaf_0058d740: movl 4(%esp), %eax\n\t"
                     ".Lsession_leaf_0058d744: movl 8(%esp), %ecx\n\t"
                     ".Lsession_leaf_0058d748: movl %eax, _dat_0070c3c8\n\t"
                     ".Lsession_leaf_0058d74d: decl %eax\n\t"
                     ".Lsession_leaf_0058d74e: negl %eax\n\t"
                     ".Lsession_leaf_0058d750: sbbl %eax, %eax\n\t"
                     ".Lsession_leaf_0058d752: andl %ecx, %eax\n\t"
                     ".Lsession_leaf_0058d754: movl %eax, _dat_0224e34c\n\t"
                     ".Lsession_leaf_0058d759: retl\n\t");
}
