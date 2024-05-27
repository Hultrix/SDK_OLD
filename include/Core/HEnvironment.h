#pragma once
#include "HString.h"

namespace Ht {

class HEnvironment {
public:
    HString osName() const;
    HString osVersion() const;
    HString osArchitecture() const;
    HString currentUser() const;
    HString homeDir() const;
    HString shell() const;

private:
    HString getOsReleaseInfo(const HString& key) const;
};

} // namespace Ht

