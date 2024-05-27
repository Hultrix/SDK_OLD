#pragma once

#include "HApplication.h"
#include <iostream>
#include <vector>
#include "HString.h" // Assuming HString is a typedef for std::string

namespace Ht {

class HServerApplication : public HApplication {
public:
    HServerApplication();
    virtual ~HServerApplication();

protected:
    virtual void initializeApplication() override;
    virtual void uninitializeApplication() override;
    virtual void defineApplicationOptions() override;
    virtual int main(const std::vector<HString>& args) override;
};

} // namespace Ht

