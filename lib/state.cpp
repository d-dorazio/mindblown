#include "../include/state.hpp"

State::Cell State::cur() const { return _cur; }

void State::add1() { _cur += 1; }

void State::sub1() { _cur -= 1; }

void State::forward() {
  _left_cells.push_front(_cur);
  _cur = 0;
  if (!_right_cells.empty()) {
    _cur = _right_cells.front();
    _right_cells.pop_front();
  }
}

void State::backward() {
  _right_cells.push_front(_cur);
  if (!_left_cells.empty()) {
    _cur = _left_cells.front();
    _left_cells.pop_front();
  }
}

void State::in(std::istream &stream) {
  std::string line;
  while (line.empty()) {
    std::getline(stream, line);
  }
  _cur = line[0];
}

void State::out(std::ostream &stream) { stream << _cur; }
