cmake_minimum_required (VERSION 3.13)
find_package (Threads)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_link_options("-latomic")

add_executable(Example "example.cpp")
target_link_libraries(Example LIOLinuxlib)
install(TARGETS Example DESTINATION "~/Example")
