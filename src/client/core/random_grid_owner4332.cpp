#include "random_grid_owner4332.h"
#include "runtime/thread_random.h"
extern "C" uint32_t __attribute__((thiscall)) FUN_0054f9a0(OriginalRandomGrid4332* self) {
    *static_cast<volatile uint32_t*>(&self->word_04) = 0;
    for (uint32_t column = 0; column != 20; ++column) {
        for (uint32_t row = 0; row != 27; ++row) {
            const int32_t first = fun_005cdacd();
            *static_cast<volatile float*>(&self->plane[0][row][column]) =
                static_cast<float>(first % 10000);
            const int32_t second = fun_005cdacd();
            *static_cast<volatile float*>(&self->plane[1][row][column]) =
                static_cast<float>(second % 10000);
        }
    }
    *static_cast<volatile uint32_t*>(&self->word_08) = 0;
    return 0; // Original final outer-loop DEC leaves EAX zero.
}
extern "C" OriginalRandomGrid4332* __attribute__((thiscall))
FUN_0054fb80(OriginalRandomGrid4332* self) {
    *static_cast<volatile uint32_t*>(&self->word_00) = 0;
    FUN_0054f9a0(self);
    return self;
}
