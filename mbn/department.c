#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <limits.h>
#include "department.h"

department *new_department();

department *add_department(department *head, char *department_name, char *department_manager, char *secretariat_tel) {
    department *d = new_department(), *ptr, dummy = {"", "", "", head};
    int compare;
    d->department_name = department_name;
    d->department_manager = department_manager;
    d->secretariat_tel = secretariat_tel;
    for (ptr = &dummy; ptr->next && (compare = strcmp(department_name, ptr->next->department_name)) > 0; ptr = ptr->next)
        /**/;
    if (compare != 0 && strcmp(d->department_name, ptr->department_name) != 0) {
        d->next = ptr->next;
        ptr->next = d;
    }
    return dummy.next;
}

department *remove_department(department *head, char *department_name) {
    department dummy = {"", "", "", head}, *ptr, *tmp;
    int compare = 1;
    for (ptr = &dummy; ptr->next && (compare = strcmp(department_name, ptr->next->department_name)) != 0; ptr = ptr->next)
        /**/;
    if (ptr->next != NULL && (compare == 0 || strcmp(department_name, ptr->next->department_name) == 0)) {
        tmp = ptr->next;
        ptr->next = ptr->next->next;
        free(tmp);
    }
    return dummy.next;
}

department *find_department(department *head, char *department_name) {
    department dummy = {"", "", "", head}, *ptr;
    int compare = 1;
    for (ptr = &dummy; ptr->next && (compare = strcmp(department_name, ptr->next->department_name)) != 0; ptr = ptr->next)
        /**/;
    if (ptr->next != NULL && (compare == 0 || strcmp(department_name, ptr->next->department_name) == 0))
        return ptr->next;
    return NULL;
}

department *new_department() {
    department *e = (department *) malloc(sizeof(department));
    if (e == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    return e;
}