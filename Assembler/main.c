#include <stdio.h>
#include <ctype.h>
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
    int LC, is_error, is_label;
    if (argc == 1)
        return 0;
    while (--argc > 0) {
        clear_tables();
        is_error = 0;
        if ((fp = fopen(*++argv, "r")) == NULL) {
            replace_line(ERROR, 0, file_not_open(*argv), NULL);
            is_error = 1;
        } else {
            LC = 0;
            while (fgets(line, LINE_SIZE, fp)) {
                strcpy(line_copy, line);
                trim(line_copy, 0);
                if (strlen(line_copy) == 0 || line_copy[0] == ';')
                    continue;
                if ((is_label = parser(line_copy, label, operation, operandA, operandB, LC, line)) < 0)
                    is_error = 1;
                if (is_label) {
                    if (is_label_exist(label)) {
                        replace_line(ERROR, LC, ERR_LABEL_NAME_ALREADY_IN_USE, line);
                        is_error=1;
                    }
                    else
                        replace_line(SYMBOL,)
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
    for (; *pnt && *pnt != '(' && *pnt != '\"'; pnt++) {
        if (*pnt == ' ')
            count_spaces++;
        if (*pnt == ',') {
            if (*(pnt + 1) == ',') {
                replace_line(ERROR, line_counter, ERR_TOO_MANY_COMMAS, line_original);
                is_label *= -1;
            } else
                *pnt = ' ';
        }
    }
    if (count_spaces == 0) {
        replace_line(ERROR, line_counter, ERR_MISSING_OPERATION_NAME, line_original);
        is_label *= is_label > 0 ? -1 : 1;
    } else if (count_spaces == 1)
        sscanf(line, "%s%s%s%s", operation, operandA, operandB, tmp);
    else if (count_spaces == 2) {
        sscanf(line, "%s%s%s%s%s", label, operation, operandA, operandB, tmp);
        is_label += is_label > 0 ? 1 : -1;
    } else {
        replace_line(ERROR, line_counter, ERR_MISSING_COMMA, line_original);
        is_label *= is_label > 0 ? -1 : 1;
    }
    if (tmp) {
        replace_line(ERROR, line_counter, ERR_WRONG_NUMBER_OF_OPERATORS, line_original);
        is_label *= is_label > 0 ? -1 : 1;
    }
    return is_label - 1;
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