#include "item_classify.h"
namespace {
uint8_t mapped_004c8fb0(uint8_t code) {
    if ((code >= 1 && code <= 15) || (code >= 0x2d && code <= 0x41))
        return 5;
    switch (code) {
    case 0x10:
    case 0x1f:
    case 0x42:
    case 0x48:
    case 0x51:
    case 0x57:
        return 0;
    case 0x11:
    case 0x20:
    case 0x43:
    case 0x49:
    case 0x52:
    case 0x58:
        return 1;
    case 0x12:
    case 0x21:
    case 0x44:
    case 0x4a:
    case 0x53:
    case 0x59:
        return 2;
    case 0x13:
    case 0x22:
    case 0x45:
    case 0x4b:
    case 0x54:
    case 0x5a:
        return 6;
    case 0x14:
    case 0x23:
    case 0x46:
    case 0x4c:
    case 0x55:
    case 0x5b:
        return 3;
    case 0x15:
    case 0x24:
    case 0x47:
    case 0x4d:
    case 0x56:
    case 0x5c:
        return 4;
    case 0x16:
    case 0x25:
        return 9;
    case 0x17:
    case 0x60:
        return 8;
    case 0x18:
    case 0x27:
        return 7;
    case 0x28:
    case 0x61:
        return 11;
    case 0x2a:
        return 13;
    default:
        return 14;
    }
}
uint8_t mapped_004cba90(uint8_t code) {
    switch (code) {
    case 0x26:
    case 0x29:
    case 0x2b:
    case 0x2c:
    case 0x5e:
        return 0x19;
    case 0x2d:
        return 1;
    case 0x2e:
        return 2;
    case 0x2f:
        return 3;
    case 0x30:
        return 4;
    case 0x31:
    case 0x32:
        return 5;
    case 0x33:
    case 0x34:
        return 6;
    case 0x35:
    case 0x36:
        return 7;
    case 0x37:
    case 0x38:
        return 8;
    case 0x39:
        return 9;
    case 0x3a:
        return 10;
    case 0x3b:
        return 11;
    case 0x3c:
    case 0x3d:
        return 12;
    case 0x3e:
    case 0x3f:
        return 13;
    case 0x40:
        return 14;
    case 0x41:
        return 15;
    case 0x42:
    case 0x48:
        return 0x10;
    case 0x43:
    case 0x49:
        return 0x11;
    case 0x44:
    case 0x4a:
        return 0x12;
    case 0x45:
    case 0x4b:
        return 0x13;
    case 0x46:
    case 0x4c:
        return 0x14;
    case 0x47:
    case 0x4d:
        return 0x15;
    case 0x51:
    case 0x57:
        return 0x1f;
    case 0x52:
    case 0x58:
        return 0x20;
    case 0x53:
    case 0x59:
        return 0x21;
    case 0x54:
    case 0x5a:
        return 0x22;
    case 0x55:
    case 0x5b:
        return 0x23;
    case 0x56:
    case 0x5c:
        return 0x24;
    case 0x5f:
        return 0x1e;
    default:
        return code;
    }
}
} // namespace
extern "C" uint32_t recovered_004c8fb0(uint32_t argument, uint32_t incoming) {
    return (incoming & 0xffffff00u) | mapped_004c8fb0(static_cast<uint8_t>(argument));
}
extern "C" uint32_t recovered_004cba90(uint32_t argument, uint32_t incoming) {
    return (incoming & 0xffffff00u) | mapped_004cba90(static_cast<uint8_t>(argument));
}
// Textual original-entry adapters only; algorithms and actual case constants
// are above. Incoming EAX must be captured before a C++ prologue can reuse it.
extern "C" uint32_t __attribute__((naked, thiscall)) FUN_004c8fb0(void*, uint32_t) {
    __asm__ volatile(
        "pushl %eax\n\tpushl 8(%esp)\n\tcalll _recovered_004c8fb0\n\taddl $8,%esp\n\tretl $4");
}
extern "C" uint32_t __attribute__((naked, thiscall)) FUN_004cba90(void*, uint32_t) {
    __asm__ volatile(
        "pushl %eax\n\tpushl 8(%esp)\n\tcalll _recovered_004cba90\n\taddl $8,%esp\n\tretl $4");
}
