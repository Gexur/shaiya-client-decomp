#include "com_resource.h"
#include "../startup/global_ownership.h"
#include "graphics/native_resources.h"
extern "C" OriginalResourcePair* __attribute__((thiscall))
FUN_0041fef0(OriginalResourcePair* object) {
    object->second = nullptr;
    object->first = nullptr;
    object->unknown08 = 0;
    object->unknown0c = 0;
    return object;
}
extern "C" void __attribute__((thiscall)) FUN_0041ff00(OriginalResourcePair* object) {
    OriginalComObject* current = object->first;
    if (current != nullptr) {
        shaiya::graphics::native::release_asset_resource(current);
        object->first = nullptr;
    }
    current = object->second;
    if (current != nullptr) {
        shaiya::graphics::native::release_asset_resource(current);
        object->second = nullptr;
    }
}
