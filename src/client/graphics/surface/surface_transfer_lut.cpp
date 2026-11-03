#include "graphics/surface/surface_transfer_lut.h"
#include "graphics/render_half_decode_sse2.h"
namespace {
using u32 = uint32_t;
void square_index(u32 argument, u32 scratch) {
    __asm__ volatile(
        "flds (%0)\n\tfmuls (%0)\n\tfmuls %2\n\tfstps (%0)\n\tflds (%0)\n\tfistpl (%1)" ::"r"(
            argument),
        "r"(scratch), "m"(dat_006df40c)
        : "st", "memory");
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
// Complete original5f1dfc..5f1e45. Actual argument becomes the F32 square
// position. The hardware FISTP index is also the physical EAX return residue.
extern "C" u32 recovered_005f1dfc(u32 argument) {
    u32 index;
    square_index(argument, reinterpret_cast<uintptr_t>(&index));
    const u32 table = reinterpret_cast<uintptr_t>(dat_006defb0);
    const u32 first = table + index * 4;
    interpolation_begin(first, first + 4, reinterpret_cast<uintptr_t>(&index));
    if (index & 0x80000000u)
        __asm__ volatile("fadds %0" ::"m"(dat_006bb60c) : "st", "memory");
    interpolation_finish(argument);
    return index;
}
extern "C" __attribute__((naked, stdcall)) long double FUN_005f1dfc(float) {
    // This body preserves original ECX/EDX as well as returning actual80bit ST0.
    __asm__ volatile(
        "pushl %ecx\n\tpushl %edx\n\tleal 12(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005f1dfc\n\taddl $4,%esp\n\tpopl %edx\n\tpopl %ecx\n\tretl $4");
}

extern "C" {
extern const uint32_t dat_006defb0[256] = {
    0x00000000u, 0x3b144eb0u, 0x3b9ef3b0u, 0x3bf84b42u, 0x3c2a5c46u, 0x3c59c180u, 0x3c850eb5u,
    0x3c9da52au, 0x3cb6967au, 0x3ccfd852u, 0x3ce9628bu, 0x3d01974bu, 0x3d0e9b82u, 0x3d1bbba3u,
    0x3d28f5bcu, 0x3d364822u, 0x3d43b159u, 0x3d51301du, 0x3d5ec344u, 0x3d6c69c9u, 0x3d7a22c4u,
    0x3d83f6adu, 0x3d8ae465u, 0x3d91da35u, 0x3d98d7c7u, 0x3d9fdcd2u, 0x3da6e914u, 0x3dadfc47u,
    0x3db51635u, 0x3dbc36a3u, 0x3dc35d62u, 0x3dca8a3au, 0x3dd1bd02u, 0x3dd8f591u, 0x3de033bbu,
    0x3de7775du, 0x3deec050u, 0x3df60e74u, 0x3dfd61a6u, 0x3e025ce5u, 0x3e060b61u, 0x3e09bc38u,
    0x3e0d6f5fu, 0x3e1124c8u, 0x3e14dc68u, 0x3e189630u, 0x3e1c521au, 0x3e201016u, 0x3e23d01du,
    0x3e279225u, 0x3e2b5624u, 0x3e2f1c10u, 0x3e32e3e4u, 0x3e36ad94u, 0x3e3a7918u, 0x3e3e4668u,
    0x3e42157fu, 0x3e45e654u, 0x3e49b8e0u, 0x3e4d8d1du, 0x3e516304u, 0x3e553a8du, 0x3e5913b4u,
    0x3e5cee70u, 0x3e60cabfu, 0x3e64a89bu, 0x3e6887fbu, 0x3e6c68dbu, 0x3e704b3au, 0x3e742f0eu,
    0x3e781454u, 0x3e7bfb04u, 0x3e7fe321u, 0x3e81e650u, 0x3e83dbc0u, 0x3e85d1dcu, 0x3e87c8a3u,
    0x3e89c015u, 0x3e8bb830u, 0x3e8db0eeu, 0x3e8faa51u, 0x3e91a454u, 0x3e939ef9u, 0x3e959a3bu,
    0x3e97961bu, 0x3e999295u, 0x3e9b8fa7u, 0x3e9d8d52u, 0x3e9f8b93u, 0x3ea18a6au, 0x3ea389d2u,
    0x3ea589cbu, 0x3ea78a56u, 0x3ea98b6eu, 0x3eab8d15u, 0x3ead8f47u, 0x3eaf9204u, 0x3eb1954au,
    0x3eb39917u, 0x3eb59d6cu, 0x3eb7a246u, 0x3eb9a7a5u, 0x3ebbad88u, 0x3ebdb3ecu, 0x3ebfbad3u,
    0x3ec1c237u, 0x3ec3ca1au, 0x3ec5d27cu, 0x3ec7db58u, 0x3ec9e4b4u, 0x3ecbee85u, 0x3ecdf8d3u,
    0x3ed0039au, 0x3ed20ed8u, 0x3ed41a8au, 0x3ed626b5u, 0x3ed83351u, 0x3eda4065u, 0x3edc4de9u,
    0x3ede5be0u, 0x3ee06a4au, 0x3ee27923u, 0x3ee4886au, 0x3ee69821u, 0x3ee8a845u, 0x3eeab8d8u,
    0x3eecc9d6u, 0x3eeedb3fu, 0x3ef0ed13u, 0x3ef2ff53u, 0x3ef511fbu, 0x3ef7250au, 0x3ef93883u,
    0x3efb4c61u, 0x3efd60a7u, 0x3eff7553u, 0x3f00c531u, 0x3f01cfebu, 0x3f02dad9u, 0x3f03e5f5u,
    0x3f04f145u, 0x3f05fcc4u, 0x3f070875u, 0x3f081456u, 0x3f092067u, 0x3f0a2ca8u, 0x3f0b3917u,
    0x3f0c45b7u, 0x3f0d5284u, 0x3f0e5f7fu, 0x3f0f6caau, 0x3f107a03u, 0x3f118789u, 0x3f12953bu,
    0x3f13a31du, 0x3f14b12bu, 0x3f15bf64u, 0x3f16cdcau, 0x3f17dc5eu, 0x3f18eb1bu, 0x3f19fa05u,
    0x3f1b091bu, 0x3f1c185cu, 0x3f1d27c7u, 0x3f1e375cu, 0x3f1f471du, 0x3f205707u, 0x3f21671bu,
    0x3f227759u, 0x3f2387c2u, 0x3f249852u, 0x3f25a90cu, 0x3f26b9efu, 0x3f27cafbu, 0x3f28dc30u,
    0x3f29ed8bu, 0x3f2aff11u, 0x3f2c10bdu, 0x3f2d2290u, 0x3f2e348bu, 0x3f2f46adu, 0x3f3058f7u,
    0x3f316b66u, 0x3f327dfdu, 0x3f3390bau, 0x3f34a39du, 0x3f35b6a7u, 0x3f36c9d6u, 0x3f37dd2bu,
    0x3f38f0a5u, 0x3f3a0443u, 0x3f3b1808u, 0x3f3c2bf2u, 0x3f3d4000u, 0x3f3e5434u, 0x3f3f688cu,
    0x3f407d07u, 0x3f4191a8u, 0x3f42a66cu, 0x3f43bb54u, 0x3f44d05fu, 0x3f45e58eu, 0x3f46fadfu,
    0x3f481054u, 0x3f4925edu, 0x3f4a3ba8u, 0x3f4b5186u, 0x3f4c6789u, 0x3f4d7daau, 0x3f4e93f0u,
    0x3f4faa57u, 0x3f50c0e0u, 0x3f51d78bu, 0x3f52ee58u, 0x3f540545u, 0x3f551c55u, 0x3f563386u,
    0x3f574ad7u, 0x3f58624bu, 0x3f5979deu, 0x3f5a9191u, 0x3f5ba965u, 0x3f5cc15bu, 0x3f5dd971u,
    0x3f5ef1a6u, 0x3f6009fcu, 0x3f612272u, 0x3f623b08u, 0x3f6353bcu, 0x3f646c90u, 0x3f658586u,
    0x3f669e98u, 0x3f67b7cbu, 0x3f68d11bu, 0x3f69ea8du, 0x3f6b041bu, 0x3f6c1dc9u, 0x3f6d3795u,
    0x3f6e5180u, 0x3f6f6b8bu, 0x3f7085b2u, 0x3f719ff7u, 0x3f72ba5bu, 0x3f73d4dcu, 0x3f74ef7cu,
    0x3f760a38u, 0x3f772512u, 0x3f78400bu, 0x3f795b20u, 0x3f7a7651u, 0x3f7b91a2u, 0x3f7cad0eu,
    0x3f7dc896u, 0x3f7ee43cu, 0x3f800000u, 0x3f800000u,
};
extern const uint32_t dat_006df40c = 0x437e0000u;
}
