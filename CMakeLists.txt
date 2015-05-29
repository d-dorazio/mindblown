project(braincpp CXX)
cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)

include_directories(include)
add_subdirectory(lib)

add_executable(braincpp main.cpp)
set_property(TARGET braincpp PROPERTY CXX_STANDARD 11)
set_property(TARGET braincpp PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(braincpp PUBLIC libbraincpp)
