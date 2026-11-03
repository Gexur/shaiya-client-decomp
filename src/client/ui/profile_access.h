#pragma once
#include <stdint.h>
namespace shaiya::ui {
extern "C" {
// Only the proven maximum written prefix is represented. The original
// allocation extents are not established: "%d" has at most11 characters,
// so original "INTERFACE_%dX%d" writes at most34 bytes including its NUL.
extern char dat_02203440[34], dat_02203548[34];
extern const char dat_006bb5d5[1], dat_006bcafc[3], dat_006c5714[16];
extern const char dat_006c5724[19], dat_006c5738[19], dat_006c574c[20];
extern const char dat_006c5760[20], dat_006c5774[19], dat_006c5788[20];
extern const char dat_006c579c[19], dat_006c57b0[18];
void __attribute__((thiscall)) FUN_00526820(void*);
char* __attribute__((thiscall)) FUN_00526870(void*, const char*, const char*, int32_t);
char* __attribute__((thiscall)) FUN_00526c30(void*, const char*, const char*);
}
} // namespace shaiya::ui
