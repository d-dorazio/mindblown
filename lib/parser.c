#include "../include/parser.h"

#include <assert.h>

ParseResult parse(const char *str, InstructionArray *arr) {
  size_t i = 0;
  return parse_helper(str, &i, arr, 0);
}

ParseResult parse_helper(const char *str, size_t *i, InstructionArray *arr,
                         int brack_is_open) {

  assert(str && i && arr && "all args must not be null");
  for (; str[*i] != '\0'; ++*i) {
    switch (str[*i]) {
    case '+':
      instructionarray_add(arr, instruction_new(Plus, NULL));
      break;
    case '-':
      instructionarray_add(arr, instruction_new(Minus, NULL));
      break;
    case '>':
      instructionarray_add(arr, instruction_new(ShiftR, NULL));
      break;
    case '<':
      instructionarray_add(arr, instruction_new(ShiftL, NULL));
      break;
    case '.':
      instructionarray_add(arr, instruction_new(Out, NULL));
      break;
    case ',':
      instructionarray_add(arr, instruction_new(In, NULL));
      break;
    case '[': {
      InstructionArray *inner = instructionarray_new();

      ++*i; // eat [
      ParseResult res = parse_helper(str, i, inner, 1);
      if (res != Success) {
        instructionarray_free(inner);
        return res;
      }
      if (str[*i] == '\0') { // at the end of the string, cannot iterate anymore
        return BracketsMismatch;
      }
      instructionarray_add(arr, instruction_new(Loop, inner));

      break;
    }
    case ']': {
      if (!brack_is_open) {
        return BracketsMismatch;
      }
      return Success;
    }
    default:
      // ignore other characters
      break;
    }
  }
  if (brack_is_open) {
    return BracketsMismatch;
  }
  return Success;
}
