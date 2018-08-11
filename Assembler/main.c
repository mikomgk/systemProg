#include "defenitions.h"

FILE *new_file(char *file_name, char *file_extention, char *new_extention);

int error_flag,biggest_long_number,biggest_short_number, has_label_flag,LC;
char original_line[LINE_SIZE];

int main(int argc, char *argv[]) {
    FILE *fp, *n_file;
    char trimmed_line[LINE_SIZE], *label = NULL, *operation = NULL, *operandA = NULL, *operandB = NULL, binary_word[WORD_SIZE], *tmp, *operandA_type,
            *operandB_type, **addressing_options, *addressing_type_2_jumping_label=NULL, file_name[FILENAME_MAX], *file_extention;
    int label_exist_flag, label_ok_flag, parsed_ok_flag, addressing_type_2_flag, number_of_extra_words, number_of_operators, number_of_registers, is_first_operator,
            is_source_operand,i;
    long number;
    biggest_long_number = biggest_number(WORD_SIZE);
    biggest_short_number = biggest_number(NUMBER_SIZE);
    if (argc == 1)
        return 0;
    while (--argc > 0) {
        strcpy(file_name, argv[0]);
        if ((file_extention = strchr(file_name, '.')) == NULL || strcmp(file_extention, ASSEMBLEY_EXTENTION)) {
            /*not an assembley file*/
insert_error_message(ERR_NOT_AN_ASSEMBLEY_FILE);
        }
        if ((fp = fopen(*++argv, "r")) == NULL) {
            /*file not open*/
            insert_error_message(ERR_CAN_NOT_OPEN_FILE);
        } else {
            /*file open*/
            LC = 0;
            clear_tables();
            error_flag = 0;
            /*get next line*/
            while (fgets(original_line, LINE_SIZE, fp)) {
                LC++;
                number_of_extra_words = 0;
                number_of_operators = 0;
                addressing_type_2_flag = 0;
                has_label_flag = 0;
                label_exist_flag = 0;
                reset_binary_word(binary_word);
                strcpy(trimmed_line, original_line);
                trim(trimmed_line, 0);
                if (strlen(trimmed_line) == 0 || trimmed_line[0] == ';')
                    /*empty line or comment line*/
                    continue;
                /*parse line*/
                parsed_ok_flag = parse(trimmed_line, &label, &operation, &operandA, &operandB);
                if (!parsed_ok_flag)
                    /*didn't parse*/
                    continue;
                /*label already exist*/
                label_ok_flag = is_label_ok(label, 1);
                if ((label_exist_flag = has_label_flag ? is_label_exist(label) : 0)) {
                    insert_error_message(ERR_LABEL_NAME_ALREADY_IN_USE);
                }
                if (*operation == '.') {
                    /*directive line*/
                    if(!has_label_flag){
                        /*directive line without a label*/
                        insert_error_message(ERR_DIRECTIVE_LINE_MUST_HAVE_LABEL);
                        continue;
                    }
                    if (!strcmp((operation + 1), DATA)) {
                        /*.data line*/
                        if (label_ok_flag && !label_exist_flag)
                            replace_line(SYMBOL_T, DC, label, DATA);
                        if (operandB) {
                            /*too many operands*/
                            insert_error_message(ERR_WRONG_NUMBER_OF_OPERATORS);
                        } else {
                            for (operandA = strtok(operandA, ","); *operandA; operandA = strtok(NULL, ",")) {
                                /*separates each number*/
                                number = strtol(operandA, &operandB, 10);
                                if (operandB) {
                                    /*not an int*/
                                    insert_error_message(ERR_INVALID_INTEGER);
                                    break;
                                } else if (number > biggest_long_number) {
                                    /*number is too big*/
                                    insert_error_message(ERR_NUMBER_IS_TOO_BIG);
                                } else {
                                    /*insert binary number*/
                                    dec2bin(number, binary_word, WORD_SIZE);
                                    replace_line(DATA_T, 0, binary_word, NULL);
                                }
                            }
                        }
                    } else if (!strcmp((operation + 1), STRING)) {
                        /*.string line*/
                        if (label_ok_flag && !label_exist_flag)
                            replace_line(SYMBOL_T, DC, label, DATA);
                        if (operandB) {
                            /*too many operands*/
                            insert_error_message (ERR_WRONG_NUMBER_OF_OPERATORS);
                        } else if (!is_string_ok(operandA)) {
                            /*missing QM"*/
                            insert_error_message(ERR_MISSING_QUOTATION_MARK);
                        } else
                            for (operandA++; *(operandA + 1); operandA++) {
                                /*ignoring leading and finish quotation marks*/
                                dec2bin(*operandA, binary_word, WORD_SIZE);
                                replace_line(DATA_T, 0, binary_word, NULL);
                            }
                    } else if (!strcmp((operation + 1), ENTRY)) {
                        /*.entry line*/
                        if (has_label_flag)
                            replace_line(ERROR_T, LC, ALERT_LABEL_MEANINGLESS, original_line);
                    } else if (!strcmp((operation + 1), EXTERN)) {
                        /*.extern line*/
                        if (has_label_flag)
                            replace_line(ERROR_T, LC, ALERT_LABEL_MEANINGLESS, original_line);
                        if (operandB) {
                            /*too many operands*/
                            insert_error_message(ERR_WRONG_NUMBER_OF_OPERATORS);
                        } else if (!is_label_ok(operandA,1)) {
                            /*extern label name is not allowed*/
                            continue;
                        } else if (is_label_exist(operandA)) {
                            /*label already exist*/
                            insert_error_message(ERR_LABEL_NAME_ALREADY_IN_USE);
                        } else {
                            replace_line(SYMBOL_T, 0, operandA, EXTERN);
                        }
                    } else {
                        /*wrong directive name*/
                        insert_error_message(ERR_WRONG_OPERATION_NAME);
                    }
                } else {
                    /*operation line*/
                    if (label_ok_flag && !label_exist_flag)
                        replace_line(SYMBOL_T, DC, label, OPERATION);
                    if ((tmp = (char *) mapping(operation, op_names, (void **)op_code)))
                        strcpy(binary_word + OPERATION_CODE_INDEX, tmp);
                    else {
                        if (!has_label_flag && is_label_ok(operation, 0))
                            /*operation name is missing*/
                            insert_error_message(ERR_MISSING_OPERATION_NAME);
                        else
                            /*wrong operation name*/
                            insert_error_message(ERR_WRONG_OPERATION_NAME);
                        continue;
                    }
                    switch (atoi((char *) mapping(operation, op_names, (void **)num_of_operands_per_op))) {
                        case 0:
                            if (operandA) {
                                /*wrong number of operators*/
                                insert_error_message(ERR_WRONG_NUMBER_OF_OPERATORS);
                                number_of_operators = -1;
                            } else {
                                number_of_operators = 0;
                                replace_line(INSTRUCTIONS_T, 0, binary_word, NULL);
                            }
                            break;
                        case 1:
                            if (operandB) {
                                /*wrong number of operators*/
                                insert_error_message(ERR_WRONG_NUMBER_OF_OPERATORS);
                                number_of_operators = -1;
                            } else
                                number_of_operators = 1;
                            break;
                        case 2:
                            /*TODO: check number_of_operators in parse()*/
                            if (number_of_operators == 0)
                                number_of_operators = 2;
                        default:
                            number_of_operators = -1;
                    }
                    if (number_of_operators > 0) {
                        /*filling binary word by operand addressing types*/
                        write_operand_addressing(operation, operandA, binary_word, tmp, number_of_operators == 1
                                                                                        ? DESTINATION_OPERAND_ADDRESSING_INDEX
                                                                                        : SOURCE_OPERAND_ADDRESSING_INDEX, &number_of_registers, &addressing_type_2_flag);
                        write_operand_addressing(operation, operandB, binary_word, tmp, number_of_operators == 1
                                                                                        ? SOURCE_OPERAND_ADDRESSING_INDEX
                                                                                        : DESTINATION_OPERAND_ADDRESSING_INDEX, &number_of_registers, &addressing_type_2_flag);
                        if (addressing_type_2_flag) {
                            if(trim(operandA,1))
                                /*spaces between parameters in brackets)*/
                                insert_error_message(ERR_SPACE_BETWEEN_PARAMS);
                            else if (parse_addressing_type_2_parameters(operandA, &addressing_type_2_jumping_label, &operandA, &operandB)) {
                                /*trim and parse OK*/
                                write_operand_addressing(NULL, operandA, binary_word, tmp, PARAMETER1_INDEX, &number_of_registers, NULL);
                                write_operand_addressing(NULL, operandB, binary_word, tmp, PARAMETER2_INDEX, &number_of_registers, NULL);
                                number_of_extra_words++;
                            }
                        }
                        replace_line(INSTRUCTIONS_T, 0, binary_word, NULL);
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
                /*second round*/
                while (fgets(original_line, LINE_SIZE, fp)) {
                    number_of_registers = 0;
                    number_of_operators = 0;
                    /*TODO: copy line, parse, trim*/
                    if (*operation == '.') {
                        /*directive line*/
                        if (!strcmp(operation + 1, ENTRY))
                            /*.entry line*/
                            change_to_entry(operandA);
                        continue;
                    }else if ((operandA_type = get_addressing_type(operandA, &number_of_registers))) {
                        if (!strcmp(operandA_type, JUMPING_ADDRESSING)) {
                            addressing_type_2_flag=1;
                            trim(operandA,1);
                            parse_addressing_type_2_parameters(operandA,&addressing_type_2_jumping_label,&operandA,&operandB);
                            operandA_type = get_addressing_type(operandA, &number_of_registers);
                        }
                        if ((operandB_type = get_addressing_type(operandB, &number_of_registers)))
                            number_of_operators = 2;
                        else
                            number_of_operators = 1;
                    }
                    /*increase IC to effect the extra word and not the instruction word*/
                    IC++;
                    if(addressing_type_2_flag) {
                        /*write label word of addressing type 2 if needed*/
                        dec2bin(get_symbol_address(addressing_type_2_jumping_label), binary_word, NUMBER_SIZE);
                        strcpy(binary_word + ARE_INDEX, mapping(is_external(addressing_type_2_jumping_label) ? EXTERNAL : RELOCATABLE, are, (void **)are_code));
                        replace_line(INSTRUCTIONS_T, 0, binary_word, NULL);
                    }
                    for (i = 1; i <= number_of_operators; i++) {
                        /*write parameters*/
                        is_first_operator = i == 1;
                        is_source_operand = number_of_operators == 2 && is_first_operator;
                        if (number_of_registers == 2) {
                            /*write 2 registers to one word*/
                            write_parameter_binary_word(binary_word, operandA, 0, operandB, 0);
                            i++;
                        } else
                            /*write each parameter word*/
                            write_parameter_binary_word(binary_word, is_first_operator ? operandA : operandB, atoi(is_first_operator ? operandA_type : operandB_type), NULL,
                                                        is_source_operand ? 0 : 1);
                        /*insert word to table*/
                        replace_line(INSTRUCTIONS_T, 0, binary_word, NULL);
                    }
                }
            }
            fclose(fp);
        }
        if (error_flag) {
            /*writes errors to stderr*/
            write_errors(*argv);
        } else {
            /*create and write files*/
            n_file = new_file(file_name, file_extention, OBJECT_EXTENTION);
            write_table_to_file(n_file, OBJECT_F);
            fclose(n_file);
            n_file = new_file(file_name, file_extention, ENTRY_EXTENTION);
            write_table_to_file(n_file, ENTRY_F);
            fclose(n_file);
            n_file = new_file(file_name, file_extention, EXTERN_EXTENTION);
            write_table_to_file(n_file, EXTERN_F);
            fclose(n_file);
        }
    }
    return 0;
}

FILE *new_file(char *file_name, char *file_extention, char *new_extention) {
    strcpy(file_extention, new_extention);
    return fopen(file_name, "w");
}