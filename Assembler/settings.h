#ifndef ASSEMBLER_SETTINGS_H
#define ASSEMBLER_SETTINGS_H

char *addressing_13[] = {"1", "3"};
char *addressing_013[] = {"0", "1", "3"};
char *addressing_123[] = {"1", "2", "3"};
char *addressing_1[] = {"1"};

char *op_names[] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop", NULL};
char *op_code[] = {"....", ".../", "../.", "..//", "./..", "././", ".//.", ".///", "/...", "/../", "/./.", "/.//", "//..", "//./", "///.", "////", NULL};
char *num_of_operands_per_op[] = {"2", "2", "2", "2", "1", "1", "2", "1", "1", "1", "1", "1", "1", "1", "0", "0", NULL};
char **destination_operand_addressing_types_per_op[] = {addressing_13, addressing_013, addressing_13, addressing_13, addressing_13, addressing_13, addressing_13,
                                                 addressing_13, addressing_13, addressing_123, addressing_123, addressing_13, addressing_013,
                                                 addressing_123, NULL, NULL, NULL};
char **source_operand_addressing_types_per_op[] = {addressing_013, addressing_013, addressing_013, addressing_013, NULL, NULL, addressing_1, NULL, NULL, NULL,
                                                NULL, NULL, NULL, NULL, NULL, NULL, NULL};
char *register_names[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", NULL};
char *register_code[] = {"......", "...../ERROR:", "..../.", "....//", ".../..", "..././", "...//.", "...///", NULL};
char *addressing_types[] = {"0", "1", "2", "3", NULL};
char *addressing_types_code[] = {"..", "./", "/.", "//", NULL};
char *are[] = {"A", "R", "E"};
char *are_code[] = {"..", "/.", "./"};

char *directives[]={"data","string","extern","entry",NULL};
char *directives_number[]={"1","2","3","4",NULL};


char *errors[]={
        "ERROR: spaces between parameters",
        "ERROR: missing comma",
        "ERROR: too many commas",
        "ERROR: directive line must have a label",
        "ERROR: missing quotation mark",
        "ERROR: too many quotation marks",
        "ERROR: wrong number of operators",
        "ERROR: label name is not allowed",
        "ERROR: label name is already in use",
        "ERROR: label name is a saved word",
        "ERROR: expected \':\' after label name",
        "ERROR: label name is not exist",
        "ERROR: wrong operation name",
        "ERROR: addressing mode is not compatible with the given operation",
        "ERROR: number is too big",
        "ERROR: missing operation name",
        "ERROR: invalid integer",
        "ERROR: label name is too long",
        "ERROR: can't open file",
        "ERROR: not an assembly file",
        ""
};

char *alerts[]={
        "ALERT: label before .extern or .entry line is meaningless"
};

#endif //ASSEMBLER_SETTINGS_H
