#include "text_handling.h"

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
    /*trim in word white characters*/
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

int parse(char *trimmed_line, char **label, char **operation, char **operandA, char **operandB) {
    int count_spaces = 0, count_commas = 0, is_string = 0, is_brackets = 0, is_data = 0;
    char *pnt = trimmed_line, *tmp = NULL, *is_operation = NULL;
    *label = NULL;
    *operation = NULL;
    *operandA = NULL;
    *operandB = NULL;
    /*count spaces and commas*/
    for (; *pnt; pnt++) {
        if (is_brackets && *(pnt - 1) == ')') {
            /*another word after brackets*/
            insert_error_message(ERR_WRONG_NUMBER_OF_OPERATORS);
            return 0;
        }
        if (!is_brackets && !is_string && !is_data && *pnt == ' ')
            count_spaces++;
        else if (*pnt == ',') {
            count_commas++;
            if (*(pnt + 1) == ',') {
                /*two commas in a row*/
                insert_error_message(ERR_TOO_MANY_COMMAS);
                count_commas--;
            }
        } else if (*pnt == '(') {
            /*operandA has brackets*/
            is_brackets = 1;
        } else if (*pnt == '\"') {
            /*operandA is string*/
            is_string = 1;
        } else if (count_spaces > 1 && *(pnt - 1) == ' ' && isdigit(*pnt)) {
            /*operandA is numbers array*/
            is_data = 1;
        }
    }
    if (count_spaces == 0) {
        /*wrong number of operators or too many commas*/
        insert_error_message(count_commas ? ERR_TOO_MANY_COMMAS : ERR_WRONG_NUMBER_OF_OPERATORS);
        return 0;
    } else if (count_spaces > 2) {
        if (is_brackets && count_commas == 1)
            insert_error_message(ERR_SPACE_BETWEEN_PARAMS);
            /*too many spaces*/
            insert_error_message(ERR_MISSING_COMMA);
        return 0;
    } else if (count_spaces == 1) {
        /*only two words*/
        *operation = strtok(trimmed_line, " ");
    } else if (count_spaces == 2) {
        /*yes label*/
        *label = strtok(trimmed_line, " ");
        *operation = strtok(NULL, " ");
        has_label_flag = 1;
    }
    *operandA = strtok(NULL, is_string || is_brackets || is_data ? "\0" : ",");
    if (!is_string && !is_brackets) {
        if (!isdigit(**operandA))
            /*operandA is not .data input*/
            *operandB = strtok(NULL, ",");
        tmp = strtok(NULL, ",");
    }
    if (count_spaces == 1 && (is_operation = mapping(*operandA, op_names, (void **) num_of_operands_per_op)) && atoi(is_operation) == 0) {
        /*operation with no operands*/
        *label = *operation;
        *operation = *operandA;
        *operandA = NULL;
        tmp = tmp ? tmp : *operandB;
    }
    if (tmp && *tmp) {
        /*there's an extra parameter*/
        insert_error_message(ERR_WRONG_NUMBER_OF_OPERATORS);
        number_of_operators = -1;
        return 0;
    }
    return 1;
}

int parse_addressing_type_2_parameters(char *original_operand, char **addressing_type_2_jumping_label, char **parameterA, char **parameterB) {
    char *pnt;
    *addressing_type_2_jumping_label = strtok(original_operand, "(");
    *parameterA = strtok(NULL, ",");
    *parameterB = strtok(NULL, ")");
    if (!*addressing_type_2_jumping_label || !*parameterA || !*parameterB)
        /*bad format*/
        return 0;
    /*go to last character to check*/
    for (pnt=*parameterB; *pnt; pnt++)
        /**/;
    if (*(++pnt))
        /*last character is not )*/
        return 0;
    return 1;
}

int is_label_ok(char *label, int print_error, int is_extern) {
    int error = 0;
    char *pnt = label;
    if (strlen(pnt) > LABEL_SIZE + 1) {
        /*label size + 1 for colon*/
        if (!print_error)
            return 0;
        insert_error_message(ERR_LABEL_NAME_IS_TOO_LONG);
        error = 1;
    }
    if (!isalpha(*pnt++))
        error = 2;
    for (; *pnt && *pnt!=':'; pnt++) {
        if (!isalnum(*pnt))
            error = 2;
    }
    if (error == 2) {
        if (!print_error)
            return 0;
        insert_error_message(ERR_LABEL_NAME_IS_NOT_ALLOWED);
    }
    if (!is_extern && *pnt != ':') {
        if (!print_error)
            return 0;
        insert_error_message(ERR_MISSING_COLON_AFTER_LABEL);
        error = 3;
    } else
        *pnt = '\0';
    if (mapping(label, op_names, (void **) op_code))
        /*label is operation name*/
        error = 4;
    if (mapping(label, register_names, (void **) register_code))
        /*label is register name*/
        error = 4;
    if (mapping(label, directives, (void **) directives_number))
        /*label is directive name*/
        error = 4;
    if (error == 4) {
        if (!print_error)
            return 0;
        insert_error_message(ERR_LABEL_NAME_IS_SAVED_WORD);
    }
    return error ? 0 : 1;
}

int is_string_ok(char *string) {
    int is_error = 0;
    char *last_Qmark;
    if (*string != '\"') {
        /*no leading quotation mark*/
        insert_error_message(ERR_MISSING_QUOTATION_MARK);
        is_error = 1;
    }
    last_Qmark = strrchr(string, '\"');
    if (!last_Qmark || last_Qmark == string) {
        /*no ending quotation mark*/
        insert_error_message(ERR_MISSING_QUOTATION_MARK);
        is_error = 1;
    } else if (*++last_Qmark) {
        /*another word after string*/
        insert_error_message(ERR_WRONG_NUMBER_OF_OPERATORS);
        is_error = 1;
    }
    return is_error ? 0 : 1;
}