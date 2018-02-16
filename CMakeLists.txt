cmake_minimum_required (VERSION 3.10)

# Define the project
project(cmake-tutorial)

# Add definition for math library
add_library(math src/math.cc)

# Add definition for the cmake-tutorial binary
add_executable(cmake-tutorial src/main.cc)
target_link_libraries(cmake-tutorial math)
