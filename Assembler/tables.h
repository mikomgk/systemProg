#ifndef ASSEMBLER_TABLE_H
#define ASSEMBLER_TABLE_H

#include "definitions.h"

enum tables {
    INSTRUCTIONS_T, DATA_T, SYMBOL_T, ERROR_T
};

enum files {
    OBJECT_F, EXTERN_F, ENTRY_F
};

extern int *const ic;
extern int *const dc;

void clear_tables();
void replace_line(enum tables table, int int_data, char *string_data, char *string_data2);
int is_label_exist(char *label);
void update_words_addresses(int instructions_only, int program_offset);
void change_to_entry(char *label);
int get_symbol_address(char *label);
void write_errors(char *file_name);
void write_table_to_file(FILE *f, enum files file_type);
int is_external(char *label);

#endif /*ASSEMBLER_TABLE_H*/
