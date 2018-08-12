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
    int count_spaces = 0, count_commas = 0;
    char *pnt = trimmed_line, *tmp = NULL;
    *label = NULL;
    *operation = NULL;
    *operandA = NULL;
    *operandB = NULL;
    /*count spaces and commas*/
    for (; *pnt && *pnt != '(' && *pnt != '\"'; pnt++) {
        if (*pnt == ' ')
            count_spaces++;
        else if (*pnt == ',') {
            count_commas++;
            if (*(pnt + 1) == ',') {
                /*two commas in a row*/
                insert_error_message(ERR_TOO_MANY_COMMAS);
                count_commas--;
            }
        } else if (count_spaces == 1 && *(pnt - 1) == ' ' && isdigit(*pnt))
            /*operandA is numbers array*/
            break;
    }
    if (count_spaces == 0) {
        /*wrong number of operators or too many commas*/
        insert_error_message(count_commas ? ERR_TOO_MANY_COMMAS : ERR_WRONG_NUMBER_OF_OPERATORS);
        return 0;
    } else if (count_spaces > 2) {
        /*too many spaces*/
        insert_error_message(ERR_MISSING_COMMA);
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
        insert_error_message(ERR_WRONG_NUMBER_OF_OPERATORS);
        return 0;
    }
    return 1;
}

int parse_addressing_type_2_parameters(char *original_operand,char **addressing_type_2_jumping_label,char **parameterA,char **parameterB) {
    *addressing_type_2_jumping_label = strtok(original_operand, "(");
    *parameterA = strtok(NULL, ",");
    *parameterB = strtok(NULL, ")");
    if (!*addressing_type_2_jumping_label || !*parameterA || !*parameterB)
        return 0;
    for (; **parameterB; (*parameterB)++)
        /**/;
    if (*(--(*parameterB)) != ')')
        return 0;
    return 1;
}

int is_label_ok(char *label, int print_error) {
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
    for (; *pnt; pnt++) {
        if (!isalnum(*pnt))
            error = 2;
    }
    if (error == 2) {
        if (!print_error)
            return 0;
        insert_error_message(ERR_LABEL_NAME_IS_NOT_ALLOWED);
    }
    if (*--pnt != ':') {
        if (!print_error)
            return 0;
        insert_error_message(ERR_MISSING_COLON_AFTER_LABEL);
        error = 3;
    } else
        *pnt = '\0';
    if (mapping(label, op_names, (void **)op_code))
        /*label is operation name*/
        error = 4;
    if (mapping(label, register_names, (void **)register_code))
        /*label is register name*/
        error = 4;
    if (mapping(label, directives, (void **)directives_number))
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
    if (*string != '\"')
        return 0;
    for (; *string; string++)
        /**/;
    if (*--string != '\"')
        return 0;
    return 1;
}