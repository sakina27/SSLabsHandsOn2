/*
============================================================================
Name : 8c.c
Author : Sakina Baranwala
Description : Write a separate program using signal system call to catch the following signals.
c. SIGFPE
Date: 19th September, 2024
============================================================================
*/








#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handle_sigfpe(int sig) {
    printf("Caught signal %d: Floating point exception (division by zero).\n", sig);
    exit(1);
}

int main() {
    signal(SIGFPE, handle_sigfpe);

    int x = 5;
    int y = 0;
    int result = x / y; // Division by zero to trigger SIGFPE

    printf("This message will not be printed.\n");
    return 0;
}


/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./8c
Caught signal 8: Floating point exception (division by zero).*/
