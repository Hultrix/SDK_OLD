cmake_minimum_required(VERSION 3.28)

# Set the project name
project(Hultrix)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(include/Core/ include/Gui/ include/Graphics2D/)

# Options to build each component
option(BUILD_CORE "Build Core library" ON)
option(BUILD_GRAPHICS2D "Build Graphics2D library" ON)
option(BUILD_GUI "Build Gui library" ON)
option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_CORE)
    add_library(Core 
        src/Core/HObject.cpp
        src/Core/HString.cpp
    )
endif()

if(BUILD_GRAPHICS2D)
    add_library(Graphics2D
        src/Graphics2D/HMargins.cpp
        src/Graphics2D/HRect.cpp
        src/Graphics2D/HSize.cpp
    )
endif()

if(BUILD_GUI)
    add_library(Gui
        src/Gui/HCursor.cpp
        src/Gui/HWindow.cpp
        #src/Gui/HLayout.cpp
        src/Gui/HMainWindow.cpp
    )
    target_link_libraries(Gui PRIVATE Core Graphics2D)
endif()

if(BUILD_TESTS)
    # Unit tests
    add_executable(test1 tests/test1/test1.cpp) # HObject
    target_link_libraries(test1 Core)

    add_executable(test2 tests/test2/test2.cpp) # HList(int)
    target_link_libraries(test2 Core)

    add_executable(test3 tests/test3/test3.cpp) # HList(HString)
    target_link_libraries(test3 Core)

    add_executable(test4 tests/test4/test4.cpp) # HWindow
    target_link_libraries(test4 Core Graphics2D Gui)

    add_executable(test5 tests/test5/test5.cpp)
    target_link_libraries(test5 Core)
endif()

