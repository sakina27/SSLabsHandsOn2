/*
=================================================================================================
Name : 8d.c
Author : Sakina Baranwala
Description : Write a separate program using signal system call to catch the following signals.
              d. SIGALRM (use alarm system call)
Date: 19th September, 2024
=================================================================================================
*/



#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sigalrm(int sig) {
    printf("Caught signal %d: Alarm signal received.\n", sig);
    exit(0);
}

int main() {
    signal(SIGALRM, handle_sigalrm);

    printf("Setting an alarm for 5 seconds...\n");
    alarm(5);  // Set an alarm for 5 seconds

    while (1) {
        printf("Waiting for the alarm to go off...\n");
        sleep(1);
    }

    return 0;
}


/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./8d
Setting an alarm for 5 seconds...
Waiting for the alarm to go off...
Waiting for the alarm to go off...
Waiting for the alarm to go off...
Waiting for the alarm to go off...
Waiting for the alarm to go off...
Caught signal 14: Alarm signal received.
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$
*/
