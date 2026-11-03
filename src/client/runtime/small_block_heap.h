#pragma once

#include "heap.h"

// The seven address-named SBH entry points and canonical original storage are
// declared in heap.h. Metadata remains the original0x41c4-byte allocation;
// the implementation below accesses its observed fields by byte offset.
