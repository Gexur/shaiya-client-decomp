#include "triple_list32.h"
#include "../startup/game_init.h"
#include "../runtime/allocations.h"

extern "C" const OriginalVirtualDelete dat_006cc9fc[1] = {FUN_00553670};

extern "C" OriginalTripleList32* __attribute__((thiscall))
FUN_00553640(OriginalTripleList32* self) {
    self->vtable = dat_006cc9fc;
    self->first = nullptr;
    self->second = nullptr;
    self->third = nullptr;
    self->first_count = 0;
    self->second_count = 0;
    self->third_count = 0;
    self->unknown10 = 0;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_005536a0(OriginalTripleList32* self) {
    int32_t index = 0;
    while (index < self->first_count) {
        if (dat_007191d4 != nullptr &&
            uint8_t(dat_007191d4->callbacks->callback_004(dat_007191d4, 0x15)) != 0) {
            void* current = self->first[index];
            if (current != nullptr)
                FUN_005507c0(current);
        }
        void* current = self->first[index];
        if (current != nullptr) {
            FUN_00550710(current);
            fun_005cc620(current);
            self->first[index] = nullptr;
        }
        index = static_cast<int32_t>(static_cast<uint32_t>(index) + 1u);
    }
    if (self->first != nullptr) {
        fun_005cdc59(self->first);
        self->first = nullptr;
    }
    index = 0;
    while (index < self->second_count) {
        if (dat_007191d4 != nullptr &&
            uint8_t(dat_007191d4->callbacks->callback_004(dat_007191d4, 0x15)) != 0) {
            void* current = self->second[index];
            if (current != nullptr)
                FUN_0053dd40(current);
        }
        void* current = self->second[index];
        if (current != nullptr) {
            (*static_cast<const OriginalVirtualDelete**>(current))[0](current, 1);
            self->second[index] = nullptr;
        }
        index = static_cast<int32_t>(static_cast<uint32_t>(index) + 1u);
    }
    if (self->second != nullptr) {
        fun_005cdc59(self->second);
        self->second = nullptr;
    }
    index = 0;
    while (index < self->third_count) {
        void* current = self->third[index];
        if (current != nullptr) {
            fun_005cc620(current);
            self->third[index] = nullptr;
        }
        index = static_cast<int32_t>(static_cast<uint32_t>(index) + 1u);
    }
    if (self->third != nullptr) {
        fun_005cdc59(self->third);
        self->third = nullptr;
    }
    self->first_count = 0;
    self->second_count = 0;
    self->third_count = 0;
    self->unknown10 = 0;
}
extern "C" void __attribute__((thiscall)) FUN_00553660(OriginalTripleList32* self) {
    self->vtable = dat_006cc9fc;
    FUN_005536a0(self);
}
extern "C" void* __attribute__((thiscall)) FUN_00553670(void* object, uint32_t flags) {
    auto* self = static_cast<OriginalTripleList32*>(object);
    self->vtable = dat_006cc9fc;
    FUN_005536a0(self);
    if ((flags & 1) != 0)
        fun_005cc620(self);
    return self;
}
