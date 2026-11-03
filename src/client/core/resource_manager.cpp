#include "resource_manager.h"
#include "../runtime/allocations.h"

extern "C" {
OriginalResourceManager24 dat_02221c00 = {}, dat_02221c18 = {};
}
namespace {
using Word = uint16_t __attribute__((may_alias));
}
extern "C" int32_t __attribute__((thiscall)) FUN_00557b10(void* value) {
    auto* field = reinterpret_cast<Word*>(static_cast<uint8_t*>(value) + 0x30);
    const uint16_t count = *field;
    if (count != 0) {
        if (count != 1) {
            *field = static_cast<uint16_t>(count - 1u);
            return 0;
        }
        *field = 0;
    }
    return 1;
}
extern "C" int32_t __attribute__((thiscall)) FUN_0053dd10(void* value) {
    auto* field = reinterpret_cast<Word*>(static_cast<uint8_t*>(value) + 0x10c);
    const uint16_t count = *field;
    if (count != 0) {
        if (count != 1) {
            *field = static_cast<uint16_t>(count - 1u);
            return 0;
        }
        *field = 0;
    }
    return 1;
}
extern "C" void __attribute__((thiscall)) FUN_0054b6d0(OriginalResourceManager24* self,
                                                       void* value) {
    if (value != nullptr && FUN_00557b10(value) != 0) {
        self->cursor = self->tree.header->left;
        if (self->cursor != self->tree.header) {
            while (self->cursor->value != value) {
                FUN_005b8a60(&self->cursor);
                if (self->cursor == self->tree.header)
                    return;
            }
            void* current = self->cursor->value;
            if (current != nullptr) {
                FUN_00434e20(current);
                fun_005cc620(current);
                self->cursor->value = nullptr;
            }
            OriginalTreeNode48* next;
            FUN_0054b270(&self->tree, &next, self->cursor);
            self->cursor = next;
        }
    }
}
extern "C" void __attribute__((thiscall)) FUN_0054b650(OriginalResourceManager24* self,
                                                       void* value) {
    if (value != nullptr && FUN_0053dd10(value) != 0) {
        self->cursor = self->tree.header->left;
        if (self->cursor != self->tree.header) {
            while (self->cursor->value != value) {
                FUN_005b8a60(&self->cursor);
                if (self->cursor == self->tree.header)
                    return;
            }
            void* current = self->cursor->value;
            if (current != nullptr) {
                (*static_cast<const OriginalVirtualDelete**>(current))[0](current, 1);
                self->cursor->value = nullptr;
            }
            OriginalTreeNode48* next;
            FUN_0054b270(&self->tree, &next, self->cursor);
            self->cursor = next;
        }
    }
}
