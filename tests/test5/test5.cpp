#include "HString.h"
#include <iostream>

int main() {
    Ht::HString myString("Hello, world!");

    std::cout << "Original: " << myString << std::endl;

    myString.chop(6);
    std::cout << "After chop(6): " << myString << std::endl;

    Ht::HString choppedString = myString.chopped(2);
    std::cout << "After chopped(2): " << choppedString << std::endl;

    myString.clear();
    std::cout << "After clear: " << myString << std::endl;

    return 0;
}

