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

/*
 * cleans all data in all tables
 */
void clear_tables();

/*
 * inserts string_data into table table in the next line
 * if table is INSTRUCTIONS_T or DATA_T next line line is *ic / *dc +1
 * when finish increases *ic and *dc
 * if table is SYMBOL_T int_data is label address and string_data2 is label type
 * if table is ERROR_T int_data is line number and string_data2 is original line from file
 */
void insert_line(enum tables table, int int_data, char *string_data, char *string_data2);

/*
 * returns 1 if label exists in SYMBOL_T, 0 if not
 */
int is_label_exist(char *label);

/*
 * if instructions_only is non-zero
 * increase instructions addresses and EXTERN symbols by program_offset
 * if instructions_only is 0
 * increase data addresses DATA symbols addresses by *ic + program_offset and OPERATION symbols addresses by program_offset
 */
void update_words_addresses(int instructions_only, int program_offset);

/*
 * changes label type to ENTRY if exist
 */
void change_to_entry(char *label);

/*
 * returns label address, -1 if not exist
 */
int get_symbol_address(char *label);

/*
 * write all errors to stderr
 * if there are no errors - do nothing
 */
void write_errors(char *file_name);

/*
 * writes file_type into file f
 */
void write_table_to_file(FILE *f, enum files file_type);

/*
 * return 1 if label type is EXTERN, 0 if not
 */
int is_external(char *label);

/*
 * add extern label occurrence to SYMBOL_T
 */
void add_extern_occurrence(char *label);

#endif /*ASSEMBLER_TABLE_H*/
