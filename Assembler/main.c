#include <stdio.h>
#include <ctype.h>
#include "settings.h"
#include "tables.h"

void *mapping(char *word, char *words[], void *params[]);
int trim(char *word, int in_brackets);
void dec2bin(int num, char *word);

int main() {
    char a[100]=err_1;
    trim(a,0);
    puts(a);
    return 0;
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