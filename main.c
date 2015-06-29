#include "include/ast.h"
#include "include/state.h"
#include "include/parser.h"
#include "include/interpreter.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

char *read_line() {
  size_t capacity = 2;
  char *line = (char *)calloc(capacity + 1, sizeof(char));
  size_t size = 0;

  int c = getchar();
  while (c != EOF && c != '\n') {
    if (capacity <= size) {
      capacity *= 2;
      line = (char *)realloc(line, sizeof(char) * capacity + 1);
    }
    line[size++] = c;
    c = getchar();
  }
  if (size > 0)
      line[size] = '\0';

  return line;
}

void interpret_cli() {
  printf("> ");
  char *line = read_line();

  State *state = state_new();

  while (strcmp(line, "quit")) {
    InstructionArray *arr = instructionarray_new();
    ParseResult pr = parse(line, arr);

    if (pr != Success) {
      printf("Brackets mismatch!");
      instructionarray_free(arr);
      break;
    } else {
      interpret_all(arr, state);
      instructionarray_free(arr);
      free(line);
    }

    printf("> ");
    line = read_line();
  }
  free(line);

  state_free(state);
}

void interpret_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Error while opening file");
    return;
  }

  // cannot assert(!fseek(file, 0L, SEEK_END)) because assert will be
  // ignored in release builds
  const int dummy = fseek(file, 0L, SEEK_END);
  assert(dummy && "cannot seek");

  long size = ftell(file);
  rewind(file);

  char *str = (char *)malloc(sizeof(char) * size + 1);

  fread(str, sizeof(char), size, file);
  str[size] = '\0';

  InstructionArray *arr = instructionarray_new();
  ParseResult pr = parse(str, arr);

  if (pr != Success) {
      if (pr == BracketsMismatch)
          printf("Brackets mismatch!");
      else
          printf("Unknown error!");
  } else {
    State *state = state_new();

    interpret_all(arr, state);

    state_free(state);
  }

  instructionarray_free(arr);

  free(str);

  fclose(file);
}

int main(int argc, char const *argv[]) {
  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      interpret_file(argv[i]);
    }
  } else {
    interpret_cli();
  }
  return 0;
}
