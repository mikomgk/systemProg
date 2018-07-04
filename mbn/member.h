//
// Created by user on 7/4/18.
//

#ifndef MBN_MEMBER_H
#define MBN_MEMBER_H

typedef struct member{
    int id;
    int cost;
    int time;
    struct member *prev;
    struct member *next;
} member;

typedef struct members_list{
    struct member *head;
    struct member *tail;
} members_list;

members_list *add_member(members_list *list,int id,int cost,int time);
members_list *remove_member_id(members_list *list,int id);
members_list *new_members_list();

#endif //MBN_MEMBER_H
