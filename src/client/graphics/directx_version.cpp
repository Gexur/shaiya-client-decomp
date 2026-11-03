#include "graphics/directx_version.h"
#include <windows.h>
extern "C" {
extern const char s_006c86fc[] = "\\d3d9.dll";
extern const char s_006c8708[] = "\\dpnet.dll";
extern const char s_006c8714[] = "\\mpg2splt.ax";
extern const char s_006c8724[] = "\\d3d8.dll";
extern const char s_006c8730[] = "\\dinput.dll";
extern const char s_006c873c[] = "\\dplayx.dll";
extern const char s_006c8748[] = "\\d3drg8x.dll";
extern const char s_006c8758[] = "\\ddraw.dll";
}
namespace {
using namespace directx_version_detail;
void make_path(char* filename, const char* system, const char* suffix) {
    unsigned offset = 0;
    uint8_t byte;
    do {
        byte = load8(system + offset);
        store8(filename + offset, byte);
        ++offset;
    } while (byte != 0);
    --offset;
    unsigned n = 0;
    do {
        byte = load8(suffix + n);
        store8(filename + offset + n, byte);
        ++n;
    } while (byte != 0);
}
bool at_least(const uint32_t* value, uint32_t high, uint32_t low) {
    return value[1] > high || (value[1] == high && value[0] >= low);
}
void publish(uint32_t* major, uint32_t* minor, char* letter, uint32_t a, uint32_t b, uint8_t c) {
    if (major != nullptr)
        store32(major, a);
    if (minor != nullptr)
        store32(minor, b);
    if (letter != nullptr)
        store8(letter, c);
}
} // namespace
// Original005472c0..00547c24, cdecl RET. Each file query and threshold is
// retained in original order; later matches can replace earlier outputs.
extern "C" int32_t __attribute__((cdecl)) FUN_005472c0(uint32_t* major, uint32_t* minor,
                                                       char* letter) {
    bool found = false;
    char system[512], filename[512];
    uint32_t version[2];
    if (GetSystemDirectoryA(system, 260) != 0) {
        store8(system + 259, 0);
        make_path(filename, system, s_006c8758);
        if (FUN_005471c0(filename, version) >= 0) {
            if (at_least(version, 0x40002, 0x5f)) {
                publish(major, minor, letter, 1, 0, ' ');
                found = true;
            }
            if (at_least(version, 0x40003, 0x448)) {
                publish(major, minor, letter, 2, 0, ' ');
                found = true;
            }
            if (at_least(version, 0x40004, 0x44)) {
                publish(major, minor, letter, 3, 0, ' ');
                found = true;
            }
        }
        make_path(filename, system, s_006c8748);
        if (FUN_005471c0(filename, version) >= 0 && at_least(version, 0x40004, 0x46)) {
            publish(major, minor, letter, 3, 0, 'a');
            found = true;
        }
        make_path(filename, system, s_006c8758);
        if (FUN_005471c0(filename, version) >= 0) {
            if (at_least(version, 0x40005, 0x9b)) {
                publish(major, minor, letter, 5, 0, ' ');
                found = true;
            }
            if (at_least(version, 0x40006, 0x13e)) {
                publish(major, minor, letter, 6, 0, ' ');
                found = true;
            }
            if (at_least(version, 0x40006, 0x1b4)) {
                publish(major, minor, letter, 6, 1, ' ');
                found = true;
            }
        }
        make_path(filename, system, s_006c873c);
        if (FUN_005471c0(filename, version) >= 0 && at_least(version, 0x40006, 0x30206)) {
            publish(major, minor, letter, 6, 1, 'a');
            found = true;
        }
        make_path(filename, system, s_006c8758);
        if (FUN_005471c0(filename, version) >= 0 && at_least(version, 0x40007, 0x2bc)) {
            publish(major, minor, letter, 7, 0, ' ');
            found = true;
        }
        make_path(filename, system, s_006c8730);
        if (FUN_005471c0(filename, version) >= 0 && at_least(version, 0x40007, 0x2cc)) {
            publish(major, minor, letter, 7, 0, 'a');
            found = true;
        }
        make_path(filename, system, s_006c8758);
        if (FUN_005471c0(filename, version) >= 0) {
            const uint32_t platform = version[1] >> 16;
            if ((platform == 4 && at_least(version, 0x40008, 0x190)) ||
                (platform == 5 && FUN_00547290(version[0], version[1], 0x8d20190, 0x50001) >= 0)) {
                publish(major, minor, letter, 8, 0, ' ');
                found = true;
            }
        }
        make_path(filename, system, s_006c8724);
        if (FUN_005471c0(filename, version) >= 0) {
            const uint32_t platform = version[1] >> 16;
            if ((platform == 4 && at_least(version, 0x40008, 0x10371)) ||
                (platform == 5 && FUN_00547290(version[0], version[1], 0xa280371, 0x50001) >= 0)) {
                publish(major, minor, letter, 8, 1, ' ');
                found = true;
            }
            if ((platform == 4 && at_least(version, 0x40008, 0x10385)) ||
                (platform == 5 && FUN_00547290(version[0], version[1], 0xa280385, 0x50001) >= 0)) {
                publish(major, minor, letter, 8, 1, 'a');
                found = true;
            }
        }
        make_path(filename, system, s_006c8714);
        if (FUN_005471c0(filename, version) >= 0 && at_least(version, 0x60003, 0x10375)) {
            publish(major, minor, letter, 8, 1, 'b');
            found = true;
        }
        make_path(filename, system, s_006c8708);
        if (FUN_005471c0(filename, version) >= 0) {
            const uint32_t platform = version[1] >> 16;
            if ((platform == 4 && at_least(version, 0x40009, 0x86)) ||
                (platform == 5 && FUN_00547290(version[0], version[1], 0xe5d0086, 0x50002) >= 0)) {
                publish(major, minor, letter, 8, 2, ' ');
                found = true;
            }
        }
        make_path(filename, system, s_006c86fc);
        if (FUN_005471c0(filename, version) >= 0) {
            publish(major, minor, letter, 9, 0, ' ');
            return 0;
        }
        if (found)
            return 0;
    }
    publish(major, minor, letter, 0, 0, ' ');
    return 0;
}
