#include "session_callback_records.h"
// Complete original record/status methods. Shared logical fields use one owner.

// Original 0055fbd0; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_0055fbd0() {
    __asm__ volatile(".Lsession_record_0055fbd0: movw 8(%esp), %dx\n\t"
                     ".Lsession_record_0055fbd5: movl 4(%esp), %eax\n\t"
                     ".Lsession_record_0055fbd9: movw %dx, _dat_008666c4\n\t"
                     ".Lsession_record_0055fbe0: movl _dat_0085cfbc, %edx\n\t"
                     ".Lsession_record_0055fbe6: testl %edx, %edx\n\t"
                     ".Lsession_record_0055fbe8: movl %eax, _dat_008666d8\n\t"
                     ".Lsession_record_0055fbed: je .Lsession_record_0055fbf2\n\t"
                     ".Lsession_record_0055fbef: movl %eax, 0x34(%edx)\n\t"
                     ".Lsession_record_0055fbf2: movl $1, 0x1fc(%ecx)\n\t"
                     ".Lsession_record_0055fbfc: retl $8\n\t");
}

// Original 0055fc00; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_0055fc00() {
    __asm__ volatile(".Lsession_record_0055fc00: movzbl 4(%esp), %eax\n\t"
                     ".Lsession_record_0055fc05: subl $0, %eax\n\t"
                     ".Lsession_record_0055fc08: je .Lsession_record_0055fc36\n\t"
                     ".Lsession_record_0055fc0a: decl %eax\n\t"
                     ".Lsession_record_0055fc0b: je .Lsession_record_0055fc23\n\t"
                     ".Lsession_record_0055fc0d: decl %eax\n\t"
                     ".Lsession_record_0055fc0e: jne .Lsession_record_0055fc36\n\t"
                     ".Lsession_record_0055fc10: movl _dat_0223f100, %ecx\n\t"
                     ".Lsession_record_0055fc16: movl $2, 0x1ec(%ecx)\n\t"
                     ".Lsession_record_0055fc20: retl $4\n\t"
                     ".Lsession_record_0055fc23: movl _dat_0223f100, %edx\n\t"
                     ".Lsession_record_0055fc29: movl $1, 0x1ec(%edx)\n\t"
                     ".Lsession_record_0055fc33: retl $4\n\t"
                     ".Lsession_record_0055fc36: movl _dat_0223f100, %eax\n\t"
                     ".Lsession_record_0055fc3b: movl $3, 0x1ec(%eax)\n\t"
                     ".Lsession_record_0055fc45: retl $4\n\t");
}

// Original 0055fc50; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_0055fc50() {
    __asm__ volatile(".Lsession_record_0055fc50: pushl %esi\n\t"
                     ".Lsession_record_0055fc51: movl 8(%esp), %esi\n\t"
                     ".Lsession_record_0055fc55: pushl %edi\n\t"
                     ".Lsession_record_0055fc56: movl $0xa, %ecx\n\t"
                     ".Lsession_record_0055fc5b: movl $_dat_00867d5c, %edi\n\t"
                     ".Lsession_record_0055fc60: rep movsl (%esi), %es:(%edi)\n\t"
                     ".Lsession_record_0055fc62: movsw (%esi), %es:(%edi)\n\t"
                     ".Lsession_record_0055fc64: popl %edi\n\t"
                     ".Lsession_record_0055fc65: popl %esi\n\t"
                     ".Lsession_record_0055fc66: retl $4\n\t");
}

// Original 0055fd30; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_0055fd30() {
    __asm__ volatile(".Lsession_record_0055fd30: movb 4(%esp), %al\n\t"
                     ".Lsession_record_0055fd34: cmpb $1, %al\n\t"
                     ".Lsession_record_0055fd36: ja .Lsession_record_0055fd52\n\t"
                     ".Lsession_record_0055fd38: movl 8(%esp), %ecx\n\t"
                     ".Lsession_record_0055fd3c: movl 0xc(%esp), %edx\n\t"
                     ".Lsession_record_0055fd40: movzbl %al, %eax\n\t"
                     ".Lsession_record_0055fd43: shll $2, %eax\n\t"
                     ".Lsession_record_0055fd46: movl %ecx, _dat_021fe1bc+1132(%eax)\n\t"
                     ".Lsession_record_0055fd4c: movl %edx, _dat_021fe1bc+1124(%eax)\n\t"
                     ".Lsession_record_0055fd52: retl $0xc\n\t");
}

// Original 0055fee0; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_0055fee0() {
    __asm__ volatile(".Lsession_record_0055fee0: movb 4(%esp), %al\n\t"
                     ".Lsession_record_0055fee4: testb %al, %al\n\t"
                     ".Lsession_record_0055fee6: jne .Lsession_record_0055fef5\n\t"
                     ".Lsession_record_0055fee8: movl $1, 0x1ec(%ecx)\n\t"
                     ".Lsession_record_0055fef2: retl $4\n\t"
                     ".Lsession_record_0055fef5: cmpb $1, %al\n\t"
                     ".Lsession_record_0055fef7: jne .Lsession_record_0055ff06\n\t"
                     ".Lsession_record_0055fef9: movl $2, 0x1ec(%ecx)\n\t"
                     ".Lsession_record_0055ff03: retl $4\n\t"
                     ".Lsession_record_0055ff06: cmpb $2, %al\n\t"
                     ".Lsession_record_0055ff08: jne .Lsession_record_0055ff14\n\t"
                     ".Lsession_record_0055ff0a: movl $3, 0x1ec(%ecx)\n\t"
                     ".Lsession_record_0055ff14: retl $4\n\t");
}

// Original 00560e00; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_00560e00() {
    __asm__ volatile(".Lsession_record_00560e00: movl _dat_0085cfbc, %eax\n\t"
                     ".Lsession_record_00560e05: testl %eax, %eax\n\t"
                     ".Lsession_record_00560e07: je .Lsession_record_00560e17\n\t"
                     ".Lsession_record_00560e09: movzbl 4(%esp), %ecx\n\t"
                     ".Lsession_record_00560e0e: movl %ecx, 0x174(%eax)\n\t"
                     ".Lsession_record_00560e14: retl $4\n\t"
                     ".Lsession_record_00560e17: movb 4(%esp), %dl\n\t"
                     ".Lsession_record_00560e1b: movb %dl, _dat_02201968\n\t"
                     ".Lsession_record_00560e21: retl $4\n\t");
}

// Original 00561950; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_00561950() {
    __asm__ volatile(".Lsession_record_00561950: movl 4(%esp), %eax\n\t"
                     ".Lsession_record_00561954: addw %ax, _dat_00865614\n\t"
                     ".Lsession_record_0056195b: movl 8(%esp), %ecx\n\t"
                     ".Lsession_record_0056195f: movl 0xc(%esp), %edx\n\t"
                     ".Lsession_record_00561963: addw %cx, _dat_00865618\n\t"
                     ".Lsession_record_0056196a: addw %dx, _dat_0086561c\n\t"
                     ".Lsession_record_00561971: pushl %ebx\n\t"
                     ".Lsession_record_00561972: movl 0x1c(%esp), %ebx\n\t"
                     ".Lsession_record_00561976: addw %bx, _dat_0086561e\n\t"
                     ".Lsession_record_0056197d: pushl %esi\n\t"
                     ".Lsession_record_0056197e: movl 0x18(%esp), %esi\n\t"
                     ".Lsession_record_00561982: addw %si, _dat_00865616\n\t"
                     ".Lsession_record_00561989: addl %ecx, %eax\n\t"
                     ".Lsession_record_0056198b: pushl %edi\n\t"
                     ".Lsession_record_0056198c: movl 0x20(%esp), %edi\n\t"
                     ".Lsession_record_00561990: addw %di, _dat_0086561a\n\t"
                     ".Lsession_record_00561997: addl %edx, %eax\n\t"
                     ".Lsession_record_00561999: addl %esi, %eax\n\t"
                     ".Lsession_record_0056199b: addl %edi, %eax\n\t"
                     ".Lsession_record_0056199d: popl %edi\n\t"
                     ".Lsession_record_0056199e: addl %ebx, %eax\n\t"
                     ".Lsession_record_005619a0: subw %ax, _dat_00865690\n\t"
                     ".Lsession_record_005619a7: popl %esi\n\t"
                     ".Lsession_record_005619a8: popl %ebx\n\t"
                     ".Lsession_record_005619a9: retl $0x18\n\t");
}

// Original 00562440; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_00562440() {
    __asm__ volatile(".Lsession_record_00562440: movl _dat_0085cfbc, %eax\n\t"
                     ".Lsession_record_00562445: testl %eax, %eax\n\t"
                     ".Lsession_record_00562447: jne .Lsession_record_00562469\n\t"
                     ".Lsession_record_00562449: movl 4(%esp), %eax\n\t"
                     ".Lsession_record_0056244d: movl 8(%esp), %ecx\n\t"
                     ".Lsession_record_00562451: movl 0xc(%esp), %edx\n\t"
                     ".Lsession_record_00562455: movl %eax, _dat_00868d98\n\t"
                     ".Lsession_record_0056245a: movl %ecx, _dat_00868d9c\n\t"
                     ".Lsession_record_00562460: movl %edx, _dat_00868da0\n\t"
                     ".Lsession_record_00562466: retl $0xc\n\t"
                     ".Lsession_record_00562469: movl 4(%esp), %ecx\n\t"
                     ".Lsession_record_0056246d: movl %ecx, 0x13c(%eax)\n\t"
                     ".Lsession_record_00562473: movl _dat_0085cfbc, %edx\n\t"
                     ".Lsession_record_00562479: movl 8(%esp), %eax\n\t"
                     ".Lsession_record_0056247d: movl 0xc(%esp), %ecx\n\t"
                     ".Lsession_record_00562481: movl %eax, 0x144(%edx)\n\t"
                     ".Lsession_record_00562487: movl _dat_0085cfbc, %edx\n\t"
                     ".Lsession_record_0056248d: movl %ecx, 0x14c(%edx)\n\t"
                     ".Lsession_record_00562493: retl $0xc\n\t");
}

// Original 00562f50; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_00562f50() {
    __asm__ volatile(".Lsession_record_00562f50: movb 4(%esp), %al\n\t"
                     ".Lsession_record_00562f54: movb 8(%esp), %cl\n\t"
                     ".Lsession_record_00562f58: movb 0xc(%esp), %dl\n\t"
                     ".Lsession_record_00562f5c: movb %al, _dat_00864e19\n\t"
                     ".Lsession_record_00562f61: movl 0x10(%esp), %eax\n\t"
                     ".Lsession_record_00562f65: movb $1, _dat_00864e29\n\t"
                     ".Lsession_record_00562f6c: movb %cl, _dat_00864e28\n\t"
                     ".Lsession_record_00562f72: movb %dl, _dat_00864e18\n\t"
                     ".Lsession_record_00562f78: movl (%eax), %ecx\n\t"
                     ".Lsession_record_00562f7a: movl %ecx, _dat_00864e1c\n\t"
                     ".Lsession_record_00562f80: movw 4(%eax), %dx\n\t"
                     ".Lsession_record_00562f84: movl 0x14(%esp), %eax\n\t"
                     ".Lsession_record_00562f88: movw %dx, _dat_00864e20\n\t"
                     ".Lsession_record_00562f8f: movl %eax, _dat_00864e24\n\t"
                     ".Lsession_record_00562f94: retl $0x14\n\t");
}

// Original 00568b00; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_00568b00() {
    __asm__ volatile(".Lsession_record_00568b00: movb 4(%esp), %al\n\t"
                     ".Lsession_record_00568b04: movb %al, _dat_00864e38\n\t"
                     ".Lsession_record_00568b09: movl 8(%esp), %eax\n\t"
                     ".Lsession_record_00568b0d: movl $3, _dat_00864e34\n\t"
                     ".Lsession_record_00568b17: movb (%eax), %cl\n\t"
                     ".Lsession_record_00568b19: movb %cl, _dat_00864e3a\n\t"
                     ".Lsession_record_00568b1f: movb 1(%eax), %dl\n\t"
                     ".Lsession_record_00568b22: movb %dl, _dat_00864e3b\n\t"
                     ".Lsession_record_00568b28: movb 2(%eax), %cl\n\t"
                     ".Lsession_record_00568b2b: movb %cl, _dat_00864e3c\n\t"
                     ".Lsession_record_00568b31: movb 3(%eax), %dl\n\t"
                     ".Lsession_record_00568b34: movb %dl, _dat_00864e3d\n\t"
                     ".Lsession_record_00568b3a: movb 4(%eax), %cl\n\t"
                     ".Lsession_record_00568b3d: movb %cl, _dat_00864e3e\n\t"
                     ".Lsession_record_00568b43: movb 5(%eax), %dl\n\t"
                     ".Lsession_record_00568b46: movb %dl, _dat_00864e3f\n\t"
                     ".Lsession_record_00568b4c: movb 6(%eax), %cl\n\t"
                     ".Lsession_record_00568b4f: movb %cl, _dat_00864e40\n\t"
                     ".Lsession_record_00568b55: movb 7(%eax), %dl\n\t"
                     ".Lsession_record_00568b58: movb 0xc(%esp), %cl\n\t"
                     ".Lsession_record_00568b5c: movb %dl, _dat_00864e41\n\t"
                     ".Lsession_record_00568b62: movb 8(%eax), %al\n\t"
                     ".Lsession_record_00568b65: movl 0x10(%esp), %edx\n\t"
                     ".Lsession_record_00568b69: movb %al, _dat_00864e42\n\t"
                     ".Lsession_record_00568b6e: movb 0x14(%esp), %al\n\t"
                     ".Lsession_record_00568b72: movb %cl, _dat_00864e43\n\t"
                     ".Lsession_record_00568b78: movl %edx, _dat_00864e48\n\t"
                     ".Lsession_record_00568b7e: movb %al, _dat_00864e39\n\t"
                     ".Lsession_record_00568b83: retl $0x14\n\t");
}

// Original 00568c40; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_00568c40() {
    __asm__ volatile(".Lsession_record_00568c40: pushl %esi\n\t"
                     ".Lsession_record_00568c41: movl 8(%esp), %esi\n\t"
                     ".Lsession_record_00568c45: pushl %edi\n\t"
                     ".Lsession_record_00568c46: movl $7, %ecx\n\t"
                     ".Lsession_record_00568c4b: movl $_dat_007094a8, %edi\n\t"
                     ".Lsession_record_00568c50: rep movsl (%esi), %es:(%edi)\n\t"
                     ".Lsession_record_00568c52: popl %edi\n\t"
                     ".Lsession_record_00568c53: popl %esi\n\t"
                     ".Lsession_record_00568c54: retl $4\n\t");
}

// Original 00568c60; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_00568c60() {
    __asm__ volatile(".Lsession_record_00568c60: movl 8(%esp), %eax\n\t"
                     ".Lsession_record_00568c64: movl $_dat_021fe1bc+1096, %edx\n\t"
                     ".Lsession_record_00568c69: movl $1, _dat_00868dd4\n\t"
                     ".Lsession_record_00568c73: subl %eax, %edx\n\t"
                     ".Lsession_record_00568c75: movb (%eax), %cl\n\t"
                     ".Lsession_record_00568c77: movb %cl, (%edx, %eax)\n\t"
                     ".Lsession_record_00568c7a: incl %eax\n\t"
                     ".Lsession_record_00568c7b: testb %cl, %cl\n\t"
                     ".Lsession_record_00568c7d: jne .Lsession_record_00568c75\n\t"
                     ".Lsession_record_00568c7f: retl $8\n\t");
}

// Original 005692f0; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_005692f0() {
    __asm__ volatile(".Lsession_record_005692f0: movl 4(%esp), %eax\n\t"
                     ".Lsession_record_005692f4: movl $_dat_021fe1bc+1096, %edx\n\t"
                     ".Lsession_record_005692f9: movl $0xb, _dat_00868dd4\n\t"
                     ".Lsession_record_00569303: subl %eax, %edx\n\t"
                     ".Lsession_record_00569305: movb (%eax), %cl\n\t"
                     ".Lsession_record_00569307: movb %cl, (%edx, %eax)\n\t"
                     ".Lsession_record_0056930a: incl %eax\n\t"
                     ".Lsession_record_0056930b: testb %cl, %cl\n\t"
                     ".Lsession_record_0056930d: jne .Lsession_record_00569305\n\t"
                     ".Lsession_record_0056930f: retl $4\n\t");
}

// Original 0056b1b0; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_0056b1b0() {
    __asm__ volatile(".Lsession_record_0056b1b0: movl 4(%esp), %eax\n\t"
                     ".Lsession_record_0056b1b4: movl 8(%esp), %ecx\n\t"
                     ".Lsession_record_0056b1b8: movl 0xc(%esp), %edx\n\t"
                     ".Lsession_record_0056b1bc: movl %eax, _dat_00865694\n\t"
                     ".Lsession_record_0056b1c1: movl 0x10(%esp), %eax\n\t"
                     ".Lsession_record_0056b1c5: movl %ecx, _dat_00865698\n\t"
                     ".Lsession_record_0056b1cb: movl 0x14(%esp), %ecx\n\t"
                     ".Lsession_record_0056b1cf: movl %edx, _dat_0086569c\n\t"
                     ".Lsession_record_0056b1d5: movl 0x18(%esp), %edx\n\t"
                     ".Lsession_record_0056b1d9: movl %eax, _dat_008656a0\n\t"
                     ".Lsession_record_0056b1de: movl 0x1c(%esp), %eax\n\t"
                     ".Lsession_record_0056b1e2: movl %ecx, _dat_008656a4\n\t"
                     ".Lsession_record_0056b1e8: movl 0x20(%esp), %ecx\n\t"
                     ".Lsession_record_0056b1ec: movl %edx, _dat_008656a8\n\t"
                     ".Lsession_record_0056b1f2: movl 0x24(%esp), %edx\n\t"
                     ".Lsession_record_0056b1f6: movl %eax, _dat_008656ac\n\t"
                     ".Lsession_record_0056b1fb: movl 0x28(%esp), %eax\n\t"
                     ".Lsession_record_0056b1ff: movl %ecx, _dat_008656b0\n\t"
                     ".Lsession_record_0056b205: movl 0x2c(%esp), %ecx\n\t"
                     ".Lsession_record_0056b209: movl %edx, _dat_008656b4\n\t"
                     ".Lsession_record_0056b20f: movl 0x30(%esp), %edx\n\t"
                     ".Lsession_record_0056b213: movl %eax, _dat_008656b8\n\t"
                     ".Lsession_record_0056b218: movl %ecx, _dat_008656bc\n\t"
                     ".Lsession_record_0056b21e: movl %edx, _dat_008656c0\n\t"
                     ".Lsession_record_0056b224: retl $0x30\n\t");
}

// Original 0056cc60; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_0056cc60() {
    __asm__ volatile(".Lsession_record_0056cc60: movzbl 4(%esp), %eax\n\t"
                     ".Lsession_record_0056cc65: decl %eax\n\t"
                     ".Lsession_record_0056cc66: je .Lsession_record_0056cc99\n\t"
                     ".Lsession_record_0056cc68: decl %eax\n\t"
                     ".Lsession_record_0056cc69: je .Lsession_record_0056cc86\n\t"
                     ".Lsession_record_0056cc6b: decl %eax\n\t"
                     ".Lsession_record_0056cc6c: jne .Lsession_record_0056ccaa\n\t"
                     ".Lsession_record_0056cc6e: movb 8(%esp), %cl\n\t"
                     ".Lsession_record_0056cc72: xorl %eax, %eax\n\t"
                     ".Lsession_record_0056cc74: testb %cl, %cl\n\t"
                     ".Lsession_record_0056cc76: sete %al\n\t"
                     ".Lsession_record_0056cc79: movl %eax, _dat_0086de04\n\t"
                     ".Lsession_record_0056cc7e: movl %eax, _dat_0086de08\n\t"
                     ".Lsession_record_0056cc83: retl $8\n\t"
                     ".Lsession_record_0056cc86: movb 8(%esp), %cl\n\t"
                     ".Lsession_record_0056cc8a: xorl %eax, %eax\n\t"
                     ".Lsession_record_0056cc8c: testb %cl, %cl\n\t"
                     ".Lsession_record_0056cc8e: sete %al\n\t"
                     ".Lsession_record_0056cc91: movl %eax, _dat_0086de08\n\t"
                     ".Lsession_record_0056cc96: retl $8\n\t"
                     ".Lsession_record_0056cc99: movb 8(%esp), %al\n\t"
                     ".Lsession_record_0056cc9d: xorl %ecx, %ecx\n\t"
                     ".Lsession_record_0056cc9f: testb %al, %al\n\t"
                     ".Lsession_record_0056cca1: sete %cl\n\t"
                     ".Lsession_record_0056cca4: movl %ecx, _dat_0086de04\n\t"
                     ".Lsession_record_0056ccaa: retl $8\n\t");
}

// Original 0056ccb0; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_0056ccb0() {
    __asm__ volatile(".Lsession_record_0056ccb0: movzbl 4(%esp), %eax\n\t"
                     ".Lsession_record_0056ccb5: decl %eax\n\t"
                     ".Lsession_record_0056ccb6: je .Lsession_record_0056ccce\n\t"
                     ".Lsession_record_0056ccb8: decl %eax\n\t"
                     ".Lsession_record_0056ccb9: jne .Lsession_record_0056ccdf\n\t"
                     ".Lsession_record_0056ccbb: movb 8(%esp), %cl\n\t"
                     ".Lsession_record_0056ccbf: xorl %eax, %eax\n\t"
                     ".Lsession_record_0056ccc1: testb %cl, %cl\n\t"
                     ".Lsession_record_0056ccc3: setne %al\n\t"
                     ".Lsession_record_0056ccc6: movl %eax, _dat_0086de10\n\t"
                     ".Lsession_record_0056cccb: retl $8\n\t"
                     ".Lsession_record_0056ccce: movb 8(%esp), %al\n\t"
                     ".Lsession_record_0056ccd2: xorl %ecx, %ecx\n\t"
                     ".Lsession_record_0056ccd4: testb %al, %al\n\t"
                     ".Lsession_record_0056ccd6: setne %cl\n\t"
                     ".Lsession_record_0056ccd9: movl %ecx, _dat_0086de0c\n\t"
                     ".Lsession_record_0056ccdf: retl $8\n\t");
}

// Original 0056ce80; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_0056ce80() {
    __asm__ volatile(".Lsession_record_0056ce80: movb 4(%esp), %al\n\t"
                     ".Lsession_record_0056ce84: cmpb $1, %al\n\t"
                     ".Lsession_record_0056ce86: jne .Lsession_record_0056ce94\n\t"
                     ".Lsession_record_0056ce88: movl 8(%esp), %eax\n\t"
                     ".Lsession_record_0056ce8c: movl %eax, _dat_0086de14\n\t"
                     ".Lsession_record_0056ce91: retl $8\n\t"
                     ".Lsession_record_0056ce94: cmpb $2, %al\n\t"
                     ".Lsession_record_0056ce96: jne .Lsession_record_0056cea2\n\t"
                     ".Lsession_record_0056ce98: movl 8(%esp), %ecx\n\t"
                     ".Lsession_record_0056ce9c: movl %ecx, _dat_0086de18\n\t"
                     ".Lsession_record_0056cea2: retl $8\n\t");
}

// Original 0056cfd0; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_0056cfd0() {
    __asm__ volatile(".Lsession_record_0056cfd0: movzbl 0xc(%esp), %eax\n\t"
                     ".Lsession_record_0056cfd5: movb 4(%esp), %cl\n\t"
                     ".Lsession_record_0056cfd9: movb 8(%esp), %dl\n\t"
                     ".Lsession_record_0056cfdd: leal (%eax, %eax, 2), %eax\n\t"
                     ".Lsession_record_0056cfe0: shll $2, %eax\n\t"
                     ".Lsession_record_0056cfe3: movb %cl, _dat_021fe1bc+4(%eax)\n\t"
                     ".Lsession_record_0056cfe9: movl 0x10(%esp), %ecx\n\t"
                     ".Lsession_record_0056cfed: movl $1, _dat_021fe1bc(%eax)\n\t"
                     ".Lsession_record_0056cff7: movb %dl, _dat_021fe1bc+5(%eax)\n\t"
                     ".Lsession_record_0056cffd: movl %ecx, _dat_021fe1c4(%eax)\n\t"
                     ".Lsession_record_0056d003: retl $0x10\n\t");
}

// Original 0056d760; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_0056d760() {
    __asm__ volatile(".Lsession_record_0056d760: movb 4(%esp), %al\n\t"
                     ".Lsession_record_0056d764: cmpb $0xf0, %al\n\t"
                     ".Lsession_record_0056d766: jae .Lsession_record_0056d77a\n\t"
                     ".Lsession_record_0056d768: movzbl %al, %eax\n\t"
                     ".Lsession_record_0056d76b: leal _dat_021fea06(%eax, %eax, 2), %edx\n\t"
                     ".Lsession_record_0056d772: xorl %ecx, %ecx\n\t"
                     ".Lsession_record_0056d774: movw %cx, (%edx)\n\t"
                     ".Lsession_record_0056d777: movb %cl, 2(%edx)\n\t"
                     ".Lsession_record_0056d77a: retl $4\n\t");
}

// Original 00570bc0; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_00570bc0() {
    __asm__ volatile(".Lsession_record_00570bc0: movl %ecx, %edx\n\t"
                     ".Lsession_record_00570bc2: xorl %eax, %eax\n\t"
                     ".Lsession_record_00570bc4: pushl %ebx\n\t"
                     ".Lsession_record_00570bc5: movb 0xc(%esp), %bl\n\t"
                     ".Lsession_record_00570bc9: pushl %esi\n\t"
                     ".Lsession_record_00570bca: pushl %edi\n\t"
                     ".Lsession_record_00570bcb: movl $0xa, %ecx\n\t"
                     ".Lsession_record_00570bd0: leal 0x205(%edx), %edi\n\t"
                     ".Lsession_record_00570bd6: rep stosl %eax, %es:(%edi)\n\t"
                     ".Lsession_record_00570bd8: stosw %ax, %es:(%edi)\n\t"
                     ".Lsession_record_00570bda: stosb %al, %es:(%edi)\n\t"
                     ".Lsession_record_00570bdb: movl $1, 0x200(%edx)\n\t"
                     ".Lsession_record_00570be5: movb %bl, 0x207(%edx)\n\t"
                     ".Lsession_record_00570beb: movl _dat_0223f100, %eax\n\t"
                     ".Lsession_record_00570bf0: movl $0, 0x1ec(%eax)\n\t"
                     ".Lsession_record_00570bfa: xorl %ecx, %ecx\n\t"
                     ".Lsession_record_00570bfc: leal 0x230(%edx), %esi\n\t"
                     ".Lsession_record_00570c02: movl %esi, %eax\n\t"
                     ".Lsession_record_00570c04: movl %ecx, (%eax)\n\t"
                     ".Lsession_record_00570c06: movl %ecx, 4(%eax)\n\t"
                     ".Lsession_record_00570c09: movl %ecx, 8(%eax)\n\t"
                     ".Lsession_record_00570c0c: movw %cx, 0xc(%eax)\n\t"
                     ".Lsession_record_00570c10: movb %cl, 0xe(%eax)\n\t"
                     ".Lsession_record_00570c13: movl 0x10(%esp), %ecx\n\t"
                     ".Lsession_record_00570c17: subl %ecx, %esi\n\t"
                     ".Lsession_record_00570c19: leal (%esp), %esp\n\t"
                     ".Lsession_record_00570c20: movb (%ecx), %al\n\t"
                     ".Lsession_record_00570c22: movb %al, (%esi, %ecx)\n\t"
                     ".Lsession_record_00570c25: incl %ecx\n\t"
                     ".Lsession_record_00570c26: testb %al, %al\n\t"
                     ".Lsession_record_00570c28: jne .Lsession_record_00570c20\n\t"
                     ".Lsession_record_00570c2a: movzbl %bl, %esi\n\t"
                     ".Lsession_record_00570c2d: movb %al, 0x23e(%edx)\n\t"
                     ".Lsession_record_00570c33: xorl %eax, %eax\n\t"
                     ".Lsession_record_00570c35: testl %esi, %esi\n\t"
                     ".Lsession_record_00570c37: jle .Lsession_record_00570c52\n\t"
                     ".Lsession_record_00570c39: leal 0x208(%edx), %ecx\n\t"
                     ".Lsession_record_00570c3f: movl 0x18(%esp), %edx\n\t"
                     ".Lsession_record_00570c43: movw (%edx, %eax, 2), %di\n\t"
                     ".Lsession_record_00570c47: movw %di, (%ecx)\n\t"
                     ".Lsession_record_00570c4a: incl %eax\n\t"
                     ".Lsession_record_00570c4b: addl $2, %ecx\n\t"
                     ".Lsession_record_00570c4e: cmpl %esi, %eax\n\t"
                     ".Lsession_record_00570c50: jl .Lsession_record_00570c43\n\t"
                     ".Lsession_record_00570c52: popl %edi\n\t"
                     ".Lsession_record_00570c53: popl %esi\n\t"
                     ".Lsession_record_00570c54: popl %ebx\n\t"
                     ".Lsession_record_00570c55: retl $0xc\n\t");
}

// Original 00570c60; every alternate branch/return retained.
extern "C" __attribute__((naked)) void FUN_00570c60() {
    __asm__ volatile(".Lsession_record_00570c60: pushl %edi\n\t"
                     ".Lsession_record_00570c61: movl %ecx, %edx\n\t"
                     ".Lsession_record_00570c63: xorl %eax, %eax\n\t"
                     ".Lsession_record_00570c65: movl $0xa, %ecx\n\t"
                     ".Lsession_record_00570c6a: leal 0x205(%edx), %edi\n\t"
                     ".Lsession_record_00570c70: rep stosl %eax, %es:(%edi)\n\t"
                     ".Lsession_record_00570c72: stosw %ax, %es:(%edi)\n\t"
                     ".Lsession_record_00570c74: stosb %al, %es:(%edi)\n\t"
                     ".Lsession_record_00570c75: movl $1, 0x200(%edx)\n\t"
                     ".Lsession_record_00570c7f: movl _dat_0223f100, %eax\n\t"
                     ".Lsession_record_00570c84: movl $0, 0x1ec(%eax)\n\t"
                     ".Lsession_record_00570c8e: popl %edi\n\t"
                     ".Lsession_record_00570c8f: retl\n\t");
}
