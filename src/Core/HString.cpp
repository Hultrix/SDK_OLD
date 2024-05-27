#include "HString.h"

namespace Ht {

HString::HString() : m_data("") {}

HString::HString(const char* str) : m_data(str) {}

void HString::append(const std::string& value) {
    m_data += value;
}

std::string HString::data() const {
    return m_data;
}

void HString::clear() {
    m_data.clear();
}

void HString::chop(hsizetype n) {
    if (n < 0 || static_cast<std::size_t>(n) > m_data.size()) {
        m_data.clear();
    } else {
        m_data.resize(m_data.size() - n);
    }
}

HString HString::chopped(hsizetype len) const& {
    if (len < 0 || static_cast<std::size_t>(len) > m_data.size()) {
        return HString();
    }
    return HString(m_data.substr(0, m_data.size() - len).c_str());
}

HString HString::chopped(hsizetype len) && {
    if (len < 0 || static_cast<std::size_t>(len) > m_data.size()) {
        return HString();
    }
    return HString(std::move(m_data.substr(0, m_data.size() - len).c_str()));
}

std::ostream& operator<<(std::ostream& os, const HString& hstr) {
    os << hstr.m_data;
    return os;
}

const char* HString::c_str() const {
    return m_data.c_str();
}

// Define the equality operators
bool HString::operator==(const HString& other) const {
    return m_data == other.m_data;
}

bool HString::operator==(const char* other) const {
    return m_data == other;
}

} // namespace Ht

