#include "HEnvironment.h"
#include <iostream>

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

