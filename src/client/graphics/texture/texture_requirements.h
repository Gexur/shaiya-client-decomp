#pragma once
#include <stdint.h>
/**
 * @brief Normalize texture dimensions, format, and mip levels for device support.
 * @param width Optional in/out width; UINT32_MAX requests the default.
 * @param height Optional in/out height; UINT32_MAX requests the default.
 * @param depth Optional in/out volume depth.
 * @param mip_levels Optional in/out level count; zero requests the full chain.
 * @param usage Direct3D usage flags; UINT32_MAX is normalized to zero locally.
 * @param format Optional in/out Direct3D format value.
 * @param pool Direct3D memory pool from zero through three.
 * @param resource_type Direct3D texture, volume-texture, or cube-texture type.
 * @return Zero on success, D3DERR_INVALIDCALL for rejected arguments, or
 *         D3DERR_NOTAVAILABLE when no supported format can be chosen.
 * @note Custom ABI: the device arrives implicitly in EDX, followed by eight
 *       stack words and RET32. Callers require an explicit architecture bridge.
 *       Failed capability queries retain the original uninitialized scratch data.
 */
extern "C" int32_t __attribute__((stdcall))
normalize_texture_requirements(uint32_t* width, uint32_t* height, uint32_t* depth,
                               uint32_t* mip_levels, uint32_t usage, int32_t* format, uint32_t pool,
                               uint32_t resource_type);
