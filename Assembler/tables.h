#ifndef ASSEMBLER_TABLE_H
#define ASSEMBLER_TABLE_H

#include "defenitions.h"

int instructions_table_line[MAX_LINES];
char instructions_table_string[MAX_LINES][WORD_SIZE];

int data_table_line[MAX_LINES];
char data_table_string[MAX_LINES][WORD_SIZE];

char symbol_table_label[MAX_LINES][LABEL_SIZE];
int symbol_table_address[MAX_LINES];

int error_log_table_data_line[MAX_LINES];
char* error_log_table_string[MAX_LINES];


void clear_tables();

#endif //ASSEMBLER_TABLE_H
