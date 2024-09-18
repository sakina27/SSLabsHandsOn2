/*
============================================================================
Name : 10b.c
Author : Sakina Baranwala
Description : Write a separate program using sigaction system call to catch the following signals.
b. SIGINT
Date: 19th September, 2024
============================================================================
*/






#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

void handle_sigint(int signum) {
    printf("Caught SIGINT (Interrupt from keyboard)\n");
    exit(EXIT_SUCCESS);
}

int main() {
    struct sigaction sa_sigint;

    sa_sigint.sa_handler = handle_sigint;
    sa_sigint.sa_flags = 0;
    sigemptyset(&sa_sigint.sa_mask);
    sigaction(SIGINT, &sa_sigint, NULL);
    
    printf("Running... Press Ctrl+C to send SIGINT");
    while (1) {
        printf("Working...\n");
        sleep(1);
    }
    return 0;
}
   


/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./10b
Running... Press Ctrl+C to send SIGINTWorking...
Working...
Working...
Working...
Working...
^CCaught SIGINT (Interrupt from keyboard)
*/
