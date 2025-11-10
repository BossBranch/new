#pragma once

enum class ItemCommandVisibility : uint8_t {
    Visible          = 0,
    Hidden           = 1,
    DeferToBlockType = 2,
};