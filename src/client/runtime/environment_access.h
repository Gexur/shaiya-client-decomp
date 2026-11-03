#pragma once
#include <stdint.h>
#include "runtime/environment.h"
extern "C" {
extern char** dat_0224ee0c;
extern uint16_t** dat_0224ee10;
char* fun_005dec3d(const char* name);
int32_t fun_005e0bc6(const char* left, const char* right, uint32_t count);
int32_t fun_005e0c14();
// Original5e15e7 takes name on the stack and name_length in EDI.
int32_t fun_005e15e7(const char* name, uint32_t name_length);
// Original5e1634 receives the array in EDI, without a stack argument.
char** fun_005e1634(char* const* source);
int32_t fun_005e1695(char** input, int32_t update_os);
char* fun_005e186b(const char* source);
char* fun_005e1896(const char* source, uint32_t character);
char* fun_005d6670(const char* source, uint32_t character);
}
