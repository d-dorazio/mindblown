#include "../include/ast.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

Instruction instruction_new(Type t, InstructionArray *arr) {
  Instruction ins;
  ins.type = t;
  ins.inner = arr;
  return ins;
}

void instruction_free(Instruction *ins) {
  assert(ins && "ins must not be null");
  if (ins->inner)
    instructionarray_free(ins->inner);
}

void instruction_print(Instruction *ins) {
  assert(ins && "ins must not be null");
  if (ins->type != Loop) {
    char c;
    switch (ins->type) {
    case Plus:
      c = '+';
      break;
    case Minus:
      c = '-';
      break;
    case ShiftR:
      c = '>';
      break;
    case ShiftL:
      c = '<';
      break;
    case Out:
      c = '.';
      break;
    case In:
      c = ',';
      break;
    default:
      c = '\0';
    };
    printf("%c", c);
    return;
  }

  printf("[");
  if (ins->inner) {
    for (size_t i = 0; i < ins->inner->size; ++i) {
      instruction_print(&ins->inner->data[i]);
    }
  }
  printf("]");
}

InstructionArray *instructionarray_new() {
  InstructionArray *arr = (InstructionArray *)malloc(sizeof(InstructionArray));
  arr->size = 0;
  arr->capacity = 2;
  arr->data = (Instruction *)malloc(sizeof(Instruction) * arr->capacity);
  return arr;
}

void instructionarray_free(InstructionArray *arr) {
  assert(arr && "ins must not be null");
  for (size_t i = 0; i < arr->size; ++i) {
    instruction_free(&arr->data[i]);
  }
  free(arr->data);
  free(arr);
}

InstructionArray *instructionarray_add(InstructionArray *arr, Instruction i) {
  assert(arr && "ins must not be null");
  if (arr->capacity <= arr->size) {
    arr->capacity *= 2;
    arr->data =
        (Instruction *)realloc(arr->data, sizeof(Instruction) * arr->capacity);
  }
  arr->data[arr->size] = i;
  ++arr->size;
  return arr;
}
