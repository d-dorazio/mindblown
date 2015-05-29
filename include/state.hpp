#ifndef STATE_HPP
#define STATE_HPP

#include <iostream>
#include <forward_list>

#include "ast.hpp"

class State {
public:
  using Cell = uint8_t;
  using Cells = std::forward_list<Cell>;

  Cell cur() const;

  void add1();
  void sub1();
  void forward();
  void backward();
  void in(std::istream &stream = std::cin);
  void out(std::ostream &stream = std::cout);

private:
  Cells _left_cells; // reverse order for O(1) insertion and deletion
  Cell _cur = 0;
  Cells _right_cells;
};

#endif
