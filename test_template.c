#include <stdlib.h>
#include "test.h"

[% FOREACH test IN tests %]const char *[% test.name %]();
[% END %]
int
main(void)
{
    test_fixture([% number_of_tests %]);

[% FOREACH test IN tests %]    run_test("[% test.name %]", [% test.number %], [% test.name %]);
[% END %]

    exit(EXIT_SUCCESS);
}

