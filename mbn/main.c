#include <stdio.h>
#include <memory.h>

#include "employee.h"

int main() {
    add_new_department("4","4","4");
    add_new_department("3","3","3");
    add_new_department("2","2","2");
    add_new_department("1","1","1");
    remove_a_department("34");

    employee *my_employees=NULL;
    my_employees=add_employee(my_employees,123,3,"2");
    employee *my_employees2=NULL;
    my_employees2=add_employee(my_employees2,100,3,"2");

    employee *a=merge_employees_lists(my_employees,my_employees2);
    return 0;
}