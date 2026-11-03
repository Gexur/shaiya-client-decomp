#include "constructors.hpp"

// Source evidence: client/game.exe SHA256
// 796af141fd13451bab67ae0bae02d2177b1fe60af51775f296bec7b0eff752da.
// Exact disassembly and limitations: evidence/cpp-ui-original-disassembly.txt
// and evidence/cpp-ui-recovery.json. No binary code is embedded here.
namespace shaiya::ui {

extern "C" __attribute__((noinline)) u32 __attribute__((thiscall)) FUN_004a1110(void*) {
    // Original body is MOV EAX,1; RET, not an inferred success stub.
    return 1;
}

extern "C" __attribute__((noinline)) void __attribute__((thiscall)) FUN_0040a790(void*, u32) {
    // Original body is RET 4. The stack word is ignored.
}

extern "C" __attribute__((noinline)) void __attribute__((thiscall))
FUN_00422c10(void*, u32, u32, u32, u32, u32, u32, u32) {
    // Original body is RET 0x1c. The seven stack words are ignored.
}

} // namespace shaiya::ui
