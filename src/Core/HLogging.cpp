#include "HLogging.h"

namespace Ht {

HLogging::HLogging(const HString& logFile) : m_severity(Severity::INFO) {
    m_logStream.open(logFile.c_str(), std::ios::app);
    if (!m_logStream.is_open()) {
        throw std::runtime_error("Could not open log file: " + std::string(logFile.c_str()));
    }
}

HLogging::~HLogging() {
    if (m_logStream.is_open()) {
        m_logStream.close();
    }
}

void HLogging::log(Severity severity, const HString& message) {
    if (severity < m_severity) {
        return;
    }

    m_logStream << getCurrentTime().c_str() << " [" << severityToString(severity).c_str() << "] " << message.c_str() << std::endl;
    m_logStream.flush();
}

void HLogging::setSeverity(Severity severity) {
    m_severity = severity;
}

HString HLogging::getCurrentTime() const {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    std::ostringstream oss;
    oss << (localTime->tm_year + 1900) << '-'
        << (localTime->tm_mon + 1) << '-'
        << localTime->tm_mday << ' '
        << localTime->tm_hour << ':'
        << localTime->tm_min << ':'
        << localTime->tm_sec;
    return HString(oss.str().c_str());
}

HString HLogging::severityToString(Severity severity) const {
    switch (severity) {
        case Severity::INFO: return "INFO";
        case Severity::WARNING: return "WARNING";
        case Severity::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

} // namespace Ht

