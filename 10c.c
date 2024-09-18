/*
============================================================================
Name : 10c.c
Author : Sakina Baranwala
Description : Write a separate program using sigaction system call to catch the following signals.
c. SIGFPE
Date: 19th September, 2024
============================================================================
*/






#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

void handle_sigfpe(int signum) {
    printf("Caught SIGFPE (Floating Point Exception)\n");
    exit(EXIT_FAILURE);
}

int main() {
    struct sigaction sa_sigfpe;

    sa_sigfpe.sa_handler = handle_sigfpe;
    sa_sigfpe.sa_flags = 0;
    sigemptyset(&sa_sigfpe.sa_mask);
    sigaction(SIGFPE, &sa_sigfpe, NULL);
    
    while (1) {
        printf("Working...\n");
        sleep(1);
        
        int result = 1 / 0;
    }
    return 0;
}


/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./10c
Working...
Caught SIGFPE (Floating Point Exception)
*/
