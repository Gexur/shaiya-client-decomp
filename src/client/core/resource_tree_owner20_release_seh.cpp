#include "resource_tree_owner20_release.h"
#include "core/tree48_lookup.h"
#include "runtime/allocations.h"
namespace {
struct KeyUnwind {
    shaiya::startup::String_00405710* key;
    bool active = true;
    ~KeyUnwind() noexcept(false) {
        if (active)
            FUN_00529db0(key);
    }
};
__declspec(noinline) void complete_release(OriginalResourceTreeOwner20* self,
                                           shaiya::startup::String_00405710* key) {
    OriginalTreeNode48* found;
    FUN_0054b170(&self->tree04, &found, key);
    if (found != self->tree04.header) {
        void* value = found->value;
        if (value != nullptr) {
            using Delete = void(__attribute__((thiscall))*)(void*, uint32_t);
            (*static_cast<const Delete**>(value))[0](value, 1);
            found->value = nullptr;
        }
        OriginalTreeNode48* ignored;
        FUN_00529ee0(&self->tree04, &ignored, found);
    }
    // Original state0 stays active during this ordinary free. Its unwind
    // action6b30f0 invokes the actual canonical string destructor on the
    // by-value argument; the normal path does not reset private key fields.
    if (key->capacity_018 >= 16)
        fun_005cc620(*reinterpret_cast<void**>(key->storage_004));
}
} // namespace
extern "C" void __attribute__((thiscall)) FUN_0052a360(OriginalResourceTreeOwner20* self,
                                                       shaiya::startup::String_00405710 key) {
    KeyUnwind cleanup{&key};
    complete_release(self, &key);
    cleanup.active = false;
}
