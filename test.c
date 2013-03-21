#include "test.h"

struct test_results m_results;

void
test_fixture(const char *fixture_name)
{
    printf("===\nFixture: %s\n--\n", fixture_name);
    m_results.passes = 0;
    m_results.failures = 0;
}

void
run_test(const char *(*test)(void))
{
    const char *test_result;

    setup();
    test_result = (*test)();
    if (test_result == NULL) {
        printf("PASS\n");
        ++m_results.passes;
    }
    else {
        printf("FAIL (%s)\n", test_result);
        ++m_results.failures;
    }
    teardown();
}

void
display_results(void)
{
    int total = m_results.passes + m_results.failures;
    float percentage = (total > 0) ? (100.0 * m_results.passes)/total : 0.0;
    printf("--\nResults: %d/%d passed (%0.2f%%)\n===\n\n", m_results.passes, total, percentage);
}

