#ifndef ASSEMBLER_TEXT_HANDLING_H
#define ASSEMBLER_TEXT_HANDLING_H

#include "definitions.h"

/*
 * turns word into a canonical representation -
 * no leading and finishing white characters
 * every sequence of white characters is replaces by a space character
 * no sequence of white characters before and after a comma
 * returns 1 if was trimmed and 0 if not
 * if in_brackets is zero - not trims inside brackets
 */
int trim(char *word, int in_brackets);

/*
 * parse trimmed_line
 * if applicable assigns the given parameters with the appropriate pointers
 * if not assigns NULL
 * handle errors
 * turns on has_label_flag if needed
 * set number_of_operators to -1 if more then 2 operands
 * if there's " or ( or first char of operandA is digit then not checking extra words and operandA continues to the end of trimmed_line
 * return 1 if parsed OK 0 if not
 */
int parse(char *trimmed_line, char **label, char **operation, char **operandA, char **operandB);

/*
 * parse original_operand and assigns the given parameters with the appropriate pointers
 * return 1 if parsed OK 0 if not
 */
int parse_addressing_type_2_parameters(char *original_operand, char **addressing_type_2_jumping_label, char **parameterA, char **parameterB);

/*
 * checks validation of label
 * handle errors
 * if print_error is zero not handling errors and returns 0 after first error
 * if is_extern is non-zero doesn't validate colon at end of label
 * returns 1 if label OK 0 if not
 */
int is_label_ok(char *label, int print_error, int is_extern);

/*
 * returns 1 if string starts and terminates with ", otherwise 0
 * handling errors
 */
int is_string_ok(char *string);

#endif /*ASSEMBLER_TEXT_HANDLING_H*/
