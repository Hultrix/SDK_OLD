#include "HSize.h"

namespace Ht {

HSize::HSize(int w, int h)
    : width_(w), height_(h) {}

int HSize::width() const { 
  return width_; 
}

int HSize::height() const { 
  return height_; 
}

}

