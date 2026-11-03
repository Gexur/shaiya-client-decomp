#include "resource_tree56.h"
#include "runtime/allocations.h"
namespace {
struct KeyUnwind {
    shaiya::startup::String_00405710* self;
    bool active = true;
    ~KeyUnwind() noexcept(false) {
        if (active)
            FUN_00529db0(self);
    }
};
struct TreeUnwind {
    OriginalNestedTree56* self;
    bool active = true;
    ~TreeUnwind() noexcept(false) {
        if (active)
            FUN_004c3880(self);
    }
};
} // namespace
extern "C" void __attribute__((thiscall)) FUN_004c3410(OriginalNestedPayload40* self) {
    KeyUnwind cleanup{&self->key};
    OriginalNestedNode72* ignored;
    FUN_004c3320(&self->values, &ignored, self->values.header->left, self->values.header);
    fun_005cc620(self->values.header);
    self->values.header = nullptr;
    self->values.count = 0;
    if (self->key.capacity_018 >= 16)
        fun_005cc620(*reinterpret_cast<void**>(self->key.storage_004));
    self->key.size_014 = 0;
    self->key.capacity_018 = 15;
    self->key.storage_004[0] = 0;
    cleanup.active = false;
}
extern "C" void __attribute__((thiscall)) FUN_004c38b0(void* self) {
    auto* tree = reinterpret_cast<OriginalNestedTree56*>(static_cast<uint8_t*>(self) + 4);
    *reinterpret_cast<const OriginalNestedDeleting**>(self) = dat_006c2690;
    {
        TreeUnwind cleanup{tree};
        FUN_005c0050(self);
        cleanup.active = false;
    }
    FUN_004c3880(tree);
}
