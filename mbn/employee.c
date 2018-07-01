#include <stdlib.h>
#include <stdio.h>
#include "employee.h"

employee *new_employee();
void close_chain(employee *head);
void open_chain(employee *head);

department *departments;

employee *merge_employees_lists(employee *e1, employee *e2){
    employee e3, *p3=&e3;
    if(!e1)
        return e2;
    if(!e2)
        return e1;
    open_chain(e1);
    open_chain(e2);
    do{
        if(e1->emp_number<e2->emp_number){
            p3=p3->next=e1;
            e1=e1->next;
        }else{
            p3=p3->next=e2;
            e2=e2->next;
        }
    }while(e1&&e2);
    p3->next=e1?e1:e2;
    close_chain(e3.next);
    return e3.next;
}

employee *add_employee(employee *head, int emp_number, int exp_years, char *department_name) {
    department *department;
    employee *e, *ptr, dummy = {0, 0, NULL, head};
    if ((department = find_department(departments, department_name)) != NULL) {
        e = new_employee();
        e->emp_number = emp_number;
        e->exp_years = exp_years;
        e->department = department;
        open_chain(head);
        for (ptr = &dummy; ptr->next && emp_number > ptr->next->emp_number; ptr = ptr->next)
            /**/;
        if (!ptr->next || emp_number != ptr->next->emp_number) {
            e->next = ptr->next;
            ptr->next = e;
        }
        close_chain(dummy.next);
    }
    return dummy.next;
}

void close_chain(employee *head) {
    if (head) {
        employee *ptr;
        for (ptr = head; ptr->next; ptr = ptr->next)
            /**/;
        ptr->next = head;
    }
}

void open_chain(employee *head) {
    if (head) {
        employee *ptr;
        for (ptr = head; ptr->next != head; ptr = ptr->next)
            /**/;
        ptr->next = NULL;
    }
}

void add_new_department(char *department_name, char *department_manager, char *secretariat_tel) {
    departments = add_department(departments, department_name, department_manager, secretariat_tel);
}

void remove_a_department(char *department_name) {
    departments = remove_department(departments, department_name);
}

employee *new_employee() {
    employee *e = (employee *) malloc(sizeof(employee));
    if (e == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    return e;
}