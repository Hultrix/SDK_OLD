#include "HMargins.h"

namespace Ht {

HMargins::HMargins(int t, int r, int b, int l)
    : top_(t), right_(r), bottom_(b), left_(l) {}

int HMargins::top() const { 
  return top_; 
}

int HMargins::right() const { 
  return right_; 
}

int HMargins::bottom() const { 
  return bottom_; 
}

int HMargins::left() const { 
  return left_; 
}

}

