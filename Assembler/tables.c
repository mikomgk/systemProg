#include "tables.h"

void clear_tables() {
    int i;
    instructions_table_line[0] = 0;
    data_table_line[0] = 0;
    symbol_table_address[0] = 0;
    error_table_data_line_number[0] = 0;

    for (i = 1; i < MAX_LINES; i++) {
        instructions_table_line[i] = -1;
        data_table_line[i] = -1;
        symbol_table_address[i] = -1;
        error_table_data_line_number[i] = -1;
    }
}

void replace_line(enum tables table, int int_data, char *string_data, char *string_data2) {
    int line;
    switch (table) {
        case INSTRUCTIONS:
            line = instructions_table_line[0] + 1;
            instructions_table_line[line] = int_data;
            strcpy(instructions_table_string[line], string_data);
            instructions_table_line[0]++;
            break;
        case DATA:
            line = data_table_line[0] + 1;
            data_table_line[line] = int_data;
            strcpy(data_table_string[line], string_data);
            data_table_line[0]++;
            break;
        case SYMBOL:
            line = symbol_table_address[0] + 1;
            strcpy(symbol_table_label[line], string_data);
            symbol_table_address[line] = int_data;
            symbol_table_address[0]++;
            break;
        case ERROR:
            line = error_table_data_line_number[0] + 1;
            error_table_data_line_number[line] = int_data;
            error_table_error_string[line] = string_data;
            strcpy(error_table_data_line[line], string_data2);
            error_table_data_line_number[0]++;
            break;
    }
}

int is_label_exist(char *label) {
    int i = 1, result = 0;
    for (; i <= symbol_table_address[0]; i++)
        if (!strcmp(label, symbol_table_label[i])) {
            result = 1;
            break;
        }
    return result;
}