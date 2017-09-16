#include "array_list.h"

#include <stdlib.h>

struct array_list *array_list_from(void *self)
{
    return (struct array_list *)self;
}

/*
 * iterator
 */

union list_data get_current(void *self)
{
    struct array_list *l = array_list_from(self);
    return l->items[l->current];
}

int move_next(void *self)
{
    struct array_list *l = array_list_from(self);
    ++l->current;
    if (l->current < l->count)
        return 1;
    l->reset(l);
    return 0;
}

void reset(void *self)
{
    struct array_list *l = array_list_from(self);
    l->current = -1;
}

/*
 * collection
 */

int get_count(void *self)
{
    struct array_list *l = array_list_from(self);
    return l->count;
}

void add(void *self, union list_data item)
{
    struct array_list *l = array_list_from(self);
    if (l->count == l->capacity)
    {
        l->capacity *= 2;
        l->items = realloc(l->items, sizeof(union list_data)*l->capacity);
    }
    l->items[l->count++] = item;
}

void clear(void *self)
{
    struct array_list *l = array_list_from(self);
    l->count = 0;
}

int contains(void *self, union list_data item)
{
    struct array_list *l = array_list_from(self);
    for (int i = 0; i < l->count; ++i)
        if (are_equal(l->items[i], item, l->data_type))
            return 1;
    return 0;
}

int remove_item(void *self, union list_data item)
{
    struct array_list *l = array_list_from(self);
    int removed = 0;
    for (int i = 0; i < l->count; ++i)
        if (removed)
            l->items[i-1] = l->items[i];
        else if (are_equal(l->items[i], item, l->data_type))
            removed = 1;
    if (removed)
        --(l->count);
    return removed;
}

/*
 * list
 */

union list_data get_element_at(void *self, int index)
{
    struct array_list *l = array_list_from(self);
    return l->items[index];
}

void set_element_at(void *self, int index, union list_data value)
{
    struct array_list *l = array_list_from(self);
    l->items[index].as_void_ptr = value.as_void_ptr;
}

int index_of(void *self, union list_data item)
{
    struct array_list *l = array_list_from(self);
    for (int i = 0; i < l->count; ++i)
        if (are_equal(l->items[i], item, l->data_type))
            return i;
    return -1;
}

void insert_at(void *self, int index, union list_data item)
{
    struct array_list *l = array_list_from(self);
    l->add(l, empty_item());
    for (int i = l->count-1; i > index; --i)
        l->items[i] = l->items[i-1];
    l->items[index].as_void_ptr = item.as_void_ptr;
}

void remove_at(void *self, int index)
{
    struct array_list *l = array_list_from(self);
    for (int i = index; i < (l->count - 1); ++i)
        l->items[i] = l->items[i + 1];
    --(l->count);
}

/*
 * constructor/destructor
 */

struct array_list *create_array_list(enum list_data_type data_type, int initial_capacity)
{
    struct array_list *l = malloc(sizeof(struct array_list));

    l->count = 0;
    l->current = -1;
    l->capacity = initial_capacity;
    l->data_type = data_type;
    l->items = malloc(sizeof(union list_data)*initial_capacity);

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

void destroy_array_list(struct array_list *l)
{
    free(l->items);
    free(l);
}

