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
    int count = l->get_count(l);
    ASSERT_EQUAL(count, 0, "Actual %d, expected %d");
END_TEST

TEST(adding_some_elements_increase_count)
    int count;
    l->add(l, data_for(10));
    l->add(l, data_for(20));
    l->add(l, data_for(30));
    count = l->get_count(l);
    ASSERT_EQUAL(count, 3, "Actual %d, expected %d");
END_TEST

TEST(clear_resets_count_to_zero)
    int count;
    l->add(l, data_for(10));
    l->add(l, data_for(20));
    l->add(l, data_for(30));
    l->clear(l);
    count = l->get_count(l);
    ASSERT_EQUAL(count, 0, "Actual %d, expected %d");
END_TEST

TEST(contains_non_existant_element_returns_false)
    int result = l->contains(l, data_for(10));
    ASSERT_FALSE(result, "Expected 0, actual %d");
END_TEST

TEST(contains_existing_element_returns_true)
    int result;
    l->add(l, data_for(10));
    result = l->contains(l, data_for(10));
    ASSERT_TRUE(result, "Expected 1, actual %d");
END_TEST

TEST(removing_element_removes_element)
    int result;
    l->add(l, data_for(10));
    l->remove(l, data_for(10));
    result = l->contains(l, data_for(10));
    ASSERT_FALSE(result, "Expected 0, actual %d");
END_TEST

TEST(removing_non_existant_element_returns_false)
    int result = l->remove(l, data_for(10));
    ASSERT_FALSE(result, "Expected 0, actual %d");
END_TEST

