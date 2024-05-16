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
# HObject test
add_executable(Test1 tests/test1.cpp)
target_link_libraries(Test1  core)

# HList using int
add_executable(Test2 tests/test2.cpp)
target_link_libraries(Test2  core)

# HList using HString
add_executable(Test3 tests/test3.cpp)
target_link_libraries(Test3  core)
