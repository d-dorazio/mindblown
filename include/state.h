#ifndef STATE__H
#define STATE__H

#ifndef CELLS_NUMBER
#define CELLS_NUMBER 4096
#endif

#include <stdint.h>
#include <stddef.h>

typedef struct State {
  uint8_t *cells;
  size_t idx;
} State;

State *state_new();
void state_free(State *state);

State *state_plus(State *state);
State *state_minus(State *state);
State *state_forward(State *state);
State *state_backward(State *state);
State *state_in(State *state);
State *state_out(State *state);

#endif // STATE__H
