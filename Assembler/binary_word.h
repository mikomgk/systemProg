#ifndef ASSEMBLER_BINARY_WORD_H
#define ASSEMBLER_BINARY_WORD_H

#include "definitions.h"

void *mapping(char *word, char *words[], void *params[]);
void dec2bin(int num, char *binary_word, int size_of_word);
char *get_addressing_type(char *operand);
void write_operand_addressing(char *operation, char *operand, char *binary_word, int operandBinaryIndex, char ***operand_addressing_types_per_op);
void write_parameter_binary_word(char *binary_word, char *operand, int operand_type, char *option_operandB, int is_destination_operand);
void reset_binary_word(char *binary_word);
void insert_error_message(char *error_message);
int biggest_number(int num_of_binary_digits);
int pow(int x, int y);

#endif /*ASSEMBLER_BINARY_WORD_H*/
