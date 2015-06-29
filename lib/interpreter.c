#include "../include/interpreter.h"

#include <assert.h>
#include <stdio.h>

State *interpret_single(Instruction *ins, State *state) {
  assert(ins && state && "all args must be not null");
  switch (ins->type) {
  case Plus:
    state_plus(state);
    break;
  case Minus:
    state_minus(state);
    break;
  case ShiftR:
    state_forward(state);
    break;
  case ShiftL:
    state_backward(state);
    break;
  case Out:
    state_out(state);
    break;
  case In:
    state_in(state);
    break;
  case Loop: {
    if (ins->inner) {
      while (state->cells[state->idx] != 0) {
        interpret_all(ins->inner, state);
      }
    }
    break;
  }
  default:
    break;
  }
  return state;
}

State *interpret_all(InstructionArray *ins, State *state) {
  assert(ins && state && "all args must be not null");
  for (size_t i = 0; i < ins->size; ++i) {
    interpret_single(&ins->data[i], state);
  }
  return state;
}
