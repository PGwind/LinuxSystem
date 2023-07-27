/*************************************************************************
        > File Name: test.c
        > Author: echo
        > Mail: echobydq@gmail.com
        > Created Time: Wed 26 Jul 2023 04:43:07 PM CST
 ************************************************************************/

#include <stdio.h>
#include "mymath.h"

int main()
{
    int a = 4, b = 2;
    printf("%d + %d = %d\n", a, b, add(a, b));
    printf("%d - %d = %d\n", a, b, sub(a, b));
    printf("%d * %d = %d\n", a, b, mul(a, b));
    printf("%d / %d = %d\n", a, b, div1(a, b));

    return 0;
}
