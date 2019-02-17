cmake_minimum_required (VERSION 3.13)
find_package (Threads REQUIRED)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
file(GLOB mySRCs
    "./*.h"
    "./*.cpp"
)
list(REMOVE_ITEM mySRCs "example.cpp")

add_library(LIOlib ${mySRCs})
target_include_directories(LIOlib INTERFACE "./")
target_link_libraries(LIOlib Threads::Threads)
add_executable(Example "example.cpp")
target_link_libraries(Example LIOlib)
