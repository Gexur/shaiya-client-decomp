#pragma once
#include <windows.h>
#include <stdint.h>
extern "C" {
LRESULT __attribute__((stdcall)) FUN_00525510(HWND, UINT, WPARAM, LPARAM);
uintptr_t __attribute__((stdcall)) FUN_00525560(void*);
}
static_assert(sizeof(HWND) == 4 && sizeof(WPARAM) == 4 && sizeof(LPARAM) == 4 &&
              sizeof(LRESULT) == 4);
static_assert(__is_same(decltype(&FUN_00525510), WNDPROC),
              "Actual Windows SDK WNDPROC stdcall16 ABI");
