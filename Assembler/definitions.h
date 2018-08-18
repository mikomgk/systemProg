#ifndef ASSEMBLER_DEFINITIONS_H
#define ASSEMBLER_DEFINITIONS_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "settings.h"
#include "tables.h"
#include "text_handling.h"
#include "binary_word.h"

#define WORD_SIZE 14
#define NUMBER_SIZE 12
#define LABEL_SIZE 31
#define SYMBOL_TYPE_SIZE 10
#define LINE_SIZE 80
#define MAX_LINES 100
#define ADDRESSING_CODE_LENGTH 2
#define OP_CODE_LENGTH 4
#define ARE_CODE_LENGTH 2
#define REGISTER_CODE_LENGTH 6
#define ADDRESS_OFFSET 100
#define PARAMETER1_INDEX 0
#define PARAMETER2_INDEX 2
#define OPERATION_CODE_INDEX 4
#define SOURCE_OPERAND_ADDRESSING_INDEX 8
#define DESTINATION_OPERAND_ADDRESSING_INDEX 10
#define ARE_INDEX 12
#define SOURCE_REGISTER_INDEX 0
#define DESTINATION_REGISTER_INDEX 6
#define DATA "data"
#define STRING "string"
#define OPERATION "operation"
#define ENTRY "entry"
#define EXTERN "extern"
#define IMMEDIATE_ADDRESSING addressing_types[0]
#define REGISTER_ADDRESSING addressing_types[3]
#define JUMPING_ADDRESSING addressing_types[2]
#define LABEL_ADDRESSING addressing_types[1]
#define ASSEMBLY_EXTENSION ".as"
#define OBJECT_EXTENSION ".ob"
#define ENTRY_EXTENSION ".ent"
#define EXTERN_EXTENSION ".ext"
#define ABSOLUTE "A"
#define RELOCATABLE "R"
#define EXTERNAL "E"

#define ERR_SPACE_BETWEEN_PARAMS errors[0]
#define ERR_MISSING_COMMA errors[1]
#define ERR_TOO_MANY_COMMAS errors[2]
#define ERR_DIRECTIVE_LINE_MUST_HAVE_LABEL errors[3]
#define ERR_MISSING_QUOTATION_MARK errors[4]
#define ERR_LABEL_NAME_IS_TOO_LONG errors[5]
#define ERR_WRONG_NUMBER_OF_OPERATORS errors[6]
#define ERR_LABEL_NAME_IS_NOT_ALLOWED errors[7]
#define ERR_LABEL_NAME_ALREADY_IN_USE errors[8]
#define ERR_LABEL_NAME_IS_SAVED_WORD errors[9]
#define ERR_MISSING_COLON_AFTER_LABEL errors[10]
#define ERR_LABEL_NAME_IS_NOT_EXIST errors[11]
#define ERR_WRONG_OPERATION_NAME errors[12]
#define ERR_ADDRESSING_MODE_IS_NOT_COMPATIBLE errors[13]
#define ERR_NUMBER_IS_OUT_OF_RANGE errors[14]
#define ERR_MISSING_OPERATION_NAME errors[15]
#define ERR_INVALID_INTEGER errors[16]
#define ERR_CAN_NOT_OPEN_FILE errors[17]
#define ERR_NOT_AN_ASSEMBLY_FILE errors[18]
#define ERR_CAN_NOT_CREATE_FILE errors[19]
#define WARNING_LABEL_MEANINGLESS warnings[0]

extern int error_flag, biggest_long_number, biggest_short_number, smallest_long_number, smallest_short_number, has_label_flag, addressing_type_2_flag, number_of_registers, number_of_operators, LC;
extern char original_line[LINE_SIZE], assembler_name[LABEL_SIZE], file_name[FILENAME_MAX], *file_extension;

#endif /*ASSEMBLER_DEFINITIONS_H*/
