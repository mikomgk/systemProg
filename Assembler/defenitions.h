#ifndef ASSEMBLER_DEFENITIONS_H
#define ASSEMBLER_DEFENITIONS_H

#include <string.h>

#define WORD_SIZE 14
#define NUMBER_SIZE 12
#define LABEL_SIZE 31
#define LINE_SIZE 80
#define MAX_LINES 100
#define IC instructions_table_line[0]
#define DC data_table_line[0]
#define DATA "data"
#define STRING "string"
#define OPERATION "operation"
#define ENTRY "entry"
#define EXTERN "extern"

#define ERR_SPACE_BETWEEN_PARAMS errors[0]
#define ERR_MISSING_COMMA errors[1]
#define ERR_TOO_MANY_COMMAS errors[2]
#define ERR_COMMA_NOT_ALLOWED errors[3]
#define ERR_MISSING_QUOTATION_MARK errors[4]
#define ERR_TOO_MANY_QU errors[5]
#define ERR_WRONG_NUMBER_OF_OPERATORS errors[6]
#define ERR_LABEL_NAME_IS_NOT_ALLOWED errors[7]
#define ERR_LABEL_NAME_ALREADY_IN_USE errors[8]
#define ERR_LABEL_NAME_IS_SAVED_WORD errors[9]
#define ERR_MISSING_COLON_AFTER_LABEL errors[10]
#define ERR_LABEL_NAME_IS_NOT_EXIST errors[11]
#define ERR_WRONG_OPERATION_NAME errors[12]
#define ERR_ADDRESSING_MODE_IS_NOT_COMPATIBLE errors[013]
#define ERR_REGISTER_NOT_EXIST errors[14]
#define ERR_MISSING_OPERATION_NAME errors[15]
#define ERR_INVALID_INTEGER errors[16]
#define ERR_LABEL_NAME_IS_TOO_LONG errors[17]
#define ALERT_LABEL_MEANINGLESS alerts[1]
//TODO: number is too big

enum tables {
    INSTRUCTIONS_T, DATA_T, SYMBOL_T, ERROR_T
};

#endif //ASSEMBLER_DEFENITIONS_H
