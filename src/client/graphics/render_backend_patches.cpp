#include "graphics/render_backend_patches.h"

// Original code-address relocations only; unknown formal parameter types
// are not invented, and none of these entries are called by these patchers.
extern "C" {
extern const unsigned char code_00680048[] __asm__("_FUN_00680048@12");
extern const unsigned char code_006800c3[] __asm__("_FUN_006800c3@8");
extern const unsigned char code_0068015f[] __asm__("_FUN_0068015f@8");
extern const unsigned char code_006801e3[] __asm__("_FUN_006801e3@16");
extern const unsigned char code_006802a2[] __asm__("_FUN_006802a2@8");
extern const unsigned char code_006803ce[] __asm__("_FUN_006803ce@12");
extern const unsigned char code_0068040e[] __asm__("_FUN_0068040e@12");
extern const unsigned char code_00680467[] __asm__("_FUN_00680467@12");
extern const unsigned char code_006804a0[] __asm__("_FUN_006804a0@12");
extern const unsigned char code_006805d6[] __asm__("_FUN_006805d6@8");
extern const unsigned char code_0068066a[] __asm__("_FUN_0068066a@8");
extern const unsigned char code_0068070c[] __asm__("_FUN_0068070c@12");
extern const unsigned char code_006809b8[] __asm__("_FUN_006809b8@16");
extern const unsigned char code_00680a79[] __asm__("_FUN_00680a79@8");
extern const unsigned char code_00680b15[] __asm__("_FUN_00680b15@24");
extern const unsigned char code_00680bc9[] __asm__("_FUN_00680bc9@24");
extern const unsigned char code_00680c50[] __asm__("_FUN_00680c50@24");
extern const unsigned char code_00680cf7[] __asm__("_FUN_00680cf7@24");
extern const unsigned char code_00680dac[] __asm__("_FUN_00680dac@24");
extern const unsigned char code_00680e48[] __asm__("_FUN_00680e48@24");
extern const unsigned char code_00680ed0[] __asm__("_FUN_00680ed0@24");
extern const unsigned char code_00680f2c[] __asm__("_FUN_00680f2c@24");
extern const unsigned char code_00680f74[] __asm__("_FUN_00680f74@24");
extern const unsigned char code_00680fc5[] __asm__("_FUN_00680fc5@16");
extern const unsigned char code_00681075[] __asm__("_FUN_00681075@16");
extern const unsigned char code_00681161[] __asm__("_FUN_00681161@12");
extern const unsigned char code_00681259[] __asm__("_FUN_00681259@8");
extern const unsigned char code_00681331[] __asm__("_FUN_00681331@32");
extern const unsigned char code_006818a9[] __asm__("_FUN_006818a9@12");
extern const unsigned char code_00681975[] __asm__("_FUN_00681975@12");
extern const unsigned char code_00681bcf[] __asm__("_FUN_00681bcf@24");
extern const unsigned char code_00681da2[] __asm__("_FUN_00681da2@24");
extern const unsigned char code_00681f22[] __asm__("_FUN_00681f22@24");
extern const unsigned char code_0068207e[] __asm__("_FUN_0068207e@24");
extern const unsigned char code_0068218f[] __asm__("_FUN_0068218f@24");
extern const unsigned char code_0068238f[] __asm__("_FUN_0068238f@24");
extern const unsigned char code_00682543[] __asm__("_FUN_00682543@24");
extern const unsigned char code_00682871[] __asm__("_FUN_00682871@12");
extern const unsigned char code_00682947[] __asm__("_FUN_00682947@24");
extern const unsigned char code_00682b1a[] __asm__("_FUN_00682b1a@24");
extern const unsigned char code_00682c9a[] __asm__("_FUN_00682c9a@24");
extern const unsigned char code_00682df6[] __asm__("_FUN_00682df6@24");
extern const unsigned char code_00682f07[] __asm__("_FUN_00682f07@24");
extern const unsigned char code_00683107[] __asm__("_FUN_00683107@24");
extern const unsigned char code_006832bb[] __asm__("_FUN_006832bb@24");
extern const unsigned char code_006835b2[] __asm__("_FUN_006835b2@12");
extern const unsigned char code_00683686[] __asm__("_FUN_00683686@12");
extern const unsigned char code_00683746[] __asm__("_FUN_00683746@8");
extern const unsigned char code_006837da[] __asm__("_FUN_006837da@8");
extern const unsigned char code_0068387c[] __asm__("_FUN_0068387c@12");
extern const unsigned char code_006839c4[] __asm__("_FUN_006839c4@16");
extern const unsigned char code_00683a85[] __asm__("_FUN_00683a85@4");
extern const unsigned char code_00683b5d[] __asm__("_FUN_00683b5d@16");
extern const unsigned char code_00683c49[] __asm__("_FUN_00683c49@12");
extern const unsigned char code_00683d41[] __asm__("_FUN_00683d41@8");
extern const unsigned char code_00683e19[] __asm__("_FUN_00683e19@12");
extern const unsigned char code_00683ee0[] __asm__("_FUN_00683ee0@16");
extern const unsigned char code_00683f9f[] __asm__("_FUN_00683f9f@8");
}

extern "C" D3dxDispatchTable* __cdecl FUN_0065155d(D3dxDispatchTable* table) {
    table->entries[2] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00683686)); // original0x0065156a
    table->entries[35] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00683686)); // original0x0065156d
    table->entries[0] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_006803ce)); // original0x00651578
    table->entries[1] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00683e19)); // original0x0065157e
    table->entries[3] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_006804a0)); // original0x00651585
    table->entries[4] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0068387c)); // original0x0065158c
    table->entries[5] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680467)); // original0x00651593
    table->entries[6] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_006818a9)); // original0x0065159a
    table->entries[9] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0068040e)); // original0x006515a1
    table->entries[10] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00681975)); // original0x006515a8
    table->entries[7] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_006805d6)); // original0x006515af
    table->entries[8] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680a79)); // original0x006515b6
    table->entries[22] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0068066a)); // original0x006515bd
    table->entries[17] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_006809b8)); // original0x006515c4
    table->entries[21] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_006800c3)); // original0x006515cb
    table->entries[20] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680048)); // original0x006515d2
    table->entries[25] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_006802a2)); // original0x006515d9
    table->entries[26] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_006801e3)); // original0x006515e0
    table->entries[23] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680fc5)); // original0x006515e7
    table->entries[19] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0068070c)); // original0x006515ee
    table->entries[50] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680cf7)); // original0x006515f5
    table->entries[51] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680b15)); // original0x006515ff
    table->entries[52] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680ed0)); // original0x00651609
    table->entries[53] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680dac)); // original0x00651613
    table->entries[54] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680c50)); // original0x0065161d
    table->entries[55] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680f2c)); // original0x00651627
    table->entries[18] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680e48)); // original0x00651631
    table->entries[48] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680bc9)); // original0x00651638
    table->entries[49] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680f74)); // original0x00651642
    table->entries[11] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00683a85)); // original0x0065164c
    table->entries[28] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00681161)); // original0x00651653
    table->entries[14] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00681075)); // original0x0065165a
    table->entries[29] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00681259)); // original0x00651661
    table->entries[59] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00682871)); // original0x00651668
    table->entries[60] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00681da2)); // original0x00651672
    table->entries[61] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00681f22)); // original0x0065167c
    table->entries[62] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0068207e)); // original0x00651686
    table->entries[63] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00681bcf)); // original0x00651690
    table->entries[64] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00682543)); // original0x0065169a
    table->entries[65] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0068238f)); // original0x006516a4
    table->entries[66] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0068218f)); // original0x006516ae
    table->entries[69] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0068218f)); // original0x006516b4
    table->entries[71] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00681331)); // original0x006516ba
    table->entries[45] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0068015f)); // original0x006516c4
    return table;                                   // Actual EAX retains the incoming pointer.
}

extern "C" D3dxDispatchTable* __cdecl FUN_006516d0(D3dxDispatchTable* table) {
    table->entries[2] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00683686)); // original0x006516dd
    table->entries[35] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00683686)); // original0x006516e0
    table->entries[0] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_006803ce)); // original0x006516eb
    table->entries[1] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00683e19)); // original0x006516f1
    table->entries[3] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_006804a0)); // original0x006516f8
    table->entries[4] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0068387c)); // original0x006516ff
    table->entries[5] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680467)); // original0x00651706
    table->entries[6] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_006818a9)); // original0x0065170d
    table->entries[9] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0068040e)); // original0x00651714
    table->entries[10] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00681975)); // original0x0065171b
    table->entries[7] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00683746)); // original0x00651722
    table->entries[8] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680a79)); // original0x00651729
    table->entries[22] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_006837da)); // original0x00651730
    table->entries[17] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_006839c4)); // original0x00651737
    table->entries[21] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_006800c3)); // original0x0065173e
    table->entries[20] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680048)); // original0x00651745
    table->entries[25] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00683f9f)); // original0x0065174c
    table->entries[26] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00683ee0)); // original0x00651753
    table->entries[23] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680fc5)); // original0x0065175a
    table->entries[19] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_0068070c)); // original0x00651761
    table->entries[50] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680cf7)); // original0x00651768
    table->entries[51] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680b15)); // original0x00651772
    table->entries[52] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680ed0)); // original0x0065177c
    table->entries[53] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680dac)); // original0x00651786
    table->entries[54] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680c50)); // original0x00651790
    table->entries[55] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680f2c)); // original0x0065179a
    table->entries[18] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680e48)); // original0x006517a4
    table->entries[48] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680bc9)); // original0x006517ab
    table->entries[49] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00680f74)); // original0x006517b5
    table->entries[11] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00683a85)); // original0x006517bf
    table->entries[28] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00683c49)); // original0x006517c6
    table->entries[14] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00683b5d)); // original0x006517cd
    table->entries[29] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00683d41)); // original0x006517d4
    table->entries[59] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_006835b2)); // original0x006517db
    table->entries[60] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00682b1a)); // original0x006517e5
    table->entries[61] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00682c9a)); // original0x006517ef
    table->entries[62] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00682df6)); // original0x006517f9
    table->entries[63] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00682947)); // original0x00651803
    table->entries[64] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_006832bb)); // original0x0065180d
    table->entries[65] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00683107)); // original0x00651817
    table->entries[66] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00682f07)); // original0x00651821
    table->entries[69] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00682f07)); // original0x00651827
    table->entries[71] = reinterpret_cast<D3dxCodeAddress>(
        const_cast<unsigned char*>(code_00681331)); // original0x0065182d
    return table;                                   // Actual EAX retains the incoming pointer.
}
