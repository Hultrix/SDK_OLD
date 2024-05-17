#pragma once

#include "HNameSpace.h"
#include "HString.h"

namespace Ht {

class HObject {
public:
    HObject(HObject *parent = nullptr);
    void setBlockSignals(bool block);
    bool signalsBlocked() const;
    HObject *parent() const;
    void setObjectName(const HString &name);
    HString objectName() const;
    void setObjectType(HObjectType type);
    bool isWidgetType() const;
    bool isWindowType() const;
private:
    bool m_block; // Whether signals are blocked
    HObject *m_parent;
    HString m_name;
    HObjectType m_ObjectType;
};

}

