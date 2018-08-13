#ifndef ASSEMBLER_TEXT_HANDLING_H
#define ASSEMBLER_TEXT_HANDLING_H

#include "definitions.h"

int trim(char *word, int in_brackets);
int parse(char *trimmed_line, char **label, char **operation, char **operandA, char **operandB);
int parse_addressing_type_2_parameters(char *original_operand, char **addressing_type_2_jumping_label, char **parameterA, char **parameterB);
int is_label_ok(char *label, int print_error, int is_extern);
int is_string_ok(char *string);

#endif /*ASSEMBLER_TEXT_HANDLING_H*/
