#include "../include/state.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

State *state_new() {
  State *state = (State *)malloc(sizeof(State));

  if (state) {
    state->cells = (uint8_t *)calloc(CELLS_NUMBER, sizeof(uint8_t));
    state->idx = 0;
  }

  return state;
}

void state_free(State *state) {
  if (state) {
    free(state->cells);
    free(state);
  }
}

State *state_plus(State *state) {
  assert(state && "state must not be null");
  ++state->cells[state->idx];
  return state;
}

State *state_minus(State *state) {
  assert(state && "state must not be null");
  --state->cells[state->idx];
  return state;
}

State *state_forward(State *state) {
  assert(state && "state must not be null");
  assert(state->idx < CELLS_NUMBER && "sorry little memory");
  ++state->idx;
  return state;
}

State *state_backward(State *state) {
  assert(state && "state must not be null");
  assert(state->idx >= 0 && "sorry, you' re dum");
  --state->idx;
  return state;
}

State *state_in(State *state) {
  assert(state && "state must not be null");
  state->cells[state->idx] = getchar();
  while (getchar() != '\n') {
    // eat line
  }
  return state;
}

State *state_out(State *state) {
  assert(state && "state must not be null");
  putchar(state->cells[state->idx]);
  fflush(stdout);
  return state;
}
