#include <iostream>
#include "HFile.h"
#include "HString.h"

int main() {
    Ht::HFile file(Ht::HString("example.txt"));

    if (!file.exists()) {
        std::cout << "File does not exist. Creating and writing to file." << std::endl;
        file.write(Ht::HString("Hello, world!"));
    }

    Ht::HString content = file.read();
    std::cout << "File content: " << content << std::endl;

    return 0;
}

