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
    l->add(l, data_for(10));
    l->add(l, data_for(20));
    l->add(l, data_for(30));
}

void
teardown()
{
    destroy_array_list(l);
}

TEST(get_element_at_returns_expected)
    union list_data item = l->get_element_at(l, 1);
    if (item.as_int != 20)
        return "Expected item at index 1 to be 20";
END_TEST

TEST(set_element_at_sets_element)
    union list_data item;
    l->set_element_at(l, 1, data_for(15));
    item = l->get_element_at(l, 1);
    if (item.as_int != 15)
        return "Expected item at index 1 to be 15";
END_TEST

TEST(set_element_does_not_change_count)
    l->set_element_at(l, 1, data_for(15));
    if (l->get_count(l) != 3)
        return "Expected list count of 3";
END_TEST

TEST(index_of_returns_correct_index)
    if (l->index_of(l, data_for(20)) != 1)
        return "Expected index of 20 is 1";
END_TEST

TEST(insert_at_inserts_item)
    union list_data item;
    l->insert_at(l, 1, data_for(15));
    item = l->get_element_at(l, 1);
    if (item.as_int != 15)
        return "Expected item at index 1 to be 15";
END_TEST

TEST(insert_at_moves_previous_item_along)
    union list_data item;
    l->insert_at(l, 1, data_for(15));
    item = l->get_element_at(l, 2);
    if (item.as_int != 20)
        return "Expected item at index 2 to be 20";
END_TEST

TEST(insert_at_increase_count)
    l->insert_at(l, 1, data_for(15));
    if (l->get_count(l) != 4)
        return "Expected count of 4";
END_TEST

TEST(remove_at_removes_item)
    l->remove_at(l, 1);
    if (l->contains(l, data_for(20)))
        return "Expected list to not contain 20";
END_TEST

TEST(remove_at_moved_next_item_back)
    union list_data item;
    l->remove_at(l, 1);
    item = l->get_element_at(l, 1);
    if (item.as_int != 30)
        return "Expected item at index 1 to be 30";
END_TEST

TEST(remove_at_decreased_count)
    l->remove_at(l, 1);
    if (l->get_count(l) != 2)
        return "Expected count of 2";
END_TEST

