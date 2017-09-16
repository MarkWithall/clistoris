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
}

void
teardown()
{
    destroy_array_list(l);
}

TEST(first_move_next_moves_to_first_item)
    l->move_next(l);
    int i = l->get_current(l).as_int;
    ASSERT_EQUAL(i, 10, "%d", "");
END_TEST

TEST(first_move_next_returns_true)
    int r = l->move_next(l);
    ASSERT_TRUE(r, "Expected 1");
END_TEST

TEST(second_move_next_returns_false)
    l->move_next(l);
    int r = l->move_next(l);
    ASSERT_FALSE(r, "Expected 0");
END_TEST

TEST(second_move_next_resets)
    l->move_next(l); /* moves to 10 */
    l->move_next(l); /* moves to end and resets */
    l->move_next(l); /* moves to 10 */
    int i = l->get_current(l).as_int;
    ASSERT_EQUAL(i, 10, "%d", "");
END_TEST

TEST(reset_returns_to_beginning)
    l->move_next(l); /* moves to 10 */
    l->reset(l);
    l->move_next(l); /* moves to 10 */
    int i = l->get_current(l).as_int;
    ASSERT_EQUAL(i, 10, "%d", "");
END_TEST

