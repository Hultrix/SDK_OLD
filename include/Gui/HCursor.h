#pragma once

#include "HNameSpace.h"

namespace Ht {

class HCursor {
public:
    HCursor(HCursorShape shape = HCursorShape::Arrow);
    HCursorShape shape() const;
private:
    HCursorShape shape_;
};

}
