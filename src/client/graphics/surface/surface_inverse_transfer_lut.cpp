#include "graphics/surface/surface_inverse_transfer_lut.h"
#include "graphics/render_rsqrt_scalar.h"
#include "graphics/surface/surface_transfer_lut.h"
#include "graphics/render_half_decode_sse2.h"
namespace {
using u32 = uint32_t;
void position_index(u32 argument, u32 scratch) {
    __asm__ volatile(
        "flds (%0)\n\tsubl $4,%%esp\n\tfstps (%%esp)\n\tcalll _FUN_0064f3a4@4\n\tfmuls (%0)\n\tfmuls %2\n\tfstps (%0)\n\tflds (%0)\n\tfistpl (%1)" ::
            "r"(argument),
        "r"(scratch), "m"(dat_006df40c)
        : "eax", "ecx", "edx", "st", "memory", "cc");
}
void interpolation_begin(u32 first, u32 second, u32 index) {
    __asm__ volatile("flds (%0)\n\tflds (%1)\n\tfsub %%st(1),%%st(0)\n\tfildl (%2)" ::"r"(first),
                     "r"(second), "r"(index)
                     : "st", "st(1)", "st(2)", "memory");
}
void interpolation_finish(u32 argument) {
    __asm__ volatile("fsubrs (%0)\n\tfmulp %%st,%%st(1)\n\tfaddp %%st,%%st(1)" ::"r"(argument)
                     : "st", "st(1)", "st(2)", "memory");
}
} // namespace
// Complete original005f1daa..005f1dfc. The original caller word receives
// the rounded table position; physical EAX retains the actual FISTP index.
extern "C" uint32_t recovered_005f1daa(uint32_t argument) {
    u32 index;
    position_index(argument, reinterpret_cast<uintptr_t>(&index));
    const u32 first = reinterpret_cast<uintptr_t>(dat_006debb0) + index * 4u;
    // Actual index255 second word is the existing neighboring forward table.
    const u32 second = index == 255u ? reinterpret_cast<uintptr_t>(dat_006defb0) : first + 4u;
    interpolation_begin(first, second, reinterpret_cast<uintptr_t>(&index));
    if (index & 0x80000000u)
        __asm__ volatile("fadds %0" ::"m"(dat_006bb60c) : "st", "memory");
    interpolation_finish(argument);
    return index;
}
extern "C" __attribute__((naked, stdcall)) long double FUN_005f1daa(uint32_t) {
    __asm__ volatile(
        "pushl %ecx\n\tpushl %edx\n\tleal 12(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005f1daa\n\taddl $4,%esp\n\tpopl %edx\n\tpopl %ecx\n\tretl $4");
}
extern "C" {
extern const uint32_t dat_006debb0[256] = {
    0x00000000u, 0x3bd56bd3u, 0x3c486344u, 0x3c90da15u, 0x3cbc2677u, 0x3ce67704u, 0x3d080183u,
    0x3d1c7728u, 0x3d30a8fbu, 0x3d44a03cu, 0x3d586400u, 0x3d6bf9e7u, 0x3d7f6679u, 0x3d8956bdu,
    0x3d92e906u, 0x3d9c6b70u, 0x3da5df22u, 0x3daf451bu, 0x3db89e3eu, 0x3dc1eb50u, 0x3dcb2d04u,
    0x3dd463f7u, 0x3ddd90b9u, 0x3de6b3cau, 0x3defcda0u, 0x3df8dea6u, 0x3e00f3a0u, 0x3e0573e3u,
    0x3e09f046u, 0x3e0e68f0u, 0x3e12de06u, 0x3e174fa6u, 0x3e1bbdf2u, 0x3e202906u, 0x3e2490fdu,
    0x3e28f5f1u, 0x3e2d57fbu, 0x3e31b72fu, 0x3e3613a4u, 0x3e3a6d6eu, 0x3e3ec4a0u, 0x3e43194du,
    0x3e476b84u, 0x3e4bbb57u, 0x3e5008d7u, 0x3e54540fu, 0x3e589d0fu, 0x3e5ce3e5u, 0x3e61289du,
    0x3e656b44u, 0x3e69abe5u, 0x3e6dea8du, 0x3e722745u, 0x3e766217u, 0x3e7a9b0eu, 0x3e7ed235u,
    0x3e8183c9u, 0x3e839d98u, 0x3e85b68cu, 0x3e87cea8u, 0x3e89e5f2u, 0x3e8bfc6bu, 0x3e8e1219u,
    0x3e9026ffu, 0x3e923b20u, 0x3e944e7fu, 0x3e966120u, 0x3e987307u, 0x3e9a8436u, 0x3e9c94afu,
    0x3e9ea476u, 0x3ea0b38eu, 0x3ea2c1fbu, 0x3ea4cfbbu, 0x3ea6dcd5u, 0x3ea8e94au, 0x3eaaf51cu,
    0x3ead004eu, 0x3eaf0ae2u, 0x3eb114d9u, 0x3eb31e37u, 0x3eb526feu, 0x3eb72f2fu, 0x3eb936cdu,
    0x3ebb3dd8u, 0x3ebd4454u, 0x3ebf4a43u, 0x3ec14fa5u, 0x3ec3547eu, 0x3ec558cdu, 0x3ec75c95u,
    0x3ec95fd8u, 0x3ecb6297u, 0x3ecd64d4u, 0x3ecf6690u, 0x3ed167ceu, 0x3ed3688eu, 0x3ed568d1u,
    0x3ed76899u, 0x3ed967e9u, 0x3edb66bfu, 0x3edd651fu, 0x3edf630au, 0x3ee16080u, 0x3ee35d84u,
    0x3ee55a16u, 0x3ee75636u, 0x3ee951e8u, 0x3eeb4d2au, 0x3eed4800u, 0x3eef4269u, 0x3ef13c68u,
    0x3ef335fcu, 0x3ef52f26u, 0x3ef727eau, 0x3ef92046u, 0x3efb183cu, 0x3efd0fcdu, 0x3eff06fau,
    0x3f007ee2u, 0x3f017a16u, 0x3f027519u, 0x3f036fecu, 0x3f046a8fu, 0x3f056502u, 0x3f065f47u,
    0x3f07595du, 0x3f085344u, 0x3f094cfeu, 0x3f0a468bu, 0x3f0b3febu, 0x3f0c391eu, 0x3f0d3224u,
    0x3f0e2affu, 0x3f0f23afu, 0x3f101c32u, 0x3f11148cu, 0x3f120cbau, 0x3f1304bfu, 0x3f13fc9au,
    0x3f14f44bu, 0x3f15ebd3u, 0x3f16e333u, 0x3f17da6bu, 0x3f18d17au, 0x3f19c860u, 0x3f1abf1fu,
    0x3f1bb5b7u, 0x3f1cac28u, 0x3f1da272u, 0x3f1e9895u, 0x3f1f8e92u, 0x3f20846au, 0x3f217a1cu,
    0x3f226fa8u, 0x3f23650fu, 0x3f245a52u, 0x3f254f70u, 0x3f264469u, 0x3f27393fu, 0x3f282df1u,
    0x3f29227fu, 0x3f2a16eau, 0x3f2b0b31u, 0x3f2bff56u, 0x3f2cf358u, 0x3f2de738u, 0x3f2edaf6u,
    0x3f2fce91u, 0x3f30c20bu, 0x3f31b564u, 0x3f32a89bu, 0x3f339bb1u, 0x3f348ea6u, 0x3f35817au,
    0x3f36742fu, 0x3f3766c3u, 0x3f385936u, 0x3f394b8au, 0x3f3a3dbeu, 0x3f3b2fd3u, 0x3f3c21c8u,
    0x3f3d139eu, 0x3f3e0556u, 0x3f3ef6eeu, 0x3f3fe868u, 0x3f40d9c4u, 0x3f41cb01u, 0x3f42bc20u,
    0x3f43ad22u, 0x3f449e06u, 0x3f458eccu, 0x3f467f75u, 0x3f477001u, 0x3f486071u, 0x3f4950c2u,
    0x3f4a40f8u, 0x3f4b3111u, 0x3f4c210du, 0x3f4d10edu, 0x3f4e00b2u, 0x3f4ef05au, 0x3f4fdfe7u,
    0x3f50cf58u, 0x3f51beaeu, 0x3f52ade8u, 0x3f539d07u, 0x3f548c0cu, 0x3f557af5u, 0x3f5669c4u,
    0x3f575878u, 0x3f584711u, 0x3f593590u, 0x3f5a23f6u, 0x3f5b1241u, 0x3f5c0072u, 0x3f5cee89u,
    0x3f5ddc87u, 0x3f5eca6bu, 0x3f5fb835u, 0x3f60a5e7u, 0x3f619380u, 0x3f6280ffu, 0x3f636e65u,
    0x3f645bb3u, 0x3f6548e8u, 0x3f663604u, 0x3f672309u, 0x3f680ff4u, 0x3f68fcc8u, 0x3f69e983u,
    0x3f6ad627u, 0x3f6bc2b3u, 0x3f6caf27u, 0x3f6d9b83u, 0x3f6e87c8u, 0x3f6f73f5u, 0x3f70600cu,
    0x3f714c0bu, 0x3f7237f4u, 0x3f7323c4u, 0x3f740f7fu, 0x3f74fb22u, 0x3f75e6afu, 0x3f76d225u,
    0x3f77bd85u, 0x3f78a8ceu, 0x3f799401u, 0x3f7a7f1eu, 0x3f7b6a25u, 0x3f7c5516u, 0x3f7d3ff1u,
    0x3f7e2ab6u, 0x3f7f1566u, 0x3f800000u, 0x3f800000u,
};
}
