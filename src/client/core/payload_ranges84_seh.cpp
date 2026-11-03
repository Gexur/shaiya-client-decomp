#include "payload_ranges84.h"
namespace {
struct RangeCleanup {
    OriginalPointerRanges60* self;
    ~RangeCleanup() noexcept(false) {
        FUN_00585290(self);
    }
};
struct FailedConstructionCleanup {
    OriginalPointerRanges60* self;
    bool armed;
    ~FailedConstructionCleanup() noexcept(false) {
        if (armed)
            FUN_00585290(self);
    }
};
__declspec(noinline) void cleanup_payload(OriginalPayloadRanges84* self) {
    (void)FUN_005852f0(self);
}
} // namespace
extern "C" void __attribute__((thiscall)) FUN_00585440(OriginalPayloadRanges84* self) {
    self->vtable = dat_006cd3dc;
    RangeCleanup cleanup{&self->ranges};
    cleanup_payload(self);
}
extern "C" OriginalPayloadRanges84* __attribute__((thiscall))
FUN_00585700(OriginalPayloadRanges84* self) {
    self->vtable = dat_006cd3dc;
    self->ranges.first.begin = nullptr;
    self->ranges.first.end = nullptr;
    self->ranges.first.capacity = nullptr;
    self->ranges.second.begin = nullptr;
    self->ranges.second.end = nullptr;
    self->ranges.second.capacity = nullptr;
    self->ranges.third.begin = nullptr;
    self->ranges.third.end = nullptr;
    self->ranges.third.capacity = nullptr;
    self->payloads = nullptr;
    self->state0c = 0;
    self->payload_count = 0;
    self->state08 = 0;
    self->state04 = 0;
    // Original585742 activates only FuncInfo state2 before this call. Its
    // active action is585290(self+14); inactive states0/1 are not synthesized.
    FailedConstructionCleanup cleanup{&self->ranges, true};
    cleanup_payload(self);
    cleanup.armed = false;
    return self;
}
