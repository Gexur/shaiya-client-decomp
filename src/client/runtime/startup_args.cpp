#include "startup_args.h"
#include "heap.h"

extern "C" {
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetModuleFileNameA(void*, char*, uint32_t);
int32_t dat_0224edfc = 0;
char** dat_0224ee00 = nullptr;
char* dat_0224ee18 = nullptr;
char dat_0224f118[261] = {};
}

extern "C" void fun_005dbb2c(const uint8_t* input, char** argv, char* output,
                             uint32_t* argument_slots, uint32_t* text_bytes) {
    bool quoted = false;
    *text_bytes = 0;
    *argument_slots = 1;
    if (argv != nullptr)
        *argv++ = output;
    for (;;) {
        uint8_t value = *input;
        if (value == '"') {
            quoted = !quoted;
            ++input;
        } else {
            ++*text_bytes;
            if (output != nullptr)
                *output++ = static_cast<char>(value);
            ++input;
            if ((dat_02253400[value + 1] & 4) != 0) {
                ++*text_bytes;
                if (output != nullptr)
                    *output++ = static_cast<char>(*input);
                ++input;
            }
            if (value == 0) {
                --input;
                break;
            }
        }
        if (!quoted && (value == ' ' || value == '\t')) {
            if (output != nullptr)
                output[-1] = 0;
            break;
        }
    }
    quoted = false;
    while (*input != 0) {
        while (*input == ' ' || *input == '\t')
            ++input;
        if (*input == 0)
            break;
        if (argv != nullptr)
            *argv++ = output;
        ++*argument_slots;
        for (;;) {
            bool copy_character = true;
            uint32_t backslashes = 0;
            while (*input == '\\') {
                ++input;
                ++backslashes;
            }
            if (*input == '"') {
                if ((backslashes & 1) == 0) {
                    if (quoted && input[1] == '"')
                        ++input;
                    else
                        copy_character = false;
                    quoted = !quoted;
                }
                backslashes >>= 1;
            }
            while (backslashes != 0) {
                if (output != nullptr)
                    *output++ = '\\';
                ++*text_bytes;
                --backslashes;
            }
            uint8_t value = *input;
            if (value == 0 || (!quoted && (value == ' ' || value == '\t')))
                break;
            if (copy_character) {
                if ((dat_02253400[value + 1] & 4) != 0) {
                    if (output != nullptr)
                        *output++ = static_cast<char>(value);
                    ++input;
                    ++*text_bytes;
                }
                if (output != nullptr)
                    *output++ = static_cast<char>(*input);
                ++*text_bytes;
            }
            ++input;
        }
        if (output != nullptr)
            *output++ = 0;
        ++*text_bytes;
    }
    if (argv != nullptr)
        *argv = nullptr;
    ++*argument_slots;
}

extern "C" int32_t fun_005dbc98() {
    if (dat_02254650 == 0)
        fun_005d34ea();
    dat_0224f118[260] = 0;
    GetModuleFileNameA(nullptr, dat_0224f118, 260);
    dat_0224ee18 = dat_0224f118;
    const char* command = dat_02253620;
    if (command == nullptr || *command == 0)
        command = dat_0224f118;
    uint32_t argument_slots, text_bytes;
    fun_005dbb2c(reinterpret_cast<const uint8_t*>(command), nullptr, nullptr, &argument_slots,
                 &text_bytes);
    const uint32_t pointers_size = argument_slots * 4;
    auto* allocation = static_cast<char*>(fun_005cfade(pointers_size + text_bytes));
    if (allocation == nullptr)
        return -1;
    fun_005dbb2c(reinterpret_cast<const uint8_t*>(command), reinterpret_cast<char**>(allocation),
                 allocation + pointers_size, &argument_slots, &text_bytes);
    dat_0224edfc = static_cast<int32_t>(argument_slots - 1);
    dat_0224ee00 = reinterpret_cast<char**>(allocation);
    return 0;
}

extern "C" char* fun_005dba08() {
    if (dat_02254650 == 0)
        fun_005d34ea();
    const uint8_t* cursor = reinterpret_cast<const uint8_t*>(dat_02253620);
    static const uint8_t empty[] = {0}; // Original NUL at 0x006bb5d5.
    if (cursor == nullptr)
        cursor = empty;
    bool quoted = false;
    for (;;) {
        uint8_t value = *cursor;
        if (value <= 0x20) {
            if (value == 0)
                return reinterpret_cast<char*>(const_cast<uint8_t*>(cursor));
            if (!quoted) {
                while (*cursor != 0 && *cursor <= 0x20)
                    ++cursor;
                return reinterpret_cast<char*>(const_cast<uint8_t*>(cursor));
            }
        }
        if (value == '"')
            quoted = !quoted;
        if (fun_005e0417(value) != 0)
            ++cursor;
        ++cursor;
    }
}
