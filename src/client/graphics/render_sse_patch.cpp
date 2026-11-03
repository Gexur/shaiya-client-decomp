#include "graphics/render_sse_patch.h"
#include "graphics/render_cpu_features.h"

// Actual unresolved code-address relocations, never fabricated bodies.
extern "C" {
extern const unsigned char code_00684100[] __asm__("_FUN_00684100@24");
extern const unsigned char code_006841c0[] __asm__("_FUN_006841c0@24");
extern const unsigned char code_00684280[] __asm__("_FUN_00684280@24");
extern const unsigned char code_006844e0[] __asm__("_FUN_006844e0@24");
extern const unsigned char code_00684740[] __asm__("_FUN_00684740@24");
extern const unsigned char code_00684900[] __asm__("_FUN_00684900@24");
extern const unsigned char code_006849a0[] __asm__("_FUN_006849a0@24");
extern const unsigned char code_00684cc0[] __asm__("_FUN_00684cc0@24");
extern const unsigned char code_00684f3c[] __asm__("_FUN_00684f3c@12");
extern const unsigned char code_00684fd5[] __asm__("_FUN_00684fd5@8");
extern const unsigned char code_00685032[] __asm__("_FUN_00685032@12");
extern const unsigned char code_00685076[] __asm__("_FUN_00685076@8");
extern const unsigned char code_00685292[] __asm__("_FUN_00685292@8");
extern const unsigned char code_006854a7[] __asm__("_FUN_006854a7@16");
extern const unsigned char code_0068556c[] __asm__("_FUN_0068556c@12");
extern const unsigned char code_006855d8[] __asm__("_FUN_006855d8@16");
extern const unsigned char code_0068570f[] __asm__("_FUN_0068570f@24");
extern const unsigned char code_0068579c[] __asm__("_FUN_0068579c@24");
extern const unsigned char code_0068582e[] __asm__("_FUN_0068582e@8");
extern const unsigned char code_00685892[] __asm__("_FUN_00685892@8");
extern const unsigned char code_00685939[] __asm__("_FUN_00685939@8");
extern const unsigned char code_006859de[] __asm__("_FUN_006859de@28");
extern const unsigned char code_00686419[] __asm__("_FUN_00686419@12");
extern const unsigned char code_0068664b[] __asm__("_FUN_0068664b@4");
extern const unsigned char code_0068671a[] __asm__("_FUN_0068671a@16");
extern const unsigned char code_0068676a[] __asm__("_FUN_0068676a@12");
extern const unsigned char code_00686855[] __asm__("_FUN_00686855@8");
extern const unsigned char code_00686931[] __asm__("_FUN_00686931@8");
extern const unsigned char code_00686996[] __asm__("_FUN_00686996@8");
extern const unsigned char code_006869f6[] __asm__("_FUN_006869f6@8");
extern const unsigned char code_00686a51[] __asm__("_FUN_00686a51@16");
extern const unsigned char code_00686a98[] __asm__("_FUN_00686a98@8");
extern const unsigned char code_00686b07[] __asm__("_FUN_00686b07@8");
extern const unsigned char code_00686bd9[] __asm__("_FUN_00686bd9@8");
extern const unsigned char code_00686c8e[] __asm__("_FUN_00686c8e@28");
extern const unsigned char code_00687e8a[] __asm__("_FUN_00687e8a@16");
extern const unsigned char code_0068802f[] __asm__("_FUN_0068802f@20");
extern const unsigned char code_00688563[] __asm__("_FUN_00688563@12");
extern const unsigned char code_0068867e[] __asm__("_FUN_0068867e@28");
extern const unsigned char code_00689836[] __asm__("_FUN_00689836@12");
extern const unsigned char code_00689b18[] __asm__("_FUN_00689b18@12");
extern const unsigned char code_0068a246[] __asm__("_FUN_0068a246@12");
extern const unsigned char code_0068a264[] __asm__("_FUN_0068a264@12");
extern const unsigned char code_0068a2d7[] __asm__("_FUN_0068a2d7@12");
extern const unsigned char code_0068a340[] __asm__("_FUN_0068a340@8");
extern const unsigned char code_0068a39f[] __asm__("_FUN_0068a39f@24");
extern const unsigned char code_0068a410[] __asm__("_FUN_0068a410@24");
extern const unsigned char code_0068a4e4[] __asm__("_FUN_0068a4e4@24");
extern const unsigned char code_0068a824[] __asm__("_FUN_0068a824@12");
extern const unsigned char code_0068a82f[] __asm__("_FUN_0068a82f@24");
extern const unsigned char code_0068a9bb[] __asm__("_FUN_0068a9bb@24");
extern const unsigned char code_0068abd8[] __asm__("_FUN_0068abd8@24");
extern const unsigned char code_0068ad80[] __asm__("_FUN_0068ad80@12");
extern const unsigned char code_0068aec0[] __asm__("_FUN_0068aec0@12");
extern const unsigned char code_0068b03b[] __asm__("_FUN_0068b03b@12");
extern const unsigned char code_0068b092[] __asm__("_FUN_0068b092@12");
extern const unsigned char code_0068b0cd[] __asm__("_FUN_0068b0cd@12");
extern const unsigned char code_0068b133[] __asm__("_FUN_0068b133@24");
extern const unsigned char code_0068b1cb[] __asm__("_FUN_0068b1cb@24");
extern const unsigned char code_0068b214[] __asm__("_FUN_0068b214@8");
extern const unsigned char code_0068b257[] __asm__("_FUN_0068b257@24");
extern const unsigned char code_0068b302[] __asm__("_FUN_0068b302@12");
extern const unsigned char code_0068b386[] __asm__("_FUN_0068b386@8");
extern const unsigned char code_0068b3e5[] __asm__("_FUN_0068b3e5@16");
extern const unsigned char code_0068b519[] __asm__("_FUN_0068b519@24");
extern const unsigned char code_0068b58a[] __asm__("_FUN_0068b58a@24");
extern const unsigned char code_0068b652[] __asm__("_FUN_0068b652@24");
extern const unsigned char code_0068b730[] __asm__("_FUN_0068b730@12");
extern const unsigned char code_0068b773[] __asm__("_FUN_0068b773@16");
extern const unsigned char code_0068b857[] __asm__("_FUN_0068b857@16");
extern const unsigned char code_0068b915[] __asm__("_FUN_0068b915@8");
extern const unsigned char code_0068b979[] __asm__("_FUN_0068b979@12");
}

extern "C" uint64_t __cdecl FUN_0065191f(D3dxDispatchTable* table) {
    const uint64_t result = FUN_00651839();
    const uint32_t flags = uint32_t(result);
    if ((flags & 0xa0) == 0xa0) {
        table->entries[0] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b03b)); // original0x0065193f
        table->entries[1] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068a264)); // original0x00651945
        table->entries[2] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b302)); // original0x0065194c
        table->entries[3] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00686419)); // original0x00651953
        table->entries[5] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b092)); // original0x0065195a
        table->entries[6] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068a2d7)); // original0x00651961
        table->entries[7] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068a340)); // original0x00651968
        table->entries[8] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b386)); // original0x0065196f
        table->entries[9] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b0cd)); // original0x00651976
        table->entries[10] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068a824)); // original0x0065197d
        table->entries[11] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068664b)); // original0x00651984
        table->entries[13] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b730)); // original0x0065198b
        table->entries[14] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b773)); // original0x00651992
        table->entries[15] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068a82f)); // original0x00651999
        table->entries[16] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068a9bb)); // original0x006519a0
        table->entries[17] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b3e5)); // original0x006519a7
        table->entries[18] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b133)); // original0x006519ae
        table->entries[19] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068a246)); // original0x006519b5
        table->entries[20] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00684f3c)); // original0x006519bc
        table->entries[21] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00684fd5)); // original0x006519c3
        table->entries[22] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b915)); // original0x006519ca
        table->entries[23] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b857)); // original0x006519d1
        table->entries[24] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00685032)); // original0x006519d8
        table->entries[25] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00685076)); // original0x006519df
        table->entries[26] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_006854a7)); // original0x006519e6
        table->entries[27] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068671a)); // original0x006519ed
        table->entries[28] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068676a)); // original0x006519f4
        table->entries[29] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00686855)); // original0x006519fb
        table->entries[30] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068556c)); // original0x00651a02
        table->entries[31] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00686931)); // original0x00651a09
        table->entries[32] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00686996)); // original0x00651a10
        table->entries[33] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_006869f6)); // original0x00651a1a
        table->entries[34] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00686a51)); // original0x00651a24
        table->entries[35] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b979)); // original0x00651a2e
        table->entries[36] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_006855d8)); // original0x00651a38
        table->entries[37] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068570f)); // original0x00651a42
        table->entries[38] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00686a98)); // original0x00651a4c
        table->entries[39] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00686b07)); // original0x00651a56
        table->entries[40] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00686c8e)); // original0x00651a60
        table->entries[41] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00687e8a)); // original0x00651a6a
        table->entries[42] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068802f)); // original0x00651a74
        table->entries[43] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00688563)); // original0x00651a7e
        table->entries[44] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068579c)); // original0x00651a88
        table->entries[45] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068582e)); // original0x00651a92
        table->entries[55] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b519)); // original0x00651a9c
        table->entries[52] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068a39f)); // original0x00651aa6
        table->entries[49] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b1cb)); // original0x00651ab0
        table->entries[47] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b214)); // original0x00651aba
        table->entries[53] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b58a)); // original0x00651ac4
        table->entries[50] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068a410)); // original0x00651ace
        table->entries[56] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00685892)); // original0x00651ad8
        table->entries[57] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00685939)); // original0x00651ae2
        table->entries[54] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b652)); // original0x00651aec
        table->entries[48] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068b257)); // original0x00651af6
        table->entries[51] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068a4e4)); // original0x00651b00
        table->entries[4] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00689b18)); // original0x00651b0a
        table->entries[46] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_006859de)); // original0x00651b11
        table->entries[59] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068ad80)); // original0x00651b1b
        table->entries[58] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_0068aec0)); // original0x00651b25
        if ((flags & 0x300) == 0x300) {
            table->entries[16] = reinterpret_cast<D3dxCodeAddress>(
                const_cast<unsigned char*>(code_0068abd8)); // original0x00651b36
            table->entries[19] = reinterpret_cast<D3dxCodeAddress>(
                const_cast<unsigned char*>(code_00689836)); // original0x00651b3d
            table->entries[39] = reinterpret_cast<D3dxCodeAddress>(
                const_cast<unsigned char*>(code_00686bd9)); // original0x00651b44
            table->entries[40] = reinterpret_cast<D3dxCodeAddress>(
                const_cast<unsigned char*>(code_0068867e)); // original0x00651b4e
            table->entries[25] = reinterpret_cast<D3dxCodeAddress>(
                const_cast<unsigned char*>(code_00685292)); // original0x00651b58
        }
    }
    if (flags & 0x40) {
        table->entries[63] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00684900)); // original0x00651b63
        table->entries[64] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_006849a0)); // original0x00651b6d
        table->entries[65] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00684cc0)); // original0x00651b77
        table->entries[60] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00684280)); // original0x00651b81
        table->entries[61] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_006844e0)); // original0x00651b8b
        table->entries[62] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00684740)); // original0x00651b95
        table->entries[66] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_006841c0)); // original0x00651b9f
        table->entries[69] = reinterpret_cast<D3dxCodeAddress>(
            const_cast<unsigned char*>(code_00684100)); // original0x00651ba9
    }
    return result; // Actual EDX:EAX survives the pointer writes unchanged.
}
