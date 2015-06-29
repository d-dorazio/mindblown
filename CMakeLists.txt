project(brainc C)
cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)

file(GLOB BRAINC_SRC *.c)

file(GLOB INCLUDE_SRC include/*.h)

include_directories(include)
add_subdirectory(lib)

add_executable(brainc ${BRAINC_SRC} ${INCLUDE_SRC})
target_link_libraries(brainc PUBLIC libbrainc)

set_property(TARGET brainc PROPERTY C_STANDARD 99)
set_property(TARGET brainc PROPERTY C_STANDARD_REQUIRED ON)
