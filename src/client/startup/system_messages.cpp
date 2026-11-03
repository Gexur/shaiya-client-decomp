#include "system_messages.h"
#include "archive/saf.h"
#include "archive/saf_open.h"
#include "startup/client_locale.h"
#include "startup/application.h"
#include "platform/support.hpp"
#include "runtime/file_seek64.h"
#include "runtime/file_ops.h"
#include "runtime/allocations.h"
#include "runtime/stdio_scan.h"
extern "C" OriginalTreeNode24* dat_0071c1ec = nullptr;
namespace {
uint32_t length(const char* p) {
    uint32_t n = 0;
    while (p[n])
        ++n;
    return n;
}
bool before_end(int32_t fd) {
    const int64_t position = fun_005ce731(fd);
    const OriginalSafFile* f = dat_00719e80;
    const uint64_t offset = (uint64_t(f->data_offset_high) << 32) | f->data_offset_low;
    return position < int64_t(offset + f->byte_length);
}
void clear_tree() {
    FUN_0041d3f0(&dat_0071c1e0, dat_0071c1e0.header->parent);
    dat_0071c1e0.header->parent = dat_0071c1e0.header;
    dat_0071c1e0.count = 0;
    dat_0071c1e0.header->left = dat_0071c1e0.header;
    dat_0071c1e0.header->right = dat_0071c1e0.header;
}
} // namespace
extern "C" uint8_t FUN_004373e0(wchar_t* out, uint32_t, int32_t fd) {
    uint32_t count = 0;
    unsigned char bytes[2];
    while (before_end(fd)) {
        FUN_0040d020(bytes, 1, 2, fd);
        uint32_t value;
        __asm__ volatile("movzwl (%1),%0" : "=r"(value) : "r"(bytes) : "memory");
        out[count] = wchar_t(value);
        if (value == 10) {
            out[count] = 0;
            return 1;
        }
        ++count;
    }
    if (count) {
        out[count] = 0;
        return 1;
    }
    return 0;
}
extern "C" char* FUN_0046e820(char* out, const char* input) {
    char copy[2048];
    uint32_t size = 0;
    do {
        copy[size] = input[size];
    } while (input[size++] != 0);
    uint32_t opening = 0;
    while (copy[0] != '"') {
        copy[0] = copy[opening + 1];
        ++opening;
        if (!copy[0])
            return const_cast<char*>(input);
    }
    uint32_t pos = opening + 1, written = 0;
    *reinterpret_cast<uint32_t*>(out) = 0;
    for (;;) {
        const char c = copy[pos];
        if (c == '"' && copy[pos + 1] != '"' &&
            ((pos > 0 && copy[pos - 1] != '"') ||
             (pos > 1 && copy[pos - 1] == '"' && copy[pos - 2] == '"'))) {
            if (opening + 1 != pos - 1) {
                out[written] = 0;
                return const_cast<char*>(input) + pos + 1;
            }
            return const_cast<char*>(input) + pos;
        }
        if (!c) {
            out[written] = 0;
            return const_cast<char*>(input) + pos;
        }
        if (c == '"' && length(copy) > pos + 1 && copy[pos + 1] == '"') {
            out[written++] = '"';
            pos += 2;
        } else {
            out[written++] = c;
            ++pos;
        }
    }
}
extern "C" void FUN_0041f2e0() {
    clear_tree();
    const int32_t fd = open_archive_or_loose_file("data/sysmsg-uni.txt", "rb");
    if (fd == 0) {
        MessageBoxA(nullptr, "sysmsg-uni.txt Not Found!!!", "ERROR", 0);
        PostMessageA(dat_00719a3c, 0x10, 0, 0);
    }
    wchar_t wide[2048];
    char line[2048], quoted[2048];
    FUN_0040d020(wide, 1, 2, fd);
    for (wchar_t& c : wide)
        c = 0;
    while (FUN_004373e0(wide, 0x800, fd)) {
        if (dat_00708598 == 3)
            WideCharToMultiByte(65001, 0, wide, -1, line, 2048, nullptr, nullptr);
        else {
            const uint32_t n =
                WideCharToMultiByte(fun_0040a550(), 0, wide, -1, line, 0, nullptr, nullptr);
            if (n > 0x7ff) {
                _close(fd);
                return;
            }
            WideCharToMultiByte(fun_0040a550(), 0, wide, -1, line, n, nullptr, nullptr);
            line[n] = 0;
        }
        if (line[0] != '/' || line[1] != '/') {
            int32_t key = -1;
            fun_005cd26b(line, "%d", &key);
            if (key != -1) {
                for (char& c : quoted)
                    c = 0;
                FUN_0046e820(quoted, line);
                if (length(quoted) == 0)
                    MessageBoxA(nullptr, "sysmsg-uni.txt Read Failed!!!", "ERROR", 0);
                const uint32_t n = length(quoted);
                auto* text = static_cast<char*>(fun_005cc96d(n + 1));
                uint32_t i = 0;
                do {
                    text[i] = quoted[i];
                } while (quoted[i++] != 0);
                *FUN_0041f230(&dat_0071c1e0, &key) = reinterpret_cast<uint32_t>(text);
            }
        }
        for (wchar_t& c : wide)
            c = 0;
    }
    _close(fd);
}
extern "C" void FUN_0041e1b0() {
    dat_0071c1ec = dat_0071c1e0.header->left;
    while (dat_0071c1ec != dat_0071c1e0.header) {
        fun_005cc620(reinterpret_cast<void*>(dat_0071c1ec->payload10));
        FUN_00421780(&dat_0071c1ec);
    }
    clear_tree();
}
