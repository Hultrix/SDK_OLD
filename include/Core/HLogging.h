#pragma once

#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>
#include "HString.h"

namespace Ht {

class HLogging {
public:
    enum class Severity {
        INFO,
        WARNING,
        ERROR
    };

    HLogging(const HString& logFile);
    ~HLogging();

    void log(Severity severity, const HString& message);
    void setSeverity(Severity severity);

private:
    std::ofstream m_logStream;
    Severity m_severity;

    HString getCurrentTime() const;
    HString severityToString(Severity severity) const;
};

} // namespace Ht

