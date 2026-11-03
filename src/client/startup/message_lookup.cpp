#include "message_lookup.h"
#include "runtime/stdio_format.h"
#include "runtime/string_case_compare.h"
#include "core/korean_particles.h"
extern "C" {
int32_t dat_00719fb8 = 0, dat_0071add0 = 0, dat_0071c1d8 = 0, dat_0071c1dc = 0;
char dat_00719fc0[512]{}, dat_0071a1c0[512]{}, dat_0071a3c0[1024]{}, dat_0071a7c8[512]{},
    dat_0071a9c8[512]{}, dat_0071abd0[512]{}, dat_0071add8[5120]{};
uint8_t dat_0071a7c0 = 0, dat_0071a7c1 = 0, dat_0071abc8 = 0;
}
namespace {
uint32_t length(const char* p) {
    uint32_t n = 0;
    while (p[n])
        ++n;
    return n;
}
void copy(char* d, const char* s) {
    char c;
    do {
        c = *s++;
        *d++ = c;
    } while (c);
}
void copy_count(char* d, const char* s, uint32_t n) {
    // The original REP MOVSD followed by REP MOVSB is forward, including
    // any caller-supplied overlap between a message and shared output state.
    while (n >= 4) {
        uint32_t word;
        __asm__ volatile("movl (%1),%0" : "=r"(word) : "r"(s) : "memory");
        __asm__ volatile("movl %1,(%0)" ::"r"(d), "r"(word) : "memory");
        d += 4;
        s += 4;
        n -= 4;
    }
    while (n--)
        *d++ = *s++;
}
char* slot(int32_t index) {
    return dat_0071add8 + uint32_t(index) * 1024u;
}
const char* error(uint32_t id, int32_t index, const char* format, uint32_t n) {
    fun_005cd489(slot(index), format, id, n);
    return slot(dat_0071c1dc);
}
} // namespace
extern "C" const char* FUN_00578230(uint32_t) {
    if (dat_0071abc8 > 2)
        return nullptr;
    return FUN_0041d4a0(0x1a0 + dat_0071abc8);
}
extern "C" const char* FUN_00578270(uint32_t value) {
    value = uint8_t(value);
    if (value < 1 || value > 15)
        return nullptr;
    return FUN_0041d4a0(0x1a2 + value);
}
extern "C" const char* FUN_0041d4a0(uint32_t id) {
    dat_0071c1dc = int32_t(uint32_t(dat_0071c1dc) + 1u);
    if (dat_0071c1dc >= 5)
        dat_0071c1dc = 0;
    int32_t index = dat_0071c1dc;
    for (uint32_t i = 0; i < 1024; ++i)
        slot(index)[i] = 0;
    OriginalTreeNode24* found;
    const int32_t key = int32_t(id);
    find_signed_tree_node(&dat_0071c1e0, &found, &key);
    dat_0071c1ec = found;
    if (found == dat_0071c1e0.header) {
        fun_005cd489(slot(index), "GetMsg Error %d", id);
        return slot(dat_0071c1dc);
    }
    const char* cursor = reinterpret_cast<const char*>(found->payload10);
    const char* start = cursor;
    uint32_t pending = 0;
    char result[2016]{};
    char fragment[2048];
    while (*cursor) {
        if (*cursor != '<') {
            ++cursor;
            ++pending;
            continue;
        }
        if (pending) {
            uint32_t old = length(result);
            copy_count(result + old, start, pending);
            uint32_t total = old + pending;
            if (int32_t(total) >= 1024)
                return error(id, index, "GetMsg Error %d buf2:%d", total);
            result[total] = 0;
        }
        start = ++cursor;
        pending = 0;
        while (*cursor && *cursor != '>') {
            ++cursor;
            ++pending;
        }
        char tag[256]{};
        if (int32_t(pending) >= 20)
            return error(id, index, "GetMsg Error %d s:%d", pending);
        copy_count(tag, start, pending);
        const char* addition = nullptr;
        if (fun_005e0428(tag, "p") == 0) {
            if (length(dat_0071a9c8) < 256 && length(dat_0071a9c8) > 0) {
                copy(fragment, dat_0071a9c8);
                addition = fragment;
            }
        } else if (fun_005e0428(tag, "t") == 0) {
            if (length(dat_0071a1c0) < 256 && length(dat_0071a1c0) > 0) {
                copy(fragment, dat_0071a1c0);
                addition = fragment;
            }
        } else if (fun_005e0428(tag, "s") == 0) {
            if (length(dat_0071a7c8) < 256 && length(dat_0071a7c8) > 0) {
                copy(fragment, dat_0071a7c8);
                addition = fragment;
            }
        } else if (fun_005e0428(tag, "i") == 0) {
            if (length(dat_0071abd0) < 256 && length(dat_0071abd0) > 0) {
                copy(fragment, dat_0071abd0);
                addition = fragment;
            }
        } else if (fun_005e0428(tag, "r") == 0) {
            if (length(dat_00719fc0) < 256 && length(dat_00719fc0) > 0) {
                copy(fragment, dat_00719fc0);
                addition = fragment;
            }
        } else if (fun_005e0428(tag, "b") == 0) {
            if (length(dat_0071a3c0) < 512 && length(dat_0071a3c0) > 0) {
                copy(fragment, dat_0071a3c0);
                addition = fragment;
            }
        } else if (fun_005e0428(tag, "v3") == 0) {
            fun_005cd489(fragment, "%d", dat_0071add0);
            addition = fragment;
        } else if (fun_005e0428(tag, "v2") == 0) {
            fun_005cd489(fragment, "%d", dat_00719fb8);
            addition = fragment;
        } else if (fun_005e0428(tag, "v") == 0) {
            fun_005cd489(fragment, "%d", dat_0071c1d8);
            addition = fragment;
        } else if (fun_005e0428(tag, "hp") == 0) {
            copy(fragment, FUN_00578230(dat_0071abc8));
            addition = fragment;
        } else if (fun_005e0428(tag, "zz") == 0) {
            copy(fragment, FUN_00578270(dat_0071a7c1));
            addition = fragment;
        } else if (fun_005e0428(tag, "up") == 0) {
            copy(fragment, FUN_00578230(dat_0071a7c0));
            addition = fragment;
        } else if (fun_005e0428(tag, "\xc0\xba\xb4\xc2") == 0)
            addition =
                reinterpret_cast<const char*>(select_korean_topic_particle(nullptr, fragment));
        else if (fun_005e0428(tag, "\xc0\xcc\xb0\xa1") == 0)
            addition =
                reinterpret_cast<const char*>(select_korean_subject_particle(nullptr, fragment));
        else if (fun_005e0428(tag, "\xc0\xbb\xb8\xa6") == 0)
            addition =
                reinterpret_cast<const char*>(select_korean_object_particle(nullptr, fragment));
        else if (fun_005e0428(tag, reinterpret_cast<const char*>(dat_006bca7c)) == 0)
            addition = reinterpret_cast<const char*>(
                select_korean_instrumental_particle(nullptr, fragment));
        if (addition) {
            uint32_t n = length(addition) + 1;
            copy_count(result + length(result), addition, n);
        }
        index = dat_0071c1dc;
        if (!*cursor)
            break;
        start = ++cursor;
        pending = 0;
    }
    if (pending) {
        uint32_t old = length(result), total = old + pending;
        if (int32_t(total) >= 1024)
            return error(id, index, "GetMsg Error %d buf1:%d", total);
        copy_count(result + old, start, pending);
        result[total] = 0;
    }
    copy(slot(index), result);
    if (length(slot(index)) == 0) {
        fun_005cd489(slot(index), "GetMsg Error %d", id);
        index = dat_0071c1dc;
    }
    return slot(index);
}
