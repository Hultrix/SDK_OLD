#include "HTest.h"
#include "HObject.h"
#include "HString.h"

// Define the test cases within the Ht namespace
namespace Ht {

HT_TEST_CASE(SetAndGetObjectName) {
    // Create an instance of HObject
    HObject object;

    // Create an instance of HString and set its value
    HString name;
    name.append("MyObject");

    // Set the object name to the HString instance
    object.setObjectName(name);

    // Check if the object name is set correctly
    HT_CHECK_EQUAL(object.objectName(), "MyObject");
}

HT_TEST_CASE(SetAndGetObjectType) {
    // Create an instance of HObject
    HObject object;

    // Set the object type to HWindow
    object.setObjectType(HObjectType::HWindow);

    // Check if the object is of type window
    HT_CHECK(object.isWindowType());
}

} // namespace Ht

int main() {
    HTest::instance().run();
    return 0;
}

