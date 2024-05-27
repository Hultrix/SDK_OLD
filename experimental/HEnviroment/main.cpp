#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <sys/utsname.h>
#include <algorithm>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <cstdlib>

namespace Ht {

class HEnvironment {
public:
    std::string osName() const {
        return getOsReleaseInfo("NAME");
    }

    std::string osVersion() const {
        return getOsReleaseInfo("VERSION");
    }

    std::string osArchitecture() const {
        struct utsname buffer;
        if (uname(&buffer) != 0) {
            perror("uname");
            return "Unknown";
        }
        return std::string(buffer.machine);
    }

    std::string currentUser() const {
        const char* username = std::getenv("USER");
        if (username == nullptr) {
            struct passwd* pw = getpwuid(getuid());
            if (pw) {
                return std::string(pw->pw_name);
            } else {
                perror("getpwuid");
                return "Unknown";
            }
        }
        return std::string(username);
    }

    std::string homeDir() const {
        const char* homedir = std::getenv("HOME");
        if (homedir == nullptr) {
            struct passwd* pw = getpwuid(getuid());
            if (pw) {
                return std::string(pw->pw_dir);
            } else {
                perror("getpwuid");
                return "Unknown";
            }
        }
        return std::string(homedir);
    }

    std::string shell() const {
        const char* shell = std::getenv("SHELL");
        if (shell == nullptr) {
            struct passwd* pw = getpwuid(getuid());
            if (pw) {
                return std::string(pw->pw_shell);
            } else {
                perror("getpwuid");
                return "Unknown";
            }
        }
        return std::string(shell);
    }

private:
    std::string getOsReleaseInfo(const std::string& key) const {
        std::ifstream file("/etc/os-release");
        if (!file.is_open()) {
            return "Unknown";
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.find(key) == 0) {
                auto pos = line.find('=');
                if (pos != std::string::npos) {
                    std::string value = line.substr(pos + 1);
                    // Remove any surrounding quotes
                    value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());
                    return value;
                }
            }
        }

        return "Unknown";
    }
};

} // namespace Ht

int main() {
    Ht::HEnvironment env;
    std::cout << "OS Name: " << env.osName() << std::endl;
    std::cout << "OS Version: " << env.osVersion() << std::endl;
    std::cout << "OS Architecture: " << env.osArchitecture() << std::endl;
    std::cout << "Current User: " << env.currentUser() << std::endl;
    std::cout << "Home Directory: " << env.homeDir() << std::endl;
    std::cout << "Shell: " << env.shell() << std::endl;
    return 0;
}

