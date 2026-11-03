#include <stdint.h>
#include <stddef.h>
static_assert(sizeof(void*) == 4);
using OriginalSessionCodeAddress = void (*)();
struct OriginalSessionVtableStorage {
    uint32_t observed_preceding_zero;
    OriginalSessionCodeAddress slots[398];
};
static_assert(offsetof(OriginalSessionVtableStorage, slots) == 4);
static_assert(sizeof(OriginalSessionVtableStorage) == 1596);
extern "C" {
void session_original_target_0040b1f0() __asm__("_FUN_0040b1f0");
void session_original_target_0040a770() __asm__("_FUN_0040a770");
void session_original_target_0040a780() __asm__("_FUN_0040a780");
void session_original_target_0040a790() __asm__("_FUN_0040a790");
void session_original_target_0051e1b0() __asm__("_FUN_0051e1b0");
void session_original_target_0055f7e0() __asm__("_FUN_0055f7e0");
void session_original_target_0055f7f0() __asm__("_fun_0055f7f0");
void session_original_target_0055f810() __asm__("_FUN_0055f810");
void session_original_target_0055f890() __asm__("_FUN_0055f890");
void session_original_target_0055f960() __asm__("_FUN_0055f960");
void session_original_target_0055f9e0() __asm__("_FUN_0055f9e0");
void session_original_target_0055fa80() __asm__("_FUN_0055fa80");
void session_original_target_0055fa90() __asm__("_FUN_0055fa90");
void session_original_target_0055fb30() __asm__("_FUN_0055fb30");
void session_original_target_0055fbc0() __asm__("_FUN_0055fbc0");
void session_original_target_0055fbd0() __asm__("_FUN_0055fbd0");
void session_original_target_0055fc00() __asm__("_FUN_0055fc00");
void session_original_target_0055fc50() __asm__("_FUN_0055fc50");
void session_original_target_0055fc70() __asm__("_FUN_0055fc70");
void session_original_target_0055fc90() __asm__("_FUN_0055fc90");
void session_original_target_0055fd30() __asm__("_FUN_0055fd30");
void session_original_target_0055fd60() __asm__("_FUN_0055fd60");
void session_original_target_0055fee0() __asm__("_FUN_0055fee0");
void session_original_target_0055ff20() __asm__("_FUN_0055ff20");
void session_original_target_0055ff40() __asm__("_FUN_0055ff40");
void session_original_target_0055ff60() __asm__("_FUN_0055ff60");
void session_original_target_00560130() __asm__("_FUN_00560130");
void session_original_target_005602d0() __asm__("_FUN_005602d0");
void session_original_target_005603d0() __asm__("_FUN_005603d0");
void session_original_target_005604c0() __asm__("_FUN_005604c0");
void session_original_target_00560500() __asm__("_FUN_00560500");
void session_original_target_00560600() __asm__("_FUN_00560600");
void session_original_target_00560680() __asm__("_FUN_00560680");
void session_original_target_005606f0() __asm__("_FUN_005606f0");
void session_original_target_00560710() __asm__("_FUN_00560710");
void session_original_target_00560750() __asm__("_FUN_00560750");
void session_original_target_00560790() __asm__("_FUN_00560790");
void session_original_target_00560880() __asm__("_FUN_00560880");
void session_original_target_00560d50() __asm__("_FUN_00560d50");
void session_original_target_00560da0() __asm__("_FUN_00560da0");
void session_original_target_00560e00() __asm__("_FUN_00560e00");
void session_original_target_00560e30() __asm__("_FUN_00560e30");
void session_original_target_00561220() __asm__("_FUN_00561220");
void session_original_target_00561250() __asm__("_FUN_00561250");
void session_original_target_00561300() __asm__("_FUN_00561300");
void session_original_target_00561310() __asm__("_FUN_00561310");
void session_original_target_00561580() __asm__("_FUN_00561580");
void session_original_target_00561800() __asm__("_FUN_00561800");
void session_original_target_00561880() __asm__("_FUN_00561880");
void session_original_target_00561950() __asm__("_FUN_00561950");
void session_original_target_005619b0() __asm__("_FUN_005619b0");
void session_original_target_00561a00() __asm__("_FUN_00561a00");
void session_original_target_00561a40() __asm__("_FUN_00561a40");
void session_original_target_00561a70() __asm__("_FUN_00561a70");
void session_original_target_00561a90() __asm__("_FUN_00561a90");
void session_original_target_00561cc0() __asm__("_FUN_00561cc0");
void session_original_target_00561d10() __asm__("_FUN_00561d10");
void session_original_target_00561d40() __asm__("_FUN_00561d40");
void session_original_target_00561d70() __asm__("_FUN_00561d70");
void session_original_target_00561d80() __asm__("_FUN_00561d80");
void session_original_target_00561d90() __asm__("_FUN_00561d90");
void session_original_target_00561df0() __asm__("_FUN_00561df0");
void session_original_target_00561e20() __asm__("_FUN_00561e20");
void session_original_target_00561e50() __asm__("_FUN_00561e50");
void session_original_target_00561f20() __asm__("_FUN_00561f20");
void session_original_target_00562070() __asm__("_FUN_00562070");
void session_original_target_005621f0() __asm__("_FUN_005621f0");
void session_original_target_00562200() __asm__("_FUN_00562200");
void session_original_target_00562210() __asm__("_FUN_00562210");
void session_original_target_00562240() __asm__("_FUN_00562240");
void session_original_target_00562350() __asm__("_FUN_00562350");
void session_original_target_00562440() __asm__("_FUN_00562440");
void session_original_target_005624a0() __asm__("_FUN_005624a0");
void session_original_target_005624c0() __asm__("_FUN_005624c0");
void session_original_target_00562540() __asm__("_FUN_00562540");
void session_original_target_005625f0() __asm__("_FUN_005625f0");
void session_original_target_005626c0() __asm__("_FUN_005626c0");
void session_original_target_00562820() __asm__("_FUN_00562820");
void session_original_target_00562890() __asm__("_FUN_00562890");
void session_original_target_005628d0() __asm__("_FUN_005628d0");
void session_original_target_00562900() __asm__("_FUN_00562900");
void session_original_target_00562930() __asm__("_FUN_00562930");
void session_original_target_00562960() __asm__("_FUN_00562960");
void session_original_target_00562af0() __asm__("_FUN_00562af0");
void session_original_target_00562b10() __asm__("_FUN_00562b10");
void session_original_target_00562b20() __asm__("_FUN_00562b20");
void session_original_target_00562b40() __asm__("_FUN_00562b40");
void session_original_target_00562cd0() __asm__("_FUN_00562cd0");
void session_original_target_00562dd0() __asm__("_FUN_00562dd0");
void session_original_target_00562ee0() __asm__("_FUN_00562ee0");
void session_original_target_00562f00() __asm__("_FUN_00562f00");
void session_original_target_00562f10() __asm__("_FUN_00562f10");
void session_original_target_00562f30() __asm__("_FUN_00562f30");
void session_original_target_00562f50() __asm__("_FUN_00562f50");
void session_original_target_00562fa0() __asm__("_FUN_00562fa0");
void session_original_target_00562fc0() __asm__("_FUN_00562fc0");
void session_original_target_005630c0() __asm__("_FUN_005630c0");
void session_original_target_005631d0() __asm__("_FUN_005631d0");
void session_original_target_00563250() __asm__("_FUN_00563250");
void session_original_target_00563430() __asm__("_FUN_00563430");
void session_original_target_00563460() __asm__("_FUN_00563460");
void session_original_target_00563560() __asm__("_FUN_00563560");
void session_original_target_00563650() __asm__("_FUN_00563650");
void session_original_target_00563700() __asm__("_FUN_00563700");
void session_original_target_00563980() __asm__("_FUN_00563980");
void session_original_target_00563e20() __asm__("_FUN_00563e20");
void session_original_target_005641f0() __asm__("_FUN_005641f0");
void session_original_target_005642b0() __asm__("_FUN_005642b0");
void session_original_target_00564440() __asm__("_FUN_00564440");
void session_original_target_00564690() __asm__("_FUN_00564690");
void session_original_target_00564840() __asm__("_FUN_00564840");
void session_original_target_00564d40() __asm__("_FUN_00564d40");
void session_original_target_00564e50() __asm__("_FUN_00564e50");
void session_original_target_00564f20() __asm__("_FUN_00564f20");
void session_original_target_00565010() __asm__("_FUN_00565010");
void session_original_target_005651d0() __asm__("_FUN_005651d0");
void session_original_target_005655f0() __asm__("_FUN_005655f0");
void session_original_target_00565790() __asm__("_FUN_00565790");
void session_original_target_005659a0() __asm__("_FUN_005659a0");
void session_original_target_00565b10() __asm__("_FUN_00565b10");
void session_original_target_00565eb0() __asm__("_FUN_00565eb0");
void session_original_target_005665e0() __asm__("_FUN_005665e0");
void session_original_target_00566770() __asm__("_FUN_00566770");
void session_original_target_005667a0() __asm__("_FUN_005667a0");
void session_original_target_00566c30() __asm__("_FUN_00566c30");
void session_original_target_00566d60() __asm__("_FUN_00566d60");
void session_original_target_00566da0() __asm__("_FUN_00566da0");
void session_original_target_00566e20() __asm__("_FUN_00566e20");
void session_original_target_00566e60() __asm__("_FUN_00566e60");
void session_original_target_00566e80() __asm__("_FUN_00566e80");
void session_original_target_00566eb0() __asm__("_FUN_00566eb0");
void session_original_target_00566ed0() __asm__("_FUN_00566ed0");
void session_original_target_00566f10() __asm__("_FUN_00566f10");
void session_original_target_00566f40() __asm__("_FUN_00566f40");
void session_original_target_00566f90() __asm__("_FUN_00566f90");
void session_original_target_00567030() __asm__("_FUN_00567030");
void session_original_target_00567040() __asm__("_FUN_00567040");
void session_original_target_00567050() __asm__("_FUN_00567050");
void session_original_target_00567060() __asm__("_FUN_00567060");
void session_original_target_00567070() __asm__("_FUN_00567070");
void session_original_target_00567400() __asm__("_FUN_00567400");
void session_original_target_00567510() __asm__("_FUN_00567510");
void session_original_target_00567550() __asm__("_FUN_00567550");
void session_original_target_005675a0() __asm__("_FUN_005675a0");
void session_original_target_00567740() __asm__("_FUN_00567740");
void session_original_target_00567780() __asm__("_FUN_00567780");
void session_original_target_005678f0() __asm__("_FUN_005678f0");
void session_original_target_00567910() __asm__("_FUN_00567910");
void session_original_target_00567940() __asm__("_FUN_00567940");
void session_original_target_00567960() __asm__("_FUN_00567960");
void session_original_target_00567980() __asm__("_FUN_00567980");
void session_original_target_005679b0() __asm__("_FUN_005679b0");
void session_original_target_00567b00() __asm__("_FUN_00567b00");
void session_original_target_00567c30() __asm__("_FUN_00567c30");
void session_original_target_00567d60() __asm__("_FUN_00567d60");
void session_original_target_005680c0() __asm__("_FUN_005680c0");
void session_original_target_00568140() __asm__("_FUN_00568140");
void session_original_target_00568220() __asm__("_FUN_00568220");
void session_original_target_005686d0() __asm__("_FUN_005686d0");
void session_original_target_005689d0() __asm__("_FUN_005689d0");
void session_original_target_00568ab0() __asm__("_FUN_00568ab0");
void session_original_target_00568ad0() __asm__("_FUN_00568ad0");
void session_original_target_00568b00() __asm__("_FUN_00568b00");
void session_original_target_00568b90() __asm__("_FUN_00568b90");
void session_original_target_00568bb0() __asm__("_FUN_00568bb0");
void session_original_target_00568bc0() __asm__("_FUN_00568bc0");
void session_original_target_00568be0() __asm__("_FUN_00568be0");
void session_original_target_00568c10() __asm__("_FUN_00568c10");
void session_original_target_00568c30() __asm__("_FUN_00568c30");
void session_original_target_00568c40() __asm__("_FUN_00568c40");
void session_original_target_00568c60() __asm__("_FUN_00568c60");
void session_original_target_00568c90() __asm__("_FUN_00568c90");
void session_original_target_00568ca0() __asm__("_FUN_00568ca0");
void session_original_target_00568cb0() __asm__("_FUN_00568cb0");
void session_original_target_00568cf0() __asm__("_FUN_00568cf0");
void session_original_target_00568d20() __asm__("_FUN_00568d20");
void session_original_target_00568e20() __asm__("_FUN_00568e20");
void session_original_target_00568e30() __asm__("_FUN_00568e30");
void session_original_target_00568e70() __asm__("_FUN_00568e70");
void session_original_target_00568f10() __asm__("_FUN_00568f10");
void session_original_target_00568fb0() __asm__("_FUN_00568fb0");
void session_original_target_00569050() __asm__("_FUN_00569050");
void session_original_target_00569140() __asm__("_FUN_00569140");
void session_original_target_00569190() __asm__("_FUN_00569190");
void session_original_target_00569210() __asm__("_FUN_00569210");
void session_original_target_00569270() __asm__("_FUN_00569270");
void session_original_target_00569280() __asm__("_FUN_00569280");
void session_original_target_005692f0() __asm__("_FUN_005692f0");
void session_original_target_00569320() __asm__("_FUN_00569320");
void session_original_target_00569360() __asm__("_FUN_00569360");
void session_original_target_005693c0() __asm__("_FUN_005693c0");
void session_original_target_005693d0() __asm__("_FUN_005693d0");
void session_original_target_00569400() __asm__("_FUN_00569400");
void session_original_target_00569420() __asm__("_FUN_00569420");
void session_original_target_00569480() __asm__("_FUN_00569480");
void session_original_target_005694d0() __asm__("_FUN_005694d0");
void session_original_target_005694e0() __asm__("_FUN_005694e0");
void session_original_target_00569510() __asm__("_FUN_00569510");
void session_original_target_00569540() __asm__("_FUN_00569540");
void session_original_target_005695b0() __asm__("_FUN_005695b0");
void session_original_target_005695e0() __asm__("_FUN_005695e0");
void session_original_target_005696a0() __asm__("_FUN_005696a0");
void session_original_target_005696c0() __asm__("_FUN_005696c0");
void session_original_target_00569790() __asm__("_FUN_00569790");
void session_original_target_00569880() __asm__("_FUN_00569880");
void session_original_target_00569890() __asm__("_FUN_00569890");
void session_original_target_005698f0() __asm__("_FUN_005698f0");
void session_original_target_005699e0() __asm__("_FUN_005699e0");
void session_original_target_00569ba0() __asm__("_FUN_00569ba0");
void session_original_target_00569d80() __asm__("_FUN_00569d80");
void session_original_target_00569e80() __asm__("_FUN_00569e80");
void session_original_target_00569f70() __asm__("_FUN_00569f70");
void session_original_target_0056a060() __asm__("_FUN_0056a060");
void session_original_target_0056a070() __asm__("_FUN_0056a070");
void session_original_target_0056a0d0() __asm__("_FUN_0056a0d0");
void session_original_target_0056a1f0() __asm__("_FUN_0056a1f0");
void session_original_target_0056a330() __asm__("_FUN_0056a330");
void session_original_target_0056a3e0() __asm__("_FUN_0056a3e0");
void session_original_target_0056a4d0() __asm__("_FUN_0056a4d0");
void session_original_target_0056a6f0() __asm__("_FUN_0056a6f0");
void session_original_target_0056a9b0() __asm__("_FUN_0056a9b0");
void session_original_target_0056aab0() __asm__("_FUN_0056aab0");
void session_original_target_0056ab30() __asm__("_FUN_0056ab30");
void session_original_target_0056aba0() __asm__("_FUN_0056aba0");
void session_original_target_0056acc0() __asm__("_FUN_0056acc0");
void session_original_target_0056ad80() __asm__("_FUN_0056ad80");
void session_original_target_0056aff0() __asm__("_FUN_0056aff0");
void session_original_target_0056b1a0() __asm__("_FUN_0056b1a0");
void session_original_target_0056b1b0() __asm__("_FUN_0056b1b0");
void session_original_target_0056b230() __asm__("_FUN_0056b230");
void session_original_target_0056b820() __asm__("_FUN_0056b820");
void session_original_target_0056b840() __asm__("_FUN_0056b840");
void session_original_target_0056b8d0() __asm__("_FUN_0056b8d0");
void session_original_target_0056b910() __asm__("_FUN_0056b910");
void session_original_target_0056ba20() __asm__("_FUN_0056ba20");
void session_original_target_0056bb10() __asm__("_FUN_0056bb10");
void session_original_target_0056bc30() __asm__("_FUN_0056bc30");
void session_original_target_0056bc40() __asm__("_FUN_0056bc40");
void session_original_target_0056bd00() __asm__("_FUN_0056bd00");
void session_original_target_0056be20() __asm__("_FUN_0056be20");
void session_original_target_0056bf10() __asm__("_FUN_0056bf10");
void session_original_target_0056c010() __asm__("_FUN_0056c010");
void session_original_target_0056c0d0() __asm__("_FUN_0056c0d0");
void session_original_target_0056c2b0() __asm__("_FUN_0056c2b0");
void session_original_target_0056c4b0() __asm__("_FUN_0056c4b0");
void session_original_target_0056c6d0() __asm__("_FUN_0056c6d0");
void session_original_target_0056c920() __asm__("_FUN_0056c920");
void session_original_target_0056c990() __asm__("_FUN_0056c990");
void session_original_target_0056ca10() __asm__("_FUN_0056ca10");
void session_original_target_0056cba0() __asm__("_FUN_0056cba0");
void session_original_target_0056cc00() __asm__("_FUN_0056cc00");
void session_original_target_0056cc60() __asm__("_FUN_0056cc60");
void session_original_target_0056ccb0() __asm__("_FUN_0056ccb0");
void session_original_target_0056ccf0() __asm__("_FUN_0056ccf0");
void session_original_target_0056cd50() __asm__("_FUN_0056cd50");
void session_original_target_0056cdf0() __asm__("_FUN_0056cdf0");
void session_original_target_0056ce80() __asm__("_FUN_0056ce80");
void session_original_target_0056ceb0() __asm__("_FUN_0056ceb0");
void session_original_target_0056cf00() __asm__("_FUN_0056cf00");
void session_original_target_0056cf60() __asm__("_FUN_0056cf60");
void session_original_target_0056cf70() __asm__("_FUN_0056cf70");
void session_original_target_0056cfa0() __asm__("_FUN_0056cfa0");
void session_original_target_0056cfd0() __asm__("_FUN_0056cfd0");
void session_original_target_0056d010() __asm__("_FUN_0056d010");
void session_original_target_0056d030() __asm__("_FUN_0056d030");
void session_original_target_0056d050() __asm__("_FUN_0056d050");
void session_original_target_0056d1e0() __asm__("_FUN_0056d1e0");
void session_original_target_0056d200() __asm__("_FUN_0056d200");
void session_original_target_0056d210() __asm__("_FUN_0056d210");
void session_original_target_0056d2d0() __asm__("_FUN_0056d2d0");
void session_original_target_0056d2e0() __asm__("_FUN_0056d2e0");
void session_original_target_0056d490() __asm__("_FUN_0056d490");
void session_original_target_0056d4c0() __asm__("_fun_0056d4c0");
void session_original_target_0056d4f0() __asm__("_FUN_0056d4f0");
void session_original_target_0056d5b0() __asm__("_fun_0056d5b0");
void session_original_target_0056d5e0() __asm__("_FUN_0056d5e0");
void session_original_target_0056d6a0() __asm__("_FUN_0056d6a0");
void session_original_target_0056d760() __asm__("_FUN_0056d760");
void session_original_target_0056d780() __asm__("_FUN_0056d780");
void session_original_target_0056db90() __asm__("_FUN_0056db90");
void session_original_target_0056dda0() __asm__("_FUN_0056dda0");
void session_original_target_0056def0() __asm__("_FUN_0056def0");
void session_original_target_0056dfe0() __asm__("_FUN_0056dfe0");
void session_original_target_0056e060() __asm__("_FUN_0056e060");
void session_original_target_0056e170() __asm__("_FUN_0056e170");
void session_original_target_0056e2f0() __asm__("_FUN_0056e2f0");
void session_original_target_0056e300() __asm__("_FUN_0056e300");
void session_original_target_0056e4b0() __asm__("_FUN_0056e4b0");
void session_original_target_0056e640() __asm__("_FUN_0056e640");
void session_original_target_0056ea70() __asm__("_FUN_0056ea70");
void session_original_target_0056ec90() __asm__("_FUN_0056ec90");
void session_original_target_0056ee70() __asm__("_FUN_0056ee70");
void session_original_target_0056f630() __asm__("_FUN_0056f630");
void session_original_target_0056f760() __asm__("_FUN_0056f760");
void session_original_target_0056f8f0() __asm__("_FUN_0056f8f0");
void session_original_target_00570a60() __asm__("_fun_00570a60");
void session_original_target_00570ad0() __asm__("_fun_00570ad0");
void session_original_target_00570b30() __asm__("_fun_00570b30");
void session_original_target_00570bc0() __asm__("_FUN_00570bc0");
void session_original_target_00570c60() __asm__("_FUN_00570c60");
void session_original_target_00570c90() __asm__("_fun_00570c90");
void session_original_target_00570cf0() __asm__("_FUN_00570cf0");
void session_original_target_00570ff0() __asm__("_FUN_00570ff0");
void session_original_target_005712d0() __asm__("_fun_005712d0");
void session_original_target_005712f0() __asm__("_fun_005712f0");
void session_original_target_00571360() __asm__("_FUN_00571360");
void session_original_target_00572ce0() __asm__("_FUN_00572ce0");
void session_original_target_00572d70() __asm__("_FUN_00572d70");
void session_original_target_00572e40() __asm__("_FUN_00572e40");
void session_original_target_00572eb0() __asm__("_FUN_00572eb0");
void session_original_target_00572ec0() __asm__("_FUN_00572ec0");
void session_original_target_00572f00() __asm__("_FUN_00572f00");
void session_original_target_00572f50() __asm__("_FUN_00572f50");
void session_original_target_00572f90() __asm__("_FUN_00572f90");
void session_original_target_00573000() __asm__("_FUN_00573000");
void session_original_target_00573080() __asm__("_FUN_00573080");
void session_original_target_00573160() __asm__("_FUN_00573160");
void session_original_target_005731f0() __asm__("_FUN_005731f0");
void session_original_target_00573260() __asm__("_FUN_00573260");
void session_original_target_00573300() __asm__("_FUN_00573300");
void session_original_target_005733e0() __asm__("_FUN_005733e0");
void session_original_target_005734d0() __asm__("_FUN_005734d0");
void session_original_target_00573580() __asm__("_FUN_00573580");
void session_original_target_00573630() __asm__("_FUN_00573630");
void session_original_target_005736f0() __asm__("_FUN_005736f0");
void session_original_target_00573780() __asm__("_FUN_00573780");
void session_original_target_00573970() __asm__("_FUN_00573970");
void session_original_target_00573a40() __asm__("_FUN_00573a40");
void session_original_target_00573b50() __asm__("_FUN_00573b50");
void session_original_target_00573d00() __asm__("_FUN_00573d00");
void session_original_target_00573e50() __asm__("_FUN_00573e50");
void session_original_target_00573f20() __asm__("_FUN_00573f20");
void session_original_target_00574010() __asm__("_FUN_00574010");
void session_original_target_00574080() __asm__("_FUN_00574080");
void session_original_target_005741a0() __asm__("_FUN_005741a0");
void session_original_target_00574220() __asm__("_FUN_00574220");
void session_original_target_00574560() __asm__("_FUN_00574560");
void session_original_target_005747b0() __asm__("_FUN_005747b0");
void session_original_target_005749d0() __asm__("_FUN_005749d0");
void session_original_target_00574dc0() __asm__("_FUN_00574dc0");
void session_original_target_005752f0() __asm__("_FUN_005752f0");
void session_original_target_00575570() __asm__("_FUN_00575570");
void session_original_target_005757f0() __asm__("_FUN_005757f0");
void session_original_target_00575810() __asm__("_FUN_00575810");
void session_original_target_00575a40() __asm__("_FUN_00575a40");
void session_original_target_00575b30() __asm__("_fun_00575b30");
void session_original_target_00575bc0() __asm__("_FUN_00575bc0");
void session_original_target_00575df0() __asm__("_FUN_00575df0");
void session_original_target_00577b90() __asm__("_FUN_00577b90");
void session_original_target_00577f30() __asm__("_FUN_00577f30");
void session_original_target_005780a0() __asm__("_FUN_005780a0");
void session_original_target_00578390() __asm__("_FUN_00578390");
void session_original_target_005783d0() __asm__("_FUN_005783d0");
void session_original_target_00578d70() __asm__("_FUN_00578d70");
void session_original_target_005790f0() __asm__("_FUN_005790f0");
void session_original_target_005791f0() __asm__("_FUN_005791f0");
void session_original_target_00579390() __asm__("_FUN_00579390");
void session_original_target_005798a0() __asm__("_FUN_005798a0");
void session_original_target_00579aa0() __asm__("_FUN_00579aa0");
void session_original_target_00579b80() __asm__("_FUN_00579b80");
void session_original_target_0057a2c0() __asm__("_FUN_0057a2c0");
void session_original_target_0057a910() __asm__("_FUN_0057a910");
void session_original_target_0057ac10() __asm__("_FUN_0057ac10");
void session_original_target_0057ace0() __asm__("_FUN_0057ace0");
void session_original_target_0057adb0() __asm__("_FUN_0057adb0");
void session_original_target_0057adc0() __asm__("_FUN_0057adc0");
void session_original_target_0057add0() __asm__("_FUN_0057add0");
void session_original_target_0057b930() __asm__("_FUN_0057b930");
void session_original_target_0057bc30() __asm__("_FUN_0057bc30");
void session_original_target_0057bdc0() __asm__("_FUN_0057bdc0");
void session_original_target_0057db20() __asm__("_FUN_0057db20");
void session_original_target_0057e320() __asm__("_FUN_0057e320");
void session_original_target_0057fc40() __asm__("_FUN_0057fc40");
void session_original_target_00580610() __asm__("_FUN_00580610");
void session_original_target_00580700() __asm__("_FUN_00580700");
void session_original_target_00580880() __asm__("_FUN_00580880");
void session_original_target_00580a80() __asm__("_FUN_00580a80");
void session_original_target_005bfb50() __asm__("_FUN_005bfb50");
// Pointer declarations supply address bits only; native target contracts remain original.
// The preceding zero is observed storage, with no RTTI or allocation-schema inference.
extern const OriginalSessionVtableStorage original_session_vtable_storage = {
    0, {session_original_target_0055f7e0, session_original_target_0055f7f0,
        session_original_target_0055f890, session_original_target_0055f810,
        session_original_target_0055f960, session_original_target_0055f9e0,
        session_original_target_0055fd60, session_original_target_0055fee0,
        session_original_target_0055ff20, session_original_target_0055ff40,
        session_original_target_0055ff60, session_original_target_00560130,
        session_original_target_00580a80, session_original_target_00571360,
        session_original_target_00563650, session_original_target_0055fa80,
        session_original_target_0055fb30, session_original_target_0055fa90,
        session_original_target_0055fbd0, session_original_target_0055fbc0,
        session_original_target_0055fc00, session_original_target_0055ff20,
        session_original_target_0040a790, session_original_target_0055fc50,
        session_original_target_005651d0, session_original_target_005604c0,
        session_original_target_00563700, session_original_target_0056ad80,
        session_original_target_0056aff0, session_original_target_0056e640,
        session_original_target_0056ea70, session_original_target_00561880,
        session_original_target_00561800, session_original_target_00561950,
        session_original_target_0057bc30, session_original_target_00560e00,
        session_original_target_0055fd30, session_original_target_005621f0,
        session_original_target_00562200, session_original_target_00560500,
        session_original_target_00560600, session_original_target_0055fc70,
        session_original_target_0055fc90, session_original_target_005628d0,
        session_original_target_00562900, session_original_target_00562930,
        session_original_target_00560680, session_original_target_00560710,
        session_original_target_00560750, session_original_target_00560790,
        session_original_target_0051e1b0, session_original_target_0056ec90,
        session_original_target_0056b1a0, session_original_target_0051e1b0,
        session_original_target_00561a70, session_original_target_00561a90,
        session_original_target_00564840, session_original_target_00560880,
        session_original_target_00563980, session_original_target_00564d40,
        session_original_target_00560d50, session_original_target_00560da0,
        session_original_target_00560e30, session_original_target_0056b1b0,
        session_original_target_0056b230, session_original_target_00561580,
        session_original_target_0056ee70, session_original_target_0056b820,
        session_original_target_0056b840, session_original_target_0040a770,
        session_original_target_0040a770, session_original_target_0051e1b0,
        session_original_target_0040a780, session_original_target_0056bb10,
        session_original_target_0056bc30, session_original_target_005619b0,
        session_original_target_00561a00, session_original_target_005606f0,
        session_original_target_00580880, session_original_target_00580610,
        session_original_target_00577b90, session_original_target_005780a0,
        session_original_target_0057bdc0, session_original_target_00578390,
        session_original_target_0057db20, session_original_target_005783d0,
        session_original_target_00578d70, session_original_target_005790f0,
        session_original_target_005791f0, session_original_target_0057e320,
        session_original_target_0057fc40, session_original_target_00579390,
        session_original_target_005798a0, session_original_target_00579aa0,
        session_original_target_00562210, session_original_target_0057add0,
        session_original_target_00579b80, session_original_target_0057a2c0,
        session_original_target_0057a910, session_original_target_0057ac10,
        session_original_target_005655f0, session_original_target_00561220,
        session_original_target_00561250, session_original_target_00561300,
        session_original_target_00561310, session_original_target_00564e50,
        session_original_target_00561a40, session_original_target_00577f30,
        session_original_target_0056b8d0, session_original_target_0056b910,
        session_original_target_0056ba20, session_original_target_005602d0,
        session_original_target_005603d0, session_original_target_005642b0,
        session_original_target_0056c0d0, session_original_target_0056c4b0,
        session_original_target_0056c2b0, session_original_target_0056bc40,
        session_original_target_0056bd00, session_original_target_0056c010,
        session_original_target_0056be20, session_original_target_0056bf10,
        session_original_target_0056c6d0, session_original_target_00561cc0,
        session_original_target_00561d10, session_original_target_00575a40,
        session_original_target_00575b30, session_original_target_00575bc0,
        session_original_target_00575df0, session_original_target_00575810,
        session_original_target_005757f0, session_original_target_00580700,
        session_original_target_0057b930, session_original_target_00565790,
        session_original_target_00561d40, session_original_target_00561d70,
        session_original_target_00561d80, session_original_target_00563e20,
        session_original_target_00570a60, session_original_target_00570ad0,
        session_original_target_00570b30, session_original_target_00570bc0,
        session_original_target_00570c60, session_original_target_00570c90,
        session_original_target_00570ff0, session_original_target_00570cf0,
        session_original_target_005712d0, session_original_target_005712f0,
        session_original_target_00574220, session_original_target_00572ce0,
        session_original_target_00572d70, session_original_target_00574560,
        session_original_target_00573e50, session_original_target_00573f20,
        session_original_target_00573260, session_original_target_00573300,
        session_original_target_005733e0, session_original_target_005734d0,
        session_original_target_005747b0, session_original_target_00573b50,
        session_original_target_00573d00, session_original_target_00573630,
        session_original_target_00573580, session_original_target_005736f0,
        session_original_target_00573780, session_original_target_00572e40,
        session_original_target_00572eb0, session_original_target_0056c920,
        session_original_target_0056c990, session_original_target_0056ca10,
        session_original_target_0056cc60, session_original_target_0056ccb0,
        session_original_target_0056ccf0, session_original_target_0056cd50,
        session_original_target_0056cdf0, session_original_target_0056ce80,
        session_original_target_0056cba0, session_original_target_0056cc00,
        session_original_target_00561d90, session_original_target_00561df0,
        session_original_target_005659a0, session_original_target_00561e20,
        session_original_target_00561e50, session_original_target_0040a790,
        session_original_target_00561f20, session_original_target_00562070,
        session_original_target_005686d0, session_original_target_00567d60,
        session_original_target_00566e60, session_original_target_00566e80,
        session_original_target_0040a790, session_original_target_0040a790,
        session_original_target_00566c30, session_original_target_00566d60,
        session_original_target_00566da0, session_original_target_00566e20,
        session_original_target_005689d0, session_original_target_00566eb0,
        session_original_target_00568220, session_original_target_00566ed0,
        session_original_target_00566f10, session_original_target_00566f40,
        session_original_target_00566f90, session_original_target_005679b0,
        session_original_target_005680c0, session_original_target_00568140,
        session_original_target_00567b00, session_original_target_00567030,
        session_original_target_00567040, session_original_target_00567050,
        session_original_target_00567060, session_original_target_00567070,
        session_original_target_00567400, session_original_target_00567c30,
        session_original_target_00567c30, session_original_target_00567510,
        session_original_target_00567510, session_original_target_00567510,
        session_original_target_00567510, session_original_target_00567510,
        session_original_target_00567510, session_original_target_00567550,
        session_original_target_005675a0, session_original_target_005678f0,
        session_original_target_00567740, session_original_target_0040a790,
        session_original_target_0040a790, session_original_target_0040a790,
        session_original_target_0040a790, session_original_target_00567780,
        session_original_target_005678f0, session_original_target_00567740,
        session_original_target_00567910, session_original_target_00567940,
        session_original_target_00567960, session_original_target_0056e4b0,
        session_original_target_00568c60, session_original_target_005699e0,
        session_original_target_00568c90, session_original_target_0056a1f0,
        session_original_target_00568ca0, session_original_target_00568cb0,
        session_original_target_00568cf0, session_original_target_00568d20,
        session_original_target_0056a330, session_original_target_0056a3e0,
        session_original_target_00568e20, session_original_target_0056a4d0,
        session_original_target_0056a060, session_original_target_005bfb50,
        session_original_target_0056aab0, session_original_target_0056ab30,
        session_original_target_0056a9b0, session_original_target_00568e70,
        session_original_target_00568f10, session_original_target_00568fb0,
        session_original_target_00569050, session_original_target_00569140,
        session_original_target_00569190, session_original_target_00569210,
        session_original_target_00569270, session_original_target_00568e30,
        session_original_target_005665e0, session_original_target_00564f20,
        session_original_target_00562240, session_original_target_00562350,
        session_original_target_00568ab0, session_original_target_00568ad0,
        session_original_target_00568b00, session_original_target_00568b90,
        session_original_target_00568bb0, session_original_target_00568bc0,
        session_original_target_00568be0, session_original_target_00568c10,
        session_original_target_00568c30, session_original_target_00568c40,
        session_original_target_00562440, session_original_target_005624a0,
        session_original_target_00569280, session_original_target_005692f0,
        session_original_target_00569320, session_original_target_00569360,
        session_original_target_005693c0, session_original_target_005693d0,
        session_original_target_00569400, session_original_target_00569420,
        session_original_target_00569480, session_original_target_005694d0,
        session_original_target_005694e0, session_original_target_00569510,
        session_original_target_0056a6f0, session_original_target_00569540,
        session_original_target_005624c0, session_original_target_00562540,
        session_original_target_00565b10, session_original_target_0056ceb0,
        session_original_target_0056cf00, session_original_target_0056cf60,
        session_original_target_0056cf70, session_original_target_0056cfa0,
        session_original_target_0056cfd0, session_original_target_0056d010,
        session_original_target_0056d030, session_original_target_0056d050,
        session_original_target_0056d1e0, session_original_target_0056d200,
        session_original_target_0056d210, session_original_target_0056d2d0,
        session_original_target_0056d2e0, session_original_target_0056d490,
        session_original_target_005625f0, session_original_target_0057ace0,
        session_original_target_005626c0, session_original_target_00562820,
        session_original_target_00562890, session_original_target_00562960,
        session_original_target_00565010, session_original_target_00562af0,
        session_original_target_00562b10, session_original_target_00562b20,
        session_original_target_00562b40, session_original_target_00562cd0,
        session_original_target_00562dd0, session_original_target_00562ee0,
        session_original_target_00562f00, session_original_target_00566770,
        session_original_target_00562f10, session_original_target_00562f30,
        session_original_target_0056dfe0, session_original_target_0057adb0,
        session_original_target_0056e060, session_original_target_0056e170,
        session_original_target_00573970, session_original_target_00573a40,
        session_original_target_00572ec0, session_original_target_00567980,
        session_original_target_005749d0, session_original_target_00574010,
        session_original_target_00574080, session_original_target_00572f00,
        session_original_target_00572f50, session_original_target_00574dc0,
        session_original_target_00572f90, session_original_target_00573000,
        session_original_target_005741a0, session_original_target_00573080,
        session_original_target_00573160, session_original_target_005731f0,
        session_original_target_005752f0, session_original_target_00575570,
        session_original_target_0056d4c0, session_original_target_0056d4f0,
        session_original_target_0056d780, session_original_target_0056db90,
        session_original_target_0056dda0, session_original_target_0056def0,
        session_original_target_0056d5b0, session_original_target_0056d5e0,
        session_original_target_0056f630, session_original_target_0056d6a0,
        session_original_target_0056d760, session_original_target_00562f50,
        session_original_target_00562fa0, session_original_target_0056f8f0,
        session_original_target_0056f760, session_original_target_0056e2f0,
        session_original_target_0056e300, session_original_target_00562fc0,
        session_original_target_005630c0, session_original_target_005631d0,
        session_original_target_00563250, session_original_target_00564440,
        session_original_target_00569ba0, session_original_target_0056aba0,
        session_original_target_00569e80, session_original_target_00569790,
        session_original_target_0056acc0, session_original_target_0056a070,
        session_original_target_005698f0, session_original_target_00569880,
        session_original_target_00569f70, session_original_target_00569890,
        session_original_target_005696c0, session_original_target_005696a0,
        session_original_target_005695e0, session_original_target_005695b0,
        session_original_target_0056a0d0, session_original_target_00569d80,
        session_original_target_00563460, session_original_target_00563460,
        session_original_target_005641f0, session_original_target_00563560,
        session_original_target_00564690, session_original_target_00563430,
        session_original_target_0057adc0, session_original_target_00565eb0,
        session_original_target_005667a0, session_original_target_0040b1f0}};
}
__asm__(
    ".globl _dat_006bbd64\n.set _dat_006bbd64, _original_session_vtable_storage\n.globl _dat_006bbd68\n.set _dat_006bbd68, _original_session_vtable_storage+4");
