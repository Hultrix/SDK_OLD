#include <iostream>
#include "HList.h"

int main() {
    Ht::HList<int> myList;

    // Add some elements to the list
    myList.push_back(1);
    myList.push_front(0);
    myList.push_back(2);
    myList.prepend(-1);

    // Iterate and print the elements
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Print size of the list
    std::cout << "Size: " << myList.size() << std::endl;

    // Check if the list is empty
    std::cout << "Is empty: " << std::boolalpha << myList.empty() << std::endl;

    // Remove the last and first elements and print the size
    myList.pop_back();
    myList.pop_front();
    std::cout << "Size after pop_back and pop_front: " << myList.size() << std::endl;

    return 0;
}

