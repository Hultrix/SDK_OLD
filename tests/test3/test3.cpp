#include <iostream>
#include "HList.h"
#include "HString.h"

int main() {
    Ht::HList<Ht::HString> myList;

    // Add some elements to the list
    myList.push_back("one");
    myList.push_front("zero");
    myList.push_back("two");
    myList.prepend("three");

    // Iterate and print the elements using a range-based for loop
    for (const auto& item : myList) {
        std::cout << item.data() << " ";
    }

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

