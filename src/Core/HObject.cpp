#include "HObject.h"

namespace Ht {

HObject::HObject(HObject *parent) {
    m_parent = parent;
}

void HObject::setBlockSignals(bool block) {
    m_block = block;
}

bool HObject::signalsBlocked() const {
    return m_block;
}

HObject *HObject::parent() const {
    return m_parent;
}

void HObject::setObjectName(const HString &name) {
    m_name = name;
}

HString HObject::objectName() const {
    return m_name;
}

void HObject::setObjectType(HObjectType type) {
    m_ObjectType = type;
}

bool HObject::isWidgetType() const {
    return m_ObjectType == HObjectType::HWidget;
}

bool HObject::isWindowType() const {
    return m_ObjectType == HObjectType::HWindow;
}

}

