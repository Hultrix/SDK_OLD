#pragma once

namespace Ht {
class HMargins {
public:
    HMargins(int t = 0, int r = 0, int b = 0, int l = 0);
    int top() const;
    int right() const;
    int bottom() const;
    int left() const;
private:
    int top_, right_, bottom_, left_;
};
}
