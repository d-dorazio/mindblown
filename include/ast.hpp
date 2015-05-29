#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <vector>
#include <memory>

class State;

class Instruction {
public:
  virtual ~Instruction() = default;

  virtual State &eval(State &state) const = 0;
  virtual std::string to_string() const = 0;
};

using InstructionPtr = std::unique_ptr<Instruction>;
using Instructions = std::vector<InstructionPtr>;

class Plus : public Instruction {
public:
  virtual State &eval(State &state) const override;
  virtual std::string to_string() const override;
};

class Minus : public Instruction {
public:
  virtual State &eval(State &state) const override;
  virtual std::string to_string() const override;
};

class Forward : public Instruction {
public:
  virtual State &eval(State &state) const override;
  virtual std::string to_string() const override;
};

class Backward : public Instruction {
public:
  virtual State &eval(State &state) const override;
  virtual std::string to_string() const override;
};

class In : public Instruction {
public:
  explicit In(std::istream &is = std::cin);

  virtual State &eval(State &state) const override;
  virtual std::string to_string() const override;

private:
  std::istream &_is;
};

class Out : public Instruction {
public:
  explicit Out(std::ostream &os = std::cout);

  virtual State &eval(State &state) const override;
  virtual std::string to_string() const override;

private:
  std::ostream &_os;
};

// immutable
class Loop : public Instruction {
public:
  explicit Loop(Instructions sub);

  virtual State &eval(State &state) const override;
  virtual std::string to_string() const override;

  const Instructions sub;
};

#endif
