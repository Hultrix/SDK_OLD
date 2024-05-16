#include "HCursor.h"

namespace Ht {

HCursor::HCursor(HCursorShape shape)
    : shape_(shape) {}

HCursorShape HCursor::shape() const {
    return shape_;
}

}
