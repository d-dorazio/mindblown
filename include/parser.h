#ifndef PARSER_H
#define PARSER_H

#include "ast.h"

typedef enum ParseResult {
  Success,
  BracketsMismatch,
} ParseResult;

ParseResult parse(const char *str, InstructionArray *arr);

ParseResult parse_helper(const char *str, size_t *i, InstructionArray *arr,
                         int brack_is_open);

#endif // PARSER_H
