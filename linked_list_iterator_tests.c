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
}

void
teardown()
{
    destroy_linked_list(l);
}

TEST(first_move_next_moves_to_first_item)
    int i;

    l->move_next(l);
    i = l->get_current(l).as_int;
    ASSERT_EQUAL(i, 10, "Actual %d, expected %d");
END_TEST

TEST(first_move_next_returns_true)
    int result = l->move_next(l);
    ASSERT_TRUE(result, "Expected 1 but was %d");
END_TEST

TEST(second_move_next_returns_false)
    int result;
    l->move_next(l);
    result = l->move_next(l);
    ASSERT_FALSE(result, "Expected 0 but was %d");
END_TEST

TEST(second_move_next_resets)
    int i;

    l->move_next(l); /* moves to 10 */
    l->move_next(l); /* moves to end and resets */
    l->move_next(l); /* moves to 10 */
    i = l->get_current(l).as_int;
    ASSERT_EQUAL(i, 10, "Actual %d, expected %d");
END_TEST

TEST(reset_returns_to_beginning)
    int i;

    l->move_next(l); /* moves to 10 */
    l->reset(l);
    l->move_next(l); /* moves to 10 */
    i = l->get_current(l).as_int;
    ASSERT_EQUAL(i, 10, "Actual %d, expected %d");
END_TEST

