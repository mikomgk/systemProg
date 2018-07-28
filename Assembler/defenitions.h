#ifndef ASSEMBLER_DEFENITIONS_H
#define ASSEMBLER_DEFENITIONS_H

#include <string.h>

#define WORD_SIZE 14
#define NUMBER_SIZE 12
#define LABEL_SIZE 31
#define MAX_LINES 100
//TODO:  errors list
#define err_1 "                     ergfror           fld                fds                 "

enum tables {
    INSTRUCTIONS, DATA, SYMBOL, ERROR
};

#endif //ASSEMBLER_DEFENITIONS_H
