#pragma once

#include <stdint.h>
#include <stddef.h>

// Original three-word GMP-style object: allocation, signed size, little-endian
// 32-bit limbs. This structure represents the observed x86 layout only.
struct BigInt {
    int32_t capacity;
    int32_t signed_size;
    uint32_t* limbs;
};
static_assert(sizeof(void*) == 4, "recovered bigint code targets original x86");
static_assert(sizeof(BigInt) == 12, "original bigint object size");

struct RsaPublicKey {
    BigInt exponent;
    BigInt modulus;
};

#if defined(_WIN32)
#define SHAIYA_BIGINT_EXPORT __declspec(dllexport)
#else
#define SHAIYA_BIGINT_EXPORT
#endif

extern "C" {
// Original configurable allocator slots/default wrappers are defined in
// bigint_allocator.cpp; underlying CRT/FILE/abort remain external boundaries.
extern void* (*dat_0070c0d0)(uint32_t bytes);
extern void* (*dat_0070c0d4)(void* pointer, uint32_t old_bytes, uint32_t new_bytes);
extern void (*dat_0070c0d8)(void* pointer, uint32_t bytes);
void* fun_005d020a(void* pointer, uint32_t new_bytes); // original direct CRT realloc

// Original modular exponentiation control flow, with bounded differential
// evidence. Large Toom/FFT and runtime dependencies remain incomplete.
void fun_005861c0(BigInt* output, const BigInt* base, const BigInt* exponent,
                  const BigInt* modulus);
[[noreturn]] void fun_00589580(); // original hardware divide fatal path in bigint_failures.cpp
uint32_t fun_00586d80(BigInt* output, const BigInt* input, const BigInt* modulus);
void fun_00588c30(uint32_t* quotient, uint32_t* remainder, uint32_t extra_quotient_words,
                  const uint32_t* numerator, int32_t numerator_count, const uint32_t* denominator,
                  int32_t denominator_count);
void fun_00586b90(uint32_t* remainder, const uint32_t* numerator, int32_t numerator_count,
                  const uint32_t* denominator, int32_t denominator_count);
void fun_00586f70(uint32_t* output, const uint32_t* input, int32_t count);
void fun_00588b40(uint32_t* output, const uint32_t* left, const uint32_t* right, int32_t count);
SHAIYA_BIGINT_EXPORT void fun_00587720(uint32_t* output, const uint32_t* left,
                                       const uint32_t* right, int32_t count, uint32_t* scratch);
void fun_00587bb0(uint32_t* output, const uint32_t* input, uint32_t count, uint32_t* scratch);
void fun_00588790(uint32_t* output, const uint32_t* input, int32_t count, uint32_t* scratch);
void fun_00587e90(uint32_t* output, const uint32_t* left, const uint32_t* right, int32_t count,
                  uint32_t* scratch);
void fun_0058b030(uint32_t* output, const uint32_t* left, int32_t left_count, const uint32_t* right,
                  int32_t right_count);

SHAIYA_BIGINT_EXPORT void fun_00585dc0(BigInt* value);
SHAIYA_BIGINT_EXPORT void fun_00586000(BigInt* value);
SHAIYA_BIGINT_EXPORT void fun_00587300(BigInt* value, int32_t limb_capacity);
SHAIYA_BIGINT_EXPORT void fun_00586f20(BigInt* output, const BigInt* input);
SHAIYA_BIGINT_EXPORT void fun_00586020(BigInt* output, const BigInt* left, const BigInt* right);
SHAIYA_BIGINT_EXPORT void fun_00586be0(BigInt* output, const BigInt* left, const BigInt* right);
// Original 00405370: value EAX, input stack, byte length EBX.
// Preserves the original two pre-copy zero stores, including their out-of-range
// writes for inputs shorter than five bytes. No invented normalization is used.
SHAIYA_BIGINT_EXPORT void fun_00405370(BigInt* value, const void* input, uint32_t bytes);
// Original 004053E0: key EAX, input byte length EBX; output/output-length/input
// on stack; RET 12. Calls the partially closed recovered005861C0 dependency tree.
SHAIYA_BIGINT_EXPORT void fun_004053e0(const RsaPublicKey* key, void* output,
                                       uint32_t* output_bytes, const void* input,
                                       uint32_t input_bytes);

// Original little-endian limb helpers use ordinary x86 cdecl stack arguments.
// Carry/borrow/high-word returns omitted by Ghidra's void prototypes are made
// explicit from EAX in the original instruction listings.
SHAIYA_BIGINT_EXPORT int32_t fun_00587660(const uint32_t* left, const uint32_t* right,
                                          int32_t count);
SHAIYA_BIGINT_EXPORT uint32_t fun_0058b2a0(uint32_t* output, const uint32_t* left,
                                           const uint32_t* right, uint32_t count);
SHAIYA_BIGINT_EXPORT uint32_t fun_00587610(uint32_t* output, const uint32_t* left,
                                           const uint32_t* right, uint32_t count);
SHAIYA_BIGINT_EXPORT uint32_t fun_005873f0(uint32_t* output, const uint32_t* input, int32_t count,
                                           uint32_t addend);
SHAIYA_BIGINT_EXPORT uint32_t fun_00587350(uint32_t* output, const uint32_t* input, int32_t count,
                                           uint32_t subtrahend);
SHAIYA_BIGINT_EXPORT uint32_t fun_00587480(uint32_t* output, const uint32_t* input, uint32_t count,
                                           uint32_t shift);
SHAIYA_BIGINT_EXPORT uint32_t fun_00587510(uint32_t* output, const uint32_t* input, uint32_t count,
                                           uint32_t shift);
SHAIYA_BIGINT_EXPORT uint32_t fun_00587260(uint32_t* output, const uint32_t* input, uint32_t count,
                                           uint32_t multiplier);
SHAIYA_BIGINT_EXPORT uint32_t fun_00589590(uint32_t* output, const uint32_t* input, uint32_t count,
                                           uint32_t multiplier);
SHAIYA_BIGINT_EXPORT uint32_t fun_0058b350(uint32_t* output, const uint32_t* input, uint32_t count,
                                           uint32_t multiplier);
SHAIYA_BIGINT_EXPORT uint32_t fun_0058b480(uint32_t* output, const uint32_t* input, int32_t count,
                                           uint32_t carry);
SHAIYA_BIGINT_EXPORT uint32_t fun_00587590(uint32_t* output, const uint32_t* left,
                                           int32_t left_count, const uint32_t* right,
                                           int32_t right_count);
SHAIYA_BIGINT_EXPORT uint32_t fun_005876a0(uint32_t* output, const uint32_t* left,
                                           int32_t left_count, const uint32_t* right,
                                           int32_t right_count);
// Original reduction helper used by 005861C0; all five parameters are cdecl.
// Workspace includes 2*count+1 writable words and is modified in place.
SHAIYA_BIGINT_EXPORT void fun_00586ae0(uint32_t* output, const uint32_t* modulus, int32_t count,
                                       uint32_t inverse, uint32_t* workspace);
SHAIYA_BIGINT_EXPORT void fun_0058b2f0(uint32_t* output, const uint32_t* left, int32_t left_count,
                                       const uint32_t* right, int32_t right_count);
// Original dispatcher uses this fixed-workspace square for count<58. The direct
// primitive still reads/writes its first square at count0, as the binary does.
SHAIYA_BIGINT_EXPORT void fun_0058b0e0(uint32_t* output, const uint32_t* input, int32_t count);
SHAIYA_BIGINT_EXPORT int32_t fun_00589960(int32_t count, int32_t square_selector);
SHAIYA_BIGINT_EXPORT int32_t fun_005899c0(int32_t count, uint32_t shift);
SHAIYA_BIGINT_EXPORT void fun_00589de0(uint32_t** levels, int32_t depth);
// Normalized division primitives. Both modify the supplied numerator workspace;
// the returned high quotient word is separate from the lower quotient stores.
SHAIYA_BIGINT_EXPORT uint32_t fun_0058bd70(uint32_t* quotient, uint32_t* numerator,
                                           int32_t numerator_count, const uint32_t* denominator,
                                           int32_t denominator_count);
SHAIYA_BIGINT_EXPORT uint32_t fun_0058c270(uint32_t* quotient, int32_t extra_quotient_words,
                                           uint32_t* numerator, int32_t numerator_count,
                                           const uint32_t* denominator);
SHAIYA_BIGINT_EXPORT uint32_t fun_0058b4e0(uint32_t* quotient, int32_t extra_quotient_words,
                                           const uint32_t* numerator, int32_t numerator_count,
                                           uint32_t denominator);
SHAIYA_BIGINT_EXPORT uint32_t fun_00587030(uint32_t* output, const uint32_t* left,
                                           int32_t left_count, const uint32_t* right,
                                           int32_t right_count);
uint32_t fun_0058c040(uint32_t* quotient, uint32_t* numerator, const uint32_t* denominator,
                      int32_t denominator_count);
uint32_t fun_0058c190(uint32_t* quotient, uint32_t* numerator, const uint32_t* denominator,
                      int32_t half_denominator_count);
void fun_0058b450(const char* file, int32_t line, const char* expression);
[[noreturn]] void fun_005d0ba9(); // original CRT abort
void fun_00589640(BigInt* gcd, BigInt* first_coefficient, BigInt* second_coefficient,
                  const BigInt* left, const BigInt* right);
int32_t fun_0058c630(uint32_t* gcd, uint32_t* coefficient, int32_t* signed_coefficient_size,
                     uint32_t* numerator, int32_t numerator_count, uint32_t* denominator,
                     int32_t denominator_count);
void fun_00585df0(BigInt* output, const BigInt* left, const BigInt* right);
void fun_0058c4d0(BigInt* quotient, const BigInt* numerator, const BigInt* denominator);
uint32_t fun_0058d320(uint32_t numerator_high, uint32_t numerator_low, uint32_t denominator_high,
                      uint32_t denominator_low);
}
