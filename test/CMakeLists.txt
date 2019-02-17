cmake_minimum_required (VERSION 3.13)
add_subdirectory(googletest)
add_definitions(-std=c++14 -g -c -Wall)
file(GLOB testSRCs "./*.cpp" "./*.h")

add_library(EventHandledInputTest INTERFACE)
target_sources(EventHandledInputTest INTERFACE "EventHandledInput4Test.h")
target_include_directories(EventHandledInputTest INTERFACE "./")

add_executable(LIO_Test ${testSRCs})
target_link_libraries(LIO_Test gmock_main LIOlib)
