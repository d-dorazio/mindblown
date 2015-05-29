#include "../include/ast.hpp"
#include "../include/state.hpp"

#include <algorithm>

State &Plus::eval(State &state) const {
  state.add1();
  return state;
}

std::string Plus::to_string() const { return "+"; }

State &Minus::eval(State &state) const {
  state.sub1();
  return state;
}

std::string Minus::to_string() const { return "-"; }

State &Forward::eval(State &state) const {
  state.forward();
  return state;
}

std::string Forward::to_string() const { return ">"; }

State &Backward::eval(State &state) const {
  state.backward();
  return state;
}

std::string Backward::to_string() const { return "<"; }

In::In(std::istream &is) : Instruction(), _is(is) {}

State &In::eval(State &state) const {
  state.in();
  return state;
}

std::string In::to_string() const { return ","; }

Out::Out(std::ostream &os) : Instruction(), _os(os) {}

State &Out::eval(State &state) const {
  state.out();
  return state;
}

std::string Out::to_string() const { return "."; }

Loop::Loop(Instructions sub) : Instruction(), sub(std::move(sub)) {}

State &Loop::eval(State &state) const {
  while (state.cur() != 0) {
    for (auto &ins : sub) {
      state = ins->eval(state);
    }
  }
  return state;
}

std::string Loop::to_string() const {
  return std::accumulate(std::begin(sub), std::end(sub), std::string("["),
                         [](const std::string &acc, const InstructionPtr &i) {
           return acc + i->to_string();
         }) +
         "]";
}
