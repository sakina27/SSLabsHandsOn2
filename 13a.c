/*
============================================================================
Name : 13a.c
Author : Sakina Baranwala
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not.

Program 1 : to catch the stop signal
Date: 19th September, 2024
============================================================================
*/


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handle_sigstop(int sig) {
    printf("Caught signal %d: SIGSTOP\n", sig);
}

int main() {
    signal(SIGSTOP, handle_sigstop);

    printf("Waiting for SIGSTOP. My PID is %d\n", getpid());

    while (1) {
        // Infinite loop to keep the process running
        sleep(1);
    }

    return 0;
}


/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./13a
Waiting for SIGSTOP. My PID is 5613

[1]+  Stopped                 ./13a
*/
