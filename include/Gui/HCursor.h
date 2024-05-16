#pragma once

namespace Ht {

enum class HCursorShape {
    Arrow,
    Hand
};

class HCursor {
public:
    HCursor(HCursorShape shape = HCursorShape::Arrow);
    HCursorShape shape() const;
private:
    HCursorShape shape_;
};

}
