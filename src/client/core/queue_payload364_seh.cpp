#include "queue_payload364.h"
#include "resource_record.h"
namespace {
struct MemberBuffers {
    void* self;
    ~MemberBuffers() noexcept(false) {
        FUN_0040a900(self);
    }
};
} // namespace
extern "C" void __attribute__((thiscall)) FUN_005ae040(OriginalQueuePayload364* self) {
    // Actual FuncInfo704504/action6b44f0 ->40a900(self+158), both paths.
    MemberBuffers cleanup{reinterpret_cast<uint8_t*>(self) + 0x158};
    FUN_005adad0(self);
}
