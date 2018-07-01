#ifndef MBN_DEPARTMENT_H
#define MBN_DEPARTMENT_H

typedef struct department{
    char* department_name;
    char* department_manager;
    char* secretariat_tel;
    struct department* next;
} department;

department* add_department(department* head,char* department_name,char* department_manager,char* secretariat_tel);
department *remove_department(department *head, char *department_name);
department *find_department(department *head,char *department_name);

#endif //MBN_DEPARTMENT_H
