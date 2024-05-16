#include "HObject.h"
#include "HString.h"
#include <iostream>

int main() {
    Ht::HObject object;
    Ht::HString name;
    name.append("MyObject");
    object.setObjectName(name);
    std::cout << "Object name: " << object.objectName().data() << std::endl;
    
    object.setObjectType(Ht::HObjectType::HWindow);
    
    std::cout << "Object type: " << object.isWindowType() << std::endl;
    
    return 0;
}

