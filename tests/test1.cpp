#include "HObject.h"
#include "HString.h"
#include <iostream>

int main() {
    // Create an instance of HObject
    Ht::HObject object;
    
    // Create an instance of HString and set its value
    Ht::HString name;
    name.append("MyObject");
    
    // Set the object name to the HString instance
    object.setObjectName(name);
    
    // Output the object's name
    std::cout << "Object name: " << object.objectName().data() << std::endl;
    
    // Set the object type to HWindow
    object.setObjectType(Ht::HObjectType::HWindow);
    
    // Output whether the object is of type window
    std::cout << "Object type: " << object.isWindowType() << std::endl;
    
    return 0;
}


