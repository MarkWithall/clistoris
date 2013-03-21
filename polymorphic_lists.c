#include <stdio.h>
#include <stdlib.h>

#include "array_list.h"

/*
 * To compile with GCC (pre 4.6.2):
 * >gcc -fms-extensions ...
 * 4.6.2+
 * >gcc -std=c11 ...
 */

union list_data item_for(int item)
{
    union list_data d;
    d.as_int = item;
    return d;
}

void print_list(struct iterator *l)
{
    while (l->move_next(l))
        printf("%d ", l->get_current(l).as_int);
    printf("\n");
}

int main(void)
{
    struct array_list *l = create_array_list(type_INT, 2);

    l->add(l, item_for(0));
    l->add(l, item_for(1));
    l->add(l, item_for(2));
    l->add(l, item_for(3));

    l->set_element_at(l, 2, item_for(42));

    printf("Element at 2: %d\n", l->get_element_at(l, 2).as_int);
    printf("Index of 42: %d\n", l->index_of(l, item_for(42)));

    l->insert_at(l, 2, item_for(13));

    print_list((struct iterator *)l);

    l->remove_at(l, 2);

    printf("Length: %d\n", l->get_count(l));
    
    if (l->contains(l, item_for(42)))
        printf("Contains 42\n");

    l->remove(l, item_for(42));

    if (! l->contains(l, item_for(42)))
        printf("Doesn't contain 42\n");

    print_list((struct iterator *)l);

    l->clear(l);

    print_list((struct iterator *)l);

    printf("Length: %d\n", l->get_count(l));

    destroy_array_list(l);

    exit(EXIT_SUCCESS);
}
