#ifndef PARSER_HPP
#define PARSER_HPP

#include <algorithm>

#include "../include/ast.hpp"

auto default_err_call =
    [](const std::string &err) { std::cout << "Parse error: " << err; };

template <typename F = decltype(default_err_call)>
Instructions parse(const std::string &code, F errcal = default_err_call,
                   std::ostream & os = std::cout,
                   std::istream & is = std::cin) {
  std::vector<Instructions>
      loops; // a stack would be better, but move-semantics doen't work
  loops.emplace_back();

  for (const auto &token : code) {
    const auto idx = loops.size() - 1; // never gonna be < 0, otherwise bug

    if (token == '+') {
      loops[idx].emplace_back(new Plus());
    } else if (token == '-') {
      loops[idx].emplace_back(new Minus());
    } else if (token == '>') {
      loops[idx].emplace_back(new Forward());
    } else if (token == '<') {
      loops[idx].emplace_back(new Backward());
    } else if (token == ',') {
      loops[idx].emplace_back(new In(is));
    } else if (token == '.') {
      loops[idx].emplace_back(new Out(os));
    } else if (token == '[') {
      loops.emplace_back();
    } else if (token == ']') {

      if (loops.size() > 1) {
        Instructions sub;
        for (auto &ptr : loops[idx]) {
          sub.emplace_back(ptr.release());
        }
        loops.pop_back();
        loops[idx - 1].emplace_back(new Loop(std::move(sub)));
      } else {
        errcal("Mismatched brackets! Probably too many ] (or too few ])");
      }

    } else {
      // ignore other characters
    }
  }

  if (loops.size() != 1) {
    errcal("Mismatched brackets! Probably too many ] (or too few ])");
  }

  return std::move(loops[0]);
}

#endif
