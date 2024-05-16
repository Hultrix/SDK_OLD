cmake_minimum_required(VERSION 3.28)

# Set the project name
project(Hultrix)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(include/Core/ include/Gui/ include/Graphics2D/)

# Add the ProcessManager.cpp file to a library
add_library(Core 
    src/Core/HObject.cpp
    src/Core/HString.cpp
    src/Core/HSize.cpp
    )

add_library(Graphics2D
    src/Graphics2D/HMargins.cpp
    src/Graphics2D/HRect.cpp
    )

add_library(Gui
    src/Gui/HCursor.cpp
    src/Gui/HWindow.cpp
    )
# Unit tests
# HObject test
add_executable(test1 tests/test1.cpp)
target_link_libraries(test1  Core)

# HList using int
add_executable(test2 tests/test2.cpp)
target_link_libraries(test2  Core)

# HList using HString
add_executable(test3 tests/test3.cpp)
target_link_libraries(test3  Core)

# HList using HString
add_executable(test4 tests/test4.cpp)
target_link_libraries(test4 Core Graphics2D Gui)
