# LIO - Simplified GPIO handling in Linux

The purpose of this library is to simplify handling GPIO ports via Linux sysfs from C++ code.

# Compilation

Project uses CMake. To compile download and install CMake from https://cmake.org/download/. To create build files enter LIO and configure the project:
```
cmake ./CMakeLists.txt -Bbuild
cd build
cmake --build .
```
Compiler should support at least cpp11. You can ignore test build if you comment out(# at the beginning of the line) the followig line in the main CMakeList.txt 
```
add_subdirectory(test)
```
# Example

The sw tested on raspberry pi zero w, and the example code contains the pin nuber of this board (https://cdn.sparkfun.com/assets/learn_tutorials/6/7/6/PiZero_1.pdf). However you can use the code on any hardware that runs a linux that support sysfs.

Example inializes an output port (14), an asyn input port (2) and a sync input port(3). During every iteration the output port changes its state and wait 2 seconds to detect sync input change. Beside that there is an other thread that watches the async input and executes the proper function if the input changes. Both inputs are pulled up on this board, so you need to pull down them to GND to see input change.
Every change (both inputs and output) are logged to the standard output.

## License

This project is licensed under the Appache 2.0 License - see the [LICENSE]
