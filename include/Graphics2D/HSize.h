#pragma once

namespace Ht {
class HSize {
public:
    HSize(int w = 0, int h = 0);
    int width() const;
    int height() const;
private:
    int width_, height_;
};
}

