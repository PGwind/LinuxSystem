/*************************************************************************
        > File Name: getc_cmp_read.c
        > Author: echo
        > Mail: echobydq@gmail.com
        > Created Time: Fri 28 Jul 2023 01:31:36 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp, *fp_out;
    int n;

    fp = fopen("test.txt", "r");
    if (fp == NULL) {
        perror("fopen error");
        exit(1);
    }

    fp_out = fopen("test.cp", "w");
    if (fp_out == NULL) {
        perror("fopen error");
        exit(1);
    }

    while ((n = fgetc(fp)) != EOF) {
        fputc(n, fp_out);
    }

    fclose(fp);
    fclose(fp_out);

    return 0;
}

