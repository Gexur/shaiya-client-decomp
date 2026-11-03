#pragma once

#include "../crypto/bootstrap.h"

extern "C" ClientCryptoState client_crypto_state;

// One relocated source object for the original scattered crypto globals. Its
// fields are initially loader-zeroed. The recovered PRNG startup initializer
// and challenge callback both use this same object. Complete startup order
// and application integration remain separate recovery work.
