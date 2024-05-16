#include "HString.h"

namespace Ht {

HString::HString() {
}

void HString::append(const std::string& value) {
    m_data += value;
}

std::string HString::data() const {
    return m_data;
}

}

