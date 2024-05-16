#include "HRect.h"

namespace Ht {

HRect::HRect(int x, int y, int w, int h)
    : x_(x), y_(y), width_(w), height_(h) {}

int HRect::x() const { 
  return x_; 
}

int HRect::y() const { 
  return y_; 
}

int HRect::width() const { 
  return width_; 
}

int HRect::height() const { 
  return height_; 
}

}

