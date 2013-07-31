#include "test.h"

void
test_fixture(const int number_of_tests)
{
    printf("TAP version 13\n");
    printf("1..%d\n", number_of_tests);
}

void
run_test(const char *test_name, int test_number, const char *(*test)(void))
{
    const char *test_result;

    setup();
    test_result = (*test)();
    if (test_result == NULL) {
        printf("ok %d - %s\n", test_number, test_name);
    }
    else {
        printf("not ok %d - %s\n", test_number, test_name);
        printf("  ---\n");
        printf("  message: '%s'\n", test_result);
        printf("  severity: fail\n");
        printf("  ...\n");
    }
    teardown();
}
