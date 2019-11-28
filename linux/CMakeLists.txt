cmake_minimum_required (VERSION 3.13)
find_package (Threads)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
file(GLOB LinuxSRCs 
    "*.h"
    "*.cpp"
)

add_library(LIOLinuxlib ${LinuxSRCs})
target_link_libraries(LIOLinuxlib LIOlib)
target_include_directories(LIOlib PUBLIC ".")
