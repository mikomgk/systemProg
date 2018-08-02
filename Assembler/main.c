#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "settings.h"
#include "tables.h"

#define file_not_open(x) "e can't open "#x

void *mapping(char *word, char *words[], void *params[]);

int trim(char *word, int in_brackets);

void dec2bin(int num, char *word);

int parser(char *line, char *label, char *operation, char *operandA, char *operandB, int line_counter, char *line_original);

int main(int argc, char *argv[]) {
    FILE *fp;
    char line[LINE_SIZE], line_copy[LINE_SIZE], *label = NULL, *operation = NULL, *operandA = NULL, *operandB = NULL;
    int LC,tmp, error_flag, has_label_flag,label_exist_flag,number;
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
                strcpy(line_copy, line);
                trim(line_copy, 0);
                //empty line or comment line
                if (strlen(line_copy) == 0 || line_copy[0] == ';')
                    continue;
                //parse line and checks error
                if ((has_label_flag = parser(line_copy, label, operation, operandA, operandB, LC, line)) < 0)
                    error_flag = 1;
                if(has_label_flag){

                }
                has_label_flag=has_label_flag*(has_label_flag<0?-1:1)-1;
                if((label_exist_flag=has_label_flag?is_label_exist(label):0)){
                    replace_line(ERROR_T,LC,ERR_LABEL_NAME_ALREADY_IN_USE,line);
                    error_flag=1;
                }
                //directive line
                if(*operation=='.') {
                    if (!strcmp((operation + 1), DATA)) {
                        if(has_label_flag)
                            replace_line(SYMBOL_T,DC,label,DATA);
                        if(operandB) {
                            replace_line(ERROR_T, LC, ERR_WRONG_NUMBER_OF_OPERATORS, line);
                            error_flag = 1;
                            operandB=NULL;
                        } else
                        for(operandA=strtok(operandA,",");*operandA;operandA=strtok(NULL,",")) {
                            number = (int) strtol(operandA, operandB, 10);
                            if(operandB){
                                replace_line(ERROR_T,LC,ERR_INVALID_INTEGER,line);
                                error_flag=1;
                                break;
                            }
                        }
                    } else if (!strcmp((operation + 1), STRING)) {

                    } else if (!strcmp((operation + 1), ENTRY)) {

                    } else if (!strcmp((operation + 1), EXTERN)) {

                    } else {
                        replace_line(ERROR_T,LC,ERR_WRONG_OPERATION_NAME,line);
                        error_flag=1;
                    }
                }

                //there is a label in line
                if (has_label_flag) {
                    //already used label
                    if (is_label_exist(label)) {
                        replace_line(ERROR_T, LC, ERR_LABEL_NAME_ALREADY_IN_USE, line);
                        error_flag=1;
                    }
                    //new label
                    else
                        replace_line(SYMBOL_T,)
                }





                LC++;
            }
            fclose(fp);
        }
        //TODO: create error file
    }
    return 0;
}

int parser(char *line, char *label, char *operation, char *operandA, char *operandB, int line_counter, char *line_original) {
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
                replace_line(ERROR_T, line_counter, ERR_TOO_MANY_COMMAS, line_original);
                is_label *= -1;
            } else
                *pnt = ' ';
        }
    }
    //one word in line
    if (count_spaces == 0) {
        replace_line(ERROR_T, line_counter, ERR_MISSING_OPERATION_NAME, line_original);
        is_label *= is_label > 0 ? -1 : 1;
    } else if (count_spaces == 1)
        sscanf(line, "%s%s%s%s", operation, operandA, operandB, tmp);
    else if (count_spaces == 2) {
        sscanf(line, "%s%s%s%s%s", label, operation, operandA, operandB, tmp);
        is_label += is_label > 0 ? 1 : -1;
    } else {
        replace_line(ERROR_T, line_counter, ERR_MISSING_COMMA, line_original);
        is_label *= is_label > 0 ? -1 : 1;
    }
    if (tmp) {
        replace_line(ERROR_T, line_counter, ERR_WRONG_NUMBER_OF_OPERATORS, line_original);
        is_label *= is_label > 0 ? -1 : 1;
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

void dec2bin(int num, char *word) {
    int mask = 1, i;
    for (i = NUMBER_SIZE - 1; i >= 0; i--, mask <<= 1)
        if (num & mask)
            word[i] = '/';
        else
            word[i] = '.';
}