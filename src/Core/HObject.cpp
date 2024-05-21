 /*
 Copyright 2024 Hultrix

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */
 
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

