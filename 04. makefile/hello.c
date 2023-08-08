/*************************************************************************
        > File Name: test.c
        > Author: echo
        > Mail: echobydq@gmail.com
        > Created Time: Wed 26 Jul 2023 04:43:07 PM CST
 ************************************************************************/

#include <stdio.h>

int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int div1(int a, int b);
void finish(void);

int main()
{
    int a = 9, b = 3;
    printf("%d + %d = %d\n", a, b, add(a, b));
    printf("%d - %d = %d\n", a, b, sub(a, b));
    printf("%d * %d = %d\n", a, b, mul(a, b));
    printf("%d / %d = %d\n", a, b, div1(a, b));
    finish();

    return 0;
}
