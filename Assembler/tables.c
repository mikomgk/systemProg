#include "tables.h"

void clear_tables() {
    int i = 0;
    for (; i < MAX_LINES; i++) {
        instructions_table_line[i] = -1;
        data_table_line[i] = -1;
        symbol_table_label[i][0] = '\0';
        error_log_table_data_line[i] = -1;
    }
}

void replace_line(enum tables table,int line,int int_data,char* string_data) {
    switch (table) {
        case INSTRUCTIONS:
            instructions_table_line[line] = int_data;
            strcpy(instructions_table_string[line], string_data);
            break;
        case DATA:
            data_table_line[line] = int_data;
            strcpy(data_table_string[line], string_data);
            break;
        case SYMBOL:
            strcpy(symbol_table_label[line], string_data);
            symbol_table_address[line] = int_data;
            break;
        case ERROR:
            error_log_table_data_line[line] = int_data;
            error_log_table_string[line] = string_data;
            break;
    }
}