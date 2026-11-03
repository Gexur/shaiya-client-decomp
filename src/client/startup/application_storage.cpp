#include "startup/application.h"
using shaiya::startup::String_00405710;
extern "C" {
char dat_007192f4[0x23] = {}, dat_007199f4[0x23] = {}, dat_00719a18[0x23] = {};
void* dat_007191d8 = nullptr;
shaiya::startup::MessagePump dat_007199ec = nullptr;
HWND dat_00719a3c = nullptr;
uint32_t dat_00719a48 = 0, dat_00719a4c = 0, dat_00719a60 = 0, dat_00719a68 = 0;
float dat_00719a50 = 0, dat_00719a54 = 0, dat_007085c0 = 60.0f;
int32_t dat_007085a4 = 1280, dat_007085a8 = 1024, dat_007085ac = 1280, dat_007085b0 = 1024;
String_00405710 dat_007085c4 = {{}, {}, 0, 15};
// OS-major cell belongs to CommonSystemState.
shaiya::graphics::native::NativeRenderer* dat_02209400 = nullptr;
}
