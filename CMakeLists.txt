cmake_minimum_required(VERSION 3.28)

# Set the project name
project(Hultrix C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add include directories
include_directories(include/Core/ include/Gui/ include/Graphics2D/ thirdparty/include)

# Find and link Boost libraries
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# Specify the paths to the Boost libraries and includes
set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/thirdparty)
set(BOOST_LIBRARYDIR ${CMAKE_SOURCE_DIR}/thirdparty/lib)

find_package(Boost 1.85.0 REQUIRED COMPONENTS system filesystem date_time thread unit_test_framework)

# Find and link Poco libraries
#set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/thirdparty)
#find_package(Poco REQUIRED COMPONENTS Foundation Util)

# Options to build each component
option(BUILD_CORE "Build Core library" ON)
option(BUILD_GRAPHICS2D "Build Graphics2D library" ON)
option(BUILD_GUI "Build Gui library" ON)
option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_CORE)
    add_library(Core
        src/Core/HApplication.cpp
        src/Core/HObject.cpp
        src/Core/HString.cpp
        src/Core/HProcessManager.cpp
        src/Core/HSharedMemory.cpp
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
    
    add_executable(test6 tests/test6/test6.cpp)
    target_link_libraries(test6 Core)

    add_executable(test7 tests/test7/test7.cpp)
    target_link_libraries(test7 Core Boost::system Boost::filesystem Boost::date_time Boost::thread)
    
    add_executable(test8 tests/test8/test8.cpp)
    target_link_libraries(test8 Core)
    
    add_executable(test9 tests/test9/test9.cpp)
    target_link_libraries(test9 Core)
    
    add_executable(test10 tests/test10/test10.cpp)
    target_link_libraries(test10 Core)
endif()

