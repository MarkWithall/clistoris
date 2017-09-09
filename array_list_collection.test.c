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
}

void
teardown()
{
    destroy_array_list(l);
}

TEST(count_for_empty_list_is_zero)
    int count = l->get_count(l);
    ASSERT_EQUAL(count, 0, "%d", "");
END_TEST

TEST(adding_some_elements_increase_count)
    int count;
    l->add(l, data_for(10));
    l->add(l, data_for(20));
    l->add(l, data_for(30));
    count = l->get_count(l);
    ASSERT_EQUAL(count, 3, "%d", "");
END_TEST

TEST(clear_resets_count_to_zero)
    int count;
    l->add(l, data_for(10));
    l->add(l, data_for(20));
    l->add(l, data_for(30));
    l->clear(l);
    count = l->get_count(l);
    ASSERT_EQUAL(count, 0, "%d", "");
END_TEST

TEST(contains_non_existant_element_returns_false)
    int r = l->contains(l, data_for(10));
    ASSERT_FALSE(r, "Expected 0");
END_TEST

TEST(contains_existing_element_returns_true)
    int r;
    l->add(l, data_for(10));
    r = l->contains(l, data_for(10));
    ASSERT_TRUE(r, "Expected 1");
END_TEST

TEST(removing_element_removes_element)
    int r;
    l->add(l, data_for(10));
    l->remove(l, data_for(10));
    r = l->contains(l, data_for(10));
    ASSERT_FALSE(r, "Expected 0");
END_TEST

TEST(removing_non_existant_element_returns_false)
    int r = l->remove(l, data_for(10));
    ASSERT_FALSE(r, "Expected 0");
END_TEST

