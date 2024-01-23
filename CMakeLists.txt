cmake_minimum_required (VERSION 3.10)

# Define the project
project(cmake-tutorial)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

# Add definition for math library
add_library(math src/math.cc)


# Add definition for the cmake-tutorial binary
add_executable(cmake-tutorial src/main.cc)
target_link_libraries(cmake-tutorial math)


# Third-party library
include(ExternalProject)
ExternalProject_Add(googletest
    PREFIX "${CMAKE_BINARY_DIR}/lib"
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG "main"
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/installed
)


# Prevent build on all targets build
set_target_properties(googletest PROPERTIES EXCLUDE_FROM_ALL TRUE)


# Define ${CMAKE_INSTALL_...} variables
include(GNUInstallDirs)


# Specify where third-party libraries are located
link_directories(${CMAKE_BINARY_DIR}/lib/installed/${CMAKE_INSTALL_LIBDIR})
include_directories(${CMAKE_BINARY_DIR}/lib/installed/${CMAKE_INSTALL_INCLUDEDIR})


# This is required for googletest
find_package(Threads REQUIRED)


# CMakeLists.txt

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# Add test executable
add_executable(math_test test/math_test.cc)

# Link the testexecutable with the google Test andpthread library
target_link_libraries(math_test ${GTEST_BOTH_LIBRARIES}


