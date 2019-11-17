# LIO - Simplified GPIO handling in C++

The purpose of this library is to simplify/unifiy GPIO pin handling in C++. Use this library to handle I/O pins unified, regardless from HW and OS. Hence you can implement platform and hw independent business logic.

# Compilation

Project uses CMake. To compile download and install CMake from https://cmake.org/download/. To create build files enter LIO and configure the project:
```
cmake ./CMakeLists.txt -Bbuild
cd build
cmake --build . -j
```
Compiler should support at least cpp14.
# Tests
Unit tests are witten with the help of [gtest/gmock](https://github.com/google/googletest) framework. You can enable them to set BUILD_TESTS cmake veriable.

# Linux
Two implementation are provided to use the library in user space in Linux environment. Legacy Sysfs and the new gpiolib. both of the implementation are located under ```./linux``` directory. If you need performance critical IO driving, you should consider to write a driver for your applcation and use new GPIOlib features. Kernel also provide various of functionalities (including debouncing) so it worths a try. This library and the implemetation of IO driving in linux tries to make easier taking the first step and simplify GPIO handling from user space.

# Example

Example was tested on Raspiabian 10 (buster). HW was a Raspberry Pi 4. The example SW generate 4s wavelength square wave on pin 20 and 16, and creates async linstener on pin 26 and 19. Output waveform
![image](https://drive.google.com/uc?export=view&id=1ZKiBaM_AWzEz-Xh1iYnUETskyw_uQUv4)
20, 26 pins are driven by sysfs, 16, 19 pins are driven buy gpiolib implementation.
![image](https://drive.google.com/uc?export=view&id=1nP0yvO1XOLX3UUR4O4zjKIAb8EN0DDy2)

If you pull up input pins to 3.3V or pull down to GND, std output should show that the event occurred. Sysfs implementation are attached to a SW implemented debouncer.

# Release notes
v2.0 are not backwards compatible to v1.0. Sorry about that.

## License

This project is licensed under the Appache 2.0 License - see the [LICENSE]
