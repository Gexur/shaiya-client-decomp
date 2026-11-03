#include "stdio_format.h"
#include "wide_output.h"
#include "multibyte.h"
#include "fpmath.h"
#include "heap.h"
#include "strings.h"
#include "security.h"
#include "../core/uint64_divrem.h"
namespace {
uint32_t next_word(const uint8_t*& arguments) {
    const uint32_t word = *reinterpret_cast<const uint32_t*>(arguments);
    arguments += 4;
    return word;
}
const char* raw_pointer(const unsigned char* storage) {
    const char* pointer;
    __asm__ volatile("movl (%1),%0" : "=r"(pointer) : "r"(storage) : "memory");
    return pointer;
}
void set_pointer(unsigned char* storage, const char* pointer) {
    __asm__ volatile("movl %1,(%0)" ::"r"(storage), "r"(pointer) : "memory");
}
// These original slots initially name the no-argument fatal routine5dcf10,
// then the floating initializer rebinds them. The machine caller supplies
// five/one stack words and ignores EAX; it does not establish a C++ return
// type compatible with every stored target. Retain that exact call contract.
void floating_convert(FloatingRoutineAddress target, const uint32_t* value, char* output,
                      int32_t kind, int32_t precision, int32_t uppercase) {
    const uint32_t operands[] = {reinterpret_cast<uint32_t>(value),
                                 reinterpret_cast<uint32_t>(output), uint32_t(kind),
                                 uint32_t(precision), uint32_t(uppercase)};
    __asm__ volatile(
        "pushl 16(%1)\n\tpushl 12(%1)\n\tpushl 8(%1)\n\tpushl 4(%1)\n\tpushl (%1)\n\tcall *%0\n\taddl $20,%%esp" ::
            "r"(target),
        "r"(operands)
        : "eax", "ecx", "edx", "cc", "memory");
}
void floating_adjust(FloatingRoutineAddress target, char* output) {
    __asm__ volatile("pushl %1\n\tcall *%0\n\taddl $4,%%esp" ::"r"(target), "r"(output)
                     : "eax", "ecx", "edx", "cc", "memory");
}
} // namespace
extern "C" int32_t fun_005d36e4(OriginalFile* file, const char* format,
                                const void* argument_words) {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    const uint8_t* arguments = static_cast<const uint8_t*>(argument_words);
    int32_t state = 0, total = 0, length = 0;
    void* allocated = nullptr;
    char temporary[512], wide_bytes[8], prefix[2];
    unsigned char text_storage[4];
    int32_t precision, width, prefix_length, uppercase, skip, wide = 0, hexadecimal_offset;
    uint32_t flags;
    const uint8_t* position = reinterpret_cast<const uint8_t*>(format);
    while (*position) {
        uint8_t character = *position++;
        if (total < 0)
            break;
        const int32_t signed_character = static_cast<int8_t>(character);
        const uint32_t kind = signed_character >= 32 && signed_character <= 120
                                  ? dat_006d68b0[signed_character - 32] & 15u
                                  : 0;
        state = static_cast<int8_t>(dat_006d68b0[kind * 8u + uint32_t(state)]) >> 4;
        switch (state) {
        case 0:
        literal_character:
            wide = 0;
            if (dat_0070e4d8[character] & 0x8000) {
                fun_005d3656(character, file, &total);
                character = *position++;
            }
            fun_005d3656(character, file, &total);
            break;
        case 1:
            precision = -1;
            uppercase = 0;
            skip = 0;
            width = 0;
            prefix_length = 0;
            flags = 0;
            wide = 0;
            break;
        case 2:
            if (character == ' ')
                flags |= 2;
            else if (character == '#')
                flags |= 0x80;
            else if (character == '+')
                flags |= 1;
            else if (character == '-')
                flags |= 4;
            else if (character == '0')
                flags |= 8;
            break;
        case 3:
            if (character == '*') {
                width = int32_t(next_word(arguments));
                if (width < 0) {
                    flags |= 4;
                    width = int32_t(0u - uint32_t(width));
                }
            } else
                width = int32_t(uint32_t(width) * 10u + uint32_t(signed_character) - 48u);
            break;
        case 4:
            precision = 0;
            break;
        case 5:
            if (character == '*') {
                precision = int32_t(next_word(arguments));
                if (precision < 0)
                    precision = -1;
            } else
                precision = int32_t(uint32_t(precision) * 10u + uint32_t(signed_character) - 48u);
            break;
        case 6:
            if (character == 'I') {
                if (position[0] == '6' && position[1] == '4') {
                    position += 2;
                    flags |= 0x8000;
                } else if (position[0] == '3' && position[1] == '2') {
                    position += 2;
                    flags &= ~0x8000u;
                } else if (position[0] != 'd' && position[0] != 'i' && position[0] != 'o' &&
                           position[0] != 'u' && position[0] != 'x' && position[0] != 'X') {
                    state = 0;
                    goto literal_character;
                }
            } else if (character == 'h')
                flags |= 0x20;
            else if (character == 'l')
                flags |= 0x10;
            else if (character == 'w')
                flags |= 0x800;
            break;
        case 7: {
            uint32_t radix;
            switch (character) {
            case 'C':
                if (!(flags & 0x830))
                    flags |= 0x800;
                [[fallthrough]];
            case 'c': {
                const uint32_t value = next_word(arguments);
                if (flags & 0x810) {
                    length = fun_005dd14f(temporary, uint32_t(int32_t(int16_t(value))));
                    if (length < 0)
                        skip = 1;
                } else {
                    temporary[0] = static_cast<char>(value);
                    length = 1;
                }
                set_pointer(text_storage, temporary);
                break;
            }
            case 'S':
                if (!(flags & 0x830))
                    flags |= 0x800;
                [[fallthrough]];
            case 's': {
                int32_t limit = precision == -1 ? 0x7fffffff : precision;
                const char* text = reinterpret_cast<const char*>(next_word(arguments));
                if (flags & 0x810) {
                    if (!text)
                        text = reinterpret_cast<const char*>(dat_0070e614);
                    wide = 1;
                    const uint16_t* cursor = reinterpret_cast<const uint16_t*>(text);
                    while (limit) {
                        --limit;
                        if (!*cursor)
                            break;
                        ++cursor;
                    }
                    length = int32_t(reinterpret_cast<uint32_t>(cursor) -
                                     reinterpret_cast<uint32_t>(text)) >>
                             1;
                } else {
                    if (!text)
                        text = dat_0070e610;
                    const char* cursor = text;
                    while (limit) {
                        --limit;
                        if (!*cursor)
                            break;
                        ++cursor;
                    }
                    length = int32_t(reinterpret_cast<uint32_t>(cursor) -
                                     reinterpret_cast<uint32_t>(text));
                }
                set_pointer(text_storage, text);
                break;
            }
            case 'Z': {
                const auto* string = reinterpret_cast<const uint8_t*>(next_word(arguments));
                const char* text =
                    string ? *reinterpret_cast<const char* const*>(string + 4) : nullptr;
                if (!text) {
                    text = dat_0070e610;
                    length = int32_t(fun_005d4cf0(text));
                } else {
                    length = *reinterpret_cast<const int16_t*>(string);
                    if (flags & 0x800) {
                        length /= 2;
                        wide = 1;
                    } else
                        wide = 0;
                }
                set_pointer(text_storage, text);
                break;
            }
            case 'E':
            case 'G':
                uppercase = 1;
                character += 32;
                [[fallthrough]];
            case 'e':
            case 'f':
            case 'g': {
                flags |= 0x40;
                char* output = temporary;
                set_pointer(text_storage, output);
                if (precision < 0)
                    precision = 6;
                else if (!precision) {
                    if (character == 'g')
                        precision = 1;
                } else {
                    if (precision > 512)
                        precision = 512;
                    if (precision > 163) {
                        allocated = fun_005cfade(uint32_t(precision) + 0x15d);
                        if (allocated) {
                            output = static_cast<char*>(allocated);
                            set_pointer(text_storage, output);
                        } else
                            precision = 163;
                    }
                }
                uint32_t words[2];
                words[0] = next_word(arguments);
                words[1] = next_word(arguments);
                floating_convert(dat_0070e500, words, output, static_cast<int8_t>(character),
                                 precision, uppercase);
                if ((flags & 0x80) && precision == 0)
                    floating_adjust(dat_0070e50c, output);
                if (character == 'g' && !(flags & 0x80))
                    floating_adjust(dat_0070e504, output);
                if (*output == '-') {
                    flags |= 0x100;
                    ++output;
                    set_pointer(text_storage, output);
                }
                length = int32_t(fun_005d4cf0(output));
                break;
            }
            case 'n': {
                void* output = reinterpret_cast<void*>(next_word(arguments));
                if (flags & 0x20)
                    *static_cast<uint16_t*>(output) = uint16_t(total);
                else
                    *static_cast<int32_t*>(output) = total;
                skip = 1;
                goto conversion_complete;
            }
            case 'd':
            case 'i':
                flags |= 0x40;
                [[fallthrough]];
            case 'u':
                radix = 10;
                goto integer;
            case 'o':
                radix = 8;
                if (flags & 0x80)
                    flags |= 0x200;
                goto integer;
            case 'p':
                precision = 8;
                [[fallthrough]];
            case 'X':
                hexadecimal_offset = 7;
                goto hexadecimal;
            case 'x':
                hexadecimal_offset = 0x27;
            hexadecimal:
                radix = 16;
                if (flags & 0x80) {
                    prefix[0] = '0';
                    prefix[1] = static_cast<char>(hexadecimal_offset + 0x51);
                    prefix_length = 2;
                }
            integer: {
                uint32_t low = next_word(arguments), high;
                if (flags & 0x8000)
                    high = next_word(arguments);
                else {
                    if (flags & 0x20)
                        low = flags & 0x40 ? uint32_t(int32_t(int16_t(low))) : uint16_t(low);
                    high = flags & 0x40 ? uint32_t(int32_t(low) >> 31) : 0;
                }
                if ((flags & 0x40) && int32_t(high) < 0) {
                    const uint32_t old = low;
                    low = 0u - low;
                    high = 0u - high - uint32_t(old != 0);
                    flags |= 0x100;
                }
                if (!(flags & 0x8000))
                    high = 0;
                if (precision < 0)
                    precision = 1;
                else {
                    flags &= ~8u;
                    if (precision > 512)
                        precision = 512;
                }
                if (!(low | high))
                    prefix_length = 0;
                char* cursor = temporary + 511;
                for (;;) {
                    const int32_t old_precision = precision;
                    precision = int32_t(uint32_t(precision) - 1);
                    if (old_precision <= 0 && !(low | high))
                        break;
                    uint64_t remainder;
                    const uint64_t quotient = recovered_u64_divrem(
                        low, high, radix, uint32_t(int32_t(radix) >> 31), &remainder);
                    low = uint32_t(quotient);
                    high = uint32_t(quotient >> 32);
                    int32_t digit = int32_t(uint32_t(remainder) + 48u);
                    if (digit > 57)
                        digit = int32_t(uint32_t(digit) + uint32_t(hexadecimal_offset));
                    *cursor-- = static_cast<char>(digit);
                }
                length = int32_t((temporary + 511) - cursor);
                ++cursor;
                if ((flags & 0x200) && (*cursor != '0' || !length)) {
                    *--cursor = '0';
                    ++length;
                }
                set_pointer(text_storage, cursor);
                break;
            }
            default:
                break;
            }
            if (!skip) {
                if (flags & 0x40) {
                    if (flags & 0x100)
                        prefix[0] = '-';
                    else if (flags & 1)
                        prefix[0] = '+';
                    else if (flags & 2)
                        prefix[0] = ' ';
                    else
                        goto prefix_complete;
                    prefix_length = 1;
                }
            prefix_complete:
                const uint32_t preserved_flags = flags;
                const int32_t padding =
                    int32_t(uint32_t(width) - uint32_t(prefix_length) - uint32_t(length));
                if (!(flags & 0xc))
                    fun_005d3689(' ', padding, file, &total);
                fun_005d36ad(prefix, prefix_length, file, &total);
                if ((preserved_flags & 8) && !(preserved_flags & 4))
                    fun_005d3689('0', padding, file, &total);
                if (!wide || length < 1)
                    fun_005d36ad(raw_pointer(text_storage), length, file, &total);
                else {
                    auto* cursor = reinterpret_cast<const uint16_t*>(raw_pointer(text_storage));
                    uint32_t remaining = uint32_t(length);
                    do {
                        --remaining;
                        const int32_t bytes = fun_005dd14f(wide_bytes, *cursor++);
                        if (bytes < 1)
                            break;
                        fun_005d36ad(wide_bytes, bytes, file, &total);
                    } while (remaining);
                }
                if (preserved_flags & 4)
                    fun_005d3689(' ', padding, file, &total);
            }
        conversion_complete:
            // Original5d3e51 clears the slot after free. Ghidra omits this
            // continuation because its imported free prototype says noreturn.
            if (allocated) {
                fun_005cfaf0(allocated);
                allocated = nullptr;
            }
            break;
        }
        default:
            break;
        }
    }
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
    return total;
}
