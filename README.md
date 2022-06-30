# CMake Tutorial

This tutorial cover the following:

1. Build the project using simple `c++(1)` and `make(1)`.
2. Build the project using `cmake(1)`.
3. Build the project using `cmake(1)` with third party library.

In this tutorial we will use the following project structure:

```
cmake-tutorial/
├── CMakeLists.txt
├── README.md
├── src
│   ├── main.cc
│   ├── math.cc
│   └── math.h
└── test
    └── math_test.cc
```

Directory structure:

- `src` : Directory for source code.
- `test` : Directory for test.

`src/main.cc` is our main executable and `src/math.{cc,h}` is an internal library that used by `src/main.cc`.

We will start from the basic on how to build the project using `c++(1)` only
and a simple `Makefile`. Then we define the build in `CMakeLists.txt` and
using `cmake(1)` to generate complex `Makefile` for us.


## Install CMake

First of all, you need to install `cmake`. 

On Ubuntu:

```
sudo apt-get install cmake
```

On macOS:

```
brew install cmake
```

Make sure the `cmake` is installed correctly:

```
% cmake --version
cmake version 3.10.2

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

## Compiling & Linking

We can build this project using the following command: 

```
c++ src/main.cc src/math.cc -o cmake-tutorial
```

Or we can do the compile and linking on the separate steps

```
c++ -c src/math.cc -o math.o 
c++ src/main.cc math.o -o cmake-tutorial
```

## Using Makefile

We can automate the step to compile and link above using `Makefile`.
First we need to create new `Makefile` in the root directory with the following content:

```makefile
# Add definition to generate math.o object file
math.o: src/math.cc src/math.h
    c++ -c src/math.cc -o math.o

# Add definition to generate cmake-tutorial binary
cmake-tutorial: math.o
    c++ src/main.cc math.o -o cmake-tutorial
```

Now we can run:

```
make cmake-tutorial
```

to build `cmake-tutorial` binary. If there are no changes in `src/{main,math}.cc` and `src/math.h`,
the subsequent command will do nothing:

```
% make cmake-tutorial
make: Nothing to be done for `cmake-tutorial'.
```

this is useful when working on larger project, we only compile the object that changes.

## Using CMake

Now we know how to perform compiling and linking using the `C++` and `make` command.
Now we can use `cmake` to do all of this for us.

Create new `CMakeLists.txt` with the following content:

```cmake
cmake_minimum_required (VERSION 3.10)

# Define the project
project(cmake-tutorial)

# Add definition for math library
add_library(math src/math.cc)

# Add definition for the cmake-tutorial binary
add_executable(cmake-tutorial src/main.cc)
target_link_libraries(cmake-tutorial math)
```

We can generate the `Makefile` based on the definition above using the following command:

```
cmake .
```

Or create a `build` directory to store the generated files by CMake:

```
mkdir build
cd build/
cmake ..
```

Now we can run `make cmake-tutorial` to build the binary.

```
% make cmake-tutorial
Scanning dependencies of target math
[ 25%] Building CXX object CMakeFiles/math.dir/src/math.cc.o
[ 50%] Linking CXX static library libmath.a
[ 50%] Built target math
Scanning dependencies of target cmake-tutorial
[ 75%] Building CXX object CMakeFiles/cmake-tutorial.dir/src/main.cc.o
[100%] Linking CXX executable cmake-tutorial
[100%] Built target cmake-tutorial
```

Or we can use the CMake directly via:

```
cmake --build . --target cmake-tutorial
```

## Using CMake with 3rd-party library

Suppose that we want to write a unit test for `math::add(a, b)`.
We will use a [googletest](https://github.com/google/googletest) library to create and run the unit test.

Add the following definition to `CMakeLists.txt`:

```cmake
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

# Test
add_executable(math_test test/math_test.cc)
target_link_libraries(math_test math gtest Threads::Threads)
# Make sure third-party is built before executable
add_dependencies(math_test googletest)
set_target_properties(math_test PROPERTIES EXCLUDE_FROM_ALL TRUE)
```

Re-generate the build files using the following command:

```
cd build/
cmake ..
```

Build the unit test:

```
cmake --build . --target math_test
```

Run the test:

```
% ./math_test 
[==========] Running 6 tests from 3 test cases.
[----------] Global test environment set-up.
[----------] 2 tests from MathAddTest
[ RUN      ] MathAddTest.PositiveNum
[       OK ] MathAddTest.PositiveNum (0 ms)
[ RUN      ] MathAddTest.ZeroB
[       OK ] MathAddTest.ZeroB (0 ms)
[----------] 2 tests from MathAddTest (0 ms total)

[----------] 2 tests from MathSubTest
[ RUN      ] MathSubTest.PositiveNum
[       OK ] MathSubTest.PositiveNum (0 ms)
[ RUN      ] MathSubTest.ZeroB
[       OK ] MathSubTest.ZeroB (0 ms)
[----------] 2 tests from MathSubTest (0 ms total)

[----------] 2 tests from MathMulTest
[ RUN      ] MathMulTest.PositiveNum
[       OK ] MathMulTest.PositiveNum (0 ms)
[ RUN      ] MathMulTest.ZeroB
[       OK ] MathMulTest.ZeroB (0 ms)
[----------] 2 tests from MathMulTest (0 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 3 test cases ran. (0 ms total)
[  PASSED  ] 6 tests.
```

Done.


### IDE Support

If you are using `CLion`, the google test will automatically detected.

![CLion](https://s9.postimg.org/ugqkdw6nh/Screen_Shot_2018-02-16_at_21.03.10.png)

Visual studio also support cmake
