#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"
#include "state.h"

State *interpret_single(Instruction *ins, State *state);
State *interpret_all(InstructionArray *ins, State *state);

#endif // INTERPRETER_H
