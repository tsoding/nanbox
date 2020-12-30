#ifndef NANBOX_H_
#define NANBOX_H_

#include <math.h>

#define SIGN_MASK (1LL << 63LL)
#define EXP_MASK (((1LL << 11LL) - 1LL) << 52LL)
#define FRACTION_MASK ((1LL << 52LL) - 1LL)
#define TYPE_MASK (((1LL << 4LL) - 1LL) << 48LL)
#define VALUE_MASK ((1LL << 48LL) - 1LL)

#define TYPE(n) ((1LL << 3LL) + n)

#define INTEGER_TYPE 1
#define POINTER_TYPE 2

double mk_inf(void);
double set_type(double x, uint64_t type);
uint64_t get_type(double x);
double set_value(double x, uint64_t value);
uint64_t get_value(double x);
int is_double(double x);
int is_integer(double x);
int is_pointer(double x);
double as_double(double x);
uint64_t as_integer(double x);
void *as_pointer(double x);
double box_double(double x);
double box_integer(uint64_t x);
double box_pointer(void* x);

#endif // NANBOX_H_

#ifdef NANBOX_IMPLEMENTATION

double mk_inf(void)
{
    uint64_t y = EXP_MASK;
    return *(double*)&y;
}

double set_type(double x, uint64_t type)
{
    uint64_t y = *(uint64_t *)&x;
    y = (y & (~TYPE_MASK)) | (((TYPE_MASK >> 48LL) & type) << 48LL);
    return *(double*)&y;
}

uint64_t get_type(double x)
{
    uint64_t y = (*(uint64_t*)&x);
    return (y & TYPE_MASK) >> 48LL;
}

double set_value(double x, uint64_t value)
{
    uint64_t y = *(uint64_t *)&x;
    y = (y & (~VALUE_MASK)) | (value & VALUE_MASK);
    return *(double*)&y;
}

uint64_t get_value(double x)
{
    uint64_t y = (*(uint64_t*)&x);
    return (y & VALUE_MASK);
}

int is_double(double x)
{
    return !isnan(x);
}

int is_integer(double x)
{
    return isnan(x) && get_type(x) == TYPE(INTEGER_TYPE);
}

int is_pointer(double x)
{
    return isnan(x) && get_type(x) == TYPE(POINTER_TYPE);
}

double as_double(double x)
{
    return x;
}

uint64_t as_integer(double x)
{
    return get_value(x);
}

void *as_pointer(double x)
{
    return (void*) get_value(x);
}

double box_double(double x)
{
    return x;
}

double box_integer(uint64_t x)
{
    return set_value(set_type(mk_inf(), TYPE(INTEGER_TYPE)), x);
}

double box_pointer(void* x)
{
    return set_value(set_type(mk_inf(), TYPE(POINTER_TYPE)), (uint64_t) x);
}

#endif // NANBOX_IMPLEMENTATION
