#include <iostream>
#include <fstream>

#include "../include/parser.hpp"
#include "../include/interpreter.hpp"

void interpret_cli();
void interpret_file(const std::string &filename);

int main(int argc, char *argv[]) {
  if (argc == 1) {
    interpret_cli();
  } else {
    for (int i = 1; i < argc; ++i) {
      interpret_file(argv[i]);
    }
  }

  return 0;
}

void interpret_cli() {
  State state;
  std::string line;

  while (true) {
    std::cout << "> ";

    std::getline(std::cin, line);

    if (line == "quit")
      break;

    if (line.back() != '\\') {
      state = interpret(parse(line), state);
    }
  }
}

void interpret_file(const std::string &filename) {
  std::ifstream is;
  is.open(filename);
  if (is.is_open()) {

    std::string code;

    while (is) {
      std::string line;

      std::getline(is, line);

      code += line;
    }
    State state;
    interpret(parse(code), state);
  } else {
    std::cout << "Unable to open " << filename << std::endl;
  }
}
