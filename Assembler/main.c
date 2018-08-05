#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "settings.h"
#include "tables.h"

#define file_not_open(x) "e can't open "#x

void *mapping(char *word, char *words[], void *params[]);
int trim(char *word, int in_brackets);
void dec2bin(int num, char *word,int size_of_word);
int parser(char *line, char *label, char *operation, char *operandA, char *operandB, int line_counter, char *original_line,int *number_of_operators);
int is_label_ok(char* label,int line_counter,char *original_line);
int is_string_ok(char *string);
char* get_addressing_type(char *operand);

int main(int argc, char *argv[]) {
    FILE *fp;
    char line[LINE_SIZE], line_copy[LINE_SIZE], *label = NULL, *operation = NULL, *operandA = NULL, *operandB = NULL,long_number_string[WORD_SIZE],
            short_number_string[NUMBER_SIZE],binary_word[WORD_SIZE],*tmp,*operandA_type,*operandB_type,**addressin_options;
    int LC, error_flag, has_label_flag,label_exist_flag,label_ok_flag,number,number_of_words,number_of_operators,number_of_register;
    if (argc == 1)
        return 0;
    while (--argc > 0) {
        clear_tables();
        error_flag = 0;
        has_label_flag=0;
        label_exist_flag=0;
        //open file
        if ((fp = fopen(*++argv, "r")) == NULL) {
            replace_line(ERROR_T, 0, file_not_open(*argv), NULL);
            error_flag = 1;
        } else {
            LC = 0;
            //get next line
            while (fgets(line, LINE_SIZE, fp)) {
                LC++;
                number_of_words = 0;
                number_of_operators=0;
                strcpy(line_copy, line);
                trim(line_copy, 0);
                //empty line or comment line
                if (strlen(line_copy) == 0 || line_copy[0] == ';')
                    continue;
                //parse line and checks error
                if ((has_label_flag = parser(line_copy, label, operation, operandA, operandB, LC, line,&number_of_operators)) < 0)
                    error_flag = 1;
                has_label_flag = has_label_flag * (has_label_flag < 0 ? -1 : 1) - 1;
                if (has_label_flag) {
                    //TODO: has a label
                }
                //label already exist
                if (!(label_ok_flag = is_label_ok(label, LC, line))) {
                    error_flag = 1;
                } else if ((label_exist_flag = has_label_flag ? is_label_exist(label) : 0))
                    replace_line(ERROR_T, LC, ERR_LABEL_NAME_ALREADY_IN_USE, line);
                error_flag = 1;
                //directive line
                if (*operation == '.') {
                    if (!strcmp((operation + 1), DATA)) {
                        if (label_ok_flag&&!label_exist_flag)
                            replace_line(SYMBOL_T, DC, label, DATA);
                        //too many operands
                        if (operandB) {
                            replace_line(ERROR_T, LC, ERR_WRONG_NUMBER_OF_OPERATORS, line);
                            error_flag = 1;
                            operandB = NULL;
                        } else
                            for (operandA = strtok(operandA, ","); *operandA; operandA = strtok(NULL, ",")) {
                                //TODO: too big number
                                number = (int) strtol(operandA, operandB, 10);
                                //not an int
                                if (operandB) {
                                    replace_line(ERROR_T, LC, ERR_INVALID_INTEGER, line);
                                    error_flag = 1;
                                    break;
                                } else {
                                    //enter binary number
                                    dec2bin(number, long_number_string, WORD_SIZE);
                                    replace_line(DATA_T, 0, long_number_string, NULL);
                                }
                            }
                    } else if (!strcmp((operation + 1), STRING)) {
                        if (label_ok_flag&&!label_exist_flag)
                            replace_line(SYMBOL_T, DC, label, DATA);
                        //too many operands
                        if (operandB) {
                            replace_line(ERROR_T, LC, ERR_WRONG_NUMBER_OF_OPERATORS, line);
                            error_flag = 1;
                            operandB = NULL;
                        } else if (!is_string_ok(operandA)) {
                            replace_line(ERROR_T, LC, ERR_MISSING_QUOTATION_MARK, line);
                            error_flag = 1;
                        } else
                            for (operandA++; *operandA; operandA++) {
                                dec2bin(*operandA, long_number_string, WORD_SIZE);
                                replace_line(DATA_T, 0, long_number_string, NULL);
                            }
                    } else if (!strcmp((operation + 1), ENTRY)) {
                        if (has_label_flag)
                            replace_line(ERROR_T, LC, ALERT_LABEL_MEANINGLESS, line);
                    } else if (!strcmp((operation + 1), EXTERN)) {
                        if (has_label_flag)
                            replace_line(ERROR_T, LC, ALERT_LABEL_MEANINGLESS, line);
                        if (operandB) {
                            replace_line(ERROR_T, LC, ERR_WRONG_NUMBER_OF_OPERATORS, line);
                            error_flag = 1;
                            operandB = NULL;
                        } else if (!is_label_ok(operandA, LC, line)) {
                            error_flag = 1;
                        } else if (is_label_exist(operandA)) {
                            //label already exist
                            replace_line(ERROR_T, LC, ERR_LABEL_NAME_ALREADY_IN_USE, line);
                            error_flag = 1;
                        } else {
                            replace_line(SYMBOL_T, 0, operandA, EXTERN);
                        }
                    } else {
                        replace_line(ERROR_T, LC, ERR_WRONG_OPERATION_NAME, line);
                        error_flag = 1;
                    }
                } else {
                    if(label_ok_flag&&!label_exist_flag)
                        replace_line(SYMBOL_T, DC, label, OPERATION);
                    //operation line
                    if((tmp=(char*)mapping(operation,op_names,op_code))!=NULL)
                        strcpy(binary_word+4,tmp);
                    else{
                        //wrong operation name
                        replace_line(ERROR_T,LC,ERR_WRONG_OPERATION_NAME,line);
                        error_flag=1;
                        continue;
                    }
                    switch(atoi((char*)mapping(operation,op_names,num_of_operands_per_op))){
                        //wrong number of operators
                        case 0:
                            if(operandA){
                                replace_line(ERROR_T,LC,ERR_WRONG_NUMBER_OF_OPERATORS,line);
                                error_flag=1;
                                number_of_operators=-1;
                            }
                            else {
                                number_of_operators = 0;
                                strcpy(binary_word + 8, "....");
                            }
                            break;
                        case 1:
                            if(operandB){
                                replace_line(ERROR_T,LC,ERR_WRONG_NUMBER_OF_OPERATORS,line);
                                error_flag=1;
                                number_of_operators=-1;
                            }
                            else {
                                number_of_operators=1;
                                strcpy(binary_word + 8, "..");
                                operandA_type=get_addressing_type(operandA);
                                addressin_options=mapping(operation,op_names,dest_operand_addressing_types_per_op);
                                if(mapping(operandA_type,addressin_options,addressin_options)){
                                    //correct addressing type
                                    if((tmp=(char*)mapping(operandA_type,addressing_types,addressing_types_code)))
                                        strcpy(binary_word+10,tmp);
                                }

                            }
                            break;
                        case 2:
                            if(number_of_operators==0)
                                number_of_operators=2;
                        default:
                            number_of_operators=-1;
                    }
                    if(number_of_operators!=-1){

                    }

                }
            }
            fclose(fp);
        }
        //TODO: create error file
    }
    return 0;
}

int parser(char *line, char *label, char *operation, char *operandA, char *operandB, int line_counter, char *original_line,int *number_of_operators) {
    int is_label = 1, count_spaces = 0;
    char *pnt = line, *tmp = NULL;
    label = NULL;
    operation = NULL;
    operandA = NULL;
    operandB = NULL;
    //convert commas with space
    for (; *pnt && *pnt != '(' && *pnt != '\"'; pnt++) {
        //TODO: check number array with nd without label
        if (count_spaces == 1 && isdigit(*pnt))
            break;
        if (*pnt == ' ')
            count_spaces++;
        if (*pnt == ',') {
            if (*(pnt + 1) == ',') {
                replace_line(ERROR_T, line_counter, ERR_TOO_MANY_COMMAS, original_line);
                is_label *= -1;
            } else
                *pnt = ' ';
        }
    }
    //one word in line
    if (count_spaces == 0) {
        replace_line(ERROR_T, line_counter, ERR_MISSING_OPERATION_NAME, original_line);
        is_label *= is_label > 0 ? -1 : 1;
    } else if (count_spaces == 1)
        sscanf(line, "%s%s%s%s", operation, operandA, operandB, tmp);
    else if (count_spaces == 2) {
        sscanf(line, "%s%s%s%s%s", label, operation, operandA, operandB, tmp);
        is_label += is_label > 0 ? 1 : -1;
    } else {
        replace_line(ERROR_T, line_counter, ERR_MISSING_COMMA, original_line);
        is_label *= is_label > 0 ? -1 : 1;
    }
    if (tmp) {
        replace_line(ERROR_T, line_counter, ERR_WRONG_NUMBER_OF_OPERATORS, original_line);
        is_label *= is_label > 0 ? -1 : 1;
        *number_of_operators=-1;
    }
    return is_label;
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
    for (; isspace(*word); word++)
        /**/;
    for (; *word; *ptr++ = *word++)
        /**/;
    for (--word; isspace(*ptr); ptr--)
        /**/;
    *++ptr = '\0';
    for (ptr = word = start; *word; *ptr++ = *word++) {
        if (!in_brackets && *word == '\"') {
            for (; *word != '\"'; *ptr++ = *word++)
                /**/;
            continue;
        }
        if (!in_brackets && *word == '(') {
            for (; *word != ')'; *ptr++ = *word++)
                /**/;
            continue;
        }
        if (isspace(*word)) {
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

void dec2bin(int num, char *word,int size_of_word) {
    int mask = 1, i;
    for (i = size_of_word - 1; i >= 0; i--, mask <<= 1)
        if (num & mask)
            word[i] = '/';
        else
            word[i] = '.';
}

int is_label_ok(char* label,int line_counter,char *original_line) {
    int error = 0;
    char *pnt = label;
    if (strlen(pnt) > LABEL_SIZE + 1) {
        replace_line(ERROR_T, line_counter, ERR_LABEL_NAME_IS_TOO_LONG, original_line);
        error = 1;
    }
    if (!isalpha(*pnt++))
        error = 2;
    for (; *pnt; pnt++) {
        if (!isalnum(*pnt))
            error = 2;
    }
    if (*--label != ':')
        error = 2;
    else
        *pnt == '\0';
    if (error == 2)
        replace_line(ERROR_T, line_counter, ERR_LABEL_NAME_IS_NOT_ALLOWED, original_line);
    if (mapping(label, op_names, op_code))
        error = 3;
    if (mapping(label, register_names, register_code))
        error = 3;
    if (mapping(label, directives, directives_number))
        error = 3;
    if (error == 3)
        replace_line(ERROR_T, line_counter, ERR_LABEL_NAME_IS_SAVED_WORD, original_line);
    return error ? 0 : 1;
}

int is_string_ok(char *string) {
    int is_ok = 1;
    if (*string != '\"')
        is_ok = 0;
    for (; *string; string++)
        /**/;
    if (*--string != '\"')
        is_ok = 0;
    *string = '\0';
    return is_ok;
}

char* get_addressing_type(char *operand){
    if(*operand=='#')
        return addressing_types[0];
    if(mapping(operand,register_names,register_names))
        return addressing_types[3];
    for(;*operand;operand++)
        if(*operand=='(')
            return addressing_types[2];
    return addressing_types[1];
}