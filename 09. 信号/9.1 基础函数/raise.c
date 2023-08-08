#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>


int main() {
    printf("Sending SIGINT signal...\n");
    raise(SIGINT); // Send SIGINT signal to the current process
    printf("Signal sent.\n");
    return 0;
}
