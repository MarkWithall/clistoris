#ifndef _LIST_DATA_H
#define _LIST_DATA_H

/*
 * Official type list: http://en.wikipedia.org/wiki/C_data_types#Basic_types
 * char, short, unsigned short, int, unsigned int, long, unsigned long,
 * long long, unsigned long long, float, double, long double
 */

enum list_data_type
{
    type_UNKNOWN,
    type_VOIDPTR,
    type_CHARPTR,
    type_CHAR,
    type_SHORT,
    type_USHORT,
    type_INT,
    type_UINT,
    type_LONG,
    type_ULONG,
    type_LONGLONG,
    type_ULONGLONG,
    type_FLOAT,
    type_DOUBLE,
    type_LONGDOUBLE
};

union list_data
{
    void *as_void_ptr;
    char *as_char_ptr;
    char as_char;
    short as_short;
    unsigned short as_unsigned_short;
    int as_int;
    unsigned int as_unsigned_int;
    long as_long;
    unsigned long as_unsigned_long;
    long long as_long_long;
    unsigned long long as_unsigned_long_long;
    float as_float;
    double as_double;
    long double as_long_double;
};

union list_data empty_item();
int are_equal(union list_data d1, union list_data d2, enum list_data_type data_type);

#endif /* _LIST_DATA_H */

