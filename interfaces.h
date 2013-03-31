#ifndef _INTERFACES_H
#define _INTERFACES_H

#include "list_data.h"

struct iterator
{
    union list_data (*get_current)(void *self);
    int (*move_next)(void *self);
    void (*reset)(void *self);
};

struct collection
{
    struct iterator; /* in C11 standard + M$ */
    int (*get_count)(void *self);
    void (*add)(void *self, union list_data item);
    void (*clear)(void *self);
    int (*contains)(void *self, union list_data item);
    int (*remove)(void *self, union list_data item);
};

struct list
{
    struct collection; /* in C11 standard + M$ */
    union list_data (*get_element_at)(void *self, int index);
    void (*set_element_at)(void *self, int index, union list_data value);
    int (*index_of)(void *self, union list_data item);
    void (*insert_at)(void *self, int index, union list_data item);
    void (*remove_at)(void *self, int index);
};

#endif /* _INTERFACES_H */

