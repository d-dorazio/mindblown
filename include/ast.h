#ifndef AST_H
#define AST_H

#include <stddef.h>

typedef struct InstructionArray InstructionArray; // fwd

typedef enum Type { Plus, Minus, ShiftR, ShiftL, Out, In, Loop } Type;

typedef struct Instruction {
  Type type;
  InstructionArray *inner; // inner instructions of a loop
} Instruction;

Instruction instruction_new(Type t, InstructionArray *inner);
void instruction_free(Instruction *ins);

void instruction_print(Instruction *ins);

typedef struct InstructionArray {
  Instruction *data;
  size_t capacity;
  size_t size;
} InstructionArray;

#define instructionarray_foreach(L, N) \
  Instruction *N = NULL; \
  for (size_t i = 0; i < L->size; N = &L->data[i], ++i)

InstructionArray *instructionarray_new();
void instructionarray_free(InstructionArray *ins);

InstructionArray *instructionarray_add(InstructionArray *arr, Instruction i);

#endif // AST_H
