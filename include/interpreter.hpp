#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "state.hpp"

void interpret(const Instructions &ins);
State &interpret(const Instructions &ins, State &st);

#endif
