cmake_minimum_required (VERSION 3.13)
project(LIOEsp32lib)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_link_options("-latomic")
file(GLOB ESP32srcs
    "*.h"
    "*.cpp"
)

add_library(LIOEsp32lib ${ESP32srcs})

target_link_libraries(LIOEsp32lib LIOlib )
target_include_directories(LIOEsp32lib PUBLIC ".")
