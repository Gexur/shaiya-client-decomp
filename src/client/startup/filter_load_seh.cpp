#include "filter_load.h"
#include "archive/sah_loader.h"
#include "archive/saf_open.h"
#include "runtime/allocations.h"
#include "runtime/file_ops.h"
#include "runtime/stdio_scan.h"
#include "runtime/string_case_compare.h"
#include "runtime/string_errors.h"
#include "core/byte_utilities.h"
namespace {
using String = shaiya::startup::String_00405710;
void init_string(String* s) {
    s->capacity_018 = 15;
    s->size_014 = 0;
    s->storage_004[0] = 0;
}
struct TextUnwind {
    String* p;
    bool active = true;
    ~TextUnwind() noexcept(false) {
        if (active)
            FUN_00529db0(p);
    }
};
struct AllocationUnwind {
    void* p;
    bool active = true;
    ~AllocationUnwind() noexcept(false) {
        if (active)
            fun_005cc620(p);
    }
};
bool contains(const char* text, const char* part) {
    for (;; ++text) {
        const char *a = text, *b = part;
        while (*b && *a == *b) {
            ++a;
            ++b;
        }
        if (!*b)
            return true;
        if (!*text)
            return false;
    }
}
uint32_t length(const char* p) {
    uint32_t n = 0;
    while (p[n])
        ++n;
    return n;
}
const char* string_data(const String* s) {
    return s->capacity_018 < 16 ? reinterpret_cast<const char*>(s->storage_004)
                                : *reinterpret_cast<const char* const*>(s->storage_004);
}
struct LongListMessage {
    String s;
    LongListMessage() {
        init_string(&s);
        FUN_00405710(&s, "list<T> too long", 16);
    }
    ~LongListMessage() {
        FUN_00529db0(&s);
    }
};
void increment_list(OriginalFilterList* list) {
    if (0x3fffffffu - list->count < 1) {
        LongListMessage message;
        OriginalLogicError error;
        FUN_0040ad80(&error, &message.s);
        error.base.vtable = &dat_006dbc80;
        fun_005cce46(&error, const_cast<CxxThrowInfo*>(&dat_006fa52c));
        __builtin_unreachable();
    }
    ++list->count;
}
OriginalFilterNode* list_header() {
    auto* p = static_cast<OriginalFilterNode*>(fun_005cc96d(12));
    const uint32_t a = reinterpret_cast<uint32_t>(p);
    if (a)
        *reinterpret_cast<volatile uint32_t*>(a) = a;
    if (a + 4)
        *reinterpret_cast<volatile uint32_t*>(a + 4) = a;
    return p;
}
} // namespace
extern "C" OriginalFilterText* __attribute__((thiscall))
FUN_0040b250(OriginalFilterText* self, const char* text, uint32_t flags) {
    init_string(&self->string);
    TextUnwind unwind{&self->string};
    if (text)
        assign_archive_entry_name(reinterpret_cast<OriginalSafFile*>(self), text);
    self->flags = flags;
    unwind.active = false;
    return self;
}
extern "C" uint8_t __attribute__((thiscall)) FUN_0040ac50(OriginalFilterRecord* r, const char* text,
                                                          OriginalFilterText** output) {
    uint32_t hash = 0x1505;
    for (const char* p = text; *p; ++p) {
        int32_t c = int8_t(*p);
        if (c > 0x40 && c < 0x5b)
            c += 0x20;
        hash = hash * 33u + uint32_t(c);
    }
    r->current_list = r->buckets[hash % r->buckets_count];
    if (r->current_list) {
        r->current_node = r->current_list->header->next;
        if (r->current_node != r->current_list->header) {
            do {
                r->current_entry = r->current_node->value;
                if (fun_005e0428(text, string_data(&r->current_entry->string)) == 0) {
                    if (output)
                        *output = reinterpret_cast<OriginalFilterText*>(r->current_entry->flags);
                    return 1;
                }
                r->current_node = r->current_node->next;
            } while (r->current_node != r->current_list->header);
        }
    }
    if (output)
        *output = nullptr;
    return 0;
}
extern "C" void __attribute__((thiscall)) FUN_0040b8e0(OriginalFilterRecord* r, const char* text,
                                                       OriginalFilterText* value) {
    auto* entry = static_cast<OriginalFilterText*>(fun_005cc96d(36));
    if (entry)
        init_string(&entry->string);
    r->current_entry = entry;
    OriginalFilterText key;
    init_string(&key.string);
    TextUnwind unwind{&key.string};
    assign_archive_entry_name(reinterpret_cast<OriginalSafFile*>(&key), text);
    r->current_entry->hash = key.hash;
    FUN_00405620(&r->current_entry->string, &key.string, 0, 0xffffffffu);
    FUN_00529db0(&key.string);
    unwind.active = false;
    r->current_entry->flags = reinterpret_cast<uint32_t>(value);
    r->current_list = r->buckets[r->current_entry->hash % r->buckets_count];
    if (!r->current_list) {
        void* allocation = fun_005cc96d(12);
        AllocationUnwind cleanup{allocation};
        auto* list = static_cast<OriginalFilterList*>(allocation);
        if (list) {
            list->header = list_header();
            list->count = 0;
        }
        r->current_list = list;
        r->buckets[r->current_entry->hash % r->buckets_count] = list;
        cleanup.active = false;
    }
    auto* head = r->current_list->header;
    auto* node = static_cast<OriginalFilterNode*>(fun_005cc96d(12));
    if (node) {
        node->next = head;
        node->previous = head->previous;
        node->value = r->current_entry;
    }
    increment_list(r->current_list);
    head->previous = node;
    node->previous->next = node;
}
extern "C" uint8_t __attribute__((thiscall))
FUN_0040ba20(OriginalFilterOwner12* owner, const char* input, OriginalFilterText* value) {
    uint32_t n = length(input);
    char text[256]{};
    if (int32_t(n) < 256) {
        uint32_t written = 0;
        for (uint32_t i = 0; i < n; ++i)
            if (input[i] != ' ')
                text[written++] = input[i];
        n = length(text);
        if (int32_t(n) <= int32_t(owner->count) && int32_t(n) > 0) {
            auto* record = static_cast<OriginalFilterRecord*>(owner->records) + (n - 1);
            OriginalFilterText* old;
            if (!FUN_0040ac50(record, text, &old)) {
                FUN_0040b8e0(record, text, value);
                if (int32_t(owner->state) < int32_t(n))
                    owner->state = n;
                return 1;
            }
            old->hash = value->hash;
            FUN_00405620(&old->string, &value->string, 0, 0xffffffffu);
            old->flags |= value->flags;
        }
    }
    return 0;
}
extern "C" uint8_t __attribute__((thiscall)) FUN_0040bb10(OriginalFilterOwner12* owner,
                                                          const char* path) {
    const int32_t fd = open_archive_or_loose_file(path, "rt");
    if (fd == 0)
        return 0;
    char line[1024]{};
    int32_t mode = 0;
    while (read_archive_line(line, 1024, fd)) {
        if (contains(line, "<\xb1\xdd\xc1\xf6\xbe\xee") || contains(line, "<ban"))
            mode = 1;
        else if (contains(line, "<\xc7\xca\xc5\xcd\xb8\xb5") || contains(line, "<filter"))
            mode = 2;
        if (contains(line, "<\xc4\xb3\xb8\xaf\xc5\xcd") || contains(line, "<char"))
            mode = 4;
        else if (mode == 1 || mode == 4) {
            fun_0040a6f0(line);
            if (length(line)) {
                auto* value = static_cast<OriginalFilterText*>(fun_005cc96d(36));
                if (value) {
                    init_string(&value->string);
                    value->flags = mode;
                }
                FUN_0040ba20(owner, line, value);
            }
        } else if (mode == 2) {
            char first[1024]{}, second[1024]{};
            fun_005cd26b(line, "%s%s", first, second);
            fun_0040a6f0(first);
            fun_0040a6f0(second);
            if (length(first)) {
                void* allocation = fun_005cc96d(36);
                AllocationUnwind unwind{allocation};
                auto* value =
                    allocation
                        ? FUN_0040b250(static_cast<OriginalFilterText*>(allocation), second, 2)
                        : nullptr;
                unwind.active = false;
                FUN_0040ba20(owner, first, value);
            }
        }
        for (char& c : line)
            c = 0;
    }
    _close(fd);
    return 1;
}
