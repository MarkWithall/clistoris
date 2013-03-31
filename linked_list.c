#include "linked_list.h"

#include <stdlib.h>

struct linked_list *linked_list_from(void *self)
{
    return (struct linked_list *)self;
}

/*
 * iterator
 */

union list_data get_current(void *self)
{
    struct linked_list *l = linked_list_from(self);
    return l->current->data;
}

int move_next(void *self)
{
    struct linked_list *l = linked_list_from(self);
    if (l->current == NULL)
        l->current = l->first;
    else
        l->current = l->current->next;
    return l->current != NULL;
}

void reset(void *self)
{
    struct linked_list *l = linked_list_from(self);
    l->current = NULL;
}

/*
 * collection
 */

int get_count(void *self)
{
    return linked_list_from(self)->count;
}

void add(void *self, union list_data item)
{
    struct linked_list *l = linked_list_from(self);
    struct list_item *new = malloc(sizeof(struct list_item));
    new->data = item;
    new->next = NULL;
    if (l->first == NULL)
    {
        l->first = new;
        l->last = new;
    }
    else
    {
        l->last->next = new;
        l->last = new;
    }
    l->count++;
}

void clear(void *self)
{
    struct linked_list *l = linked_list_from(self);
    struct list_item *item = l->first;
    struct list_item *temp;
    while (item != NULL)
    {
        temp = item;
        item = item->next;
        free(temp);
    }
    l->count = 0;
    l->first = NULL;
    l->last = NULL;
}

int contains(void *self, union list_data item)
{
    struct linked_list *l = linked_list_from(self);
    struct list_item *node = l->first;
    while (node != NULL)
    {
        if (are_equal(node->data, item, l->data_type))
            return 1;
        node = node->next;
    }
    return 0;
}

int remove_item(void *self, union list_data item)
{
    struct linked_list *l = linked_list_from(self);
    struct list_item *node = l->first;
    struct list_item *previous = NULL;
    while (node != NULL)
    {
        if (are_equal(node->data, item, l->data_type))
        {
            if (previous != NULL)
                previous->next = node->next;
            else
                l->first = node->next;
            free(node);
            l->count--;
            return 1;
        }
        previous = node;
        node = node->next;
    }
    return 0;
}

/*
 * list
 */

union list_data get_element_at(void *self, int index)
{
    struct linked_list *l = linked_list_from(self);
    struct list_item *node = l->first;
    int i = 0;
    while (node != NULL)
    {
        if (i == index)
            return node->data;
        node = node->next;
        ++i;
    }
    return (union list_data)NULL;
}

void set_element_at(void *self, int index, union list_data value)
{
    struct linked_list *l = linked_list_from(self);
    struct list_item *node = l->first;
    int i = 0;
    while (node != NULL)
    {
        if (i == index)
        {
            node->data = value;
            return;
        }
        node = node->next;
        ++i;
    }
}

int index_of(void *self, union list_data item)
{
    struct linked_list *l = linked_list_from(self);
    struct list_item *node = l->first;
    int i = 0;
    while (node != NULL)
    {
        if (are_equal(node->data, item, l->data_type))
            return i;
        node = node->next;
        ++i;
    }
    return -1;
}

void insert_at(void *self, int index, union list_data item)
{
    struct linked_list *l = linked_list_from(self);
    struct list_item *node = l->first;
    struct list_item *previous = NULL;
    struct list_item *new = malloc(sizeof(struct list_item));
    new->data = item;
    new->next = NULL;
    int i = 0;
    while (node != NULL)
    {
        if (i == index)
        {
            if (previous != NULL)
            {
                new->next = previous->next;
                previous->next = new;
                l->count++;
                return;
            }
            else
            {
                l->first = new;
                l->last = new;
                l->count++;
                return;
            }
        }
        previous = node;
        node = node->next;
        ++i;
    }
    l->count++;
}

void remove_at(void *self, int index)
{
    struct linked_list *l = linked_list_from(self);
    struct list_item *node = l->first;
    struct list_item *previous = NULL;
    int i = 0;
    while (node != NULL)
    {
        if (i == index) {
            previous->next = node->next;
            free(node);
            l->count--;
            return;
        }
        previous = node;
        node = node->next;
        ++i;
    }
}

/*
 * constructor/destructor
 */

struct linked_list *create_linked_list(enum list_data_type data_type)
{
    struct linked_list *l = malloc(sizeof(struct linked_list));

    l->count = 0;
    l->current = NULL;
    l->data_type = data_type;
    l->first = NULL;
    l->last = NULL;

    /* iterator */
    l->get_current = &get_current;
    l->move_next = &move_next;
    l->reset = &reset;

    /* collection */
    l->get_count = &get_count;
    l->add = &add;
    l->clear = &clear;
    l->contains = &contains;
    l->remove = &remove_item;

    /* list */
    l->get_element_at = &get_element_at;
    l->set_element_at = &set_element_at;
    l->index_of = &index_of;
    l->insert_at = &insert_at;
    l->remove_at = &remove_at;

    return l;
}

void destroy_linked_list(struct linked_list *l)
{
    struct list_item *item = l->first;
    struct list_item *temp;
    while (item != NULL)
    {
        temp = item;
        item = item->next;
        free(temp);
    }
    free(l);
}

