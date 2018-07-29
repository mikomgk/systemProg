#ifndef ASSEMBLER_SETTINGS_H
#define ASSEMBLER_SETTINGS_H

char *addressing_13[] = {"1", "3"};
char *addressing_013[] = {"0", "1", "3"};
char *addressing_123[] = {"1", "2", "3"};
char *addressing_1[] = {"1"};

char *op_names[] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop", NULL};
char *op_code[] = {"....", ".../", "../.", "..//", "./..", "././", ".//.", ".///", "/...", "/../", "/./.", "/.//", "//..", "//./", "///.", "////", NULL};
char *num_of_operands_per_op[] = {"2", "2", "2", "2", "1", "1", "2", "1", "1", "1", "1", "1", "1", "1", "0", "0", NULL};
char **dest_operand_addressing_types_per_op[] = {addressing_13, addressing_013, addressing_13, addressing_13, addressing_13, addressing_13, addressing_13,
                                                 addressing_13, addressing_13, addressing_123, addressing_123, addressing_13, addressing_013,
                                                 addressing_123, NULL, NULL, NULL};
char **src_operand_addressing_types_per_op[] = {addressing_013, addressing_013, addressing_013, addressing_013, NULL, NULL, addressing_1, NULL, NULL, NULL,
                                                NULL, NULL, NULL, NULL, NULL, NULL, NULL};
char *register_names[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", NULL};
char *register_code[] = {"......", "...../", "..../.", "....//", ".../..", "..././", "...//.", "...///", NULL};
char *addressing_types[] = {"0", "1", "2", "3", NULL};
char *addressing_types_code[] = {"..", "./", "/.", "//", NULL};
char *are[] = {"A", "R", "E"};
char *are_code[] = {"..", "/.", "./"};

char *errors[]={
        "e spaces between parameters",
        "e missing comma",
        "e too many commas",
        "e comma not allowed",
        "e missing quotation mark",
        "e too many quotation marks",
        "e wrong number of operators",
        "e label name is not allowed",
        "e label name is already in use",
        "e label name is a saved word",
        "e expected \':\' after label name",
        "e label name is not exist",
        "e wrong operation name",
        "e addressing mode is not compatible with the given operation",
        "e register is not exist",
        "e missing operation name"
};

char *alerts[]={
        "a label before .extern or .entry line is meaningless"
};

#endif //ASSEMBLER_SETTINGS_H
