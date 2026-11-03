#include "string_token.h"
#include "thread_data.h"
#include "security.h"
namespace {
struct TokenStorage {
    uint8_t map[32];
    volatile uint32_t guard;
};
static_assert(offsetof(TokenStorage, guard) == 32);
uint8_t read_byte(const char* pointer) {
    uint32_t value;
    // Retain the original byte accesses, including the repeated token reads,
    // and their fault-visible order relative to the final PTD token store.
    __asm__ __volatile__("movzbl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return uint8_t(value);
}
char* previous_token(const OriginalPerThreadData* data) {
    char* pointer;
    static_assert(offsetof(OriginalPerThreadData, undecoded_18) == 0x18);
    static_assert(sizeof(pointer) == 4);
    __builtin_memcpy(&pointer, data->undecoded_18, sizeof(pointer));
    return pointer;
}
void save_token(OriginalPerThreadData* data, char* pointer) {
    __builtin_memcpy(data->undecoded_18, &pointer, sizeof(pointer));
}
} // namespace
extern "C" char* fun_005ce160(char* input, const char* delimiters) {
    TokenStorage storage;
    storage.guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&storage.guard);
    auto* const data = static_cast<OriginalPerThreadData*>(fun_005d2659());
    auto& map = storage.map;
    __builtin_memset(map, 0, sizeof(map));
    uint8_t character;
    do {
        character = read_byte(delimiters);
        map[character >> 3] |= uint8_t(1u << (character & 7));
        ++delimiters;
    } while (character != 0);
    if (input == nullptr)
        input = previous_token(data);
    for (;;) {
        character = read_byte(input);
        if ((map[character >> 3] & uint8_t(1u << (character & 7))) == 0 || character == 0)
            break;
        ++input;
    }
    char* cursor = input;
    while (read_byte(cursor) != 0) {
        character = read_byte(cursor);
        if (map[character >> 3] & uint8_t(1u << (character & 7))) {
            *cursor = 0;
            ++cursor;
            break;
        }
        ++cursor;
    }
    save_token(data, cursor);
    char* const result = input == cursor ? nullptr : input;
    fun_005d0efa(storage.guard ^ reinterpret_cast<uint32_t>(&storage.guard));
    return result;
}
// Original WinMain's declaration has this identical cdecl pointer interface.
extern "C" char* FUN_005ce160(char*, const char*) __attribute__((alias("fun_005ce160")));
