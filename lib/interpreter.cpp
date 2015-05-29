#include "../include/interpreter.hpp"

void interpret(const Instructions &ins) {
  State s;
  interpret(ins, s);
}

State &interpret(const Instructions &ins, State &st) {
  for (auto &i : ins) {
    st = i->eval(st);
  }
  return st;
}
