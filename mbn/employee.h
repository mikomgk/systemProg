#ifndef MBN_EMPLOYEE_H
#define MBN_EMPLOYEE_H

#include "department.h"

typedef struct employee{
    int emp_number;
    int exp_years;
    department* department;
    struct employee* next;
} employee;

employee *add_employee(employee *head, int emp_number, int exp_years, char *department_name);
void add_new_department(char *department_name, char *department_manager, char *secretariat_tel);
void remove_a_department(char *department_name);
employee *merge_employees_lists(employee *e1, employee *e2);

#endif //MBN_EMPLOYEE_H
