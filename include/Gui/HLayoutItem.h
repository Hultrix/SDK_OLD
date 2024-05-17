#pragma once

#include "HNameSpace.h"

namespace Ht {

class HLayoutItem{
public:
    HLayoutItem(Ht::Alignment alignment = Ht::Alignment());
    virtual ~HLayoutItem();
    Ht::Alignment alignment() const;
    
};

}

