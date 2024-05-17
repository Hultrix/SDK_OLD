#pragma once

#include <cstdint>

namespace Ht {

using hsizetype = int64_t; 

enum class ScreenOrientation {
    PortraitOrientation,
    LandscapeOrientation
};

enum class WindowFlags {
    Window,
    Dialog
};

enum class Alignment : uint32_t {
    AlignLeft    = 0x1,
    AlignRight   = 0x2,
    AlignHCenter = 0x4,
    AlignTop     = 0x10,
    AlignBottom  = 0x20,
    AlignVCenter = 0x40,
    AlignCenter  = AlignHCenter | AlignVCenter
};

enum class HCursorShape {
    Arrow,
    Hand
};

enum class HObjectType {
    HWidget = 1,
    HWindow
};


}