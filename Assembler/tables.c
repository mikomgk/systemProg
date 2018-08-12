#include "tables.h"

/*instructions table - line counter,binary string*/
int instructions_table_address[MAX_LINES];
char instructions_table_word[MAX_LINES][WORD_SIZE];

/*data table - line counter,binary string*/
int data_table_address[MAX_LINES];
char data_table_word[MAX_LINES][WORD_SIZE];

/*symbol table - label name,label address,symbol type*/
char symbol_table_label[MAX_LINES][LABEL_SIZE];
int symbol_table_address[MAX_LINES];
char symbol_table_type[MAX_LINES][SYMBOL_TYPE_SIZE];

/*error table - file line number,error description,original line with error*/
int error_table_data_line_number[MAX_LINES];
char *error_table_error_string[MAX_LINES];
char error_table_data_line[MAX_LINES][LINE_SIZE];

int *const ic = instructions_table_address;
int *const dc = data_table_address;
int *const sc = symbol_table_address;
int *const ec = error_table_data_line_number;

void clear_tables() {
    int i;
    *ic = 0;
    *dc = 0;
    *sc = 0;
    *ec = 0;
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
            line = *ic + 1;
            instructions_table_address[line] = line - 1;
            strcpy(instructions_table_word[line], string_data);
            (*ic)++;
            break;
        case DATA_T:
            line = *dc + 1;
            data_table_address[line] = line - 1;
            strcpy(data_table_word[line], string_data);
            (*dc)++;
            break;
        case SYMBOL_T:
            line = *sc + 1;
            strcpy(symbol_table_label[line], string_data);
            symbol_table_address[line] = int_data;
            strcpy(symbol_table_type[line], string_data2);
            (*sc)++;
            break;
        case ERROR_T:
            line = *ec + 1;
            error_table_data_line_number[line] = int_data;
            error_table_error_string[line] = string_data;
            strcpy(error_table_data_line[line], string_data2);
            (*ec)++;
            break;
    }
}

void write_table_to_file(FILE *f, enum files file_type) {
    int i;
    switch (file_type) {
        case OBJECT_F:
            update_words_addresses(0, BEGINNING_ADDRESS);
            fprintf(f, "%d %d", *ic, *dc);
            for (i = 1; i <= *ic; i++) {
                fprintf(f, "\n%.4d\t%s", instructions_table_address[i], instructions_table_word[i]);
            }
            for (i = 1; i <= *dc; i++) {
                fprintf(f, "\n%.4d\t%s", data_table_address[i], data_table_word[i]);
            }
            break;
        case EXTERN_F:
            for (i = 1; i < *sc; i++) {
                if (!strcmp(symbol_table_type[i], EXTERN))
                    fprintf(f, "%s %d", symbol_table_label[i], symbol_table_address[i]);
            }
            break;
        case ENTRY_F:
            for (i = 1; i < *sc; i++) {
                if (!strcmp(symbol_table_type[i], ENTRY))
                    fprintf(f, "%s %d", symbol_table_label[i], symbol_table_address[i]);
            }
            break;
    }
}

int is_label_exist(char *label) {
    int i = 1;
    for (; i <= *sc; i++)
        if (!strcmp(label, symbol_table_label[i])) {
            return 1;
        }
    return 0;
}

void update_words_addresses(int only_data_table, int delta) {
    int i;
    if (!only_data_table)
        for (i = 1; i <= *ic; i++)
            instructions_table_address[i] += delta;
    for (i = 1; i <= *dc; i++)
        data_table_address[i] += delta;
}

void change_to_entry(char *label) {
    int i = 1;
    for (; i <= *sc; i++)
        if (!strcmp(label, symbol_table_label[i])) {
            strcpy(symbol_table_type[i], ENTRY);
            return;
        }
}

int get_symbol_address(char *label) {
    int i = 1;
    for (; i <= *sc; i++)
        if (!strcmp(symbol_table_label[i], label))
            return symbol_table_address[i];
    return -1;
}

void write_errors(char *file_name) {
    int i = 1;
    for (; i <= *ec; i++)
        fprintf(stderr, "%s: %s:%d: %s\n\t%s\n\n", assembler_name, file_name, error_table_data_line_number[i], error_table_error_string[i], error_table_data_line[i]);
}

int is_external(char *label) {
    int i = 1;
    for (; i <= *sc; i++)
        if (!strcmp(label, symbol_table_label[i])) {
            return !strcmp(symbol_table_type[i], EXTERN);
        }
    return 0;
}