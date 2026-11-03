#pragma once

#include <stddef.h>
#include <stdint.h>

// This prefix describes only offsets read/written by the recovered procedures.
// Unknown fields and unknown vtable entries have deliberately not been invented.
// All layouts and calling conventions below are for the original 32-bit client.
#define PACKET_EXPORT __declspec(dllexport)
#define PACKET_THISCALL __attribute__((thiscall))
#define PACKET_CDECL __attribute__((cdecl))

struct PacketReader {
    uint8_t bytes[0x2000];
    uint32_t length;
    uint8_t* cursor;
    uint8_t* end;
};

struct SessionPrefix;
struct ServerListRecord {
    uint8_t bytes[0x26];
};
typedef void(PACKET_THISCALL* Callback220)(SessionPrefix*, uint32_t, uint8_t, uint16_t);
typedef void(PACKET_THISCALL* Callback224)(SessionPrefix*, uint32_t, uint8_t, uint32_t, uint32_t,
                                           uint32_t, uint32_t);
typedef void(PACKET_THISCALL* ChallengeResult)(SessionPrefix*, uint8_t, uint8_t, uint8_t,
                                               const uint8_t*, const uint8_t*);
typedef void(PACKET_THISCALL* ServerListResult)(SessionPrefix*, uint8_t, const ServerListRecord*);
typedef void(PACKET_THISCALL* DwordResult)(SessionPrefix*, uint32_t);
typedef void(PACKET_THISCALL* ByteDwordResult)(SessionPrefix*, uint8_t, uint32_t);
typedef void(PACKET_THISCALL* LoginResult)(SessionPrefix*, uint8_t, uint32_t, uint8_t,
                                           const uint8_t*);
typedef void(PACKET_THISCALL* WorldAddress)(SessionPrefix*, uint8_t, uint32_t);
typedef void(PACKET_THISCALL* SeedResult)(SessionPrefix*, uint8_t, uint8_t, const uint8_t*);
typedef void(PACKET_THISCALL* SingleStatus)(SessionPrefix*, uint8_t);
typedef void(PACKET_THISCALL* TwoByteStatus)(SessionPrefix*, uint8_t, uint8_t);
typedef void(PACKET_THISCALL* ReadDiagnostic)(SessionPrefix*, PacketReader*);
typedef void(PACKET_THISCALL* UnknownPacket)(SessionPrefix*, uint32_t, PacketReader*);

struct SessionCallbacks {
    void* unknown_000[0x220 / 4];
    Callback220 callback_220;
    Callback224 callback_224;
    ChallengeResult challenge_a101;
    LoginResult login_result;
    SingleStatus status_a105;
    void* unknown_234[(0x23c - 0x234) / 4];
    TwoByteStatus status_a108;
    ServerListResult server_list;
    void* unknown_244;
    WorldAddress world_address;
    SeedResult seed_result;
    void* unknown_250;
    DwordResult callback_254;
    ByteDwordResult callback_258;
    void* unknown_25c[(0x62c - 0x25c) / 4];
    ReadDiagnostic read_diagnostic;
    UnknownPacket unknown_packet;
};

#pragma pack(push, 1)
struct SessionPrefix {
    SessionCallbacks* callbacks;
    uint8_t unknown_004[0x1ec - 4];
    uint32_t state;
    uint32_t world_ipv4;
    uint32_t user_id_1f4;
    uint32_t user_id_1f8;
    uint32_t field_1fc;
    uint32_t field_200;
    uint8_t field_204;
    uint8_t unknown_205[0x46f - 0x205];
    uint8_t login_token[16];
};
#pragma pack(pop)

struct SessionStorage {
    SessionPrefix prefix;
    uint8_t unknown_47f[0x4a0 - sizeof(SessionPrefix)];
};

static_assert(sizeof(void*) == 4, "Recovered client code requires a 32-bit target");
static_assert(offsetof(PacketReader, length) == 0x2000);
static_assert(offsetof(PacketReader, cursor) == 0x2004);
static_assert(offsetof(PacketReader, end) == 0x2008);
static_assert(sizeof(PacketReader) == 0x200c);
static_assert(offsetof(SessionCallbacks, login_result) == 0x22c);
static_assert(offsetof(SessionCallbacks, challenge_a101) == 0x228);
static_assert(offsetof(SessionCallbacks, server_list) == 0x240);
static_assert(offsetof(SessionCallbacks, callback_220) == 0x220);
static_assert(offsetof(SessionCallbacks, callback_224) == 0x224);
static_assert(offsetof(SessionCallbacks, callback_254) == 0x254);
static_assert(offsetof(SessionCallbacks, callback_258) == 0x258);
static_assert(offsetof(SessionCallbacks, world_address) == 0x248);
static_assert(offsetof(SessionCallbacks, seed_result) == 0x24c);
static_assert(offsetof(SessionCallbacks, read_diagnostic) == 0x62c);
static_assert(offsetof(SessionCallbacks, unknown_packet) == 0x630);
static_assert(offsetof(SessionPrefix, state) == 0x1ec);
static_assert(offsetof(SessionPrefix, world_ipv4) == 0x1f0);
static_assert(offsetof(SessionPrefix, user_id_1f4) == 0x1f4);
static_assert(offsetof(SessionPrefix, user_id_1f8) == 0x1f8);
static_assert(offsetof(SessionPrefix, field_204) == 0x204);
static_assert(offsetof(SessionPrefix, login_token) == 0x46f);
static_assert(sizeof(SessionStorage) == 0x4a0);

extern "C" {
// Symbolic relocations of original storage. A real session constructor and its
// remaining callbacks are still required before these packet consumers run.
extern PACKET_EXPORT SessionPrefix* dat_0224a328;
extern PACKET_EXPORT SessionPrefix* dat_0223f100;
// The original vtable's remaining methods are not recovered. Its definition is
// intentionally unresolved in the production archive.
#if defined(SHAIYA_PACKET_VTABLE_TEST_FIXTURE)
extern PACKET_EXPORT SessionCallbacks dat_006bbd68;
#else
extern SessionCallbacks dat_006bbd68;
#endif
extern PACKET_EXPORT uint8_t dat_008655e8;
extern PACKET_EXPORT uint32_t dat_008655ec;
extern PACKET_EXPORT int32_t dat_00708598;
extern PACKET_EXPORT uint8_t dat_02251fe0[4096];
extern PACKET_EXPORT uint32_t dat_02252fe4;
extern PACKET_EXPORT uint8_t dat_02252fea;

/**
 * @brief Read packet bytes, reporting requests beyond the current available data.
 * @param reader Reader with the original cursor and length fields.
 * @param output Destination for the requested bytes and any diagnostic-path copy.
 * @param length Requested byte count.
 * @return The number of bytes copied, advancing the reader's current cursor.
 * @note On shortage, the requested output range is cleared before the session
 *       diagnostic callback. Cursor and length are then reloaded, and the full
 *       remaining length is copied without capping it to the original request.
 *       Aliasing and forward DWORD-then-byte copy order are retained.
 */
PACKET_EXPORT uint32_t PACKET_THISCALL read_packet_bytes_with_diagnostic(PacketReader* reader,
                                                                         void* output,
                                                                         uint32_t length);
/**
 * @brief Clear a reader's storage and initialize it from at most 8192 input bytes.
 * @param reader Reader whose byte storage, cursor, end, and length are initialized.
 * @param input Source bytes, copied after clearing the reader's byte array.
 * @param length Requested input length, clamped to the byte array capacity.
 * @return The original reader pointer.
 * @note Forward DWORD-then-byte copy order and input/output alias effects are retained.
 */
PACKET_EXPORT PacketReader* PACKET_THISCALL initialize_packet_reader(PacketReader* reader,
                                                                     const void* input,
                                                                     uint32_t length);
/**
 * @brief Read up to the remaining packet bytes, diagnosing an exhausted reader.
 * @param reader Reader with the original cursor and length fields.
 * @param output Destination for copied bytes, cleared only on the empty shortage path.
 * @param length Requested byte count, shortened to the remaining length on shortage.
 * @return Bytes copied and consumed, or zero after the empty-reader diagnostic.
 * @note Partial reads leave the rest of output untouched. The diagnostic path
 *       clears the requested range and returns without retrying the read.
 */
PACKET_EXPORT uint32_t PACKET_THISCALL read_available_packet_bytes(PacketReader* reader,
                                                                   void* output, uint32_t length);
/** @brief Invoke the current session's packet-read diagnostic with a null reader. */
PACKET_EXPORT void PACKET_CDECL report_packet_read_diagnostic();
PACKET_EXPORT void PACKET_CDECL fun_005921b0(PacketReader*);
PACKET_EXPORT void PACKET_CDECL fun_005923d0(PacketReader*);
PACKET_EXPORT void PACKET_CDECL fun_00592420(PacketReader*);
PACKET_EXPORT void PACKET_CDECL fun_005922a0(PacketReader*);
PACKET_EXPORT void PACKET_CDECL fun_00592380(PacketReader*);
// Consumer-only recovery: the typed virtual targets below remain external
// dependencies of the supplied session. No target callback bodies are supplied.
PACKET_EXPORT void PACKET_CDECL fun_00592120(PacketReader*);
PACKET_EXPORT void PACKET_CDECL fun_00592220(PacketReader*);
PACKET_EXPORT void PACKET_CDECL fun_00592030(PacketReader*);
PACKET_EXPORT void PACKET_CDECL fun_00592090(PacketReader*);
PACKET_EXPORT void PACKET_CDECL fun_00592620(PacketReader*);
PACKET_EXPORT void PACKET_CDECL fun_00592650(PacketReader*);
PACKET_EXPORT void PACKET_THISCALL fun_00570ad0(SessionPrefix*, uint8_t, uint32_t, uint8_t,
                                                const uint8_t*);
PACKET_EXPORT void PACKET_THISCALL fun_005712d0(SessionPrefix*, uint8_t, uint32_t);
PACKET_EXPORT void PACKET_THISCALL fun_005712f0(SessionPrefix*, uint8_t, uint8_t, const uint8_t*);
PACKET_EXPORT void PACKET_THISCALL fun_00570b30(SessionPrefix*, uint8_t);
PACKET_EXPORT void PACKET_THISCALL fun_00570c90(SessionPrefix*, uint8_t, uint8_t);
PACKET_EXPORT SessionStorage* PACKET_THISCALL fun_0040b0d0(SessionStorage*);
PACKET_EXPORT void PACKET_CDECL fun_00401520(uint32_t, const void*);
PACKET_EXPORT uint32_t PACKET_CDECL fun_00443cd0();
}
