#pragma once

namespace Ht {
class HRect {
public:
    HRect(int x = 0, int y = 0, int w = 0, int h = 0);
    int x() const;
    int y() const;
    int width() const;
    int height() const;
private:
    int x_, y_, width_, height_;
};
}
