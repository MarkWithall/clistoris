#pragma once

#include "interfaces.h"

struct array_list
{
    struct list;
    int count;
    int capacity;
    int current;
    enum list_data_type data_type;
    union list_data *items;
};

struct array_list *create_array_list(enum list_data_type, int);
void destroy_array_list(struct array_list *);

