#include <stdlib.h>
#include <stdio.h>
#include "member.h"


member *new_member();

members_list *add_member(members_list *list, int id, int cost, int time) {
    member dummy = {0, 0, 0, NULL, list->head}, *ptr, *m = new_member();
    int different;
    m->id = id;
    m->cost = cost;
    m->time = time;
    for (ptr = &dummy; ptr->next && (different = m->id - ptr->next->id) > 0; ptr = ptr->next)
        /**/;
    if (!ptr->next || different < 0) {
        m->next = ptr->next;
        m->prev = ptr;
        if (ptr->next)
            ptr->next->prev = m;
        else
            list->tail = m;
        ptr->next = m;
    }
    (list->head = dummy.next)->prev=NULL;
    return list;
}

members_list *remove_member_id(members_list *list, int id) {
    member dummy = {0, 0, 0, NULL, list->head}, *ptr,*tmp;
    for (ptr = &dummy; ptr->next && id != ptr->next->id; ptr = ptr->next)
        /**/;
    if (!ptr->next)
        printf("there's no such member");
    else {
        tmp=ptr->next;
        if (ptr->next->next)
            ptr->next->next->prev = ptr;
        else
            list->tail = ptr;
        ptr->next = ptr->next->next;
        free(tmp);
    }
    (list->head = dummy.next)->prev=NULL;
    return list;
}

members_list *new_members_list() {
    members_list *l = (members_list *) malloc(sizeof(members_list));
    if (l == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    l->head = NULL;
    l->tail = NULL;
    return l;
}

member *new_member() {
    member *m = (member *) malloc(sizeof(member));
    if (m == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    return m;
}