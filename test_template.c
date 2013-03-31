#include <stdlib.h>
#include "test.h"

[% FOREACH test IN tests %]const char *[% test %]();
[% END %]
int
main(void)
{
    test_fixture("[% fixture %]");

[% FOREACH test IN tests %]    run_test([% test %]);
[% END %]
    display_results();

    exit(EXIT_SUCCESS);
}

