#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NANBOX_IMPLEMENTATION
#include "./nanbox.h"

int main(void)
{
    double pi = 3.14159265359;

    assert(pi         == as_double(box_double(pi)));
    assert(12345678LL == as_integer(box_integer(12345678LL)));
    assert(&pi        == as_pointer(box_pointer(&pi)));

    printf("OK\n");

    return 0;
}
