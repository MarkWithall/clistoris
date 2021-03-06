#include "TESTickle.h"

#include "array_list.h"

struct array_list *l;

union list_data data_for(int i)
{
    union list_data d = (union list_data)0;
    d.as_int = i;
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
    int item = l->get_element_at(l, 1).as_int;
    ASSERT_EQUAL(item, 20, "%d", "");
END_TEST

TEST(set_element_at_sets_element)
    l->set_element_at(l, 1, data_for(15));
    int item = l->get_element_at(l, 1).as_int;
    ASSERT_EQUAL(item, 15, "%d", "");
END_TEST

TEST(set_element_does_not_change_count)
    l->set_element_at(l, 1, data_for(15));
    int count = l->get_count(l);
    ASSERT_EQUAL(count, 3, "%d", "");
END_TEST

TEST(index_of_returns_correct_index)
    int index = l->index_of(l, data_for(20));
    ASSERT_EQUAL(index, 1, "%d", "");
END_TEST

TEST(insert_at_inserts_item)
    l->insert_at(l, 1, data_for(15));
    int item = l->get_element_at(l, 1).as_int;
    ASSERT_EQUAL(item, 15, "%d", "");
END_TEST

TEST(insert_at_moves_previous_item_along)
    l->insert_at(l, 1, data_for(15));
    int item = l->get_element_at(l, 2).as_int;
    ASSERT_EQUAL(item, 20, "%d", "");
END_TEST

TEST(insert_at_increase_count)
    l->insert_at(l, 1, data_for(15));
    int count = l->get_count(l);
    ASSERT_EQUAL(count, 4, "%d", "");
END_TEST

TEST(remove_at_removes_item)
    l->remove_at(l, 1);
    int r = l->contains(l, data_for(20));
    ASSERT_FALSE(r, "Expected 0");
END_TEST

TEST(remove_at_moved_next_item_back)
    l->remove_at(l, 1);
    int item = l->get_element_at(l, 1).as_int;
    ASSERT_EQUAL(item, 30, "%d", "");
END_TEST

TEST(remove_at_decreased_count)
    l->remove_at(l, 1);
    int count = l->get_count(l);
    ASSERT_EQUAL(count, 2, "%d", "");
END_TEST

