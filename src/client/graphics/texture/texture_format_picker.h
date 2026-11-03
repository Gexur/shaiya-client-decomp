#pragma once
#include "graphics/texture/texture_format.h"
/**
 * @brief Choose a supported texture format closest to the desired descriptor.
 * @param device Direct3D device queried for capabilities, or null to skip support checks.
 * @param usage Resource usage flags; original local argument updates are retained.
 * @param resource_type Direct3D resource type supplied to CheckDeviceFormat.
 * @param desired_format Requested format descriptor.
 * @return The chosen Direct3D format value, or zero when no candidate is selected.
 * @note Exact matches win. Scored ties prefer fewer storage bits, then retain
 *       the earlier entry. Failed COM output calls retain original uninitialized storage.
 */
extern "C" uint32_t __attribute__((stdcall))
choose_supported_texture_format(void* device, uint32_t usage, uint32_t resource_type,
                                const TextureFormatRecord* desired_format);
