#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int main() {
    printf("Starting program...\n");
    int x = 10;
    if (x > 5) {
        printf("x is greater than 5.\n");
        printf("Aborting the program...\n");
        abort(); // Exceptional termination of the program
    }
    printf("Program continues...\n");
    return 0;
}

