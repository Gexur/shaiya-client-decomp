// Recovered decision behavior of original 0x59cf70.
// Generated only from exhaustive original-instruction routing evidence.
// Real packet consumers remain external symbols until separately recovered.
#include "dispatcher.h"

extern "C" {
void PACKET_CDECL fun_004015a0();
void PACKET_CDECL fun_0058d5c0(PacketReader*);
void PACKET_CDECL fun_0058d5f0(PacketReader*);
void PACKET_CDECL fun_0058d640(PacketReader*);
void PACKET_CDECL fun_0058d690(PacketReader*);
void PACKET_CDECL fun_0058d6c0(PacketReader*);
void PACKET_CDECL fun_0058d6f0(PacketReader*);
void PACKET_CDECL fun_0058d710(PacketReader*);
void PACKET_CDECL fun_0058d790(PacketReader*);
void PACKET_CDECL fun_0058d7e0(PacketReader*);
void PACKET_CDECL fun_0058d830(PacketReader*);
void PACKET_CDECL fun_0058d860(PacketReader*);
void PACKET_CDECL fun_0058db20(PacketReader*);
void PACKET_CDECL fun_0058db50(PacketReader*);
void PACKET_CDECL fun_0058db90(PacketReader*);
void PACKET_CDECL fun_0058dbd0(PacketReader*);
void PACKET_CDECL fun_0058dd30(PacketReader*);
void PACKET_CDECL fun_0058e020(PacketReader*);
void PACKET_CDECL fun_0058e0e0(PacketReader*);
void PACKET_CDECL fun_0058e120(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_040(PacketReader*);
void PACKET_CDECL fun_0058e190(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_050(PacketReader*);
void PACKET_CDECL dispatch_packet_u16_to_session_slot_058(PacketReader*);
void PACKET_CDECL fun_0058e240(PacketReader*);
void PACKET_CDECL fun_0058e280(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_064(PacketReader*);
void PACKET_CDECL fun_0058e360(PacketReader*);
void PACKET_CDECL fun_0058e510(PacketReader*);
void PACKET_CDECL fun_0058eb30(PacketReader*);
void PACKET_CDECL fun_0058eca0(PacketReader*);
void PACKET_CDECL fun_0058ed20(PacketReader*);
void PACKET_CDECL fun_0058eda0(PacketReader*);
void PACKET_CDECL fun_0058ee30(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_08c(PacketReader*);
void PACKET_CDECL fun_0058eed0(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_098(PacketReader*);
void PACKET_CDECL fun_0058ef60(PacketReader*);
void PACKET_CDECL fun_0058efe0(PacketReader*);
void PACKET_CDECL fun_0058f030(PacketReader*);
void PACKET_CDECL fun_0058f080(PacketReader*);
void PACKET_CDECL fun_0058f0d0(PacketReader*);
void PACKET_CDECL fun_0058f150(PacketReader*);
void PACKET_CDECL fun_0058f200(PacketReader*);
void PACKET_CDECL fun_0058f260(PacketReader*);
void PACKET_CDECL fun_0058f2d0(PacketReader*);
void PACKET_CDECL fun_0058f320(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_0d0(PacketReader*);
void PACKET_CDECL fun_0058f410(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_0d8(PacketReader*);
void PACKET_CDECL fun_0058f490(PacketReader*);
void PACKET_CDECL fun_0058f4f0(PacketReader*);
void PACKET_CDECL fun_0058f5b0(PacketReader*);
void PACKET_CDECL dispatch_packet_u16_to_session_slot_128(PacketReader*);
void PACKET_CDECL fun_0058f640(PacketReader*);
void PACKET_CDECL fun_0058f6d0(PacketReader*);
void PACKET_CDECL fun_0058f760(PacketReader*);
void PACKET_CDECL fun_0058f7c0(PacketReader*);
void PACKET_CDECL fun_0058f830(PacketReader*);
void PACKET_CDECL dispatch_packet_12_dwords_to_session_slot_0fc(PacketReader*);
void PACKET_CDECL fun_0058f980(PacketReader*);
void PACKET_CDECL fun_0058fa30(PacketReader*);
void PACKET_CDECL fun_0058fac0(PacketReader*);
void PACKET_CDECL fun_0058fb50(PacketReader*);
void PACKET_CDECL fun_0058fbc0(PacketReader*);
void PACKET_CDECL fun_0058fc50(PacketReader*);
void PACKET_CDECL fun_0058fcd0(PacketReader*);
void PACKET_CDECL fun_0058fd30(PacketReader*);
void PACKET_CDECL fun_0058fd80(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_13c(PacketReader*);
void PACKET_CDECL fun_0058fe10(PacketReader*);
void PACKET_CDECL fun_0058fea0(PacketReader*);
void PACKET_CDECL fun_0058ff10(PacketReader*);
void PACKET_CDECL fun_0058ffd0(PacketReader*);
void PACKET_CDECL dispatch_packet_11_mixed_fields_to_session_slot_150(PacketReader*);
void PACKET_CDECL fun_00590120(PacketReader*);
void PACKET_CDECL fun_005901e0(PacketReader*);
void PACKET_CDECL fun_00590280(PacketReader*);
void PACKET_CDECL fun_00590300(PacketReader*);
void PACKET_CDECL fun_00590370(PacketReader*);
void PACKET_CDECL dispatch_packet_11_mixed_fields_to_session_slot_168(PacketReader*);
void PACKET_CDECL fun_00590520(PacketReader*);
void PACKET_CDECL fun_005905e0(PacketReader*);
void PACKET_CDECL fun_00590680(PacketReader*);
void PACKET_CDECL fun_00590700(PacketReader*);
void PACKET_CDECL fun_00590750(PacketReader*);
void PACKET_CDECL dispatch_packet_9_mixed_fields_to_session_slot_17c(PacketReader*);
void PACKET_CDECL dispatch_packet_12_mixed_fields_to_session_slot_180(PacketReader*);
void PACKET_CDECL fun_00590970(PacketReader*);
void PACKET_CDECL fun_00590a30(PacketReader*);
void PACKET_CDECL fun_00590ad0(PacketReader*);
void PACKET_CDECL fun_00590b50(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_194(PacketReader*);
void PACKET_CDECL fun_00590c00(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_19c(PacketReader*);
void PACKET_CDECL fun_00590ca0(PacketReader*);
void PACKET_CDECL fun_00590d30(PacketReader*);
void PACKET_CDECL fun_00590d90(PacketReader*);
void PACKET_CDECL fun_00590df0(PacketReader*);
void PACKET_CDECL fun_00590e80(PacketReader*);
void PACKET_CDECL fun_00590ef0(PacketReader*);
void PACKET_CDECL fun_00590f90(PacketReader*);
void PACKET_CDECL fun_00591030(PacketReader*);
void PACKET_CDECL fun_00591170(PacketReader*);
void PACKET_CDECL fun_005911e0(PacketReader*);
void PACKET_CDECL fun_00591330(PacketReader*);
void PACKET_CDECL fun_00591490(PacketReader*);
void PACKET_CDECL fun_005915f0(PacketReader*);
void PACKET_CDECL dispatch_packet_13_mixed_fields_to_session_slot_1c8(PacketReader*);
void PACKET_CDECL fun_005917b0(PacketReader*);
void PACKET_CDECL fun_005918a0(PacketReader*);
void PACKET_CDECL fun_00591a30(PacketReader*);
void PACKET_CDECL fun_00591a90(PacketReader*);
void PACKET_CDECL fun_00591af0(PacketReader*);
void PACKET_CDECL fun_00591b50(PacketReader*);
void PACKET_CDECL fun_00591bb0(PacketReader*);
void PACKET_CDECL dispatch_packet_10_mixed_fields_to_session_slot_200(PacketReader*);
void PACKET_CDECL fun_00591ce0(PacketReader*);
void PACKET_CDECL dispatch_packet_u16_to_session_slot_208(PacketReader*);
void PACKET_CDECL fun_00591d70(PacketReader*);
void PACKET_CDECL fun_00591dd0(PacketReader*);
void PACKET_CDECL fun_00591e30(PacketReader*);
void PACKET_CDECL fun_00591e70(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_218(PacketReader*);
void PACKET_CDECL fun_00591fe0(PacketReader*);
void PACKET_CDECL fun_00592030(PacketReader*);
void PACKET_CDECL fun_00592090(PacketReader*);
void PACKET_CDECL fun_00592120(PacketReader*);
void PACKET_CDECL fun_005921b0(PacketReader*);
void PACKET_CDECL fun_00592220(PacketReader*);
void PACKET_CDECL fun_005922a0(PacketReader*);
void PACKET_CDECL fun_005922d0(PacketReader*);
void PACKET_CDECL fun_00592380(PacketReader*);
void PACKET_CDECL fun_005923d0(PacketReader*);
void PACKET_CDECL fun_00592420(PacketReader*);
void PACKET_CDECL fun_00592480(PacketReader*);
void PACKET_CDECL fun_00592620(PacketReader*);
void PACKET_CDECL fun_00592650(PacketReader*);
void PACKET_CDECL fun_005926a0(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_260(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_264(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_268(PacketReader*);
void PACKET_CDECL fun_00592870(PacketReader*, uint32_t);
void PACKET_CDECL fun_005928d0(PacketReader*, uint32_t);
void PACKET_CDECL fun_00592930(PacketReader*, uint32_t);
void PACKET_CDECL fun_005929a0(PacketReader*, uint32_t);
void PACKET_CDECL fun_00592a00(PacketReader*, uint32_t);
void PACKET_CDECL fun_00592a60(PacketReader*, uint32_t);
void PACKET_CDECL fun_00592a90(PacketReader*, uint32_t);
void PACKET_CDECL fun_00592b10(PacketReader*, uint32_t);
void PACKET_CDECL fun_00592b80(PacketReader*, uint32_t);
void PACKET_CDECL fun_00592bd0(PacketReader*, uint32_t);
void PACKET_CDECL fun_00592c30(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_29c(PacketReader*);
void PACKET_CDECL fun_00592cc0(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_2a4(PacketReader*);
void PACKET_CDECL fun_00592d40(PacketReader*);
void PACKET_CDECL fun_00592d90(PacketReader*);
void PACKET_CDECL fun_00592de0(PacketReader*);
void PACKET_CDECL fun_00592e30(PacketReader*);
void PACKET_CDECL fun_00592e80(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_2cc(PacketReader*);
void PACKET_CDECL fun_00592f50(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_2d4(PacketReader*);
void PACKET_CDECL fun_00593020(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_2dc(PacketReader*);
void PACKET_CDECL fun_005930d0(PacketReader*);
void PACKET_CDECL fun_00593140(PacketReader*);
void PACKET_CDECL fun_005931b0(PacketReader*);
void PACKET_CDECL fun_00593230(PacketReader*);
void PACKET_CDECL fun_005932d0(PacketReader*);
void PACKET_CDECL fun_00593360(PacketReader*);
void PACKET_CDECL fun_005933f0(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_2f0(PacketReader*);
void PACKET_CDECL fun_005934a0(PacketReader*);
void PACKET_CDECL fun_00593510(PacketReader*);
void PACKET_CDECL fun_005935a0(PacketReader*);
void PACKET_CDECL fun_00593640(PacketReader*);
void PACKET_CDECL fun_00593690(PacketReader*);
void PACKET_CDECL fun_00593700(PacketReader*);
void PACKET_CDECL fun_00593790(PacketReader*);
void PACKET_CDECL fun_00593810(PacketReader*);
void PACKET_CDECL fun_005938b0(PacketReader*);
void PACKET_CDECL fun_00593940(PacketReader*);
void PACKET_CDECL fun_005939d0(PacketReader*);
void PACKET_CDECL fun_00593a50(PacketReader*);
void PACKET_CDECL fun_00593ab0(PacketReader*);
void PACKET_CDECL dispatch_packet_u16_to_session_slot_314(PacketReader*);
void PACKET_CDECL dispatch_packet_u16_to_session_slot_318(PacketReader*);
void PACKET_CDECL fun_00593be0(PacketReader*);
void PACKET_CDECL fun_00593c40(PacketReader*);
void PACKET_CDECL fun_00593cb0(PacketReader*);
void PACKET_CDECL fun_00593d30(PacketReader*);
void PACKET_CDECL fun_00593db0(PacketReader*);
void PACKET_CDECL fun_00593e30(PacketReader*);
void PACKET_CDECL fun_00593fd0(PacketReader*);
void PACKET_CDECL fun_00594050(PacketReader*);
void PACKET_CDECL fun_005940d0(PacketReader*);
void PACKET_CDECL fun_00594150(PacketReader*);
void PACKET_CDECL fun_005941b0(PacketReader*);
void PACKET_CDECL fun_00594210(PacketReader*);
void PACKET_CDECL fun_00594270(PacketReader*);
void PACKET_CDECL fun_005942d0(PacketReader*);
void PACKET_CDECL fun_00594330(PacketReader*);
void PACKET_CDECL dispatch_packet_u16_to_session_slot_380(PacketReader*);
void PACKET_CDECL dispatch_packet_u16_to_session_slot_384(PacketReader*);
void PACKET_CDECL dispatch_packet_u16_to_session_slot_388(PacketReader*);
void PACKET_CDECL dispatch_packet_u16_to_session_slot_38c(PacketReader*);
void PACKET_CDECL dispatch_packet_u16_to_session_slot_390(PacketReader*);
void PACKET_CDECL fun_00594480(PacketReader*);
void PACKET_CDECL dispatch_packet_u16_to_session_slot_39c(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_3a0(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_3a4(PacketReader*);
void PACKET_CDECL fun_00594560(PacketReader*);
void PACKET_CDECL fun_005945c0(PacketReader*);
void PACKET_CDECL fun_00594620(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_3b8(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_3bc(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_3c0(PacketReader*);
void PACKET_CDECL fun_00594740(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_3c8(PacketReader*);
void PACKET_CDECL fun_005947c0(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_3d0(PacketReader*);
void PACKET_CDECL fun_00594860(PacketReader*);
void PACKET_CDECL fun_005948b0(PacketReader*);
void PACKET_CDECL fun_00594940(PacketReader*);
void PACKET_CDECL fun_00594990(PacketReader*);
void PACKET_CDECL fun_005949f0(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_3f0(PacketReader*);
void PACKET_CDECL fun_00594a60(PacketReader*);
void PACKET_CDECL fun_00594ac0(PacketReader*);
void PACKET_CDECL fun_00594b20(PacketReader*);
void PACKET_CDECL fun_00594b80(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_404(PacketReader*);
void PACKET_CDECL fun_00594c00(PacketReader*);
void PACKET_CDECL fun_00594c60(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_410(PacketReader*);
void PACKET_CDECL fun_00594cd0(PacketReader*);
void PACKET_CDECL fun_00594d20(PacketReader*);
void PACKET_CDECL fun_00594d80(PacketReader*);
void PACKET_CDECL fun_00594dd0(PacketReader*);
void PACKET_CDECL fun_00594e30(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_428(PacketReader*);
void PACKET_CDECL fun_00594ec0(PacketReader*);
void PACKET_CDECL fun_00594f20(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_434(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_43c(PacketReader*);
void PACKET_CDECL fun_00595000(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_444(PacketReader*);
void PACKET_CDECL fun_00595090(PacketReader*);
void PACKET_CDECL fun_005950f0(PacketReader*);
void PACKET_CDECL fun_00595140(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_460(PacketReader*);
void PACKET_CDECL fun_00595250(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_468(PacketReader*);
void PACKET_CDECL fun_005952e0(PacketReader*);
void PACKET_CDECL fun_00595350(PacketReader*);
void PACKET_CDECL fun_005953a0(PacketReader*);
void PACKET_CDECL fun_00595440(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_47c(PacketReader*);
void PACKET_CDECL fun_005954c0(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_484(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_488(PacketReader*);
void PACKET_CDECL fun_00595590(PacketReader*);
void PACKET_CDECL fun_00595630(PacketReader*);
void PACKET_CDECL fun_00595680(PacketReader*);
void PACKET_CDECL fun_00595740(PacketReader*);
void PACKET_CDECL fun_005957c0(PacketReader*);
void PACKET_CDECL fun_00595840(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_4b4(PacketReader*);
void PACKET_CDECL fun_005958e0(PacketReader*);
void PACKET_CDECL fun_00595930(PacketReader*);
void PACKET_CDECL fun_00595990(PacketReader*);
void PACKET_CDECL fun_005959e0(PacketReader*);
void PACKET_CDECL fun_00595a40(PacketReader*);
void PACKET_CDECL fun_00595ba0(PacketReader*);
void PACKET_CDECL fun_00595bf0(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_4dc(PacketReader*);
void PACKET_CDECL fun_00595c70(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_4e4(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_4e8(PacketReader*);
void PACKET_CDECL fun_00595d20(PacketReader*);
void PACKET_CDECL fun_00595d70(PacketReader*);
void PACKET_CDECL fun_00595dc0(PacketReader*);
void PACKET_CDECL fun_00595e10(PacketReader*);
void PACKET_CDECL fun_00595e60(PacketReader*);
void PACKET_CDECL fun_00595eb0(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_4fc(PacketReader*);
void PACKET_CDECL fun_00595f30(PacketReader*);
void PACKET_CDECL fun_00595f80(PacketReader*);
void PACKET_CDECL fun_00595fd0(PacketReader*);
void PACKET_CDECL fun_00596020(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_514(PacketReader*);
void PACKET_CDECL fun_005960b0(PacketReader*);
void PACKET_CDECL fun_00596100(PacketReader*);
void PACKET_CDECL fun_00596150(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_524(PacketReader*);
void PACKET_CDECL fun_00596210(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_530(PacketReader*);
void PACKET_CDECL fun_00596290(PacketReader*);
void PACKET_CDECL dispatch_packet_u16_to_session_slot_538(PacketReader*);
void PACKET_CDECL fun_00596310(PacketReader*);
void PACKET_CDECL fun_00596380(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_544(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_54c(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_550(PacketReader*);
void PACKET_CDECL fun_00596490(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_558(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_55c(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_560(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_564(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_568(PacketReader*);
void PACKET_CDECL fun_005965f0(PacketReader*);
void PACKET_CDECL fun_00596740(PacketReader*);
void PACKET_CDECL fun_00596950(PacketReader*);
void PACKET_CDECL fun_005969b0(PacketReader*);
void PACKET_CDECL fun_00596a40(PacketReader*);
void PACKET_CDECL fun_00596aa0(PacketReader*);
void PACKET_CDECL fun_00596b30(PacketReader*);
void PACKET_CDECL fun_00596b90(PacketReader*);
void PACKET_CDECL fun_00596c30(PacketReader*);
void PACKET_CDECL fun_00596d10(PacketReader*);
void PACKET_CDECL fun_00596d70(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_584(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_588(PacketReader*);
void PACKET_CDECL fun_00596e20(PacketReader*);
void PACKET_CDECL fun_00596e80(PacketReader*);
void PACKET_CDECL fun_00596f00(PacketReader*);
void PACKET_CDECL fun_00596f50(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_2c4(PacketReader*);
void PACKET_CDECL fun_00596fd0(PacketReader*);
void PACKET_CDECL fun_00597040(PacketReader*);
void PACKET_CDECL fun_005970e0(PacketReader*);
void PACKET_CDECL fun_00597160(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_5b4(PacketReader*);
void PACKET_CDECL fun_00597250(PacketReader*);
void PACKET_CDECL fun_00597380(PacketReader*);
void PACKET_CDECL fun_005974a0(PacketReader*);
void PACKET_CDECL fun_005975c0(PacketReader*);
void PACKET_CDECL fun_00597640(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_604(PacketReader*);
void PACKET_CDECL fun_005976d0(PacketReader*);
void PACKET_CDECL fun_00597720(PacketReader*);
void PACKET_CDECL fun_00597780(PacketReader*);
void PACKET_CDECL fun_005977d0(PacketReader*);
void PACKET_CDECL fun_00597830(PacketReader*);
void PACKET_CDECL fun_00597870(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_5ec(PacketReader*);
void PACKET_CDECL fun_005978f0(PacketReader*);
void PACKET_CDECL fun_00597940(PacketReader*);
void PACKET_CDECL fun_005979b0(PacketReader*);
void PACKET_CDECL dispatch_packet_u32_to_session_slot_60c(PacketReader*);
void PACKET_CDECL fun_00597a30(PacketReader*);
void PACKET_CDECL fun_00597a80(PacketReader*);
void PACKET_CDECL fun_00597ae0(PacketReader*);
void PACKET_CDECL fun_00597b10(PacketReader*);
void PACKET_CDECL fun_00597c40(PacketReader*);
void PACKET_CDECL dispatch_packet_u8_to_session_slot_618(PacketReader*);
void PACKET_CDECL fun_0059cf10(PacketReader*);
}

namespace {
template <class Callback> Callback method(SessionPrefix* session, uint32_t offset) {
    const uint8_t* p = reinterpret_cast<const uint8_t*>(session->callbacks) + offset;
    const uintptr_t address =
        uint32_t(p[0]) | uint32_t(p[1]) << 8 | uint32_t(p[2]) << 16 | uint32_t(p[3]) << 24;
    return reinterpret_cast<Callback>(address);
}
void virtual_no_args(uint32_t slot) {
    SessionPrefix* session = dat_0224a328;
    method<void(PACKET_THISCALL*)(SessionPrefix*)>(session, slot)(session);
}
void unknown_packet(uint32_t opcode, PacketReader* reader) {
    SessionPrefix* session = dat_0224a328;
    method<void(PACKET_THISCALL*)(SessionPrefix*, uint32_t, PacketReader*)>(session, 0x630)(
        session, opcode, reader);
}
} // namespace

extern "C" void PACKET_CDECL fun_0059cf70(uint32_t opcode, PacketReader* reader) {
    switch (opcode & 0xffffu) {
    case 0x0002:
        virtual_no_args(0x10);
        return;
    case 0x0004:
        fun_0058d830(reader);
        return;
    case 0x0101:
        fun_0058d860(reader);
        return;
    case 0x0102:
        fun_0058db20(reader);
        return;
    case 0x0103:
        fun_0058db50(reader);
        return;
    case 0x0104:
        fun_0058db90(reader);
        return;
    case 0x0105:
        fun_0058dbd0(reader);
        return;
    case 0x0106:
        fun_0058dd30(reader);
        return;
    case 0x0107:
        fun_004015a0();
        virtual_no_args(0x38);
        return;
    case 0x0108:
        fun_0058e020(reader);
        return;
    case 0x0109:
        fun_0058e0e0(reader);
        return;
    case 0x010a:
        fun_00591d70(reader);
        return;
    case 0x010b:
        fun_00591dd0(reader);
        return;
    case 0x010d:
        virtual_no_args(0x3c);
        return;
    case 0x010e:
        dispatch_packet_u8_to_session_slot_050(reader);
        return;
    case 0x010f:
        fun_00591e30(reader);
        return;
    case 0x0110:
        dispatch_packet_u8_to_session_slot_040(reader);
        return;
    case 0x0111:
        fun_0058e190(reader);
        return;
    case 0x0112:
        fun_0058e120(reader);
        return;
    case 0x0113:
        virtual_no_args(0x4c);
        return;
    case 0x0116:
        fun_0058e240(reader);
        return;
    case 0x0117:
        fun_00594cd0(reader);
        return;
    case 0x0201:
        fun_0058e280(reader);
        return;
    case 0x0202:
        dispatch_packet_u32_to_session_slot_064(reader);
        return;
    case 0x0204:
        fun_0058e510(reader);
        return;
    case 0x0205:
        fun_0058eb30(reader);
        return;
    case 0x0206:
        fun_0058eca0(reader);
        return;
    case 0x0207:
        fun_0058ed20(reader);
        return;
    case 0x0208:
        fun_0058eda0(reader);
        return;
    case 0x0209:
        fun_0058ee30(reader);
        return;
    case 0x020a:
        fun_00597a30(reader);
        return;
    case 0x020b:
        fun_0058ef60(reader);
        return;
    case 0x020c:
        fun_00595630(reader);
        return;
    case 0x020d:
        fun_0058efe0(reader);
        return;
    case 0x020e:
        fun_0058f030(reader);
        return;
    case 0x020f:
        fun_0058f080(reader);
        return;
    case 0x0210:
        dispatch_packet_u8_to_session_slot_08c(reader);
        return;
    case 0x0211:
        fun_0058eed0(reader);
        return;
    case 0x0212:
        virtual_no_args(0x94);
        return;
    case 0x0213:
        dispatch_packet_u32_to_session_slot_098(reader);
        return;
    case 0x0214:
        fun_00595680(reader);
        return;
    case 0x0215:
        fun_00595740(reader);
        return;
    case 0x0216:
        fun_00595bf0(reader);
        return;
    case 0x0217:
        dispatch_packet_u32_to_session_slot_4dc(reader);
        return;
    case 0x0218:
        fun_00595d20(reader);
        return;
    case 0x0219:
        fun_00595d70(reader);
        return;
    case 0x021a:
        fun_00595dc0(reader);
        return;
    case 0x021b:
        fun_00596100(reader);
        return;
    case 0x021c:
        fun_00595c70(reader);
        return;
    case 0x021d:
        dispatch_packet_u32_to_session_slot_4e4(reader);
        return;
    case 0x021e:
        dispatch_packet_u8_to_session_slot_4e8(reader);
        return;
    case 0x0220:
        fun_00596150(reader);
        return;
    case 0x0221:
        dispatch_packet_u32_to_session_slot_524(reader);
        return;
    case 0x0222:
        fun_00596210(reader);
        return;
    case 0x0223:
        dispatch_packet_u32_to_session_slot_530(reader);
        return;
    case 0x0224:
        fun_00596290(reader);
        return;
    case 0x0225:
        fun_00596950(reader);
        return;
    case 0x0226:
        fun_0058fc50(reader);
        return;
    case 0x0228:
        virtual_no_args(0x10c);
        return;
    case 0x0230:
        dispatch_packet_u16_to_session_slot_058(reader);
        return;
    case 0x0301:
        fun_0058f0d0(reader);
        return;
    case 0x0302:
        fun_0058f200(reader);
        return;
    case 0x0303:
        fun_0058e360(reader);
        return;
    case 0x0304:
        fun_0058f260(reader);
        return;
    case 0x0305:
        fun_0058f2d0(reader);
        return;
    case 0x0307:
        fun_0058f150(reader);
        return;
    case 0x0401:
        fun_0058f320(reader);
        return;
    case 0x0402:
        dispatch_packet_u32_to_session_slot_0d0(reader);
        return;
    case 0x0403:
        fun_0058f410(reader);
        return;
    case 0x0404:
        dispatch_packet_u32_to_session_slot_0d8(reader);
        return;
    case 0x0405:
        fun_00591e70(reader);
        return;
    case 0x0406:
        dispatch_packet_u32_to_session_slot_218(reader);
        return;
    case 0x0451:
        fun_0058f490(reader);
        return;
    case 0x0501:
        fun_0058f4f0(reader);
        return;
    case 0x0502:
        fun_0058f640(reader);
        return;
    case 0x0503:
        fun_0058f6d0(reader);
        return;
    case 0x0504:
        fun_0058f760(reader);
        return;
    case 0x0505:
        fun_0058f7c0(reader);
        return;
    case 0x0506:
        fun_0058f830(reader);
        return;
    case 0x0507:
        fun_0058f980(reader);
        return;
    case 0x0508:
        fun_0058fa30(reader);
        return;
    case 0x0509:
        return;
    case 0x050a:
        fun_0058fbc0(reader);
        return;
    case 0x050b:
        fun_0058fcd0(reader);
        return;
    case 0x050c:
        fun_0058fd30(reader);
        return;
    case 0x050d:
        fun_0058fd80(reader);
        return;
    case 0x050e:
        dispatch_packet_u32_to_session_slot_13c(reader);
        return;
    case 0x050f:
        fun_0058fe10(reader);
        return;
    case 0x0510:
        fun_0058fea0(reader);
        return;
    case 0x0511:
        fun_0058ff10(reader);
        return;
    case 0x0512:
        dispatch_packet_11_mixed_fields_to_session_slot_150(reader);
        return;
    case 0x0513:
        fun_00590120(reader);
        return;
    case 0x0514:
        fun_005901e0(reader);
        return;
    case 0x0515:
        fun_00590280(reader);
        return;
    case 0x0516:
        fun_00590300(reader);
        return;
    case 0x0517:
        fun_00590370(reader);
        return;
    case 0x0518:
        dispatch_packet_11_mixed_fields_to_session_slot_168(reader);
        return;
    case 0x0519:
        fun_00590520(reader);
        return;
    case 0x051a:
        fun_005905e0(reader);
        return;
    case 0x051b:
        fun_00590680(reader);
        return;
    case 0x051c:
        fun_00591a30(reader);
        return;
    case 0x051d:
        fun_00591fe0(reader);
        return;
    case 0x051e:
        fun_0058fac0(reader);
        return;
    case 0x051f:
        fun_0058fb50(reader);
        return;
    case 0x0520:
        fun_00590700(reader);
        return;
    case 0x0521:
        fun_00595090(reader);
        return;
    case 0x0522:
        fun_005950f0(reader);
        return;
    case 0x0523:
        fun_005957c0(reader);
        return;
    case 0x0524:
        fun_00592030(reader);
        return;
    case 0x0525:
        dispatch_packet_u16_to_session_slot_538(reader);
        return;
    case 0x0526:
        dispatch_packet_12_dwords_to_session_slot_0fc(reader);
        return;
    case 0x0527:
        virtual_no_args(0x628);
        return;
    case 0x0551:
        fun_00592090(reader);
        return;
    case 0x0554:
        fun_0058f5b0(reader);
        return;
    case 0x0555:
        dispatch_packet_u16_to_session_slot_128(reader);
        return;
    case 0x0558:
        fun_0058ffd0(reader);
        return;
    case 0x0601:
        fun_00590b50(reader);
        return;
    case 0x0602:
        dispatch_packet_u32_to_session_slot_194(reader);
        return;
    case 0x0603:
        fun_00590c00(reader);
        return;
    case 0x0604:
        dispatch_packet_u32_to_session_slot_19c(reader);
        return;
    case 0x0605:
        fun_00590ca0(reader);
        return;
    case 0x0606:
        fun_00590d30(reader);
        return;
    case 0x0607:
        fun_00590df0(reader);
        return;
    case 0x0608:
        fun_00590d90(reader);
        return;
    case 0x0609:
        fun_00591a90(reader);
        return;
    case 0x060b:
        dispatch_packet_9_mixed_fields_to_session_slot_17c(reader);
        return;
    case 0x060c:
        dispatch_packet_12_mixed_fields_to_session_slot_180(reader);
        return;
    case 0x060d:
        fun_00590970(reader);
        return;
    case 0x060e:
        fun_00590a30(reader);
        return;
    case 0x060f:
        fun_00590ad0(reader);
        return;
    case 0x0610:
        fun_00590750(reader);
        return;
    case 0x0701:
        fun_00590e80(reader);
        return;
    case 0x0702:
        fun_00590ef0(reader);
        return;
    case 0x0703:
        fun_00590f90(reader);
        return;
    case 0x0711:
        fun_00591030(reader);
        return;
    case 0x0801:
        dispatch_packet_13_mixed_fields_to_session_slot_1c8(reader);
        return;
    case 0x0802:
        fun_005918a0(reader);
        return;
    case 0x0803:
        fun_00596e80(reader);
        return;
    case 0x0804:
        fun_00596f00(reader);
        return;
    case 0x0805:
        fun_005917b0(reader);
        return;
    case 0x0806:
        fun_00591170(reader);
        return;
    case 0x0807:
        fun_005911e0(reader);
        return;
    case 0x0808:
        fun_005915f0(reader);
        return;
    case 0x080b:
        fun_00591330(reader);
        return;
    case 0x080c:
        fun_00591330(reader);
        return;
    case 0x080d:
        fun_00591490(reader);
        return;
    case 0x0901:
        fun_00591b50(reader);
        return;
    case 0x0902:
        fun_00591bb0(reader);
        return;
    case 0x0903:
        dispatch_packet_10_mixed_fields_to_session_slot_200(reader);
        return;
    case 0x0905:
        fun_00591ce0(reader);
        return;
    case 0x0906:
        fun_00591af0(reader);
        return;
    case 0x0907:
        dispatch_packet_u16_to_session_slot_208(reader);
        return;
    case 0x0a01:
        dispatch_packet_u32_to_session_slot_29c(reader);
        return;
    case 0x0a03:
        fun_00592cc0(reader);
        return;
    case 0x0a04:
        dispatch_packet_u8_to_session_slot_2a4(reader);
        return;
    case 0x0a05:
        fun_00592d40(reader);
        return;
    case 0x0a06:
        fun_00596fd0(reader);
        return;
    case 0x0a07:
        fun_00592de0(reader);
        return;
    case 0x0a08:
        fun_00592e30(reader);
        return;
    case 0x0a09:
        fun_00597040(reader);
        return;
    case 0x0a0a:
        fun_00592d90(reader);
        return;
    case 0x0b01:
        fun_00592480(reader);
        return;
    case 0x0b02:
        fun_00592620(reader);
        return;
    case 0x0b03:
        fun_00592650(reader);
        return;
    case 0x0b04:
        fun_005926a0(reader);
        return;
    case 0x0b05:
        dispatch_packet_u32_to_session_slot_260(reader);
        return;
    case 0x0b06:
        dispatch_packet_u32_to_session_slot_264(reader);
        return;
    case 0x0b07:
        dispatch_packet_u32_to_session_slot_268(reader);
        return;
    case 0x0b08:
        fun_00592bd0(reader, 0);
        return;
    case 0x0b09:
        fun_0058d5c0(reader);
        return;
    case 0x0b0b:
        fun_00596740(reader);
        return;
    case 0x0b0c:
        fun_005965f0(reader);
        return;
    case 0x0b0d:
        dispatch_packet_u32_to_session_slot_544(reader);
        return;
    case 0x0b0e:
        fun_00596380(reader);
        return;
    case 0x0b0f:
        dispatch_packet_u32_to_session_slot_54c(reader);
        return;
    case 0x0b10:
        dispatch_packet_u8_to_session_slot_550(reader);
        return;
    case 0x0b12:
        fun_00596490(reader);
        return;
    case 0x0b13:
        dispatch_packet_u32_to_session_slot_55c(reader);
        return;
    case 0x0b14:
        dispatch_packet_u32_to_session_slot_568(reader);
        return;
    case 0x0b15:
        fun_00592650(reader);
        return;
    case 0x0b16:
        fun_0058d6f0(reader);
        return;
    case 0x0b17:
        dispatch_packet_u32_to_session_slot_558(reader);
        return;
    case 0x0b18:
        fun_0058d710(reader);
        return;
    case 0x0b19:
        dispatch_packet_u32_to_session_slot_564(reader);
        return;
    case 0x0b1a:
        dispatch_packet_u32_to_session_slot_560(reader);
        return;
    case 0x0b1b:
        fun_0059cf10(reader);
        return;
    case 0x0b1c:
        fun_00592c30(reader);
        return;
    case 0x0c01:
        fun_00592870(reader, 0);
        return;
    case 0x0c02:
        fun_005928d0(reader, 0);
        return;
    case 0x0c03:
        fun_00592930(reader, 0);
        return;
    case 0x0c04:
        fun_005929a0(reader, 0);
        return;
    case 0x0c05:
        fun_00592a00(reader, 0);
        return;
    case 0x0c06:
        fun_00592a60(reader, 0);
        return;
    case 0x0c07:
        fun_00592a90(reader, 0);
        return;
    case 0x0c08:
        fun_00592b10(reader, 0);
        return;
    case 0x0c09:
        fun_00592b80(reader, 0);
        return;
    case 0x0c0a:
        fun_00592870(reader, 1);
        return;
    case 0x0c0b:
        fun_005928d0(reader, 1);
        return;
    case 0x0c0c:
        fun_00592930(reader, 1);
        return;
    case 0x0c0d:
        fun_00592b10(reader, 1);
        return;
    case 0x0c0e:
        fun_005929a0(reader, 1);
        return;
    case 0x0c10:
        fun_00592a00(reader, 1);
        return;
    case 0x0c11:
        fun_00592a60(reader, 1);
        return;
    case 0x0c12:
        fun_00592a90(reader, 1);
        return;
    case 0x0c13:
        fun_00592b80(reader, 1);
        return;
    case 0x0c14:
        fun_00592bd0(reader, 1);
        return;
    case 0x0d01:
        fun_00594620(reader);
        return;
    case 0x0d02:
        fun_005945c0(reader);
        return;
    case 0x0d03:
        dispatch_packet_u8_to_session_slot_3bc(reader);
        return;
    case 0x0d04:
        dispatch_packet_u32_to_session_slot_3b8(reader);
        return;
    case 0x0d05:
        dispatch_packet_u32_to_session_slot_3c0(reader);
        return;
    case 0x0d06:
        fun_00594740(reader);
        return;
    case 0x0d07:
        dispatch_packet_u8_to_session_slot_3c8(reader);
        return;
    case 0x0d08:
        fun_005947c0(reader);
        return;
    case 0x0d09:
        dispatch_packet_u8_to_session_slot_3d0(reader);
        return;
    case 0x0d0a:
        fun_00594860(reader);
        return;
    case 0x0d0b:
        fun_005948b0(reader);
        return;
    case 0x0d0c:
        fun_00594940(reader);
        return;
    case 0x0d0d:
        virtual_no_args(0x3e0);
        return;
    case 0x0d0e:
        virtual_no_args(0x3e4);
        return;
    case 0x0d0f:
        fun_00594990(reader);
        return;
    case 0x0d10:
        fun_005949f0(reader);
        return;
    case 0x0d11:
        dispatch_packet_u32_to_session_slot_3f0(reader);
        return;
    case 0x0d12:
        fun_00594ac0(reader);
        return;
    case 0x0d13:
        fun_00594b20(reader);
        return;
    case 0x0d14:
        fun_00594b80(reader);
        return;
    case 0x0d15:
        dispatch_packet_u32_to_session_slot_404(reader);
        return;
    case 0x0d16:
        fun_00594c00(reader);
        return;
    case 0x0d17:
        fun_00594c60(reader);
        return;
    case 0x0d18:
        dispatch_packet_u32_to_session_slot_410(reader);
        return;
    case 0x0d19:
        fun_00594a60(reader);
        return;
    case 0x0d20:
        fun_00597870(reader);
        return;
    case 0x0d21:
        fun_005975c0(reader);
        return;
    case 0x0d22:
        fun_005945c0(reader);
        return;
    case 0x0d23:
        dispatch_packet_u32_to_session_slot_5ec(reader);
        return;
    case 0x0d24:
        fun_005977d0(reader);
        return;
    case 0x0d25:
        fun_00597940(reader);
        return;
    case 0x0d26:
        fun_005976d0(reader);
        return;
    case 0x0d27:
        fun_00597640(reader);
        return;
    case 0x0d28:
        fun_005979b0(reader);
        return;
    case 0x0d29:
        fun_00597250(reader);
        return;
    case 0x0d2f:
        fun_00597720(reader);
        return;
    case 0x0d30:
        fun_00597830(reader);
        return;
    case 0x0d31:
        fun_00597380(reader);
        return;
    case 0x0d32:
        fun_005974a0(reader);
        return;
    case 0x0d34:
        fun_005978f0(reader);
        return;
    case 0x0d35:
        fun_00597780(reader);
        return;
    case 0x0d36:
        dispatch_packet_u8_to_session_slot_604(reader);
        return;
    case 0x0d37:
        fun_00597a80(reader);
        return;
    case 0x0d38:
        dispatch_packet_u32_to_session_slot_60c(reader);
        return;
    case 0x0e01:
        fun_00592f50(reader);
        return;
    case 0x0e02:
        dispatch_packet_u32_to_session_slot_2d4(reader);
        return;
    case 0x0e03:
        fun_00593020(reader);
        return;
    case 0x0e04:
        dispatch_packet_u32_to_session_slot_2dc(reader);
        return;
    case 0x0e05:
        fun_005930d0(reader);
        return;
    case 0x0e06:
        fun_00593140(reader);
        return;
    case 0x0f01:
        fun_00592e80(reader);
        return;
    case 0x0f02:
        dispatch_packet_u8_to_session_slot_2cc(reader);
        return;
    case 0x1101:
        fun_005931b0(reader);
        return;
    case 0x1102:
        fun_00593230(reader);
        return;
    case 0x1103:
        fun_005932d0(reader);
        return;
    case 0x1104:
        fun_00593360(reader);
        return;
    case 0x1105:
        fun_005933f0(reader);
        return;
    case 0x1106:
        dispatch_packet_u8_to_session_slot_2f0(reader);
        return;
    case 0x1107:
        fun_005934a0(reader);
        return;
    case 0x1108:
        fun_00593510(reader);
        return;
    case 0x1109:
        fun_005935a0(reader);
        return;
    case 0x110a:
        fun_00593640(reader);
        return;
    case 0x110b:
        fun_00593690(reader);
        return;
    case 0x1111:
        fun_00593700(reader);
        return;
    case 0x1112:
        fun_00596310(reader);
        return;
    case 0x2101:
        fun_00594d20(reader);
        return;
    case 0x2102:
        fun_00594d80(reader);
        return;
    case 0x2103:
        fun_00594dd0(reader);
        return;
    case 0x2104:
        fun_00594e30(reader);
        return;
    case 0x2201:
        fun_00595140(reader);
        return;
    case 0x2202:
        fun_0058d6c0(reader);
        return;
    case 0x2203:
        dispatch_packet_u8_to_session_slot_460(reader);
        return;
    case 0x2204:
        fun_00595250(reader);
        return;
    case 0x2205:
        dispatch_packet_u32_to_session_slot_468(reader);
        return;
    case 0x2206:
        fun_005952e0(reader);
        return;
    case 0x2207:
        fun_00595350(reader);
        return;
    case 0x2208:
        fun_005953a0(reader);
        return;
    case 0x2209:
        fun_00595440(reader);
        return;
    case 0x220a:
        dispatch_packet_u32_to_session_slot_47c(reader);
        return;
    case 0x220b:
        fun_005954c0(reader);
        return;
    case 0x220c:
        dispatch_packet_u8_to_session_slot_488(reader);
        return;
    case 0x220d:
        fun_00595590(reader);
        return;
    case 0x220e:
        dispatch_packet_u8_to_session_slot_484(reader);
        return;
    case 0x2301:
        virtual_no_args(0x4a0);
        return;
    case 0x2302:
        virtual_no_args(0x4a4);
        return;
    case 0x2303:
        virtual_no_args(0x4a8);
        return;
    case 0x2304:
        virtual_no_args(0x4ac);
        return;
    case 0x2305:
        fun_00595840(reader);
        return;
    case 0x2306:
        dispatch_packet_u8_to_session_slot_4b4(reader);
        return;
    case 0x2307:
        fun_005958e0(reader);
        return;
    case 0x2308:
        fun_00595930(reader);
        return;
    case 0x2309:
        fun_00595990(reader);
        return;
    case 0x230a:
        virtual_no_args(0x4c4);
        return;
    case 0x230b:
        fun_005959e0(reader);
        return;
    case 0x230c:
        virtual_no_args(0x4cc);
        return;
    case 0x230d:
        fun_00595a40(reader);
        return;
    case 0x230e:
        fun_00595ba0(reader);
        return;
    case 0x2401:
        fun_00595e10(reader);
        return;
    case 0x2402:
        fun_00595e60(reader);
        return;
    case 0x2403:
        fun_00595eb0(reader);
        return;
    case 0x2404:
        virtual_no_args(0x4f8);
        return;
    case 0x2405:
        dispatch_packet_u8_to_session_slot_4fc(reader);
        return;
    case 0x2406:
        fun_00595f30(reader);
        return;
    case 0x2407:
        fun_00596f50(reader);
        return;
    case 0x2408:
        dispatch_packet_u8_to_session_slot_2c4(reader);
        return;
    case 0x2409:
        fun_00592d40(reader);
        return;
    case 0x240a:
        fun_00596fd0(reader);
        return;
    case 0x240b:
        fun_00592de0(reader);
        return;
    case 0x240c:
        fun_00592e30(reader);
        return;
    case 0x240d:
        fun_00597040(reader);
        return;
    case 0x2501:
        fun_00595f80(reader);
        return;
    case 0x2502:
        fun_00595fd0(reader);
        return;
    case 0x2503:
        fun_00596020(reader);
        return;
    case 0x2504:
        virtual_no_args(0x510);
        return;
    case 0x2505:
        dispatch_packet_u8_to_session_slot_514(reader);
        return;
    case 0x2506:
        fun_005960b0(reader);
        return;
    case 0x2601:
        fun_005970e0(reader);
        return;
    case 0x2602:
        fun_00597160(reader);
        return;
    case 0x2603:
        fun_00596b90(reader);
        return;
    case 0x2604:
        fun_00596c30(reader);
        return;
    case 0x2605:
        dispatch_packet_u32_to_session_slot_5b4(reader);
        return;
    case 0x2606:
        fun_00596aa0(reader);
        return;
    case 0x2607:
        fun_00596b30(reader);
        return;
    case 0x2609:
        fun_00596d10(reader);
        return;
    case 0x2701:
        fun_00597b10(reader);
        return;
    case 0x2702:
        fun_00597c40(reader);
        return;
    case 0x2703:
        dispatch_packet_u8_to_session_slot_618(reader);
        return;
    case 0x2704:
        fun_00597ae0(reader);
        return;
    case 0x3101:
        dispatch_packet_u8_to_session_slot_428(reader);
        return;
    case 0x3102:
        fun_00594ec0(reader);
        return;
    case 0x3103:
        fun_00594f20(reader);
        return;
    case 0x3104:
        dispatch_packet_u8_to_session_slot_434(reader);
        return;
    case 0x3105:
        virtual_no_args(0x438);
        return;
    case 0x3106:
        dispatch_packet_u32_to_session_slot_43c(reader);
        return;
    case 0x3107:
        fun_00595000(reader);
        return;
    case 0x3108:
        dispatch_packet_u8_to_session_slot_444(reader);
        return;
    case 0x3109:
        virtual_no_args(0x448);
        return;
    case 0x3110:
        fun_0058d690(reader);
        return;
    case 0xa101:
        fun_00592120(reader);
        return;
    case 0xa102:
        fun_005921b0(reader);
        return;
    case 0xa104:
        fun_005922d0(reader);
        return;
    case 0xa105:
        fun_005922a0(reader);
        return;
    case 0xa107:
        virtual_no_args(0x238);
        return;
    case 0xa108:
        fun_00592380(reader);
        return;
    case 0xa201:
        fun_00592220(reader);
        return;
    case 0xa202:
        fun_005923d0(reader);
        return;
    case 0xa301:
        fun_00592420(reader);
        return;
    case 0xa302:
        fun_0058d790(reader);
        return;
    case 0xa303:
        fun_0058d7e0(reader);
        return;
    case 0xb101:
        fun_005969b0(reader);
        return;
    case 0xb102:
        fun_00596a40(reader);
        return;
    case 0xb103:
        fun_00596d70(reader);
        return;
    case 0xb104:
        dispatch_packet_u32_to_session_slot_584(reader);
        return;
    case 0xb105:
        dispatch_packet_u32_to_session_slot_588(reader);
        return;
    case 0xb106:
        fun_00596e20(reader);
        return;
    case 0xf101:
        fun_00593790(reader);
        return;
    case 0xf102:
        fun_00593810(reader);
        return;
    case 0xf103:
        fun_005938b0(reader);
        return;
    case 0xf104:
        fun_00593940(reader);
        return;
    case 0xf105:
        fun_005939d0(reader);
        return;
    case 0xf106:
        fun_00593a50(reader);
        return;
    case 0xf107:
        fun_0058d5f0(reader);
        return;
    case 0xf109:
        fun_0058d640(reader);
        return;
    case 0xf10a:
        fun_00596310(reader);
        return;
    case 0xf201:
        fun_00593ab0(reader);
        return;
    case 0xf204:
        dispatch_packet_u16_to_session_slot_314(reader);
        return;
    case 0xf501:
        dispatch_packet_u16_to_session_slot_318(reader);
        return;
    case 0xf601:
        dispatch_packet_u8_to_session_slot_3a0(reader);
        return;
    case 0xf602:
        dispatch_packet_u8_to_session_slot_3a4(reader);
        return;
    case 0xf603:
        fun_00594560(reader);
        return;
    case 0xf701:
        fun_00594480(reader);
        return;
    case 0xf709:
        virtual_no_args(0x398);
        return;
    case 0xf70a:
        dispatch_packet_u16_to_session_slot_39c(reader);
        return;
    case 0xf802:
        virtual_no_args(0x374);
        return;
    case 0xf803:
        virtual_no_args(0x378);
        return;
    case 0xf804:
        virtual_no_args(0x37c);
        return;
    case 0xf805:
        dispatch_packet_u16_to_session_slot_380(reader);
        return;
    case 0xf80b:
        dispatch_packet_u16_to_session_slot_384(reader);
        return;
    case 0xf80c:
        dispatch_packet_u16_to_session_slot_388(reader);
        return;
    case 0xf80f:
        dispatch_packet_u16_to_session_slot_38c(reader);
        return;
    case 0xf810:
        dispatch_packet_u16_to_session_slot_390(reader);
        return;
    case 0xf901:
        fun_00593e30(reader);
        return;
    case 0xf904:
        fun_00593fd0(reader);
        return;
    case 0xf905:
        fun_00594050(reader);
        return;
    case 0xf906:
        fun_00594150(reader);
        return;
    case 0xf907:
        fun_005941b0(reader);
        return;
    case 0xf908:
        fun_00594210(reader);
        return;
    case 0xf909:
        fun_00594270(reader);
        return;
    case 0xf90a:
        fun_005942d0(reader);
        return;
    case 0xf90b:
        fun_00594330(reader);
        return;
    case 0xf90c:
        fun_005940d0(reader);
        return;
    case 0xfa07:
        fun_00593be0(reader);
        return;
    case 0xfa08:
        fun_00593c40(reader);
        return;
    case 0xfa09:
        fun_00593cb0(reader);
        return;
    case 0xfa0a:
        fun_00593d30(reader);
        return;
    case 0xfa0d:
        virtual_no_args(0x33c);
        return;
    case 0xfa0e:
        virtual_no_args(0x340);
        return;
    case 0xfa0f:
        virtual_no_args(0x344);
        return;
    case 0xfa10:
        virtual_no_args(0x348);
        return;
    case 0xfa11:
        fun_00593db0(reader);
        return;
    case 0xfa12:
        fun_00593db0(reader);
        return;
    default:
        unknown_packet(opcode, reader);
        return;
    }
}
