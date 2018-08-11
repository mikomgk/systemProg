#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "settings.h"
#include "tables.h"

void *mapping(char *word, char *words[], void *params[]);
int trim(char *word, int in_brackets);
void dec2bin(int num, char *binary_word, int size_of_word);
int parse(char *trimmed_line, char **label, char **operation, char **operandA, char **operandB, int line_counter, char *original_line);
int is_label_ok(char *label, int line_counter, char *original_line);
int is_string_ok(char *string);
char *get_addressing_type(char *operand, int *number_of_registers);
void write_operand_addressing(char *operation, char *operand, char *binary_word, char *tmp, int operandBinaryIndex, int *number_of_registers, int
*addressing_type_2_flag);
void write_parameter_binary_word(char *binary_word, char *operand, int operand_type, char *option_operandB, int is_destination_operand);
void reset_binary_word(char *binary_word);
FILE *new_file(char *file_name, char *file_extention, char *new_extention);
void insert_error_message(int LC, char *error_message, char *line);
int biggest_number(int num_of_binary_digits);

int error_flag,biggest_long_number,biggest_short_number, has_label_flag;

int main(int argc, char *argv[]) {
    FILE *fp, *n_file;
    char line[LINE_SIZE], line_copy[LINE_SIZE], *label = NULL, *operation = NULL, *operandA = NULL, *operandB = NULL, binary_word[WORD_SIZE], *tmp, *operandA_type,
            *operandB_type, **addressin_options, *parameterA, *parameterB, file_name[FILENAME_MAX], *file_extention;
    int LC, label_exist_flag, label_ok_flag, parsed_ok_flag, addressing_type_2_flag, number_of_extra_words, number_of_operators, number_of_registers, i;
    long number;
    extern int error_fla, biggest_long_number, biggest_short_number;
    biggest_long_number = biggest_number(WORD_SIZE), biggest_short_number = biggest_number(NUMBER_SIZE)
    if (argc == 1)
        return 0;
    while (--argc > 0) {
        strcpy(file_name, argv[0]);
        if ((file_extention = strchr(file_name, '.')) == NULL || strcmp(file_extention, ASSEMBLEY_EXTENTION)) {
            //not an assembley file
            insert_error_message(0, ERR_NOT_AN_ASSEMBLEY_FILE, NULL);
        }
        if ((fp = fopen(*++argv, "r")) == NULL) {
            //file not open
            insert_error_message(0, ERR_CAN_NOT_OPEN_FILE, NULL);
        } else {
            //file open
            LC = 0;
            clear_tables();
            error_flag = 0;
            //get next line
            while (fgets(line, LINE_SIZE, fp)) {
                LC++;
                number_of_extra_words = 0;
                number_of_operators = 0;
                addressing_type_2_flag = 0;
                has_label_flag = 0;
                label_exist_flag = 0;
                reset_binary_word(binary_word);
                strcpy(line_copy, line);
                trim(line_copy, 0);
                if (strlen(line_copy) == 0 || line_copy[0] == ';')
                    //empty line or comment line
                    continue;
                //parse line
                parsed_ok_flag = parse(line_copy, &label, &operation, &operandA, &operandB, LC, line);
                if (!parsed_ok_flag)
                    //didn't parse
                    continue;
                if (has_label_flag) {
                    //TODO: has a label
                }
                //label already exist
                label_ok_flag = is_label_ok(label, LC, line);
                if ((label_exist_flag = has_label_flag ? is_label_exist(label) : 0)) {
                    insert_error_message(LC, ERR_LABEL_NAME_ALREADY_IN_USE, line);
                }
                //directive line
                if (*operation == '.') {
                    if (!strcmp((operation + 1), DATA)) {
                        if (label_ok_flag && !label_exist_flag)
                            replace_line(SYMBOL_T, DC, label, DATA);
                        //too many operands
                        if (operandB) {
                            insert_error_message(line, LC, ERR_WRONG_NUMBER_OF_OPERATORS);
                        } else {
                            for (operandA = strtok(operandA, ","); *operandA; operandA = strtok(NULL, ",")) {
                                number = strtol(operandA, &operandB, 10);
                                //not an int
                                if (operandB) {
                                    insert_error_message(LC, ERR_INVALID_INTEGER, line);
                                    break;
                                } else if (number > biggest_long_number) {
                                    insert_error_message(LC, ERR_NUMBER_IS_TOO_BIG, line);
                                } else {
                                    //enter binary number
                                    dec2bin(number, binary_word, WORD_SIZE);
                                    replace_line(DATA_T, 0, binary_word, NULL);
                                }
                            }
                        }
                    } else if (!strcmp((operation + 1), STRING)) {
                        if (label_ok_flag && !label_exist_flag)
                            replace_line(SYMBOL_T, DC, label, DATA);
                        //too many operands
                        if (operandB) {
                            insert_error_message(line, LC, ERR_WRONG_NUMBER_OF_OPERATORS);
                        } else if (!is_string_ok(operandA)) {
                            insert_error_message(LC, ERR_MISSING_QUOTATION_MARK, line);
                        } else
                            //ignoring quotation marks
                            for (operandA++; *(operandA + 1); operandA++) {
                                dec2bin(*operandA, binary_word, WORD_SIZE);
                                replace_line(DATA_T, 0, binary_word, NULL);
                            }
                    } else if (!strcmp((operation + 1), ENTRY)) {
                        if (has_label_flag)
                            replace_line(ERROR_T, LC, ALERT_LABEL_MEANINGLESS, line);
                    } else if (!strcmp((operation + 1), EXTERN)) {
                        if (has_label_flag)
                            replace_line(ERROR_T, LC, ALERT_LABEL_MEANINGLESS, line);
                        if (operandB) {
                            insert_error_message(line, LC, ERR_WRONG_NUMBER_OF_OPERATORS);
                        } else if (!is_label_ok(operandA, LC, line)) {
                            error_flag = 1;
                        } else if (is_label_exist(operandA)) {
                            //label already exist
                            insert_error_message(LC, ERR_LABEL_NAME_ALREADY_IN_USE, line);
                        } else {
                            replace_line(SYMBOL_T, 0, operandA, EXTERN);
                        }
                    } else {
                        insert_error_message(LC, ERR_WRONG_OPERATION_NAME, line);
                    }
                } else {
                    if (label_ok_flag && !label_exist_flag)
                        replace_line(SYMBOL_T, DC, label, OPERATION);
                    //operation line
                    if ((tmp = (char *) mapping(operation, op_names, op_code)) != NULL)
                        strcpy(binary_word + 4, tmp);
                    else {
                        //wrong operation name
                        insert_error_message(LC, ERR_WRONG_OPERATION_NAME, line);
                        continue;
                    }
                    switch (atoi((char *) mapping(operation, op_names, num_of_operands_per_op))) {
                        //wrong number of operators
                        case 0:
                            if (operandA) {
                                insert_error_message(LC, ERR_WRONG_NUMBER_OF_OPERATORS, line);
                                number_of_operators = -1;
                            } else {
                                number_of_operators = 0;
                                replace_line(INSTRUCTIONS_T, NULL, binary_word, NULL);
                            }
                            break;
                        case 1:
                            if (operandB) {
                                insert_error_message(LC, ERR_WRONG_NUMBER_OF_OPERATORS, line);
                                number_of_operators = -1;
                            } else
                                number_of_operators = 1;
                            break;
                        case 2:
                            if (number_of_operators == 0)
                                number_of_operators = 2;
                        default:
                            number_of_operators = -1;
                    }
                    if (number_of_operators > 0) {
                        write_operand_addressing(operation, operandA, binary_word, tmp, number_of_operators == 1
                                                                                        ? DESTINATION_OPERAND_ADDRESSING_INDEX
                                                                                        : SOURCE_OPERAND_ADDRESSING_INDEX, &number_of_registers, &addressing_type_2_flag);
                        write_operand_addressing(operation, operandB, binary_word, tmp, number_of_operators == 1
                                                                                        ? SOURCE_OPERAND_ADDRESSING_INDEX
                                                                                        : DESTINATION_OPERAND_ADDRESSING_INDEX, &number_of_registers, &addressing_type_2_flag);
                        if (addressing_type_2_flag) {
                            //TODO: parse parameters
                            write_operand_addressing(NULL, parameterA, binary_word, tmp, 0, &number_of_registers, NULL);
                            write_operand_addressing(NULL, parameterB, binary_word, tmp, 2, &number_of_registers, NULL);
                            number_of_extra_words++;
                        } else
                            replace_line(INSTRUCTIONS_T, NULL, binary_word, NULL);
                        number_of_extra_words = number_of_extra_words + number_of_operators - (number_of_registers == 2 ? 1 : 0);
                        IC += number_of_extra_words;
                    }
                }
            }
            if (!error_flag) {
                /*there is no error*/
                update_words_addresses(1, IC);
                fseek(fp, 0, SEEK_SET);
                IC = 0;
                //second round
                while (fgets(line, LINE_SIZE, fp)) {
                    number_of_registers = 0;
                    number_of_operators = 0;
                    //TODO: copy line, parse, trim
                    if (*operation == '.') {
                        if (!strcmp(operation + 1, ENTRY))
                            for (i = 1; i <= SC; i++)
                                change_to_entry(operandA);
                        continue;
                    }
                    if ((operandA_type = get_addressing_type(operandA, &number_of_registers))) {
                        if (!strcmp(operandA_type, "2")) {
                            //TODO: parse and trim
                            operandA_type = get_addressing_type(operandA, &number_of_registers);
                        }
                        if ((operandB_type = get_addressing_type(operandB, &number_of_registers)))
                            number_of_operators = 2;
                        else
                            number_of_operators = 1;
                    }
                    //increase IC to effect the extra word and not the instruction word
                    IC++;
                    //writes extra words
                    for (i = 1; i <= number_of_operators; i++) {
                        int is_first_operator = i == 1;
                        int is_source_operand = number_of_operators == 2 && is_first_operator;
                        if (number_of_registers == 2) {
                            write_parameter_binary_word(binary_word, operandA, operandA_type, operandB, 0);
                            i++;
                        }
                        write_parameter_binary_word(binary_word, is_first_operator ? operandA : operandB, atoi(is_first_operator ? operandA_type : operandB_type), NULL,
                                                    is_source_operand ? 0 : 1);
                        replace_line(INSTRUCTIONS_T, NULL, binary_word, NULL);
                    }
                }
            }
            fclose(fp);
        }
        if (error_flag) {
            //writes errors to stderr
            write_errors(*argv);
        } else {
            //create and write files
            n_file = new_file(file_name, file_extention, OBJECT_EXTENTION);
            write_table_to_file(n_file, OBJECT_F);
            n_file = new_file(file_name, file_extention, ENTRY_EXTENTION);
            write_table_to_file(n_file, ENTRY_F);
            n_file = new_file(file_name, file_extention, EXTERN_EXTENTION);
            write_table_to_file(n_file, EXTERN_F);
        }
    }
    return 0;
}

void insert_error_message(int LC, char *error_message, char *line) {
    extern int error_flag;
    replace_line(ERROR_T, LC, error_message, line);
    error_flag = 1;
}

FILE *new_file(char *file_name, char *file_extention, char *new_extention) {
    strcpy(file_extention, new_extention);
    return fopen(file_name, "w");
}

void reset_binary_word(char *binary_word) {
    int i = 0;
    for (; i < WORD_SIZE; i++)
        *binary_word++ = '.';
}

void write_parameter_binary_word(char *binary_word, char *operand, int operand_type, char *option_operandB, int is_destination_operand) {
    int number;
    char *tmp = NULL;
    reset_binary_word(binary_word);
    if (option_operandB) {
        strcpy(binary_word, mapping(operand, register_names, register_code));
        strcpy(binary_word + DESTINATION_REGISTER_INDEX, mapping(option_operandB, register_names, register_code));
        return;
    }
    switch (operand_type) {
        case 0:
            number = strtol(operand + 1, &tmp, 10);
            if (tmp) {
                insert_error_message(LC, ERR_INVALID_INTEGER, line);
                return;
            }
            if(number>biggest_short_number) {
                insert_error_message(LC, ERR_NUMBER_IS_TOO_BIG, line);
                return;
            }
            dec2bin(number, binary_word, NUMBER_SIZE);
            break;
        case 1:
            number = get_symbol_address(operand);
            if (number == -1)
                insert_error_message(LC, ERR_LABEL_NAME_IS_NOT_EXIST, line);
            else
                dec2bin(number, binary_word, NUMBER_SIZE);
            break;
        case 3:
            strcpy(binary_word + (is_destination_operand ? DESTINATION_REGISTER_INDEX : 0), mapping(operand, register_names, register_code));
            break;
    }
}

void write_operand_addressing(char *operation, char *operand, char *binary_word, char *tmp, int operandBinaryIndex, int *number_of_registers, int
*addressing_type_2_flag) {
    char *operand_type = get_addressing_type(operand, number_of_registers);
    char **addressing_options = mapping(operation, op_names, dest_operand_addressing_types_per_op);
    if (!strcmp(operand_type, "2"))
        *addressing_type_2_flag = 1;
    if (mapping(operand_type, addressing_options, addressing_options)) {
        //correct addressing type
        if ((tmp = (char *) mapping(operand_type, addressing_types, addressing_types_code)))
            strcpy(binary_word + operandBinaryIndex, tmp);
    }else
        //wrong addressing type
        insert_error_message(LC,ERR_ADDRESSING_MODE_IS_NOT_COMPATIBLE,line);
}

int parse(char *trimmed_line, char **label, char **operation, char **operandA, char **operandB, int line_counter, char *original_line) {
    int count_spaces = 0, count_commas = 0;
    char *pnt = trimmed_line, *tmp = NULL;
    *label = NULL;
    *operation = NULL;
    *operandA = NULL;
    *operandB = NULL;
    //count spaces and commas
    for (; *pnt && *pnt != '(' && *pnt != '\"'; pnt++) {
        if (*pnt == ' ')
            count_spaces++;
        else if (*pnt == ',') {
            count_commas++;
            if (*(pnt + 1) == ',') {
                replace_line(ERROR_T, line_counter, ERR_TOO_MANY_COMMAS, original_line);
                count_commas--;
            }
        } else if (count_spaces == 1 && *(pnt - 1) == ' ' && isdigit(*pnt))
            /*operandA is numbers array*/
            break;
    }
    if (count_spaces == 0) {
        /*wrong number of operators or too many commas*/
        replace_line(ERROR_T, line_counter, count_commas ? ERR_TOO_MANY_COMMAS : ERR_WRONG_NUMBER_OF_OPERATORS, original_line);
        return 0;
    } else if (count_spaces > 2) {
        /*too many spaces*/
        replace_line(ERROR_T, line_counter, ERR_MISSING_COMMA, original_line);
        return 0;
    } else if (count_spaces == 1) {
        /*no label*/
        *operation = strtok(trimmed_line, " ");
    } else if (count_spaces == 2) {
        /*yes label*/
        *label = strtok(trimmed_line, " ");
        *operation = strtok(NULL, " ");
        has_label_flag = 1;
    }
    *operandA = strtok(NULL, ",");
    if(**operandA=='\"') {
        /*in a string*/
        for (tmp = *(operandA + 1); *tmp != '\"'; tmp++)
            /**/;
        tmp++;
    }else {
        if (!isdigit(**operandA))
            /*operandA is not .data input*/
            *operandB = strtok(NULL, ",");
        tmp = strtok(NULL, " ");
    }
    if (tmp) {
        /*there's an extra parameter*/
        replace_line(ERROR_T, line_counter, ERR_WRONG_NUMBER_OF_OPERATORS, original_line);
        return 0;
    }
    return 1;
}

void *mapping(char *word, char *words[], void *params[]) {
    if (!word)
        return NULL;
    for (; *words; words++, params++)
        if (!strcmp(word, *words))
            return *params;
    return NULL;
}

int trim(char *word, int in_brackets) {
    char *ptr = word, *start = word, *tmp;
    int trimmed_flag = 0;
    /*trim leading and finishing white characters*/
    for (; isspace(*word); word++)
        /**/;
    for (; *word; *ptr++ = *word++)
        /**/;
    for (--ptr; isspace(*ptr); ptr--)
        /**/;
    *++ptr = '\0';
    /*trim inword white characters*/
    for (ptr = word = start; *word; *ptr++ = *word++) {
        if (*word == '\"') {
            for (*ptr++ = *word++; *word != '\"'; *ptr++ = *word++)
                /**/;
        } else if (!in_brackets && *word == '(') {
            for (; *word != ')'; *ptr++ = *word++)
                /**/;
        } else if (isspace(*word)) {
            tmp = word - 1;
            for (; isspace(*word); word++)
                /**/;
            if (*word != ',' && *tmp != ',')
                *--word = ' ';
            else
                *--word = *--ptr;
            trimmed_flag = 1;
        }
    }
    for (; *word; *ptr++ = *word++)
        /**/;
    *ptr = '\0';
    return trimmed_flag;
}

void dec2bin(int num, char *binary_word, int size_of_word) {
    int mask = 1, i;
    for (i = size_of_word - 1; i >= 0; i--, mask <<= 1)
        if (num & mask)
            binary_word[i] = '/';
        else
            binary_word[i] = '.';
}

int is_label_ok(char *label, int line_counter, char *original_line) {
    int error = 0;
    char *pnt = label;
    if (strlen(pnt) > LABEL_SIZE + 1) {
        insert_error_message(line_counter, ERR_LABEL_NAME_IS_TOO_LONG, original_line);
        error = 1;
    }
    if (!isalpha(*pnt++))
        error = 2;
    for (; *pnt; pnt++) {
        if (!isalnum(*pnt))
            error = 2;
    }
    if (error == 2)
        insert_error_message(line_counter, ERR_LABEL_NAME_IS_NOT_ALLOWED, original_line);
    if (*--label != ':') {
        insert_error_message(line_counter,ERR_MISSING_COLON_AFTER_LABEL,original_line);
        error = 2;
    }
    else
        *pnt == '\0';
    if (mapping(label, op_names, op_code))
        error = 4;
    if (mapping(label, register_names, register_code))
        error = 4;
    if (mapping(label, directives, directives_number))
        error = 4;
    if (error == 4)
        insert_error_message(line_counter, ERR_LABEL_NAME_IS_SAVED_WORD, original_line);
    return error ? 0 : 1;
}

int is_string_ok(char *string) {
    if (*string != '\"')
        return 0;
    for (; *string; string++)
        /**/;
    if (*--string != '\"')
        return 0;
    return 1;
}

char *get_addressing_type(char *operand, int *number_of_registers) {
    if (!operand)
        return NULL;
    if (*operand == '#')
        return IMMEDIATE_ADDRESSING;
    if (mapping(operand, register_names, register_names)) {
        *number_of_registers++;
        return REGISTER_ADDRESSING;
    }
    for (; *operand; operand++)
        if (*operand == '(')
            return JUMPING_ADDRESSING;
    return LABEL_ADDRESSING;
}

int biggest_number(int num_of_binary_digits){
    int i=0,sum=0;
    for(;i<num_of_binary_digits;i++)
        sum+=pow(2,i);
    return sum;
}