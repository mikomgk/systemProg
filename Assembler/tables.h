#ifndef ASSEMBLER_TABLE_H
#define ASSEMBLER_TABLE_H

#include "defenitions.h"
//instructions table - line counter,binary string
int instructions_table_line[MAX_LINES];
char instructions_table_string[MAX_LINES][WORD_SIZE];

//data table - line counter,binary string
int data_table_line[MAX_LINES];
char data_table_string[MAX_LINES][WORD_SIZE];

//symbol table - label name,label address,symbol type
char symbol_table_label[MAX_LINES][LABEL_SIZE];
int symbol_table_address[MAX_LINES];
char symbol_table_type[MAX_LINES];

//error table - file line number,error description,original line with error
int error_table_data_line_number[MAX_LINES];
char* error_table_error_string[MAX_LINES];
char error_table_data_line[MAX_LINES][LINE_SIZE];


void clear_tables();
void replace_line(enum tables table, int int_data, char *string_data, char *string_data2);
int is_label_exist(char *label);

#endif //ASSEMBLER_TABLE_H
