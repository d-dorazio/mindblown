include_directories(../include)
set(SRC_LIST ../include/ast.hpp ast.cpp ../include/state.hpp state.cpp ../include/interpreter.hpp
        interpreter.cpp ../include/parser.hpp)

add_library(libbraincpp ${SRC_LIST})
set_property(TARGET libbraincpp PROPERTY CXX_STANDARD 11)
set_property(TARGET libbraincpp PROPERTY CXX_STANDARD_REQUIRED ON)
