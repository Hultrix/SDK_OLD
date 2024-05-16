#pragma once
#include <string>

namespace Ht {

class HString {
public:
    HString();
    void append(const std::string& value);
    std::string data() const;
private:
    std::string m_data;
};

}

