#include <stdint.h>
extern "C" {
struct RibbonInputPosition {
    float x, y, z;
};
static_assert(sizeof(RibbonInputPosition) == 12);
// Actual constructor/caller family sets count5. Original erased capacity is unknown.
RibbonInputPosition dat_02224b18[5] = {};
RibbonInputPosition dat_0222a8d8[5] = {};
__asm__(
    ".globl _dat_02224b1c\n.set _dat_02224b1c, _dat_02224b18+4\n.globl _dat_02224b20\n.set _dat_02224b20, _dat_02224b18+8\n.globl _dat_0222a8dc\n.set _dat_0222a8dc, _dat_0222a8d8+4\n.globl _dat_0222a8e0\n.set _dat_0222a8e0, _dat_0222a8d8+8\n");
}
