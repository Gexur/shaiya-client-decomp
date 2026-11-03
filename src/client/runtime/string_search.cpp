#include "environment_access.h"
extern "C" char* fun_005d6670(const char* source, uint32_t character) {
    auto* cursor = reinterpret_cast<const uint8_t*>(source);
    uint8_t wanted = static_cast<uint8_t>(character);
    while (reinterpret_cast<uint32_t>(cursor) & 3u) {
        uint8_t byte = *reinterpret_cast<const volatile uint8_t*>(cursor);
        ++cursor;
        if (byte == wanted)
            return const_cast<char*>(reinterpret_cast<const char*>(cursor - 1));
        if (!byte)
            return nullptr;
    }
    uint32_t repeated = wanted;
    repeated |= repeated << 8;
    repeated |= repeated << 16;
    for (;;) {
        uint32_t word = *reinterpret_cast<const volatile uint32_t*>(cursor);
        uint32_t matched = word ^ repeated;
        uint32_t sum = word + 0x7efefeffu;
        uint32_t zeros = (~word ^ sum) & 0x81010100u;
        cursor += 4;
        if (((~matched ^ (matched + 0x7efefeffu)) & 0x81010100u) == 0) {
            if (!zeros)
                continue;
            if ((zeros & 0x01010100u) || !(sum & 0x80000000u))
                return nullptr;
            continue;
        }
        word = *reinterpret_cast<const volatile uint32_t*>(cursor - 4);
        for (uint32_t i = 0; i < 4; ++i) {
            uint8_t byte = static_cast<uint8_t>(word >> (i * 8));
            if (byte == wanted)
                return const_cast<char*>(reinterpret_cast<const char*>(cursor - 4 + i));
            if (!byte)
                return nullptr;
        }
    }
}
