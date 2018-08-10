#ifndef ASSEMBLER_DEFENITIONS_H
#define ASSEMBLER_DEFENITIONS_H

#include <stdio.h>
#include <string.h>

#define WORD_SIZE 14
#define NUMBER_SIZE 12
#define LABEL_SIZE 31
#define SYMBOL_TYPE_SIZE 8
#define LINE_SIZE 80
#define MAX_LINES 100
#define BEGINNING_ADDRESS 100
#define SOURCE_OPERAND_ADDRESSING_INDEX 8
#define DESTINATION_OPERAND_ADDRESSING_INDEX 10
#define DESTINATION_REGISTER_INDEX 6
#define ARE_INDEX 12
#define IC instructions_table_address[0]
#define DC data_table_address[0]
#define SC symbol_table_address[0]
#define DATA "data"
#define STRING "string"
#define OPERATION "operation"
#define ENTRY "entry"
#define EXTERN "extern"
#define IMMEDIATE_ADDRESSING addressing_types[0]
#define REGISTER_ADDRESSING addressing_types[3]
#define JUMPING_ADDRESSING addressing_types[2]
#define LABEL_ADDRESSING addressing_types[1]
#define ASSEMBLEY_EXTENTION ".as"
#define OBJECT_EXTENTION ".ob"
#define ENTRY_EXTENTION ".ent"
#define EXTERN_EXTENTION ".ext"

#define ERR_SPACE_BETWEEN_PARAMS errors[0]
#define ERR_MISSING_COMMA errors[1]
#define ERR_TOO_MANY_COMMAS errors[2]
#define ERR_COMMA_NOT_ALLOWED errors[3]
#define ERR_MISSING_QUOTATION_MARK errors[4]
#define ERR_TOO_MANY_QUOTATION_MARKS errors[5]
#define ERR_WRONG_NUMBER_OF_OPERATORS errors[6]
#define ERR_LABEL_NAME_IS_NOT_ALLOWED errors[7]
#define ERR_LABEL_NAME_ALREADY_IN_USE errors[8]
#define ERR_LABEL_NAME_IS_SAVED_WORD errors[9]
#define ERR_MISSING_COLON_AFTER_LABEL errors[10]
#define ERR_LABEL_NAME_IS_NOT_EXIST errors[11]
#define ERR_WRONG_OPERATION_NAME errors[12]
#define ERR_ADDRESSING_MODE_IS_NOT_COMPATIBLE errors[13]
#define ERR_REGISTER_NOT_EXIST errors[14]
#define ERR_MISSING_OPERATION_NAME errors[15]
#define ERR_INVALID_INTEGER errors[16]
#define ERR_LABEL_NAME_IS_TOO_LONG errors[17]
#define ERR_CAN_NOT_OPEN_FILE errors[18]
#define ERR_NOT_AN_ASSEMBLEY_FILE errors[19]
#define ALERT_LABEL_MEANINGLESS alerts[1]
//TODO: number is too big

enum tables {
    INSTRUCTIONS_T, DATA_T, SYMBOL_T, ERROR_T
};

enum files{
    OBJECT_F,EXTERN_F,ENTRY_F
};

#endif //ASSEMBLER_DEFENITIONS_H
