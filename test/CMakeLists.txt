cmake_minimum_required (VERSION 3.14)
add_definitions(-std=c++14 -g -c -Wall)
include(FetchContent)
include(GoogleTest)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.1
)
FetchContent_MakeAvailable(googletest)

file(GLOB testSRCs "./*.cpp" "./*.h")

add_library(EventHandledInputTest INTERFACE)
target_sources(EventHandledInputTest INTERFACE "EventHandledInput4Test.h")
target_include_directories(EventHandledInputTest INTERFACE "./")

add_executable(LIO_Test ${testSRCs})
target_link_libraries(LIO_Test gmock_main LIOlib)
gtest_discover_tests(LIO_Test)

