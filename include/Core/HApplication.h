#pragma once

#include "HObject.h"
#include "HString.h"
#include <vector>
#include <iostream>

namespace Ht {

class HApplication : public HObject {
public:
    HApplication();
    virtual ~HApplication();

    void initialize();
    void uninitialize();
    void defineOptions();
    void handleHelp(const HString& name, const HString& value);
    void displayHelp();
    int run(int argc, char** argv);

protected:
    virtual void initializeApplication();
    virtual void uninitializeApplication();
    virtual void defineApplicationOptions();
    virtual int main(const std::vector<HString>& args);

private:
    bool m_helpRequested = false;
    std::vector<HString> m_options;
};

} // namespace Ht

