#include "HString.h"

namespace Ht {

HString::HString() : m_data("") {
}

HString::HString(const char *str) : m_data(str) {
}

void HString::append(const std::string& value) {
    m_data += value;
}

std::string HString::data() const {
    return m_data;
}

}

