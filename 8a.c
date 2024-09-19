/*
============================================================================
Name : 8a.c
Author : Sakina Baranwala
Description : Write a separate program using signal system call to catch the following signals.
a. SIGSEGV
Date: 19th September, 2024
============================================================================
*/







#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handle_sigsegv(int sig) {
    printf("Caught signal %d: Segmentation fault occurred.\n", sig);
    exit(1);
}

int main() {
    signal(SIGSEGV, handle_sigsegv);

    int *ptr = NULL;
    *ptr = 42;

    printf("This message will not be printed.\n");
    return 0;
}




/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./8a
Caught signal 11: Segmentation fault occurred.
*/
