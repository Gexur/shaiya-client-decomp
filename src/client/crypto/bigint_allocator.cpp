#include "bigint_allocator.h"

// Recovered from original instructions and initialized .data pointers:
// evidence/cpp-bigint-allocator-disassembly.txt and cpp-bigint-allocator-recovery.json.
// The REA/Ghidra fprintf/fwprintf ambiguity is resolved by the original ASCII
// format bytes and the formatter's byte-sized format reads, not its guessed name.
namespace {
const char str_0070c0dc[] = "GNU MP: Cannot allocate memory (size=%u)\n";
const char str_0070c108[] = "GNU MP: Cannot reallocate memory (old_size=%u new_size=%u)\n";
} // namespace

extern "C" {
BigIntAllocate dat_0070c0d0 = &fun_00586ea0;
BigIntReallocate dat_0070c0d4 = &fun_00586ed0;
BigIntFree dat_0070c0d8 = &fun_00586f10;
}

// 0x586ea0..0x586ecb. Zero-byte requests take the same null-result check.
extern "C" void* fun_00586ea0(uint32_t bytes) {
    void* result = fun_005cfade(bytes);
    if (result == nullptr) {
        fun_005cdb8c(&dat_0070e280, str_0070c0dc, bytes);
        fun_005d0ba9();
    }
    return result;
}

// 0x586ed0..0x586f05. old_bytes is used only in the failure diagnostic;
// it is not an argument of the original CRT realloc call.
extern "C" void* fun_00586ed0(void* pointer, uint32_t old_bytes, uint32_t new_bytes) {
    void* result = fun_005d020a(pointer, new_bytes);
    if (result == nullptr) {
        fun_005cdb8c(&dat_0070e280, str_0070c108, old_bytes, new_bytes);
        fun_005d0ba9();
    }
    return result;
}

// 0x586f10..0x586f1b. The callback ABI has a second size argument, but the
// original ignores it and calls its returning free implementation once.
extern "C" void fun_00586f10(void* pointer, uint32_t bytes) {
    (void)bytes;
    fun_005cfaf0(pointer);
}
