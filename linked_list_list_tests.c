#include "test.h"

#include "linked_list.h"

struct linked_list *l;

union list_data data_for(int i)
{
    union list_data d = {.as_int = i};
    return d;
}

void
setup()
{
    l = create_linked_list(type_INT);
    l->add(l, data_for(10));
    l->add(l, data_for(20));
    l->add(l, data_for(30));
}

void
teardown()
{
    destroy_linked_list(l);
}

TEST(get_element_at_returns_expected)
    int item = l->get_element_at(l, 1).as_int;
    ASSERT_EQUAL(item, 20, "Actual %d, expected %d");
END_TEST

TEST(set_element_at_sets_element)
    int item;
    l->set_element_at(l, 1, data_for(15));
    item = l->get_element_at(l, 1).as_int;
    ASSERT_EQUAL(item, 15, "Actual %d, expected %d");
END_TEST

TEST(set_element_does_not_change_count)
    int count;
    l->set_element_at(l, 1, data_for(15));
    count = l->get_count(l);
    ASSERT_EQUAL(count, 3, "Actual %d, expected %d");
END_TEST

TEST(index_of_returns_correct_index)
    int index = l->index_of(l, data_for(20));
    ASSERT_EQUAL(index, 1, "Actual %d, expected %d");
END_TEST

TEST(insert_at_inserts_item)
    int item;
    l->insert_at(l, 1, data_for(15));
    item = l->get_element_at(l, 1).as_int;
    ASSERT_EQUAL(item, 15, "Actual %d, expected %d");
END_TEST

TEST(insert_at_moves_previous_item_along)
    int item;
    l->insert_at(l, 1, data_for(15));
    item = l->get_element_at(l, 2).as_int;
    ASSERT_EQUAL(item, 20, "Actual %d, expected %d");
END_TEST

TEST(insert_at_increase_count)
    int count;
    l->insert_at(l, 1, data_for(15));
    count = l->get_count(l);
    ASSERT_EQUAL(count, 4, "Actual %d, expected %d");
END_TEST

TEST(remove_at_removes_item)
    int result;
    l->remove_at(l, 1);
    result = l->contains(l, data_for(20));
    ASSERT_FALSE(result, "Expected 0, actual %d");
END_TEST

TEST(remove_at_moved_next_item_back)
    int item;
    l->remove_at(l, 1);
    item = l->get_element_at(l, 1).as_int;
    ASSERT_EQUAL(item, 30, "Actual %d, expected %d");
END_TEST

TEST(remove_at_decreased_count)
    int count;
    l->remove_at(l, 1);
    count = l->get_count(l);
    ASSERT_EQUAL(count, 2, "Actual %d, expected %d");
END_TEST

