#pragma once
#include <string>
#include <iostream> // Include for std::ostream
#include "HNameSpace.h" // Ensure this include is correct

namespace Ht {

class HString {
public:
    HString();
    HString(const char* str);

    void append(const std::string& value);
    std::string data() const;
    void clear();
    void chop(int64_t n);
    HString chopped(int64_t len) const&;
    HString chopped(int64_t len) &&;
    const char* c_str() const;

    // Overload the equality operators
    bool operator==(const HString& other) const;
    bool operator==(const char* other) const;

    // Overload the << operator for HString
    friend std::ostream& operator<<(std::ostream& os, const HString& hstr);

private:
    std::string m_data;
};

} // namespace Ht

