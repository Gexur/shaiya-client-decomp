#include "ordered_stores.h"
namespace shaiya::ui {
extern "C" Object_00527000* __attribute__((thiscall)) FUN_00527000(Object_00527000* self) {
    using namespace ordered_detail;
    // Exact00527000 write widths and order, including its actual REP STOSD.
    store32(self, 0, reinterpret_cast<u32>(PTR_FUN_006c57cc));
    store8(self, 4, 1);
    store8(self, 6, 0);
    store8(self, 0xa3, 0);
    store32(self, 8, 0);
    store8(self, 0xd, 0);
    store8(self, 5, 0);
    store32(self, 0x5c8, 0);
    store32(self, 0x5cc, 0);
    store32(self, 0x5d4, 0);
    store32(self, 0x98, 0x3f800000);
    store8(self, 0xa0, 0xff);
    store8(self, 0xa1, 0xff);
    store8(self, 0xa2, 0xff);
    zero_words(self, 0xc4, 0x100);
    for (u32 i = 0; i != 5; ++i) {
        store32(self, 0x70 + i * 4, 0);
        store32(self, 0x48 + i * 4, 0);
        store32(self, 0x84 + i * 4, 0x3f800000);
        store32(self, 0x5c + i * 4, 0x3f800000);
    }
    store32(self, 0x9c, 0x3f800000);
    for (u32 offset = 0xb4; offset != 0xc4; offset += 4)
        store32(self, offset, 0);
    store8(self, 0xa4, 0);
    store8(self, 0x4c4, 0);
    store8(self, 0x5d0, 1);
    return self;
}
} // namespace shaiya::ui
