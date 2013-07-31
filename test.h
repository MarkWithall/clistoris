#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>

#define TEST(test_name) \
    const char *test_name(void) \
    {

#define END_TEST \
        return NULL; \
    }

#define ASSERT_EQUAL(a, b, msg) \
    if (a != b) { \
        snprintf(error_message, ERROR_LENGTH, msg, a, b); \
        return error_message; \
    }

#define ASSERT_TRUE(a, msg) \
    if (!(a)) { \
        snprintf(error_message, ERROR_LENGTH, msg, a); \
        return error_message; \
    }

#define ASSERT_FALSE(a, msg) \
    if (a) { \
        snprintf(error_message, ERROR_LENGTH, msg, a); \
        return error_message; \
    }

#define ERROR_LENGTH 128
char error_message[ERROR_LENGTH];

void setup(void);
void teardown(void);

void test_fixture(int number_of_tests);
void run_test(const char *, int, const char *(*test)(void));

#endif /* TEST_H */

