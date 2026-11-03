#include <stdint.h>
extern "C" {
struct ShaderScope {
    int32_t enclosing;
    const void* filter;
    const void* handler;
};
struct ShaderProfile {
    const char* name;
    uint32_t version, flags;
};
struct ShaderOpcode {
    const char* name;
    uint32_t opcode;
    uint32_t counts[15];
};
struct ShaderConditionOpcode {
    const char* name;
    uint32_t opcode;
    uint32_t counts[16];
};
struct ShaderRegister {
    const char* name;
    uint32_t type;
    uint32_t counts[15];
    uint32_t flags;
};
struct ShaderInterfaceId {
    uint32_t first;
    uint16_t second, third;
    uint8_t tail[8];
};
struct QualifiedLocale {
    uint32_t id;
    uint8_t id_text[8];
    const char* language;
    uint8_t language_abbr[4];
    const char* country;
    uint8_t country_abbr[4];
    uint8_t oem[8], ansi[8];
};
struct LocaleAlias {
    const char* name;
    uint8_t abbreviation[4];
};
struct LocaleId {
    uint16_t language, country, codepage;
};
struct LocaleCategoryAction {
    const char* name;
    const void* value;
    const void* initialize;
};
struct ShaderCriticalSection {
    void* debug_info;
    int32_t lock_count, recursion_count;
    void* owning_thread;
    void* semaphore;
    uint32_t spin_count;
};
extern const unsigned char code_ref_005d5889[] __asm__("_FUN_005d5889");
extern const unsigned char code_ref_005dd7c4[] __asm__("_FUN_005dd7c4");
extern const unsigned char code_ref_005dd882[] __asm__("_FUN_005dd882");
extern const unsigned char code_ref_005ddb28[] __asm__("_FUN_005ddb28");
extern const unsigned char code_ref_005ddd67[] __asm__("_FUN_005ddd67");
extern const unsigned char code_ref_005decbe[] __asm__("_FUN_005decbe");
extern const unsigned char code_ref_005e1020[] __asm__("_FUN_005e1020");
extern const unsigned char code_ref_005e1024[] __asm__("_FUN_005e1024");
extern const unsigned char code_ref_005e1147[] __asm__("_FUN_005e1147");
extern const unsigned char code_ref_005e114b[] __asm__("_FUN_005e114b");
extern const unsigned char code_ref_0061cb82[] __asm__("_FUN_0061cb82");
extern const unsigned char code_ref_0061cb91[] __asm__("_FUN_0061cb91");
extern const unsigned char code_ref_00620527[] __asm__("_FUN_00620527");
extern const unsigned char code_ref_00620553[] __asm__("_FUN_00620553@4");
extern const unsigned char code_ref_00620565[] __asm__("_FUN_00620565");
extern const unsigned char code_ref_0062058a[] __asm__("_FUN_0062058a");
extern const unsigned char code_ref_006205ab[] __asm__("_FUN_006205ab");
extern const unsigned char code_ref_00651d38[] __asm__("_FUN_00651d38");
extern const unsigned char code_ref_00651df8[] __asm__("_FUN_00651df8");
extern const unsigned char code_ref_00651ffc[] __asm__("_FUN_00651ffc");
extern const unsigned char code_ref_006523bd[] __asm__("_FUN_006523bd");
extern const unsigned char code_ref_00652532[] __asm__("_FUN_00652532");
extern const unsigned char code_ref_006528a1[] __asm__("_FUN_006528a1");
extern const unsigned char code_ref_00652a9d[] __asm__("_FUN_00652a9d");
extern const unsigned char code_ref_00652abd[] __asm__("_FUN_00652abd");
extern const unsigned char code_ref_00652b91[] __asm__("_FUN_00652b91");
extern const unsigned char code_ref_00652db2[] __asm__("_FUN_00652db2");
extern const unsigned char code_ref_00652ed0[] __asm__("_FUN_00652ed0");
extern const unsigned char code_ref_00653142[] __asm__("_FUN_00653142");
extern const unsigned char code_ref_00653c75[] __asm__("_FUN_00653c75");
extern const unsigned char code_ref_00653d39[] __asm__("_FUN_00653d39");
extern const unsigned char code_ref_0069dae1[] __asm__("_FUN_0069dae1");
extern const unsigned char label_ref_006058f9[] __asm__("_shader_location_006058f9");
extern const unsigned char label_ref_0060590d[] __asm__("_shader_location_0060590d");
extern const unsigned char label_ref_0060591f[] __asm__("_shader_location_0060591f");
extern const unsigned char label_ref_00605932[] __asm__("_shader_location_00605932");
extern const unsigned char label_ref_0060593a[] __asm__("_shader_location_0060593a");
extern const unsigned char label_ref_00605946[] __asm__("_shader_location_00605946");
extern const unsigned char label_ref_00605952[] __asm__("_shader_location_00605952");
extern const unsigned char label_ref_00605964[] __asm__("_shader_location_00605964");
extern const unsigned char label_ref_00605975[] __asm__("_shader_location_00605975");
extern const unsigned char label_ref_0060598c[] __asm__("_shader_location_0060598c");
extern const unsigned char label_ref_0060599e[] __asm__("_shader_location_0060599e");
extern const unsigned char label_ref_006059aa[] __asm__("_shader_location_006059aa");
extern const unsigned char label_ref_006059b6[] __asm__("_shader_location_006059b6");
extern const unsigned char label_ref_006059cf[] __asm__("_shader_location_006059cf");
extern const unsigned char label_ref_006059da[] __asm__("_shader_location_006059da");
extern const unsigned char label_ref_006059e6[] __asm__("_shader_location_006059e6");
extern const unsigned char label_ref_006059ee[] __asm__("_shader_location_006059ee");
extern const unsigned char label_ref_00605a04[] __asm__("_shader_location_00605a04");
extern const unsigned char label_ref_00605a26[] __asm__("_shader_location_00605a26");
extern const unsigned char label_ref_00605a39[] __asm__("_shader_location_00605a39");
extern const unsigned char label_ref_00605a44[] __asm__("_shader_location_00605a44");
extern const unsigned char label_ref_00605a53[] __asm__("_shader_location_00605a53");
extern const unsigned char label_ref_00605a9a[] __asm__("_shader_location_00605a9a");
extern const unsigned char label_ref_00605aab[] __asm__("_shader_location_00605aab");
extern const unsigned char label_ref_00605abc[] __asm__("_shader_location_00605abc");
extern const unsigned char label_ref_00605aca[] __asm__("_shader_location_00605aca");
extern const unsigned char label_ref_00605adf[] __asm__("_shader_location_00605adf");
extern const unsigned char label_ref_00605aef[] __asm__("_shader_location_00605aef");
extern const unsigned char label_ref_00605afd[] __asm__("_shader_location_00605afd");
extern const unsigned char label_ref_00605b13[] __asm__("_shader_location_00605b13");
extern const unsigned char label_ref_00605b2c[] __asm__("_shader_location_00605b2c");
extern const unsigned char label_ref_00605b44[] __asm__("_shader_location_00605b44");
extern const unsigned char label_ref_00605b55[] __asm__("_shader_location_00605b55");
extern const unsigned char label_ref_00605b6b[] __asm__("_shader_location_00605b6b");
extern const unsigned char label_ref_00605e06[] __asm__("_shader_location_00605e06");
extern const unsigned char label_ref_00605e0f[] __asm__("_shader_location_00605e0f");
extern const unsigned char label_ref_00605e18[] __asm__("_shader_location_00605e18");
extern const unsigned char label_ref_00605e21[] __asm__("_shader_location_00605e21");
extern const unsigned char label_ref_00605e2a[] __asm__("_shader_location_00605e2a");
extern const unsigned char label_ref_00605e33[] __asm__("_shader_location_00605e33");
extern const unsigned char label_ref_00605e3c[] __asm__("_shader_location_00605e3c");
extern const unsigned char label_ref_00605e45[] __asm__("_shader_location_00605e45");
extern const unsigned char label_ref_00605e4e[] __asm__("_shader_location_00605e4e");
extern const unsigned char label_ref_00605e57[] __asm__("_shader_location_00605e57");
extern const unsigned char label_ref_00605e60[] __asm__("_shader_location_00605e60");
extern const unsigned char label_ref_00605e69[] __asm__("_shader_location_00605e69");
extern const unsigned char label_ref_00605e72[] __asm__("_shader_location_00605e72");
extern const unsigned char label_ref_00605e7b[] __asm__("_shader_location_00605e7b");
extern const unsigned char label_ref_00605e84[] __asm__("_shader_location_00605e84");
extern const unsigned char label_ref_00605e8d[] __asm__("_shader_location_00605e8d");
extern const unsigned char label_ref_00605e96[] __asm__("_shader_location_00605e96");
extern const unsigned char label_ref_00605e9f[] __asm__("_shader_location_00605e9f");
extern const unsigned char label_ref_00605ea8[] __asm__("_shader_location_00605ea8");
extern const unsigned char label_ref_00605eb1[] __asm__("_shader_location_00605eb1");
extern const unsigned char label_ref_00605eba[] __asm__("_shader_location_00605eba");
extern const unsigned char label_ref_00605ec3[] __asm__("_shader_location_00605ec3");
extern const unsigned char label_ref_00605ecc[] __asm__("_shader_location_00605ecc");
extern const unsigned char label_ref_00605ed5[] __asm__("_shader_location_00605ed5");
extern const unsigned char label_ref_00605ede[] __asm__("_shader_location_00605ede");
extern const unsigned char label_ref_00605ee7[] __asm__("_shader_location_00605ee7");
extern const unsigned char label_ref_00605eed[] __asm__("_shader_location_00605eed");
extern const unsigned char label_ref_00605ef3[] __asm__("_shader_location_00605ef3");
extern const unsigned char label_ref_00605ef9[] __asm__("_shader_location_00605ef9");
extern const unsigned char label_ref_00605eff[] __asm__("_shader_location_00605eff");
extern const unsigned char label_ref_00605f05[] __asm__("_shader_location_00605f05");
extern const unsigned char label_ref_00605f0b[] __asm__("_shader_location_00605f0b");
extern const unsigned char label_ref_00605f11[] __asm__("_shader_location_00605f11");
extern const unsigned char label_ref_00605f17[] __asm__("_shader_location_00605f17");
extern const unsigned char label_ref_00605f1d[] __asm__("_shader_location_00605f1d");
extern const unsigned char label_ref_00605f23[] __asm__("_shader_location_00605f23");
extern const unsigned char label_ref_00605f29[] __asm__("_shader_location_00605f29");
extern const unsigned char label_ref_00605f2f[] __asm__("_shader_location_00605f2f");
extern const unsigned char label_ref_00605f35[] __asm__("_shader_location_00605f35");
extern const unsigned char label_ref_00605f3b[] __asm__("_shader_location_00605f3b");
extern const unsigned char label_ref_00605f41[] __asm__("_shader_location_00605f41");
extern const unsigned char label_ref_00605f47[] __asm__("_shader_location_00605f47");
extern const unsigned char label_ref_00605f4d[] __asm__("_shader_location_00605f4d");
extern const unsigned char label_ref_00605f53[] __asm__("_shader_location_00605f53");
extern const unsigned char label_ref_00605f59[] __asm__("_shader_location_00605f59");
extern const unsigned char label_ref_00605f5f[] __asm__("_shader_location_00605f5f");
extern const unsigned char label_ref_00605f65[] __asm__("_shader_location_00605f65");
extern const unsigned char label_ref_00607090[] __asm__("_shader_location_00607090");
extern const unsigned char label_ref_0060709a[] __asm__("_shader_location_0060709a");
extern const unsigned char label_ref_006070a0[] __asm__("_shader_location_006070a0");
extern const unsigned char label_ref_006070aa[] __asm__("_shader_location_006070aa");
extern const unsigned char label_ref_006070b4[] __asm__("_shader_location_006070b4");
extern const unsigned char label_ref_006070be[] __asm__("_shader_location_006070be");
extern const unsigned char label_ref_006070cd[] __asm__("_shader_location_006070cd");
extern const unsigned char label_ref_006070dc[] __asm__("_shader_location_006070dc");
extern const unsigned char label_ref_006070eb[] __asm__("_shader_location_006070eb");
extern const unsigned char label_ref_0060710e[] __asm__("_shader_location_0060710e");
extern const unsigned char label_ref_0060712c[] __asm__("_shader_location_0060712c");
extern const unsigned char label_ref_00607133[] __asm__("_shader_location_00607133");
extern const unsigned char label_ref_0060713a[] __asm__("_shader_location_0060713a");
extern const unsigned char label_ref_00607141[] __asm__("_shader_location_00607141");
extern const unsigned char label_ref_0060a471[] __asm__("_shader_location_0060a471");
extern const unsigned char label_ref_0060a478[] __asm__("_shader_location_0060a478");
extern const unsigned char label_ref_0060a480[] __asm__("_shader_location_0060a480");
extern const unsigned char label_ref_0060a492[] __asm__("_shader_location_0060a492");
extern const unsigned char label_ref_0060a4ab[] __asm__("_shader_location_0060a4ab");
extern const unsigned char label_ref_0060a4b0[] __asm__("_shader_location_0060a4b0");
extern const unsigned char label_ref_0060a4dc[] __asm__("_shader_location_0060a4dc");
extern const unsigned char label_ref_0060a513[] __asm__("_shader_location_0060a513");
extern const unsigned char label_ref_0060a552[] __asm__("_shader_location_0060a552");
extern const unsigned char label_ref_0060a57c[] __asm__("_shader_location_0060a57c");
extern const unsigned char label_ref_0060a5c2[] __asm__("_shader_location_0060a5c2");
extern const unsigned char label_ref_0060a5e6[] __asm__("_shader_location_0060a5e6");
extern const unsigned char label_ref_0060a666[] __asm__("_shader_location_0060a666");
extern const unsigned char label_ref_0060a6c8[] __asm__("_shader_location_0060a6c8");
extern const unsigned char label_ref_0060a711[] __asm__("_shader_location_0060a711");
extern const unsigned char label_ref_0060a726[] __asm__("_shader_location_0060a726");
extern const unsigned char label_ref_0060a72b[] __asm__("_shader_location_0060a72b");
extern const unsigned char label_ref_0060a764[] __asm__("_shader_location_0060a764");
extern const unsigned char label_ref_0060a788[] __asm__("_shader_location_0060a788");
extern const unsigned char label_ref_0060a7a3[] __asm__("_shader_location_0060a7a3");
extern const unsigned char label_ref_0060a7d6[] __asm__("_shader_location_0060a7d6");
extern const unsigned char label_ref_0060a80a[] __asm__("_shader_location_0060a80a");
extern const unsigned char label_ref_0060a815[] __asm__("_shader_location_0060a815");
extern const unsigned char label_ref_0060a834[] __asm__("_shader_location_0060a834");
extern const unsigned char label_ref_0060a850[] __asm__("_shader_location_0060a850");
extern const unsigned char label_ref_0060a85a[] __asm__("_shader_location_0060a85a");
extern const unsigned char label_ref_0060a87d[] __asm__("_shader_location_0060a87d");
extern const unsigned char label_ref_0060a89f[] __asm__("_shader_location_0060a89f");
extern const unsigned char label_ref_0060aaec[] __asm__("_shader_location_0060aaec");
extern const unsigned char label_ref_0060aaf5[] __asm__("_shader_location_0060aaf5");
extern const unsigned char label_ref_0060aafe[] __asm__("_shader_location_0060aafe");
extern const unsigned char label_ref_0060ab07[] __asm__("_shader_location_0060ab07");
extern const unsigned char label_ref_0060ab10[] __asm__("_shader_location_0060ab10");
extern const unsigned char label_ref_0060ab19[] __asm__("_shader_location_0060ab19");
extern const unsigned char label_ref_0060ab22[] __asm__("_shader_location_0060ab22");
extern const unsigned char label_ref_0060ab2b[] __asm__("_shader_location_0060ab2b");
extern const unsigned char label_ref_0060ab34[] __asm__("_shader_location_0060ab34");
extern const unsigned char label_ref_0060ab3d[] __asm__("_shader_location_0060ab3d");
extern const unsigned char label_ref_0060ab46[] __asm__("_shader_location_0060ab46");
extern const unsigned char label_ref_0060ab4f[] __asm__("_shader_location_0060ab4f");
extern const unsigned char label_ref_0060ab58[] __asm__("_shader_location_0060ab58");
extern const unsigned char label_ref_0060ab61[] __asm__("_shader_location_0060ab61");
extern const unsigned char label_ref_0060ab6a[] __asm__("_shader_location_0060ab6a");
extern const unsigned char label_ref_0060ab73[] __asm__("_shader_location_0060ab73");
extern const unsigned char label_ref_0060ab7c[] __asm__("_shader_location_0060ab7c");
extern const unsigned char label_ref_0060ab85[] __asm__("_shader_location_0060ab85");
extern const unsigned char label_ref_0060ab8e[] __asm__("_shader_location_0060ab8e");
extern const unsigned char label_ref_0060ab97[] __asm__("_shader_location_0060ab97");
extern const unsigned char label_ref_0060aba0[] __asm__("_shader_location_0060aba0");
extern const unsigned char label_ref_0060aba9[] __asm__("_shader_location_0060aba9");
extern const unsigned char label_ref_0060abb2[] __asm__("_shader_location_0060abb2");
extern const unsigned char label_ref_0060abbb[] __asm__("_shader_location_0060abbb");
extern const unsigned char label_ref_0060abc4[] __asm__("_shader_location_0060abc4");
extern const unsigned char label_ref_0060abcd[] __asm__("_shader_location_0060abcd");
extern const unsigned char label_ref_0060abd6[] __asm__("_shader_location_0060abd6");
extern const unsigned char label_ref_0060abdf[] __asm__("_shader_location_0060abdf");
extern const unsigned char label_ref_0060abe8[] __asm__("_shader_location_0060abe8");
extern const unsigned char label_ref_0060abf1[] __asm__("_shader_location_0060abf1");
extern const unsigned char label_ref_0060abfa[] __asm__("_shader_location_0060abfa");
extern const unsigned char label_ref_0060ac03[] __asm__("_shader_location_0060ac03");
extern const unsigned char label_ref_0060ac0c[] __asm__("_shader_location_0060ac0c");
extern const unsigned char label_ref_0060ac15[] __asm__("_shader_location_0060ac15");
extern const unsigned char label_ref_0060ac1e[] __asm__("_shader_location_0060ac1e");
extern const unsigned char label_ref_0060ac27[] __asm__("_shader_location_0060ac27");
extern const unsigned char label_ref_0060ac30[] __asm__("_shader_location_0060ac30");
extern const unsigned char label_ref_0060ac39[] __asm__("_shader_location_0060ac39");
extern const unsigned char label_ref_0060ac42[] __asm__("_shader_location_0060ac42");
extern const unsigned char label_ref_0060ac4b[] __asm__("_shader_location_0060ac4b");
extern const unsigned char label_ref_0060ac54[] __asm__("_shader_location_0060ac54");
extern const unsigned char label_ref_0060ac5a[] __asm__("_shader_location_0060ac5a");
extern const unsigned char label_ref_0060ac60[] __asm__("_shader_location_0060ac60");
extern const unsigned char label_ref_0060ac66[] __asm__("_shader_location_0060ac66");
extern const unsigned char label_ref_0060ac6c[] __asm__("_shader_location_0060ac6c");
extern const unsigned char label_ref_0060ac72[] __asm__("_shader_location_0060ac72");
extern const unsigned char label_ref_0060ac78[] __asm__("_shader_location_0060ac78");
extern const unsigned char label_ref_0060ac7e[] __asm__("_shader_location_0060ac7e");
extern const unsigned char label_ref_0060ac84[] __asm__("_shader_location_0060ac84");
extern const unsigned char label_ref_0060ac8a[] __asm__("_shader_location_0060ac8a");
extern const unsigned char label_ref_0060ac90[] __asm__("_shader_location_0060ac90");
extern const unsigned char label_ref_0060ac96[] __asm__("_shader_location_0060ac96");
extern const unsigned char label_ref_0060ac9c[] __asm__("_shader_location_0060ac9c");
extern const unsigned char label_ref_0060aca2[] __asm__("_shader_location_0060aca2");
extern const unsigned char label_ref_0060aca8[] __asm__("_shader_location_0060aca8");
extern const unsigned char label_ref_0060acae[] __asm__("_shader_location_0060acae");
extern const unsigned char label_ref_0060acb4[] __asm__("_shader_location_0060acb4");
extern const unsigned char label_ref_0060acba[] __asm__("_shader_location_0060acba");
extern const unsigned char label_ref_0060acc0[] __asm__("_shader_location_0060acc0");
extern const unsigned char label_ref_0060acc6[] __asm__("_shader_location_0060acc6");
extern const unsigned char label_ref_0060accc[] __asm__("_shader_location_0060accc");
extern const unsigned char label_ref_0060acd2[] __asm__("_shader_location_0060acd2");
extern const unsigned char label_ref_006297e1[] __asm__("_shader_location_006297e1");
extern const unsigned char label_ref_006297f1[] __asm__("_shader_location_006297f1");
extern const unsigned char label_ref_00629804[] __asm__("_shader_location_00629804");
extern const unsigned char label_ref_00629813[] __asm__("_shader_location_00629813");
extern const unsigned char label_ref_00629827[] __asm__("_shader_location_00629827");
extern const unsigned char label_ref_00629831[] __asm__("_shader_location_00629831");
extern const unsigned char label_ref_0062983b[] __asm__("_shader_location_0062983b");
extern const unsigned char label_ref_00629840[] __asm__("_shader_location_00629840");
extern const unsigned char label_ref_0069606a[] __asm__("_shader_location_0069606a");
extern const unsigned char label_ref_00696075[] __asm__("_shader_location_00696075");
extern const unsigned char label_ref_00696080[] __asm__("_shader_location_00696080");
extern const unsigned char label_ref_00696089[] __asm__("_shader_location_00696089");
extern const unsigned char label_ref_00696094[] __asm__("_shader_location_00696094");
extern const unsigned char label_ref_0069609f[] __asm__("_shader_location_0069609f");
extern const unsigned char label_ref_006960a7[] __asm__("_shader_location_006960a7");
extern const unsigned char label_ref_006960af[] __asm__("_shader_location_006960af");
extern const unsigned char label_ref_006960b7[] __asm__("_shader_location_006960b7");
extern const unsigned char label_ref_006960bf[] __asm__("_shader_location_006960bf");
extern const unsigned char label_ref_006960c9[] __asm__("_shader_location_006960c9");
extern const unsigned char label_ref_006960d8[] __asm__("_shader_location_006960d8");
extern const unsigned char label_ref_006960f0[] __asm__("_shader_location_006960f0");
extern const unsigned char label_ref_006960f8[] __asm__("_shader_location_006960f8");
extern const unsigned char label_ref_00696100[] __asm__("_shader_location_00696100");
extern const unsigned char label_ref_00696108[] __asm__("_shader_location_00696108");
extern const unsigned char label_ref_00696110[] __asm__("_shader_location_00696110");
extern const unsigned char label_ref_00696118[] __asm__("_shader_location_00696118");
extern const unsigned char storage_ref_006bcaf4[] __asm__("_dat_006bcaf4");
extern const unsigned char storage_ref_006bcb04[] __asm__("_dat_006bcb04");
extern const unsigned char storage_ref_006bcb08[] __asm__("_dat_006bcb08");
extern const unsigned char storage_ref_006bcb0c[] __asm__("_dat_006bcb0c");
extern const unsigned char storage_ref_006bcb10[] __asm__("_dat_006bcb10");
extern const unsigned char storage_ref_006bcb14[] __asm__("_dat_006bcb14");
extern const unsigned char storage_ref_006bcb18[] __asm__("_dat_006bcb18");
extern const unsigned char storage_ref_006c584c[] __asm__("_dat_006c584c");
extern const unsigned char storage_ref_006d2380[] __asm__("_dat_006d2380");
extern const unsigned char storage_ref_006d6ab8[] __asm__("_dat_006d6ab8");
extern const unsigned char storage_ref_006d6ac0[] __asm__("_dat_006d6ac0");
extern const unsigned char storage_ref_006d6acc[] __asm__("_dat_006d6acc");
extern const unsigned char storage_ref_006d6ad8[] __asm__("_dat_006d6ad8");
extern const unsigned char storage_ref_006d6ae4[] __asm__("_dat_006d6ae4");
extern const unsigned char storage_ref_006d6af0[] __asm__("_dat_006d6af0");
extern const unsigned char storage_ref_006d6ce8[] __asm__("_s_006d6ce8");
extern const unsigned char storage_ref_006d6cec[] __asm__("_s_006d6cec");
extern const unsigned char storage_ref_006d6cf8[] __asm__("_s_006d6cf8");
extern const unsigned char storage_ref_006db1d4[] __asm__("_dat_006db1d4");
extern const unsigned char storage_ref_006db1e0[] __asm__("_dat_006db1e0");
extern const unsigned char storage_ref_006db1e8[] __asm__("_dat_006db1e8");
extern const unsigned char storage_ref_006db1f0[] __asm__("_dat_006db1f0");
extern const unsigned char storage_ref_006db1f8[] __asm__("_dat_006db1f8");
extern const unsigned char storage_ref_006db204[] __asm__("_dat_006db204");
extern const unsigned char storage_ref_006db20c[] __asm__("_dat_006db20c");
extern const unsigned char storage_ref_006db218[] __asm__("_dat_006db218");
extern const unsigned char storage_ref_006db224[] __asm__("_dat_006db224");
extern const unsigned char storage_ref_006db238[] __asm__("_dat_006db238");
extern const unsigned char storage_ref_006db248[] __asm__("_dat_006db248");
extern const unsigned char storage_ref_006db250[] __asm__("_dat_006db250");
extern const unsigned char storage_ref_006db25c[] __asm__("_dat_006db25c");
extern const unsigned char storage_ref_006db268[] __asm__("_dat_006db268");
extern const unsigned char storage_ref_006db274[] __asm__("_dat_006db274");
extern const unsigned char storage_ref_006db280[] __asm__("_dat_006db280");
extern const unsigned char storage_ref_006db288[] __asm__("_dat_006db288");
extern const unsigned char storage_ref_006db2a0[] __asm__("_dat_006db2a0");
extern const unsigned char storage_ref_006db2ac[] __asm__("_dat_006db2ac");
extern const unsigned char storage_ref_006db2b4[] __asm__("_dat_006db2b4");
extern const unsigned char storage_ref_006db2bc[] __asm__("_dat_006db2bc");
extern const unsigned char storage_ref_006db2c4[] __asm__("_dat_006db2c4");
extern const unsigned char storage_ref_006db2cc[] __asm__("_dat_006db2cc");
extern const unsigned char storage_ref_006db2d4[] __asm__("_dat_006db2d4");
extern const unsigned char storage_ref_006db2dc[] __asm__("_dat_006db2dc");
extern const unsigned char storage_ref_006db2e4[] __asm__("_dat_006db2e4");
extern const unsigned char storage_ref_006db2ec[] __asm__("_dat_006db2ec");
extern const unsigned char storage_ref_006db2f4[] __asm__("_dat_006db2f4");
extern const unsigned char storage_ref_006db2fc[] __asm__("_dat_006db2fc");
extern const unsigned char storage_ref_006db308[] __asm__("_dat_006db308");
extern const unsigned char storage_ref_006db310[] __asm__("_dat_006db310");
extern const unsigned char storage_ref_006db318[] __asm__("_dat_006db318");
extern const unsigned char storage_ref_006db320[] __asm__("_dat_006db320");
extern const unsigned char storage_ref_006db328[] __asm__("_dat_006db328");
extern const unsigned char storage_ref_006db330[] __asm__("_dat_006db330");
extern const unsigned char storage_ref_006db418[] __asm__("_dat_006db418");
extern const unsigned char storage_ref_006db428[] __asm__("_dat_006db428");
extern const unsigned char storage_ref_006db438[] __asm__("_dat_006db438");
extern const unsigned char storage_ref_006db44c[] __asm__("_dat_006db44c");
extern const unsigned char storage_ref_006db458[] __asm__("_dat_006db458");
extern const unsigned char storage_ref_006db468[] __asm__("_dat_006db468");
extern const unsigned char storage_ref_006db474[] __asm__("_dat_006db474");
extern const unsigned char storage_ref_006db484[] __asm__("_dat_006db484");
extern const unsigned char storage_ref_006db48c[] __asm__("_dat_006db48c");
extern const unsigned char storage_ref_006db498[] __asm__("_dat_006db498");
extern const unsigned char storage_ref_006db4a4[] __asm__("_dat_006db4a4");
extern const unsigned char storage_ref_006db4b0[] __asm__("_dat_006db4b0");
extern const unsigned char storage_ref_006db4b4[] __asm__("_dat_006db4b4");
extern const unsigned char storage_ref_006db4c0[] __asm__("_dat_006db4c0");
extern const unsigned char storage_ref_006db4cc[] __asm__("_dat_006db4cc");
extern const unsigned char storage_ref_006db4d4[] __asm__("_dat_006db4d4");
extern const unsigned char storage_ref_006db4e4[] __asm__("_dat_006db4e4");
extern const unsigned char storage_ref_006db4ec[] __asm__("_dat_006db4ec");
extern const unsigned char storage_ref_006db4f4[] __asm__("_dat_006db4f4");
extern const unsigned char storage_ref_006db4fc[] __asm__("_dat_006db4fc");
extern const unsigned char storage_ref_006db504[] __asm__("_dat_006db504");
extern const unsigned char storage_ref_006db718[] __asm__("_dat_006db718");
extern const unsigned char storage_ref_006db71c[] __asm__("_dat_006db71c");
extern const unsigned char storage_ref_006db720[] __asm__("_dat_006db720");
extern const unsigned char storage_ref_006db724[] __asm__("_dat_006db724");
extern const unsigned char storage_ref_006db72c[] __asm__("_dat_006db72c");
extern const unsigned char storage_ref_006db73c[] __asm__("_dat_006db73c");
extern const unsigned char storage_ref_006db750[] __asm__("_dat_006db750");
extern const unsigned char storage_ref_006db760[] __asm__("_dat_006db760");
extern const unsigned char storage_ref_006db774[] __asm__("_dat_006db774");
extern const unsigned char storage_ref_006db784[] __asm__("_dat_006db784");
extern const unsigned char storage_ref_006db798[] __asm__("_dat_006db798");
extern const unsigned char storage_ref_006db7a8[] __asm__("_dat_006db7a8");
extern const unsigned char storage_ref_006db7bc[] __asm__("_dat_006db7bc");
extern const unsigned char storage_ref_006db7cc[] __asm__("_dat_006db7cc");
extern const unsigned char storage_ref_006db7dc[] __asm__("_dat_006db7dc");
extern const unsigned char storage_ref_006db7f0[] __asm__("_dat_006db7f0");
extern const unsigned char storage_ref_006db804[] __asm__("_dat_006db804");
extern const unsigned char storage_ref_006db818[] __asm__("_dat_006db818");
extern const unsigned char storage_ref_006db828[] __asm__("_dat_006db828");
extern const unsigned char storage_ref_006db844[] __asm__("_dat_006db844");
extern const unsigned char storage_ref_006db858[] __asm__("_dat_006db858");
extern const unsigned char storage_ref_006db86c[] __asm__("_dat_006db86c");
extern const unsigned char storage_ref_006db87c[] __asm__("_dat_006db87c");
extern const unsigned char storage_ref_006db88c[] __asm__("_dat_006db88c");
extern const unsigned char storage_ref_006db8a0[] __asm__("_dat_006db8a0");
extern const unsigned char storage_ref_006db8b8[] __asm__("_dat_006db8b8");
extern const unsigned char storage_ref_006db8cc[] __asm__("_dat_006db8cc");
extern const unsigned char storage_ref_006db8e0[] __asm__("_dat_006db8e0");
extern const unsigned char storage_ref_006db8ec[] __asm__("_dat_006db8ec");
extern const unsigned char storage_ref_006db8fc[] __asm__("_dat_006db8fc");
extern const unsigned char storage_ref_006db90c[] __asm__("_dat_006db90c");
extern const unsigned char storage_ref_006db91c[] __asm__("_dat_006db91c");
extern const unsigned char storage_ref_006db930[] __asm__("_dat_006db930");
extern const unsigned char storage_ref_006db944[] __asm__("_dat_006db944");
extern const unsigned char storage_ref_006db954[] __asm__("_dat_006db954");
extern const unsigned char storage_ref_006db964[] __asm__("_dat_006db964");
extern const unsigned char storage_ref_006db978[] __asm__("_dat_006db978");
extern const unsigned char storage_ref_006db988[] __asm__("_dat_006db988");
extern const unsigned char storage_ref_006db998[] __asm__("_dat_006db998");
extern const unsigned char storage_ref_006db9a4[] __asm__("_dat_006db9a4");
extern const unsigned char storage_ref_006db9b0[] __asm__("_dat_006db9b0");
extern const unsigned char storage_ref_006db9bc[] __asm__("_dat_006db9bc");
extern const unsigned char storage_ref_006db9d8[] __asm__("_dat_006db9d8");
extern const unsigned char storage_ref_006db9f0[] __asm__("_dat_006db9f0");
extern const unsigned char storage_ref_006db9fc[] __asm__("_dat_006db9fc");
extern const unsigned char storage_ref_006dba0c[] __asm__("_dat_006dba0c");
extern const unsigned char storage_ref_006dba18[] __asm__("_dat_006dba18");
extern const unsigned char storage_ref_006dba2c[] __asm__("_dat_006dba2c");
extern const unsigned char storage_ref_006dba38[] __asm__("_dat_006dba38");
extern const unsigned char storage_ref_006dba48[] __asm__("_dat_006dba48");
extern const unsigned char storage_ref_006dba54[] __asm__("_dat_006dba54");
extern const unsigned char storage_ref_006dba68[] __asm__("_dat_006dba68");
extern const unsigned char storage_ref_006dba78[] __asm__("_dat_006dba78");
extern const unsigned char storage_ref_006dba8c[] __asm__("_dat_006dba8c");
extern const unsigned char storage_ref_006dbaa0[] __asm__("_dat_006dbaa0");
extern const unsigned char storage_ref_006dbab4[] __asm__("_dat_006dbab4");
extern const unsigned char storage_ref_006dbac8[] __asm__("_dat_006dbac8");
extern const unsigned char storage_ref_006dbad0[] __asm__("_dat_006dbad0");
extern const unsigned char storage_ref_006dbad4[] __asm__("_dat_006dbad4");
extern const unsigned char storage_ref_006dbad8[] __asm__("_dat_006dbad8");
extern const unsigned char storage_ref_006dbae4[] __asm__("_dat_006dbae4");
extern const unsigned char storage_ref_006dbaec[] __asm__("_dat_006dbaec");
extern const unsigned char storage_ref_006dbaf8[] __asm__("_dat_006dbaf8");
extern const unsigned char storage_ref_006dbb0c[] __asm__("_dat_006dbb0c");
extern const unsigned char storage_ref_006dbb20[] __asm__("_dat_006dbb20");
extern const unsigned char storage_ref_006de7c0[] __asm__("_dat_006de7c0");
extern const unsigned char storage_ref_006de7c8[] __asm__("_dat_006de7c8");
extern const unsigned char storage_ref_006de7d0[] __asm__("_dat_006de7d0");
extern const unsigned char storage_ref_006de7d8[] __asm__("_dat_006de7d8");
extern const unsigned char storage_ref_006de7e0[] __asm__("_dat_006de7e0");
extern const unsigned char storage_ref_006de7e8[] __asm__("_dat_006de7e8");
extern const unsigned char storage_ref_006de7f0[] __asm__("_dat_006de7f0");
extern const unsigned char storage_ref_006de7f8[] __asm__("_dat_006de7f8");
extern const unsigned char storage_ref_006de800[] __asm__("_dat_006de800");
extern const unsigned char storage_ref_006de808[] __asm__("_dat_006de808");
extern const unsigned char storage_ref_006de810[] __asm__("_dat_006de810");
extern const unsigned char storage_ref_006de818[] __asm__("_dat_006de818");
extern const unsigned char storage_ref_006de820[] __asm__("_dat_006de820");
extern const unsigned char storage_ref_006de828[] __asm__("_dat_006de828");
extern const unsigned char storage_ref_006de830[] __asm__("_dat_006de830");
extern const unsigned char storage_ref_006de838[] __asm__("_dat_006de838");
extern const unsigned char storage_ref_006de840[] __asm__("_dat_006de840");
extern const unsigned char storage_ref_006de844[] __asm__("_dat_006de844");
extern const unsigned char storage_ref_006de84c[] __asm__("_dat_006de84c");
extern const unsigned char storage_ref_006de850[] __asm__("_dat_006de850");
extern const unsigned char storage_ref_006de858[] __asm__("_dat_006de858");
extern const unsigned char storage_ref_006de860[] __asm__("_dat_006de860");
extern const unsigned char storage_ref_006de868[] __asm__("_dat_006de868");
extern const unsigned char storage_ref_006de870[] __asm__("_dat_006de870");
extern const unsigned char storage_ref_006de878[] __asm__("_dat_006de878");
extern const unsigned char storage_ref_006de880[] __asm__("_dat_006de880");
extern const unsigned char storage_ref_006de888[] __asm__("_dat_006de888");
extern const unsigned char storage_ref_006de890[] __asm__("_dat_006de890");
extern const unsigned char storage_ref_006de898[] __asm__("_dat_006de898");
extern const unsigned char storage_ref_006de8a0[] __asm__("_dat_006de8a0");
extern const unsigned char storage_ref_006de8a8[] __asm__("_dat_006de8a8");
extern const unsigned char storage_ref_006de8b0[] __asm__("_dat_006de8b0");
extern const unsigned char storage_ref_006de8b8[] __asm__("_dat_006de8b8");
extern const unsigned char storage_ref_006de8c0[] __asm__("_dat_006de8c0");
extern const unsigned char storage_ref_006de8c8[] __asm__("_dat_006de8c8");
extern const unsigned char storage_ref_006de8d0[] __asm__("_dat_006de8d0");
extern const unsigned char storage_ref_006de8d8[] __asm__("_dat_006de8d8");
extern const unsigned char storage_ref_006de8e0[] __asm__("_dat_006de8e0");
extern const unsigned char storage_ref_006de8e8[] __asm__("_dat_006de8e8");
extern const unsigned char storage_ref_006de8f0[] __asm__("_dat_006de8f0");
extern const unsigned char storage_ref_006de8f8[] __asm__("_dat_006de8f8");
extern const unsigned char storage_ref_006de900[] __asm__("_dat_006de900");
extern const unsigned char storage_ref_006de908[] __asm__("_dat_006de908");
extern const unsigned char storage_ref_006de910[] __asm__("_dat_006de910");
extern const unsigned char storage_ref_006dfbd8[] __asm__("_dat_006dfbd8");
extern const unsigned char storage_ref_006dfd08[] __asm__("_dat_006dfd08");
extern const unsigned char storage_ref_006dfd10[] __asm__("_dat_006dfd10");
extern const unsigned char storage_ref_006dfd38[] __asm__("_dat_006dfd38");
extern const unsigned char storage_ref_006e1d38[] __asm__("_dat_006e1d38");
extern const unsigned char storage_ref_006e1d3c[] __asm__("_dat_006e1d3c");
extern const unsigned char storage_ref_006e1d40[] __asm__("_dat_006e1d40");
extern const unsigned char storage_ref_006e1d48[] __asm__("_dat_006e1d48");
extern const unsigned char storage_ref_006e1d50[] __asm__("_dat_006e1d50");
extern const unsigned char storage_ref_006e1d54[] __asm__("_dat_006e1d54");
extern const unsigned char storage_ref_006e1d5c[] __asm__("_dat_006e1d5c");
extern const unsigned char storage_ref_006e1d60[] __asm__("_dat_006e1d60");
extern const unsigned char storage_ref_006e1d64[] __asm__("_dat_006e1d64");
extern const unsigned char storage_ref_006e1d68[] __asm__("_dat_006e1d68");
extern const unsigned char storage_ref_006e1d70[] __asm__("_dat_006e1d70");
extern const unsigned char storage_ref_006e1d78[] __asm__("_dat_006e1d78");
extern const unsigned char storage_ref_006e1d80[] __asm__("_dat_006e1d80");
extern const unsigned char storage_ref_006e1d88[] __asm__("_dat_006e1d88");
extern const unsigned char storage_ref_006e1d90[] __asm__("_dat_006e1d90");
extern const unsigned char storage_ref_006e1d98[] __asm__("_dat_006e1d98");
extern const unsigned char storage_ref_006e1da0[] __asm__("_dat_006e1da0");
extern const unsigned char storage_ref_006e1da8[] __asm__("_dat_006e1da8");
extern const unsigned char storage_ref_006e1db0[] __asm__("_dat_006e1db0");
extern const unsigned char storage_ref_006e1db4[] __asm__("_dat_006e1db4");
extern const unsigned char storage_ref_006e1db8[] __asm__("_dat_006e1db8");
extern const unsigned char storage_ref_006e1dc0[] __asm__("_dat_006e1dc0");
extern const unsigned char storage_ref_006e1dc4[] __asm__("_dat_006e1dc4");
extern const unsigned char storage_ref_006e1dc8[] __asm__("_dat_006e1dc8");
extern const unsigned char storage_ref_006e1dd4[] __asm__("_dat_006e1dd4");
extern const unsigned char storage_ref_006e1ddc[] __asm__("_dat_006e1ddc");
extern const unsigned char storage_ref_006e1de4[] __asm__("_dat_006e1de4");
extern const unsigned char storage_ref_006e1df4[] __asm__("_dat_006e1df4");
extern const unsigned char storage_ref_006e1e00[] __asm__("_dat_006e1e00");
extern const unsigned char storage_ref_006e1e0c[] __asm__("_dat_006e1e0c");
extern const unsigned char storage_ref_006e1e14[] __asm__("_dat_006e1e14");
extern const unsigned char storage_ref_006e1e1c[] __asm__("_dat_006e1e1c");
extern const unsigned char storage_ref_006e1e20[] __asm__("_dat_006e1e20");
extern const unsigned char storage_ref_006e1e28[] __asm__("_dat_006e1e28");
extern const unsigned char storage_ref_006e1e30[] __asm__("_dat_006e1e30");
extern const unsigned char storage_ref_006e1e40[] __asm__("_dat_006e1e40");
extern const unsigned char storage_ref_006e1e4c[] __asm__("_dat_006e1e4c");
extern const unsigned char storage_ref_006e1e58[] __asm__("_dat_006e1e58");
extern const unsigned char storage_ref_006e1e64[] __asm__("_dat_006e1e64");
extern const unsigned char storage_ref_006e1e70[] __asm__("_dat_006e1e70");
extern const unsigned char storage_ref_006e1e7c[] __asm__("_dat_006e1e7c");
extern const unsigned char storage_ref_006e1e88[] __asm__("_dat_006e1e88");
extern const unsigned char storage_ref_006e1e94[] __asm__("_dat_006e1e94");
extern const unsigned char storage_ref_006e1e9c[] __asm__("_dat_006e1e9c");
extern const unsigned char storage_ref_006e1ea4[] __asm__("_dat_006e1ea4");
extern const unsigned char storage_ref_006e1eac[] __asm__("_dat_006e1eac");
extern const unsigned char storage_ref_006e1eb4[] __asm__("_dat_006e1eb4");
extern const unsigned char storage_ref_006e1ebc[] __asm__("_dat_006e1ebc");
extern const unsigned char storage_ref_006e1ec0[] __asm__("_dat_006e1ec0");
extern const unsigned char storage_ref_006e1ec8[] __asm__("_dat_006e1ec8");
extern const unsigned char storage_ref_006e1ed0[] __asm__("_dat_006e1ed0");
extern const unsigned char storage_ref_006e1edc[] __asm__("_dat_006e1edc");
extern const unsigned char storage_ref_006e1ee4[] __asm__("_dat_006e1ee4");
extern const unsigned char storage_ref_006e1eec[] __asm__("_dat_006e1eec");
extern const unsigned char storage_ref_006e1ef4[] __asm__("_dat_006e1ef4");
extern const unsigned char storage_ref_006e1efc[] __asm__("_dat_006e1efc");
extern const unsigned char storage_ref_006e1f00[] __asm__("_dat_006e1f00");
extern const unsigned char storage_ref_006e1f08[] __asm__("_dat_006e1f08");
extern const unsigned char storage_ref_006e1f0c[] __asm__("_dat_006e1f0c");
extern const unsigned char storage_ref_006e1f10[] __asm__("_dat_006e1f10");
extern const unsigned char storage_ref_006e1f14[] __asm__("_dat_006e1f14");
extern const unsigned char storage_ref_006e1f18[] __asm__("_dat_006e1f18");
extern const unsigned char storage_ref_006e1f1c[] __asm__("_dat_006e1f1c");
extern const unsigned char storage_ref_006e1f24[] __asm__("_dat_006e1f24");
extern const unsigned char storage_ref_006e1f2c[] __asm__("_dat_006e1f2c");
extern const unsigned char storage_ref_006e1f30[] __asm__("_dat_006e1f30");
extern const unsigned char storage_ref_006e1f38[] __asm__("_dat_006e1f38");
extern const unsigned char storage_ref_006e1f40[] __asm__("_dat_006e1f40");
extern const unsigned char storage_ref_006e1f48[] __asm__("_dat_006e1f48");
extern const unsigned char storage_ref_006e1f50[] __asm__("_dat_006e1f50");
extern const unsigned char storage_ref_006e1f58[] __asm__("_dat_006e1f58");
extern const unsigned char storage_ref_006e1f60[] __asm__("_dat_006e1f60");
extern const unsigned char storage_ref_006e1f68[] __asm__("_dat_006e1f68");
extern const unsigned char storage_ref_006e1f70[] __asm__("_dat_006e1f70");
extern const unsigned char storage_ref_006e1f74[] __asm__("_dat_006e1f74");
extern const unsigned char storage_ref_006e1f78[] __asm__("_dat_006e1f78");
extern const unsigned char storage_ref_006e1f7c[] __asm__("_dat_006e1f7c");
extern const unsigned char storage_ref_006e1f80[] __asm__("_dat_006e1f80");
extern const unsigned char storage_ref_006e1f84[] __asm__("_dat_006e1f84");
extern const unsigned char storage_ref_006e1f88[] __asm__("_dat_006e1f88");
extern const unsigned char storage_ref_006e1f8c[] __asm__("_dat_006e1f8c");
extern const unsigned char storage_ref_006e1f90[] __asm__("_dat_006e1f90");
extern const unsigned char storage_ref_006e1f94[] __asm__("_dat_006e1f94");
extern const unsigned char storage_ref_006e1f98[] __asm__("_dat_006e1f98");
extern const unsigned char storage_ref_006e1f9c[] __asm__("_dat_006e1f9c");
extern const unsigned char storage_ref_006e1fa0[] __asm__("_dat_006e1fa0");
extern const unsigned char storage_ref_006e1fa4[] __asm__("_dat_006e1fa4");
extern const unsigned char storage_ref_006e1fa8[] __asm__("_dat_006e1fa8");
extern const unsigned char storage_ref_006e1fac[] __asm__("_dat_006e1fac");
extern const unsigned char storage_ref_006e1fb0[] __asm__("_dat_006e1fb0");
extern const unsigned char storage_ref_006e1fb4[] __asm__("_dat_006e1fb4");
extern const unsigned char storage_ref_006eb85c[] __asm__("_dat_006eb85c");
extern const unsigned char storage_ref_006eb864[] __asm__("_dat_006eb864");
extern const unsigned char storage_ref_006eb870[] __asm__("_dat_006eb870");
extern const unsigned char storage_ref_006eb87c[] __asm__("_dat_006eb87c");
extern const unsigned char storage_ref_006eb888[] __asm__("_dat_006eb888");
extern const unsigned char storage_ref_0070e188[] __asm__("_dat_0070e188");
extern const unsigned char storage_ref_0070e620[] __asm__("_dat_0070e620");
extern const void* const dat_00696253[29] = {
    label_ref_0069606a, label_ref_00696080, label_ref_00696080, label_ref_00696080,
    label_ref_00696080, label_ref_00696080, label_ref_00696080, label_ref_00696080,
    label_ref_00696080, label_ref_00696075, label_ref_00696075, label_ref_00696075,
    label_ref_00696075, label_ref_00696080, label_ref_00696089, label_ref_00696094,
    label_ref_0069609f, label_ref_006960a7, label_ref_006960af, label_ref_006960b7,
    label_ref_006960bf, label_ref_006960f0, label_ref_006960c9, label_ref_006960d8,
    label_ref_006960f8, label_ref_00696100, label_ref_00696108, label_ref_00696110,
    label_ref_00696118};
extern const void* const dat_0062984e[12] = {
    label_ref_006297e1, label_ref_006297f1, label_ref_00629804, label_ref_00629813,
    label_ref_006297e1, label_ref_006297f1, label_ref_00629804, label_ref_00629813,
    label_ref_00629827, label_ref_00629831, label_ref_0062983b, label_ref_00629840};
extern const void* const dat_0060ae8d[62] = {
    label_ref_0060aaec, label_ref_0060aaf5, label_ref_0060aafe, label_ref_0060ab07,
    label_ref_0060ab10, label_ref_0060ab19, label_ref_0060ab22, label_ref_0060ab2b,
    label_ref_0060ab34, label_ref_0060ab3d, label_ref_0060ab46, label_ref_0060ab4f,
    label_ref_0060ab58, label_ref_0060ab61, label_ref_0060ab6a, label_ref_0060ab73,
    label_ref_0060ab7c, label_ref_0060ab85, label_ref_0060ab8e, label_ref_0060ab97,
    label_ref_0060aba0, label_ref_0060aba9, label_ref_0060abb2, label_ref_0060abbb,
    label_ref_0060abc4, label_ref_0060abcd, label_ref_0060abd6, label_ref_0060abdf,
    label_ref_0060abe8, label_ref_0060abf1, label_ref_0060abfa, label_ref_0060ac03,
    label_ref_0060ac0c, label_ref_0060ac15, label_ref_0060ac1e, label_ref_0060ac27,
    label_ref_0060ac30, label_ref_0060ac39, label_ref_0060ac42, label_ref_0060ac4b,
    label_ref_0060ac54, label_ref_0060ac5a, label_ref_0060ac60, label_ref_0060ac66,
    label_ref_0060ac6c, label_ref_0060ac72, label_ref_0060ac78, label_ref_0060ac7e,
    label_ref_0060ac84, label_ref_0060ac8a, label_ref_0060ac90, label_ref_0060ac96,
    label_ref_0060ac9c, label_ref_0060aca2, label_ref_0060aca8, label_ref_0060acae,
    label_ref_0060acb4, label_ref_0060acba, label_ref_0060acc0, label_ref_0060acc6,
    label_ref_0060accc, label_ref_0060acd2};
extern const void* const dat_00607179[14] = {
    label_ref_00607090, label_ref_0060709a, label_ref_006070a0, label_ref_006070aa,
    label_ref_006070b4, label_ref_006070be, label_ref_006070cd, label_ref_006070dc,
    label_ref_006070eb, label_ref_0060710e, label_ref_0060712c, label_ref_00607141,
    label_ref_00607133, label_ref_0060713a};
extern const void* const dat_00606120[47] = {
    label_ref_00605e06, label_ref_00605e0f, label_ref_00605e18, label_ref_00605e21,
    label_ref_00605e2a, label_ref_00605e33, label_ref_00605e3c, label_ref_00605e45,
    label_ref_00605e4e, label_ref_00605e57, label_ref_00605e60, label_ref_00605e69,
    label_ref_00605e72, label_ref_00605e7b, label_ref_00605e84, label_ref_00605e8d,
    label_ref_00605e96, label_ref_00605e9f, label_ref_00605ea8, label_ref_00605eb1,
    label_ref_00605eba, label_ref_00605ec3, label_ref_00605ecc, label_ref_00605ed5,
    label_ref_00605ede, label_ref_00605ee7, label_ref_00605eed, label_ref_00605ef3,
    label_ref_00605ef9, label_ref_00605eff, label_ref_00605f05, label_ref_00605f0b,
    label_ref_00605f11, label_ref_00605f17, label_ref_00605f1d, label_ref_00605f23,
    label_ref_00605f29, label_ref_00605f2f, label_ref_00605f35, label_ref_00605f3b,
    label_ref_00605f41, label_ref_00605f47, label_ref_00605f4d, label_ref_00605f53,
    label_ref_00605f59, label_ref_00605f5f, label_ref_00605f65};
extern const void* const dat_00605bfc[47] = {
    label_ref_006058f9, label_ref_0060590d, label_ref_0060591f, label_ref_00605932,
    label_ref_0060593a, label_ref_00605946, label_ref_00605952, label_ref_00605964,
    label_ref_00605975, label_ref_0060598c, label_ref_0060599e, label_ref_006059aa,
    label_ref_006059b6, label_ref_006059cf, label_ref_006059da, label_ref_006059e6,
    label_ref_006059e6, label_ref_006059ee, label_ref_00605a04, label_ref_006059e6,
    label_ref_00605a26, label_ref_00605a39, label_ref_006059e6, label_ref_006059e6,
    label_ref_00605a44, label_ref_00605a53, label_ref_006059e6, label_ref_00605a9a,
    label_ref_00605aab, label_ref_006059e6, label_ref_00605abc, label_ref_00605aca,
    label_ref_00605adf, label_ref_00605aef, label_ref_006059e6, label_ref_00605afd,
    label_ref_00605b13, label_ref_006059e6, label_ref_00605b2c, label_ref_006059e6,
    label_ref_00605b44, label_ref_006059e6, label_ref_00605b55, label_ref_006059e6,
    label_ref_00605b6b, label_ref_00605b6b, label_ref_00605b6b};
extern const void* const dat_0060a8ee[28] = {
    label_ref_0060a471, label_ref_0060a478, label_ref_0060a480, label_ref_0060a492,
    label_ref_0060a4ab, label_ref_0060a4b0, label_ref_0060a4dc, label_ref_0060a513,
    label_ref_0060a552, label_ref_0060a57c, label_ref_0060a5c2, label_ref_0060a5e6,
    label_ref_0060a666, label_ref_0060a6c8, label_ref_0060a711, label_ref_0060a726,
    label_ref_0060a72b, label_ref_0060a764, label_ref_0060a788, label_ref_0060a7a3,
    label_ref_0060a7d6, label_ref_0060a80a, label_ref_0060a815, label_ref_0060a834,
    label_ref_0060a850, label_ref_0060a85a, label_ref_0060a87d, label_ref_0060a89f};
extern const uint8_t dat_0060a95e[64] = {
    0,  1,  1,  2, 1,  1,  0,  3,  4,  5,  1,  6,  7,  7,  7,  7,  7,  7,  7,  7, 7, 8,
    8,  1,  9,  1, 10, 11, 12, 1,  13, 27, 27, 14, 15, 1,  16, 17, 18, 19, 20, 1, 1, 21,
    22, 22, 23, 1, 1,  24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26};
extern const void* const dat_006e335c[7] = {code_ref_006205ab, code_ref_00620553, code_ref_00620565,
                                            code_ref_0061cb91, code_ref_0061cb82, code_ref_0062058a,
                                            code_ref_00620527};
extern const void* const dat_006f0270[3] = {code_ref_00651d38, code_ref_00652a9d,
                                            code_ref_0069dae1};
extern const void* const dat_006f027c[3] = {code_ref_00651df8, code_ref_00652abd,
                                            code_ref_0069dae1};
extern const void* const dat_006f0294[3] = {code_ref_00651ffc, code_ref_00652b91,
                                            code_ref_0069dae1};
extern const void* const dat_006f02dc[3] = {code_ref_006523bd, code_ref_00652db2,
                                            code_ref_0069dae1};
extern const void* const dat_006f02f4[3] = {code_ref_00652532, code_ref_00652ed0,
                                            code_ref_0069dae1};
extern const void* const dat_006f0318[3] = {code_ref_006528a1, code_ref_00653142,
                                            code_ref_0069dae1};
extern const void* const dat_006f04ac[3] = {code_ref_00651d38, code_ref_00653c75,
                                            code_ref_0069dae1};
extern const void* const dat_006f04b8[3] = {code_ref_00651d38, code_ref_00653d39,
                                            code_ref_0069dae1};
extern const ShaderScope dat_006d6b10[1] = {{-1, nullptr, code_ref_005d5889}};
extern const ShaderScope dat_006dbc38[1] = {{-1, code_ref_005e1020, code_ref_005e1024}};
extern const ShaderScope dat_006dbc48[1] = {{-1, code_ref_005e1147, code_ref_005e114b}};
extern const ShaderProfile dat_006de5b0[44] = {
    {reinterpret_cast<const char*>(storage_ref_006de910), 0xffff0000, 0x0},
    {reinterpret_cast<const char*>(storage_ref_006de908), 0xffff0100, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de900), 0xffff0101, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de8f8), 0xffff0102, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de8f0), 0xffff0103, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de8e8), 0xffff0104, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de8e0), 0xffff0200, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de8d8), 0xffff0202, 0x2},
    {reinterpret_cast<const char*>(storage_ref_006de8d0), 0xffff0203, 0x2},
    {reinterpret_cast<const char*>(storage_ref_006de8c8), 0xffff02ff, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de8c0), 0xffff0201, 0x1},
    {reinterpret_cast<const char*>(storage_ref_006de8b8), 0xffff0300, 0x1},
    {reinterpret_cast<const char*>(storage_ref_006de8b0), 0xffff03ff, 0x1},
    {reinterpret_cast<const char*>(storage_ref_006de8a8), 0xffff0100, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de8a0), 0xffff0101, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de898), 0xffff0102, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de890), 0xffff0103, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de888), 0xffff0104, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de880), 0xffff0200, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de878), 0xffff0202, 0x2},
    {reinterpret_cast<const char*>(storage_ref_006de870), 0xffff0203, 0x2},
    {reinterpret_cast<const char*>(storage_ref_006de868), 0xffff02ff, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de860), 0xffff0201, 0x1},
    {reinterpret_cast<const char*>(storage_ref_006de858), 0xffff0300, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de850), 0xffff03ff, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de84c), 0x54580000, 0x0},
    {reinterpret_cast<const char*>(storage_ref_006de844), 0x54580100, 0x6},
    {reinterpret_cast<const char*>(storage_ref_006de840), 0xfffe0000, 0x0},
    {reinterpret_cast<const char*>(storage_ref_006de838), 0xfffe0100, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de830), 0xfffe0101, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de828), 0xfffe0200, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de820), 0xfffe0202, 0x2},
    {reinterpret_cast<const char*>(storage_ref_006de818), 0xfffe02ff, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de810), 0xfffe0201, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de808), 0xfffe0300, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de800), 0xfffe03ff, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de7f8), 0xfffe0100, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de7f0), 0xfffe0101, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de7e8), 0xfffe0200, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de7e0), 0xfffe0202, 0x2},
    {reinterpret_cast<const char*>(storage_ref_006de7d8), 0xfffe02ff, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de7d0), 0xfffe0201, 0x1},
    {reinterpret_cast<const char*>(storage_ref_006de7c8), 0xfffe0300, 0x3},
    {reinterpret_cast<const char*>(storage_ref_006de7c0), 0xfffe03ff, 0x3}};
extern const ShaderOpcode dat_006e0070[84] = {
    {reinterpret_cast<const char*>(storage_ref_006e1fb4),
     0x0,
     {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}},
    {reinterpret_cast<const char*>(storage_ref_006e1fb0),
     0x1,
     {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2}},
    {reinterpret_cast<const char*>(storage_ref_006e1fac),
     0x2,
     {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1fa8),
     0x3,
     {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1fa4),
     0x4,
     {0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4}},
    {reinterpret_cast<const char*>(storage_ref_006e1fa0),
     0x5,
     {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1f9c),
     0x6,
     {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2, 0x2,
      0x2, 0x2}},
    {reinterpret_cast<const char*>(storage_ref_006e1f98),
     0x7,
     {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2, 0x2,
      0x2, 0x2}},
    {reinterpret_cast<const char*>(storage_ref_006e1f94),
     0x8,
     {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1f90),
     0x9,
     {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xffffffff, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1f8c),
     0xa,
     {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x3, 0x3, 0x3,
      0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1f88),
     0xb,
     {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x3, 0x3, 0x3,
      0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1f84),
     0xc,
     {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1f80),
     0xd,
     {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006d6cf8),
     0xe,
     {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2, 0x2,
      0x2, 0x2}},
    {reinterpret_cast<const char*>(storage_ref_006d6cec),
     0xf,
     {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2, 0x2,
      0x2, 0x2}},
    {reinterpret_cast<const char*>(storage_ref_006e1f7c),
     0x10,
     {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1f78),
     0x11,
     {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1f74),
     0x12,
     {0xffffffff, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4}},
    {reinterpret_cast<const char*>(storage_ref_006e1f70),
     0x13,
     {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2, 0x2,
      0x2, 0x2}},
    {reinterpret_cast<const char*>(storage_ref_006e1f68),
     0x14,
     {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x3, 0x3, 0x3,
      0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1f60),
     0x15,
     {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x3, 0x3, 0x3,
      0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1f58),
     0x16,
     {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x3, 0x3, 0x3,
      0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1f50),
     0x17,
     {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x3, 0x3, 0x3,
      0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1f48),
     0x18,
     {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x3, 0x3, 0x3,
      0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1f40),
     0x19,
     {0xffffffff, 0xfffffffb, 0xfffffffb, 0xfffffffb, 0xfffffffb, 0xfffffffb, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffb, 0xfffffffb, 0xfffffffb,
      0xfffffffb}},
    {reinterpret_cast<const char*>(storage_ref_006e1f38),
     0x1a,
     {0xffffffff, 0xfffffffa, 0xfffffffa, 0xfffffffa, 0xfffffffa, 0xfffffffa, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffa, 0xfffffffa, 0xfffffffa,
      0xfffffffa}},
    {reinterpret_cast<const char*>(storage_ref_006e1f30),
     0x1b,
     {0xffffffff, 0xfffffffa, 0xfffffffa, 0xfffffffa, 0xfffffffa, 0xfffffffa, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffa,
      0xfffffffa}},
    {reinterpret_cast<const char*>(storage_ref_006e1f2c),
     0x1c,
     {0xffffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0x0, 0x0, 0x0, 0x0}},
    {reinterpret_cast<const char*>(storage_ref_006e1f24),
     0x1d,
     {0xffffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0x0, 0x0}},
    {reinterpret_cast<const char*>(storage_ref_006e1f1c),
     0x1e,
     {0xffffffff, 0xfffffffb, 0xfffffffb, 0xfffffffb, 0xfffffffb, 0xfffffffb, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffb, 0xfffffffb, 0xfffffffb,
      0xfffffffb}},
    {reinterpret_cast<const char*>(storage_ref_006e1f18),
     0x1f,
     {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x1, 0x1, 0x1,
      0x1, 0x1}},
    {reinterpret_cast<const char*>(storage_ref_006d6ce8),
     0x20,
     {0xffffffff, 0x3, 0x3, 0x3, 0x3, 0x3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x3, 0x3,
      0x3, 0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1f14),
     0x21,
     {0xffffffff, 0x3, 0x3, 0x3, 0x3, 0x3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x3, 0x3,
      0x3, 0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1f10),
     0x22,
     {0xffffffff, 0x4, 0x4, 0x4, 0x4, 0x4, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1f0c),
     0x23,
     {0xffffffff, 0x2, 0x2, 0x2, 0x2, 0x2, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2,
      0x2, 0x2, 0x2}},
    {reinterpret_cast<const char*>(storage_ref_006e1f08),
     0x24,
     {0xffffffff, 0x2, 0x2, 0x2, 0x2, 0x2, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2,
      0x2, 0x2, 0x2}},
    {reinterpret_cast<const char*>(storage_ref_006e1f00),
     0x25,
     {0xffffffff, 0x4, 0x4, 0x4, 0x2, 0x2, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x4, 0x4,
      0x4, 0x2, 0x2}},
    {reinterpret_cast<const char*>(storage_ref_006e1efc),
     0x26,
     {0xffffffff, 0xfffffffb, 0xfffffffb, 0xfffffffb, 0xfffffffb, 0xfffffffb, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffb, 0xfffffffb, 0xfffffffb,
      0xfffffffb}},
    {reinterpret_cast<const char*>(storage_ref_006e1ef4),
     0x27,
     {0xffffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0x0, 0x0, 0x0, 0x0}},
    {reinterpret_cast<const char*>(storage_ref_006dfd38),
     0x28,
     {0xffffffff, 0xfffffffb, 0xfffffffb, 0xfffffffb, 0xfffffffb, 0xfffffffb, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffb, 0xfffffffb, 0xfffffffb, 0xfffffffb,
      0xfffffffb}},
    {reinterpret_cast<const char*>(storage_ref_006dfd10),
     0x2a,
     {0xffffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x0, 0x0,
      0x0, 0x0, 0x0}},
    {reinterpret_cast<const char*>(storage_ref_006dfd08),
     0x2b,
     {0xffffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x0, 0x0,
      0x0, 0x0, 0x0}},
    {reinterpret_cast<const char*>(storage_ref_006e1eec),
     0x2c,
     {0xffffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0x0, 0x0, 0x0, 0x0}},
    {reinterpret_cast<const char*>(storage_ref_006e1ee4),
     0x60,
     {0xffffffff, 0xffffffff, 0xfffffffb, 0xfffffffb, 0xfffffffb, 0xfffffffb, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffb, 0xfffffffb, 0xfffffffb,
      0xfffffffb}},
    {reinterpret_cast<const char*>(storage_ref_006e1edc),
     0x2e,
     {0xffffffff, 0x2, 0x2, 0x2, 0x2, 0x2, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1ed0),
     0x40,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x1, 0x1, 0x1,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1ec8),
     0x40,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0x2, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1ec0),
     0x41,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x1, 0x1, 0x1, 0x1,
      0x1, 0x1, 0x1, 0x1, 0x1}},
    {reinterpret_cast<const char*>(storage_ref_006e1ebc),
     0x42,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x1, 0x1, 0x1,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1eb4),
     0x42,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1eac),
     0x10042,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0x3, 0x3, 0x3, 0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1ea4),
     0x20042,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0x3, 0x3, 0x3, 0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1e9c),
     0x43,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2, 0x2,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1e94),
     0x44,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2, 0x2,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1e88),
     0x45,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2, 0x2,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1e7c),
     0x46,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2, 0x2,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1e70),
     0x47,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2, 0x2,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1e64),
     0x48,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2, 0x2,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1e58),
     0x49,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2, 0x2,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1e4c),
     0x4a,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2, 0x2,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1e40),
     0x4c,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x3, 0x3, 0x3,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1e30),
     0x4d,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2, 0x2,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1e28),
     0x4e,
     {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1e20),
     0x4f,
     {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1e1c),
     0x50,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x4, 0x4, 0x4, 0x4,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006dfbd8),
     0x51,
     {0xfffffffd, 0xfffffffd, 0xfffffffd, 0xfffffffd, 0xfffffffd, 0xfffffffd, 0xfffffffd,
      0xfffffffd, 0xfffffffd, 0xfffffffd, 0xfffffffd, 0xfffffffd, 0xfffffffd, 0xfffffffd,
      0xfffffffd}},
    {reinterpret_cast<const char*>(storage_ref_006e1e14),
     0x30,
     {0xffffffff, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffe, 0xfffffffe, 0xfffffffe,
      0xfffffffe}},
    {reinterpret_cast<const char*>(storage_ref_006e1e0c),
     0x2f,
     {0xffffffff, 0xfffffffc, 0xfffffffc, 0xfffffffc, 0xfffffffc, 0xfffffffc, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffc, 0xfffffffc, 0xfffffffc, 0xfffffffc,
      0xfffffffc}},
    {reinterpret_cast<const char*>(storage_ref_006e1e00),
     0x52,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1df4),
     0x53,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1de4),
     0x54,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0x2, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1ddc),
     0x55,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1dd4),
     0x56,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1dc8),
     0x57,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0x1, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1dc4),
     0x58,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x4, 0x4,
      0x4, 0x4, 0x4, 0x4, 0x4, 0x4}},
    {reinterpret_cast<const char*>(storage_ref_006e1dc0),
     0x59,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0x3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
    {reinterpret_cast<const char*>(storage_ref_006e1db8),
     0x5a,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0x4, 0x4, 0x4, 0x4, 0x4}},
    {reinterpret_cast<const char*>(storage_ref_006e1db4),
     0x5b,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2, 0x2, 0x2}},
    {reinterpret_cast<const char*>(storage_ref_006e1db0),
     0x5c,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x2, 0x2, 0x2, 0x2}},
    {reinterpret_cast<const char*>(storage_ref_006e1da8),
     0x5d,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x5, 0x5, 0x5, 0x5}},
    {reinterpret_cast<const char*>(storage_ref_006e1da0),
     0x5e,
     {0xffffffff, 0xffffffff, 0x3, 0x3, 0x3, 0x3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0x3, 0x3, 0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1d98),
     0x5f,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x3, 0x3, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x3, 0x3}},
    {reinterpret_cast<const char*>(storage_ref_006e1d90),
     0xfffd,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}}};
extern const ShaderConditionOpcode dat_006e16c0[2] = {
    {reinterpret_cast<const char*>(storage_ref_006e1d88),
     0x29,
     {0xffffffff, 0xffffffff, 0xfffffffa, 0xfffffffa, 0xfffffffa, 0xfffffffa, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffa, 0xfffffffa, 0xfffffffa,
      0xfffffffa, 0x0}},
    {reinterpret_cast<const char*>(storage_ref_006e1d80),
     0x2d,
     {0xffffffff, 0xffffffff, 0xfffffffa, 0xfffffffa, 0xfffffffa, 0xfffffffa, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffa, 0xfffffffa, 0xfffffffa,
      0xfffffffa, 0x0}}};
extern const ShaderRegister dat_006e1750[21] = {
    {reinterpret_cast<const char*>(storage_ref_006bcaf4),
     0x1,
     {0x10, 0x10, 0x10, 0x10, 0xfffffff0, 0xfffffff0, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0xfffffff6,
      0xfffffff2},
     0x0},
    {reinterpret_cast<const char*>(storage_ref_006bcb08),
     0x0,
     {0xc, 0xc, 0x20, 0x20, 0x20, 0x20, 0x2, 0x2, 0x2, 0x6, 0xc, 0x20, 0x20, 0x20, 0x20},
     0x0},
    {reinterpret_cast<const char*>(storage_ref_006c584c),
     0x2,
     {0xffffe000, 0xffffe000, 0xffffe000, 0xffffe000, 0xffffe000, 0xffffe000, 0x8, 0x8, 0x8, 0x8,
      0x20, 0x20, 0x2000, 0xe0, 0x2000},
     0x0},
    {reinterpret_cast<const char*>(storage_ref_006d2380),
     0x3,
     {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff},
     0x0},
    {reinterpret_cast<const char*>(storage_ref_006bcb14),
     0x3,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x4, 0x4, 0x4, 0x6,
      0x8, 0x8, 0x8, 0xffffffff, 0xffffffff},
     0x0},
    {reinterpret_cast<const char*>(storage_ref_006e1d78),
     0xfffffffd,
     {0x0, 0x0, 0x0, 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff},
     0x0},
    {reinterpret_cast<const char*>(storage_ref_006e1d70),
     0xfffffffc,
     {0x0, 0x0, 0x0, 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff},
     0x1},
    {reinterpret_cast<const char*>(storage_ref_006e1d68),
     0xfffffffb,
     {0x0, 0x0, 0x0, 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff},
     0x1},
    {reinterpret_cast<const char*>(storage_ref_006e1d64),
     0x5,
     {0x2, 0x2, 0x2, 0x2, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff},
     0x0},
    {reinterpret_cast<const char*>(storage_ref_006e1d60),
     0x6,
     {0x8, 0x8, 0x8, 0x8, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff},
     0x0},
    {reinterpret_cast<const char*>(storage_ref_006bcb0c),
     0x7,
     {0xffffffff, 0x10, 0x10, 0x800, 0x10, 0x800, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0x10, 0x800, 0x10, 0x800},
     0x0},
    {reinterpret_cast<const char*>(storage_ref_006e1d5c),
     0x8,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0x4, 0x4, 0x4, 0x4, 0x4},
     0x0},
    {reinterpret_cast<const char*>(storage_ref_006e1d54),
     0x9,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0x0, 0x0, 0x0, 0x0, 0x0},
     0x1},
    {reinterpret_cast<const char*>(storage_ref_006bcb10),
     0xa,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x4, 0x4, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0x10, 0x10, 0x10, 0x10, 0x10},
     0x0},
    {reinterpret_cast<const char*>(storage_ref_006bcb04),
     0xe,
     {0xffffffff, 0x10, 0x10, 0x800, 0x10, 0x800, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0x10, 0x10, 0x800, 0x10, 0x800},
     0x1},
    {reinterpret_cast<const char*>(storage_ref_006e1d50),
     0xf,
     {0xffffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0x0, 0x0},
     0x1},
    {reinterpret_cast<const char*>(storage_ref_006e1d48),
     0xfffffffa,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x0, 0x0},
     0x0},
    {reinterpret_cast<const char*>(storage_ref_006e1d40),
     0xfffffff9,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x0, 0x0},
     0x1},
    {reinterpret_cast<const char*>(storage_ref_006e1d3c),
     0x12,
     {0xffffffff, 0x800, 0x800, 0x800, 0x800, 0x800, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0x800, 0x800, 0x800, 0x800},
     0x1},
    {reinterpret_cast<const char*>(storage_ref_006bcb18),
     0x13,
     {0xffffffff, 0xffffffff, 0x1, 0x1, 0x1, 0x1, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff, 0x1, 0x1, 0x1, 0x1},
     0x0},
    {reinterpret_cast<const char*>(storage_ref_006e1d38),
     0x6,
     {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff4, 0xfffffff0, 0xffffffff,
      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
      0xffffffff},
     0x0}};
extern const uint32_t dat_006eb538[24] = {0, 15, 0,  10, 8,  10, 16, 10, 32, 10, 0,  14,
                                          8, 14, 16, 14, 32, 14, 0,  8,  16, 8,  32, 8};
extern const char* const dat_006eb8f0[5] = {reinterpret_cast<const char*>(storage_ref_006eb888),
                                            reinterpret_cast<const char*>(storage_ref_006eb87c),
                                            reinterpret_cast<const char*>(storage_ref_006eb870),
                                            reinterpret_cast<const char*>(storage_ref_006eb864),
                                            reinterpret_cast<const char*>(storage_ref_006eb85c)};
extern const ShaderInterfaceId dat_006f0004 = {
    0x8ba5fb08, 0x5195, 0x40e2, {172, 88, 13, 152, 156, 58, 1, 2}};
extern const int16_t dat_0070ff08[48] = {-1, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0,
                                         5,  5, 5, 5,  6,  6,  6,  6,  7,  7,  7,  8,  8, 8, 9, 9,
                                         9,  9, 9, 10, 10, 10, 11, 11, 12, 12, 13, 13, 4, 1, 2, 3};
extern const int16_t dat_0070ff68[48] = {2, 2, 2, 2, 3, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1,
                                         1, 3, 1, 4, 1, 2, 2, 2, 1, 3, 3, 1, 3, 3, 1, 3,
                                         3, 3, 3, 1, 3, 3, 1, 3, 1, 3, 1, 5, 1, 1, 1, 1};
extern const int16_t dat_0070ffc8[80] = {0,  0, 0, 0,  5, 6,  0, 0, 0,  0,  11, 12, 13, 14, 15, 0,
                                         45, 1, 2, 46, 0, 0,  0, 0, 0,  0,  18, 16, 7,  20, 24, 0,
                                         0,  0, 0, 0,  0, 44, 8, 9, 10, 47, 4,  0,  0,  21, 22, 23,
                                         0,  0, 0, 0,  0, 0,  0, 0, 0,  0,  0,  0,  0,  0,  17, 25,
                                         26, 0, 0, 0,  0, 0,  0, 0, 0,  0,  0,  0,  19, 0,  43, 0};
extern const int16_t dat_00710068[16] = {15, 26, 27, 42, 28, 29, 30, 31,
                                         32, 33, 34, 35, 36, 37, 0,  0};
extern const int16_t dat_00710088[80] = {
    -101, -244, -244, -243, 0,    0,   -31, -244, -244, -31,  0,    0,    0,   0,   0, 0,
    0,    0,    0,    0,    -245, -2,  -31, -31,  -31,  -31,  0,    0,    0,   0,   0, -36,
    -19,  -52,  -247, -237, -60,  0,   0,   0,    0,    0,    0,    -244, 6,   0,   0, 0,
    -31,  -31,  -31,  -31,  -31,  -31, -31, -31,  -31,  -31,  -31,  -31,  -31, 10,  0, 0,
    0,    -36,  -36,  -19,  -19,  -19, -19, -52,  -52,  -247, -237, -58,  0,   -31, 0, 0};
extern const int16_t dat_00710128[80] = {
    0, 0, 0, 0, 0, 0,  0,  0,  0,  0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  53, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 19, 49, 57, 86, 4, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,  0,  0,  0,  0, 0, 7, 13, 25, 31, 37, 43, 55, 68, 80, 92, 0, 0, 0, 0, 0};
extern const int16_t dat_007101c8[16] = {0,   109, 59, 0,  -4, 0,  -8, -21,
                                         -32, -24, 16, 45, 42, 46, 0,  0};
extern const int16_t dat_007101e8[372] = {
    77, 27, 23, 60, 42, 40, 48, 29, 54, 22, 55, 49, 25, 28, 24, 45, 46, 47, 44, 30, 67, 68, 69, 70,
    51, 33, 50, 56, 57, 65, 66, 34, 71, 72, 16, 41, 19, 31, 43, 58, 63, 64, 27, 32, 27, 42, 27, 62,
    29, 35, 29, 76, 29, 3,  28, 36, 28, 38, 28, 27, 30, 27, 20, 27, 27, 29, 33, 29, 37, 29, 29, 28,
    34, 28, 73, 28, 28, 30, 31, 30, 39, 30, 30, 33, 32, 33, 40, 33, 33, 34, 35, 34, 41, 34, 34, 31,
    36, 31, 38, 31, 31, 32, 75, 32, 74, 32, 32, 35, 0,  37, 17, 18, 35, 36, 0,  38, 38, 39, 36, 0,
    38, 39, 0,  78, 0,  0,  37, 40, 0,  0,  0,  37, 0,  41, 0,  0,  0,  0,  39, 0,  0,  0,  0,  39,
    40, 0,  0,  0,  0,  40, 41, 0,  61, 0,  0,  41, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
    13, 14, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  59, 0,  59, 52, 53, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    21, 0,  0,  0,  0,  0,  0,  16, 19, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  27, 27, 27, 27, 27, 27, 29, 29, 29, 29, 29, 29, 28, 28, 28,
    28, 28, 28, 30, 30, 30, 30, 30, 30, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 31, 31, 31,
    31, 31, 31, 32, 32, 32, 32, 32, 32, 0,  0,  35, 35, 35, 35, 0,  0,  36, 36, 36, 36, 38, 38, 0,
    0,  0,  0,  0,  0,  0,  37, 37, 37, 37, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  39, 39, 0,  0,
    0,  0,  0,  40, 0,  0,  0,  0,  0,  41, 0,  0};
extern const int16_t dat_007104d0[372] = {
    58,  0,   33,  63,  0,   9,   42,  0,   60,  40,  62,  47,  43,  0,   45,  23,  24,  25,  22,
    0,   52,  53,  54,  55,  43,  0,   45,  274, 275, 50,  51,  0,   56,  57,  278, 280, 279, 0,
    40,  276, 48,  49,  41,  0,   43,  41,  45,  41,  41,  0,   43,  41,  45,  0,   41,  0,   43,
    0,   45,  58,  41,  60,  3,   62,  63,  58,  41,  60,  0,   62,  63,  58,  41,  60,  58,  62,
    63,  58,  41,  60,  0,   62,  63,  58,  41,  60,  0,   62,  63,  58,  41,  60,  0,   62,  63,
    58,  41,  60,  41,  62,  63,  58,  60,  60,  59,  62,  63,  58,  -1,  41,  1,   2,   63,  58,
    -1,  58,  7,   8,   63,  -1,  63,  41,  -1,  77,  -1,  -1,  58,  41,  -1,  -1,  -1,  63,  -1,
    41,  -1,  -1,  -1,  -1,  58,  -1,  -1,  -1,  -1,  63,  58,  -1,  -1,  -1,  -1,  63,  58,  -1,
    43,  -1,  -1,  63,  257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, -1,
    -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  277, -1,  277, 272, 273, -1,  -1,  -1,  -1,  -1,  -1,
    -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  271, -1,  -1,  -1,  -1,  -1,  -1,
    278, 279, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1,  -1,  -1,  -1,  -1,  -1,  -1,  272, 273, 274, 275, 276, 277, 272, 273, 274, 275, 276, 277,
    272, 273, 274, 275, 276, 277, 272, 273, 274, 275, 276, 277, 272, 273, 274, 275, 276, 277, 272,
    273, 274, 275, 276, 277, 272, 273, 274, 275, 276, 277, 272, 273, 274, 275, 276, 277, -1,  -1,
    274, 275, 276, 277, -1,  -1,  274, 275, 276, 277, 276, 277, -1,  -1,  -1,  -1,  -1,  -1,  -1,
    274, 275, 276, 277, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  276, 277, -1,  -1,  -1,
    -1,  -1,  277, -1,  -1,  -1,  -1,  -1,  277, 0,   0};
extern const int16_t dat_007107b8[64] = {
    -1, 0,  0,  1,  1,  2, 2,  2,  3,  4,  4,  6,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,
    7,  7,  11, 11, 8,  8, 8,  8,  25, 25, 24, 24, 27, 27, 28, 28, 21, 21, 19, 19, 19, 17,
    17, 17, 17, 17, 17, 9, 10, 12, 13, 14, 15, 16, 18, 20, 22, 23, 5,  26, 29, 0};
extern const int16_t dat_00710838[64] = {2, 0, 1,  1,  2,  1, 1, 1, 2, 1, 2, 1, 4, 1, 2, 4,
                                         6, 8, 10, 10, 10, 4, 2, 4, 1, 3, 1, 2, 2, 3, 1, 3,
                                         1, 4, 1,  3,  1,  1, 1, 1, 1, 2, 2, 1, 2, 2, 1, 2,
                                         2, 1, 1,  1,  1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};
extern const int16_t dat_007108b8[132] = {
    0,  7,  0,  49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 0,  0,  0,  0,  3,  5,  6,  9,
    11, 13, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  60, 8,  10, 61, 0,  0,  0,  0,  0,  26,
    0,  4,  14, 0,  0,  0,  0,  0,  0,  0,  0,  22, 0,  27, 28, 0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  36, 37, 0,  0,  12, 31, 29, 25, 15, 0,  0,  0,  62, 0,  0,  0,
    43, 46, 0,  0,  0,  40, 38, 39, 21, 23, 33, 0,  0,  0,  0,  44, 47, 45, 48, 0,  41, 42,
    0,  35, 16, 0,  0,  0,  0,  0,  0,  0,  0,  17, 0,  0,  0,  0,  0,  0,  18, 19, 20, 0};
extern const int16_t dat_007109c0[32] = {16, 17, 18, 19, 20, 40, 21, 22, 41, 23, 24,
                                         46, 25, 26, 27, 28, 29, 87, 30, 92, 31, 96,
                                         32, 33, 42, 43, 44, 74, 75, 89, 0,  0};
extern const int16_t dat_00710a00[132] = {
    -38,  0,    -266, 0,    0,   0,   0,   0,   0,    0,    0,    0,    0,    0,    -20,
    -33,  0,    -38,  0,    0,   0,   0,   0,   0,    -266, -266, -266, -266, -266, -266,
    -266, -266, -33,  -33,  0,   0,   0,   0,   -266, -266, -83,  -28,  -12,  0,    -10,
    0,    0,    -9,   -6,   -4,  -1,  2,   4,   9,    15,   0,    16,   0,    0,    -246,
    -125, -266, -266, -266, -33, -33, -33, -33, -39,  -36,  -248, -33,  0,    0,    -32,
    19,   0,    0,    0,    0,   0,   21,  22,  24,   0,    -240, -240, 25,   0,    0,
    -207, -207, 28,   0,    0,   0,   0,   0,   0,    -246, -33,  -33,  -33,  0,    0,
    0,    0,    -39,  0,    0,   -36, 0,   0,   31,   33,   35,   37,   -33,  -33,  -39,
    -36,  0,    38,   39,   40,  -33, -39, -36, 0,    0,    0,    0};
extern const int16_t dat_00710b08[132] = {
    88, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 89, 0, 0, 0,  0, 0, 0, 0, 0, 0,
    0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 14, 0, 0,  0, 0, 27, 0, 0, 0, 0, 0, 0,
    0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,  0, 0, 0,  6, 0, 0, 0, 0, 0,
    0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0,
    0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,  0, 0, 0,  0, 0, 0};
extern const int16_t dat_00710c10[32] = {0,   0, 75, 0,   0, 17, 79,  41,  -15, 0, 0,
                                         119, 0, 0,  0,   0, 0,  -97, 0,   -99, 0, 0,
                                         0,   0, 92, -23, 5, -2, 0,   -53, 0,   0};
extern const int16_t dat_00710c50[296] = {
    38, 32,  15,  34,  85,  14,  86,  90,  59,  91,  115, 116, 39,  60,  30, 57,  58,  55,  56, 35,
    15, 124, 123, 34,  37,  94,  95,  24,  130, 129, 37,  84,  104, 106, 61, 62,  72,  63,  64, 78,
    65, 32,  32,  66,  32,  32,  67,  32,  68,  80,  81,  82,  83,  69,  30, 30,  97,  30,  30, 70,
    71, 98,  99,  37,  73,  100, 101, 24,  102, 107, 24,  24,  110, 88,  93, 117, 72,  118, 77, 119,
    79, 120, 125, 126, 127, 112, 113, 114, 1,   2,   103, 105, 45,  36,  32, 108, 109, 111, 0,  34,
    0,  76,  121, 122, 73,  0,   0,   30,  0,   0,   128, 0,   88,  0,   0,  93,  47,  47,  47, 47,
    47, 47,  47,  47,  88,  93,  0,   0,   0,   0,   0,   88,  93,  3,   4,  5,   6,   7,   8,  9,
    10, 11,  12,  13,  48,  49,  50,  51,  52,  53,  54,  0,   0,   0,   0,  0,   0,   0,   0,  0,
    0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,   0,   0,   0,  0,
    0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,   0,   0,   0,  0,
    0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,   0,   0,   1,  2,
    3,  4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  37,  84,  0,   37, 0,   34,  37,  3,  4,
    5,  6,   7,   8,   9,   10,  11,  12,  13,  0,   0,   0,   0,   0,   0,  0,   0,   32,  32, 32,
    32, 32,  32,  32,  32,  32,  32,  32,  32,  32,  30,  30,  30,  30,  30, 30,  30,  30,  30, 30,
    30, 30,  30,  24,  24,  24,  24,  24,  24,  24,  24,  24,  24,  24,  24, 24};
extern const int16_t dat_00710ea0[296] = {
    33,  0,   40,  269, 43,  43,  45,  43,  91,  45,  107, 110, 45,  41,  0,   38,  39,  32,  33,
    2,   40,  120, 119, 269, 270, 273, 274, 0,   127, 126, 270, 271, 85,  86,  46,  45,  59,  46,
    44,  62,  44,  40,  41,  44,  43,  44,  44,  46,  44,  64,  65,  66,  67,  44,  40,  41,  71,
    43,  44,  44,  44,  93,  43,  270, 59,  44,  44,  40,  44,  44,  43,  44,  44,  68,  69,  44,
    99,  44,  61,  44,  63,  44,  44,  44,  44,  100, 101, 102, 0,   0,   85,  86,  17,  14,  93,
    90,  91,  99,  -1,  93,  -1,  60,  117, 118, 99,  -1,  -1,  93,  -1,  -1,  125, -1,  107, -1,
    -1,  110, 24,  25,  26,  27,  28,  29,  30,  31,  119, 120, -1,  -1,  -1,  -1,  -1,  126, 127,
    258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 25,  26,  27,  28,  29,  30,  31,  -1,
    -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  256, 257, 258, 259, 260, 261, 262, 263, 264, 265,
    266, 267, 268, 270, 271, -1,  270, -1,  269, 270, 258, 259, 260, 261, 262, 263, 264, 265, 266,
    267, 268, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  256, 257, 258, 259, 260, 261, 262, 263, 264,
    265, 266, 267, 268, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 256, 257,
    258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268};
extern const uint16_t dat_006d6938[128] = {
    32,  32,  32,  32,  32,  32,  32,  32,  104, 40,  40,  40,  40,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  72,  16,  16,  16,  16,  16,  16,
    16,  16,  16,  16,  16,  16,  16,  16,  16,  132, 132, 132, 132, 132, 132, 132, 132, 132, 132,
    16,  16,  16,  16,  16,  16,  16,  385, 385, 385, 385, 385, 385, 257, 257, 257, 257, 257, 257,
    257, 257, 257, 257, 257, 257, 257, 257, 257, 257, 257, 257, 257, 257, 16,  16,  16,  16,  16,
    16,  386, 386, 386, 386, 386, 386, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258,
    258, 258, 258, 258, 258, 258, 258, 258, 16,  16,  16,  16,  32,  0};
extern const uint8_t dat_006d6a38[128] = {
    1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,  15,  16,  17,  18,  19,
    20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,
    39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,
    58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,
    77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
    96,  97,  98,  99,  100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
    115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 0};
extern const QualifiedLocale dat_006dad30[27] = {
    {0x40a,
     {48, 52, 48, 97, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db330),
     {69, 83, 80, 0},
     reinterpret_cast<const char*>(storage_ref_006db328),
     {69, 83, 80, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x40b,
     {48, 52, 48, 98, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db320),
     {70, 73, 78, 0},
     reinterpret_cast<const char*>(storage_ref_006db318),
     {70, 73, 78, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x40c,
     {48, 52, 48, 99, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db310),
     {70, 82, 65, 0},
     reinterpret_cast<const char*>(storage_ref_006db308),
     {70, 82, 65, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x40f,
     {48, 52, 48, 102, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2fc),
     {73, 83, 76, 0},
     reinterpret_cast<const char*>(storage_ref_006db2f4),
     {73, 83, 76, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x41d,
     {48, 52, 49, 100, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2ec),
     {83, 86, 69, 0},
     reinterpret_cast<const char*>(storage_ref_006db2e4),
     {83, 87, 69, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x42d,
     {48, 52, 50, 100, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2dc),
     {69, 85, 81, 0},
     reinterpret_cast<const char*>(storage_ref_006db328),
     {69, 83, 80, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x80a,
     {48, 56, 48, 97, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2d4),
     {69, 83, 77, 0},
     reinterpret_cast<const char*>(storage_ref_006db2cc),
     {77, 69, 88, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x80c,
     {48, 56, 48, 99, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db310),
     {70, 82, 66, 0},
     reinterpret_cast<const char*>(storage_ref_006db2c4),
     {66, 69, 76, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0xc07,
     {48, 99, 48, 55, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2bc),
     {68, 69, 65, 0},
     reinterpret_cast<const char*>(storage_ref_006db2b4),
     {65, 85, 84, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0xc09,
     {48, 99, 48, 57, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2ac),
     {69, 78, 65, 0},
     reinterpret_cast<const char*>(storage_ref_006db2a0),
     {65, 85, 83, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0xc0a,
     {48, 99, 48, 97, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db288),
     {69, 83, 78, 0},
     reinterpret_cast<const char*>(storage_ref_006db328),
     {69, 83, 80, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0xc0c,
     {48, 99, 48, 99, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db310),
     {70, 82, 67, 0},
     reinterpret_cast<const char*>(storage_ref_006db280),
     {67, 65, 78, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x100a,
     {49, 48, 48, 97, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2d4),
     {69, 83, 71, 0},
     reinterpret_cast<const char*>(storage_ref_006db274),
     {71, 84, 77, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x100c,
     {49, 48, 48, 99, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db310),
     {70, 82, 83, 0},
     reinterpret_cast<const char*>(storage_ref_006db268),
     {67, 72, 69, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x140a,
     {49, 52, 48, 97, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2d4),
     {69, 83, 67, 0},
     reinterpret_cast<const char*>(storage_ref_006db25c),
     {67, 82, 73, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x140c,
     {49, 52, 48, 99, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db310),
     {70, 82, 76, 0},
     reinterpret_cast<const char*>(storage_ref_006db250),
     {76, 85, 88, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x180a,
     {49, 56, 48, 97, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2d4),
     {69, 83, 65, 0},
     reinterpret_cast<const char*>(storage_ref_006db248),
     {80, 65, 78, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x1c09,
     {49, 99, 48, 57, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2ac),
     {69, 78, 83, 0},
     reinterpret_cast<const char*>(storage_ref_006db238),
     {90, 65, 70, 0},
     {52, 51, 55, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x1c0a,
     {49, 99, 48, 97, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2d4),
     {69, 83, 68, 0},
     reinterpret_cast<const char*>(storage_ref_006db224),
     {68, 79, 77, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x200a,
     {50, 48, 48, 97, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2d4),
     {69, 83, 86, 0},
     reinterpret_cast<const char*>(storage_ref_006db218),
     {86, 69, 78, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x240a,
     {50, 52, 48, 97, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2d4),
     {69, 83, 79, 0},
     reinterpret_cast<const char*>(storage_ref_006db20c),
     {67, 79, 76, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x280a,
     {50, 56, 48, 97, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2d4),
     {69, 83, 82, 0},
     reinterpret_cast<const char*>(storage_ref_006db204),
     {80, 69, 82, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x2c0a,
     {50, 99, 48, 97, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2d4),
     {69, 83, 83, 0},
     reinterpret_cast<const char*>(storage_ref_006db1f8),
     {65, 82, 71, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x300a,
     {51, 48, 48, 97, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2d4),
     {69, 83, 70, 0},
     reinterpret_cast<const char*>(storage_ref_006db1f0),
     {69, 67, 85, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x340a,
     {51, 52, 48, 97, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2d4),
     {69, 83, 76, 0},
     reinterpret_cast<const char*>(storage_ref_006db1e8),
     {67, 72, 76, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x380a,
     {51, 56, 48, 97, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2d4),
     {69, 83, 89, 0},
     reinterpret_cast<const char*>(storage_ref_006db1e0),
     {85, 82, 89, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}},
    {0x3c0a,
     {51, 99, 48, 97, 0, 0, 0, 0},
     reinterpret_cast<const char*>(storage_ref_006db2d4),
     {69, 83, 90, 0},
     reinterpret_cast<const char*>(storage_ref_006db1d4),
     {80, 82, 89, 0},
     {56, 53, 48, 0, 0, 0, 0, 0},
     {49, 50, 53, 50, 0, 0, 0, 0}}};
extern const uint16_t dat_006db34c[10] = {3084, 3098, 4103, 1078, 2060,
                                          1069, 1027, 4108, 2064, 2077};
extern const LocaleAlias dat_006db360[23] = {
    {reinterpret_cast<const char*>(storage_ref_006db504), {85, 83, 65, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db4fc), {71, 66, 82, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db4f4), {67, 72, 78, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db4ec), {67, 90, 69, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db4e4), {71, 66, 82, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db4d4), {71, 66, 82, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db4cc), {78, 76, 68, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db4c0), {72, 75, 71, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db4b4), {78, 90, 76, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db4b0), {78, 90, 76, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db4a4), {67, 72, 78, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db498), {67, 72, 78, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db48c), {80, 82, 73, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db484), {83, 86, 75, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db474), {90, 65, 70, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db468), {75, 79, 82, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db458), {90, 65, 70, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db44c), {75, 79, 82, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db438), {84, 84, 79, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db720), {71, 66, 82, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db428), {71, 66, 82, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db418), {85, 83, 65, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db71c), {85, 83, 65, 0}}};
extern const LocaleAlias dat_006db510[65] = {
    {reinterpret_cast<const char*>(storage_ref_006dbb20), {69, 78, 85, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dbb0c), {69, 78, 85, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dbaf8), {69, 78, 85, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dbaec), {69, 78, 65, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dbae4), {78, 76, 66, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dbad8), {69, 78, 67, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dbad4), {90, 72, 72, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dbad0), {90, 72, 73, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dbac8), {67, 72, 83, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dbab4), {90, 72, 72, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dbaa0), {67, 72, 83, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dba8c), {90, 72, 73, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dba78), {67, 72, 84, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dba68), {78, 76, 66, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dba54), {69, 78, 85, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dba48), {69, 78, 65, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dba38), {69, 78, 76, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dba2c), {69, 78, 67, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dba18), {69, 78, 66, 0}},
    {reinterpret_cast<const char*>(storage_ref_006dba0c), {69, 78, 73, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db9fc), {69, 78, 74, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db9f0), {69, 78, 90, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db9d8), {69, 78, 83, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db9bc), {69, 78, 84, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db9b0), {69, 78, 71, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db9a4), {69, 78, 85, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db998), {69, 78, 85, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db988), {70, 82, 66, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db978), {70, 82, 67, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db964), {70, 82, 76, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db954), {70, 82, 83, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db944), {68, 69, 65, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db930), {68, 69, 67, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db91c), {68, 69, 76, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db90c), {68, 69, 83, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db8fc), {69, 78, 73, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db8ec), {73, 84, 83, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db8e0), {78, 79, 82, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db8cc), {78, 79, 82, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db8b8), {78, 79, 78, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db8a0), {80, 84, 66, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db88c), {69, 83, 83, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db87c), {69, 83, 66, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db86c), {69, 83, 76, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db858), {69, 83, 79, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db844), {69, 83, 67, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db828), {69, 83, 68, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db818), {69, 83, 70, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db804), {69, 83, 69, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db7f0), {69, 83, 71, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db7dc), {69, 83, 72, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db7cc), {69, 83, 77, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db7bc), {69, 83, 78, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db7a8), {69, 83, 73, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db798), {69, 83, 65, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db784), {69, 83, 90, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db774), {69, 83, 82, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db760), {69, 83, 85, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db750), {69, 83, 89, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db73c), {69, 83, 86, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db72c), {83, 86, 70, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db724), {68, 69, 83, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db720), {69, 78, 71, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db71c), {69, 78, 85, 0}},
    {reinterpret_cast<const char*>(storage_ref_006db718), {69, 78, 85, 0}}};
const void* dat_0070e180 = storage_ref_0070e188;
uint32_t dat_0070e4e8 = 0x1;
struct LocaleCTypeCacheEntry {
    uint32_t codepage, classification_matches_C;
};
static_assert(sizeof(LocaleCTypeCacheEntry) == 8);
LocaleCTypeCacheEntry dat_0070e680[5] = {{0, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
__asm__(".globl _dat_0070e684\n.set _dat_0070e684,_dat_0070e680+4\n");
__asm__(".globl _dat_0070e6a0\n.set _dat_0070e6a0,_dat_0070e680+32\n");
__asm__(".globl _dat_0070e6a4\n.set _dat_0070e6a4,_dat_0070e680+36\n");
uint32_t dat_0070ef00 = 0x1;
char dat_0070e620[4] = {67};
char dat_0070e6a8[132] = {67};
char dat_0070e730[132] = {67};
LocaleCategoryAction dat_0070e7b8[6] = {
    {reinterpret_cast<const char*>(storage_ref_006d6af0), nullptr, code_ref_005decbe},
    {reinterpret_cast<const char*>(storage_ref_006d6ae4), storage_ref_0070e620, code_ref_005decbe},
    {reinterpret_cast<const char*>(storage_ref_006d6ad8), storage_ref_0070e620, code_ref_005ddd67},
    {reinterpret_cast<const char*>(storage_ref_006d6acc), storage_ref_0070e620, code_ref_005ddb28},
    {reinterpret_cast<const char*>(storage_ref_006d6ac0), storage_ref_0070e620, code_ref_005dd882},
    {reinterpret_cast<const char*>(storage_ref_006d6ab8), storage_ref_0070e620, code_ref_005dd7c4}};
LocaleId dat_0224ee68 = {0, 0, 0};
LocaleId dat_0224f290[6] = {};
uint16_t dat_0224f2d4[4] = {};
ShaderCriticalSection dat_0224ffa0 = {};
uint32_t dat_0224f3c8[500] = {};
uint32_t dat_0224ffc8[500] = {};
int16_t dat_0224fb98[500] = {};
int16_t dat_02250798[500] = {};
uint32_t dat_0224ee70 = 0;
uint32_t dat_0224f25c = 0;
uint32_t dat_0224f26c = 0;
uint32_t dat_0224f270 = 0;
uint32_t dat_0224f274 = 0;
uint32_t dat_0224f278 = 0;
uint32_t dat_0224f27c = 0;
uint32_t dat_0224f280 = 0;
uint32_t dat_0224f284 = 0;
uint32_t dat_0224f288 = 0;
uint32_t dat_0224f28c = 0;
uint32_t dat_0224f2dc = 0;
uint32_t dat_0224f2e0 = 0;
uint32_t dat_0224ff80 = 0;
uint32_t dat_0224ff84 = 0;
uint32_t dat_0224ff88 = 0;
uint32_t dat_0224ff8c = 0;
uint32_t dat_0224ff90 = 0;
uint32_t dat_0224ff94 = 0;
uint32_t dat_0224ff98 = 0;
uint32_t dat_0224ffb8 = 0;
uint32_t dat_0224ffbc = 0;
uint32_t dat_0224ffc0 = 0;
uint32_t dat_02250b80 = 0;
uint32_t dat_02250b84 = 0;
uint32_t dat_02250b88 = 0;
uint32_t dat_02250b8c = 0;
uint32_t dat_02250b90 = 0;
uint32_t dat_02250b94 = 0;
uint32_t dat_02250b98 = 0;
uint32_t dat_02250ba0 = 0;
uint32_t dat_02251784 = 0;
uint32_t dat_02253294 = 0;
uint32_t dat_022532a0 = 0;
extern const char dat_006bb6d0[] = "COLOR";
extern const char dat_006bbd40[] = "false";
extern const char dat_006bcaf4[] = "v";
extern const char dat_006bcb0c[] = "i";
extern const char dat_006bcb10[] = "s";
extern const char dat_006bcb18[] = "p";
extern const char dat_006c0310[] = ",";
extern const char dat_006c0314[] = ":";
extern const char dat_006c174c[] = "-";
extern const char dat_006c1b58[] = "NULL";
extern const char dat_006c3ec8[] = "C";
extern const char dat_006c3ee8[] = ";";
extern const char dat_006c3f64[] = "=";
extern const char dat_006c584c[] = "c";
extern const char dat_006cd044[] = "NORMAL";
extern const char dat_006d6ab8[] = "LC_TIME";
extern const char dat_006d6ac0[] = "LC_NUMERIC";
extern const char dat_006d6acc[] = "LC_MONETARY";
extern const char dat_006d6ad8[] = "LC_CTYPE";
extern const char dat_006d6ae4[] = "LC_COLLATE";
extern const char dat_006d6af0[] = "LC_ALL";
extern const char dat_006d6af8[] = "_.,";
extern const char dat_006d6b0c[] = "=;";
extern const char dat_006db1d4[] = "Paraguay";
extern const char dat_006db1e0[] = "Uruguay";
extern const char dat_006db1e8[] = "Chile";
extern const char dat_006db1f0[] = "Ecuador";
extern const char dat_006db1f8[] = "Argentina";
extern const char dat_006db204[] = "Peru";
extern const char dat_006db20c[] = "Colombia";
extern const char dat_006db218[] = "Venezuela";
extern const char dat_006db224[] = "Dominican Republic";
extern const char dat_006db238[] = "South Africa";
extern const char dat_006db248[] = "Panama";
extern const char dat_006db250[] = "Luxembourg";
extern const char dat_006db25c[] = "Costa Rica";
extern const char dat_006db268[] = "Switzerland";
extern const char dat_006db274[] = "Guatemala";
extern const char dat_006db280[] = "Canada";
extern const char dat_006db288[] = "Spanish - Modern Sort";
extern const char dat_006db2a0[] = "Australia";
extern const char dat_006db2ac[] = "English";
extern const char dat_006db2b4[] = "Austria";
extern const char dat_006db2bc[] = "German";
extern const char dat_006db2c4[] = "Belgium";
extern const char dat_006db2cc[] = "Mexico";
extern const char dat_006db2d4[] = "Spanish";
extern const char dat_006db2dc[] = "Basque";
extern const char dat_006db2e4[] = "Sweden";
extern const char dat_006db2ec[] = "Swedish";
extern const char dat_006db2f4[] = "Iceland";
extern const char dat_006db2fc[] = "Icelandic";
extern const char dat_006db308[] = "France";
extern const char dat_006db310[] = "French";
extern const char dat_006db318[] = "Finland";
extern const char dat_006db320[] = "Finnish";
extern const char dat_006db328[] = "Spain";
extern const char dat_006db330[] = "Spanish - Traditional Sort";
extern const char dat_006db418[] = "united-states";
extern const char dat_006db428[] = "united-kingdom";
extern const char dat_006db438[] = "trinidad & tobago";
extern const char dat_006db44c[] = "south-korea";
extern const char dat_006db458[] = "south-africa";
extern const char dat_006db468[] = "south korea";
extern const char dat_006db474[] = "south africa";
extern const char dat_006db484[] = "slovak";
extern const char dat_006db48c[] = "puerto-rico";
extern const char dat_006db498[] = "pr-china";
extern const char dat_006db4a4[] = "pr china";
extern const char dat_006db4b0[] = "nz";
extern const char dat_006db4b4[] = "new-zealand";
extern const char dat_006db4c0[] = "hong-kong";
extern const char dat_006db4cc[] = "holland";
extern const char dat_006db4d4[] = "great britain";
extern const char dat_006db4e4[] = "england";
extern const char dat_006db4ec[] = "czech";
extern const char dat_006db4f4[] = "china";
extern const char dat_006db4fc[] = "britain";
extern const char dat_006db504[] = "america";
extern const char dat_006db718[] = "usa";
extern const char dat_006db71c[] = "us";
extern const char dat_006db720[] = "uk";
extern const char dat_006db724[] = "swiss";
extern const char dat_006db72c[] = "swedish-finland";
extern const char dat_006db73c[] = "spanish-venezuela";
extern const char dat_006db750[] = "spanish-uruguay";
extern const char dat_006db760[] = "spanish-puerto rico";
extern const char dat_006db774[] = "spanish-peru";
extern const char dat_006db784[] = "spanish-paraguay";
extern const char dat_006db798[] = "spanish-panama";
extern const char dat_006db7a8[] = "spanish-nicaragua";
extern const char dat_006db7bc[] = "spanish-modern";
extern const char dat_006db7cc[] = "spanish-mexican";
extern const char dat_006db7dc[] = "spanish-honduras";
extern const char dat_006db7f0[] = "spanish-guatemala";
extern const char dat_006db804[] = "spanish-el salvador";
extern const char dat_006db818[] = "spanish-ecuador";
extern const char dat_006db828[] = "spanish-dominican republic";
extern const char dat_006db844[] = "spanish-costa rica";
extern const char dat_006db858[] = "spanish-colombia";
extern const char dat_006db86c[] = "spanish-chile";
extern const char dat_006db87c[] = "spanish-bolivia";
extern const char dat_006db88c[] = "spanish-argentina";
extern const char dat_006db8a0[] = "portuguese-brazilian";
extern const char dat_006db8b8[] = "norwegian-nynorsk";
extern const char dat_006db8cc[] = "norwegian-bokmal";
extern const char dat_006db8e0[] = "norwegian";
extern const char dat_006db8ec[] = "italian-swiss";
extern const char dat_006db8fc[] = "irish-english";
extern const char dat_006db90c[] = "german-swiss";
extern const char dat_006db91c[] = "german-luxembourg";
extern const char dat_006db930[] = "german-lichtenstein";
extern const char dat_006db944[] = "german-austrian";
extern const char dat_006db954[] = "french-swiss";
extern const char dat_006db964[] = "french-luxembourg";
extern const char dat_006db978[] = "french-canadian";
extern const char dat_006db988[] = "french-belgian";
extern const char dat_006db998[] = "english-usa";
extern const char dat_006db9a4[] = "english-us";
extern const char dat_006db9b0[] = "english-uk";
extern const char dat_006db9bc[] = "english-trinidad y tobago";
extern const char dat_006db9d8[] = "english-south africa";
extern const char dat_006db9f0[] = "english-nz";
extern const char dat_006db9fc[] = "english-jamaica";
extern const char dat_006dba0c[] = "english-ire";
extern const char dat_006dba18[] = "english-caribbean";
extern const char dat_006dba2c[] = "english-can";
extern const char dat_006dba38[] = "english-belize";
extern const char dat_006dba48[] = "english-aus";
extern const char dat_006dba54[] = "english-american";
extern const char dat_006dba68[] = "dutch-belgian";
extern const char dat_006dba78[] = "chinese-traditional";
extern const char dat_006dba8c[] = "chinese-singapore";
extern const char dat_006dbaa0[] = "chinese-simplified";
extern const char dat_006dbab4[] = "chinese-hongkong";
extern const char dat_006dbac8[] = "chinese";
extern const char dat_006dbad0[] = "chi";
extern const char dat_006dbad4[] = "chh";
extern const char dat_006dbad8[] = "canadian";
extern const char dat_006dbae4[] = "belgian";
extern const char dat_006dbaec[] = "australian";
extern const char dat_006dbaf8[] = "american-english";
extern const char dat_006dbb0c[] = "american english";
extern const char dat_006dbb20[] = "american";
extern const char dat_006dbb2c[] = "OCP";
extern const char dat_006dbb30[] = "ACP";
extern const char dat_006dbb34[] = "Norwegian-Nynorsk";
extern const char dat_006de7c0[] = "vs_3_sw";
extern const char dat_006de7c8[] = "vs_3_0";
extern const char dat_006de7d0[] = "vs_2_x";
extern const char dat_006de7d8[] = "vs_2_sw";
extern const char dat_006de7e0[] = "vs_2_a";
extern const char dat_006de7e8[] = "vs_2_0";
extern const char dat_006de7f0[] = "vs_1_1";
extern const char dat_006de7f8[] = "vs_1_0";
extern const char dat_006de800[] = "vs.3.sw";
extern const char dat_006de808[] = "vs.3.0";
extern const char dat_006de810[] = "vs.2.x";
extern const char dat_006de818[] = "vs.2.sw";
extern const char dat_006de820[] = "vs.2.a";
extern const char dat_006de828[] = "vs.2.0";
extern const char dat_006de830[] = "vs.1.1";
extern const char dat_006de838[] = "vs.1.0";
extern const char dat_006de840[] = "vs";
extern const char dat_006de844[] = "tx_1_0";
extern const char dat_006de84c[] = "tx";
extern const char dat_006de850[] = "ps_3_sw";
extern const char dat_006de858[] = "ps_3_0";
extern const char dat_006de860[] = "ps_2_x";
extern const char dat_006de868[] = "ps_2_sw";
extern const char dat_006de870[] = "ps_2_b";
extern const char dat_006de878[] = "ps_2_a";
extern const char dat_006de880[] = "ps_2_0";
extern const char dat_006de888[] = "ps_1_4";
extern const char dat_006de890[] = "ps_1_3";
extern const char dat_006de898[] = "ps_1_2";
extern const char dat_006de8a0[] = "ps_1_1";
extern const char dat_006de8a8[] = "ps_1_0";
extern const char dat_006de8b0[] = "ps.3.sw";
extern const char dat_006de8b8[] = "ps.3.0";
extern const char dat_006de8c0[] = "ps.2.x";
extern const char dat_006de8c8[] = "ps.2.sw";
extern const char dat_006de8d0[] = "ps.2.b";
extern const char dat_006de8d8[] = "ps.2.a";
extern const char dat_006de8e0[] = "ps.2.0";
extern const char dat_006de8e8[] = "ps.1.4";
extern const char dat_006de8f0[] = "ps.1.3";
extern const char dat_006de8f8[] = "ps.1.2";
extern const char dat_006de900[] = "ps.1.1";
extern const char dat_006de908[] = "ps.1.0";
extern const char dat_006de910[] = "ps";
extern const char dat_006dfa24[] = "failed to open source file: '%s'";
extern const char dat_006dfa48[] = "invalid preprocessor command '%s'";
extern const char dat_006dfa6c[] = "syntax error";
extern const char dat_006dfa7c[] = "too many nested #includes";
extern const char dat_006dfa98[] =
    "include interface required to support #include from resource or memory";
extern const char dat_006dfae0[] = "error: %s";
extern const char dat_006dfaec[] = "unexpected #elif following #else";
extern const char dat_006dfb10[] = "unexpected #elif";
extern const char dat_006dfb24[] = "unexpected #else following #else";
extern const char dat_006dfb48[] = "unexpected #else";
extern const char dat_006dfb5c[] = "unexpected #endif";
extern const char dat_006dfb70[] = "column_major";
extern const char dat_006dfb80[] = "row_major";
extern const char dat_006dfb8c[] = ")";
extern const char dat_006dfb90[] = "(";
extern const char dat_006dfb94[] = "default";
extern const char dat_006dfb9c[] = "disable";
extern const char dat_006dfba4[] = "error";
extern const char dat_006dfbac[] = "once";
extern const char dat_006dfbb4[] = "internal error: production failed";
extern const char dat_006dfbd8[] = "def";
extern const char dat_006dfbdc[] = "warning";
extern const char dat_006dfbe4[] = "pack_matrix";
extern const char dat_006dfbf0[] = "'%s' : macro redefinition";
extern const char dat_006dfc0c[] = "invalid or unsupported integer constant expression";
extern const char dat_006dfc40[] =
    "functional defines in preprocessor expressions not yet implemented";
extern const char dat_006dfc84[] = "__LINE__";
extern const char dat_006dfc90[] = "not enough actual parameters for macro '%s'";
extern const char dat_006dfcbc[] = "##";
extern const char dat_006dfcc0[] = "#@";
extern const char dat_006dfcc4[] = "unexpected end of file in macro expansion";
extern const char dat_006dfcf0[] = "#";
extern const char dat_006dfcf4[] = "Arg";
extern const char dat_006dfcf8[] = "defined";
extern const char dat_006dfd00[] = "define";
extern const char dat_006dfd08[] = "endif";
extern const char dat_006dfd10[] = "else";
extern const char dat_006dfd18[] = "elif";
extern const char dat_006dfd20[] = "include";
extern const char dat_006dfd28[] = "ifndef";
extern const char dat_006dfd30[] = "ifdef";
extern const char dat_006dfd38[] = "if";
extern const char dat_006dfd3c[] = "line";
extern const char dat_006dfd44[] = "pragma";
extern const char dat_006dfd4c[] = "undef";
extern const char dat_006dfd54[] = "duplicate macro parameter '%s'";
extern const char dat_006dfd74[] = "D3DX_VERSION";
extern const char dat_006dfd84[] = "DIRECT3D_VERSION";
extern const char dat_006dfd98[] = "D3DX";
extern const char dat_006dfda0[] = "DIRECT3D";
extern const char dat_006dfdac[] = "internal error: out of memory";
extern const char dat_006dfdcc[] = "Stack";
extern const char dat_006dfdd4[] = "division by zero in preprocessor expression";
extern const char dat_006dfe00[] = "internal error: stack underflow";
extern const char dat_006dfe20[] = "yacc stack overflow";
extern const char dat_006dfe34[] = "unexpected end of file";
extern const char dat_006dfe4c[] = "__FILE__";
extern const char dat_006dfe58[] = "unexpected tokens following preprocessor directive";
extern const char dat_006dfe8c[] = "error X%u: ";
extern const char dat_006dfe98[] = "(%u): ";
extern const char dat_006dfea0[] = "%s X%u: ";
extern const char dat_006dfeac[] = "syntax error : unexpected %s";
extern const char dat_006dfecc[] = "token";
extern const char dat_006dfed4[] = "end of file";
extern const char dat_006dfee0[] = "end of line";
extern const char dat_006dfeec[] = "string constant";
extern const char dat_006dfefc[] = "token '%s'";
extern const char dat_006dff08[] = "float '%gl'";
extern const char dat_006dff14[] = "float '%gf'";
extern const char dat_006dff20[] = "float '%gh'";
extern const char dat_006dff2c[] = "float '%g'";
extern const char dat_006dff38[] = "integer '%uul'";
extern const char dat_006dff48[] = "integer '%dl'";
extern const char dat_006dff58[] = "integer '%u'";
extern const char dat_006dff68[] = "version token";
extern const char dat_006dff78[] = "comment continues past end of file";
extern const char dat_006dff9c[] = "hex value truncated to 32bits";
extern const char dat_006dffbc[] = "octal value truncated to 32bits";
extern const char dat_006dffdc[] = "decimal value truncated to 32bits";
extern const char dat_006e0000[] = "character continues past end of file";
extern const char dat_006e0028[] = "string continues past end of line";
extern const char dat_006e004c[] = "string continues past end of file";
extern const char dat_006e1d38[] = "o";
extern const char dat_006e1d3c[] = "l";
extern const char dat_006e1d40[] = "vFace";
extern const char dat_006e1d48[] = "vPos";
extern const char dat_006e1d50[] = "aL";
extern const char dat_006e1d54[] = "oDepth";
extern const char dat_006e1d5c[] = "oC";
extern const char dat_006e1d60[] = "oT";
extern const char dat_006e1d64[] = "oD";
extern const char dat_006e1d68[] = "oFog";
extern const char dat_006e1d70[] = "oPts";
extern const char dat_006e1d78[] = "oPos";
extern const char dat_006e1d80[] = "break_c";
extern const char dat_006e1d88[] = "if_c";
extern const char dat_006e1d90[] = "phase";
extern const char dat_006e1d98[] = "texldl";
extern const char dat_006e1da0[] = "setp";
extern const char dat_006e1da8[] = "texldd";
extern const char dat_006e1db0[] = "dsy";
extern const char dat_006e1db4[] = "dsx";
extern const char dat_006e1db8[] = "dp2add";
extern const char dat_006e1dc0[] = "bem";
extern const char dat_006e1dc4[] = "cmp";
extern const char dat_006e1dc8[] = "texdepth";
extern const char dat_006e1dd4[] = "texm3x3";
extern const char dat_006e1ddc[] = "texdp3";
extern const char dat_006e1de4[] = "texm3x2depth";
extern const char dat_006e1df4[] = "texdp3tex";
extern const char dat_006e1e00[] = "texreg2rgb";
extern const char dat_006e1e0c[] = "defb";
extern const char dat_006e1e14[] = "defi";
extern const char dat_006e1e1c[] = "cnd";
extern const char dat_006e1e20[] = "logp";
extern const char dat_006e1e28[] = "expp";
extern const char dat_006e1e30[] = "texm3x3vspec";
extern const char dat_006e1e40[] = "texm3x3spec";
extern const char dat_006e1e4c[] = "texm3x3tex";
extern const char dat_006e1e58[] = "texm3x3pad";
extern const char dat_006e1e64[] = "texm3x2tex";
extern const char dat_006e1e70[] = "texm3x2pad";
extern const char dat_006e1e7c[] = "texreg2gb";
extern const char dat_006e1e88[] = "texreg2ar";
extern const char dat_006e1e94[] = "texbeml";
extern const char dat_006e1e9c[] = "texbem";
extern const char dat_006e1ea4[] = "texldb";
extern const char dat_006e1eac[] = "texldp";
extern const char dat_006e1eb4[] = "texld";
extern const char dat_006e1ebc[] = "tex";
extern const char dat_006e1ec0[] = "texkill";
extern const char dat_006e1ec8[] = "texcrd";
extern const char dat_006e1ed0[] = "texcoord";
extern const char dat_006e1edc[] = "mova";
extern const char dat_006e1ee4[] = "breakp";
extern const char dat_006e1eec[] = "break";
extern const char dat_006e1ef4[] = "endrep";
extern const char dat_006e1efc[] = "rep";
extern const char dat_006e1f00[] = "sincos";
extern const char dat_006e1f08[] = "nrm";
extern const char dat_006e1f0c[] = "abs";
extern const char dat_006e1f10[] = "sgn";
extern const char dat_006e1f14[] = "crs";
extern const char dat_006e1f18[] = "dcl";
extern const char dat_006e1f1c[] = "label";
extern const char dat_006e1f24[] = "endloop";
extern const char dat_006e1f2c[] = "ret";
extern const char dat_006e1f30[] = "loop";
extern const char dat_006e1f38[] = "callnz";
extern const char dat_006e1f40[] = "call";
extern const char dat_006e1f48[] = "m3x2";
extern const char dat_006e1f50[] = "m3x3";
extern const char dat_006e1f58[] = "m3x4";
extern const char dat_006e1f60[] = "m4x3";
extern const char dat_006e1f68[] = "m4x4";
extern const char dat_006e1f70[] = "frc";
extern const char dat_006e1f74[] = "lrp";
extern const char dat_006e1f78[] = "dst";
extern const char dat_006e1f7c[] = "lit";
extern const char dat_006e1f80[] = "sge";
extern const char dat_006e1f84[] = "slt";
extern const char dat_006e1f88[] = "max";
extern const char dat_006e1f8c[] = "min";
extern const char dat_006e1f90[] = "dp4";
extern const char dat_006e1f94[] = "dp3";
extern const char dat_006e1f98[] = "rsq";
extern const char dat_006e1f9c[] = "rcp";
extern const char dat_006e1fa0[] = "mul";
extern const char dat_006e1fa4[] = "mad";
extern const char dat_006e1fa8[] = "sub";
extern const char dat_006e1fac[] = "add";
extern const char dat_006e1fb0[] = "mov";
extern const char dat_006e1fb4[] = "nop";
extern const char dat_006e1fb8[] = "SPECULAR";
extern const char dat_006e1fc4[] = "DIFFUSE";
extern const char dat_006e1fcc[] = "SAMPLE";
extern const char dat_006e1fd4[] = "DEPTH";
extern const char dat_006e1fdc[] = "FOG";
extern const char dat_006e1fe0[] = "POSITIONT";
extern const char dat_006e1fec[] = "TESSFACTOR";
extern const char dat_006e1ff8[] = "BINORMAL";
extern const char dat_006e2004[] = "TANGENT";
extern const char dat_006e200c[] = "TEXCOORD";
extern const char dat_006e2018[] = "PSIZE";
extern const char dat_006e2020[] = "BLENDINDICES";
extern const char dat_006e2030[] = "BLENDWEIGHT";
extern const char dat_006e203c[] = "POSITION";
extern const char dat_006e2050[] = "invalid instruction modifiers '%s'";
extern const char dat_006e2074[] = "'%s' is not a valid instruction in this shader version";
extern const char dat_006e20ac[] = "le";
extern const char dat_006e20b0[] = "ne";
extern const char dat_006e20b4[] = "lt";
extern const char dat_006e20b8[] = "ge";
extern const char dat_006e20bc[] = "eq";
extern const char dat_006e20c0[] = "gt";
extern const char dat_006e20c4[] = "sample";
extern const char dat_006e20cc[] = "depth";
extern const char dat_006e20d4[] = "fog";
extern const char dat_006e20d8[] = "color";
extern const char dat_006e20e0[] = "positiont";
extern const char dat_006e20ec[] = "tessfactor";
extern const char dat_006e20f8[] = "binormal";
extern const char dat_006e2104[] = "tangent";
extern const char dat_006e210c[] = "psize";
extern const char dat_006e2114[] = "normal";
extern const char dat_006e211c[] = "blendindices";
extern const char dat_006e212c[] = "blendweight";
extern const char dat_006e2138[] = "position";
extern const char dat_006e2144[] = "pp";
extern const char dat_006e2148[] = "volume";
extern const char dat_006e2150[] = "cube";
extern const char dat_006e2158[] = "2d";
extern const char dat_006e215c[] = "d8";
extern const char dat_006e2160[] = "d4";
extern const char dat_006e2164[] = "d2";
extern const char dat_006e2168[] = "x2";
extern const char dat_006e216c[] = "x4";
extern const char dat_006e2170[] = "x8";
extern const char dat_006e2174[] = "centroid";
extern const char dat_006e2180[] = "sat";
extern const char dat_006e2184[] = "invalid mask '%s'";
extern const char dat_006e2198[] = "invalid swizzle '%s'";
extern const char dat_006e21b0[] = "internal error: instruction size mismatch";
extern const char dat_006e21dc[] = "only a0.x is allowed as a relative address register in vs_1_1";
extern const char dat_006e221c[] = "source modifiers incompatible with SUB instruction";
extern const char dat_006e2250[] =
    "relative addressing of predicates is not supported in this shader version";
extern const char dat_006e229c[] = "source modifiers are not allowed on predicates";
extern const char dat_006e22cc[] = "predicates are not supported in this shader version";
extern const char dat_006e2300[] =
    "relative addressing of destination parameters is not supported in this shader version";
extern const char dat_006e2358[] =
    "only one address register reference is allowed in a relative address expression";
extern const char dat_006e23a8[] = "source modifiers are not allowed on destination parameters";
extern const char dat_006e23e8[] =
    "call, callnz, label, and ret instructions are not allowed in assembly fragments";
extern const char dat_006e2438[] =
    "Matrices cannot be specified in temp registers with the fragment linker";
extern const char dat_006e2480[] = "o_";
extern const char dat_006e2484[] = "r_";
extern const char dat_006e2488[] = "v_";
extern const char dat_006e248c[] = "fragment info exceeds maximum comment size";
extern const char dat_006e24b8[] = "Microsoft (R) D3DX9 Shader Assembler 5.04.00.2904";
extern const char dat_006e24ec[] = "debug info exceeds maximum comment size; no debug info emitted";
extern const char dat_006e2530[] =
    "constant register address out of bounds on constant '%s', size %d, offset %d";
extern const char dat_006e2580[] = "constant register '%s' must be defined as a variable '%s'";
extern const char dat_006e25c0[] =
    "'%s' is not a valid register name.  Registers must start with v_, r_, c_, b_, or i_ depending on the register type. (o_ for vs_3_0 only)";
extern const char dat_006e264c[] = "addressing operations are not allowed on output registers '%s'";
extern const char dat_006e268c[] = "Invalid output register '%s' specified";
extern const char dat_006e26b4[] = "s_";
extern const char dat_006e26b8[] = "i_";
extern const char dat_006e26bc[] = "b_";
extern const char dat_006e26c0[] = "c_";
extern const char dat_006e26c4[] = "addressing operations not allowed on temporary registers '%s'";
extern const char dat_006e2704[] = "addressing operations are not allowed on input registers '%s'";
extern const char dat_006e2744[] = "Invalid pixel shader input register '%s' specified";
extern const char dat_006e2778[] = "Invalid input register '%s' specified";
extern const char dat_006e27a0[] = "invalid register, input, or constant name '%s'";
extern const char dat_006e27d0[] = "entrypoint";
extern const char dat_006e27e0[] =
    "temporary and constant registers are not allowed in assembly fragments";
extern const char dat_006e2828[] = "invalid register '%s'";
extern const char dat_006e2840[] = "invalid register '%s[...]'";
extern const char dat_006e285c[] = "invalid register '%s[%u]'";
extern const char dat_006e2878[] = "da";
extern const char dat_006e287c[] = "dw";
extern const char dat_006e2880[] = "db";
extern const char dat_006e2884[] = "dz";
extern const char dat_006e2888[] = "bx2";
extern const char dat_006e288c[] = "bias";
extern const char dat_006e2898[] =
    "temporary, constant, and output registers are not allowed in vs_3_0 assembly fragments";
extern const char dat_006e28f0[] =
    "only one address register reference allowed in a relative address expression";
extern const char dat_006e2940[] = "scalar registers cannot be swizzled";
extern const char dat_006e2964[] = "complement is not supported in this shader version";
extern const char dat_006e2998[] = "complement cannot be used with other modifiers";
extern const char dat_006e29c8[] = "invalid complement expression";
extern const char dat_006e29e8[] = "negate and divide modifiers cannot be combined";
extern const char dat_006e2a18[] = "not cannot be used with other modifiers";
extern const char dat_006e2a40[] = "scalar registers cannot be masked";
extern const char dat_006e2a68[] =
    "instruction predication is not supported in this shader version";
extern const char dat_006e2aa8[] = "instruction coissue is not supported in this shader version";
extern const char dat_006e2ae4[] = "Direct3DShaderValidatorCreate9";
extern const char dat_006e2b08[] =
    "only vs_1_1, vs_2_0, vs_2_x, vs_2_sw, ps_2_0, ps_2_x, and ps_2_sw are supported for assembly fragments";
extern const char dat_006e2b70[] = "unrecognized shader version";
extern const char dat_006e2b8c[] = "ps_1_0 is no longer supported; using ps_1_1";
extern const char dat_006e2bb8[] = "vs_1_0 is no longer supported; using vs_1_1";
extern const char dat_006e2be4[] = "shader version expected";
extern const char dat_006e2c18[] = "internal error: unknown node";
extern const char dat_006eb464[] = "vertexshader";
extern const char dat_006eb474[] = "pixelshader";
extern const char dat_006eb4e8[] = "texture";
extern const char dat_006eb4f0[] = "string";
extern const char dat_006eb4f8[] = "double";
extern const char dat_006eb500[] = "float";
extern const char dat_006eb508[] = "half";
extern const char dat_006eb510[] = "int";
extern const char dat_006eb514[] = "bool";
extern const char dat_006eb6f4[] = "Values";
extern const char dat_006eb85c[] = "pass";
extern const char dat_006eb864[] = "techinque";
extern const char dat_006eb870[] = "function";
extern const char dat_006eb87c[] = "variable";
extern const char dat_006eb888[] = "type";
extern const char dat_006eb890[] = "undeclared identifier '%s'";
extern const char dat_006eb8ac[] = "matrix";
extern const char dat_006eb8b4[] = "vector";
extern const char dat_006eb8bc[] = "dword";
extern const char dat_006eb8c4[] = "'%s': identifier represents a %s, not a %s";
extern const char dat_006eb904[] = "'%s': ambiguous function call";
extern const char dat_006eb928[] =
    "'%s': loop control variable used outside for-loop scope conflicts with a previous declaration in the outer scope; most recent definition used";
extern const char dat_006f0348[] =
    "integer constant register '%s' must be defined as a variable of type int3 or int4 only";
extern const char dat_006f03a0[] =
    "boolean constant register '%s' must be defined as a variable of type bool only";
extern const char dat_006f03f0[] =
    "Sampler variable '%s' does not specify the sampler type.  Explicit sampler types required for asm fragments.";
extern const char dat_006f0460[] =
    "Constant variable '%s' bound to register greater than 8191 (%d requested)";
__asm__(".globl _dat_006dad34\n.set _dat_006dad34,_dat_006dad30+4\n");
__asm__(".globl _dat_006dad3c\n.set _dat_006dad3c,_dat_006dad30+12\n");
__asm__(".globl _dat_006dad40\n.set _dat_006dad40,_dat_006dad30+16\n");
__asm__(".globl _dat_006dad44\n.set _dat_006dad44,_dat_006dad30+20\n");
__asm__(".globl _dat_006dad48\n.set _dat_006dad48,_dat_006dad30+24\n");
__asm__(".globl _dat_006dad4c\n.set _dat_006dad4c,_dat_006dad30+28\n");
__asm__(".globl _dat_006dad54\n.set _dat_006dad54,_dat_006dad30+36\n");
__asm__(".globl _dat_006de5b8\n.set _dat_006de5b8,_dat_006de5b0+8\n");
__asm__(".globl _dat_006e0074\n.set _dat_006e0074,_dat_006e0070+4\n");
__asm__(".globl _dat_006e0078\n.set _dat_006e0078,_dat_006e0070+8\n");
__asm__(".globl _dat_006e16c8\n.set _dat_006e16c8,_dat_006e16c0+8\n");
__asm__(".globl _dat_006e1710\n.set _dat_006e1710,_dat_006e16c0+80\n");
__asm__(".globl _dat_006e1754\n.set _dat_006e1754,_dat_006e1750+4\n");
__asm__(".globl _dat_006e1758\n.set _dat_006e1758,_dat_006e1750+8\n");
__asm__(".globl _dat_006e1794\n.set _dat_006e1794,_dat_006e1750+68\n");
__asm__(".globl _dat_006eb53c\n.set _dat_006eb53c,_dat_006eb538+4\n");
__asm__(".globl _dat_0070e72a\n.set _dat_0070e72a,_dat_0070e6a8+130\n");
__asm__(".globl _dat_0070e7bc\n.set _dat_0070e7bc,_dat_0070e7b8+4\n");
__asm__(".globl _dat_0070e7c0\n.set _dat_0070e7c0,_dat_0070e7b8+8\n");
__asm__(".globl _dat_0070e7c4\n.set _dat_0070e7c4,_dat_0070e7b8+12\n");
__asm__(".globl _dat_0070e7c8\n.set _dat_0070e7c8,_dat_0070e7b8+16\n");
__asm__(".globl _dat_0070e7d4\n.set _dat_0070e7d4,_dat_0070e7b8+28\n");
__asm__(".globl _dat_0070e7f4\n.set _dat_0070e7f4,_dat_0070e7b8+60\n");
__asm__(".globl _dat_0070e7f8\n.set _dat_0070e7f8,_dat_0070e7b8+64\n");
__asm__(".globl _dat_0224ee6c\n.set _dat_0224ee6c,_dat_0224ee68+4\n");
__asm__(".globl _dat_0224f26d\n.set _dat_0224f26d,_dat_0224f26c+1\n");
__asm__(".globl _dat_0224f29c\n.set _dat_0224f29c,_dat_0224f290+12\n");
__asm__(".globl _dat_0224f2a4\n.set _dat_0224f2a4,_dat_0224f290+20\n");
__asm__(".globl _dat_0224f2aa\n.set _dat_0224f2aa,_dat_0224f290+26\n");
__asm__(".globl _dat_0224f2ae\n.set _dat_0224f2ae,_dat_0224f290+30\n");
__asm__(".globl _dat_0224f2b0\n.set _dat_0224f2b0,_dat_0224f290+32\n");
__asm__(".globl _dat_0224ff7e\n.set _dat_0224ff7e,_dat_0224fb98+998\n");
__asm__(".globl _dat_02250b7e\n.set _dat_02250b7e,_dat_02250798+998\n");
}
