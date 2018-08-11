#ifndef ASSEMBLER_BINARY_WORD_H
#define ASSEMBLER_BINARY_WORD_H

#include "defenitions.h"

void *mapping(char *word, char *words[], void *params[]);
void dec2bin(int num, char *binary_word, int size_of_word);
char *get_addressing_type(char *operand, int *number_of_registers);
void write_operand_addressing(char *operation, char *operand, char *binary_word, char *tmp, int operandBinaryIndex, int *number_of_registers, int *addressing_type_2_flag);
void write_parameter_binary_word(char *binary_word, char *operand, int operand_type, char *option_operandB, int is_destination_operand);
void reset_binary_word(char *binary_word);
void insert_error_message(char *error_message);
int biggest_number(int num_of_binary_digits);

#endif //ASSEMBLER_BINARY_WORD_H
