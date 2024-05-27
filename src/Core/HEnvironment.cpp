#include "HEnvironment.h"
#include <fstream>
#include <sstream>
#include <sys/utsname.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <cstdlib>
#include <algorithm>

namespace Ht {

HString HEnvironment::osName() const {
    return getOsReleaseInfo("NAME");
}

HString HEnvironment::osVersion() const {
    return getOsReleaseInfo("VERSION");
}

HString HEnvironment::osArchitecture() const {
    struct utsname buffer;
    if (uname(&buffer) != 0) {
        perror("uname");
        return "Unknown";
    }
    return buffer.machine;
}

HString HEnvironment::currentUser() const {
    const char* username = std::getenv("USER");
    if (username == nullptr) {
        struct passwd* pw = getpwuid(getuid());
        if (pw) {
            return pw->pw_name;
        } else {
            perror("getpwuid");
            return "Unknown";
        }
    }
    return username;
}

HString HEnvironment::homeDir() const {
    const char* homedir = std::getenv("HOME");
    if (homedir == nullptr) {
        struct passwd* pw = getpwuid(getuid());
        if (pw) {
            return pw->pw_dir;
        } else {
            perror("getpwuid");
            return "Unknown";
        }
    }
    return homedir;
}

HString HEnvironment::shell() const {
    const char* shell = std::getenv("SHELL");
    if (shell == nullptr) {
        struct passwd* pw = getpwuid(getuid());
        if (pw) {
            return pw->pw_shell;
        } else {
            perror("getpwuid");
            return "Unknown";
        }
    }
    return shell;
}

HString HEnvironment::getOsReleaseInfo(const HString& key) const {
    std::ifstream file("/etc/os-release");
    if (!file.is_open()) {
        return "Unknown";
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find(key.data()) == 0) {
            auto pos = line.find('=');
            if (pos != std::string::npos) {
                std::string value = line.substr(pos + 1);
                // Remove any surrounding quotes
                value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());
                return HString(value.c_str());
            }
        }
    }

    return "Unknown";
}

} // namespace Ht

