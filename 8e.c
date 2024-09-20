/*
=================================================================================================
Name : 8e.c
Author : Sakina Baranwala
Description : Write a separate program using signal system call to catch the following signals.
              e. SIGALRM (use setitimer system call)
Date: 19th September, 2024
=================================================================================================
*/







#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

void handle_sigalrm(int sig) {
    printf("Caught signal %d: Alarm signal received from setitimer.\n", sig);
    exit(0);
}

int main() {
    struct itimerval timer;

    signal(SIGALRM, handle_sigalrm);

    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);

    while (1) {
        printf("Waiting for the timer to go off...\n");
        sleep(1);
    }

    return 0;
}


/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./8e
Waiting for the timer to go off...
Waiting for the timer to go off...
Waiting for the timer to go off...
Caught signal 14: Alarm signal received from setitimer.*/
