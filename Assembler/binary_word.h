#ifndef ASSEMBLER_BINARY_WORD_H
#define ASSEMBLER_BINARY_WORD_H

#include "definitions.h"

/*
 * search for word in words and returns the matching pointer from params
 */
void *mapping(char *word, char *words[], void *params[]);

/*
 * writes number binary form into the first size_of_word bits in binary_word
 */
void dec2bin(int num, char *binary_word, int size_of_word);

/*
 * returns the number of the addressing type of operand as a string
 */
char *get_addressing_type(char *operand);

/* writes the operand addressing type binary code into binary_word in the operand_binary_index index
 * checks if it's correct addressing type and handle error if needed
 * if using for addressing type 2 parameters - operand_addressing_type_per_op must be NULL
 * if operand is NULL - do nothing
 * turns on addressing_type_2_flag if needed
 */
void write_operand_addressing(char *operation, char *operand, char *binary_word, int operand_binary_index, char ***operand_addressing_types_per_op);

/* writes operand binary code into binary_word
 * option_operandB is for 2 registers in one word, if given - operand_type and is_destination_operand are useless
 * handle errors if needed
 * handles extern occurrences
 */
void write_parameter_binary_word(char *binary_word, char *operand, int operand_type, char *option_operandB, int is_destination_operand);

/*
 * reset binary_word to zeros
 */
void reset_binary_word(char *binary_word);

/*
 * inserts error message to errors table and turns on error_flag
 */
void insert_error_message(char *error_message);

#endif /*ASSEMBLER_BINARY_WORD_H*/
