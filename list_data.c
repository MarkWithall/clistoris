#include "list_data.h"

#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024

union list_data empty_item()
{
	union list_data d;
	memset(&d, 0, sizeof(union list_data));
	return d;
}

int are_equal(union list_data d1, union list_data d2, enum list_data_type data_type)
{
	switch (data_type)
	{
	case type_CHARPTR:
		return strncmp(d1.as_char_ptr, d2.as_char_ptr, MAX_STRING_LENGTH) == 0;
	default:
		return memcmp(&d1, &d2, sizeof(union list_data)) == 0;
	}
}
