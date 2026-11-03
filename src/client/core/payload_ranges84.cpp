#include "payload_ranges84.h"
#include "triple_list32.h"
#include "../startup/game_init.h"
#include "../runtime/allocations.h"

extern "C" const OriginalVirtualDelete dat_006cd3dc[1] = {FUN_00585500};
extern "C" void __attribute__((thiscall)) FUN_00585290(OriginalPointerRanges60* self) {
    if (self->third.begin != nullptr)
        fun_005cc620(self->third.begin);
    self->third.begin = nullptr;
    self->third.end = nullptr;
    self->third.capacity = nullptr;
    if (self->second.begin != nullptr)
        fun_005cc620(self->second.begin);
    self->second.begin = nullptr;
    self->second.end = nullptr;
    self->second.capacity = nullptr;
    if (self->first.begin != nullptr)
        fun_005cc620(self->first.begin);
    self->first.begin = nullptr;
    self->first.end = nullptr;
    self->first.capacity = nullptr;
}
extern "C" uint32_t __attribute__((thiscall)) FUN_005852f0(OriginalPayloadRanges84* self) {
    int32_t payload_index = 0;
    while (payload_index < self->payload_count) {
        if (dat_007191d4 != nullptr &&
            uint8_t(dat_007191d4->callbacks->callback_004(dat_007191d4, 0x15)) != 0) {
            void* current = self->payloads[payload_index];
            if (current != nullptr)
                FUN_005507c0(current);
        }
        void* current = self->payloads[payload_index];
        if (current != nullptr) {
            FUN_00550710(current);
            fun_005cc620(current);
            self->payloads[payload_index] = nullptr;
        }
        payload_index = static_cast<int32_t>(static_cast<uint32_t>(payload_index) + 1u);
    }
    if (self->payloads != nullptr) {
        fun_005cdc59(self->payloads);
        self->payloads = nullptr;
    }
    self->state0c = 0;
    self->payload_count = 0;
    self->state08 = 0;
    self->state04 = 0;
    uint32_t index = 0;
    while (self->ranges.first.begin != nullptr &&
           index < static_cast<uint32_t>(
                       static_cast<int32_t>(reinterpret_cast<uint32_t>(self->ranges.first.end) -
                                            reinterpret_cast<uint32_t>(self->ranges.first.begin)) >>
                       2)) {
        fun_005cc620(self->ranges.first.begin[index]);
        ++index;
    }
    if (self->ranges.first.begin != nullptr)
        fun_005cc620(self->ranges.first.begin);
    self->ranges.first.begin = nullptr;
    self->ranges.first.end = nullptr;
    self->ranges.first.capacity = nullptr;
    index = 0;
    while (self->ranges.second.begin != nullptr &&
           index <
               static_cast<uint32_t>(
                   static_cast<int32_t>(reinterpret_cast<uint32_t>(self->ranges.second.end) -
                                        reinterpret_cast<uint32_t>(self->ranges.second.begin)) >>
                   2)) {
        fun_005cc620(self->ranges.second.begin[index]);
        ++index;
    }
    if (self->ranges.second.begin != nullptr)
        fun_005cc620(self->ranges.second.begin);
    self->ranges.second.begin = nullptr;
    self->ranges.second.end = nullptr;
    self->ranges.second.capacity = nullptr;
    index = 0;
    while (self->ranges.third.begin != nullptr &&
           index < static_cast<uint32_t>(
                       static_cast<int32_t>(reinterpret_cast<uint32_t>(self->ranges.third.end) -
                                            reinterpret_cast<uint32_t>(self->ranges.third.begin)) >>
                       2)) {
        fun_005cc620(self->ranges.third.begin[index]);
        ++index;
    }
    if (self->ranges.third.begin != nullptr)
        fun_005cc620(self->ranges.third.begin);
    self->ranges.third.begin = nullptr;
    self->ranges.third.end = nullptr;
    self->ranges.third.capacity = nullptr;
    return 1;
}
extern "C" void* __attribute__((thiscall)) FUN_00585500(void* value, uint32_t flags) {
    FUN_00585440(static_cast<OriginalPayloadRanges84*>(value));
    if ((flags & 1) != 0)
        fun_005cc620(value);
    return value;
}
