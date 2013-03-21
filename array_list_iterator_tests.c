#include "test.h"

#include <stdlib.h>

#include "array_list.h"

struct array_list *l;

union list_data data_for(int i)
{
    union list_data d = {.as_int = i};
    return d;
}

void
setup()
{
    l = create_array_list(type_INT, 2);
    l->add(l, data_for(10)); 
}

void
teardown()
{
    destroy_array_list(l);
}

TEST(first_move_next_moves_to_first_item)
    int i;

    l->move_next(l);
    i = l->get_current(l).as_int;
    if (i != 10)
        return "current value expected 10";
END_TEST

int main(void)
{
    test_fixture("array_list iterator tests");

    run_test(first_move_next_moves_to_first_item);

    display_results();

    exit(EXIT_SUCCESS);
}

