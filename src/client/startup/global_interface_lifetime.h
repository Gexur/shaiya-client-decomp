#pragma once
#include <stddef.h>
#include <stdint.h>
using OriginalInterfaceDeleting = void*(__attribute__((thiscall)) *)(void*, uint32_t);

// Loaders 584d50/584e80/584fb0/5850e0 store the four cloak texture
// tables here. Their counts are read directly from the corresponding CTL files.
struct OriginalCloakTextureTables36 {
    const OriginalInterfaceDeleting* vtable;
    void** dark_elf_textures;
    void** elf_textures;
    void** human_textures;
    void** vail_textures;
    int32_t dark_elf_count;
    int32_t elf_count;
    int32_t human_count;
    int32_t vail_count;
};
static_assert(sizeof(OriginalCloakTextureTables36) == 0x24);
static_assert(offsetof(OriginalCloakTextureTables36, dark_elf_textures) == 0x04 &&
              offsetof(OriginalCloakTextureTables36, elf_textures) == 0x08 &&
              offsetof(OriginalCloakTextureTables36, human_textures) == 0x0c &&
              offsetof(OriginalCloakTextureTables36, vail_textures) == 0x10);
static_assert(offsetof(OriginalCloakTextureTables36, dark_elf_count) == 0x14 &&
              offsetof(OriginalCloakTextureTables36, elf_count) == 0x18 &&
              offsetof(OriginalCloakTextureTables36, human_count) == 0x1c &&
              offsetof(OriginalCloakTextureTables36, vail_count) == 0x20);

extern "C" {
extern const OriginalInterfaceDeleting dat_006cd2a8[1];
extern OriginalCloakTextureTables36 dat_0070c0ac;
void* __attribute__((thiscall)) FUN_00584d30(void*, uint32_t flags);
void fun_006b7670();
void fun_006ba730();
}
