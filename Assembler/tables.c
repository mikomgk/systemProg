#include "tables.h"

void clear_tables() {
    int i;
    instructions_table_address[0] = 0;
    data_table_address[0] = 0;
    symbol_table_address[0] = 0;
    error_table_data_line_number[0] = 0;

    for (i = 1; i < MAX_LINES; i++) {
        instructions_table_address[i] = -1;
        data_table_address[i] = -1;
        symbol_table_address[i] = -1;
        error_table_data_line_number[i] = -1;
    }
}

void replace_line(enum tables table, int int_data, char *string_data, char *string_data2) {
    int line;
    switch (table) {
        case INSTRUCTIONS_T:
            line = instructions_table_address[0] + 1;
            instructions_table_address[line] = line - 1;
            strcpy(instructions_table_word[line], string_data);
            instructions_table_address[0]++;
            break;
        case DATA_T:
            line = data_table_address[0] + 1;
            data_table_address[line] = line - 1;
            strcpy(data_table_word[line], string_data);
            data_table_address[0]++;
            break;
        case SYMBOL_T:
            line = symbol_table_address[0] + 1;
            strcpy(symbol_table_label[line], string_data);
            symbol_table_address[line] = int_data;
            strcpy(symbol_table_type[line], string_data2);
            symbol_table_address[0]++;
            break;
        case ERROR_T:
            line = error_table_data_line_number[0] + 1;
            error_table_data_line_number[line] = int_data;
            error_table_error_string[line] = string_data;
            strcpy(error_table_data_line[line], string_data2);
            error_table_data_line_number[0]++;
            break;
    }
}

void write_table_to_file(FILE *f,enum files file_type) {
    int i;
    switch (file_type) {
        case OBJECT_F:
            update_words_addresses(0, BEGINNING_ADDRESS);
            fprintf(f, "%d %d", instructions_table_address[0], data_table_address[0]);
            for (i = 1; i <= instructions_table_address[0]; i++) {
                fprintf(f, "\n%.4d\t%s", instructions_table_address[i], instructions_table_word[i]);
            }
            for (i = 1; i <= data_table_address[0]; i++) {
                fprintf(f, "\n%.4d\t%s", data_table_address[i], data_table_word[i]);
            }
            break;
        case EXTERN_F:
            for(i=1;i<symbol_table_address[0];i++){
                if(!strcmp(symbol_table_type[i],EXTERN))
                    fprintf(f,"%s %d",symbol_table_label[i],symbol_table_address[i]);
            }
            break;
        case ENTRY_F:
            for(i=1;i<symbol_table_address[0];i++){
                if(!strcmp(symbol_table_type[i],ENTRY))
                    fprintf(f,"%s %d",symbol_table_label[i],symbol_table_address[i]);
            }
            break;
    }
}

int is_label_exist(char *label) {
    int i = 1;
    for (; i <= symbol_table_address[0]; i++)
        if (!strcmp(label, symbol_table_label[i])) {
            return 1;
        }
    return 0;
}

void update_words_addresses(int only_data_table,int delta) {
    int i;
    if (!only_data_table)
        for (i = 1; i <= instructions_table_address[0]; i++)
            instructions_table_address[i] += delta;
    for (i = 1; i <= data_table_address[0]; i++)
        data_table_address[i] += delta;
}

void change_to_entry(char *label){
    int i=1;
    for(;i<=symbol_table_address[0];i++)
        if(!strcmp(label,symbol_table_label[i])) {
            strcpy(symbol_table_type[i], ENTRY);
            return;
        }
}

int get_symbol_address(char *label){
    int i=1;
    for(;i<=symbol_table_address[0];i++)
        if(!strcmp(symbol_table_label[i],label))
            return symbol_table_address[i];
    return -1;
}

void write_errors(char *file_name) {
    int i = 1;
    for (; i <= error_table_data_line_number[0]; i++)
        fprintf(stderr, "%s:%d: %s\n\t%s\n\n", file_name, error_table_data_line_number[i], error_table_error_string[i], error_table_data_line[i]);
}

int is_external(char *label){
    int i=1;
    for(;i<=symbol_table_address[0];i++)
        if(!strcmp(label,symbol_table_label[i])) {
            return !strcmp(symbol_table_type[i],EXTERN);
        }
}