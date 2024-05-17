#pragma once
#include <string>
#include <HNameSpace.h>

namespace Ht {

class HString {
public:
    HString();
    HString(const char *str);
    void append(const std::string& value);
    
    std::string data() const; //
    
    void clear();
    void chop(hsizetype n);
    HString chopped(hsizetype len) const &;
    HString chopped(hsizetype len) &&;

    friend std::ostream& operator<<(std::ostream& os, const HString& hstr);
private:
    std::string m_data;
};

}

