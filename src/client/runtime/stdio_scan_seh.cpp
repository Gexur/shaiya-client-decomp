// Original5d3eb6 algorithm, with instruction-derived storage and restored SEH.
#include "runtime/stdio_scan.h"
#include "runtime/stdio_input.h"
#include "runtime/character_case.h"
#include "runtime/character_classify.h"
#include "runtime/multibyte_input.h"
#include "runtime/multibyte.h"
#include "runtime/floating_text.h"
#include "runtime/fpmath.h"
#include "runtime/heap.h"
#include "runtime/nls.h"
#include "core/memory.h"
#include "core/uint64_multiply.h"
namespace {
using Assign = void*(__cdecl*)(int32_t, void*, const char*);
uint16_t scan_load16(const void* p) {
    uint32_t v;
    __asm__ volatile("movzwl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return uint16_t(v);
}
void scan_store64(void* p, uint64_t v) {
    __asm__ volatile("movl %1,(%0)\n\tmovl %2,4(%0)" ::"r"(p), "r"(uint32_t(v)),
                     "r"(uint32_t(v >> 32))
                     : "memory");
}
} // namespace
extern "C" int32_t fun_005d4654() {
    return 1;
}
extern "C" int32_t fun_005d3eb6(OriginalFile* param_1, const char* format,
                                const void* argument_words)

{
    uint8_t bVar1;
    uint8_t* puVar2;
    OriginalFile* _File;
    int iVar3;
    int iVar4;
    uint8_t bVar5;
    uint8_t bVar6;
    uint32_t uVar7;
    uint16_t* pwVar8;
    uint32_t uVar9;
    char* pcVar10;
    char* pcVar11;
    uint8_t* pbVar12;
    uint8_t* pbVar13;
    uint8_t* pbVar14;
    uint8_t* param_2 = reinterpret_cast<uint8_t*>(const_cast<char*>(format));
    auto* param_3 = static_cast<uint32_t*>(const_cast<void*>(argument_words));
    uint32_t heap_bitmap = 0;
    uint16_t* pwVar15;
    bool bVar16;

    uint32_t* local_1ec;
    uint32_t local_1e0;
    unsigned char local_1dc[4];
    uint32_t* local_1d8;
    int local_1d4;
    unsigned char input_bytes[2];

    uint8_t* local_1cc;
    uint32_t local_1c8;
    int local_1c4;
    int local_1c0;
    uint16_t* local_1bc;
    uint8_t local_1b5;
    uint64_t local_1b4;
    int local_1ac;
    uint8_t local_1a5;
    int local_1a4;
    uint8_t* local_1a0;
    char local_19b;
    char local_19a;
    char local_199;
    OriginalFile* local_198;
    uint32_t local_194;
    char local_18f;
    char local_18e;
    char local_18d;
    int local_18c;
    int local_188;
    char local_181;
    char collected[352];

    local_198 = param_1;
    local_1a0 = param_2;
    local_1d8 = param_3;
    local_1cc = (uint8_t*)0x0;
    local_1bc = (uint16_t*)0x0;
    local_194 = 0;
    local_199 = '\0';
    local_188 = 0;
    local_1c4 = 0;
    pbVar12 = local_1a0;
LAB_005d3f1e:
    do {
        local_1a0 = pbVar12;
        if (*local_1a0 == 0) {
        LAB_005d4c98:
            if ((local_194 == 0xffffffff) && ((local_1c4 == 0 && (local_199 == '\0')))) {
                local_1c4 = -1;
            }
            goto return_result;
        }
        iVar3 = fun_005d92ae((uint32_t)*local_1a0);
        pbVar12 = local_1a0;
        if (iVar3 == 0) {
            if (*local_1a0 == 0x25) {
                iVar3 = 0;
                local_1ac = 0;
                local_1a5 = 0;
                local_1a4 = 0;
                local_1c0 = 0;
                local_18c = 0;
                local_1b5 = 0;
                local_19b = '\0';
                local_18e = '\0';
                local_181 = '\0';
                local_19a = '\0';
                local_18d = '\0';
                local_18f = '\x01';
                local_1d4 = 0;
                do {
                    pbVar13 = pbVar12 + 1;
                    uVar7 = (uint32_t)*pbVar13;
                    iVar4 = fun_005d9235(uVar7);
                    pbVar14 = pbVar13;
                    if (iVar4 == 0) {
                        if (uVar7 < 0x4f) {
                            if (uVar7 != 0x4e) {
                                if (uVar7 == 0x2a) {
                                    local_18e = local_18e + '\x01';
                                } else if (uVar7 != 0x46) {
                                    if (uVar7 == 0x49) {
                                        bVar6 = pbVar12[2];
                                        if ((bVar6 == 0x36) && (pbVar12[3] == 0x34)) {
                                            local_1d4 = local_1d4 + 1;
                                            local_1b4 = 0;
                                            pbVar14 = pbVar12 + 3;
                                        } else if (((bVar6 != 0x33) ||
                                                    (pbVar14 = pbVar12 + 3, *pbVar14 != 0x32)) &&
                                                   ((((pbVar14 = pbVar13,
                                                       bVar6 != 100 && (bVar6 != 0x69)) &&
                                                      (bVar6 != 0x6f)) &&
                                                     ((bVar6 != 0x78 && (bVar6 != 0x58))))))
                                            goto LAB_005d40b2;
                                    } else if (uVar7 == 0x4c) {
                                        local_18f = local_18f + '\x01';
                                    } else {
                                    LAB_005d40b2:
                                        local_181 = local_181 + '\x01';
                                        pbVar14 = pbVar13;
                                    }
                                }
                            }
                        } else if (uVar7 == 0x68) {
                            local_18f = local_18f + -1;
                            local_18d = local_18d + -1;
                        } else {
                            if (uVar7 == 0x6c) {
                                local_18f = local_18f + '\x01';
                            } else if (uVar7 != 0x77)
                                goto LAB_005d40b2;
                            local_18d = local_18d + '\x01';
                        }
                    } else {
                        local_1c0 = local_1c0 + 1;
                        iVar3 = (uVar7 - 0x30) + iVar3 * 10;
                    }
                    pbVar12 = pbVar14;
                } while (local_181 == '\0');
                if (local_18e == '\0') {
                    local_1ec = local_1d8;
                    local_1bc = (uint16_t*)*local_1d8;
                    local_1d8 = local_1d8 + 1;
                }
                pwVar8 = local_1bc;
                local_181 = '\0';
                if ((local_18d == '\0') &&
                    ((*pbVar14 == 0x53 || (local_18d = -1, *pbVar14 == 0x43)))) {
                    local_18d = '\x01';
                }
                uVar9 = *pbVar14 | 0x20;
                local_1c8 = uVar9;
                local_1a0 = pbVar14;
                uVar7 = local_194;
                local_18c = iVar3;

                if (uVar9 != 0x6e) {
                    if ((uVar9 == 99) || (uVar9 == 0x7b)) {
                        local_188 = local_188 + 1;
                        uVar7 = fun_005d3ea0(local_198);

                    } else {
                        do {
                            local_188 = local_188 + 1;
                            uVar7 = fun_005d3ea0(local_198);
                            iVar3 = fun_005d92ae(uVar7);
                            uVar9 = local_1c8;

                        } while (iVar3 != 0);
                    }
                }
                local_194 = uVar7;
                _File = local_198;
                uVar7 = local_194;
                if ((local_1c0 != 0) && (local_18c == 0)) {
                LAB_005d4c59:
                    if (uVar7 != 0xffffffff) {

                        fun_005dd176(local_194, local_198);
                    }
                    goto LAB_005d4c98;
                }

                if ((int)uVar9 < 0x70) {
                    if (uVar9 == 0x6f) {
                    LAB_005d48c2:
                        if (local_194 == 0x2d) {
                            local_19b = '\x01';
                        } else if (local_194 != 0x2b)
                            goto LAB_005d4909;
                        local_18c = local_18c + -1;
                        if ((local_18c == 0) && (local_1c0 != 0)) {
                            local_181 = '\x01';
                        } else {
                            local_188 = local_188 + 1;
                            local_194 = fun_005d3ea0(local_198);
                        }
                        goto LAB_005d4909;
                    }
                    if (uVar9 != 99) {
                        if (uVar9 == 100)
                            goto LAB_005d48c2;
                        if ((int)uVar9 < 0x65) {
                        LAB_005d45bd:
                            if (*pbVar14 != local_194)
                                goto LAB_005d4c59;
                            local_199 = local_199 + -1;
                            local_1a0 = pbVar14;
                            if (local_18e == '\0') {
                                local_1d8 = local_1ec;
                            }
                            goto LAB_005d4436;
                        }
                        if (0x67 < (int)uVar9) {
                            if (uVar9 == 0x69) {
                                uVar9 = 100;
                                goto LAB_005d420e;
                            }
                            if (uVar9 != 0x6e)
                                goto LAB_005d45bd;
                            iVar3 = local_188;
                            local_1a0 = pbVar14;
                            if (local_18e != '\0')
                                goto LAB_005d4436;
                            goto LAB_005d4bb6;
                        }
                        pcVar10 = &collected[0];
                        if (local_194 == 0x2d) {
                            collected[0] = '-';
                            pcVar10 = (collected + 1);
                        LAB_005d424d:
                            local_18c = local_18c + -1;
                            local_188 = local_188 + 1;
                            local_194 = fun_005d3ea0(local_198);

                        } else if (local_194 == 0x2b)
                            goto LAB_005d424d;

                        if ((local_1c0 == 0) || (0x15d < local_18c)) {
                            local_18c = 0x15d;
                        }
                        while (true) {
                            uVar7 = local_194;
                            iVar3 = fun_005d9235(local_194);
                            if ((iVar3 == 0) || (iVar3 = local_18c + -1, bVar16 = local_18c == 0,
                                                 local_18c = iVar3, bVar16))
                                break;
                            local_1a4 = local_1a4 + 1;
                            *pcVar10 = (char)uVar7;
                            pcVar10 = pcVar10 + 1;
                            local_188 = local_188 + 1;
                            local_194 = fun_005d3ea0(local_198);
                        }
                        if ((dat_0070e4e4[0] == (char)uVar7) &&
                            (iVar3 = local_18c + -1, bVar16 = local_18c != 0, local_18c = iVar3,
                             bVar16)) {
                            local_188 = local_188 + 1;
                            uVar7 = fun_005d3ea0(local_198);
                            *pcVar10 = dat_0070e4e4[0];
                            while (true) {
                                pcVar10 = pcVar10 + 1;
                                local_194 = uVar7;
                                iVar3 = fun_005d9235(uVar7);
                                if ((iVar3 == 0) ||
                                    (iVar3 = local_18c + -1, bVar16 = local_18c == 0,
                                     local_18c = iVar3, bVar16))
                                    break;
                                local_1a4 = local_1a4 + 1;
                                *pcVar10 = (char)uVar7;
                                local_188 = local_188 + 1;
                                uVar7 = fun_005d3ea0(local_198);
                            }
                        }
                        pcVar11 = pcVar10;
                        if ((local_1a4 != 0) && (((uVar7 == 0x65 || (uVar7 == 0x45)) &&
                                                  (iVar3 = local_18c + -1, bVar16 = local_18c != 0,
                                                   local_18c = iVar3, bVar16)))) {
                            *pcVar10 = 'e';
                            pcVar11 = pcVar10 + 1;
                            local_188 = local_188 + 1;
                            local_194 = fun_005d3ea0(local_198);
                            if (local_194 == 0x2d) {
                                *pcVar11 = '-';
                                pcVar11 = pcVar10 + 2;
                            LAB_005d438d:
                                bVar16 = local_18c != 0;
                                local_18c = local_18c + -1;
                                if (bVar16)
                                    goto LAB_005d43be;
                                local_18c = 0;
                            } else if (local_194 == 0x2b)
                                goto LAB_005d438d;
                            while (true) {
                                uVar7 = local_194;
                                iVar3 = fun_005d9235(local_194);
                                if ((iVar3 == 0) ||
                                    (iVar3 = local_18c + -1, bVar16 = local_18c == 0,
                                     local_18c = iVar3, bVar16))
                                    break;
                                local_1a4 = local_1a4 + 1;
                                *pcVar11 = (char)uVar7;
                                pcVar11 = pcVar11 + 1;
                            LAB_005d43be:
                                local_188 = local_188 + 1;
                                local_194 = fun_005d3ea0(local_198);
                            }
                        }
                        local_188 = local_188 + -1;
                        if (uVar7 != 0xffffffff) {
                            fun_005dd176(uVar7, _File);
                        }
                        if (local_1a4 != 0) {
                            if (local_18e == '\0') {
                                local_1c4 = local_1c4 + 1;
                                *pcVar11 = '\0';
                                reinterpret_cast<Assign>(dat_0070e508)(local_18f - 1, local_1bc,
                                                                       &collected[0]);
                            }
                            goto LAB_005d4436;
                        }
                        goto LAB_005d4c98;
                    }
                    if (local_1c0 == 0) {
                        local_1c0 = 1;
                        local_18c = local_18c + 1;
                    }
                LAB_005d445c:
                    if ('\0' < local_18d) {
                        local_19a = '\x01';
                    }
                LAB_005d446c:
                    local_188 = local_188 + -1;
                    pwVar15 = pwVar8;
                    if (local_194 != 0xffffffff) {
                        fun_005dd176(local_194, local_198);
                    }
                    while (true) {
                        if ((local_1c0 != 0) && (iVar3 = local_18c + -1, bVar16 = local_18c == 0,
                                                 local_18c = iVar3, bVar16))
                            goto LAB_005d486d;
                        local_188 = local_188 + 1;
                        local_194 = fun_005d3ea0(local_198);
                        if ((local_194 == 0xffffffff) ||
                            ((bVar6 = (uint8_t)local_194,
                              uVar9 != 99 &&
                                  (((uVar9 != 0x73 ||
                                     (((8 < (int)local_194 && ((int)local_194 < 0xe)) ||
                                       (local_194 == 0x20)))) &&
                                    ((uVar9 != 0x7b ||
                                      (uVar9 = local_1c8,
                                       ((int)(char)(local_1cc[(int)local_194 >> 3] ^ local_1b5) &
                                        1 << (bVar6 & 7)) == 0))))))))
                            break;
                        if (local_18e == '\0') {
                            if (local_19a == '\0') {
                                *(uint8_t*)pwVar8 = bVar6;
                                pwVar8 = (uint16_t*)((int)pwVar8 + 1);
                                local_1bc = pwVar8;
                            } else {
                                input_bytes[0] = bVar6;
                                if ((dat_0070e4d8[local_194 & 0xff] & 0x8000) != 0) {
                                    local_188 = local_188 + 1;
                                    input_bytes[1] = fun_005d3ea0(local_198);
                                }
                                fun_005dd2a2(reinterpret_cast<uint16_t*>(local_1dc),
                                             (char*)&input_bytes[0], dat_0070e4e0);
                                *pwVar8 = scan_load16(local_1dc);
                                pwVar8 = pwVar8 + 1;
                                local_1bc = pwVar8;
                            }
                        } else {
                            pwVar15 = (uint16_t*)((int)pwVar15 + 1);
                        }
                    }
                    local_188 = local_188 + -1;
                    if (local_194 != 0xffffffff) {
                        fun_005dd176(local_194, local_198);
                    }
                LAB_005d486d:
                    if (pwVar15 == pwVar8)
                        goto LAB_005d4c98;
                    if ((local_18e == '\0') && (local_1c4 = local_1c4 + 1, local_1c8 != 99)) {
                        if (local_19a == '\0') {
                            *(uint8_t*)local_1bc = 0;
                        } else {
                            *local_1bc = L'\0';
                        }
                    }
                } else {
                    if (uVar9 == 0x70) {
                        local_18f = '\x01';
                        goto LAB_005d48c2;
                    }
                    if (uVar9 == 0x73)
                        goto LAB_005d445c;
                    if (uVar9 == 0x75)
                        goto LAB_005d48c2;
                    if (uVar9 != 0x78) {
                        if (uVar9 != 0x7b)
                            goto LAB_005d45bd;
                        if ('\0' < local_18d) {
                            local_19a = '\x01';
                        }
                        pbVar14 = local_1a0 + 1;
                        pbVar12 = pbVar14;
                        if (*pbVar14 == 0x5e) {
                            pbVar12 = local_1a0 + 2;
                            local_1b5 = 0xff;
                        }
                        if (local_1cc == (uint8_t*)0x0) {
                            // Actual5d4638..5d468f exception scope; Ghidra omits the handler.
                            __try {
                                volatile uint32_t bytes = 32;
                                local_1cc = static_cast<uint8_t*>(__builtin_alloca(bytes));
                            } __except (fun_005d4654()) {
                                fun_005cfb61();
                                local_1cc = static_cast<uint8_t*>(fun_005cfade(32));
                                if (!local_1cc)
                                    goto return_result;
                                heap_bitmap = 1;
                            }
                        }
                        puVar2 = local_1cc;
                        local_1a0 = pbVar14;
                        fun_005dceb0(local_1cc, 0, 0x20);
                        bVar6 = local_1a5;
                        if ((local_1c8 == 0x7b) && (*pbVar12 == 0x5d)) {
                            puVar2[0xb] = 0x20;
                            pbVar12 = pbVar12 + 1;
                            bVar6 = 0x5d;
                        }
                        while (bVar5 = *pbVar12, bVar5 != 0x5d) {
                            if (((bVar5 == 0x2d) && (bVar6 != 0)) &&
                                (bVar1 = pbVar12[1], bVar1 != 0x5d)) {
                                bVar5 = bVar1;
                                if (bVar6 < bVar1) {
                                    bVar5 = bVar6;
                                    bVar6 = bVar1;
                                }
                                if (bVar5 <= bVar6) {
                                    uVar7 = (uint32_t)bVar5;
                                    local_1e0 = (uint32_t)(uint8_t)((bVar6 - bVar5) + 1);
                                    do {
                                        puVar2[uVar7 >> 3] =
                                            puVar2[uVar7 >> 3] | '\x01' << ((uint8_t)uVar7 & 7);
                                        uVar7 = uVar7 + 1;
                                        local_1e0 = local_1e0 - 1;
                                    } while (local_1e0 != 0);
                                }
                                pbVar12 = pbVar12 + 2;
                                bVar6 = 0;
                            } else {
                                local_1a5 = bVar5;
                                puVar2[bVar5 >> 3] = puVar2[bVar5 >> 3] | '\x01' << (bVar5 & 7);
                                pbVar12 = pbVar12 + 1;
                                bVar6 = local_1a5;
                            }
                        }
                        pwVar8 = local_1bc;
                        uVar9 = local_1c8;
                        if (local_1c8 == 0x7b) {
                            local_1a0 = pbVar12;
                        }
                        goto LAB_005d446c;
                    }
                LAB_005d420e:
                    if (local_194 == 0x2d) {
                        local_19b = '\x01';
                    LAB_005d475b:
                        local_18c = local_18c + -1;
                        if ((local_18c == 0) && (local_1c0 != 0)) {
                            local_181 = '\x01';
                        } else {
                            local_188 = local_188 + 1;
                            local_194 = fun_005d3ea0(local_198);
                        }
                    } else if (local_194 == 0x2b)
                        goto LAB_005d475b;

                    if (local_194 == 0x30) {
                        local_188 = local_188 + 1;
                        local_194 = fun_005d3ea0(local_198);
                        if (((char)local_194 == 'x') || ((char)local_194 == 'X')) {
                            local_188 = local_188 + 1;
                            local_194 = fun_005d3ea0(local_198);
                            if ((local_1c0 != 0) && (local_18c = local_18c + -2, local_18c < 1)) {
                                local_181 = local_181 + '\x01';
                            }
                            uVar9 = 0x78;
                        } else {
                            local_1a4 = 1;
                            if (uVar9 == 0x78) {
                                local_188 = local_188 + -1;
                                if (local_194 != 0xffffffff) {
                                    fun_005dd176(local_194, local_198);
                                }
                                local_194 = 0x30;
                            } else {
                                if ((local_1c0 != 0) &&
                                    (local_18c = local_18c + -1, local_18c == 0)) {
                                    local_181 = local_181 + '\x01';
                                }
                                uVar9 = 0x6f;
                            }
                        }
                    }
                LAB_005d4909:
                    uVar7 = local_194;

                    if (local_1d4 == 0) {
                        while (local_181 == '\0') {

                            if ((uVar9 == 0x78) || (uVar9 == 0x70)) {
                                iVar3 = fun_005d926f(uVar7);
                                if (iVar3 != 0) {
                                    local_1ac = int32_t(uint32_t(local_1ac) << 4);
                                    iVar3 = fun_005d9235(uVar7);
                                    if (iVar3 == 0) {
                                        uVar7 = (uVar7 & 0xffffffdf) - 7;
                                    }
                                    goto LAB_005d4aef;
                                }
                            LAB_005d4ae9:
                                local_181 = local_181 + '\x01';
                            } else {
                                iVar3 = fun_005d9235(uVar7);
                                if (iVar3 == 0)
                                    goto LAB_005d4ae9;
                                if (uVar9 == 0x6f) {
                                    if (0x37 < (int)uVar7)
                                        goto LAB_005d4ae9;
                                    local_1ac = int32_t(uint32_t(local_1ac) << 3);
                                } else {
                                    local_1ac = int32_t(uint32_t(local_1ac) * 10u);
                                }
                            }
                        LAB_005d4aef:

                            if (local_181 == '\0') {
                                local_1a4 = local_1a4 + 1;
                                local_1ac = local_1ac + -0x30 + uVar7;
                                if ((local_1c0 == 0) ||
                                    (local_18c = local_18c + -1, local_18c != 0)) {
                                    local_188 = local_188 + 1;
                                    uVar7 = fun_005d3ea0(local_198);

                                } else {
                                    local_181 = '\x01';
                                }
                            } else {
                                local_188 = local_188 + -1;
                                if (uVar7 != 0xffffffff) {
                                    fun_005dd176(uVar7, local_198);
                                }
                            }
                        }
                        local_194 = uVar7;
                        if (local_19b != '\0') {
                            local_1ac = -local_1ac;
                        }
                    } else {
                        while (local_181 == '\0') {

                            if ((uVar9 == 0x78) || (uVar9 == 0x70)) {
                                iVar3 = fun_005d926f(uVar7);
                                if (iVar3 != 0) {
                                    local_1b4 = local_1b4 << 4;
                                    iVar3 = fun_005d9235(uVar7);
                                    if (iVar3 == 0) {
                                        uVar7 = (uVar7 & 0xffffffdf) - 7;
                                    }
                                    goto LAB_005d49d1;
                                }
                            LAB_005d49cb:
                                local_181 = local_181 + '\x01';
                            } else {
                                iVar3 = fun_005d9235(uVar7);
                                if (iVar3 == 0)
                                    goto LAB_005d49cb;
                                if (uVar9 == 0x6f) {
                                    if (0x37 < (int)uVar7)
                                        goto LAB_005d49cb;
                                    local_1b4 = local_1b4 << 3;
                                } else {
                                    local_1b4 = multiply_uint64_words(
                                        uint32_t(local_1b4), uint32_t(local_1b4 >> 32), 10, 0);
                                }
                            }
                        LAB_005d49d1:
                            if (local_181 == '\0') {
                                local_1a4 = local_1a4 + 1;
                                if ((local_1c0 == 0) ||
                                    (local_18c = local_18c + -1, local_18c != 0)) {
                                    local_188 = local_188 + 1;
                                    local_1b4 = local_1b4 + (int)(uVar7 - 0x30);
                                    uVar7 = fun_005d3ea0(local_198);

                                } else {
                                    local_181 = '\x01';
                                    local_1b4 += int32_t(uVar7 - 0x30);
                                }
                            } else {
                                local_188 = local_188 + -1;

                                if (uVar7 != 0xffffffff) {
                                    fun_005dd176(uVar7, local_198);
                                }
                            }
                        }

                        local_194 = uVar7;
                        if (local_19b != '\0') {
                            local_1b4 = uint64_t(0) - local_1b4;
                        }
                    }
                    if (uVar9 == 0x46) {
                        local_1a4 = 0;
                    }
                    if (local_1a4 == 0)
                        goto LAB_005d4c98;

                    if (local_18e == '\0') {
                        local_1c4 = local_1c4 + 1;
                        iVar3 = local_1ac;
                        pwVar8 = local_1bc;
                    LAB_005d4bb6:

                        if (local_1d4 == 0) {
                            if (local_18f == '\0') {
                                *pwVar8 = (uint16_t)iVar3;
                            } else {
                                *(int*)pwVar8 = iVar3;
                            }
                        } else {
                            scan_store64(pwVar8, local_1b4);
                        }
                    }
                }
            LAB_005d4436:
                local_199 = local_199 + '\x01';
                local_1a0 = local_1a0 + 1;
            } else {
                local_188 = local_188 + 1;
                uVar7 = fun_005d3ea0(local_198);
                pbVar14 = pbVar12 + 1;
                local_1a0 = pbVar14;
                local_194 = uVar7;

                if (*pbVar12 != uVar7)
                    goto LAB_005d4c59;
                if ((dat_0070e4d8[uVar7 & 0xff] & 0x8000) != 0) {
                    local_188 = local_188 + 1;
                    uVar9 = fun_005d3ea0(local_198);
                    local_1a0 = pbVar12 + 2;
                    if (*pbVar14 != uVar9) {

                        if (uVar9 != 0xffffffff) {
                            fun_005dd176(uVar9, local_198);
                        }
                        goto LAB_005d4c59;
                    }
                    local_188 = local_188 + -1;
                }
            }
            pbVar12 = local_1a0;
            if ((local_194 == 0xffffffff) && ((*local_1a0 != 0x25 || (local_1a0[1] != 0x6e))))
                goto LAB_005d4c98;
            goto LAB_005d3f1e;
        }
        local_188 = local_188 + -1;
        do {
            local_188 = local_188 + 1;
            iVar3 = fun_005d3ea0(local_198);
            iVar4 = fun_005d92ae(iVar3);
        } while (iVar4 != 0);
        pbVar12 = local_1a0;
        if (iVar3 != -1) {
            fun_005dd176(iVar3, local_198);
            pbVar12 = local_1a0;
        }
        do {
            pbVar12 = pbVar12 + 1;
            iVar3 = fun_005d92ae((uint32_t)*pbVar12);
        } while (iVar3 != 0);
    } while (true);
return_result:
    if (heap_bitmap)
        fun_005cfaf0(local_1cc);
    return local_1c4;
}
