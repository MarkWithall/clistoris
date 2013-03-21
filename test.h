#ifndef _TEST_H
#define _TEST_H

#include <stdio.h>
#include <stdlib.h>

#define TEST(test_name) \
    const char *test_name(void) \
    { \
        printf("%s...", #test_name);

#define END_TEST \
        return NULL; \
    }

struct test_results
{
    int passes;
    int failures;
};

void setup(void);
void teardown(void);

void test_fixture(const char *);
void run_test(const char *(*test)(void));
void display_results(void);

#endif /* _TEST_H */

