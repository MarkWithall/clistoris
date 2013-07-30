#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "interfaces.h"

struct list_item
{
    union list_data data;
    struct list_item *next;
};

struct linked_list
{
    struct list;
    int count;
    struct list_item *current;
    enum list_data_type data_type;
    struct list_item *first;
    struct list_item *last;
};

struct linked_list *create_linked_list(enum list_data_type);
void destroy_linked_list(struct linked_list *);

#endif /* LINKED_LIST_H */

