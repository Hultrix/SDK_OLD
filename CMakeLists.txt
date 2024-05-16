cmake_minimum_required(VERSION 3.28)

# Set the project name
project(Hultrix)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(include/core/)

# Add the ProcessManager.cpp file to a library
add_library(core 
    src/core/HObject.cpp
    src/core/HString.cpp
    )

# Unit tests
add_executable(Test1 tests/test1.cpp)
target_link_libraries(Test1  core)

