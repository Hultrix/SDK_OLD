#include <iostream>
#include "HDir.h"
#include "HString.h"

int main() {
    Ht::HDir dir(Ht::HString("example_dir"));

    if (!dir.exists()) {
        std::cout << "Directory does not exist. Creating directory." << std::endl;
        dir.create();
    }

    std::cout << "Listing files in directory:" << std::endl;
    std::vector<Ht::HString> files = dir.listFiles();
    for (const auto& file : files) {
        std::cout << file << std::endl;
    }

    // Uncomment to remove the directory
    // dir.remove();
    
    return 0;
}

