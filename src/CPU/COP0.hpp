#pragma once

#include "../types.hpp"

union Cop0SR {
    u32 value;

    struct {
        // Interrupt Enable
        u32 ie      :1;
        // Kernel / User (unused in PS?)
        u32 ku      :1;

        // Previous values
        u32 pIe     :1;
        u32 pKu     :1;

        // Old values
        u32 oIe     :1;
        u32 oKu     :1;

        u32 zero    :2;

        // Which interrupts can generate exceptions
        u32 interruptMask :8;

        // Disconnect the memory bus (all load/store go to cache)
        u32 disableMemoryAccess :1;

        // Invert the use of data and instruction caches (BUT WHY?)
        u32 swapCaches :1;

        // Parity zero (?)
        u32 pz :1;

        // When disableMemoryAccess is 1 (the cache is isolated)
        // this bit is set to 1 when a read is successful
        // (no need to go to memory, it was in the cache)
        u32 cm :1;

        // Parity error (?)
        u32 pe :1;

        // TLB Shutdown (probably unused since PS does not have MMU)
        u32 ts :1;

        // Use Exception vectors at 0x00000080 or in the ROM at 0x1fc00180
        u32 bev   :1;

        u32 zero2 :2;

        // Invert CPU endianness (SURE! WHY NOT!?)
        // Unlikely to be implemented on PS anyway
        u32 re :1;

        u32 zero3 :2;

        // Which coprocessors are enabled (4 fields, only 0 and 2 exist on PS)
        u32 cop :4;
    } fields;
};