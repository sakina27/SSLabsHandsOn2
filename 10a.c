/*
====================================================================================================
Name : 10a.c
Author : Sakina Baranwala
Description : Write a separate program using sigaction system call to catch the following signals.
              a. SIGSEGV
Date: 19th September, 2024
====================================================================================================
*/






#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

void handle_sigsegv(int signum) {
    printf("Caught SIGSEGV (Segmentation Fault)\n");
    exit(EXIT_FAILURE);
}

int main() {
    struct sigaction sa_sigsegv;

    sa_sigsegv.sa_handler = handle_sigsegv;
    sa_sigsegv.sa_flags = 0;
    sigemptyset(&sa_sigsegv.sa_mask);
    sigaction(SIGSEGV, &sa_sigsegv, NULL);
    while (1) {
        printf("Working...\n");
        sleep(1);
	int *p = NULL; *p = 42;
    }
    return 0;
}


/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./10a
Working...
Caught SIGSEGV (Segmentation Fault)*/
