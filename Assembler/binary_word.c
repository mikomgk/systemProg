#include <math.h>
#include "binary_word.h"

void *mapping(char *word, char *words[], void *params[]) {
    if (!word)
        return NULL;
    for (; *words; words++, params++)
        if (!strcmp(word, *words))
            return *params;
    return NULL;
}

void dec2bin(int num, char *binary_word, int size_of_word) {
    int mask = 1, i;
    for (i = size_of_word - 1; i >= 0; i--, mask <<= 1)
        if (num & mask)
            binary_word[i] = '/';
        else
            binary_word[i] = '.';
}

char *get_addressing_type(char *operand) {
    if (!operand)
        return NULL;
    if (*operand == '#')
        return IMMEDIATE_ADDRESSING;
    if (mapping(operand, register_names, (void **)register_names)) {
        number_of_registers++;
        return REGISTER_ADDRESSING;
    }
    for (; *operand; operand++)
        if (*operand == '(')
            return JUMPING_ADDRESSING;
    return LABEL_ADDRESSING;
}

void write_operand_addressing(char *operation, char *operand, char *binary_word, int operandBinaryIndex,char ***operand_addressing_types_per_op) {
    char *operand_type, **addressing_options, *tmp;
    if (!operand)
        /*no operand - do nothing*/
        return;
    operand_type = get_addressing_type(operand);
    if (operand_addressing_types_per_op)
        /*operand_addressing_types_per_op is not null*/
        addressing_options = mapping(operation, op_names, (void **) operand_addressing_types_per_op);
    else
        /*operand_addressing_types_per_op is null - parameters of addressing type 2 can have all addressing types beside 2*/
        addressing_options = addressing_013;
    if (!strcmp(operand_type, JUMPING_ADDRESSING))
        addressing_type_2_flag = 1;
    if (mapping(operand_type, addressing_options, (void **) addressing_options) || !operation) {
        /*correct addressing type*/
        if ((tmp = (char *) mapping(operand_type, addressing_types, (void **) addressing_types_code)))
            strcpy(binary_word + operandBinaryIndex, tmp);
    } else
        /*wrong addressing type*/
        insert_error_message(ERR_ADDRESSING_MODE_IS_NOT_COMPATIBLE);
}

void write_parameter_binary_word(char *binary_word, char *operand, int operand_type, char *option_operandB, int is_destination_operand) {
    int number;
    char *tmp = NULL;
    reset_binary_word(binary_word);
    if (option_operandB) {
        strcpy(binary_word + SOURCE_REGISTER_INDEX, mapping(operand, register_names, (void **) register_code));
        strcpy(binary_word + DESTINATION_REGISTER_INDEX, mapping(option_operandB, register_names, (void **) register_code));
        return;
    }
    switch (operand_type) {
        case 0:
            number = strtol(operand + 1, &tmp, 10);
            if (tmp) {
                insert_error_message(ERR_INVALID_INTEGER);
                return;
            }
            if (number > biggest_short_number) {
                insert_error_message(ERR_NUMBER_IS_TOO_BIG);
                return;
            }
            dec2bin(number, binary_word, NUMBER_SIZE);
            break;
        case 1:
            number = get_symbol_address(operand);
            if (number == -1)
                insert_error_message(ERR_LABEL_NAME_IS_NOT_EXIST);
            else {
                dec2bin(number, binary_word, NUMBER_SIZE);
                strcpy(binary_word + ARE_INDEX, mapping(is_external(operand)
                                                        ? EXTERNAL
                                                        : RELOCATABLE, are, (void **) are_code));
            }
            break;
        case 3:
            strcpy(binary_word + (is_destination_operand
                                  ? DESTINATION_REGISTER_INDEX
                                  : SOURCE_REGISTER_INDEX), mapping(operand, register_names, (void **) register_code));
            break;
    }
}

void reset_binary_word(char *binary_word) {
    int i = 0;
    for (; i < WORD_SIZE; i++)
        *binary_word++ = '.';
}

void insert_error_message(char *error_message) {
    replace_line(ERROR_T, LC, error_message, original_line);
    error_flag = 1;
}

int biggest_number(int num_of_binary_digits) {
    int i = 0, sum = 0;
    for (; i < num_of_binary_digits; i++)
        sum += pow(2, i);
    return sum;
}