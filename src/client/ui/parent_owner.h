#pragma once
#include "constructors.hpp"
namespace shaiya::ui {
extern "C" {
// Exact table symbol identity is required by the original seven-byte leaf.
// Its ten actual entries are defined in the staged ui/virtual_tables.cpp.
extern const VtableAddress PTR_FUN_006bcc18[10];
void __attribute__((thiscall)) FUN_00422c00(void*);
}
} // namespace shaiya::ui
