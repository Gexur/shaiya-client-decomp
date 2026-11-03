#pragma once

// Original 004013a0 takes no stack arguments and accesses global crypto state.
// The recovered transport API takes its canonical state explicitly instead.
extern "C" __declspec(dllexport) void client_crypto_reconnect_original_abi();
