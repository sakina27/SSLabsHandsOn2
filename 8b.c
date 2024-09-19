/*
============================================================================
Name : 8b.c
Author : Sakina Baranwala
Description : Write a separate program using signal system call to catch the following signals.
b. SIGINT
Date: 19th September, 2024
============================================================================
*/









#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handle_sigint(int sig) {
    printf("Caught signal %d: Interrupt signal received.\n", sig);
    exit(0);
}

int main() {
    signal(SIGINT, handle_sigint);

    while (1) {
        printf("Running... Press Ctrl+C to trigger SIGINT.\n");
        sleep(1);
    }

    return 0;
}



/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./8b
Running... Press Ctrl+C to trigger SIGINT.
Running... Press Ctrl+C to trigger SIGINT.
Running... Press Ctrl+C to trigger SIGINT.
^CCaught signal 2: Interrupt signal received.
*/
