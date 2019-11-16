cmake_minimum_required (VERSION 3.13)
find_package (Threads)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
FetchContent_Declare(
  boost-interprocess
  GIT_REPOSITORY https://github.com/boostorg/interprocess.git
  GIT_TAG        boost-1.71.0
)
FetchContent_MakeAvailable(boost-interprocess)


file(GLOB coreSRCs
    "./src/*.h"
    "./src/*.cpp"
)
add_library(LIOlib ${coreSRCs})
if(${Threads_FOUND})
    target_link_libraries(LIOlib Threads::Threads rt)
endif()
target_include_directories(LIOlib PUBLIC "./src")
target_link_libraries(LIOlib)
if(BUILD_TESTS)
    add_subdirectory(test)
endif()
