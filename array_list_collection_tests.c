#include "test.h"

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
}

void
teardown()
{
    destroy_array_list(l);
}

TEST(count_for_empty_list_is_zero)
    if (l->get_count(l) != 0)
        return "Expected count is zero";
END_TEST

TEST(adding_some_elements_increase_count)
    l->add(l, data_for(10));
    l->add(l, data_for(20));
    l->add(l, data_for(30));
    if (l->get_count(l) != 3)
        return "Expected count is 3";
END_TEST

TEST(clear_resets_count_to_zero)
    l->add(l, data_for(10));
    l->add(l, data_for(20));
    l->add(l, data_for(30));
    l->clear(l);
    if (l->get_count(l) != 0)
        return "Expected count is zero";
END_TEST

