# CMake Tutorial
This tutorial contains step-by-step how to setup CMake on your
C++ project.


## Install CMake
First of all, you need to install `cmake`. 

On Ubuntu:

    sudo apt-get install cmake

On macOS:

    brew install cmake

Make sure the `cmake` is installed correctly:

    % cmake --version
    cmake version 3.10.2

    CMake suite maintained and supported by Kitware (kitware.com/cmake).


## Compiling & Linking
We can build this project using the following command: 

    c++ src/main.cc src/math.cc -o cmake-tutorial

Or we can do the compile and linking on the separate steps

    c++ -c src/math.cc -o math.o 
    c++ src/main.cc math.o -o cmake-tutorial 


## Using Makefile
We can automate the step to compile and link above using `Makefile`.
First we need to write a `Makefile` with the following content:

    math.o: src/math.cc src/math.h
        c++ -c src/math.cc -o math.o

    cmake-tutorial: math.o
        c++ src/main.cc math.o -o cmake-tutorial

    build: cmake-tutorial

Now we can run:

    make build

to build `cmake-tutorial` binary. If there are no changes in `src/{main,math}.c` and
`src/math.h`, the subsequent command will do nothing:

    % make build
    make: Nothing to be done for `build'.

this is usefull when working on larger project, we only compile the object that changes.


## Using CMake
Now we know how to perform compiling and linking using the `C++` and
`make` command. Now we can use `cmake` to do all of this for us.

Create new `CMakeLists.txt` with the following content:
    
    cmake_minimum_required (VERSION 3.10)

    # Define the project
    project(cmake-tutorial)

    # Add definition for math library
    add_library(math src/math.cc)

    # Add definition for the cmake-tutorial binary
    add_executable(cmake-tutorial src/main.cc)
    target_link_libraries(cmake-tutorial math)

We can generate the `Makefile` based on the definition above using the following
command:

    cmake .

Now we can run `make cmake-tutorial` to build the binary.

    % make cmake-tutorial
    Scanning dependencies of target math
    [ 25%] Building CXX object CMakeFiles/math.dir/src/math.cc.o
    [ 50%] Linking CXX static library libmath.a
    [ 50%] Built target math
    Scanning dependencies of target cmake-tutorial
    [ 75%] Building CXX object CMakeFiles/cmake-tutorial.dir/src/main.cc.o
    [100%] Linking CXX executable cmake-tutorial
    [100%] Built target cmake-tutorial





