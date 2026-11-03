#include "packets.h"

namespace {
void clear_range(uint8_t* storage, uint32_t start, uint32_t end) {
    for (uint32_t offset = start; offset != end; ++offset)
        storage[offset] = 0;
}
} // namespace

// 0x40b0d0..0x40b1e5: preserve every original initialized range and every gap.
// In particular, a blanket zero-initialization would overwrite unknown bytes
// which the original constructor leaves untouched.
extern "C" SessionStorage* PACKET_THISCALL fun_0040b0d0(SessionStorage* session) {
    session->prefix.callbacks = &dat_006bbd68;
    uint8_t* storage = reinterpret_cast<uint8_t*>(session);
    clear_range(storage, 0x48c, 0x49c);
    clear_range(storage, 4, 8);
    clear_range(storage, 0xc, 0x1ec);
    clear_range(storage, 0x1ec, 0x200);
    clear_range(storage, 0x240, 0x26f);
    clear_range(storage, 0x26f, 0x292);
    clear_range(storage, 0x3bf, 0x47f);
    clear_range(storage, 0x480, 0x488);
    clear_range(storage, 0x49c, 0x4a0);
    clear_range(storage, 0x200, 0x230);
    clear_range(storage, 0x230, 0x23f);
    clear_range(storage, 8, 0xc);
    return session;
}
