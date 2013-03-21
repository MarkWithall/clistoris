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
        return "Current value expected 10";
END_TEST

TEST(first_move_next_returns_true)
    if (l->move_next(l) == 0)
        return "Expected true but was false";
END_TEST

TEST(second_move_next_returns_false)
    l->move_next(l);
    if (l->move_next(l) != 0)
        return "Expected false but was true";
END_TEST

TEST(second_move_next_resets)
    int i;

    l->move_next(l); /* moves to 10 */
    l->move_next(l); /* moves to end and resets */
    l->move_next(l); /* moves to 10 */
    i = l->get_current(l).as_int;
    if (i != 10)
        return "Current value expected 10";
END_TEST

TEST(reset_returns_to_beginning)
    int i;

    l->move_next(l); /* moves to 10 */
    l->reset(l);
    l->move_next(l); /* moves to 10 */
    i = l->get_current(l).as_int;
    if (i != 10)
        return "Current value expected 10";
END_TEST

int main(void)
{
    test_fixture("array_list iterator tests");

    run_test(first_move_next_moves_to_first_item);
    run_test(first_move_next_returns_true);
    run_test(second_move_next_returns_false);
    run_test(second_move_next_resets);
    run_test(reset_returns_to_beginning);

    display_results();

    exit(EXIT_SUCCESS);
}

