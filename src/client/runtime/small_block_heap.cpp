#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include "small_block_heap.h"
#include "../core/memory.h"

namespace {
uint32_t& word(void* base, uint32_t offset = 0) {
    return *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(base) + offset);
}
uint8_t& byte(void* base, uint32_t offset) {
    return *(static_cast<uint8_t*>(base) + offset);
}
uint32_t address(const void* pointer) {
    return reinterpret_cast<uint32_t>(pointer);
}
uint8_t* pointer(uint32_t value) {
    return reinterpret_cast<uint8_t*>(value);
}
uint32_t size_class(uint32_t size) {
    uint32_t result = uint32_t((int32_t(size) >> 4) - 1);
    return result > 63 ? 63 : result;
}
uint32_t class_bit(uint32_t index) {
    return 0x80000000u >> (index & 31);
}
uint8_t* group_data(SmallBlockRegion* region, uint32_t group) {
    return region->metadata + 0x144 + group * 0x204;
}

// Repeated literal list/bitmap sequences from the three original block
// operations, factored without introducing another allocator or API boundary.
void remove_free(SmallBlockRegion* region, uint32_t group, uint8_t* block, uint32_t index) {
    if (word(block, 4) == word(block, 8)) {
        const uint32_t mask = ~class_bit(index);
        const uint32_t table = index < 32 ? 0x44 : 0xc4;
        word(region->metadata, table + group * 4) &= mask;
        --byte(region->metadata, index + 4);
        if (byte(region->metadata, index + 4) == 0) {
            if (index < 32)
                region->class_mask_low &= mask;
            else
                region->class_mask_high &= mask;
        }
    }
    word(pointer(word(block, 8)), 4) = word(block, 4);
    word(pointer(word(block, 4)), 8) = word(block, 8);
}

void insert_free(SmallBlockRegion* region, uint32_t group, uint8_t* block, uint32_t index) {
    uint8_t* head = group_data(region, group) + index * 8;
    word(block, 4) = word(head, 4);
    word(block, 8) = address(head);
    word(head, 4) = address(block);
    word(pointer(word(block, 4)), 8) = address(block);
    if (word(block, 4) == word(block, 8)) {
        const uint8_t previous = byte(region->metadata, index + 4);
        byte(region->metadata, index + 4) = uint8_t(previous + 1);
        const uint32_t mask = class_bit(index);
        const uint32_t table = index < 32 ? 0x44 : 0xc4;
        if (previous == 0) {
            if (index < 32)
                region->class_mask_low |= mask;
            else
                region->class_mask_high |= mask;
        }
        word(region->metadata, table + group * 4) |= mask;
    }
}
} // namespace

extern "C" int32_t fun_005d9768(uint32_t threshold) {
    dat_022532b0 = static_cast<SmallBlockRegion*>(HeapAlloc(dat_022532c4, 0, 0x140));
    if (dat_022532b0 == nullptr)
        return 0;
    dat_022532a8 = nullptr;
    dat_022532ac = 0;
    dat_022532b8 = dat_022532b0;
    dat_022532b4 = threshold;
    dat_022532bc = 16;
    return 1;
}

extern "C" SmallBlockRegion* fun_005d97b0(const void* block) {
    SmallBlockRegion* region = dat_022532b0;
    for (;;) {
        if (address(dat_022532b0) + dat_022532ac * 20 <= address(region))
            return nullptr;
        if (address(block) - address(region->reserved_memory) < 0x100000)
            return region;
        ++region;
    }
}

extern "C" SmallBlockRegion* fun_005d9af3() {
    if (dat_022532ac == dat_022532bc) {
        void* resized = HeapReAlloc(dat_022532c4, 0, dat_022532b0, (dat_022532bc * 5 + 0x50) * 4);
        if (resized == nullptr)
            return nullptr;
        dat_022532bc += 16;
        dat_022532b0 = static_cast<SmallBlockRegion*>(resized);
    }
    SmallBlockRegion* region = dat_022532b0 + dat_022532ac;
    region->metadata = static_cast<uint8_t*>(HeapAlloc(dat_022532c4, 8, 0x41c4));
    if (region->metadata == nullptr)
        return nullptr;
    region->reserved_memory = static_cast<uint8_t*>(VirtualAlloc(nullptr, 0x100000, 0x2000, 4));
    if (region->reserved_memory == nullptr) {
        HeapFree(dat_022532c4, 0, region->metadata);
        return nullptr;
    }
    region->uncommitted_group_mask = 0xffffffffu;
    region->class_mask_low = 0;
    region->class_mask_high = 0;
    ++dat_022532ac;
    word(region->metadata) = 0xffffffffu;
    return region;
}

extern "C" int32_t fun_005d9baa(SmallBlockRegion* region) {
    uint32_t group = 0;
    for (uint32_t bits = region->uncommitted_group_mask; int32_t(bits) >= 0; bits <<= 1)
        ++group;
    uint8_t* data = group_data(region, group);
    uint8_t* head = data;
    for (uint32_t index = 0; index != 63; ++index, head += 8) {
        word(head, 8) = address(head);
        word(head, 4) = address(head);
    }
    uint8_t* base = region->reserved_memory + group * 0x8000;
    if (VirtualAlloc(base, 0x8000, 0x1000, 4) == nullptr)
        return -1;
    if (address(base) <= address(base) + 0x7000u) {
        const uint32_t pages = ((address(base) + 0x7000u - address(base)) >> 12) + 1;
        for (uint32_t index = 0; index != pages; ++index) {
            uint8_t* page = base + index * 0x1000;
            word(page, 8) = 0xffffffffu;
            word(page, 0xffc) = 0xffffffffu;
            word(page, 0x10) = address(page) + 0x100c;
            word(page, 0x0c) = 0xff0;
            word(page, 0x14) = address(page) - 0xff4;
            word(page, 0xff8) = 0xff0;
        }
    }
    word(data, 0x1fc) = address(base) + 0xc;
    word(base, 0x14) = address(data) + 0x1f8;
    word(data, 0x200) = address(base) + 0x700c;
    word(base, 0x7010) = address(data) + 0x1f8;
    word(region->metadata, 0x44 + group * 4) = 0;
    word(region->metadata, 0xc4 + group * 4) = 1;
    const uint8_t previous = byte(region->metadata, 0x43);
    byte(region->metadata, 0x43) = uint8_t(previous + 1);
    if (previous == 0)
        region->class_mask_high |= 1;
    region->uncommitted_group_mask &= ~class_bit(group);
    return int32_t(group);
}

extern "C" void fun_005d97db(SmallBlockRegion* region, void* block_pointer) {
    uint8_t* block = static_cast<uint8_t*>(block_pointer) - 4;
    const uint32_t group = (address(block_pointer) - address(region->reserved_memory)) >> 15;
    uint8_t* data = group_data(region, group);
    uint32_t size = word(block) - 1;
    if ((size & 1) != 0)
        return;
    uint8_t* next = block + size;
    const uint32_t next_size = word(next);
    const uint32_t previous_size = word(block - 4);
    if ((next_size & 1) == 0) {
        remove_free(region, group, next, size_class(next_size));
        size += next_size;
    }
    uint32_t index = size_class(size);
    uint32_t previous_index = 0;
    if ((previous_size & 1) == 0) {
        block -= previous_size;
        previous_index = size_class(previous_size);
        size += previous_size;
        index = size_class(size);
        if (previous_index != index)
            remove_free(region, group, block, previous_index);
    }
    if ((previous_size & 1) != 0 || previous_index != index)
        insert_free(region, group, block, index);
    word(block) = size;
    word(block + size - 4) = size;
    --word(data);
    if (word(data) != 0)
        return;
    if (dat_022532a8 != nullptr) {
        VirtualFree(dat_022532a8->reserved_memory + dat_022532c0 * 0x8000, 0x8000, 0x4000);
        dat_022532a8->uncommitted_group_mask |= class_bit(dat_022532c0);
        word(dat_022532a8->metadata, 0xc4 + dat_022532c0 * 4) = 0;
        --byte(dat_022532a8->metadata, 0x43);
        if (byte(dat_022532a8->metadata, 0x43) == 0)
            dat_022532a8->class_mask_high &= 0xfffffffeu;
        if (dat_022532a8->uncommitted_group_mask == 0xffffffffu) {
            VirtualFree(dat_022532a8->reserved_memory, 0, 0x8000);
            HeapFree(dat_022532c4, 0, dat_022532a8->metadata);
            fun_005cc630(dat_022532a8, dat_022532a8 + 1,
                         dat_022532ac * 20 - address(dat_022532a8) - 20 + address(dat_022532b0));
            --dat_022532ac;
            if (address(dat_022532a8) < address(region))
                --region;
            dat_022532b8 = dat_022532b0;
        }
    }
    dat_022532a8 = region;
    dat_022532c0 = group;
}

extern "C" int32_t fun_005d9cb0(SmallBlockRegion* region, void* block_pointer, uint32_t bytes) {
    uint8_t* block = static_cast<uint8_t*>(block_pointer) - 4;
    const uint32_t group = (address(block_pointer) - address(region->reserved_memory)) >> 15;
    const uint32_t wanted = (bytes + 0x17u) & 0xfffffff0u;
    const uint32_t old_size = word(block) - 1;
    uint8_t* next = block + old_size;
    const uint32_t next_size = word(next);
    if (int32_t(old_size) < int32_t(wanted)) {
        if ((next_size & 1) != 0 || int32_t(next_size + old_size) < int32_t(wanted))
            return 0;
        remove_free(region, group, next, size_class(next_size));
        const uint32_t remaining = next_size + old_size - wanted;
        if (int32_t(remaining) > 0) {
            uint8_t* remainder = block + wanted;
            insert_free(region, group, remainder, size_class(remaining));
            word(remainder) = remaining;
            word(remainder + remaining - 4) = remaining;
        }
        word(block) = wanted + 1;
        word(block + wanted - 4) = wanted + 1;
    } else if (int32_t(wanted) < int32_t(old_size)) {
        uint32_t remaining = old_size - wanted;
        word(block) = wanted + 1;
        uint8_t* remainder = block + wanted;
        word(remainder - 4) = wanted + 1;
        if ((next_size & 1) == 0) {
            remove_free(region, group, next, size_class(next_size));
            remaining += next_size;
        }
        insert_free(region, group, remainder, size_class(remaining));
        word(remainder) = remaining;
        word(remainder + remaining - 4) = remaining;
    }
    return 1;
}

extern "C" void* fun_005d9f8f(uint32_t bytes) {
    const uint32_t wanted = (bytes + 0x17u) & 0xfffffff0u;
    const int32_t wanted_index = (int32_t(bytes + 0x17u) >> 4) - 1;
    const uint32_t low_mask = wanted_index < 32 ? 0xffffffffu >> (uint32_t(wanted_index) & 31) : 0;
    const uint32_t high_mask =
        wanted_index < 32 ? 0xffffffffu : 0xffffffffu >> ((uint32_t(wanted_index) - 32) & 31);
    SmallBlockRegion* end = dat_022532b0 + dat_022532ac;
    SmallBlockRegion* region = dat_022532b8;
    while (address(region) < address(end) && (region->class_mask_high & high_mask) == 0 &&
           (region->class_mask_low & low_mask) == 0)
        ++region;
    if (region == end) {
        region = dat_022532b0;
        while (address(region) < address(dat_022532b8) &&
               (region->class_mask_high & high_mask) == 0 &&
               (region->class_mask_low & low_mask) == 0)
            ++region;
        if (region == dat_022532b8) {
            while (address(region) < address(end) && region->uncommitted_group_mask == 0)
                ++region;
            if (region == end) {
                region = dat_022532b0;
                while (address(region) < address(dat_022532b8) &&
                       region->uncommitted_group_mask == 0)
                    ++region;
                if (region == dat_022532b8) {
                    region = fun_005d9af3();
                    if (region == nullptr)
                        return nullptr;
                }
            }
            word(region->metadata) = uint32_t(fun_005d9baa(region));
            if (int32_t(word(region->metadata)) == -1)
                return nullptr;
        }
    }
    uint32_t group = word(region->metadata);
    if (group == 0xffffffffu || ((word(region->metadata, 0xc4 + group * 4) & high_mask) == 0 &&
                                 (word(region->metadata, 0x44 + group * 4) & low_mask) == 0)) {
        group = 0;
        while ((word(region->metadata, 0xc4 + group * 4) & high_mask) == 0 &&
               (word(region->metadata, 0x44 + group * 4) & low_mask) == 0)
            ++group;
    }
    uint8_t* data = group_data(region, group);
    uint32_t bits = word(region->metadata, 0x44 + group * 4) & low_mask;
    uint32_t index = 0;
    if (bits == 0) {
        bits = word(region->metadata, 0xc4 + group * 4) & high_mask;
        index = 32;
    }
    while (int32_t(bits) >= 0) {
        bits <<= 1;
        ++index;
    }
    uint8_t* block = pointer(word(data, index * 8 + 4));
    const uint32_t remaining = word(block) - wanted;
    // Unlike the free/resize clamps,005DA12B uses signed JLE. In particular,
    // an exact fit keeps the class at-1 and must unlink the selected block.
    int32_t signed_remaining_index = (int32_t(remaining) >> 4) - 1;
    if (signed_remaining_index > 63)
        signed_remaining_index = 63;
    const uint32_t remaining_index = uint32_t(signed_remaining_index);
    dat_022532b8 = region;
    if (remaining_index != index) {
        remove_free(region, group, block, index);
        if (remaining != 0)
            insert_free(region, group, block, remaining_index);
    }
    if (remaining != 0) {
        word(block) = remaining;
        word(block + remaining - 4) = remaining;
    }
    block += remaining;
    word(block) = wanted + 1;
    word(block + wanted - 4) = wanted + 1;
    const uint32_t previous = word(data);
    word(data) = previous + 1;
    if (previous == 0 && region == dat_022532a8 && group == dat_022532c0)
        dat_022532a8 = nullptr;
    word(region->metadata) = group;
    return block + 4;
}
